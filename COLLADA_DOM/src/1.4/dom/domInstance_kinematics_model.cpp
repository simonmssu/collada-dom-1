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
#include <dom/domInstance_kinematics_model.h>
#include <dae/daeMetaCMPolicy.h>
#include <dae/daeMetaSequence.h>
#include <dae/daeMetaChoice.h>
#include <dae/daeMetaGroup.h>
#include <dae/daeMetaAny.h>
#include <dae/daeMetaElementAttribute.h>

daeElementRef
domInstance_kinematics_model::create(daeInt)
{
	domInstance_kinematics_modelRef ref = new domInstance_kinematics_model;
	ref->attrUrl.setContainer( (domInstance_kinematics_model*)ref );
	return ref;
}


daeMetaElement *
domInstance_kinematics_model::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "instance_kinematics_model" );
	_Meta->registerClass(domInstance_kinematics_model::create, &_Meta);

	daeMetaCMPolicy *cm = NULL;
	daeMetaElementAttribute *mea = NULL;
	cm = new daeMetaChoice( _Meta, cm, 0, 0, 1, 1 );

	cm = new daeMetaSequence( _Meta, cm, 0, 1, 1 );

	mea = new daeMetaElementAttribute( _Meta, cm, 0, 1, 1 );
	mea->setName( "attach" );
	mea->setOffset( daeOffsetOf(domInstance_kinematics_model,elemAttach) );
	mea->setElementType( domInstance_kinematics_model::domAttach::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementArrayAttribute( _Meta, cm, 1, 0, -1 );
	mea->setName( "rotate" );
	mea->setOffset( daeOffsetOf(domInstance_kinematics_model,elemRotate_array) );
	mea->setElementType( domRotate::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementAttribute( _Meta, cm, 2, 0, 1 );
	mea->setName( "translate" );
	mea->setOffset( daeOffsetOf(domInstance_kinematics_model,elemTranslate) );
	mea->setElementType( domTranslate::registerElement() );
	cm->appendChild( mea );
	
	cm->setMaxOrdinal( 2 );
	cm->getParent()->appendChild( cm );
	cm = cm->getParent();
	
	cm = new daeMetaSequence( _Meta, cm, 3, 1, 1 );

	mea = new daeMetaElementAttribute( _Meta, cm, 0, 1, 1 );
	mea->setName( "bind_joint" );
	mea->setOffset( daeOffsetOf(domInstance_kinematics_model,elemBind_joint) );
	mea->setElementType( domInstance_kinematics_model::domBind_joint::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementAttribute( _Meta, cm, 1, 1, 1 );
	mea->setName( "bind_link" );
	mea->setOffset( daeOffsetOf(domInstance_kinematics_model,elemBind_link) );
	mea->setElementType( domInstance_kinematics_model::domBind_link::registerElement() );
	cm->appendChild( mea );
	
	cm->setMaxOrdinal( 1 );
	cm->getParent()->appendChild( cm );
	cm = cm->getParent();
	
	cm->setMaxOrdinal( 0 );
	_Meta->setCMRoot( cm );	
	// Ordered list of sub-elements
    _Meta->addContents(daeOffsetOf(domInstance_kinematics_model,_contents));
    _Meta->addContentsOrder(daeOffsetOf(domInstance_kinematics_model,_contentsOrder));
        
    _Meta->addCMDataArray(daeOffsetOf(domInstance_kinematics_model,_CMData), 1);
	//	Add attribute: sid
 	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "sid" );
		ma->setType( daeAtomicType::get("xsNCName"));
		ma->setOffset( daeOffsetOf( domInstance_kinematics_model , attrSid ));
		ma->setContainer( _Meta );
	
		_Meta->appendAttribute(ma);
	}

	//	Add attribute: name
 	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "name" );
		ma->setType( daeAtomicType::get("xsNCName"));
		ma->setOffset( daeOffsetOf( domInstance_kinematics_model , attrName ));
		ma->setContainer( _Meta );
	
		_Meta->appendAttribute(ma);
	}

	//	Add attribute: url
 	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "url" );
		ma->setType( daeAtomicType::get("xsAnyURI"));
		ma->setOffset( daeOffsetOf( domInstance_kinematics_model , attrUrl ));
		ma->setContainer( _Meta );
		ma->setIsRequired( true );
	
		_Meta->appendAttribute(ma);
	}
	
	
	_Meta->setElementSize(sizeof(domInstance_kinematics_model));
	_Meta->validate();

	return _Meta;
}

daeElementRef
domInstance_kinematics_model::domAttach::create(daeInt)
{
	domInstance_kinematics_model::domAttachRef ref = new domInstance_kinematics_model::domAttach;
	return ref;
}


daeMetaElement *
domInstance_kinematics_model::domAttach::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "attach" );
	_Meta->registerClass(domInstance_kinematics_model::domAttach::create, &_Meta);

	_Meta->setIsInnerClass( true );

	//	Add attribute: predecessor
 	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "predecessor" );
		ma->setType( daeAtomicType::get("Token"));
		ma->setOffset( daeOffsetOf( domInstance_kinematics_model::domAttach , attrPredecessor ));
		ma->setContainer( _Meta );
	
		_Meta->appendAttribute(ma);
	}

	//	Add attribute: successor
 	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "successor" );
		ma->setType( daeAtomicType::get("Token"));
		ma->setOffset( daeOffsetOf( domInstance_kinematics_model::domAttach , attrSuccessor ));
		ma->setContainer( _Meta );
	
		_Meta->appendAttribute(ma);
	}
	
	
	_Meta->setElementSize(sizeof(domInstance_kinematics_model::domAttach));
	_Meta->validate();

	return _Meta;
}

