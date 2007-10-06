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

#include <sstream>
#include <dae/daeMetaAttribute.h>
#include <dae/daeMetaElement.h>
#include <dae/daeErrorHandler.h>
#include <dae/daeDocument.h>

void daeMetaAttribute::set(daeElement* e, daeString s) {
	stringToMemory(e, s);
}

void daeMetaAttribute::copy(daeElement* to, daeElement *from) {
	_type->copy(getWritableMemory(from), getWritableMemory(to));
}

void daeMetaArrayAttribute::copy(daeElement* to, daeElement *from) {
	daeArray& fromArray = (daeArray&)*getWritableMemory(from);
	daeArray& toArray = (daeArray&)*getWritableMemory(to);
	_type->copyArray(fromArray, toArray);
}

void daeMetaAttribute::copyDefault(daeElement* element) {
	if (_defaultValue)
		_type->copy(_defaultValue, get(element));
}

void daeMetaArrayAttribute::copyDefault(daeElement* element) {
	if (_defaultValue)
		_type->copyArray((daeArray&)*_defaultValue, (daeArray&)*getWritableMemory(element));
}
	
daeInt daeMetaAttribute::compare(daeElement* elt1, daeElement* elt2) {
	return _type->compare(get(elt1), get(elt2));
}

daeInt daeMetaArrayAttribute::compare(daeElement* elt1, daeElement* elt2) {
	daeArray& value1 = (daeArray&)*getWritableMemory(elt1);
	daeArray& value2 = (daeArray&)*getWritableMemory(elt2);
	return _type->compareArray(value1, value2);
}

daeInt daeMetaAttribute::compareToDefault(daeElement* e) {
	if (!_defaultValue)
		return 1;
	return _type->compare(get(e), _defaultValue);
}

daeInt daeMetaArrayAttribute::compareToDefault(daeElement* e) {
	if (!_defaultValue)
		return 1;
	daeArray& value1 = (daeArray&)*getWritableMemory(e);
	daeArray& value2 = (daeArray&)*_defaultValue;
	return _type->compareArray(value1, value2);
}

daeMetaAttribute::daeMetaAttribute()
{
	_name = "noname";
	_offset = -1;
	_type = NULL;
	_container = NULL;
	_defaultString = "";
	_defaultValue = NULL;
	_isRequired = false;
}

daeMetaAttribute::~daeMetaAttribute() {
	if (_defaultValue)
		_type->destroy(_defaultValue);
	_defaultValue = NULL;
}

daeMetaArrayAttribute::~daeMetaArrayAttribute() {
	delete (daeArray*)_defaultValue;
	_defaultValue = NULL;
}

void
daeMetaAttribute::resolve(daeElementRef element)
{
	if (_type != NULL)
		_type->resolve(element, getWritableMemory(element) );
}

void
daeMetaArrayAttribute::resolve(daeElementRef element)
{
	daeArray* era = (daeArray*)getWritableMemory(element);
	size_t cnt = era->getCount();
	for ( size_t i = 0; i < cnt; i++ )
	{
		_type->resolve( element, era->getRaw(i) );
	}
}

daeInt
daeMetaAttribute::getSize()
{
	return _type->getSize();
}
daeInt
daeMetaAttribute::getAlignment()
{
	return _type->getAlignment();
}

daeInt
daeMetaAttribute::getCount(daeElement* e)
{
	if (e == NULL)
		return 0;
	return (getWritableMemory(e) != NULL);
}

void daeMetaAttribute::memoryToString(daeElement* e, std::ostringstream& buffer) {
	_type->memoryToString(get(e), buffer);
}

void daeMetaAttribute::stringToMemory(daeElement* e, daeString s) {
	if (!strcmp(_name, "id") && e->getDocument()) {
		e->getDocument()->changeElementID(e, s);
	}

	_type->stringToMemory((daeChar*)s, get(e));
}

daeChar* daeMetaAttribute::getWritableMemory(daeElement* e) {
	return (daeChar*)e + _offset;
}

daeMemoryRef
daeMetaAttribute::get(daeElement *e, daeInt index)
{
	(void)index; 
	return getWritableMemory(e);
}

void daeMetaAttribute::setDefaultString(daeString defaultVal) {
	_defaultString = defaultVal;
	if (!_defaultValue)
		_defaultValue = _type->create();
	_type->stringToMemory((daeChar*)_defaultString.c_str(), _defaultValue);
}

void daeMetaAttribute::setDefaultValue(daeMemoryRef defaultVal) {
	if (!_defaultValue)
		_defaultValue = _type->create();
	_type->copy(defaultVal, _defaultValue);
	std::ostringstream buffer;
	_type->memoryToString(_defaultValue, buffer);
	_defaultString = buffer.str();
}

daeInt
daeMetaArrayAttribute::getCount(daeElement *e)
{
	if (e == NULL)
		return 0;
	return (daeInt)((daeArray*)getWritableMemory(e))->getCount();
}

void daeMetaArrayAttribute::memoryToString(daeElement* e, std::ostringstream& buffer) {
	if (e)
		_type->arrayToString(*(daeArray*)getWritableMemory(e), buffer);
}

void daeMetaArrayAttribute::stringToMemory(daeElement* e, daeString s) {
	if (e)
		_type->stringToArray((daeChar*)s, *(daeArray*)getWritableMemory(e));
}

daeMemoryRef daeMetaArrayAttribute::get(daeElement* e, daeInt index) {
	if (e) {
		daeArray* array = (daeArray*)getWritableMemory(e);
		if (index < (daeInt)array->getCount())
			return array->getRaw(index);
	}

	return NULL;
}

void daeMetaArrayAttribute::setDefaultString(daeString defaultVal) {
	_defaultString = defaultVal;
	if (!_defaultValue)
		_defaultValue = (daeMemoryRef)_type->createArray();
	_type->stringToArray((daeChar*)_defaultString.c_str(), (daeArray&)*_defaultValue);
}

void daeMetaArrayAttribute::setDefaultValue(daeMemoryRef defaultVal) {
	if (!_defaultValue)
		_defaultValue = (daeMemoryRef)_type->createArray();
	_type->copyArray((daeArray&)*defaultVal, (daeArray&)*_defaultValue);
	std::ostringstream buffer;
	_type->arrayToString((daeArray&)*_defaultValue, buffer);
	_defaultString = buffer.str();
}

daeString daeMetaAttribute::getDefaultString() {
	return _defaultString.c_str();
}

daeMemoryRef daeMetaAttribute::getDefaultValue() {
	return _defaultValue;
}
