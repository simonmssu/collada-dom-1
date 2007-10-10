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
#ifndef __domLinear_extrusion_surface_h__
#define __domLinear_extrusion_surface_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

#include <dom/domCurveType.h>

/**
 * Describes a surface of linear extrusion ("extruded     surface"), e.g.
 * a generalized cylinder. Such a surface     is obtained by sweeping a curve
 * (called the "extruded     curve" or "basis") in a given direction (referred
 * to as     the "direction of extrusion" and defined by a unit     vector).
 * The u parameter is along the extruded curve.     The v parameter is along
 * the direction of extrusion. The     parameter range for the u parameter
 * is defined by the     reference curve. The parameter range for the v parameter
 * is ] - infinity, + infinity [. The position of the curve     gives the
 * origin of the v parameter. The form of a     surface of linear extrusion
 * is generally a ruled     surface. It can be: - a cylindrical surface, if
 * the     extruded curve is a circle, or a trimmed circle, with an     axis
 * parallel to the direction of extrusion, or - a     planar surface, if the
 * extruded curve is a line.
 */
class domLinear_extrusion_surface : public daeElement
{
public:
	COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::LINEAR_EXTRUSION_SURFACE; }
public:
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
	domCurveTypeRef elemCurve;
	domDirectionRef elemDirection;

public:	//Accessors and Mutators
	/**
	 * Gets the curve element.
	 * @return a daeSmartRef to the curve element.
	 */
	const domCurveTypeRef getCurve() const { return elemCurve; }
	/**
	 * Gets the direction element.
	 * @return a daeSmartRef to the direction element.
	 */
	const domDirectionRef getDirection() const { return elemDirection; }
protected:
	/**
	 * Constructor
	 */
	domLinear_extrusion_surface() : elemCurve(), elemDirection() {}
	/**
	 * Destructor
	 */
	virtual ~domLinear_extrusion_surface() {}
	/**
	 * Copy Constructor
	 */
	domLinear_extrusion_surface( const domLinear_extrusion_surface &cpy ) : daeElement() { (void)cpy; }
	/**
	 * Overloaded assignment operator
	 */
	virtual domLinear_extrusion_surface &operator=( const domLinear_extrusion_surface &cpy ) { (void)cpy; return *this; }

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
