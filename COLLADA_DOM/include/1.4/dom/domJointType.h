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
#ifndef __domJointType_h__
#define __domJointType_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

#include <dom/domLimitsType.h>

class domJointType_complexType 
{
public:
	class domAxis;

	typedef daeSmartRef<domAxis> domAxisRef;
	typedef daeTArray<domAxisRef> domAxis_Array;

	class domAxis : public daeElement
	{
	public:
		COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::AXIS; }
	protected:  // Attribute
		xsNCName attrSid;

	protected:  // Value
		/**
		 * The domFloat3 value of the text data of this element. 
		 */
		domFloat3 _value;

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
		 * @return Returns a domFloat3 reference of the _value array.
		 */
		domFloat3 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant domFloat3 reference of the _value array.
		 */
		const domFloat3 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const domFloat3 &val ) { _value = val; }

	protected:
		/**
		 * Constructor
		 */
		domAxis() : attrSid(), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domAxis() {}
		/**
		 * Copy Constructor
		 */
		domAxis( const domAxis &cpy ) : daeElement() { (void)cpy; }
		/**
		 * Overloaded assignment operator
		 */
		virtual domAxis &operator=( const domAxis &cpy ) { (void)cpy; return *this; }

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


protected:  // Attribute
	xsNCName attrSid;

protected:  // Elements
	domAxisRef elemAxis;
	domLimitsTypeRef elemLimits;

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
	 * Gets the axis element.
	 * @return a daeSmartRef to the axis element.
	 */
	const domAxisRef getAxis() const { return elemAxis; }
	/**
	 * Gets the limits element.
	 * @return a daeSmartRef to the limits element.
	 */
	const domLimitsTypeRef getLimits() const { return elemLimits; }
protected:
	/**
	 * Constructor
	 */
	domJointType_complexType() : attrSid(), elemAxis(), elemLimits() {}
	/**
	 * Destructor
	 */
	virtual ~domJointType_complexType() {}
	/**
	 * Copy Constructor
	 */
	domJointType_complexType( const domJointType_complexType &cpy ) { (void)cpy; }
	/**
	 * Overloaded assignment operator
	 */
	virtual domJointType_complexType &operator=( const domJointType_complexType &cpy ) { (void)cpy; return *this; }
};

/**
 * An element of type domJointType_complexType.
 */
class domJointType : public daeElement, public domJointType_complexType
{
public:
	COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::JOINTTYPE; }

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
	domJointType() {}
	/**
	 * Destructor
	 */
	virtual ~domJointType() {}
	/**
	 * Copy Constructor
	 */
	domJointType( const domJointType &cpy ) : daeElement(), domJointType_complexType() { (void)cpy; }
	/**
	 * Overloaded assignment operator
	 */
	virtual domJointType &operator=( const domJointType &cpy ) { (void)cpy; return *this; }

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
