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
#ifndef __domHyperbola_h__
#define __domHyperbola_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>


/**
 * Describes a branch of a hyperbola in 3D space. A     hyperbola is defined
 * by its major and minor radii and,     as with any conic curve, is positioned
 * in space with a     right-handed coordinate system where: - the origin
 * is     the center of the hyperbola, - the "X Direction" defines     the
 * major axis, and - the "Y Direction" defines the     minor axis. The origin,
 * "X Direction" and "Y Direction"     of this coordinate system define the
 * plane of the     hyperbola. The coordinate system is the local coordinate
 * system of the hyperbola. The branch of the hyperbola     described is the
 * one located on the positive side of the     major axis. The "main Direction"
 * of the local coordinate     system is a vector normal to the plane of the
 * hyperbola.     The axis, of which the origin and unit vector are     respectively
 * the origin and "main Direction" of the     local coordinate system, is
 * termed the "Axis" or "main     Axis" of the hyperbola. The "main Direction"
 * of the     local coordinate system gives an explicit orientation to   
 * the hyperbola, determining the direction in which the     parameter increases
 * along the hyperbola. The     Geom_Hyperbola hyperbola is parameterized
 * as follows:     P(U) = O + MajRad*Cosh(U)*XDir + MinRad*Sinh(U)*YDir, 
 * where: - P is the point of parameter U, - O, XDir and     YDir are respectively
 * the origin, "X Direction" and "Y     Direction" of its local coordinate
 * system, - MajRad and     MinRad are the major and minor radii of the hyperbola.
 * The "X Axis" of the local coordinate system therefore     defines the origin
 * of the parameter of the hyperbola.     The parameter range is ] -infinite,
 * +infinite [.
 */
class domHyperbola : public daeElement
{
public:
	COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::HYPERBOLA; }
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
		 * The domFloat2 value of the text data of this element. 
		 */
		domFloat2 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a domFloat2 reference of the _value array.
		 */
		domFloat2 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant domFloat2 reference of the _value array.
		 */
		const domFloat2 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const domFloat2 &val ) { _value = val; }

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
	domHyperbola() : elemRadius() {}
	/**
	 * Destructor
	 */
	virtual ~domHyperbola() {}
	/**
	 * Copy Constructor
	 */
	domHyperbola( const domHyperbola &cpy ) : daeElement() { (void)cpy; }
	/**
	 * Overloaded assignment operator
	 */
	virtual domHyperbola &operator=( const domHyperbola &cpy ) { (void)cpy; return *this; }

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
