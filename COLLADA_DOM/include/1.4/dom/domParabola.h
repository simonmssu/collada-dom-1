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
#ifndef __domParabola_h__
#define __domParabola_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>


/**
 * Describes a parabola in 3D space. A parabola is defined     by its focal
 * length (i.e. the distance between its focus     and its apex) and is positioned
 * in space with a     coordinate system where: - the origin is     the apex
 * of the parabola, - the "X Axis"     defines the axis of symmetry; the parabola
 * is on the     positive side of this axis, - the origin, "X     Direction"
 * and "Y Direction" define the     plane of the parabola. This coordinate
 * system is the     local coordinate system of the parabola. The "main  
 * Direction" of this coordinate system is a vector     normal to the plane
 * of the parabola. The axis, of which     the origin and unit vector are
 * respectively the origin     and "main Direction" of the local coordinate
 * system, is termed the "Axis" or "main     Axis" of the parabola. The "main
 * Direction" of the local coordinate system gives an     explicit orientation
 * to the parabola, determining the     direction in which the parameter increases
 * along the     parabola. The Geom_Parabola parabola is parameterized as
 * follows: P(U) = O + U*U/(4.*F)*XDir + U*YDir where: - P     is the point
 * of parameter U, - O, XDir and YDir are     respectively the origin, "X
 * <br>     Direction" and "Y Direction" of its local     coordinate system,
 * - F is the focal length of the     parabola. The parameter of the parabola
 * is therefore its     Y coordinate in the local coordinate system, with
 * the     "X <br> Axis" of the local coordinate     system defining the origin
 * of the parameter. The     parameter range is ] -infinite, +infinite [.
 */
class domParabola : public daeElement
{
public:
	COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::PARABOLA; }
public:
	class domFocal;

	typedef daeSmartRef<domFocal> domFocalRef;
	typedef daeTArray<domFocalRef> domFocal_Array;

	class domFocal : public daeElement
	{
	public:
		COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::FOCAL; }

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
		domFocal() : _value() {}
		/**
		 * Destructor
		 */
		virtual ~domFocal() {}
		/**
		 * Copy Constructor
		 */
		domFocal( const domFocal &cpy ) : daeElement() { (void)cpy; }
		/**
		 * Overloaded assignment operator
		 */
		virtual domFocal &operator=( const domFocal &cpy ) { (void)cpy; return *this; }

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
	domFocalRef elemFocal;

public:	//Accessors and Mutators
	/**
	 * Gets the focal element.
	 * @return a daeSmartRef to the focal element.
	 */
	const domFocalRef getFocal() const { return elemFocal; }
protected:
	/**
	 * Constructor
	 */
	domParabola() : elemFocal() {}
	/**
	 * Destructor
	 */
	virtual ~domParabola() {}
	/**
	 * Copy Constructor
	 */
	domParabola( const domParabola &cpy ) : daeElement() { (void)cpy; }
	/**
	 * Overloaded assignment operator
	 */
	virtual domParabola &operator=( const domParabola &cpy ) { (void)cpy; return *this; }

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
