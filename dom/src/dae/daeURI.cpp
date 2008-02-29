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
#include <dae/daeURI.h>
#include <ctype.h>
#include <dae/daeDocument.h>
#include <dae/daeErrorHandler.h>
#include <dae/daeUtils.h>
#include <pcrecpp.h>

using namespace std;

namespace {
	// Returns true if parsing succeeded, false otherwise. Parsing can fail if the uri
	// reference isn't properly formed.
	bool parseUriRef(const string& uriRef,
	                 string& scheme,
	                 string& authority,
	                 string& path,
	                 string& query,
	                 string& fragment) {
		// This regular expression for parsing URI references comes from the URI spec:
		//   http://tools.ietf.org/html/rfc3986#appendix-B
		static pcrecpp::RE re("^(([^:/?#]+):)?(//([^/?#]*))?([^?#]*)(\\?([^#]*))?(#(.*))?");
		string s1, s3, s6, s8;
		if (re.FullMatch(uriRef, &s1, &scheme, &s3, &authority, &path, &s6, &query, &s8, &fragment))
			return true;

		return false;
	}
}


void daeURI::initialize() {
	reset();
	container = NULL;
}

daeURI::~daeURI() { }

daeURI::daeURI(DAE& dae) : dae(&dae) {
	initialize();
}

daeURI::daeURI(DAE& dae, daeString uriString, daeBool nofrag) : dae(&dae) {
	initialize();

	string uriStr = uriString ? uriString : "";
	if (nofrag) {
		size_t pos = uriStr.find_last_of('#');
		if (pos != string::npos)
			uriStr = uriStr.substr(0, pos);
	}

	setURI(uriString);
	validate();
}

daeURI::daeURI(daeURI& baseURI, daeString uriString) : dae(baseURI.getDAE())
{
	initialize();
	setURI(uriString);
	validate(&baseURI);
}

daeURI::daeURI(const daeURI& copyFrom) : dae(copyFrom.getDAE())
{
	initialize();
	setURI(copyFrom.getOriginalURI());
	element = copyFrom.element;   // !!!GAC SetURI immediately clears element so we must do this after
	state = copyFrom.state;
}

daeURI::daeURI(daeElement& container_, daeString uriString)
	: dae(container_.getDAE())
{
	initialize();
	container = &container_;
	setURI(uriString);
	validate();
}

daeURI::daeURI(DAE& dae, daeElement& container_, daeString uriString)
	: dae(&dae)
{
	initialize();
	container = &container_;
	setURI(uriString);
	validate();
}

void
daeURI::copyFrom(daeURI& copyFrom)
{
	setURI(copyFrom.getOriginalURI());
	element = copyFrom.element;		// !!!GAC SetURI immediately clears element so we must do this after
	state = copyFrom.state;
	// !!!GAC Should there be a call to validate in here?
}

daeURI& daeURI::operator=(daeString uri) {
	setURI(uri);
	return *this;
}

void daeURI::reset() {
	// Clear everything except the container, which doesn't change for the lifetime of the daeURI
	uriString	        = "";
	originalURIString	= "";
	protocol          = "";
	authority	        = "";
	filepath          = "";
	file              = "";
	id                = "";
	extension         = "";
	state	            = uri_empty;
	element	          = NULL;
	external          = false;
}

DAE* daeURI::getDAE() const {
	return dae;
}

void daeURI::setURI(daeString _URIString) {
	string uriStr = _URIString ? _URIString : "";
	if (originalURIString == uriStr)
		return;
	internalSetURI(uriStr);
}

namespace {
	void parsePath(const string& path,
	               /* out */ string& dir,
	               /* out */ string& file,
	               /* out */ string& extension) {
		static pcrecpp::RE re("(.*/)?([^.]*(\\.(.*))?)?");
		string s;
		re.FullMatch(path, &dir, &file, &s, &extension);
	}
}

