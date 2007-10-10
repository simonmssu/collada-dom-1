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
#include <dom/domRevolution_surface.h>
#include <dae/daeMetaCMPolicy.h>
#include <dae/daeMetaSequence.h>
#include <dae/daeMetaChoice.h>
#include <dae/daeMetaGroup.h>
#include <dae/daeMetaAny.h>
#include <dae/daeMetaElementAttribute.h>

daeElementRef
domRevolution_surface::create(daeInt)
{
	domRevolution_surfaceRef ref = new domRevolution_surface;
	return ref;
}


daeMetaElement *
domRevolution_surface::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "revolution_surface" );
	_Meta->registerClass(domRevolution_surface::create, &_Meta);

	daeMetaCMPolicy *cm = NULL;
	daeMetaElementAttribute *mea = NULL;
	cm = new daeMetaSequence( _Meta, cm, 0, 1, 1 );

	mea = new daeMetaElementAttribute( _Meta, cm, 0, 1, 1 );
	mea->setName( "curve" );
	mea->setOffset( daeOffsetOf(domRevolution_surface,elemCurve) );
	mea->setElementType( domCurveType::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementAttribute( _Meta, cm, 1, 1, 1 );
	mea->setName( "origin" );
	mea->setOffset( daeOffsetOf(domRevolution_surface,elemOrigin) );
	mea->setElementType( domRevolution_surface::domOrigin::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementAttribute( _Meta, cm, 2, 1, 1 );
	mea->setName( "axis" );
	mea->setOffset( daeOffsetOf(domRevolution_surface,elemAxis) );
	mea->setElementType( domRevolution_surface::domAxis::registerElement() );
	cm->appendChild( mea );
	
	cm->setMaxOrdinal( 2 );
	_Meta->setCMRoot( cm );	
	
	
	_Meta->setElementSize(sizeof(domRevolution_surface));
	_Meta->validate();

	return _Meta;
}

daeElementRef
domRevolution_surface::domOrigin::create(daeInt)
{
	domRevolution_surface::domOriginRef ref = new domRevolution_surface::domOrigin;
	return ref;
}


daeMetaElement *
domRevolution_surface::domOrigin::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "origin" );
	_Meta->registerClass(domRevolution_surface::domOrigin::create, &_Meta);

	_Meta->setIsInnerClass( true );
	//	Add attribute: _value
 	{
		daeMetaAttribute *ma = new daeMetaArrayAttribute;
		ma->setName( "_value" );
		ma->setType( daeAtomicType::get("Float3"));
		ma->setOffset( daeOffsetOf( domRevolution_surface::domOrigin , _value ));
		ma->setContainer( _Meta );
		_Meta->appendAttribute(ma);
	}
	
	
	_Meta->setElementSize(sizeof(domRevolution_surface::domOrigin));
	_Meta->validate();

	return _Meta;
}

daeElementRef
domRevolution_surface::domAxis::create(daeInt)
{
	domRevolution_surface::domAxisRef ref = new domRevolution_surface::domAxis;
	return ref;
}


daeMetaElement *
domRevolution_surface::domAxis::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "axis" );
	_Meta->registerClass(domRevolution_surface::domAxis::create, &_Meta);

	_Meta->setIsInnerClass( true );
	//	Add attribute: _value
 	{
		daeMetaAttribute *ma = new daeMetaArrayAttribute;
		ma->setName( "_value" );
		ma->setType( daeAtomicType::get("Float3"));
		ma->setOffset( daeOffsetOf( domRevolution_surface::domAxis , _value ));
		ma->setContainer( _Meta );
		_Meta->appendAttribute(ma);
	}
	
	
	_Meta->setElementSize(sizeof(domRevolution_surface::domAxis));
	_Meta->validate();

	return _Meta;
}


daeMetaElement * domRevolution_surface::_Meta = NULL;
daeMetaElement * domRevolution_surface::domOrigin::_Meta = NULL;
daeMetaElement * domRevolution_surface::domAxis::_Meta = NULL;


