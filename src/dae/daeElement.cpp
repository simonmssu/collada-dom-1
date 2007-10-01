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

#include <dae/daeElement.h>
#include <dae/daeArray.h>
#include <dae/daeMetaAttribute.h>
#include <dae/daeMetaElementAttribute.h>
#include <dae/daeMetaElement.h>
#include <dae/daeDatabase.h>
#include <dae/daeErrorHandler.h>

#include <dae/daeIntegrationObject.h>
#include <dae/daeURI.h>
#include <dae/domAny.h>

daeElementRef DAECreateElement(int)
{
	return new daeElement;
}

//Contributed by Nus - Wed, 08 Nov 2006
// static daeElementRefArray resolveArray;
static daeElementRefArray* pResolveArray = NULL;
//static char StaticIndentBuf[] = "";

extern "C" void initializeResolveArray(void)
{
  if(!pResolveArray) {
    pResolveArray = new daeElementRefArray;
  }
}

extern "C" void terminateResolveArray(void)
{
  if(pResolveArray) {
    delete pResolveArray;
    pResolveArray = NULL;
  }
}
//----------------------------------

// sthomas (see https://collada.org/public_forum/viewtopic.php?t=325&)
void daeElement::releaseElements()
{
    // resolveArray.clear();
    pResolveArray->clear();
}

daeIntegrationObject*
daeElement::getIntObject( IntegrationState from_state, IntegrationState to_state )
{
	if ( !_intObject ) {
		return NULL;
	}
	if ( from_state >= int_created ) {
		if ( _intObject->_from_state < int_created ) {
			daeErrorHandler::get()->handleWarning("Warning: getIntObject tries to get object that is not created (from)");
			return NULL;
		}
		if ( from_state >= int_converted ) {
			_intObject->fromCOLLADAChecked();
			if ( from_state == int_finished ) {
				_intObject->fromCOLLADAPostProcessChecked();
			}
		}
	}
	if ( to_state >= int_created ) {
		if ( _intObject->_to_state < int_created ) {
			daeErrorHandler::get()->handleWarning("Warning: getIntObject tries to get object that is not created (to)");
			return NULL;
		}
		if ( to_state >= int_converted ) {
			_intObject->toCOLLADAChecked();
			if ( to_state == int_finished ) {
				_intObject->toCOLLADAPostProcessChecked();
			}
		}
	}
	return _intObject;
}

daeElementRef
daeElement::createElement(daeString className)
{
	daeElementRef elem = _meta->create(className);
	// Bug #225 work around
//	if ( elem != NULL)
//		elem->ref(); // change premature delete into memory leak.
	return elem;
}

daeElement*
daeElement::createAndPlace(daeString className)
{
	daeElementRef elem = _meta->create(className);
	daeBool place = false;
	if (elem != NULL)
		place = placeElement(elem);
	if (place)
		return elem;
	return NULL;
}

daeElement*
daeElement::createAndPlaceAt(daeInt index, daeString className)
{
	daeElementRef elem = _meta->create(className);
	daeBool place = false;
	if (elem != NULL)
		place = placeElementAt(index, elem);
	if (place)
		return elem;
	return NULL;
}

daeBool
daeElement::placeElement(daeElement* e)
{
	if (e == NULL || e == this)
		return false;
	return _meta->place( this, e );
}

daeBool daeElement::placeElementAt(daeInt index, daeElement* e) {
	if (e == NULL || e == this)
		return false;
	return _meta->placeAt( index, this, e );
}

daeBool daeElement::placeElementBefore( daeElement *marker, daeElement *element ) {
	if (marker == NULL || element == NULL || marker->getXMLParentElement() != this ) {
		return false;
	}
	//if ( _meta->getContents() != NULL ) {
	//	size_t idx;
	//	daeElementRefArray* contents =
	//					(daeElementRefArray*)_meta->getContents()->getWritableMemory(this);
	//	if ( contents->find( marker, idx ) != DAE_OK ) {
	//		return false;
	//	}
	//	return placeElementAt( (daeInt)idx, element );
	//}
	//if ( strcmp( marker->getTypeName(), element->getTypeName() ) == 0 ) {
	//	//same type
	//	daeMetaElementAttribute *mea = _meta->getChildMetaElementAttribute( element->getTypeName() );
	//	daeElementRefArray* era = (daeElementRefArray*)mea->getWritableMemory(this);
	//	size_t idx;
	//	if ( era->find( marker, idx ) != DAE_OK ) {
	//		return false;
	//	}
	//	era->insertAt( idx, element );
	//	return true;
	//}
	//return placeElement( element );
	return _meta->placeBefore( marker, this, element );
}