void daeURI::internalSetURI(const string& uriStr) {
	reset();
	originalURIString = uriStr;

	string scheme, auth, path, query, fragment;
	if (!parseUriRef(uriStr, scheme, auth, path, query, fragment)) {
		reset();
		return;
	}

	protocol = scheme;
	authority = auth;
	parsePath(path, filepath, file, extension);
	id = fragment;
	state = uri_loaded;
}

void
daeURI::print()
{
	fprintf(stderr,"URI(%s)\n",uriString.c_str());
	fprintf(stderr,"protocol = %s\n",protocol.c_str());
	fprintf(stderr,"authority = %s\n",authority.c_str());
	fprintf(stderr,"path = %s\n",filepath.c_str());
	fprintf(stderr,"file = %s\n",file.c_str());
	fprintf(stderr,"id = %s\n",id.c_str());
	fprintf(stderr,"URI without base = %s\n",originalURIString.c_str());
	fflush(stderr);
}

daeString
daeURI::getURI() const
{
	return uriString.c_str();
}

daeString
daeURI::getOriginalURI() const
{
	return originalURIString.c_str();
}

namespace {
	void normalize(string& path) {
		daeURI::normalizeURIPath(const_cast<char*>(path.c_str()));
		path = path.substr(0, strlen(path.c_str()));
	}
}

void
daeURI::validate(daeURI* baseURI)
{
	// If no base URI was supplied, get the application base and use it
	if (!baseURI) {
		if (!container || !(baseURI = container->getDocumentURI()))
			baseURI = &dae->getBaseURI();
		if (this == baseURI)
			return;
	}

	// This is rewritten according to the updated rfc 3986
	if (!protocol.empty()) // if defined(R.scheme) then
	{
		// Everything stays the same except path which we normalize
		// T.scheme    = R.scheme;
		// T.authority = R.authority;
		// T.path      = remove_dot_segments(R.path);
		// T.query     = R.query;
		normalize(filepath);
	}
	else
	{
		if (!authority.empty()) // if defined(R.authority) then
		{
			// Authority and query stay the same, path is normalized
			// T.authority = R.authority;
			// T.path      = remove_dot_segments(R.path);
			// T.query     = R.query;
			normalize(filepath);
		}
		else
		{
			if (filepath.empty() && file.empty())  // if (R.path == "") then
			{
				// T.path = Base.path;
				filepath = baseURI->filepath;
				file = baseURI->file;
				extension = baseURI->extension;
				// We don't handle querys, but if we did
				//if defined(R.query) then
				//   T.query = R.query;
				//else
				//   T.query = Base.query;
				//endif;
			}
			else
			{
				if (!filepath.empty() && filepath[0] == '/')  //if (R.path starts-with "/") then
				{
					// T.path = remove_dot_segments(R.path);
					normalize(filepath);
				}
				else
				{
					//T.path = merge(Base.path, R.path);
					if (!baseURI->authority.empty() && baseURI->filepath.empty() && baseURI->file.empty()) //authority defined, path empty
						filepath.insert(0, "/");
					else
						filepath = baseURI->filepath + filepath;
					//T.path = remove_dot_segments(T.path);
					normalize(filepath);
				}
				// T.query = R.query;
			}
			// T.authority = Base.authority;
			authority = baseURI->authority;
		}
		// T.scheme = Base.scheme;
		protocol = baseURI->protocol;
	}
	// T.fragment = R.fragment;

	// Reassemble all this into a string version of the URI
	uriString = "";
	if (!protocol.empty())
		uriString += protocol + ':';
	uriString += "//" + authority + filepath + file;
	if (!id.empty())
		uriString += "#" + id;

	state = uri_pending;

	if (container && container->getDocumentURI()) {
		daeURI* docURI = container->getDocumentURI();
		if (filepath != docURI->filepath  ||  file != docURI->file) {
			// external ref
			container->getDocument()->addExternalReference(*this);
			external = true;
		}
		else if (external) {
			// Was external but now isn't
			container->getDocument()->removeExternalReference(*this);
			external = false;
		}
	}
}

daeElement* daeURI::getElement() {
	if (!element)
		internalResolveElement();
	return element;
}

