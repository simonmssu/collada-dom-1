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
#include <dom/domInputLocal.h>
#include <dae/daeMetaCMPolicy.h>
#include <dae/daeMetaSequence.h>
#include <dae/daeMetaChoice.h>
#include <dae/daeMetaGroup.h>
#include <dae/daeMetaAny.h>
#include <dae/daeMetaElementAttribute.h>

daeElementRef
domInputLocal::create()
{
	domInputLocalRef ref = new domInputLocal;
	ref->attrSource.setContainer( (domInputLocal*)ref );
	return ref;
}


daeMetaElement *
domInputLocal::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(getTypeStatic());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement;
	dae.setMeta(getTypeStatic(), *meta);
	meta->setName( "InputLocal" );
	meta->registerClass(domInputLocal::create, &meta);


	//	Add attribute: semantic
	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "semantic" );
		ma->setType( daeAtomicType::get("xsNMTOKEN"));
		ma->setOffset( daeOffsetOf( domInputLocal , attrSemantic ));
		ma->setContainer( meta );
		ma->setIsRequired( true );
	
		meta->appendAttribute(ma);
	}

	//	Add attribute: source
	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "source" );
		ma->setType( daeAtomicType::get("URIFragmentType"));
		ma->setOffset( daeOffsetOf( domInputLocal , attrSource ));
		ma->setContainer( meta );
		ma->setIsRequired( true );
	
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domInputLocal));
	meta->validate();

	return meta;
}