daeBool daeElement::placeElementAfter( daeElement *marker, daeElement *element ) {
	if (marker == NULL || element == NULL || marker->getXMLParentElement() != this ) {
		return false;
	}
	/*if ( _meta->getContents() != NULL ) {
		size_t idx;
		daeElementRefArray* contents =
						(daeElementRefArray*)_meta->getContents()->getWritableMemory(this);
		if ( contents->find( marker, idx ) != DAE_OK ) {
			return false;
		}
		return placeElementAt( (daeInt)idx+1, element );
	}
	if ( strcmp( marker->getTypeName(), element->getTypeName() ) == 0 ) {
		daeMetaElementAttribute *mea = _meta->getChildMetaElementAttribute( element->getTypeName() );
		daeElementRefArray* era = (daeElementRefArray*)mea->getWritableMemory(this);
		size_t idx;
		if ( era->find( marker, idx ) != DAE_OK ) {
			return false;
		}
		era->insertAt( idx+1, element );
		return true;
	}*/
	return _meta->placeAfter( marker, this, element );
}

daeInt daeElement::findLastIndexOf( daeString elementName ) {
	if ( _meta->getContents() != NULL ) {
		daeElementRefArray* contents =
						(daeElementRefArray*)_meta->getContents()->getWritableMemory(this);
		for ( int i = (int)contents->getCount()-1; i >= 0; --i ) {
			if ( strcmp( contents->get(i)->getElementName(), elementName ) == 0 ) {
				return i;
			}
		}
	}
	return -1;
}

daeBool 
daeElement::removeChildElement(daeElement* element)
{
	// error traps
	if(element==NULL)
		return false;
	if(element->_parent != this)
		return false;

	return _meta->remove( this, element );
}

// !!!ACL Added to fix mantis issue 0000416
void daeElement::setDocument( daeDocument *c, bool notifyDocument ) {
	if( _document == c ) {
		return;
	}
	if ( _document != NULL && notifyDocument )
	{
		_document->removeElement(this);
	}
	_document = c;
	if ( _document != NULL && notifyDocument )
	{
		_document->insertElement(this);
	}

	daeElementRefArray ea;
	getChildren( ea );
	for ( size_t x = 0; x < ea.getCount(); x++ ) {
		// Since inserting and removing elements works recursively in the database,
		// we don't need to notify it about inserts/removals as we process the
		// children of this element.
		ea[x]->setDocument( c, false );
	}
}

void daeElement::deleteCMDataArray(daeTArray<daeCharArray*>& cmData) {
	for (unsigned int i = 0; i < cmData.getCount(); i++)
		delete cmData.get(i);
	cmData.clear();
}

namespace {
	// A helper function that implements daeElement::getAttributeObject's interface but also
	// optionally returns the index of the attribute.
	daeMetaAttribute* getAttributeObjectWithIndex(daeElement& el,
																								daeString name,
																								/* out */ size_t* index = 0) {
		if (el.getMeta()) {
			daeMetaAttributeRefArray& metaAttrs = el.getMeta()->getMetaAttributes();
			for (size_t i = 0; i < metaAttrs.getCount(); i++)
				if (metaAttrs[i]->getName()  &&  strcmp(metaAttrs[i]->getName(), name) == 0) {
					if (index)
						*index = i;
					return metaAttrs[i];
				}
		}
		if (index)
			*index = (size_t)-1;
		return NULL;
	}
}

daeMetaAttribute* daeElement::getAttributeObject(daeString name) {
	return getAttributeObjectWithIndex(*this, name);
}

daeBool daeElement::hasAttribute(daeString name) {
	return getAttributeObject(name) != 0;
}

daeBool daeElement::isAttributeSet(daeString name) {
	size_t i;
	if (getAttributeObjectWithIndex(*this, name, &i))
		return _validAttributeArray[i];
	return false;
}

std::string daeElement::getAttribute(daeString name) {
	std::string value;
	getAttribute(name, value);
	return value;
}

