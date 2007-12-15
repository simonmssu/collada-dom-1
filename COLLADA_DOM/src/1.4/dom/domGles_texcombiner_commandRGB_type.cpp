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
#include <dom/domGles_texcombiner_commandRGB_type.h>
#include <dae/daeMetaCMPolicy.h>
#include <dae/daeMetaSequence.h>
#include <dae/daeMetaChoice.h>
#include <dae/daeMetaGroup.h>
#include <dae/daeMetaAny.h>
#include <dae/daeMetaElementAttribute.h>

daeElementRef
domGles_texcombiner_commandRGB_type::create(DAE& dae)
{
	domGles_texcombiner_commandRGB_typeRef ref = new domGles_texcombiner_commandRGB_type(dae);
	return ref;
}


daeMetaElement *
domGles_texcombiner_commandRGB_type::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(typeIDStatic());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(typeIDStatic(), *meta);
	meta->setName( "gles_texcombiner_commandRGB_type" );
	meta->registerClass(domGles_texcombiner_commandRGB_type::create);

	daeMetaCMPolicy *cm = NULL;
	daeMetaElementAttribute *mea = NULL;
	cm = new daeMetaSequence( meta, cm, 0, 1, 1 );

	mea = new daeMetaElementArrayAttribute( meta, cm, 0, 1, 3 );
	mea->setName( "argument" );
	mea->setOffset( daeOffsetOf(domGles_texcombiner_commandRGB_type,elemArgument_array) );
	mea->setElementType( domGles_texcombiner_argumentRGB_type::registerElement(dae) );
	cm->appendChild( mea );

	cm->setMaxOrdinal( 0 );
	meta->setCMRoot( cm );	

	//	Add attribute: operator
	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "operator" );
		ma->setType( dae.getAtomicTypes().get("Gles_texcombiner_operatorRGB_enums"));
		ma->setOffset( daeOffsetOf( domGles_texcombiner_commandRGB_type , attrOperator ));
		ma->setContainer( meta );
	
		meta->appendAttribute(ma);
	}

	//	Add attribute: scale
	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "scale" );
		ma->setType( dae.getAtomicTypes().get("xsFloat"));
		ma->setOffset( daeOffsetOf( domGles_texcombiner_commandRGB_type , attrScale ));
		ma->setContainer( meta );
		ma->setIsRequired( false );
	
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domGles_texcombiner_commandRGB_type));
	meta->validate();

	return meta;
}

