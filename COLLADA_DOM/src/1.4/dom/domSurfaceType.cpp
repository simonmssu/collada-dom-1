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
#include <dom/domSurfaceType.h>
#include <dae/daeMetaCMPolicy.h>
#include <dae/daeMetaSequence.h>
#include <dae/daeMetaChoice.h>
#include <dae/daeMetaGroup.h>
#include <dae/daeMetaAny.h>
#include <dae/daeMetaElementAttribute.h>

daeElementRef
domSurfaceType::create(daeInt)
{
	domSurfaceTypeRef ref = new domSurfaceType;
	return ref;
}


daeMetaElement *
domSurfaceType::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "surfaceType" );
	_Meta->registerClass(domSurfaceType::create, &_Meta);

	daeMetaCMPolicy *cm = NULL;
	daeMetaElementAttribute *mea = NULL;
	cm = new daeMetaSequence( _Meta, cm, 0, 1, 1 );

	cm = new daeMetaChoice( _Meta, cm, 0, 0, 1, 1 );

	mea = new daeMetaElementAttribute( _Meta, cm, 0, 1, 1 );
	mea->setName( "cylinder" );
	mea->setOffset( daeOffsetOf(domSurfaceType,elemCylinder) );
	mea->setElementType( domCylinder::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementAttribute( _Meta, cm, 0, 1, 1 );
	mea->setName( "plane" );
	mea->setOffset( daeOffsetOf(domSurfaceType,elemPlane) );
	mea->setElementType( domPlane::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementAttribute( _Meta, cm, 0, 1, 1 );
	mea->setName( "sphere" );
	mea->setOffset( daeOffsetOf(domSurfaceType,elemSphere) );
	mea->setElementType( domSphere::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementAttribute( _Meta, cm, 0, 1, 1 );
	mea->setName( "cylindrical" );
	mea->setOffset( daeOffsetOf(domSurfaceType,elemCylindrical) );
	mea->setElementType( domCylindrical::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementAttribute( _Meta, cm, 0, 1, 1 );
	mea->setName( "torus" );
	mea->setOffset( daeOffsetOf(domSurfaceType,elemTorus) );
	mea->setElementType( domTorus::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementAttribute( _Meta, cm, 0, 1, 1 );
	mea->setName( "linear_extrusion_surface" );
	mea->setOffset( daeOffsetOf(domSurfaceType,elemLinear_extrusion_surface) );
	mea->setElementType( domLinear_extrusion_surface::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementAttribute( _Meta, cm, 0, 1, 1 );
	mea->setName( "revolution_surface" );
	mea->setOffset( daeOffsetOf(domSurfaceType,elemRevolution_surface) );
	mea->setElementType( domRevolution_surface::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementAttribute( _Meta, cm, 0, 1, 1 );
	mea->setName( "tapered_cylinder" );
	mea->setOffset( daeOffsetOf(domSurfaceType,elemTapered_cylinder) );
	mea->setElementType( domTapered_cylinder::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementAttribute( _Meta, cm, 0, 1, 1 );
	mea->setName( "spline" );
	mea->setOffset( daeOffsetOf(domSurfaceType,elemSpline) );
	mea->setElementType( domSpline::registerElement() );
	cm->appendChild( mea );
	
	cm->setMaxOrdinal( 0 );
	cm->getParent()->appendChild( cm );
	cm = cm->getParent();
	
	mea = new daeMetaElementArrayAttribute( _Meta, cm, 1, 0, -1 );
	mea->setName( "rotate" );
	mea->setOffset( daeOffsetOf(domSurfaceType,elemRotate_array) );
	mea->setElementType( domRotate::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementArrayAttribute( _Meta, cm, 2, 0, -1 );
	mea->setName( "translate" );
	mea->setOffset( daeOffsetOf(domSurfaceType,elemTranslate_array) );
	mea->setElementType( domTranslate::registerElement() );
	cm->appendChild( mea );
	
	cm->setMaxOrdinal( 2 );
	_Meta->setCMRoot( cm );	
	// Ordered list of sub-elements
    _Meta->addContents(daeOffsetOf(domSurfaceType,_contents));
    _Meta->addContentsOrder(daeOffsetOf(domSurfaceType,_contentsOrder));
        
    _Meta->addCMDataArray(daeOffsetOf(domSurfaceType,_CMData), 1);
	//	Add attribute: sid
 	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "sid" );
		ma->setType( daeAtomicType::get("xsNCName"));
		ma->setOffset( daeOffsetOf( domSurfaceType , attrSid ));
		ma->setContainer( _Meta );
		ma->setIsRequired( false );
	
		_Meta->appendAttribute(ma);
	}

	//	Add attribute: name
 	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "name" );
		ma->setType( daeAtomicType::get("xsNCName"));
		ma->setOffset( daeOffsetOf( domSurfaceType , attrName ));
		ma->setContainer( _Meta );
	
		_Meta->appendAttribute(ma);
	}
	
	
	_Meta->setElementSize(sizeof(domSurfaceType));
	_Meta->validate();

	return _Meta;
}


daeMetaElement * domSurfaceType::_Meta = NULL;


