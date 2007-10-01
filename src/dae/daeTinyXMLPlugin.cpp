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

// The user can choose whether or not to include TinyXML support in the DOM. Supporting TinyXML will
// require linking against it. By default TinyXML support isn't included.
#if defined(DOM_INCLUDE_TINYXML)

#if defined(DOM_DYNAMIC)
#pragma comment(lib, "tinyxml.lib")
#endif

#pragma warning(disable: 4100) // warning C4100: 'element' : unreferenced formal parameter

#include <string>
#include <tinyxml.h>
#include <dae.h>
#include <dom.h>
#include <dae/daeMetaElement.h>
#include <dae/daeErrorHandler.h>
#include <dae/daeMetaElementAttribute.h>
#include <dae/daeTinyXMLPlugin.h>

namespace {
	daeInt getCurrentLineNumber(TiXmlElement* element) {
		return -1;
	}
}

daeTinyXMLPlugin::daeTinyXMLPlugin()
{
  m_doc = NULL;
}

daeTinyXMLPlugin::~daeTinyXMLPlugin()
{
}

daeInt daeTinyXMLPlugin::setOption( daeString option, daeString value )
{
	return DAE_ERR_INVALID_CALL;
}

daeString daeTinyXMLPlugin::getOption( daeString option )
{
	return NULL;
}

void daeTinyXMLPlugin::getProgress(daeInt* bytesParsed,
						 daeInt* lineNumber,
						 daeInt* totalBytes,
						 daeBool reset)
{
	if (totalBytes)
		*totalBytes = 0; // Not available
}


daeElementRef daeTinyXMLPlugin::readFromFile(const daeURI& uri) {
	// !!!steveT: Replace this with real URI to file path code, and update the resolver to only handle the file scheme
	TiXmlDocument doc;
	char file[512];
	uri.getPath(file, 512);
#if defined(WIN32)
	doc.LoadFile(&file[1]);
#else
	doc.LoadFile(&file[0]);
#endif
	if (!doc.RootElement()) {
		daeErrorHandler::get()->handleError((std::string("Failed to open ") + uri.getURI() +
																				 " in daeTinyXMLPlugin::readFromFile\n").c_str());
		return NULL;
	}
	return readElement(doc.RootElement(), NULL);
}

daeElementRef daeTinyXMLPlugin::readFromMemory(daeString buffer, const daeURI& baseUri) {
	TiXmlDocument doc;
	doc.Parse(buffer);
	if (!doc.RootElement()) {
		daeErrorHandler::get()->handleError("Failed to open XML document from memory buffer in "
																				"daeTinyXMLPlugin::readFromMemory\n");
		return NULL;
	}
	return readElement(doc.RootElement(), NULL);
}

daeElementRef daeTinyXMLPlugin::readElement(TiXmlElement* tinyXmlElement, daeElement* parentElement) {
	std::vector<attrPair> attributes;
	for (TiXmlAttribute* attrib = tinyXmlElement->FirstAttribute(); attrib != NULL; attrib = attrib->Next())
		attributes.push_back(attrPair(attrib->Name(), attrib->Value()));
		
	daeElementRef element = beginReadElement(parentElement, tinyXmlElement->Value(),
																					 attributes, getCurrentLineNumber(tinyXmlElement));
	if (!element) {
		// We couldn't create the element. beginReadElement already printed an error message.
		return NULL;
	}

  if (tinyXmlElement->GetText() != NULL)
		readElementText(element, tinyXmlElement->GetText(), getCurrentLineNumber(tinyXmlElement));
  
  // Recurse children
  for (TiXmlElement* child = tinyXmlElement->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
    element->placeElement(readElement(child, element));

	return element;
}

daeInt daeTinyXMLPlugin::write(daeURI *name, daeDocument *document, daeBool replace)
{
	// Make sure database and document are both set
	if (!database)
		return DAE_ERR_INVALID_CALL;
	if(!document)
		return DAE_ERR_COLLECTION_DOES_NOT_EXIST;

	// !!!steveT: Do a decent URI to file path conversion
	// Extract just the file path from the URI
	daeFixedName finalname;
	if (!name->getPath(finalname,sizeof(finalname)))
	{
		daeErrorHandler::get()->handleError( "can't get path in write\n" );
		return DAE_ERR_BACKEND_IO;
	}
	// If replace=false, don't replace existing files
	if(!replace)
	{
		// Using "stat" would be better, but it's not available on all platforms
#ifdef WIN32
		FILE *tempfd = fopen(finalname+1,"r");
#else
		FILE *tempfd = fopen(finalname, "r");
#endif
		if(tempfd != NULL)
		{
			// File exists, return error
			fclose(tempfd);
			return DAE_ERR_BACKEND_FILE_EXISTS;
		}
		fclose(tempfd);
	}
	
  m_doc = new TiXmlDocument(name->getURI());
  if (m_doc)
  {
    m_doc->SetTabSize(4);

   	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );  
	  m_doc->LinkEndChild( decl ); 

    writeElement(document->getDomRoot());

#ifdef WIN32
		m_doc->SaveFile(finalname+1);
#else
    m_doc->SaveFile(finalname);
#endif
    delete m_doc;
    m_doc = NULL;
  }
	return DAE_OK;
}

