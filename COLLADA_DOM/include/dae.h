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

#ifndef __DAE__
#define __DAE__

#include <dae/daeTypes.h>
#include <dae/daeError.h>
#include <dae/daeInterface.h>
#include <dae/daeDatabase.h>
#include <dae/daeIOPlugin.h>
#include <dae/daeIntegrationObject.h>
#include <dae/daeAtomicType.h>
#include <dae/daeMetaElement.h>
#include <dae/daeIDRef.h>
#include <dae/daeURI.h>

class domCOLLADA;
class daeDatabase;

/**
 * The @c DAE class implements a standard interface to the
 * COLLADA runtime database.
 *
 * @c DAE serves as a wrapper for the entire pipeline ensuring
 * a consistent interface, regardless of extensions to or replacements
 * for the various API components. It provides methods to load, store,
 * translate and query COLLADA elements. A @c DAE object automatically creates
 * and initializes default versions of the COLLADA backend, the COLLADA
 * runtime database, and registered integration libraries. 
 */
class DLLSPEC DAE : public daeInterface
{
public:	
	/** 
	 *  Constructor.
	 */
	DAE(daeDatabase* database = NULL, daeIOPlugin* ioPlugin = NULL)
		: atomicTypes(*this),
	    baseUri(*this, true)
	{
		// See the end of the thread linked below for an explanation of why we have the DAE
		// constructor set up this way. Basically, I'm going to be changing the build output 
		// location, and when this happens people sometimes continue to link against the old
		// libraries by accident (e.g. if they just do an svn update). By introducing a new
		// function that gets called from a function in a header file, I'm ensuring that someone
		// who tries linking against old libraries will get a link error. This may not sound
		// very nice, but it's certainly better than getting bizarre runtime crashes.
		// https://collada.org/public_forum/viewtopic.php?t=771&sid=f13c34f2d17ca720c5021bccbe5128b7
		init(database, ioPlugin);
	}

	/** 
	* Destructor.
	*/	
	virtual ~DAE();

	/**
	 * Releases all static meta information associated with the COLLADA DOM.
	 * Ff there are no remaining instances of a @c DAE cleanup happens automatically.
	 * @note This function is useless if called by the application in a non-static
	 * context.
	 */
	static void cleanup();
	
	// Abstract Interface Class for the daeDatabase front end
public:
	// Database setup	
	virtual daeDatabase* getDatabase();
	virtual daeInt setDatabase(daeDatabase* database);

	// IO Plugin setup
	virtual daeIOPlugin* getIOPlugin();
	virtual daeInt setIOPlugin(daeIOPlugin* plugin);

	// Integration Library Setup
	virtual daeIntegrationLibraryFunc getIntegrationLibrary();
	virtual daeInt setIntegrationLibrary(daeIntegrationLibraryFunc regFunc);

	// batch file operations
	virtual daeInt load(daeString uri, daeString docBuffer = NULL);
	virtual daeInt save(daeString uri, daeBool replace=true);
	virtual daeInt save(daeUInt documentIndex, daeBool replace=true);
	virtual daeInt saveAs(daeString uriToSaveTo, daeString docUri, daeBool replace=true);
	virtual daeInt saveAs(daeString uriToSaveTo, daeUInt documentIndex=0, daeBool replace=true);
	virtual daeInt unload(daeString uri);

	// These are exactly the same as the other load/save/unload functions, except that they
	// work with file paths instead of URIs.
	virtual daeInt loadFile(daeString file, daeString memBuffer = NULL);
	virtual daeInt saveFile(daeString file, daeBool replace = true);
	virtual daeInt saveFileAs(daeString fileToSaveTo, daeString file, daeBool replace = true);
	virtual daeInt saveFileAs(daeString fileToSaveTo, daeUInt documentIndex = 0, daeBool replace = true);
	virtual daeInt unloadFile(daeString file);

	virtual daeInt clear();

	// Load/Save Progress	
	virtual void getProgress(daeInt* bytesParsed,
		daeInt* lineNumber,
		daeInt* totalBytes,
		daeBool reset = false );

	// Simple Query
	virtual domCOLLADA* getDom(daeString uri);
	virtual daeString getDomVersion();
	virtual daeInt setDom(daeString uri, domCOLLADA* dom);

	// Same as getDom/setDom, except works with file paths instead of URIs
	virtual domCOLLADA* getDomFile(daeString file);
	virtual daeInt      setDomFile(daeString file, domCOLLADA* dom);

	daeAtomicTypeList& getAtomicTypes();

	daeMetaElement* getMeta(daeInt typeID);
	daeMetaElementRefArray& getAllMetas();
	void setMeta(daeInt typeID, daeMetaElement& meta);

	/**
	 * Appends the passed in element to the list of elements that need to be resolved.
	 * The elements in this list will be resolved during @c resolveAll().
	 * @param elem Element to add to the list of elements
	 * waiting for their @c daeURIs to be resolved.
	 */
	void appendResolveElement(daeElement* elem);

	/**
	 * Resolves all @c daeURIs yet to be resolved in all @c daeElements that have been
	 * created.
	 * This is used as part of post-parsing process of a COLLADA instance document, 
	 * which results in a new document in the database.
	 */
	void resolveAll();

	daeURIResolverList& getURIResolvers();
	daeURI& getBaseURI();
	void setBaseURI(daeURI& uri);

	daeIDRefResolverList& getIDRefResolvers();

private:
	void init(daeDatabase* database, daeIOPlugin* ioPlugin);

	daeDatabase *database;
	daeIOPlugin *plugin;
	bool defaultDatabase;
	bool defaultPlugin;
	daeIntegrationLibraryFunc registerFunc; 
	daeMetaElement *topMeta;
	daeAtomicTypeList atomicTypes;
	daeMetaElementRefArray metas;
	daeElementRefArray resolveArray;
	daeURI baseUri;
	daeURIResolverList uriResolvers;
	daeIDRefResolverList idRefResolvers;
};


template <typename T> 
inline T *daeSafeCast( daeElement *element ) 
{ 
	if (element  &&  element->typeID() == T::typeIDStatic())
		return (T *)element; 
	return NULL; 
}


#endif // __DAE_INTERFACE__
