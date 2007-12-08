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

#include <dae.h>
#include <dae/daeDatabase.h>
#include <dae/daeDom.h>
#include <dae/daeIDRef.h>
#include <dae/daeMetaElement.h>
#include <modules/daeSTLDatabase.h>
#include <dae/daeErrorHandler.h>
#include <dae/daeRawResolver.h>
#include <dae/daeStandardURIResolver.h>

#ifndef NO_DEFAULT_PLUGIN

#ifdef DOM_INCLUDE_LIBXML
#include <modules/daeLIBXMLPlugin.h>
#endif

#ifdef DOM_INCLUDE_TINYXML
#include <dae/daeTinyXMLPlugin.h>
#endif

//This plugin is not provided with the public release. If you don't know about it then you don't need
//to worry about it.
#ifdef DEFAULT_BXCEPLUGIN
#include <modules/daebXCePlugin.h>
#endif

#endif // NO_DEFAULT_PLUGIN

using namespace std;

// Don't include domConstants.h because it varies depending on the dom version,
// just extern the one thing we need (COLLADA_VERSION) which all versions of
// domConstants.h/.cpp are required to define.

extern daeString COLLADA_VERSION;		 

daeInt DAEInstanceCount = 0;

void
DAE::cleanup()
{
	//Contributed by Nus - Wed, 08 Nov 2006
	daeStringRef::releaseStringTable();
	daeIDRefResolver::terminateIDRefSolver();
	//----------------------
}

void DAE::init(daeDatabase* database_, daeIOPlugin* ioPlugin) {
	database = NULL;
	plugin = NULL;
	idResolver = NULL;
	defaultDatabase = false;
	defaultPlugin = false;
	registerFunc = NULL;
	topMeta = NULL;

//Contributed by Nus - Wed, 08 Nov 2006
	daeIDRefResolver::initializeIDRefSolver();
//------------------------
	topMeta = initializeDomMeta(atomicTypes);
	DAEInstanceCount++;
	uriResolvers.addResolver(new daeStandardURIResolver(*this));
	uriResolvers.addResolver(new daeRawResolver(*this));
	idResolver = new daeDefaultIDRefResolver();

	setDatabase(database_);
	setIOPlugin(ioPlugin);
}

DAE::~DAE()
{
	if (defaultDatabase)
		delete database;
	if (defaultPlugin)
		delete plugin;
	delete idResolver;
	--DAEInstanceCount;
	if ( DAEInstanceCount <= 0 )
	{
		cleanup();
	}
}

// Database setup	
daeDatabase* DAE::getDatabase()
{
	return database;	
}

daeInt DAE::setDatabase(daeDatabase* _database)
{
	if (defaultDatabase)
		delete database;
	if (_database)
	{
		defaultDatabase = false;
		database = _database;
	}
	else
	{
		//create default database
		database = new daeSTLDatabase(*this);
		defaultDatabase = true;
	}
	// !!!GAC Not sure what good the error return is, current implementations never fail, what would we do if they did?
	int res = database->setMeta(topMeta);
	(void)res;
	((daeDefaultIDRefResolver*)idResolver)->setDatabase( database );
	return DAE_OK;
}

// IO Plugin setup
daeIOPlugin* DAE::getIOPlugin()
{
	return plugin;
}

daeInt DAE::setIOPlugin(daeIOPlugin* _plugin)
{
	if (defaultPlugin) 
		delete plugin;
	if (_plugin)
	{
		defaultPlugin = false;
		plugin = _plugin;
	}
	else
	{
#ifndef NO_DEFAULT_PLUGIN
		
		//create default plugin
#ifdef DEFAULT_BXCEPLUGIN
		plugin = new daebXCePlugin();
		defaultPlugin = true;
#else
#ifdef DOM_INCLUDE_LIBXML
		plugin = new daeLIBXMLPlugin;
		defaultPlugin = true;
#else
#ifdef DOM_INCLUDE_TINYXML
		plugin = new daeTinyXMLPlugin;
		defaultPlugin = true;
#else
		daeErrorHandler::get()->handleWarning( "No IOPlugin Set! Neither DOM_INCLUDE_LIBXML or DOM_INCLUDE_TINYXML  is defined." );
		plugin = NULL;
		return DAE_ERR_BACKEND_IO;
#endif // DOM_INCLUDE_TINYXML
#endif // DOM_INCLUDE_LIBXML
#endif // DEFAULT_BXCEPLUGIN

#else // NO_DEFAULT_PLUGIN
		daeErrorHandler::get()->handleWarning( "No IOPlugin Set! NO_DEFAULT_PLUGIN is defined." );
		plugin = NULL;
		return DAE_ERR_BACKEND_IO;
#endif // NO_DEFAULT_PLUGIN
	}
	int res = plugin->setMeta(topMeta);
	if (res != DAE_OK)
	{
		if (defaultPlugin)
		{
			defaultPlugin = false;
			delete plugin;
		}
		plugin = NULL;
		return res;
	}
	return DAE_OK;
}

