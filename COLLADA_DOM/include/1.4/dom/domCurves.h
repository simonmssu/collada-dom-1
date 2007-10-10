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
#ifndef __domCurves_h__
#define __domCurves_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

#include <dom/domCurveType.h>

/**
 * This element holds all the curves that are needed for     the geometrical
 * description of the topological entities     edges an also surfaces (for
 * an extrusion).
 */
class domCurves : public daeElement
{
public:
	COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::CURVES; }

protected:  // Element
	domCurveType_Array elemCurve_array;

public:	//Accessors and Mutators
	/**
	 * Gets the curve element array.
	 * @return Returns a reference to the array of curve elements.
	 */
	domCurveType_Array &getCurve_array() { return elemCurve_array; }
	/**
	 * Gets the curve element array.
	 * @return Returns a constant reference to the array of curve elements.
	 */
	const domCurveType_Array &getCurve_array() const { return elemCurve_array; }
protected:
	/**
	 * Constructor
	 */
	domCurves() : elemCurve_array() {}
	/**
	 * Destructor
	 */
	virtual ~domCurves() {}
	/**
	 * Copy Constructor
	 */
	domCurves( const domCurves &cpy ) : daeElement() { (void)cpy; }
	/**
	 * Overloaded assignment operator
	 */
	virtual domCurves &operator=( const domCurves &cpy ) { (void)cpy; return *this; }

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
