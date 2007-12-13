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
#include <dom/domLink.h>
#include <dae/daeMetaCMPolicy.h>
#include <dae/daeMetaSequence.h>
#include <dae/daeMetaChoice.h>
#include <dae/daeMetaGroup.h>
#include <dae/daeMetaAny.h>
#include <dae/daeMetaElementAttribute.h>

daeElementRef
domLink::create(daeInt)
{
	domLinkRef ref = new domLink;
	return ref;
}


daeMetaElement *
domLink::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "link" );
	_Meta->registerClass(domLink::create, &_Meta);

	daeMetaCMPolicy *cm = NULL;
	daeMetaElementAttribute *mea = NULL;
	cm = new daeMetaSequence( _Meta, cm, 0, 1, 1 );

	mea = new daeMetaElementArrayAttribute( _Meta, cm, 0, 0, -1 );
	mea->setName( "attachment_full" );
	mea->setOffset( daeOffsetOf(domLink,elemAttachment_full_array) );
	mea->setElementType( domLink::domAttachment_full::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementArrayAttribute( _Meta, cm, 1, 0, -1 );
	mea->setName( "attachment_start" );
	mea->setOffset( daeOffsetOf(domLink,elemAttachment_start_array) );
	mea->setElementType( domLink::domAttachment_start::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementArrayAttribute( _Meta, cm, 2, 0, -1 );
	mea->setName( "attachment_end" );
	mea->setOffset( daeOffsetOf(domLink,elemAttachment_end_array) );
	mea->setElementType( domLink::domAttachment_end::registerElement() );
	cm->appendChild( mea );
	
	cm->setMaxOrdinal( 2 );
	_Meta->setCMRoot( cm );	

	//	Add attribute: sid
 	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "sid" );
		ma->setType( daeAtomicType::get("xsNCName"));
		ma->setOffset( daeOffsetOf( domLink , attrSid ));
		ma->setContainer( _Meta );
	
		_Meta->appendAttribute(ma);
	}

	//	Add attribute: name
 	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "name" );
		ma->setType( daeAtomicType::get("xsNCName"));
		ma->setOffset( daeOffsetOf( domLink , attrName ));
		ma->setContainer( _Meta );
	
		_Meta->appendAttribute(ma);
	}
	
	
	_Meta->setElementSize(sizeof(domLink));
	_Meta->validate();

	return _Meta;
}

daeElementRef
domLink::domAttachment_full::create(daeInt)
{
	domLink::domAttachment_fullRef ref = new domLink::domAttachment_full;
	return ref;
}


daeMetaElement *
domLink::domAttachment_full::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "attachment_full" );
	_Meta->registerClass(domLink::domAttachment_full::create, &_Meta);

	_Meta->setIsInnerClass( true );
	daeMetaCMPolicy *cm = NULL;
	daeMetaElementAttribute *mea = NULL;
	cm = new daeMetaSequence( _Meta, cm, 0, 1, 1 );

	mea = new daeMetaElementAttribute( _Meta, cm, 0, 0, 1 );
	mea->setName( "translate" );
	mea->setOffset( daeOffsetOf(domLink::domAttachment_full,elemTranslate) );
	mea->setElementType( domTranslate::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementArrayAttribute( _Meta, cm, 1, 0, -1 );
	mea->setName( "rotate" );
	mea->setOffset( daeOffsetOf(domLink::domAttachment_full,elemRotate_array) );
	mea->setElementType( domRotate::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementAttribute( _Meta, cm, 2, 1, 1 );
	mea->setName( "link" );
	mea->setOffset( daeOffsetOf(domLink::domAttachment_full,elemLink) );
	mea->setElementType( domLink::registerElement() );
	cm->appendChild( mea );
	
	cm->setMaxOrdinal( 2 );
	_Meta->setCMRoot( cm );	

	//	Add attribute: joint
 	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "joint" );
		ma->setType( daeAtomicType::get("Token"));
		ma->setOffset( daeOffsetOf( domLink::domAttachment_full , attrJoint ));
		ma->setContainer( _Meta );
	
		_Meta->appendAttribute(ma);
	}
	
	
	_Meta->setElementSize(sizeof(domLink::domAttachment_full));
	_Meta->validate();

	return _Meta;
}

