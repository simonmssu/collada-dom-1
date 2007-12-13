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
#include <dom/domKinematics.h>
#include <dae/daeMetaCMPolicy.h>
#include <dae/daeMetaSequence.h>
#include <dae/daeMetaChoice.h>
#include <dae/daeMetaGroup.h>
#include <dae/daeMetaAny.h>
#include <dae/daeMetaElementAttribute.h>

daeElementRef
domKinematics::create(daeInt)
{
	domKinematicsRef ref = new domKinematics;
	ref->attrSource.setContainer( (domKinematics*)ref );
	return ref;
}


daeMetaElement *
domKinematics::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "kinematics" );
	_Meta->registerClass(domKinematics::create, &_Meta);

	daeMetaCMPolicy *cm = NULL;
	daeMetaElementAttribute *mea = NULL;
	cm = new daeMetaSequence( _Meta, cm, 0, 1, 1 );

	mea = new daeMetaElementArrayAttribute( _Meta, cm, 0, 0, -1 );
	mea->setName( "axis_info" );
	mea->setOffset( daeOffsetOf(domKinematics,elemAxis_info_array) );
	mea->setElementType( domKinematics::domAxis_info::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementAttribute( _Meta, cm, 1, 1, 1 );
	mea->setName( "kinematics_frame" );
	mea->setOffset( daeOffsetOf(domKinematics,elemKinematics_frame) );
	mea->setElementType( domKinematics::domKinematics_frame::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementArrayAttribute( _Meta, cm, 2, 0, -1 );
	mea->setName( "extra" );
	mea->setOffset( daeOffsetOf(domKinematics,elemExtra_array) );
	mea->setElementType( domExtra::registerElement() );
	cm->appendChild( mea );
	
	cm->setMaxOrdinal( 2 );
	_Meta->setCMRoot( cm );	

	//	Add attribute: source
 	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "source" );
		ma->setType( daeAtomicType::get("xsAnyURI"));
		ma->setOffset( daeOffsetOf( domKinematics , attrSource ));
		ma->setContainer( _Meta );
		ma->setIsRequired( true );
	
		_Meta->appendAttribute(ma);
	}
	
	
	_Meta->setElementSize(sizeof(domKinematics));
	_Meta->validate();

	return _Meta;
}

daeElementRef
domKinematics::domAxis_info::create(daeInt)
{
	domKinematics::domAxis_infoRef ref = new domKinematics::domAxis_info;
	return ref;
}


daeMetaElement *
domKinematics::domAxis_info::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "axis_info" );
	_Meta->registerClass(domKinematics::domAxis_info::create, &_Meta);

	_Meta->setIsInnerClass( true );
	daeMetaCMPolicy *cm = NULL;
	daeMetaElementAttribute *mea = NULL;
	cm = new daeMetaSequence( _Meta, cm, 0, 1, 1 );

	mea = new daeMetaElementAttribute( _Meta, cm, 0, 0, 1 );
	mea->setName( "limits" );
	mea->setOffset( daeOffsetOf(domKinematics::domAxis_info,elemLimits) );
	mea->setElementType( domLimitsType::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementAttribute( _Meta, cm, 1, 0, 1 );
	mea->setName( "formula" );
	mea->setOffset( daeOffsetOf(domKinematics::domAxis_info,elemFormula) );
	mea->setElementType( domFormula::registerElement() );
	cm->appendChild( mea );
	
	cm->setMaxOrdinal( 1 );
	_Meta->setCMRoot( cm );	

	//	Add attribute: sid
 	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "sid" );
		ma->setType( daeAtomicType::get("xsNCName"));
		ma->setOffset( daeOffsetOf( domKinematics::domAxis_info , attrSid ));
		ma->setContainer( _Meta );
	
		_Meta->appendAttribute(ma);
	}

	//	Add attribute: name
 	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "name" );
		ma->setType( daeAtomicType::get("xsNCName"));
		ma->setOffset( daeOffsetOf( domKinematics::domAxis_info , attrName ));
		ma->setContainer( _Meta );
	
		_Meta->appendAttribute(ma);
	}

	//	Add attribute: target
 	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "target" );
		ma->setType( daeAtomicType::get("xsToken"));
		ma->setOffset( daeOffsetOf( domKinematics::domAxis_info , attrTarget ));
		ma->setContainer( _Meta );
		ma->setIsRequired( true );
	
		_Meta->appendAttribute(ma);
	}

	//	Add attribute: locked
 	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "locked" );
		ma->setType( daeAtomicType::get("Bool"));
		ma->setOffset( daeOffsetOf( domKinematics::domAxis_info , attrLocked ));
		ma->setContainer( _Meta );
	
		_Meta->appendAttribute(ma);
	}

	//	Add attribute: active
 	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "active" );
		ma->setType( daeAtomicType::get("Bool"));
		ma->setOffset( daeOffsetOf( domKinematics::domAxis_info , attrActive ));
		ma->setContainer( _Meta );
	
		_Meta->appendAttribute(ma);
	}

	//	Add attribute: index
 	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "index" );
		ma->setType( daeAtomicType::get("Uint"));
		ma->setOffset( daeOffsetOf( domKinematics::domAxis_info , attrIndex ));
		ma->setContainer( _Meta );
		ma->setIsRequired( true );
	
		_Meta->appendAttribute(ma);
	}
	
	
	_Meta->setElementSize(sizeof(domKinematics::domAxis_info));
	_Meta->validate();

	return _Meta;
}

