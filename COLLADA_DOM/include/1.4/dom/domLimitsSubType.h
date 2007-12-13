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
#ifndef __domLimitsSubType_h__
#define __domLimitsSubType_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>


class domLimitsSubType_complexType 
{
protected:  // Attribute
	xsNCName attrSid;

protected:  // Value
	/**
	 * The domFloat value of the text data of this element. 
	 */
	domFloat _value;

public:	//Accessors and Mutators
	/**
	 * Gets the sid attribute.
	 * @return Returns a xsNCName of the sid attribute.
	 */
	xsNCName getSid() const { return attrSid; }
	/**
	 * Sets the sid attribute.
	 * @param atSid The new value for the sid attribute.
	 */
	void setSid( xsNCName atSid ) { *(daeStringRef*)&attrSid = atSid;}

	/**
	 * Gets the value of this element.
	 * @return a domFloat of the value.
	 */
	domFloat getValue() const { return _value; }
	/**
	 * Sets the _value of this element.
	 * @param val The new value for this element.
	 */
	void setValue( domFloat val ) { _value = val; }

protected:
	/**
	 * Constructor
	 */
	domLimitsSubType_complexType() : attrSid(), _value() {}
	/**
	 * Destructor
	 */
	virtual ~domLimitsSubType_complexType() {}
	/**
	 * Copy Constructor
	 */
	domLimitsSubType_complexType( const domLimitsSubType_complexType &cpy ) { (void)cpy; }
	/**
	 * Overloaded assignment operator
	 */
	virtual domLimitsSubType_complexType &operator=( const domLimitsSubType_complexType &cpy ) { (void)cpy; return *this; }
};

/**
 * An element of type domLimitsSubType_complexType.
 */
class domLimitsSubType : public daeElement, public domLimitsSubType_complexType
{
public:
	COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::LIMITSSUBTYPE; }

public:	//Accessors and Mutators
	/**
	 * Gets the sid attribute.
	 * @return Returns a xsNCName of the sid attribute.
	 */
	xsNCName getSid() const { return attrSid; }
	/**
	 * Sets the sid attribute.
	 * @param atSid The new value for the sid attribute.
	 */
	void setSid( xsNCName atSid ) { *(daeStringRef*)&attrSid = atSid; _validAttributeArray[0] = true; }

protected:
	/**
	 * Constructor
	 */
	domLimitsSubType() {}
	/**
	 * Destructor
	 */
	virtual ~domLimitsSubType() {}
	/**
	 * Copy Constructor
	 */
	domLimitsSubType( const domLimitsSubType &cpy ) : daeElement(), domLimitsSubType_complexType() { (void)cpy; }
	/**
	 * Overloaded assignment operator
	 */
	virtual domLimitsSubType &operator=( const domLimitsSubType &cpy ) { (void)cpy; return *this; }

public: // STATIC METHODS
	/**
	 * Creates an instance of this class and returns a daeElementRef referencing it.
	 * @param bytes The size allocated for this instance.
	 * @return a daeElementRef referencing an instance of this object.
	 */
	static DLLSPEC daeElementRef create(daeInt bytes);
	/**
	 * Creates a daeMetaElement object that describes this element in the meta object reflection framework.
	 * If a daeMetaElement already exists it will return that instead of creating a new one. 
	 * @return A daeMetaElement describing this COLLADA element.
	 */
	static DLLSPEC daeMetaElement* registerElement();

public: // STATIC MEMBERS
	/**
	 * The daeMetaElement that describes this element in the meta object reflection framework.
	 */
	static DLLSPEC daeMetaElement* _Meta;
};


#endif
