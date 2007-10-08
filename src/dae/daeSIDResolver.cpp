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

#include <vector>
#include <sstream>
#include <dae/daeSIDResolver.h>
#include <dae/daeIDRef.h>
#include <dae/daeAtomicType.h>
#include <dae/daeMetaAttribute.h>
#include <dae/daeMetaElement.h>
#include <dae/daeURI.h>

using namespace std;

daeSIDResolver::daeSIDResolver( daeElement *container, daeString target, daeString profile )
	: container(NULL)
{
	setContainer(container);
	setTarget(target);
	setProfile(profile);
}

daeString daeSIDResolver::getTarget() const {
	return target.empty() ? NULL : target.c_str();
}

void daeSIDResolver::setTarget( daeString t )
{
	target = t ? t : "";
	resetResolveState();
}

daeString daeSIDResolver::getProfile() const {
	return profile.empty() ? NULL : profile.c_str();
}

void daeSIDResolver::setProfile( daeString p )
{
	profile = p ? p : "";
	resetResolveState();
}

daeElement* daeSIDResolver::getContainer() const {
	return container;
}

void daeSIDResolver::setContainer(daeElement* element)
{
	if ( element != container ) {
		container = element;
		resetResolveState();
	}
}

daeSIDResolver::ResolveState daeSIDResolver::getState() const {
	return state;
}

daeElementRef daeSIDResolver::getElement()
{
	if ( state == target_loaded ) {
		resolve();
	}
	return resolvedElement;
}

daeDoubleArray *daeSIDResolver::getDoubleArray()
{
	if ( state == target_loaded ) {
		resolve();
	}
	return resolvedDoubleArray;
}

daeDouble *daeSIDResolver::getDouble()
{
	if ( state == target_loaded ) {
		resolve();
	}
	return resolvedDoublePtr;
}

void daeSIDResolver::resetResolveState() {
	state = target.empty() ? target_empty : target_loaded;
	resolvedElement = NULL;
	resolvedDoubleArray = NULL;
	resolvedDoublePtr = NULL;
}

namespace {
	void tokenizeSIDRef(const string& sidRef, /* out */ vector<string>& tokens) {
		string separators = "/.()";
		size_t currentIndex = 0, nextTokenIndex = 0;
		while (currentIndex < sidRef.length() &&
					 (nextTokenIndex = sidRef.find_first_of(separators, currentIndex)) != string::npos) {
			if ((nextTokenIndex - currentIndex) > 0)
				tokens.push_back(sidRef.substr(currentIndex, nextTokenIndex-currentIndex));
			tokens.push_back(string(1, sidRef[nextTokenIndex]));
			currentIndex = nextTokenIndex+1;
		}

		if (currentIndex < sidRef.length())
			tokens.push_back(sidRef.substr(currentIndex, sidRef.length()-currentIndex));
	}
}