daeElementRef
domInstance_kinematics_model::domBind_joint::create(daeInt)
{
	domInstance_kinematics_model::domBind_jointRef ref = new domInstance_kinematics_model::domBind_joint;
	return ref;
}


daeMetaElement *
domInstance_kinematics_model::domBind_joint::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "bind_joint" );
	_Meta->registerClass(domInstance_kinematics_model::domBind_joint::create, &_Meta);

	_Meta->setIsInnerClass( true );
	daeMetaCMPolicy *cm = NULL;
	daeMetaElementAttribute *mea = NULL;
	cm = new daeMetaSequence( _Meta, cm, 0, 1, 1 );

	mea = new daeMetaElementAttribute( _Meta, cm, 0, 1, 1 );
	mea->setName( "value" );
	mea->setOffset( daeOffsetOf(domInstance_kinematics_model::domBind_joint,elemValue) );
	mea->setElementType( domInstance_kinematics_model::domBind_joint::domValue::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementAttribute( _Meta, cm, 1, 1, 1 );
	mea->setName( "channel" );
	mea->setOffset( daeOffsetOf(domInstance_kinematics_model::domBind_joint,elemChannel) );
	mea->setElementType( domChannel::registerElement() );
	cm->appendChild( mea );
	
	cm->setMaxOrdinal( 1 );
	_Meta->setCMRoot( cm );	

	//	Add attribute: source
 	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "source" );
		ma->setType( daeAtomicType::get("xsToken"));
		ma->setOffset( daeOffsetOf( domInstance_kinematics_model::domBind_joint , attrSource ));
		ma->setContainer( _Meta );
	
		_Meta->appendAttribute(ma);
	}
	
	
	_Meta->setElementSize(sizeof(domInstance_kinematics_model::domBind_joint));
	_Meta->validate();

	return _Meta;
}

daeElementRef
domInstance_kinematics_model::domBind_joint::domValue::create(daeInt)
{
	domInstance_kinematics_model::domBind_joint::domValueRef ref = new domInstance_kinematics_model::domBind_joint::domValue;
	return ref;
}


daeMetaElement *
domInstance_kinematics_model::domBind_joint::domValue::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "value" );
	_Meta->registerClass(domInstance_kinematics_model::domBind_joint::domValue::create, &_Meta);

	_Meta->setIsInnerClass( true );
	//	Add attribute: _value
 	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "_value" );
		ma->setType( daeAtomicType::get("Float"));
		ma->setOffset( daeOffsetOf( domInstance_kinematics_model::domBind_joint::domValue , _value ));
		ma->setContainer( _Meta );
		_Meta->appendAttribute(ma);
	}

	//	Add attribute: target
 	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "target" );
		ma->setType( daeAtomicType::get("Token"));
		ma->setOffset( daeOffsetOf( domInstance_kinematics_model::domBind_joint::domValue , attrTarget ));
		ma->setContainer( _Meta );
	
		_Meta->appendAttribute(ma);
	}
	
	
	_Meta->setElementSize(sizeof(domInstance_kinematics_model::domBind_joint::domValue));
	_Meta->validate();

	return _Meta;
}

daeElementRef
domInstance_kinematics_model::domBind_link::create(daeInt)
{
	domInstance_kinematics_model::domBind_linkRef ref = new domInstance_kinematics_model::domBind_link;
	return ref;
}


daeMetaElement *
domInstance_kinematics_model::domBind_link::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "bind_link" );
	_Meta->registerClass(domInstance_kinematics_model::domBind_link::create, &_Meta);

	_Meta->setIsInnerClass( true );

	//	Add attribute: target
 	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "target" );
		ma->setType( daeAtomicType::get("xsToken"));
		ma->setOffset( daeOffsetOf( domInstance_kinematics_model::domBind_link , attrTarget ));
		ma->setContainer( _Meta );
	
		_Meta->appendAttribute(ma);
	}

	//	Add attribute: source
 	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "source" );
		ma->setType( daeAtomicType::get("xsToken"));
		ma->setOffset( daeOffsetOf( domInstance_kinematics_model::domBind_link , attrSource ));
		ma->setContainer( _Meta );
	
		_Meta->appendAttribute(ma);
	}
	
	
	_Meta->setElementSize(sizeof(domInstance_kinematics_model::domBind_link));
	_Meta->validate();

	return _Meta;
}


daeMetaElement * domInstance_kinematics_model::_Meta = NULL;
daeMetaElement * domInstance_kinematics_model::domAttach::_Meta = NULL;
daeMetaElement * domInstance_kinematics_model::domBind_joint::_Meta = NULL;
daeMetaElement * domInstance_kinematics_model::domBind_joint::domValue::_Meta = NULL;
daeMetaElement * domInstance_kinematics_model::domBind_link::_Meta = NULL;