// Integration Library Setup
daeIntegrationLibraryFunc DAE::getIntegrationLibrary()
{
	return registerFunc;
}

daeInt DAE::setIntegrationLibrary(daeIntegrationLibraryFunc _registerFunc)
{
	registerFunc = _registerFunc;
	return DAE_OK;
}

// batch file operations
daeInt DAE::load(daeString uri, daeString docBuffer)
{
	if (!database)
		setDatabase(NULL);

	if (!plugin)
		setIOPlugin(NULL);
	
	if (registerFunc) 
		registerFunc();

	if ( !plugin || !database ) {
		//printf( "no plugin or database\n" );
		daeErrorHandler::get()->handleError("no plugin or database\n");
		return DAE_ERR_BACKEND_IO;
	}

	plugin->setDatabase(database);

	if (!uri || uri[0] == '\0')
		return DAE_ERR_INVALID_CALL;

	daeURI tempURI(uri);
	
	return plugin->read(tempURI, docBuffer);
}
daeInt DAE::save(daeString uri, daeBool replace)
{
	if (!database)
		setDatabase(NULL);

	if (!plugin)
		setIOPlugin(NULL);

	if (registerFunc) 
		registerFunc();
	
	if ( !plugin || !database ) {
		return DAE_ERR_BACKEND_IO;
	}

	plugin->setDatabase(database);
	
	// Find the document we want by name
	daeDocument* document = database->getDocument(uri);
	if(document == NULL)
		return DAE_ERR_COLLECTION_DOES_NOT_EXIST;

	// Save it out to the URI it was loaded from
	return plugin->write(document->getDocumentURI(), document, replace);

}
daeInt DAE::save(daeUInt documentIndex, daeBool replace)
{
	if (!database)
		setDatabase(NULL);

	if (!plugin)
		setIOPlugin(NULL);

	if (registerFunc) 
		registerFunc();
	
	if ( !plugin || !database ) {
		return DAE_ERR_BACKEND_IO;
	}

	plugin->setDatabase(database);
	
	if(documentIndex >= database->getDocumentCount())
		return DAE_ERR_COLLECTION_DOES_NOT_EXIST;

	daeDocument *document = database->getDocument(documentIndex);
	
	// Save it out to the URI it was loaded from
	return plugin->write(document->getDocumentURI(), document, replace);
}
daeInt DAE::saveAs(daeString uriToSaveTo, daeString docUri, daeBool replace)
{
	if (!database)
		setDatabase(NULL);

	if (!plugin)
		setIOPlugin(NULL);

	if (registerFunc) 
		registerFunc();
	
	if ( !plugin || !database ) {
		return DAE_ERR_BACKEND_IO;
	}

	plugin->setDatabase(database);
	
	// Find the document we want by name
	daeDocument* document = database->getDocument(docUri);
	if(document == NULL)
		return DAE_ERR_COLLECTION_DOES_NOT_EXIST;

	// Make a URI from uriToSaveTo and save to that
	daeURI tempURI(uriToSaveTo, true);
	return plugin->write(&tempURI, document, replace);
	
}
daeInt DAE::saveAs(daeString uriToSaveTo, daeUInt documentIndex, daeBool replace)
{
	if (!database)
		setDatabase(NULL);

	if (!plugin)
		setIOPlugin(NULL);

	if (registerFunc) 
		registerFunc();
	
	if ( !plugin || !database ) {
		return DAE_ERR_BACKEND_IO;
	}

	plugin->setDatabase(database);
	
	if(documentIndex >= database->getDocumentCount())
		return DAE_ERR_COLLECTION_DOES_NOT_EXIST;

	daeDocument *document = database->getDocument(documentIndex);
	
	daeURI tempURI(uriToSaveTo, true);
	return plugin->write(&tempURI, document, replace);
}
daeInt DAE::unload(daeString uri)
{
	daeDocument *col = database->getDocument( uri );
	if ( col == NULL ) return DAE_ERR_COLLECTION_DOES_NOT_EXIST;
	return database->removeDocument( col );
}