void daeSIDResolver::resolve()
{
	resetResolveState();
	if (target.empty())
		return;

	daeElement*     element = 0;
	daeDoubleArray* doubleArray = 0;
	daeDouble*      doublePtr = 0;
	state = sid_failed_not_found; // Assume that we're going to fail

	vector<string> tokens;
	tokenizeSIDRef(target, /* out */ tokens);

	vector<string>::iterator tok = tokens.begin();

	// The first token should be the ID of the element we want to start our search from, or a '.' to indicate
	// that we should start the search from the container element.
	if (tok == tokens.end())
		return;

	if (*tok == ".") {
		element = container;
	}	else {
		daeIDRef idref( (*tok).c_str() );
		idref.setContainer( container );
		idref.resolveElement();
		if ( idref.getState() != daeIDRef::id_success )
			return;
		element = idref.getElement();
	}

	// Next we have a list of SIDs, each one separated by "/". Once we hit one of ".()", we know we're
	// done with the SID section.
	tok++;
	if (tok != tokens.end()  &&  *tok != "/")
		return;
	
	for (; tok != tokens.end() && *tok == "/"; tok++) {
		tok++; // Read the '/'
		if (tok == tokens.end())
			return;

		// Find the element matching the SID
		string sid = *tok;
		daeElement* lastElementFound = element;
		element = findSID(element, sid.c_str());
		if (element == NULL) {
			// !!!steveT: This behavior will probably need to change once bug 1293 in Khronos gets resolved.
			// We weren't able to find an element with a matching SID. Before we bail, try consuming some more
			// of the target to use as additional SID.
			tok++;
			for (; tok != tokens.end()  &&  element == NULL; tok++) {
				sid += *tok;
				element = findSID(lastElementFound, sid.c_str());
			}
			tok--; // Step back. tok is about to be incremented by the outer for loop.
		}
		
		if (element == NULL)
			return;
	}

	// Now we want to parse the member selection tokens. It can either be
	//   (a) '.' followed by a string representing the member to access
	//   (b) '(x)' where x is a number, optionally followed by another '(x)'
	// Anything else is an error.
	string member;
	size_t arrayIndex1 = UINT_MAX, arrayIndex2 = UINT_MAX;
	if (tok != tokens.end()) {
		if (*tok == ".") {
			tok++;
			if (tok == tokens.end())
				return;
			member = *tok;
			tok++;
		}
		else if (*tok == "(") {
			tok++;
			if (tok == tokens.end())
				return;

			istringstream stream(*tok);
			stream >> arrayIndex1;
			if (!stream.good() && !stream.eof())
				return;
			tok++;
			if (tok == tokens.end()  ||  *tok != ")")
				return;
			tok++;
			
			if (tok != tokens.end()  &&  *tok == "(") {
				tok++;
				if (tok == tokens.end())
					return;

				stream.clear();
				stream.str(*tok);
				stream >> arrayIndex2;
				if (!stream.good() && !stream.eof())
					return;
				tok++;
				if (tok == tokens.end()  ||  *tok != ")")
					return;
				tok++;
			}
		}
	}

	// We shouldn't have any tokens left. If we do it's an error.
	if (tok != tokens.end())
		return;

	// At this point we've parsed a correctly formatted SID reference. The only thing left is to resolve
	// the member selection portion of the SID ref. First, see if the resolved element has a float array we
	// can use.
	if ( strcmp( element->getTypeName(), "source" ) == 0 ) {
		daeElementRefArray children;
		element->getChildren( children );
		size_t cnt = children.getCount();

		for ( size_t x = 0; x < cnt; x++ ) {
			if ( strcmp( children[x]->getTypeName(), "float_array" ) == 0 ) {
				doubleArray = (daeDoubleArray*)children[x]->getMeta()->getValueAttribute()->getWritableMemory( children[x] );
				break;
			}
		}
	}
	else 
	{
		daeMetaAttribute *ma = element->getMeta()->getValueAttribute();
		if ( ma != NULL ) {
			if ( ma->isArrayAttribute() && ma->getType()->getTypeEnum() == daeAtomicType::DoubleType ) {
				doubleArray = (daeDoubleArray*)ma->getWritableMemory( element );
			}
		}
	}

	if( doubleArray ) {
		// We have an array to use for indexing. Let's see if the SID ref uses member selection.
		if (!member.empty()) {
			// Do member lookup based on the constants defined in the COMMON profile
			if (member == "ANGLE") {
				doublePtr = &(doubleArray->get(3));
			}	else if (member.length() == 1) {
				switch(member[0]) {
					case 'X':
					case 'R':
					case 'U':
					case 'S':
						doublePtr = &(doubleArray->get(0));
						break;
					case 'Y':
					case 'G':
					case 'V':
					case 'T':
						doublePtr = &(doubleArray->get(1));
						break;
					case 'Z':
					case 'B':
					case 'P':
						doublePtr = &(doubleArray->get(2));
						break;
					case 'W':
					case 'A':
					case 'Q':
						doublePtr = &(doubleArray->get(3));
						break;
				};
			}
		} else if (arrayIndex1 != UINT_MAX) {
			// Use the indices to lookup a value in the array
			if (arrayIndex2 != UINT_MAX  &&  doubleArray->getCount() == 16) {
				// We're doing a matrix lookup. Make sure the index is valid.
				size_t i = arrayIndex1*4 + arrayIndex2;
				if (i < doubleArray->getCount())
					doublePtr = &(doubleArray->get(i));
			} else {
				// Vector lookup. Make sure the index is valid.
				if (arrayIndex1 < doubleArray->getCount())
					doublePtr = &(doubleArray->get(arrayIndex1));
			}
		}
	}

	// If we tried to do member selection but we couldn't resolve it to a doublePtr, fail.
	if ((!member.empty() || arrayIndex1 != UINT_MAX)  &&  doublePtr == NULL)
		return;

	// SID resolution was successful. Apply the results.
	resolvedElement = element;
	resolvedDoubleArray = doubleArray;
	resolvedDoublePtr = doublePtr;
	if (resolvedDoublePtr)
		state = sid_success_double;
	else if (resolvedDoubleArray)
		state = sid_success_array;
	else if (resolvedElement)
		state = sid_success_element;
}

daeElement *daeSIDResolver::findSID( daeElement *el, daeString sid ) {
	//first check yourself
	daeString *s = (daeString*)el->getAttributeValue( "sid" );
	if ( s != NULL && *s != NULL && strcmp( *s, sid ) == 0 ) {
		//found it
		return el;
	}
	//and if you are a instance_* then check what you point to
	if ( strncmp( el->getElementName(), "instance_", 9 ) == 0 ) {
		daeURI *uri = (daeURI*)el->getAttributeValue("url");
		if ( uri != NULL && uri->getElement() != NULL ) {
			daeElement *e = findSID( uri->getElement(), sid );
			if ( e != NULL ) {
				//found it
				return e;
			}
		}
	}
	
	daeElementRefArray children;
	el->getChildren( children );
	size_t cnt = children.getCount();
	for ( size_t x = 0; x < cnt; x++ ) {
		//examine the children
		//char s[56]; 
		//daeAtomicType::get( "token" )->memoryToString( children[x]->getAttributeValue( "sid" ), s, 56 );
		daeString *s = (daeString*)children[x]->getAttributeValue( "sid" );
		if ( s != NULL && *s != NULL && strcmp( *s, sid ) == 0 ) {
			//found it
			return children[x];
		}
	}
	for ( size_t x = 0; x < cnt; x++ ) {
		//if not found look for it in each child
		if ( !profile.empty() && strcmp( children[x]->getTypeName(), "technique_COMMON" ) == 0 ) {
			//not looking for common profile
			continue;
		}
		else if ( strcmp( children[x]->getTypeName(), "technique" ) == 0 && children[x]->hasAttribute( "profile" ) ) {
			if ( profile.empty() || profile != children[x]->getAttributeValue( "profile" ) ) {
				//not looking for this technique profile
				continue;
			}		
		}
		daeElement *e = findSID( children[x], sid );
		if ( e != NULL ) {
			//found it
			return e;
		}
	}
	return NULL;
}