void daeURI::internalResolveElement() {
	if (state == uri_empty)
		return;
	
	if (state == uri_loaded) {
		if (container != NULL)
			validate(container->getDocumentURI());
		else
			validate();
	}

	dae->getURIResolvers().resolveElement(*this);
}

void daeURI::resolveElement() { }

void
daeURI::resolveURI()
{
	// !!!GAC bug 486, there used to be code here that just returned if state was uri_empty or uri_resolve_local this has been removed.
	if (element)
	{
		// !!!GAC bug 388 and 421, need to add a fragment (#) before the ID (was setURI(element->getID()))
		string elementID = element->getAttribute("id");
		if (elementID.empty())
		{
			// We can't resolve to an element that has no ID, so if the ID is blank, fail and return
			state = uri_failed_invalid_reference;
			return;
		}
		// !!!GAC We have to save element and container because setURI clears them for some reason
		daeElementRef	elementSave = element;
		setURI((string("#") + elementID).c_str());
		// !!!GAC Hopefully, calling validate like below is the right thing to do to get the full URI resolution
		element	= elementSave;
		validate(element->getDocumentURI());
		element	= elementSave;
		state = uri_success;  // !!!GAC The element pointer and the URI should agree now, so set success
	}
	else
	{
		state = uri_failed_invalid_reference;
	}
}

daeBool daeURI::getPath(daeChar *dest, daeInt size) const
{
	string path = getPath();
	if (int(path.length()) < size) {
		strcat(dest, path.c_str());
		return true;
	}
	return false;
}

string daeURI::getPath() const {
	return filepath + file;
}

