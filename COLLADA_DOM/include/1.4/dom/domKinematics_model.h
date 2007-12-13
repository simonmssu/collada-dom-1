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
#ifndef __domKinematics_model_h__
#define __domKinematics_model_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

#include <dom/domAsset.h>
#include <dom/domJoint.h>
#include <dom/domInstance_joint.h>
#include <dom/domLink.h>
#include <dom/domAttach_point.h>
#include <dom/domInstance_kinematics_model.h>
#include <dom/domExtra.h>

class domKinematics_model : public daeElement
{
public:
	COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::KINEMATICS_MODEL; }
protected:  // Attributes
	xsID attrId;
	xsNCName attrName;

protected:  // Elements
	domAssetRef elemAsset;
	domJoint_Array elemJoint_array;
	domInstance_joint_Array elemInstance_joint_array;
	domLink_Array elemLink_array;
	domAttach_point_Array elemAttach_point_array;
	domInstance_kinematics_model_Array elemInstance_kinematics_model_array;
	domExtra_Array elemExtra_array;
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
	 * Gets the id attribute.
	 * @return Returns a xsID of the id attribute.
	 */
	xsID getId() const { return attrId; }
	/**
	 * Sets the id attribute.
	 * @param atId The new value for the id attribute.
	 */
	void setId( xsID atId ) { *(daeStringRef*)&attrId = atId; _validAttributeArray[0] = true; 
		if( _document != NULL ) _document->changeElementID( this, attrId );
	}

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

	/**
	 * Gets the asset element.
	 * @return a daeSmartRef to the asset element.
	 */
	const domAssetRef getAsset() const { return elemAsset; }
	/**
	 * Gets the joint element array.
	 * @return Returns a reference to the array of joint elements.
	 */
	domJoint_Array &getJoint_array() { return elemJoint_array; }
	/**
	 * Gets the joint element array.
	 * @return Returns a constant reference to the array of joint elements.
	 */
	const domJoint_Array &getJoint_array() const { return elemJoint_array; }
	/**
	 * Gets the instance_joint element array.
	 * @return Returns a reference to the array of instance_joint elements.
	 */
	domInstance_joint_Array &getInstance_joint_array() { return elemInstance_joint_array; }
	/**
	 * Gets the instance_joint element array.
	 * @return Returns a constant reference to the array of instance_joint elements.
	 */
	const domInstance_joint_Array &getInstance_joint_array() const { return elemInstance_joint_array; }
	/**
	 * Gets the link element array.
	 * @return Returns a reference to the array of link elements.
	 */
	domLink_Array &getLink_array() { return elemLink_array; }
	/**
	 * Gets the link element array.
	 * @return Returns a constant reference to the array of link elements.
	 */
	const domLink_Array &getLink_array() const { return elemLink_array; }
	/**
	 * Gets the attach_point element array.
	 * @return Returns a reference to the array of attach_point elements.
	 */
	domAttach_point_Array &getAttach_point_array() { return elemAttach_point_array; }
	/**
	 * Gets the attach_point element array.
	 * @return Returns a constant reference to the array of attach_point elements.
	 */
	const domAttach_point_Array &getAttach_point_array() const { return elemAttach_point_array; }
	/**
	 * Gets the instance_kinematics_model element array.
	 * @return Returns a reference to the array of instance_kinematics_model elements.
	 */
	domInstance_kinematics_model_Array &getInstance_kinematics_model_array() { return elemInstance_kinematics_model_array; }
	/**
	 * Gets the instance_kinematics_model element array.
	 * @return Returns a constant reference to the array of instance_kinematics_model elements.
	 */
	const domInstance_kinematics_model_Array &getInstance_kinematics_model_array() const { return elemInstance_kinematics_model_array; }
	/**
	 * Gets the extra element array.
	 * @return Returns a reference to the array of extra elements.
	 */
	domExtra_Array &getExtra_array() { return elemExtra_array; }
	/**
	 * Gets the extra element array.
	 * @return Returns a constant reference to the array of extra elements.
	 */
	const domExtra_Array &getExtra_array() const { return elemExtra_array; }
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
	domKinematics_model() : attrId(), attrName(), elemAsset(), elemJoint_array(), elemInstance_joint_array(), elemLink_array(), elemAttach_point_array(), elemInstance_kinematics_model_array(), elemExtra_array() {}
	/**
	 * Destructor
	 */
	virtual ~domKinematics_model() { daeElement::deleteCMDataArray(_CMData); }
	/**
	 * Copy Constructor
	 */
	domKinematics_model( const domKinematics_model &cpy ) : daeElement() { (void)cpy; }
	/**
	 * Overloaded assignment operator
	 */
	virtual domKinematics_model &operator=( const domKinematics_model &cpy ) { (void)cpy; return *this; }

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
