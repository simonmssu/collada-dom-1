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

#include <dae.h>
#include <dae/daeDom.h>
#include <dom/domEllipsoid.h>
#include <dae/daeMetaCMPolicy.h>
#include <dae/daeMetaSequence.h>
#include <dae/daeMetaChoice.h>
#include <dae/daeMetaGroup.h>
#include <dae/daeMetaAny.h>
#include <dae/daeMetaElementAttribute.h>

daeElementRef
domEllipsoid::create()
{
	domEllipsoidRef ref = new domEllipsoid;
	return ref;
}


daeMetaElement *
domEllipsoid::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(getTypeStatic());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement;
	dae.setMeta(getTypeStatic(), *meta);
	meta->setName( "ellipsoid" );
	meta->registerClass(domEllipsoid::create, &meta);

	daeMetaCMPolicy *cm = NULL;
	daeMetaElementAttribute *mea = NULL;
	cm = new daeMetaSequence( meta, cm, 0, 1, 1 );

	mea = new daeMetaElementAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "size" );
	mea->setOffset( daeOffsetOf(domEllipsoid,elemSize) );
	mea->setElementType( domEllipsoid::domSize::registerElement(dae) );
	cm->appendChild( mea );

	cm->setMaxOrdinal( 0 );
	meta->setCMRoot( cm );	

	meta->setElementSize(sizeof(domEllipsoid));
	meta->validate();

	return meta;
}

daeElementRef
domEllipsoid::domSize::create()
{
	domEllipsoid::domSizeRef ref = new domEllipsoid::domSize;
	return ref;
}


daeMetaElement *
domEllipsoid::domSize::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(getTypeStatic());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement;
	dae.setMeta(getTypeStatic(), *meta);
	meta->setName( "size" );
	meta->registerClass(domEllipsoid::domSize::create, &meta);

	meta->setIsInnerClass( true );
	//	Add attribute: _value
	{
		daeMetaAttribute *ma = new daeMetaArrayAttribute;
		ma->setName( "_value" );
		ma->setType( daeAtomicType::get("Float3"));
		ma->setOffset( daeOffsetOf( domEllipsoid::domSize , _value ));
		ma->setContainer( meta );
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domEllipsoid::domSize));
	meta->validate();

	return meta;
}

