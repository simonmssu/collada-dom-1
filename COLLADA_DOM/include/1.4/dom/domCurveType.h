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
#ifndef __domCurveType_h__
#define __domCurveType_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

#include <dom/domLine.h>
#include <dom/domCircle.h>
#include <dom/domEllipse.h>
#include <dom/domParabola.h>
#include <dom/domHyperbola.h>
#include <dom/domSpline.h>
#include <dom/domRotate.h>
#include <dom/domTranslate.h>

/**
 * A curveType defines the attributes of a curve element.     With rotate
 * and translate the surface can be positioned     to its right location.
 */
class domCurveType_complexType 
{
protected:  // Attributes
/**
 * The sid of a curve.
 */
	xsNCName attrSid;
/**
 *       The name of a curve.     
 */
	xsNCName attrName;

protected:  // Elements
	domLineRef elemLine;
	domCircleRef elemCircle;
	domEllipseRef elemEllipse;
	domParabolaRef elemParabola;
	domHyperbolaRef elemHyperbola;
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
	 * Gets the line element.
	 * @return a daeSmartRef to the line element.
	 */
	const domLineRef getLine() const { return elemLine; }
	/**
	 * Gets the circle element.
	 * @return a daeSmartRef to the circle element.
	 */
	const domCircleRef getCircle() const { return elemCircle; }
	/**
	 * Gets the ellipse element.
	 * @return a daeSmartRef to the ellipse element.
	 */
	const domEllipseRef getEllipse() const { return elemEllipse; }
	/**
	 * Gets the parabola element.
	 * @return a daeSmartRef to the parabola element.
	 */
	const domParabolaRef getParabola() const { return elemParabola; }
	/**
	 * Gets the hyperbola element.
	 * @return a daeSmartRef to the hyperbola element.
	 */
	const domHyperbolaRef getHyperbola() const { return elemHyperbola; }
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
	domCurveType_complexType() : attrSid(), attrName(), elemLine(), elemCircle(), elemEllipse(), elemParabola(), elemHyperbola(), elemSpline(), elemRotate_array(), elemTranslate_array() {}
	/**
	 * Destructor
	 */
	virtual ~domCurveType_complexType() { daeElement::deleteCMDataArray(_CMData); }
	/**
	 * Copy Constructor
	 */
	domCurveType_complexType( const domCurveType_complexType &cpy ) { (void)cpy; }
	/**
	 * Overloaded assignment operator
	 */
	virtual domCurveType_complexType &operator=( const domCurveType_complexType &cpy ) { (void)cpy; return *this; }
};

/**
 * An element of type domCurveType_complexType.
 */
class domCurveType : public daeElement, public domCurveType_complexType
{
public:
	COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::CURVETYPE; }

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
	domCurveType() {}
	/**
	 * Destructor
	 */
	virtual ~domCurveType() {}
	/**
	 * Copy Constructor
	 */
	domCurveType( const domCurveType &cpy ) : daeElement(), domCurveType_complexType() { (void)cpy; }
	/**
	 * Overloaded assignment operator
	 */
	virtual domCurveType &operator=( const domCurveType &cpy ) { (void)cpy; return *this; }

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