// This code is loosely based on the RFC 2396 normalization code from
// libXML. Specifically it does the RFC steps 6.c->6.g from section 5.2
// The path is modified in place, there is no error return.
void daeURI::normalizeURIPath(char* path)
{
	char *cur, // location we are currently processing
	     *out; // Everything from this back we are done with

	// Return if the path pointer is null

	if (path == NULL) return;

	// Skip any initial / characters to get us to the start of the first segment

	for(cur=path; *cur == '/'; cur++);

	// Return if we hit the end of the string

	if (*cur == 0) return;

	// Keep everything we've seen so far.
    
	out = cur;

	// Analyze each segment in sequence for cases (c) and (d).

	while (*cur != 0) 
	{
		// (c) All occurrences of "./", where "." is a complete path segment, are removed from the buffer string.
		
		if ((*cur == '.') && (*(cur+1) == '/')) 
		{
			cur += 2;
			// If there were multiple slashes, skip them too
			while (*cur == '/') cur++;
			continue;
		}

		// (d) If the buffer string ends with "." as a complete path segment, that "." is removed.

		if ((*cur == '.') && (*(cur+1) == 0))
			break;

		// If we passed the above tests copy the segment to the output side

		while (*cur != '/' && *cur != 0)
		{
			*(out++) = *(cur++);
		}

		if(*cur != 0)
		{
			// Skip any occurrances of // at the end of the segment

			while ((*cur == '/') && (*(cur+1) == '/')) cur++;

			// Bring the last character in the segment (/ or a null terminator) into the output
        
			*(out++) = *(cur++);
		}
	}

	*out = 0;

    // Restart at the beginning of the first segment for the next part

	for(cur=path; *cur == '/'; cur++);
	if (*cur == 0) return;

	// Analyze each segment in sequence for cases (e) and (f).
	//
	// e) All occurrences of "<segment>/../", where <segment> is a
	//    complete path segment not equal to "..", are removed from the
	//    buffer string.  Removal of these path segments is performed
	//    iteratively, removing the leftmost matching pattern on each
	//    iteration, until no matching pattern remains.
	//
	// f) If the buffer string ends with "<segment>/..", where <segment>
	//    is a complete path segment not equal to "..", that
	//    "<segment>/.." is removed.
	//
	// To satisfy the "iterative" clause in (e), we need to collapse the
	// string every time we find something that needs to be removed.  Thus,
	// we don't need to keep two pointers into the string: we only need a
	// "current position" pointer.
	//
	while (true)
	{
		char *segp, *tmp;

		// At the beginning of each iteration of this loop, "cur" points to
		// the first character of the segment we want to examine.

		// Find the end of the current segment.  
        
		for(segp = cur;(*segp != '/') && (*segp != 0); ++segp);

		// If this is the last segment, we're done (we need at least two
		// segments to meet the criteria for the (e) and (f) cases).

		if (*segp == 0)
			break;

		// If the first segment is "..", or if the next segment _isn't_ "..",
		// keep this segment and try the next one.

		++segp;
		if (((*cur == '.') && (cur[1] == '.') && (segp == cur+3))
            || ((*segp != '.') || (segp[1] != '.')
            || ((segp[2] != '/') && (segp[2] != 0)))) 
		{
			cur = segp;
			continue;
		}

		// If we get here, remove this segment and the next one and back up
		// to the previous segment (if there is one), to implement the
		// "iteratively" clause.  It's pretty much impossible to back up
		// while maintaining two pointers into the buffer, so just compact
		// the whole buffer now.

		// If this is the end of the buffer, we're done.

		if (segp[2] == 0) 
		{
			*cur = 0;
			break;
		}

		// Strings overlap during this copy, but not in a bad way, just avoid using strcpy
		
		tmp = cur;
		segp += 3;
		while ((*(tmp++) = *(segp++)) != 0);

		// If there are no previous segments, then keep going from here.
        
		segp = cur;
		while ((segp > path) && (*(--segp) == '/'));
        
		if (segp == path)
			continue;

		// "segp" is pointing to the end of a previous segment; find it's
		// start.  We need to back up to the previous segment and start
		// over with that to handle things like "foo/bar/../..".  If we
		// don't do this, then on the first pass we'll remove the "bar/..",
		// but be pointing at the second ".." so we won't realize we can also
		// remove the "foo/..".

		for(cur = segp;(cur > path) && (*(cur-1) != '/'); cur--);
	}

	*out = 0;

	// g) If the resulting buffer string still begins with one or more
	//    complete path segments of "..", then the reference is
	//    considered to be in error. Implementations may handle this
	//    error by retaining these components in the resolved path (i.e.,
	//    treating them as part of the final URI), by removing them from
	//    the resolved path (i.e., discarding relative levels above the
	//    root), or by avoiding traversal of the reference.
	//
	// We discard them from the final path.

	if (*path == '/') 
	{
		for(cur=path; (*cur == '/') && (cur[1] == '.') && (cur[2] == '.') && ((cur[3] == '/') || (cur[3] == 0)); cur += 3);

		if (cur != path) 
		{
			for(out=path; *cur != 0; *(out++) = *(cur++));

			*out = 0;
		}
	}
	return;
}

// This function will take a resolved URI and create a version of it that is relative to
// another existing URI.  The new URI is stored in the "originalURI"
int daeURI::makeRelativeTo(const daeURI* relativeToURI)
{
	if( getState() == uri_empty || relativeToURI->getState() == uri_empty ) 
		return(DAE_ERR_INVALID_CALL);
	if( getState() == uri_loaded )
	{
		if (container != NULL)
			validate(container->getDocumentURI());
		else
			validate();
	}
	if( relativeToURI->getState() == uri_loaded )
	{
		if (relativeToURI->getContainer() != NULL)
			const_cast<daeURI*>(relativeToURI)->validate(relativeToURI->getContainer()->getDocumentURI());
		else
			const_cast<daeURI*>(relativeToURI)->validate();
	}

	// Can only do this function if both URIs have the same scheme and authority
	if (protocol != relativeToURI->protocol  ||  authority != relativeToURI->authority)
		return DAE_ERR_INVALID_CALL;

	// advance till we find a segment that doesn't match
	const char *this_filepath		= getFilepath();
	const char *relativeTo_filepath = relativeToURI->getFilepath();
	const char *this_slash			= this_filepath;
	const char *relativeTo_slash	= relativeTo_filepath;

	while((*this_filepath == *relativeTo_filepath) && *this_filepath)
	{
		if(*this_filepath == '/')
		{
			this_slash = this_filepath;
			relativeTo_slash = relativeTo_filepath;
		}
		this_filepath++;
		relativeTo_filepath++;
	}

	// Decide how many ../ segments are needed (Filepath should always end in a /)
	int segment_count = 0;
	relativeTo_slash++;
	while(*relativeTo_slash != 0)
	{
		if(*relativeTo_slash == '/')
			segment_count ++;
		relativeTo_slash++;
	}
	this_slash++;

	string newUri;
	for (int i = 0; i < segment_count; i++)
		newUri += "../";
	newUri += this_slash + file;
	if (!id.empty())
		newUri += "#" + id;
	
	setURI(newUri.c_str());
	return(DAE_OK);
}


