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
#include <dom/domLine.h>
#include <dae/daeMetaCMPolicy.h>
#include <dae/daeMetaSequence.h>
#include <dae/daeMetaChoice.h>
#include <dae/daeMetaGroup.h>
#include <dae/daeMetaAny.h>
#include <dae/daeMetaElementAttribute.h>

daeElementRef
domLine::create(daeInt)
{
	domLineRef ref = new domLine;
	return ref;
}


daeMetaElement *
domLine::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "line" );
	_Meta->registerClass(domLine::create, &_Meta);

	daeMetaCMPolicy *cm = NULL;
	daeMetaElementAttribute *mea = NULL;
	cm = new daeMetaSequence( _Meta, cm, 0, 1, 1 );

	mea = new daeMetaElementAttribute( _Meta, cm, 0, 1, 1 );
	mea->setName( "origin" );
	mea->setOffset( daeOffsetOf(domLine,elemOrigin) );
	mea->setElementType( domLine::domOrigin::registerElement() );
	cm->appendChild( mea );
	
	mea = new daeMetaElementAttribute( _Meta, cm, 1, 1, 1 );
	mea->setName( "direction" );
	mea->setOffset( daeOffsetOf(domLine,elemDirection) );
	mea->setElementType( domLine::domDirection::registerElement() );
	cm->appendChild( mea );
	
	cm->setMaxOrdinal( 1 );
	_Meta->setCMRoot( cm );	
	
	
	_Meta->setElementSize(sizeof(domLine));
	_Meta->validate();

	return _Meta;
}

daeElementRef
domLine::domOrigin::create(daeInt)
{
	domLine::domOriginRef ref = new domLine::domOrigin;
	return ref;
}


daeMetaElement *
domLine::domOrigin::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "origin" );
	_Meta->registerClass(domLine::domOrigin::create, &_Meta);

	_Meta->setIsInnerClass( true );
	//	Add attribute: _value
 	{
		daeMetaAttribute *ma = new daeMetaArrayAttribute;
		ma->setName( "_value" );
		ma->setType( daeAtomicType::get("Float3"));
		ma->setOffset( daeOffsetOf( domLine::domOrigin , _value ));
		ma->setContainer( _Meta );
		_Meta->appendAttribute(ma);
	}
	
	
	_Meta->setElementSize(sizeof(domLine::domOrigin));
	_Meta->validate();

	return _Meta;
}

daeElementRef
domLine::domDirection::create(daeInt)
{
	domLine::domDirectionRef ref = new domLine::domDirection;
	return ref;
}


daeMetaElement *
domLine::domDirection::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "direction" );
	_Meta->registerClass(domLine::domDirection::create, &_Meta);

	_Meta->setIsInnerClass( true );
	//	Add attribute: _value
 	{
		daeMetaAttribute *ma = new daeMetaArrayAttribute;
		ma->setName( "_value" );
		ma->setType( daeAtomicType::get("Float3"));
		ma->setOffset( daeOffsetOf( domLine::domDirection , _value ));
		ma->setContainer( _Meta );
		_Meta->appendAttribute(ma);
	}
	
	
	_Meta->setElementSize(sizeof(domLine::domDirection));
	_Meta->validate();

	return _Meta;
}


daeMetaElement * domLine::_Meta = NULL;
daeMetaElement * domLine::domOrigin::_Meta = NULL;
daeMetaElement * domLine::domDirection::_Meta = NULL;


