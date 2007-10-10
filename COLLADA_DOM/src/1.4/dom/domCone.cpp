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
#include <dom/domCone.h>
#include <dae/daeMetaCMPolicy.h>
#include <dae/daeMetaSequence.h>
#include <dae/daeMetaChoice.h>
#include <dae/daeMetaGroup.h>
#include <dae/daeMetaAny.h>
#include <dae/daeMetaElementAttribute.h>

daeElementRef
domCone::create(daeInt)
{
	domConeRef ref = new domCone;
	return ref;
}


daeMetaElement *
domCone::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "cone" );
	_Meta->registerClass(domCone::create, &_Meta);

	daeMetaCMPolicy *cm = NULL;
	daeMetaElementAttribute *mea = NULL;
	cm = new daeMetaSequence( _Meta, cm, 0, 1, 1 );

	mea = new daeMetaElementAttribute( _Meta, cm, 0, 1, 1 );
	mea->setName( "radius" );
	mea->setOffset( daeOffsetOf(domCone,elemRadius) );
	mea->setElementType( domCone::domRadius::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementAttribute( _Meta, cm, 1, 1, 1 );
	mea->setName( "half_apex" );
	mea->setOffset( daeOffsetOf(domCone,elemHalf_apex) );
	mea->setElementType( domCone::domHalf_apex::registerElement() );
	cm->appendChild( mea );
	
	cm->setMaxOrdinal( 1 );
	_Meta->setCMRoot( cm );	
	
	
	_Meta->setElementSize(sizeof(domCone));
	_Meta->validate();

	return _Meta;
}

daeElementRef
domCone::domRadius::create(daeInt)
{
	domCone::domRadiusRef ref = new domCone::domRadius;
	return ref;
}


daeMetaElement *
domCone::domRadius::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "radius" );
	_Meta->registerClass(domCone::domRadius::create, &_Meta);

	_Meta->setIsInnerClass( true );
	//	Add attribute: _value
 	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "_value" );
		ma->setType( daeAtomicType::get("Float"));
		ma->setOffset( daeOffsetOf( domCone::domRadius , _value ));
		ma->setContainer( _Meta );
		_Meta->appendAttribute(ma);
	}
	
	
	_Meta->setElementSize(sizeof(domCone::domRadius));
	_Meta->validate();

	return _Meta;
}

daeElementRef
domCone::domHalf_apex::create(daeInt)
{
	domCone::domHalf_apexRef ref = new domCone::domHalf_apex;
	return ref;
}


daeMetaElement *
domCone::domHalf_apex::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "half_apex" );
	_Meta->registerClass(domCone::domHalf_apex::create, &_Meta);

	_Meta->setIsInnerClass( true );
	//	Add attribute: _value
 	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "_value" );
		ma->setType( daeAtomicType::get("xsFloat"));
		ma->setOffset( daeOffsetOf( domCone::domHalf_apex , _value ));
		ma->setContainer( _Meta );
		_Meta->appendAttribute(ma);
	}
	
	
	_Meta->setElementSize(sizeof(domCone::domHalf_apex));
	_Meta->validate();

	return _Meta;
}


daeMetaElement * domCone::_Meta = NULL;
daeMetaElement * domCone::domRadius::_Meta = NULL;
daeMetaElement * domCone::domHalf_apex::_Meta = NULL;