void daeElement::getAttribute(daeString name, std::string& value) {
	value = "";
	if (daeMetaAttribute* attr = getAttributeObject(name)) {
		std::ostringstream buffer;
		attr->memoryToString(this, buffer);
		value = buffer.str();
	}
}

daeMemoryRef daeElement::getAttributeValue(daeString name) {
	if (daeMetaAttribute* attr = getAttributeObject(name))
		return attr->get(this);
	return NULL;
}

daeBool daeElement::setAttribute(daeString name, daeString value) {
	size_t index;
	if (daeMetaAttribute* attr = getAttributeObjectWithIndex(*this, name, &index)) {
		if (attr->getType()) {
			attr->stringToMemory(this, value);
			_validAttributeArray.set(index, true);
			return true;
		}
	}
	return false;
}

daeMetaAttribute* daeElement::getCharDataObject() {
	if (_meta)
		return _meta->getValueAttribute();
	return NULL;
}

daeBool daeElement::hasCharData() {
	return getCharDataObject() != NULL;
}

std::string daeElement::getCharData() {
	std::string result;
	getCharData(result);
	return result;
}		

void daeElement::getCharData(std::string& data) {
	data = "";
	if (daeMetaAttribute* charDataAttr = getCharDataObject()) {
		std::ostringstream buffer;
		charDataAttr->memoryToString(this, buffer);
		data = buffer.str();
	}
}

void daeElement::setCharData(const std::string& data) {
	if (daeMetaAttribute* charDataAttr = getCharDataObject()) {
		charDataAttr->stringToMemory(this, data.c_str());
	}
}

daeBool daeElement::hasValue() {
	return hasCharData();
}

daeMemoryRef daeElement::getValuePointer() {
	if (daeMetaAttribute* charDataAttr = getCharDataObject())
		return charDataAttr->get(this);
	return NULL;
}

void
daeElement::appendResolveElement(daeElement* elem)
{
//Contributed by Nus - Wed, 08 Nov 2006
	// resolveArray.append(elem);
	pResolveArray->append(elem);
//----------------------
}
void
daeElement::resolveAll()
{
	int cnt;
//Contributed by Nus - Wed, 08 Nov 2006
	// while(resolveArray.getCount()) {
	while(pResolveArray->getCount()) {
		// cnt = (int)resolveArray.getCount();
		cnt = (int)pResolveArray->getCount();
		// daeElementRef elem = resolveArray[cnt-1];
		daeElementRef elem = (*pResolveArray)[cnt-1];
		// resolveArray.removeIndex(cnt-1);
		pResolveArray->removeIndex(cnt-1);
//--------------------------
		elem->resolve();
	}
	/*size_t cnt = resolveArray.getCount();
	for ( size_t i =0; i < cnt; i++ ) {
		resolveArray[i]->resolve();
	}
	resolveArray.clear();*/
}

void
daeElement::clearResolveArray()
{
//Contributed by Nus - Wed, 08 Nov 2006
	// resolveArray.clear();
	pResolveArray->clear();
//------------------------
}

void
daeElement::resolve()
{
	if (_meta == NULL)
		return;
	
	daeMetaAttributePtrArray& maa = _meta->getMetaResolvers();
	int n = (int)maa.getCount();
	int i;
	for(i=0;i<n;i++)
		maa[i]->resolve(this);
}

void
daeElement::setup(daeMetaElement* meta)
{
	if (_meta)
		return;
	_meta = meta;
	if (meta->needsResolve())
		appendResolveElement((daeElement*)this);
	daeMetaElement* intlibMeta = meta->getMetaIntegration();
	if (intlibMeta != NULL)
	{
		 daeElementRef intObj = intlibMeta->create();
		 intObj->ref(); //inc the ref count
		_intObject = (daeIntegrationObject*)(daeElement*)intObj;
	}
	daeMetaAttributeRefArray& attrs = meta->getMetaAttributes();
	int macnt = (int)attrs.getCount();

	_validAttributeArray.setCount( macnt );

	int i;
	for(i=0;i<macnt;i++) {
		if (attrs[i]->getDefaultValue() != NULL) {
			attrs[i]->copyDefault(this);
			_validAttributeArray[i] = true;
		}
//		else {
//			_validAttributeArray[i] = false;
//		}
	}

	//set up the _CMData array if there is one
	if ( _meta->getMetaCMData() != NULL )
	{
		daeTArray< daeCharArray *> *CMData = (daeTArray< daeCharArray *>*)_meta->getMetaCMData()->getWritableMemory(this);
		CMData->setCount( _meta->getNumChoices() );
		for ( unsigned int i = 0; i < _meta->getNumChoices(); i++ )
		{
			CMData->set( i, new daeCharArray() );
		}
	}

#if 0	
	// Setup resolvers to know their containers and thus their file context
	daeMetaAttributePtrArray& resolvers = meta->getMetaResolvers();
	int racnt = resolvers.getCount();
	for(i=0;i<racnt;i++)
		((daeURI*)(resolvers[i]->getWritableMemory(this)))->_container =
			this;
#endif	
}

