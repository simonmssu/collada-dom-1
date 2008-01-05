/*
 * Copyright 2006 Sony Computer Entertainment Inc.
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

#ifndef __DAE_STLDATABASE__
#define __DAE_STLDATABASE__

#include <stdio.h>

#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <functional>

#include <dae/daeElement.h>
#include <dae/daeDatabase.h>

/**
 * The @c daeSTLDatabase class derives from @c daeDatabase and implements
 * the default database.
 */
class DLLSPEC daeSTLDatabase : public daeDatabase
{
public:
	/**
	  * Constructor
	  */
	daeSTLDatabase(DAE& dae);
	/**
	  * Destructor
	  */
	virtual ~daeSTLDatabase();

public:
	// Element Types of all Elements
	virtual daeUInt getTypeCount();
	virtual daeString getTypeName(daeUInt index);
	virtual daeInt setMeta(daeMetaElement *_topMeta);

	// Documents
	virtual daeInt insertDocument(daeString name, daeElement* dom, daeDocument** document = NULL);
	virtual daeInt insertDocument(daeString name, daeDocument** document = NULL);
	virtual daeInt createDocument(daeString name, daeElement* dom, daeDocument** document = NULL);
	virtual daeInt createDocument(daeString name, daeDocument** document = NULL);
	virtual daeInt insertDocument( daeDocument *c );

	virtual daeInt removeDocument(daeDocument* document);
	virtual daeUInt getDocumentCount();
	virtual daeDocument* getDocument(daeUInt index);
	virtual daeDocument* getDocument(daeString name);
	virtual daeString getDocumentName(daeUInt index);
	virtual daeBool isDocumentLoaded(daeString name);

	// Elements 
	virtual daeInt insertElement(daeDocument* document, daeElement* element);
	virtual daeInt removeElement(daeDocument* document, daeElement* element); 
	virtual daeInt changeElementID(daeElement* element, daeString newID);
	virtual daeInt changeElementSID(daeElement* element, daeString newSID); // Not implemented
	virtual daeInt clear();
	virtual daeUInt getElementCount(daeString name = NULL,
	                                daeString type = NULL,
	                                daeString file = NULL);
	virtual daeInt getElement(daeElement** pElement, 
	                          daeInt index,
	                          daeString name = NULL,
	                          daeString type = NULL,
	                          daeString file = NULL); 

	// Not implemented
	virtual void sidLookup(const std::string& sid, std::list<daeElement*>& result);

	// Generic Query
	virtual daeInt queryElement(daeElement** pElement, daeString genericQuery);

	// !!!steveT Remove
	void getTypeList(const std::string& typeName, std::list<daeElement*>& result);
	void getTypeArray(const std::string& typeName, std::vector<daeElement*>& result);

private:

	std::map< std::string, std::vector< daeElement* > > elements; //map for all elements keyed on Type
	std::multimap< std::string, daeElement* > elementsIDMap; //map for elements keyed on ID

	std::multimap< std::string, daeElement* > sidMap; // sid --> element lookup table
	typedef std::pair<std::string, daeElement*> sidMapPair;
	typedef std::multimap<std::string, daeElement*>::iterator sidMapIter;

	std::vector<daeDocument*> documents;
	daeMetaElement* topMeta;

	daeInt insertChildren( daeDocument *c, daeElement *element );
	daeInt removeChildren( daeDocument *c, daeElement *element );
};

#endif // __DAE_STLDATABASE__
