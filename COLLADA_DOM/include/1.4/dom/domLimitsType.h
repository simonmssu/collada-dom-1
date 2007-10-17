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
#ifndef __domLimitsType_h__
#define __domLimitsType_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

#include <dom/domLimitsSubType.h>

class domLimitsType_complexType 
{
protected:  // Attribute
	xsNCName attrSid;

protected:  // Elements
	domLimitsSubTypeRef elemMin;
	domLimitsSubTypeRef elemMax;

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
	 * Gets the min element.
	 * @return a daeSmartRef to the min element.
	 */
	const domLimitsSubTypeRef getMin() const { return elemMin; }
	/**
	 * Gets the max element.
	 * @return a daeSmartRef to the max element.
	 */
	const domLimitsSubTypeRef getMax() const { return elemMax; }
protected:
	/**
	 * Constructor
	 */
	domLimitsType_complexType() : attrSid(), elemMin(), elemMax() {}
	/**
	 * Destructor
	 */
	virtual ~domLimitsType_complexType() {}
	/**
	 * Copy Constructor
	 */
	domLimitsType_complexType( const domLimitsType_complexType &cpy ) { (void)cpy; }
	/**
	 * Overloaded assignment operator
	 */
	virtual domLimitsType_complexType &operator=( const domLimitsType_complexType &cpy ) { (void)cpy; return *this; }
};

/**
 * An element of type domLimitsType_complexType.
 */
class domLimitsType : public daeElement, public domLimitsType_complexType
{
public:
	COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::LIMITSTYPE; }

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
	domLimitsType() {}
	/**
	 * Destructor
	 */
	virtual ~domLimitsType() {}
	/**
	 * Copy Constructor
	 */
	domLimitsType( const domLimitsType &cpy ) : daeElement(), domLimitsType_complexType() { (void)cpy; }
	/**
	 * Overloaded assignment operator
	 */
	virtual domLimitsType &operator=( const domLimitsType &cpy ) { (void)cpy; return *this; }

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