daeElement::daeElement():
		_intObject(0),
		_parent(NULL),
		_document(NULL),
		_meta(NULL),
		_elementName(NULL)
{}

daeElement::~daeElement()
{
	if (_intObject)
		_intObject->release();

	if (_elementName) {
		delete[] _elementName;
		_elementName = NULL;
	}
}

//function used until we clarify what's a type and what's a name for an element
daeString daeElement::getTypeName() const
{
	return _meta->getName();
}
daeString daeElement::getElementName() const
{
	return _elementName ? _elementName : (daeString)_meta->getName();
}
void daeElement::setElementName( daeString nm ) {
	if ( nm == NULL ) {
		if ( _elementName ) delete[] _elementName;
		_elementName = NULL;
		return;
	}
	if ( !_elementName ) _elementName = new daeChar[128];
	strcpy( (char*)_elementName, nm );
}

daeString daeElement::getID() const
{
	if ((_meta == NULL) || (!_meta->getIDAttribute()))
		return NULL;
	else
		return *(daeStringRef*)_meta->getIDAttribute()->getWritableMemory(const_cast<daeElement*>(this));
}

void daeElement::getChildren( daeElementRefArray &array ) {
	_meta->getChildren( this, array );
}

daeSmartRef<daeElement> daeElement::clone(daeString idSuffix, daeString nameSuffix) {
	// Use the meta object system to create a new instance of this element. We need to
	// create a new meta if we're cloning a domAny object because domAnys never share meta objects.
	// Ideally we'd be able to clone the _meta for domAny objects. Then we wouldn't need
	// any additional special case code for cloning domAny. Unfortunately, we don't have a
	// daeMetaElement::clone method.
	bool any = strcmp(getTypeName(), "any") == 0;
	daeElementRef ret = any ? domAny::registerElement()->create() : _meta->create();
	ret->setElementName( _elementName );

	// Copy the attributes and character data. Requires special care for domAny.
	if (any) {
		domAny* thisAny = (domAny*)this;
		domAny* retAny = (domAny*)ret.cast();
		for (size_t i = 0; i < thisAny->getAttributeCount(); i++)
			retAny->setAttribute(thisAny->getAttributeName(i), thisAny->getAttributeValue(i));
		retAny->setValue(thisAny->getValue());
	} else {
		// Use the meta system to copy attributes
		daeMetaAttributeRefArray &attrs = _meta->getMetaAttributes();
		for (unsigned int i = 0; i < attrs.getCount(); i++) {
			attrs[i]->copy( ret, this );
			ret->_validAttributeArray[i] = _validAttributeArray[i];
		}
		if (daeMetaAttribute* valueAttr = getCharDataObject())
			valueAttr->copy( ret, this );
	}
	
	daeElementRefArray children;
	_meta->getChildren( this, children );
	for ( size_t x = 0; x < children.getCount(); x++ ) {
		ret->placeElement( children.get(x)->clone( idSuffix, nameSuffix ) );
	}

	// Mangle the id
	if (idSuffix) {
		std::string id = ret->getAttribute("id");
		if (!id.empty())
			ret->setAttribute("id", (id + idSuffix).c_str());
	}
	// Mangle the name
	if (nameSuffix) {
		std::string name = ret->getAttribute("name");
		if (!name.empty())
			ret->setAttribute("name", (name + nameSuffix).c_str());
	}
	return ret;
}

daeURI *daeElement::getDocumentURI() const {
	if ( _document == NULL ) {
		return NULL;
	}
	return _document->getDocumentURI();
}