namespace {
	// Take a URI ref and return a full URI. Uses the current working directory
	// as the base URI if a relative URI reference is given.
	string makeFullUri(const string& uriRef) {
		daeURI uri(uriRef.c_str());
		return uri.getURI();
	}

	// Take a file path (either relative or absolute) and return a full URI
	// representing the path. If a relative path is given, uses the current working
	// directory as a base URI to construct the full URI.
	string filePathToFullUri(const string& path) {
		return makeFullUri(cdom::filePathToUri(path));
	}
}

daeInt DAE::loadFile(daeString file, daeString memBuffer) {
	return load(filePathToFullUri(file).c_str(), memBuffer);
}

daeInt DAE::saveFile(daeString file, daeBool replace) {
	return save(filePathToFullUri(file).c_str(), replace);
}

daeInt DAE::saveFileAs(daeString fileToSaveTo, daeString file, daeBool replace) {
	return saveAs(filePathToFullUri(fileToSaveTo).c_str(), filePathToFullUri(file).c_str(), replace);
}

daeInt DAE::saveFileAs(daeString fileToSaveTo, daeUInt documentIndex, daeBool replace) {
	return saveAs(filePathToFullUri(fileToSaveTo).c_str(), documentIndex, replace);
}

daeInt DAE::unloadFile(daeString file) {
	return unload(filePathToFullUri(file).c_str());
}


daeInt DAE::clear()
{
	resolveArray.clear();
	if (database)
		database->clear();
	return DAE_OK;
}

// Load/Save Progress	
void DAE::getProgress(daeInt* bytesParsed,daeInt* lineNumber,daeInt* totalBytes,daeBool reset)
{
	if (!database || !plugin)
	{
		if (bytesParsed)
			*bytesParsed=0;
		if (lineNumber)
			*lineNumber=0;
		if (totalBytes)
			*totalBytes=0;
	}
	else
		plugin->getProgress(bytesParsed,lineNumber,totalBytes,reset);
}

// Simple Query
domCOLLADA* DAE::getDom(daeString uri)
{
	if (!database)
		return NULL;

	// Find the document by uri
	daeDocument *document = database->getDocument(uri);
	if(document)
	{
		// Return the root domCOLLADA element
		return (domCOLLADA*)(daeElement*)document->getDomRoot();
	}
	else
	{
		return(NULL);
	}
}

daeInt DAE::setDom(daeString uri, domCOLLADA* dom)
{
	if (!database)
		setDatabase(NULL);
	
	// Find the document by uri
	
	daeDocument *document = database->getDocument(uri);

	if(document)
	{
		//replace a DOM on an existing document by the one provided.
		// Note that the casts are needed because we don't want to include the full definition of domCOLLADA
		document->setDomRoot((daeElement*)dom);
		return DAE_OK;
	}
	else
	{
		// Document doesn't exist, make a new one
		return database->insertDocument(uri,(daeElement*)dom);
	}
}

domCOLLADA* DAE::getDomFile(daeString file) {
	return getDom(filePathToFullUri(file).c_str());
}

daeInt DAE::setDomFile(daeString file, domCOLLADA* dom) {
	return setDom(filePathToFullUri(file).c_str(), dom);
}

daeString DAE::getDomVersion()
{
	return(COLLADA_VERSION);
}

daeAtomicTypeList& DAE::getAtomicTypes() {
	return atomicTypes;
}

daeMetaElement* DAE::getMeta(int typeID) {
	int index = typeID - 2;
	if (index < 0 || index >= metas.getCount())
		return NULL;
	return metas[index];
}

void DAE::setMeta(int typeID, daeMetaElement& meta) {
	int index = typeID - 2;
	if (index < 0 || index >= metas.getCount())
		return;
	metas[index] = &meta;
}

void DAE::appendResolveElement(daeElement* elem) {
	resolveArray.append(elem);
}

void DAE::resolveAll() {
	// !!!steveT Make sure this works ok
	for (size_t i = 0; i < resolveArray.getCount(); i++)
		resolveArray[i]->resolve();
	resolveArray.clear();
}

daeURIResolverPtrArray& DAE::getUriResolvers() {
	return uriResolvers;
}

daeURI& DAE::getBaseURI() {
	return baseUri;
}

daeURI& DAE::setBaseURI(daeURI& uri) {
	baseUri.reset();
	baseUri.setURI(uri.getURI());
}