daeBool daeURIResolver::_loadExternalDocuments = true;

daeURIResolver::daeURIResolver(DAE& dae) : dae(&dae), supportsAnyExtension(false) { }

daeURIResolver::~daeURIResolver() { }

void daeURIResolver::setAutoLoadExternalDocuments( daeBool load ) 
{ 
	_loadExternalDocuments = load; 
}

daeBool daeURIResolver::getAutoLoadExternalDocuments() 
{ 
	return _loadExternalDocuments; 
}


daeURIResolverList::daeURIResolverList() { }

daeURIResolverList::~daeURIResolverList() {
	for (size_t i = 0; i < resolvers.getCount(); i++)
		delete resolvers[i];
}

void daeURIResolverList::addResolver(daeURIResolver* resolver) {
	resolvers.append(resolver);
}

void daeURIResolverList::removeResolver(daeURIResolver* resolver) {
	resolvers.remove(resolver);
}

void daeURIResolverList::resolveElement(daeURI& uri) {
	for (size_t i = 0; i < resolvers.getCount(); i++) {
		if (resolvers[i]->isProtocolSupported(uri.getProtocol())) {
			if (uri.getFile() == NULL ||
			    uri.getFile()[0] == '\0' ||
			    resolvers[i]->isExtensionSupported(uri.getExtension())) {
				resolvers[i]->resolveElement(uri);
			}
		}
	}
}


string cdom::filePathToUri(const string& filePath) {
	string uri = filePath;

	// Windows - convert "c:\" to "/c:\"
	if (uri.length() >= 2  &&  isalpha(uri[0])  &&  uri[1] == ':')
		uri.insert(0, "/");
	else if (!uri.empty()  &&  uri[0] == '\\') {
		// Windows - If it's an absolute path with no drive letter, or a UNC path,
		// prepend "file:///"
		uri.insert(0, "file:///");
	}
	
	// Windows - convert backslashes to forward slashes
	uri = replace(uri, "\\", "/");

	// Convert spaces to %20
	uri = replace(uri, " ", "%20");

	return uri;
}


string cdom::uriToFilePath(const string& uriRef) {
	string scheme, authority, path, query, fragment;
	parseUriRef(uriRef, scheme, authority, path, query, fragment);

	// Make sure we have a file scheme URI, or that it doesn't have a scheme
	if (!scheme.empty()  &&  scheme != "file")
		return "";

	string filePath = path;

#ifdef WIN32
	// Windows - replace two leading slashes with one leading slash, so that
	// ///otherComputer/file.dae becomes //otherComputer/file.dae
	if (filePath.length() >= 2  &&  filePath[0] == '/'  &&  filePath[1] == '/')
		filePath.erase(0, 1);

	// Windows - convert "/C:/" to "C:/"
	if (filePath.length() >= 3  &&  filePath[0] == '/'  &&  filePath[2] == ':')
		filePath.erase(0, 1);

	// Windows - convert forward slashes to back slashes
	filePath = replace(filePath, "/", "\\");
#endif

	// Replace %20 with space
	filePath = replace(filePath, "%20", " ");
	
	return filePath;
}
