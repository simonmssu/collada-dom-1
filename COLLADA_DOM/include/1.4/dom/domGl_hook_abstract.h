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

#ifndef __domGl_hook_abstract_h__
#define __domGl_hook_abstract_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

class DAE;

class domGl_hook_abstract : public daeElement
{
public:
	virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::GL_HOOK_ABSTRACT; }
	static COLLADA_TYPE::TypeEnum getTypeStatic() const { return COLLADA_TYPE::GL_HOOK_ABSTRACT; }

protected:
	/**
	 * Constructor
	 */
	domGl_hook_abstract(DAE& dae) {}
	/**
	 * Destructor
	 */
	virtual ~domGl_hook_abstract() {}
	/**
	 * Copy Constructor
	 */
	domGl_hook_abstract( const domGl_hook_abstract &cpy ) : daeElement() { (void)cpy; }
	/**
	 * Overloaded assignment operator
	 */
	virtual domGl_hook_abstract &operator=( const domGl_hook_abstract &cpy ) { (void)cpy; return *this; }

public: // STATIC METHODS
	/**
	 * Creates an instance of this class and returns a daeElementRef referencing it.
	 * @return a daeElementRef referencing an instance of this object.
	 */
	static DLLSPEC daeElementRef create();
	/**
	 * Creates a daeMetaElement object that describes this element in the meta object reflection framework.
	 * If a daeMetaElement already exists it will return that instead of creating a new one. 
	 * @return A daeMetaElement describing this COLLADA element.
	 */
	static DLLSPEC daeMetaElement* registerElement(DAE& dae);
};


#endif
