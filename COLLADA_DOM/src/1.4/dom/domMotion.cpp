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
#include <dom/domMotion.h>
#include <dae/daeMetaCMPolicy.h>
#include <dae/daeMetaSequence.h>
#include <dae/daeMetaChoice.h>
#include <dae/daeMetaGroup.h>
#include <dae/daeMetaAny.h>
#include <dae/daeMetaElementAttribute.h>

daeElementRef
domMotion::create(daeInt)
{
	domMotionRef ref = new domMotion;
	return ref;
}


daeMetaElement *
domMotion::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "motion" );
	_Meta->registerClass(domMotion::create, &_Meta);

	daeMetaCMPolicy *cm = NULL;
	daeMetaElementAttribute *mea = NULL;
	cm = new daeMetaSequence( _Meta, cm, 0, 1, 1 );

	mea = new daeMetaElementAttribute( _Meta, cm, 0, 1, 1 );
	mea->setName( "instance_articulated_system" );
	mea->setOffset( daeOffsetOf(domMotion,elemInstance_articulated_system) );
	mea->setElementType( domInstance_articulated_system::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementArrayAttribute( _Meta, cm, 1, 1, -1 );
	mea->setName( "source" );
	mea->setOffset( daeOffsetOf(domMotion,elemSource_array) );
	mea->setElementType( domSource::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementAttribute( _Meta, cm, 2, 1, 1 );
	mea->setName( "axis_infos" );
	mea->setOffset( daeOffsetOf(domMotion,elemAxis_infos) );
	mea->setElementType( domMotion::domAxis_infos::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementAttribute( _Meta, cm, 3, 1, 1 );
	mea->setName( "effector_info" );
	mea->setOffset( daeOffsetOf(domMotion,elemEffector_info) );
	mea->setElementType( domMotion::domEffector_info::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementArrayAttribute( _Meta, cm, 4, 0, -1 );
	mea->setName( "extra" );
	mea->setOffset( daeOffsetOf(domMotion,elemExtra_array) );
	mea->setElementType( domExtra::registerElement() );
	cm->appendChild( mea );
	
	cm->setMaxOrdinal( 4 );
	_Meta->setCMRoot( cm );	
	
	
	_Meta->setElementSize(sizeof(domMotion));
	_Meta->validate();

	return _Meta;
}

daeElementRef
domMotion::domAxis_infos::create(daeInt)
{
	domMotion::domAxis_infosRef ref = new domMotion::domAxis_infos;
	return ref;
}


daeMetaElement *
domMotion::domAxis_infos::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "axis_infos" );
	_Meta->registerClass(domMotion::domAxis_infos::create, &_Meta);

	_Meta->setIsInnerClass( true );
	daeMetaCMPolicy *cm = NULL;
	daeMetaElementAttribute *mea = NULL;
	cm = new daeMetaSequence( _Meta, cm, 0, 1, 1 );

	mea = new daeMetaElementArrayAttribute( _Meta, cm, 0, 1, -1 );
	mea->setName( "input" );
	mea->setOffset( daeOffsetOf(domMotion::domAxis_infos,elemInput_array) );
	mea->setElementType( domInputLocal::registerElement() );
	cm->appendChild( mea );
	
	cm->setMaxOrdinal( 0 );
	_Meta->setCMRoot( cm );	
	
	
	_Meta->setElementSize(sizeof(domMotion::domAxis_infos));
	_Meta->validate();

	return _Meta;
}

daeElementRef
domMotion::domEffector_info::create(daeInt)
{
	domMotion::domEffector_infoRef ref = new domMotion::domEffector_info;
	return ref;
}


daeMetaElement *
domMotion::domEffector_info::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "effector_info" );
	_Meta->registerClass(domMotion::domEffector_info::create, &_Meta);

	_Meta->setIsInnerClass( true );
	daeMetaCMPolicy *cm = NULL;
	daeMetaElementAttribute *mea = NULL;
	cm = new daeMetaSequence( _Meta, cm, 0, 1, 1 );

	mea = new daeMetaElementAttribute( _Meta, cm, 0, 0, 1 );
	mea->setName( "speed" );
	mea->setOffset( daeOffsetOf(domMotion::domEffector_info,elemSpeed) );
	mea->setElementType( domMotion::domEffector_info::domSpeed::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementAttribute( _Meta, cm, 1, 0, 1 );
	mea->setName( "acceleration" );
	mea->setOffset( daeOffsetOf(domMotion::domEffector_info,elemAcceleration) );
	mea->setElementType( domMotion::domEffector_info::domAcceleration::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementAttribute( _Meta, cm, 2, 0, 1 );
	mea->setName( "deceleration" );
	mea->setOffset( daeOffsetOf(domMotion::domEffector_info,elemDeceleration) );
	mea->setElementType( domMotion::domEffector_info::domDeceleration::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementAttribute( _Meta, cm, 3, 0, 1 );
	mea->setName( "jerk" );
	mea->setOffset( daeOffsetOf(domMotion::domEffector_info,elemJerk) );
	mea->setElementType( domMotion::domEffector_info::domJerk::registerElement() );
	cm->appendChild( mea );
	
	cm->setMaxOrdinal( 3 );
	_Meta->setCMRoot( cm );	
	
	
	_Meta->setElementSize(sizeof(domMotion::domEffector_info));
	_Meta->validate();

	return _Meta;
}

daeElementRef
domMotion::domEffector_info::domSpeed::create(daeInt)
{
	domMotion::domEffector_info::domSpeedRef ref = new domMotion::domEffector_info::domSpeed;
	return ref;
}


daeMetaElement *
domMotion::domEffector_info::domSpeed::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "speed" );
	_Meta->registerClass(domMotion::domEffector_info::domSpeed::create, &_Meta);

	_Meta->setIsInnerClass( true );
	//	Add attribute: _value
 	{
		daeMetaAttribute *ma = new daeMetaArrayAttribute;
		ma->setName( "_value" );
		ma->setType( daeAtomicType::get("DynamicLimitType"));
		ma->setOffset( daeOffsetOf( domMotion::domEffector_info::domSpeed , _value ));
		ma->setContainer( _Meta );
		_Meta->appendAttribute(ma);
	}
	
	
	_Meta->setElementSize(sizeof(domMotion::domEffector_info::domSpeed));
	_Meta->validate();

	return _Meta;
}

