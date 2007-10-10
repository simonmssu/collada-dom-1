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
#ifndef __domRevolution_surface_h__
#define __domRevolution_surface_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

#include <dom/domCurveType.h>

/**
 * Describes a surface of revolution (revolved surface).     Such a surface
 * is obtained by rotating a curve (called     the "meridian") through a complete
 * revolution about an     axis (referred to as the "axis of revolution").
 * The     curve and the axis must be in the same plane (the     "reference
 * plane" of the surface). Rotation around the     axis of revolution in the
 * trigonometric sense defines     the u parametric direction. So the u parameter
 * is an     angle, and its origin is given by the position of the     meridian
 * on the surface. The parametric range for the u     parameter is: [ 0, 2.*Pi
 * ] The v parameter is that of     the meridian. The form of a surface of
 * revolution is     typically a general revolution surface. It can be: -
 * a     conical surface, if the meridian is a line or a trimmed     line
 * - a cylindrical surface, if the meridian is a line     or a trimmed line
 * parallel to the axis of revolution, -     a planar surface if the meridian
 * is a line or a trimmed     line perpendicular to the axis of revolution
 * of the     surface, - a toroidal surface, if the meridian is a     circle
 * or a trimmed circle), or - a spherical surface,     if the meridian is
 * a circle, the center of which is     located on the axis of the revolved
 * surface.
 */
class domRevolution_surface : public daeElement
{
public:
	COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::REVOLUTION_SURFACE; }
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

	class domAxis;

	typedef daeSmartRef<domAxis> domAxisRef;
	typedef daeTArray<domAxisRef> domAxis_Array;

	class domAxis : public daeElement
	{
	public:
		COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::AXIS; }

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
		domAxis() : _value() {}
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



protected:  // Elements
	domCurveTypeRef elemCurve;
	domOriginRef elemOrigin;
	domAxisRef elemAxis;

public:	//Accessors and Mutators
	/**
	 * Gets the curve element.
	 * @return a daeSmartRef to the curve element.
	 */
	const domCurveTypeRef getCurve() const { return elemCurve; }
	/**
	 * Gets the origin element.
	 * @return a daeSmartRef to the origin element.
	 */
	const domOriginRef getOrigin() const { return elemOrigin; }
	/**
	 * Gets the axis element.
	 * @return a daeSmartRef to the axis element.
	 */
	const domAxisRef getAxis() const { return elemAxis; }
protected:
	/**
	 * Constructor
	 */
	domRevolution_surface() : elemCurve(), elemOrigin(), elemAxis() {}
	/**
	 * Destructor
	 */
	virtual ~domRevolution_surface() {}
	/**
	 * Copy Constructor
	 */
	domRevolution_surface( const domRevolution_surface &cpy ) : daeElement() { (void)cpy; }
	/**
	 * Overloaded assignment operator
	 */
	virtual domRevolution_surface &operator=( const domRevolution_surface &cpy ) { (void)cpy; return *this; }

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
