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
#ifndef __domLine_h__
#define __domLine_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>


/**
 * Describes an infinite line. A line is defined and     positioned in space
 * with an axis which gives it an     origin and a unit vector. The Geom_Line
 * line is     parameterized: P (U) = O + U*Dir, where: - P is the     point
 * of parameter U, - O is the origin and Dir the unit     vector of its positioning
 * axis. The parameter range is ]     -infinite, +infinite [. The orientation
 * of the line is     given by the unit vector of its positioning axis.
 */
class domLine : public daeElement
{
public:
	COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::LINE; }
public:
	class domOrigin;

	typedef daeSmartRef<domOrigin> domOriginRef;
	typedef daeTArray<domOriginRef> domOrigin_Array;

	class domOrigin : public daeElement
	{
	public:
		COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::ORIGIN; }

	protected:  // Value
		/**
		 * The domFloat3 value of the text data of this element. 
		 */
		domFloat3 _value;

	public:	//Accessors and Mutators
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
		domOrigin() : _value() {}
		/**
		 * Destructor
		 */
		virtual ~domOrigin() {}
		/**
		 * Copy Constructor
		 */
		domOrigin( const domOrigin &cpy ) : daeElement() { (void)cpy; }
		/**
		 * Overloaded assignment operator
		 */
		virtual domOrigin &operator=( const domOrigin &cpy ) { (void)cpy; return *this; }

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

	class domDirection;

	typedef daeSmartRef<domDirection> domDirectionRef;
	typedef daeTArray<domDirectionRef> domDirection_Array;

	class domDirection : public daeElement
	{
	public:
		COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::DIRECTION; }

	protected:  // Value
		/**
		 * The domFloat3 value of the text data of this element. 
		 */
		domFloat3 _value;

	public:	//Accessors and Mutators
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
		domDirection() : _value() {}
		/**
		 * Destructor
		 */
		virtual ~domDirection() {}
		/**
		 * Copy Constructor
		 */
		domDirection( const domDirection &cpy ) : daeElement() { (void)cpy; }
		/**
		 * Overloaded assignment operator
		 */
		virtual domDirection &operator=( const domDirection &cpy ) { (void)cpy; return *this; }

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
	domOriginRef elemOrigin;
	domDirectionRef elemDirection;

public:	//Accessors and Mutators
	/**
	 * Gets the origin element.
	 * @return a daeSmartRef to the origin element.
	 */
	const domOriginRef getOrigin() const { return elemOrigin; }
	/**
	 * Gets the direction element.
	 * @return a daeSmartRef to the direction element.
	 */
	const domDirectionRef getDirection() const { return elemDirection; }
protected:
	/**
	 * Constructor
	 */
	domLine() : elemOrigin(), elemDirection() {}
	/**
	 * Destructor
	 */
	virtual ~domLine() {}
	/**
	 * Copy Constructor
	 */
	domLine( const domLine &cpy ) : daeElement() { (void)cpy; }
	/**
	 * Overloaded assignment operator
	 */
	virtual domLine &operator=( const domLine &cpy ) { (void)cpy; return *this; }

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