daeElementRef
domMotion::domEffector_info::domAcceleration::create(daeInt)
{
	domMotion::domEffector_info::domAccelerationRef ref = new domMotion::domEffector_info::domAcceleration;
	return ref;
}


daeMetaElement *
domMotion::domEffector_info::domAcceleration::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "acceleration" );
	_Meta->registerClass(domMotion::domEffector_info::domAcceleration::create, &_Meta);

	_Meta->setIsInnerClass( true );
	//	Add attribute: _value
 	{
		daeMetaAttribute *ma = new daeMetaArrayAttribute;
		ma->setName( "_value" );
		ma->setType( daeAtomicType::get("DynamicLimitType"));
		ma->setOffset( daeOffsetOf( domMotion::domEffector_info::domAcceleration , _value ));
		ma->setContainer( _Meta );
		_Meta->appendAttribute(ma);
	}
	
	
	_Meta->setElementSize(sizeof(domMotion::domEffector_info::domAcceleration));
	_Meta->validate();

	return _Meta;
}

daeElementRef
domMotion::domEffector_info::domDeceleration::create(daeInt)
{
	domMotion::domEffector_info::domDecelerationRef ref = new domMotion::domEffector_info::domDeceleration;
	return ref;
}


daeMetaElement *
domMotion::domEffector_info::domDeceleration::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "deceleration" );
	_Meta->registerClass(domMotion::domEffector_info::domDeceleration::create, &_Meta);

	_Meta->setIsInnerClass( true );
	//	Add attribute: _value
 	{
		daeMetaAttribute *ma = new daeMetaArrayAttribute;
		ma->setName( "_value" );
		ma->setType( daeAtomicType::get("DynamicLimitType"));
		ma->setOffset( daeOffsetOf( domMotion::domEffector_info::domDeceleration , _value ));
		ma->setContainer( _Meta );
		_Meta->appendAttribute(ma);
	}
	
	
	_Meta->setElementSize(sizeof(domMotion::domEffector_info::domDeceleration));
	_Meta->validate();

	return _Meta;
}

daeElementRef
domMotion::domEffector_info::domJerk::create(daeInt)
{
	domMotion::domEffector_info::domJerkRef ref = new domMotion::domEffector_info::domJerk;
	return ref;
}


daeMetaElement *
domMotion::domEffector_info::domJerk::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "jerk" );
	_Meta->registerClass(domMotion::domEffector_info::domJerk::create, &_Meta);

	_Meta->setIsInnerClass( true );
	//	Add attribute: _value
 	{
		daeMetaAttribute *ma = new daeMetaArrayAttribute;
		ma->setName( "_value" );
		ma->setType( daeAtomicType::get("DynamicLimitType"));
		ma->setOffset( daeOffsetOf( domMotion::domEffector_info::domJerk , _value ));
		ma->setContainer( _Meta );
		_Meta->appendAttribute(ma);
	}
	
	
	_Meta->setElementSize(sizeof(domMotion::domEffector_info::domJerk));
	_Meta->validate();

	return _Meta;
}


daeMetaElement * domMotion::_Meta = NULL;
daeMetaElement * domMotion::domAxis_infos::_Meta = NULL;
daeMetaElement * domMotion::domEffector_info::_Meta = NULL;
daeMetaElement * domMotion::domEffector_info::domSpeed::_Meta = NULL;
daeMetaElement * domMotion::domEffector_info::domAcceleration::_Meta = NULL;
daeMetaElement * domMotion::domEffector_info::domDeceleration::_Meta = NULL;
daeMetaElement * domMotion::domEffector_info::domJerk::_Meta = NULL;