daeElementRef
domKinematics::domKinematics_frame::create(daeInt)
{
	domKinematics::domKinematics_frameRef ref = new domKinematics::domKinematics_frame;
	return ref;
}


daeMetaElement *
domKinematics::domKinematics_frame::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "kinematics_frame" );
	_Meta->registerClass(domKinematics::domKinematics_frame::create, &_Meta);

	_Meta->setIsInnerClass( true );
	daeMetaCMPolicy *cm = NULL;
	daeMetaElementAttribute *mea = NULL;
	cm = new daeMetaSequence( _Meta, cm, 0, 1, 1 );

	mea = new daeMetaElementAttribute( _Meta, cm, 0, 1, 1 );
	mea->setName( "origin" );
	mea->setOffset( daeOffsetOf(domKinematics::domKinematics_frame,elemOrigin) );
	mea->setElementType( domKinematics::domKinematics_frame::domOrigin::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementAttribute( _Meta, cm, 1, 1, 1 );
	mea->setName( "tip" );
	mea->setOffset( daeOffsetOf(domKinematics::domKinematics_frame,elemTip) );
	mea->setElementType( domKinematics::domKinematics_frame::domTip::registerElement() );
	cm->appendChild( mea );
	
	cm->setMaxOrdinal( 1 );
	_Meta->setCMRoot( cm );	
	
	
	_Meta->setElementSize(sizeof(domKinematics::domKinematics_frame));
	_Meta->validate();

	return _Meta;
}

daeElementRef
domKinematics::domKinematics_frame::domOrigin::create(daeInt)
{
	domKinematics::domKinematics_frame::domOriginRef ref = new domKinematics::domKinematics_frame::domOrigin;
	return ref;
}


daeMetaElement *
domKinematics::domKinematics_frame::domOrigin::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "origin" );
	_Meta->registerClass(domKinematics::domKinematics_frame::domOrigin::create, &_Meta);

	_Meta->setIsInnerClass( true );
	daeMetaCMPolicy *cm = NULL;
	daeMetaElementAttribute *mea = NULL;
	cm = new daeMetaSequence( _Meta, cm, 0, 1, 1 );

	mea = new daeMetaElementArrayAttribute( _Meta, cm, 0, 0, -1 );
	mea->setName( "rotate" );
	mea->setOffset( daeOffsetOf(domKinematics::domKinematics_frame::domOrigin,elemRotate_array) );
	mea->setElementType( domRotate::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementAttribute( _Meta, cm, 1, 0, 1 );
	mea->setName( "translate" );
	mea->setOffset( daeOffsetOf(domKinematics::domKinematics_frame::domOrigin,elemTranslate) );
	mea->setElementType( domTranslate::registerElement() );
	cm->appendChild( mea );
	
	cm->setMaxOrdinal( 1 );
	_Meta->setCMRoot( cm );	

	//	Add attribute: ref
 	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "ref" );
		ma->setType( daeAtomicType::get("xsToken"));
		ma->setOffset( daeOffsetOf( domKinematics::domKinematics_frame::domOrigin , attrRef ));
		ma->setContainer( _Meta );
	
		_Meta->appendAttribute(ma);
	}
	
	
	_Meta->setElementSize(sizeof(domKinematics::domKinematics_frame::domOrigin));
	_Meta->validate();

	return _Meta;
}

daeElementRef
domKinematics::domKinematics_frame::domTip::create(daeInt)
{
	domKinematics::domKinematics_frame::domTipRef ref = new domKinematics::domKinematics_frame::domTip;
	return ref;
}


daeMetaElement *
domKinematics::domKinematics_frame::domTip::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "tip" );
	_Meta->registerClass(domKinematics::domKinematics_frame::domTip::create, &_Meta);

	_Meta->setIsInnerClass( true );
	daeMetaCMPolicy *cm = NULL;
	daeMetaElementAttribute *mea = NULL;
	cm = new daeMetaSequence( _Meta, cm, 0, 1, 1 );

	mea = new daeMetaElementArrayAttribute( _Meta, cm, 0, 0, -1 );
	mea->setName( "rotate" );
	mea->setOffset( daeOffsetOf(domKinematics::domKinematics_frame::domTip,elemRotate_array) );
	mea->setElementType( domRotate::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementAttribute( _Meta, cm, 1, 0, 1 );
	mea->setName( "translate" );
	mea->setOffset( daeOffsetOf(domKinematics::domKinematics_frame::domTip,elemTranslate) );
	mea->setElementType( domTranslate::registerElement() );
	cm->appendChild( mea );
	
	cm->setMaxOrdinal( 1 );
	_Meta->setCMRoot( cm );	

	//	Add attribute: ref
 	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "ref" );
		ma->setType( daeAtomicType::get("Token"));
		ma->setOffset( daeOffsetOf( domKinematics::domKinematics_frame::domTip , attrRef ));
		ma->setContainer( _Meta );
	
		_Meta->appendAttribute(ma);
	}
	
	
	_Meta->setElementSize(sizeof(domKinematics::domKinematics_frame::domTip));
	_Meta->validate();

	return _Meta;
}


daeMetaElement * domKinematics::_Meta = NULL;
daeMetaElement * domKinematics::domAxis_info::_Meta = NULL;
daeMetaElement * domKinematics::domKinematics_frame::_Meta = NULL;
daeMetaElement * domKinematics::domKinematics_frame::domOrigin::_Meta = NULL;
daeMetaElement * domKinematics::domKinematics_frame::domTip::_Meta = NULL;


