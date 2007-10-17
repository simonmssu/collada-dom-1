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

#ifndef __DAE_IO_PLUGIN_COMMON__
#define __DAE_IO_PLUGIN_COMMON__

#include <vector>
#include <dae/daeElement.h>
#include <dae/daeURI.h>
#include <dae/daeMetaAttribute.h>
#include <dae/daeIOPlugin.h>

class daeIntegrationObject;
class daeMetaElement;
class daeDocument;

/**
 * The @c daeIOPluginCommon class was created to serve as a base class for the common functionality
 * between the daeLIBXMLPlugin and daeTinyXMLPlugin classes.
 */
class daeIOPluginCommon : public daeIOPlugin {
public:
	/**
	 * Constructor.
	 */
	DLLSPEC daeIOPluginCommon();
	/**
	 * Destructor.
	 */
	virtual DLLSPEC ~daeIOPluginCommon();

	virtual DLLSPEC daeInt setMeta(daeMetaElement *topMeta);

	// Database setup	
	virtual DLLSPEC void setDatabase(daeDatabase* database);

	// Operations
	virtual DLLSPEC daeInt read(daeURI& uri, daeString docBuffer);

protected:
	daeDatabase* database;

	// On failure, these functions return NULL
	virtual DLLSPEC daeElementRef readFromFile(const daeURI& uri) = 0;
	virtual DLLSPEC daeElementRef readFromMemory(daeString buffer, const daeURI& baseUri) = 0;

  // Reading support for subclasses
	typedef std::pair<daeString, daeString> attrPair;
	DLLSPEC daeElementRef beginReadElement(daeElement* parentElement, 
																				 daeString elementName, 
																				 const std::vector<attrPair>& attributes,
																				 daeInt lineNumber);
	DLLSPEC bool readElementText(daeElement* element, daeString text, daeInt elementLineNumber);

private:
	typedef struct
	{
		daeElement* element;
		daeIntegrationObject* intObject;
	} INTEGRATION_ITEM;
	
	daeMetaElement* topMeta;

	void postProcessDom(daeDocument *document, daeElement* element, std::vector<INTEGRATION_ITEM> &intItems);
};

#endif //__DAE_IO_PLUGIN_COMMON__
