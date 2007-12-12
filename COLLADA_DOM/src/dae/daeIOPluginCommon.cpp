/*
 * Copyright 2007 Sony Computer Entertainment Inc.
 *
 * Licensed under the SCEA Shared Source License, Version 1.0 (the "License"); you may not use this 
 * file except in compliance with the License. You may obtain a copy of the License at:
 * http://research.scea.com/scea_shared_source_license.html
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License 
 * is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or 
 * implied. See the License for the specific language governing permissions and limitations under the 
 * License. 
 */

#include <sstream>
#include <dae.h>
#include <dom.h>
#include <dae/daeDatabase.h>
#include <dae/daeIOPluginCommon.h>
#include <dae/daeMetaElement.h>
#include <dae/daeErrorHandler.h>
#include <dae/daeMetaElementAttribute.h>

using namespace std;

daeIOPluginCommon::daeIOPluginCommon()
	: database(NULL),
		topMeta(NULL)
{
}

daeIOPluginCommon::~daeIOPluginCommon()
{
}

daeInt daeIOPluginCommon::setMeta(daeMetaElement *_topMeta)
{
	topMeta = _topMeta;
	return DAE_OK;
}

void daeIOPluginCommon::setDatabase(daeDatabase* _database)
{
	database = _database;
}

// This function needs to be re-entrant, it can be called recursively from inside of resolveAll
// to load files that the first file depends on.
daeInt daeIOPluginCommon::read(daeURI& uri, daeString docBuffer)
{
	// Make sure topMeta has been set before proceeding
	if (topMeta == NULL) 
	{
		return DAE_ERR_BACKEND_IO;
	}

	// Generate a version of the URI with the fragment removed
	daeURI fileURI(*uri.getDAE(), uri.getURI(), true);

	//check if document already exists
	if ( database->isDocumentLoaded( fileURI.getURI() ) )
	{
		return DAE_ERR_COLLECTION_ALREADY_EXISTS;
	}

	daeElementRef domObject = docBuffer ?
		readFromMemory(docBuffer, fileURI) : // Load from memory (experimental)
		readFromFile(fileURI); // Load from URI

	if (!domObject) {
		string msg = docBuffer ?
			"Failed to load XML document from memory\n" :
			string("Failed to load ") + fileURI.getURI() + "\n";
		daeErrorHandler::get()->handleError(msg.c_str());
		return DAE_ERR_BACKEND_IO;
	}

	// Insert the document into the database, the Database will keep a ref on the main dom, so it won't get deleted
	// until we clear the database

	daeDocument *document = NULL;

	int res = database->insertDocument(fileURI.getURI(),domObject,&document);
	if (res!= DAE_OK)
		return res;

	// Make a vector to store a list of the integration items that need to be processed later
	// postProcessDom will fill this in for us (this should probably not be done in the IOPlugin)
	
	vector<INTEGRATION_ITEM> intItems;
	
	//insert the elements into the database, for this DB the elements are the Collada object which have
	//an ID. 
	//this function will fill the _integrationItems array as well
	postProcessDom(document, domObject, intItems);
	database->getDAE()->resolveAll();

	//create the integration objects
	int size = (int)intItems.size();
	int i;
	for (i=0;i<size;i++)
		intItems[i].intObject->createFromChecked(intItems[i].element);
	
	for (i=0;i<size;i++)
		intItems[i].intObject->fromCOLLADAChecked();

	for (i=0;i<size;i++)
		intItems[i].intObject->fromCOLLADAPostProcessChecked();

	return DAE_OK;
}

daeElementRef daeIOPluginCommon::beginReadElement(daeElement* parentElement,
																									daeString elementName,
																									const vector<attrPair>& attributes,
																									daeInt lineNumber) {
	daeMetaElement* parentMeta = parentElement ? parentElement->getMeta() : topMeta;
	daeElementRef element = parentMeta->create(elementName);
	
	if(!element)
	{
		ostringstream msg;
		msg << "The DOM was unable to create an element named " << elementName << " at line "
			     << lineNumber << ". Probably a schema violation.\n";
		daeErrorHandler::get()->handleWarning( msg.str().c_str() );
		return NULL;
	}

	// Process the attributes
	for (size_t i = 0; i < attributes.size(); i++) {
		daeString name  = attributes[i].first,
			        value = attributes[i].second;
		if (!element->setAttribute(name, value)) {
			ostringstream msg;
			msg << "The DOM was unable to create an attribute " << name << " = " << value
				  << " at line " << lineNumber << ".\nProbably a schema violation.\n";
			daeErrorHandler::get()->handleWarning(msg.str().c_str());
		}
	}
		
	if (parentElement == NULL) {
		// This is the root element. Check the COLLADA version.
		daeURI *xmlns = (daeURI*)(element->getMeta()->getMetaAttribute( "xmlns" )->getWritableMemory( element ));
		if ( strcmp( xmlns->getURI(), COLLADA_NAMESPACE ) != 0 ) {
			// Invalid COLLADA version
			daeErrorHandler::get()->handleError("Trying to load an invalid COLLADA version for this DOM build!");
			return NULL;
		}
	}
	
	return element;
}

bool daeIOPluginCommon::readElementText(daeElement* element, daeString text, daeInt elementLineNumber) {
	if (element->setCharData(text))
		return true;
	
	ostringstream msg;
	msg << "The DOM was unable to set a value for element of type " << element->getTypeName()
			<< " at line " << elementLineNumber << ".\nProbably a schema violation.\n";
	daeErrorHandler::get()->handleWarning(msg.str().c_str());
	return false;
}

// postProcessDom traverses all elements below the passed in one and creates a list of all the integration objects.
// this should probably NOT be done in the IO plugin.
void daeIOPluginCommon::postProcessDom(daeDocument *document, daeElement* element, std::vector<INTEGRATION_ITEM> &intItems)
{
	// Null element?  Return
	if (!element)
		return;

	// If this element has an integration object, add it to a list so we can process them all in a bunch later
	if (element->getIntObject(daeElement::int_uninitialized))
	{
		INTEGRATION_ITEM item;
		item.element = element;
		item.intObject = element->getIntObject(daeElement::int_uninitialized);
		intItems.push_back(item);
	}

	// Recursively call postProcessDom on all of this element's children
	daeElementRefArray children;
	element->getChildren( children );
	for ( size_t x = 0; x < children.getCount(); x++ ) {
		postProcessDom(document, children.get(x), intItems);
	}
}

