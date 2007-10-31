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
	mea->setName( "ref_attachment" );
	mea->setOffset( daeOffsetOf(domLink,elemRef_attachment_array) );
	mea->setElementType( domLink::domRef_attachment::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementArrayAttribute( _Meta, cm, 2, 0, -1 );
	mea->setName( "attachment" );
	mea->setOffset( daeOffsetOf(domLink,elemAttachment_array) );
	mea->setElementType( domLink::domAttachment::registerElement() );
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

	mea = new daeMetaElementArrayAttribute( _Meta, cm, 0, 0, -1 );
	mea->setName( "rotate" );
	mea->setOffset( daeOffsetOf(domLink::domAttachment_full,elemRotate_array) );
	mea->setElementType( domRotate::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementAttribute( _Meta, cm, 1, 0, 1 );
	mea->setName( "translate" );
	mea->setOffset( daeOffsetOf(domLink::domAttachment_full,elemTranslate) );
	mea->setElementType( domTranslate::registerElement() );
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
domLink::domRef_attachment::create(daeInt)
{
	domLink::domRef_attachmentRef ref = new domLink::domRef_attachment;
	return ref;
}


daeMetaElement *
domLink::domRef_attachment::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "ref_attachment" );
	_Meta->registerClass(domLink::domRef_attachment::create, &_Meta);

	_Meta->setIsInnerClass( true );
	daeMetaCMPolicy *cm = NULL;
	daeMetaElementAttribute *mea = NULL;
	cm = new daeMetaSequence( _Meta, cm, 0, 1, 1 );

	mea = new daeMetaElementArrayAttribute( _Meta, cm, 0, 0, -1 );
	mea->setName( "rotate" );
	mea->setOffset( daeOffsetOf(domLink::domRef_attachment,elemRotate_array) );
	mea->setElementType( domRotate::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementAttribute( _Meta, cm, 1, 0, 1 );
	mea->setName( "translate" );
	mea->setOffset( daeOffsetOf(domLink::domRef_attachment,elemTranslate) );
	mea->setElementType( domTranslate::registerElement() );
	cm->appendChild( mea );
	
	cm->setMaxOrdinal( 1 );
	_Meta->setCMRoot( cm );	

	//	Add attribute: joint
 	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "joint" );
		ma->setType( daeAtomicType::get("Token"));
		ma->setOffset( daeOffsetOf( domLink::domRef_attachment , attrJoint ));
		ma->setContainer( _Meta );
	
		_Meta->appendAttribute(ma);
	}
	
	
	_Meta->setElementSize(sizeof(domLink::domRef_attachment));
	_Meta->validate();

	return _Meta;
}

daeElementRef
domLink::domAttachment::create(daeInt)
{
	domLink::domAttachmentRef ref = new domLink::domAttachment;
	return ref;
}


daeMetaElement *
domLink::domAttachment::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "attachment" );
	_Meta->registerClass(domLink::domAttachment::create, &_Meta);

	_Meta->setIsInnerClass( true );
	daeMetaCMPolicy *cm = NULL;
	daeMetaElementAttribute *mea = NULL;
	cm = new daeMetaSequence( _Meta, cm, 0, 1, 1 );

	mea = new daeMetaElementArrayAttribute( _Meta, cm, 0, 0, -1 );
	mea->setName( "rotate" );
	mea->setOffset( daeOffsetOf(domLink::domAttachment,elemRotate_array) );
	mea->setElementType( domRotate::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementAttribute( _Meta, cm, 1, 0, 1 );
	mea->setName( "translate" );
	mea->setOffset( daeOffsetOf(domLink::domAttachment,elemTranslate) );
	mea->setElementType( domTranslate::registerElement() );
	cm->appendChild( mea );
	
	cm->setMaxOrdinal( 1 );
	_Meta->setCMRoot( cm );	

	//	Add attribute: joint
 	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "joint" );
		ma->setType( daeAtomicType::get("Token"));
		ma->setOffset( daeOffsetOf( domLink::domAttachment , attrJoint ));
		ma->setContainer( _Meta );
	
		_Meta->appendAttribute(ma);
	}
	
	
	_Meta->setElementSize(sizeof(domLink::domAttachment));
	_Meta->validate();

	return _Meta;
}


daeMetaElement * domLink::_Meta = NULL;
daeMetaElement * domLink::domAttachment_full::_Meta = NULL;
daeMetaElement * domLink::domRef_attachment::_Meta = NULL;
daeMetaElement * domLink::domAttachment::_Meta = NULL;