void daeTinyXMLPlugin::writeElement( daeElement* element )
{
	daeIntegrationObject* _intObject = element->getIntObject();
	daeMetaElement* _meta = element->getMeta();
	if(_intObject)
	{
		// added in response to bug 478
		_intObject->toCOLLADAChecked();
		_intObject->toCOLLADAPostProcessChecked();
	}

  if (!_meta->getIsTransparent() ) 
  {
		TiXmlElement* tiElm = new TiXmlElement( element->getElementName() );  
        
		if (m_elements.empty() == true) {
				m_doc->LinkEndChild(tiElm);
			} else {
			TiXmlElement* first = m_elements.front();
			first->LinkEndChild(tiElm);
		}
		m_elements.push_front(tiElm);

		daeMetaAttributeRefArray& attrs = _meta->getMetaAttributes();
		
		int acnt = (int)attrs.getCount();
		
		for(int i=0;i<acnt;i++) 
    {
			writeAttribute( attrs[i], element );
		}
	}
	writeValue(element);
	
	daeElementRefArray children;
	element->getChildren( children );
	for ( size_t x = 0; x < children.getCount(); x++ ) 
  {
		writeElement( children.get(x) );
	}

	/*if (_meta->getContents() != NULL) {
		daeElementRefArray* era = (daeElementRefArray*)_meta->getContents()->getWritableMemory(element);
		int elemCnt = (int)era->getCount();
		for(int i = 0; i < elemCnt; i++) {
			daeElementRef elem = (daeElementRef)era->get(i);
			if (elem != NULL) {
				writeElement( elem );
			}
		}
	}
	else
	{
		daeMetaElementAttributeArray& children = _meta->getMetaElements();
		int cnt = (int)children.getCount();
		for(int i=0;i<cnt;i++) {
			daeMetaElement *type = children[i]->getElementType();
			if ( !type->getIsAbstract() ) {
				for (int c = 0; c < children[i]->getCount(element); c++ ) {
					writeElement( *(daeElementRef*)children[i]->get(element,c) );
				}
			}
		}
	}*/
	if (!_meta->getIsTransparent() ) 
  {
    m_elements.pop_front();
	}
}


void daeTinyXMLPlugin::writeValue( daeElement* element )
{
	if (daeMetaAttribute* attr = element->getMeta()->getValueAttribute()) {
		std::ostringstream buffer;
		attr->memoryToString(element, buffer);
		std::string s = buffer.str();
		if (!s.empty())
			m_elements.front()->LinkEndChild( new TiXmlText(buffer.str().c_str()) );
	}
}

void daeTinyXMLPlugin::writeAttribute( daeMetaAttribute* attr, daeElement* element )
{
	//don't write if !required and is set && is default
	if ( !attr->getIsRequired() )
	{
		//not required
		if ( !element->isAttributeSet( attr->getName() ) )
		{
			//early out if !value && !required && !set
			return;
		}
		
		//is set
		//check for default suppression
		if ( attr->getDefaultValue() != NULL )
		{
			//has a default value
			if (attr->compareToDefault(element) == 0) {
				// We match the default value, so exit early
				return;
			}
		}
	}

	std::ostringstream buffer;
	attr->memoryToString(element, buffer);
	m_elements.front()->SetAttribute(attr->getName(), buffer.str().c_str());
}

#endif // DOM_INCLUDE_TINYXML
