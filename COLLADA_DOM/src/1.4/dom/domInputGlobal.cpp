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
#include <dom/domInputGlobal.h>
#include <dae/daeMetaCMPolicy.h>
#include <dae/daeMetaSequence.h>
#include <dae/daeMetaChoice.h>
#include <dae/daeMetaGroup.h>
#include <dae/daeMetaAny.h>
#include <dae/daeMetaElementAttribute.h>

daeElementRef
domInputGlobal::create(daeInt)
{
	domInputGlobalRef ref = new domInputGlobal;
	ref->attrSource.setContainer( (domInputGlobal*)ref );
	return ref;
}


daeMetaElement *
domInputGlobal::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "InputGlobal" );
	_Meta->registerClass(domInputGlobal::create, &_Meta);


	//	Add attribute: semantic
 	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "semantic" );
		ma->setType( daeAtomicType::get("xsNMTOKEN"));
		ma->setOffset( daeOffsetOf( domInputGlobal , attrSemantic ));
		ma->setContainer( _Meta );
		ma->setIsRequired( true );
	
		_Meta->appendAttribute(ma);
	}

	//	Add attribute: source
 	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "source" );
		ma->setType( daeAtomicType::get("xsAnyURI"));
		ma->setOffset( daeOffsetOf( domInputGlobal , attrSource ));
		ma->setContainer( _Meta );
		ma->setIsRequired( true );
	
		_Meta->appendAttribute(ma);
	}
	
	
	_Meta->setElementSize(sizeof(domInputGlobal));
	_Meta->validate();

	return _Meta;
}


daeMetaElement * domInputGlobal::_Meta = NULL;

