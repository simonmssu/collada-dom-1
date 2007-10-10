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
#ifndef __domSurfaceType_h__
#define __domSurfaceType_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

#include <dom/domCylinder.h>
#include <dom/domPlane.h>
#include <dom/domSphere.h>
#include <dom/domCylindrical.h>
#include <dom/domTorus.h>
#include <dom/domLinear_extrusion_surface.h>
#include <dom/domRevolution_surface.h>
#include <dom/domTapered_cylinder.h>
#include <dom/domSpline.h>
#include <dom/domRotate.h>
#include <dom/domTranslate.h>

/**
 * A surfaceType defines the attributes of a surface     element. With rotate
 * and translate the surface can be     positioned to its right location.
 */
class domSurfaceType_complexType 
{
protected:  // Attributes
/**
 *       The sid of the surface.     
 */
	xsNCName attrSid;
/**
 *       The name of the surface.     
 */
	xsNCName attrName;

protected:  // Elements
	domCylinderRef elemCylinder;
	domPlaneRef elemPlane;
	domSphereRef elemSphere;
	domCylindricalRef elemCylindrical;
	domTorusRef elemTorus;
	domLinear_extrusion_surfaceRef elemLinear_extrusion_surface;
	domRevolution_surfaceRef elemRevolution_surface;
	domTapered_cylinderRef elemTapered_cylinder;
	domSplineRef elemSpline;
	domRotate_Array elemRotate_array;
	domTranslate_Array elemTranslate_array;
	/**
	 * Used to preserve order in elements that do not specify strict sequencing of sub-elements.
	 */
	daeElementRefArray _contents;
	/**
	 * Used to preserve order in elements that have a complex content model.
	 */
	daeUIntArray       _contentsOrder;

	/**
	 * Used to store information needed for some content model objects.
	 */
	daeTArray< daeCharArray * > _CMData;


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
	 * Gets the name attribute.
	 * @return Returns a xsNCName of the name attribute.
	 */
	xsNCName getName() const { return attrName; }
	/**
	 * Sets the name attribute.
	 * @param atName The new value for the name attribute.
	 */
	void setName( xsNCName atName ) { *(daeStringRef*)&attrName = atName;}

	/**
	 * Gets the cylinder element.
	 * @return a daeSmartRef to the cylinder element.
	 */
	const domCylinderRef getCylinder() const { return elemCylinder; }
	/**
	 * Gets the plane element.
	 * @return a daeSmartRef to the plane element.
	 */
	const domPlaneRef getPlane() const { return elemPlane; }
	/**
	 * Gets the sphere element.
	 * @return a daeSmartRef to the sphere element.
	 */
	const domSphereRef getSphere() const { return elemSphere; }
	/**
	 * Gets the cylindrical element.
	 * @return a daeSmartRef to the cylindrical element.
	 */
	const domCylindricalRef getCylindrical() const { return elemCylindrical; }
	/**
	 * Gets the torus element.
	 * @return a daeSmartRef to the torus element.
	 */
	const domTorusRef getTorus() const { return elemTorus; }
	/**
	 * Gets the linear_extrusion_surface element.
	 * @return a daeSmartRef to the linear_extrusion_surface element.
	 */
	const domLinear_extrusion_surfaceRef getLinear_extrusion_surface() const { return elemLinear_extrusion_surface; }
	/**
	 * Gets the revolution_surface element.
	 * @return a daeSmartRef to the revolution_surface element.
	 */
	const domRevolution_surfaceRef getRevolution_surface() const { return elemRevolution_surface; }
	/**
	 * Gets the tapered_cylinder element.
	 * @return a daeSmartRef to the tapered_cylinder element.
	 */
	const domTapered_cylinderRef getTapered_cylinder() const { return elemTapered_cylinder; }
	/**
	 * Gets the spline element.
	 * @return a daeSmartRef to the spline element.
	 */
	const domSplineRef getSpline() const { return elemSpline; }
	/**
	 * Gets the rotate element array.
	 * @return Returns a reference to the array of rotate elements.
	 */
	domRotate_Array &getRotate_array() { return elemRotate_array; }
	/**
	 * Gets the rotate element array.
	 * @return Returns a constant reference to the array of rotate elements.
	 */
	const domRotate_Array &getRotate_array() const { return elemRotate_array; }
	/**
	 * Gets the translate element array.
	 * @return Returns a reference to the array of translate elements.
	 */
	domTranslate_Array &getTranslate_array() { return elemTranslate_array; }
	/**
	 * Gets the translate element array.
	 * @return Returns a constant reference to the array of translate elements.
	 */
	const domTranslate_Array &getTranslate_array() const { return elemTranslate_array; }
	/**
	 * Gets the _contents array.
	 * @return Returns a reference to the _contents element array.
	 */
	daeElementRefArray &getContents() { return _contents; }
	/**
	 * Gets the _contents array.
	 * @return Returns a constant reference to the _contents element array.
	 */
	const daeElementRefArray &getContents() const { return _contents; }

protected:
	/**
	 * Constructor
	 */
	domSurfaceType_complexType() : attrSid(), attrName(), elemCylinder(), elemPlane(), elemSphere(), elemCylindrical(), elemTorus(), elemLinear_extrusion_surface(), elemRevolution_surface(), elemTapered_cylinder(), elemSpline(), elemRotate_array(), elemTranslate_array() {}
	/**
	 * Destructor
	 */
	virtual ~domSurfaceType_complexType() { daeElement::deleteCMDataArray(_CMData); }
	/**
	 * Copy Constructor
	 */
	domSurfaceType_complexType( const domSurfaceType_complexType &cpy ) { (void)cpy; }
	/**
	 * Overloaded assignment operator
	 */
	virtual domSurfaceType_complexType &operator=( const domSurfaceType_complexType &cpy ) { (void)cpy; return *this; }
};

/**
 * An element of type domSurfaceType_complexType.
 */
class domSurfaceType : public daeElement, public domSurfaceType_complexType
{
public:
	COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::SURFACETYPE; }

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
	 * Gets the name attribute.
	 * @return Returns a xsNCName of the name attribute.
	 */
	xsNCName getName() const { return attrName; }
	/**
	 * Sets the name attribute.
	 * @param atName The new value for the name attribute.
	 */
	void setName( xsNCName atName ) { *(daeStringRef*)&attrName = atName; _validAttributeArray[1] = true; }

protected:
	/**
	 * Constructor
	 */
	domSurfaceType() {}
	/**
	 * Destructor
	 */
	virtual ~domSurfaceType() {}
	/**
	 * Copy Constructor
	 */
	domSurfaceType( const domSurfaceType &cpy ) : daeElement(), domSurfaceType_complexType() { (void)cpy; }
	/**
	 * Overloaded assignment operator
	 */
	virtual domSurfaceType &operator=( const domSurfaceType &cpy ) { (void)cpy; return *this; }

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
