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
#ifndef __domCone_h__
#define __domCone_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>


/**
 * A cone is defined by its base radius and the half of the           apex
 * angle.
 */
class domCone : public daeElement
{
public:
	COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::CONE; }
public:
	class domRadius;

	typedef daeSmartRef<domRadius> domRadiusRef;
	typedef daeTArray<domRadiusRef> domRadius_Array;

	class domRadius : public daeElement
	{
	public:
		COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::RADIUS; }

	protected:  // Value
		/**
		 * The domFloat value of the text data of this element. 
		 */
		domFloat _value;

	public:	//Accessors and Mutators
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
		domRadius() : _value() {}
		/**
		 * Destructor
		 */
		virtual ~domRadius() {}
		/**
		 * Copy Constructor
		 */
		domRadius( const domRadius &cpy ) : daeElement() { (void)cpy; }
		/**
		 * Overloaded assignment operator
		 */
		virtual domRadius &operator=( const domRadius &cpy ) { (void)cpy; return *this; }

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

	class domHalf_apex;

	typedef daeSmartRef<domHalf_apex> domHalf_apexRef;
	typedef daeTArray<domHalf_apexRef> domHalf_apex_Array;

	class domHalf_apex : public daeElement
	{
	public:
		COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::HALF_APEX; }

	protected:  // Value
		/**
		 * The xsFloat value of the text data of this element. 
		 */
		xsFloat _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the value of this element.
		 * @return a xsFloat of the value.
		 */
		xsFloat getValue() const { return _value; }
		/**
		 * Sets the _value of this element.
		 * @param val The new value for this element.
		 */
		void setValue( xsFloat val ) { _value = val; }

	protected:
		/**
		 * Constructor
		 */
		domHalf_apex() : _value() {}
		/**
		 * Destructor
		 */
		virtual ~domHalf_apex() {}
		/**
		 * Copy Constructor
		 */
		domHalf_apex( const domHalf_apex &cpy ) : daeElement() { (void)cpy; }
		/**
		 * Overloaded assignment operator
		 */
		virtual domHalf_apex &operator=( const domHalf_apex &cpy ) { (void)cpy; return *this; }

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



protected:  // Elements
	domRadiusRef elemRadius;
	domHalf_apexRef elemHalf_apex;

public:	//Accessors and Mutators
	/**
	 * Gets the radius element.
	 * @return a daeSmartRef to the radius element.
	 */
	const domRadiusRef getRadius() const { return elemRadius; }
	/**
	 * Gets the half_apex element.
	 * @return a daeSmartRef to the half_apex element.
	 */
	const domHalf_apexRef getHalf_apex() const { return elemHalf_apex; }
protected:
	/**
	 * Constructor
	 */
	domCone() : elemRadius(), elemHalf_apex() {}
	/**
	 * Destructor
	 */
	virtual ~domCone() {}
	/**
	 * Copy Constructor
	 */
	domCone( const domCone &cpy ) : daeElement() { (void)cpy; }
	/**
	 * Overloaded assignment operator
	 */
	virtual domCone &operator=( const domCone &cpy ) { (void)cpy; return *this; }

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
