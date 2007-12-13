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
#include <dom/domKinematics_model.h>
#include <dae/daeMetaCMPolicy.h>
#include <dae/daeMetaSequence.h>
#include <dae/daeMetaChoice.h>
#include <dae/daeMetaGroup.h>
#include <dae/daeMetaAny.h>
#include <dae/daeMetaElementAttribute.h>

daeElementRef
domKinematics_model::create(daeInt)
{
	domKinematics_modelRef ref = new domKinematics_model;
	return ref;
}


daeMetaElement *
domKinematics_model::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "kinematics_model" );
	_Meta->registerClass(domKinematics_model::create, &_Meta);

	daeMetaCMPolicy *cm = NULL;
	daeMetaElementAttribute *mea = NULL;
	cm = new daeMetaSequence( _Meta, cm, 0, 1, 1 );

	mea = new daeMetaElementAttribute( _Meta, cm, 0, 0, 1 );
	mea->setName( "asset" );
	mea->setOffset( daeOffsetOf(domKinematics_model,elemAsset) );
	mea->setElementType( domAsset::registerElement() );
	cm->appendChild( mea );
	
	cm = new daeMetaChoice( _Meta, cm, 0, 1, 1, 1 );

	cm = new daeMetaSequence( _Meta, cm, 0, 1, 1 );

	cm = new daeMetaChoice( _Meta, cm, 1, 0, 1, -1 );

	mea = new daeMetaElementArrayAttribute( _Meta, cm, 0, 0, -1 );
	mea->setName( "joint" );
	mea->setOffset( daeOffsetOf(domKinematics_model,elemJoint_array) );
	mea->setElementType( domJoint::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementArrayAttribute( _Meta, cm, 0, 0, -1 );
	mea->setName( "instance_joint" );
	mea->setOffset( daeOffsetOf(domKinematics_model,elemInstance_joint_array) );
	mea->setElementType( domInstance_joint::registerElement() );
	cm->appendChild( mea );
	
	cm->setMaxOrdinal( 0 );
	cm->getParent()->appendChild( cm );
	cm = cm->getParent();
	
	mea = new daeMetaElementArrayAttribute( _Meta, cm, 3001, 1, -1 );
	mea->setName( "link" );
	mea->setOffset( daeOffsetOf(domKinematics_model,elemLink_array) );
	mea->setElementType( domLink::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementArrayAttribute( _Meta, cm, 3002, 0, -1 );
	mea->setName( "attach_point" );
	mea->setOffset( daeOffsetOf(domKinematics_model,elemAttach_point_array) );
	mea->setElementType( domAttach_point::registerElement() );
	cm->appendChild( mea );
	
	cm->setMaxOrdinal( 3002 );
	cm->getParent()->appendChild( cm );
	cm = cm->getParent();
	
	mea = new daeMetaElementArrayAttribute( _Meta, cm, 3003, 1, -1 );
	mea->setName( "instance_kinematics_model" );
	mea->setOffset( daeOffsetOf(domKinematics_model,elemInstance_kinematics_model_array) );
	mea->setElementType( domInstance_kinematics_model::registerElement() );
	cm->appendChild( mea );
	
	cm->setMaxOrdinal( 3002 );
	cm->getParent()->appendChild( cm );
	cm = cm->getParent();
	
	mea = new daeMetaElementArrayAttribute( _Meta, cm, 2, 0, -1 );
	mea->setName( "extra" );
	mea->setOffset( daeOffsetOf(domKinematics_model,elemExtra_array) );
	mea->setElementType( domExtra::registerElement() );
	cm->appendChild( mea );
	
	cm->setMaxOrdinal( 2 );
	_Meta->setCMRoot( cm );	
	// Ordered list of sub-elements
    _Meta->addContents(daeOffsetOf(domKinematics_model,_contents));
    _Meta->addContentsOrder(daeOffsetOf(domKinematics_model,_contentsOrder));
        
    _Meta->addCMDataArray(daeOffsetOf(domKinematics_model,_CMData), 2);
	//	Add attribute: id
 	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "id" );
		ma->setType( daeAtomicType::get("xsID"));
		ma->setOffset( daeOffsetOf( domKinematics_model , attrId ));
		ma->setContainer( _Meta );
	
		_Meta->appendAttribute(ma);
	}

	//	Add attribute: name
 	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "name" );
		ma->setType( daeAtomicType::get("xsNCName"));
		ma->setOffset( daeOffsetOf( domKinematics_model , attrName ));
		ma->setContainer( _Meta );
	
		_Meta->appendAttribute(ma);
	}
	
	
	_Meta->setElementSize(sizeof(domKinematics_model));
	_Meta->validate();

	return _Meta;
}


daeMetaElement * domKinematics_model::_Meta = NULL;