daeElementRef
domLink::domAttachment_start::create(daeInt)
{
	domLink::domAttachment_startRef ref = new domLink::domAttachment_start;
	return ref;
}


daeMetaElement *
domLink::domAttachment_start::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "attachment_start" );
	_Meta->registerClass(domLink::domAttachment_start::create, &_Meta);

	_Meta->setIsInnerClass( true );
	daeMetaCMPolicy *cm = NULL;
	daeMetaElementAttribute *mea = NULL;
	cm = new daeMetaSequence( _Meta, cm, 0, 1, 1 );

	mea = new daeMetaElementAttribute( _Meta, cm, 0, 0, 1 );
	mea->setName( "translate" );
	mea->setOffset( daeOffsetOf(domLink::domAttachment_start,elemTranslate) );
	mea->setElementType( domTranslate::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementArrayAttribute( _Meta, cm, 1, 0, -1 );
	mea->setName( "rotate" );
	mea->setOffset( daeOffsetOf(domLink::domAttachment_start,elemRotate_array) );
	mea->setElementType( domRotate::registerElement() );
	cm->appendChild( mea );
	
	cm->setMaxOrdinal( 1 );
	_Meta->setCMRoot( cm );	

	//	Add attribute: joint
 	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "joint" );
		ma->setType( daeAtomicType::get("Token"));
		ma->setOffset( daeOffsetOf( domLink::domAttachment_start , attrJoint ));
		ma->setContainer( _Meta );
	
		_Meta->appendAttribute(ma);
	}
	
	
	_Meta->setElementSize(sizeof(domLink::domAttachment_start));
	_Meta->validate();

	return _Meta;
}

daeElementRef
domLink::domAttachment_end::create(daeInt)
{
	domLink::domAttachment_endRef ref = new domLink::domAttachment_end;
	return ref;
}


daeMetaElement *
domLink::domAttachment_end::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "attachment_end" );
	_Meta->registerClass(domLink::domAttachment_end::create, &_Meta);

	_Meta->setIsInnerClass( true );
	daeMetaCMPolicy *cm = NULL;
	daeMetaElementAttribute *mea = NULL;
	cm = new daeMetaSequence( _Meta, cm, 0, 1, 1 );

	mea = new daeMetaElementAttribute( _Meta, cm, 0, 0, 1 );
	mea->setName( "translate" );
	mea->setOffset( daeOffsetOf(domLink::domAttachment_end,elemTranslate) );
	mea->setElementType( domTranslate::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementArrayAttribute( _Meta, cm, 1, 0, -1 );
	mea->setName( "rotate" );
	mea->setOffset( daeOffsetOf(domLink::domAttachment_end,elemRotate_array) );
	mea->setElementType( domRotate::registerElement() );
	cm->appendChild( mea );
	
	cm->setMaxOrdinal( 1 );
	_Meta->setCMRoot( cm );	

	//	Add attribute: joint
 	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "joint" );
		ma->setType( daeAtomicType::get("Token"));
		ma->setOffset( daeOffsetOf( domLink::domAttachment_end , attrJoint ));
		ma->setContainer( _Meta );
	
		_Meta->appendAttribute(ma);
	}
	
	
	_Meta->setElementSize(sizeof(domLink::domAttachment_end));
	_Meta->validate();

	return _Meta;
}


daeMetaElement * domLink::_Meta = NULL;
daeMetaElement * domLink::domAttachment_full::_Meta = NULL;
daeMetaElement * domLink::domAttachment_start::_Meta = NULL;
daeMetaElement * domLink::domAttachment_end::_Meta = NULL;


