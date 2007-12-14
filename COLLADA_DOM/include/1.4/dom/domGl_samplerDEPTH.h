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

#ifndef __domGl_samplerDEPTH_h__
#define __domGl_samplerDEPTH_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

#include <dom/domFx_samplerDEPTH_common.h>
class DAE;

/**
 * A depth texture sampler for the GLSL profile.
 */
class domGl_samplerDEPTH_complexType  : public domFx_samplerDEPTH_common_complexType
{

protected:
	/**
	 * Constructor
	 */
	domGl_samplerDEPTH_complexType(DAE& dae) : domFx_samplerDEPTH_common_complexType(dae) {}
	/**
	 * Destructor
	 */
	virtual ~domGl_samplerDEPTH_complexType() {}
	/**
	 * Overloaded assignment operator
	 */
	virtual domGl_samplerDEPTH_complexType &operator=( const domGl_samplerDEPTH_complexType &cpy ) { (void)cpy; return *this; }
};

/**
 * An element of type domGl_samplerDEPTH_complexType.
 */
class domGl_samplerDEPTH : public daeElement, public domGl_samplerDEPTH_complexType
{
public:
	virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::GL_SAMPLERDEPTH; }
	static daeInt typeIDStatic() { return 102; }
	virtual daeInt typeID() const { return typeIDStatic(); }
protected:
	/**
	 * Constructor
	 */
	domGl_samplerDEPTH(DAE& dae) : daeElement(dae), domGl_samplerDEPTH_complexType(dae) {}
	/**
	 * Destructor
	 */
	virtual ~domGl_samplerDEPTH() {}
	/**
	 * Overloaded assignment operator
	 */
	virtual domGl_samplerDEPTH &operator=( const domGl_samplerDEPTH &cpy ) { (void)cpy; return *this; }

public: // STATIC METHODS
	/**
	 * Creates an instance of this class and returns a daeElementRef referencing it.
	 * @return a daeElementRef referencing an instance of this object.
	 */
	static DLLSPEC daeElementRef create(DAE& dae);
	/**
	 * Creates a daeMetaElement object that describes this element in the meta object reflection framework.
	 * If a daeMetaElement already exists it will return that instead of creating a new one. 
	 * @return A daeMetaElement describing this COLLADA element.
	 */
	static DLLSPEC daeMetaElement* registerElement(DAE& dae);
};


#endif
