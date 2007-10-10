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
#ifndef __domCircle_h__
#define __domCircle_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>


/**
 * Describes a circle. A circle is defined by its radius     and, as with
 * any conic curve, is positioned in space     with a right-handed coordinate
 * system where: - the     origin is the center of the circle, and - the origin,
 * "X     Direction" and "Y Direction" define the plane of the     circle.
 * This coordinate system is the local coordinate     system of the circle.
 * The "main Direction" of this     coordinate system is the vector normal
 * to the plane of     the circle. The axis, of which the origin and unit
 * vector are respectively the origin and "main Direction"     of the local
 * coordinate system, is termed the "Axis" or     "main Axis" of the circle.
 * The "main Direction" of the     local coordinate system gives an explicit
 * orientation to     the circle (definition of the trigonometric sense),
 * determining the direction in which the parameter     increases along the
 * circle. The Geom_Circle circle is     parameterized by an angle: P(U) =
 * O + R*Cos(U)*XDir +     R*Sin(U)*YDir, where: - P is the point of parameter
 * U, -     O, XDir and YDir are respectively the origin, "X     Direction"
 * and "Y Direction" of its local coordinate     system, - R is the radius
 * of the circle. The "X     Axis" of the local coordinate system therefore
 * defines the origin of the parameter of the circle.     The parameter is
 * the angle with this "X Direction".     A circle is a closed and periodic
 * curve. The period     is 2.*Pi and the parameter range is [ 0, 2.*Pi [.
 */
class domCircle : public daeElement
{
public:
	COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::CIRCLE; }
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



protected:  // Element
	domRadiusRef elemRadius;

public:	//Accessors and Mutators
	/**
	 * Gets the radius element.
	 * @return a daeSmartRef to the radius element.
	 */
	const domRadiusRef getRadius() const { return elemRadius; }
protected:
	/**
	 * Constructor
	 */
	domCircle() : elemRadius() {}
	/**
	 * Destructor
	 */
	virtual ~domCircle() {}
	/**
	 * Copy Constructor
	 */
	domCircle( const domCircle &cpy ) : daeElement() { (void)cpy; }
	/**
	 * Overloaded assignment operator
	 */
	virtual domCircle &operator=( const domCircle &cpy ) { (void)cpy; return *this; }

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
