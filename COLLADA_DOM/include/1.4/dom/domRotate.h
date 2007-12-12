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

#ifndef __domRotate_h__
#define __domRotate_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

class DAE;

/**
 * The rotate element contains an angle and a mathematical vector that represents
 * the axis of rotation.
 */
class domRotate : public daeElement
{
public:
	virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::ROTATE; }
	static COLLADA_TYPE::TypeEnum getTypeStatic() { return COLLADA_TYPE::ROTATE; }
protected:  // Attribute
/**
 *  The sid attribute is a text string value containing the sub-identifier
 * of this element.  This value must be unique within the scope of the parent
 * element. Optional attribute. 
 */
	xsNCName attrSid;

protected:  // Value
	/**
	 * The domFloat4 value of the text data of this element. 
	 */
	domFloat4 _value;

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

	/**
	 * Gets the _value array.
	 * @return Returns a domFloat4 reference of the _value array.
	 */
	domFloat4 &getValue() { return _value; }
	/**
	 * Gets the _value array.
	 * @return Returns a constant domFloat4 reference of the _value array.
	 */
	const domFloat4 &getValue() const { return _value; }
	/**
	 * Sets the _value array.
	 * @param val The new value for the _value array.
	 */
	void setValue( const domFloat4 &val ) { _value = val; }

protected:
	/**
	 * Constructor
	 */
	domRotate(DAE& dae) : attrSid(), _value() {}
	/**
	 * Destructor
	 */
	virtual ~domRotate() {}
	/**
	 * Overloaded assignment operator
	 */
	virtual domRotate &operator=( const domRotate &cpy ) { (void)cpy; return *this; }

public: // STATIC METHODS
	/**
	 * Creates an instance of this class and returns a daeElementRef referencing it.
	 * @return a daeElementRef referencing an instance of this object.
	 */
	static DLLSPEC daeElementRef create(DAE& dae);
	/**
	 * Creates a daeMetaElement object that describes this element in the meta object reflection framework.
	 * If a daeMetaElement already exists it will return that instead of creating a new one. 
	 * @return A daeMetaElement describing this COLLADA element.
	 */
	static DLLSPEC daeMetaElement* registerElement(DAE& dae);
};


#endif
