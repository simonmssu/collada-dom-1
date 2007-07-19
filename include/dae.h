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

class daeIDRefResolver;
class domCOLLADA;

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
class DAE : public daeInterface
{
public:	
	/** 
	*  Constructor.
	*/
	DLLSPEC DAE() {
		// See the end of the thread linked below for an explanation of why we have the DAE
		// constructor set up this way. Basically, I'm going to be changing the build output 
		// location, and when this happens people sometimes continue to link against the old
		// libraries by accident (e.g. if they just do an svn update). By introducing a new
		// function that gets called from a function in a header file, I'm ensuring that someone
		// who tries linking against old libraries will get a link error. This may not sound
		// very nice, but it's certainly better than getting bizarre runtime crashes.
		// https://collada.org/public_forum/viewtopic.php?t=771&sid=f13c34f2d17ca720c5021bccbe5128b7
		init();
	}

	/** 
	* Destructor.
	*/	
	virtual DLLSPEC ~DAE();

	/**
	 * Releases all static meta information associated with the COLLADA DOM.
	 * Ff there are no remaining instances of a @c DAE cleanup happens automatically.
	 * @note This function is useless if called by the application in a non-static
	 * context.
	 */
	static DLLSPEC void cleanup();
	
	// Abstract Interface Class for the daeDatabase front end
public:
	// Database setup	
	virtual DLLSPEC daeDatabase* getDatabase();
	virtual DLLSPEC daeInt setDatabase(daeDatabase* database);

	// IO Plugin setup
	virtual DLLSPEC daeIOPlugin* getIOPlugin();
	virtual DLLSPEC daeInt setIOPlugin(daeIOPlugin* plugin);

	// Integration Library Setup
	virtual DLLSPEC daeIntegrationLibraryFunc getIntegrationLibrary();
	virtual DLLSPEC daeInt setIntegrationLibrary(daeIntegrationLibraryFunc regFunc);

	// batch file operations
	virtual DLLSPEC daeInt load(daeString name, daeString docBuffer = NULL);
	virtual DLLSPEC daeInt save(daeString documentName, daeBool replace=true);
	virtual DLLSPEC daeInt save(daeUInt documentIndex, daeBool replace=true);
	virtual DLLSPEC daeInt saveAs(daeString name, daeString documentName, daeBool replace=true);
	virtual DLLSPEC daeInt saveAs(daeString name, daeUInt documentIndex=0, daeBool replace=true);

	virtual DLLSPEC daeInt unload(daeString name);
	virtual DLLSPEC daeInt clear();

	// Load/Save Progress	
	virtual DLLSPEC void getProgress(daeInt* bytesParsed,
		daeInt* lineNumber,
		daeInt* totalBytes,
		daeBool reset = false );

	// Simple Query
	virtual DLLSPEC domCOLLADA* getDom(daeString name);
	virtual DLLSPEC daeString getDomVersion();
	virtual DLLSPEC daeInt setDom(daeString name, domCOLLADA* dom);

private:
	void DLLSPEC init();

	daeDatabase *database;
	daeIOPlugin *plugin;
	daeURIResolver* resolver;
	daeURIResolver* rawResolver;
	daeIDRefResolver* idResolver;
	bool defaultDatabase;
	bool defaultPlugin;
	daeIntegrationLibraryFunc registerFunc; 
	static daeMetaElement *topMeta;
};

#endif // __DAE_INTERFACE__
