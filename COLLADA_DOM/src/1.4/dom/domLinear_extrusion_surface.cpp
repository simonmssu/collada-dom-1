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

#include <dae/daeDom.h>
#include <dom/domLinear_extrusion_surface.h>
#include <dae/daeMetaCMPolicy.h>
#include <dae/daeMetaSequence.h>
#include <dae/daeMetaChoice.h>
#include <dae/daeMetaGroup.h>
#include <dae/daeMetaAny.h>
#include <dae/daeMetaElementAttribute.h>

daeElementRef
domLinear_extrusion_surface::create(daeInt)
{
	domLinear_extrusion_surfaceRef ref = new domLinear_extrusion_surface;
	return ref;
}


daeMetaElement *
domLinear_extrusion_surface::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "linear_extrusion_surface" );
	_Meta->registerClass(domLinear_extrusion_surface::create, &_Meta);

	daeMetaCMPolicy *cm = NULL;
	daeMetaElementAttribute *mea = NULL;
	cm = new daeMetaSequence( _Meta, cm, 0, 1, 1 );

	mea = new daeMetaElementAttribute( _Meta, cm, 0, 1, 1 );
	mea->setName( "curve" );
	mea->setOffset( daeOffsetOf(domLinear_extrusion_surface,elemCurve) );
	mea->setElementType( domCurveType::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementAttribute( _Meta, cm, 1, 1, 1 );
	mea->setName( "direction" );
	mea->setOffset( daeOffsetOf(domLinear_extrusion_surface,elemDirection) );
	mea->setElementType( domLinear_extrusion_surface::domDirection::registerElement() );
	cm->appendChild( mea );
	
	cm->setMaxOrdinal( 1 );
	_Meta->setCMRoot( cm );	
	
	
	_Meta->setElementSize(sizeof(domLinear_extrusion_surface));
	_Meta->validate();

	return _Meta;
}

daeElementRef
domLinear_extrusion_surface::domDirection::create(daeInt)
{
	domLinear_extrusion_surface::domDirectionRef ref = new domLinear_extrusion_surface::domDirection;
	return ref;
}


daeMetaElement *
domLinear_extrusion_surface::domDirection::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "direction" );
	_Meta->registerClass(domLinear_extrusion_surface::domDirection::create, &_Meta);

	_Meta->setIsInnerClass( true );
	//	Add attribute: _value
 	{
		daeMetaAttribute *ma = new daeMetaArrayAttribute;
		ma->setName( "_value" );
		ma->setType( daeAtomicType::get("Float3"));
		ma->setOffset( daeOffsetOf( domLinear_extrusion_surface::domDirection , _value ));
		ma->setContainer( _Meta );
		_Meta->appendAttribute(ma);
	}
	
	
	_Meta->setElementSize(sizeof(domLinear_extrusion_surface::domDirection));
	_Meta->validate();

	return _Meta;
}


daeMetaElement * domLinear_extrusion_surface::_Meta = NULL;
daeMetaElement * domLinear_extrusion_surface::domDirection::_Meta = NULL;


