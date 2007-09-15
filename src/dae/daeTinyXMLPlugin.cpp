/*
 * Copyright 2007 Sony Computer Entertainment Inc.
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

// The user can choose whether or not to include TinyXML support in the DOM. Supporting TinyXML will
// require linking against it. By default TinyXML support isn't included.
#if defined(DOM_INCLUDE_TINYXML)

#if defined(DOM_DYNAMIC)
#pragma comment(lib, "tinyxml.lib")
#endif

#pragma warning(disable: 4100) // warning C4100: 'element' : unreferenced formal parameter

#include <string>
#include <tinyxml.h>
#include <dae.h>
#include <dom.h>
#include <dae/daeMetaElement.h>
#include <dae/daeErrorHandler.h>
#include <dae/daeMetaElementAttribute.h>
#include <dae/daeTinyXMLPlugin.h>

#define TYPE_BUFFER_SIZE 1024*1024

namespace {
	daeInt getCurrentLineNumber(TiXmlElement* element) {
		return -1;
	}
}

daeTinyXMLPlugin::daeTinyXMLPlugin()
{
  m_doc = NULL;
}

daeTinyXMLPlugin::~daeTinyXMLPlugin()
{
}

daeInt daeTinyXMLPlugin::setOption( daeString option, daeString value )
{
	return DAE_ERR_INVALID_CALL;
}

daeString daeTinyXMLPlugin::getOption( daeString option )
{
	return NULL;
}

void daeTinyXMLPlugin::getProgress(daeInt* bytesParsed,
						 daeInt* lineNumber,
						 daeInt* totalBytes,
						 daeBool reset)
{
	if (totalBytes)
		*totalBytes = 0; // Not available
}


daeElementRef daeTinyXMLPlugin::readFromFile(const daeURI& uri) {
	// !!!steveT: Replace this with real URI to file path code, and update the resolver to only handle the file scheme
	TiXmlDocument doc;
	char file[512];
	uri.getPath(file, 512);
#if defined(WIN32)
	doc.LoadFile(&file[1]);
#else
	doc.LoadFile(&file[0]);
#endif
	if (!doc.RootElement()) {
		daeErrorHandler::get()->handleError((std::string("Failed to open ") + uri.getURI() +
																				 " in daeTinyXMLPlugin::readFromFile\n").c_str());
		return NULL;
	}
	return readElement(doc.RootElement(), NULL);
}

daeElementRef daeTinyXMLPlugin::readFromMemory(daeString buffer, const daeURI& baseUri) {
	TiXmlDocument doc;
	doc.Parse(buffer);
	if (!doc.RootElement()) {
		daeErrorHandler::get()->handleError("Failed to open XML document from memory buffer in "
																				"daeTinyXMLPlugin::readFromMemory\n");
		return NULL;
	}
	return readElement(doc.RootElement(), NULL);
}

daeElementRef daeTinyXMLPlugin::readElement(TiXmlElement* tinyXmlElement, daeElement* parentElement) {
	std::vector<attrPair> attributes;
	for (TiXmlAttribute* attrib = tinyXmlElement->FirstAttribute(); attrib != NULL; attrib = attrib->Next())
		attributes.push_back(attrPair(attrib->Name(), attrib->Value()));
		
	daeElementRef element = beginReadElement(parentElement, tinyXmlElement->Value(),
																					 attributes, getCurrentLineNumber(tinyXmlElement));
	if (!element) {
		// We couldn't create the element. beginReadElement already printed an error message.
		return NULL;
	}

  if (tinyXmlElement->GetText() != NULL)
		readElementText(element, tinyXmlElement->GetText(), getCurrentLineNumber(tinyXmlElement));
  
  // Recurse children
  for (TiXmlElement* child = tinyXmlElement->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
    element->placeElement(readElement(child, element));

	return element;
}

daeInt daeTinyXMLPlugin::write(daeURI *name, daeDocument *document, daeBool replace)
{
	// Make sure database and document are both set
	if (!database)
		return DAE_ERR_INVALID_CALL;
	if(!document)
		return DAE_ERR_COLLECTION_DOES_NOT_EXIST;

	// !!!steveT: Do a decent URI to file path conversion
	// Extract just the file path from the URI
	daeFixedName finalname;
	if (!name->getPath(finalname,sizeof(finalname)))
	{
		daeErrorHandler::get()->handleError( "can't get path in write\n" );
		return DAE_ERR_BACKEND_IO;
	}
	// If replace=false, don't replace existing files
	if(!replace)
	{
		// Using "stat" would be better, but it's not available on all platforms
#ifdef WIN32
		FILE *tempfd = fopen(finalname+1,"r");
#else
		FILE *tempfd = fopen(finalname, "r");
#endif
		if(tempfd != NULL)
		{
			// File exists, return error
			fclose(tempfd);
			return DAE_ERR_BACKEND_FILE_EXISTS;
		}
		fclose(tempfd);
	}
	
  m_doc = new TiXmlDocument(name->getURI());
  if (m_doc)
  {
    m_doc->SetTabSize(4);

   	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );  
	  m_doc->LinkEndChild( decl ); 

    writeElement(document->getDomRoot());

#ifdef WIN32
		m_doc->SaveFile(finalname+1);
#else
    m_doc->SaveFile(finalname);
#endif
    delete m_doc;
    m_doc = NULL;
  }
	return DAE_OK;
}

void daeTinyXMLPlugin::writeElement( daeElement* element )
{
	daeIntegrationObject* _intObject = element->getIntObject();
	daeMetaElement* _meta = element->getMeta();
	if(_intObject)
	{
		// added in response to bug 478
		_intObject->toCOLLADAChecked();
		_intObject->toCOLLADAPostProcessChecked();
	}

  if (!_meta->getIsTransparent() ) 
  {
		TiXmlElement* tiElm = new TiXmlElement( element->getElementName() );  
        
		if (m_elements.empty() == true) {
				m_doc->LinkEndChild(tiElm);
			} else {
			TiXmlElement* first = m_elements.front();
			first->LinkEndChild(tiElm);
		}
		m_elements.push_front(tiElm);

		daeMetaAttributeRefArray& attrs = _meta->getMetaAttributes();
		
		int acnt = (int)attrs.getCount();
		
		for(int i=0;i<acnt;i++) 
    {
			writeAttribute( attrs[i], element, i );
		}
	}
	daeMetaAttribute* valueAttr = _meta->getValueAttribute();
  if (valueAttr != NULL)
  {
    writeValue(valueAttr, element);
  }
	
	daeElementRefArray children;
	element->getChildren( children );
	for ( size_t x = 0; x < children.getCount(); x++ ) 
  {
		writeElement( children.get(x) );
	}

	/*if (_meta->getContents() != NULL) {
		daeElementRefArray* era = (daeElementRefArray*)_meta->getContents()->getWritableMemory(element);
		int elemCnt = (int)era->getCount();
		for(int i = 0; i < elemCnt; i++) {
			daeElementRef elem = (daeElementRef)era->get(i);
			if (elem != NULL) {
				writeElement( elem );
			}
		}
	}
	else
	{
		daeMetaElementAttributeArray& children = _meta->getMetaElements();
		int cnt = (int)children.getCount();
		for(int i=0;i<cnt;i++) {
			daeMetaElement *type = children[i]->getElementType();
			if ( !type->getIsAbstract() ) {
				for (int c = 0; c < children[i]->getCount(element); c++ ) {
					writeElement( *(daeElementRef*)children[i]->get(element,c) );
				}
			}
		}
	}*/
	if (!_meta->getIsTransparent() ) 
  {
    m_elements.pop_front();
	}
}


void daeTinyXMLPlugin::writeValue( daeMetaAttribute* attr, daeElement* element )
{
  char buffer[1024];
  char* elemMem;
  size_t valCount = attr->getCount(element);
  std::string str;

  if (valCount > 0)
  {
    for( size_t i = 0; i < valCount; i++ ) 
    {
      elemMem = attr->get( element, (int)i );
	    attr->getType()->memoryToString( elemMem, buffer, 1024);
      if (i > 0)
      {
        str += ' ';
      }
      str += buffer;
    }
    if (buffer[0] != 0)
    {
      TiXmlText * text = new TiXmlText( str.c_str() );
      m_elements.front()->LinkEndChild( text );
    }
  }
}

void daeTinyXMLPlugin::writeAttribute( daeMetaAttribute* attr, daeElement* element, daeInt attrNum )
{
	static daeChar atomicTypeBuf[TYPE_BUFFER_SIZE+1];
	daeChar *buf = atomicTypeBuf;
	daeUInt bufSz = TYPE_BUFFER_SIZE;

	size_t valCount = attr->getCount(element);
	//default values will not check correctly if they are arrays. Luckily there is only one array attribute in COLLADA.
	//don't write if !required and is set && is default

	int typeSize = attr->getType()->getSize();
	if ( typeSize >= TYPE_BUFFER_SIZE )
	{
		char msg[512];
		sprintf(msg,
			"daeMetaAttribute::print() - buffer too small for %s in %s\n",
			(daeString)attr->getName(),(daeString)attr->getContainer()->getName());
		daeErrorHandler::get()->handleError( msg );
		return;
	}

	if ( !attr->isArrayAttribute() && ( attr->getType()->getTypeEnum() == daeAtomicType::StringRefType || 
		 attr->getType()->getTypeEnum() == daeAtomicType::TokenType ) &&
		 *(char**)attr->getWritableMemory( element ) != NULL )
	{
		daeUInt sz = (daeUInt)strlen( *(char**)attr->getWritableMemory( element ) ) +1;
		if ( bufSz > TYPE_BUFFER_SIZE ) {
			buf = new char[ bufSz ];
			bufSz = sz;
		}
	}

	//always print value
//	if ( attrNum != -1 )
	{
		//not value attribute
		if ( !attr->getIsRequired() )
		{
			//not required
			if ( !element->isAttributeSet( attr->getName() ) )
			{
				//early out if !value && !required && !set
				return;
			}
			
			//is set
			//check for default suppression
			if ( attr->getDefault() != NULL )
			{
				//has a default value
				attr->getType()->stringToMemory( (daeChar*)attr->getDefault(), buf );
				char* elemMem = attr->get( element, 0 );
				if( memcmp( buf, elemMem, typeSize ) == 0 )
				{
					//is the default value so exit early
					return;
				}
			}

			//not default so print
//			xmlTextWriterStartAttribute( writer, (xmlChar*)(daeString)attr->getName() );
		//do val 0 first then space and the rest of the vals.
		  char* elemMem = attr->get( element, 0 );
		  attr->getType()->memoryToString( elemMem, buf, bufSz );
		  if ( buf[0] != 0 ) //null string check
		  {
        m_elements.front()->SetAttribute(attr->getName(), buf);
		  }

		}
		else {
		  char* elemMem = attr->get( element, 0 );
		  attr->getType()->memoryToString( elemMem, buf, bufSz );
		  if ( buf[0] != 0 ) //null string check
		  {
        m_elements.front()->SetAttribute(attr->getName(), buf);
		  }

			//print it because its required
//			xmlTextWriterStartAttribute( writer, (xmlChar*)(daeString)attr->getName() );
		}
	}
	if (valCount > 0) 
	{
		//do val 0 first then space and the rest of the vals.
		char* elemMem = attr->get( element, 0 );
		attr->getType()->memoryToString( elemMem, buf, bufSz );
		if ( buf[0] != 0 ) //null string check
		{
//			xmlTextWriterWriteString( writer, (xmlChar*)buf );
      m_elements.front()->SetAttribute(attr->getName(), buf);
		}

		*buf = ' ';
		for( size_t i = 1; i < valCount; i++ ) 
		{
			// !!!steveT: This isn't going to work at all.
			elemMem = attr->get( element, (int)i );
			attr->getType()->memoryToString( elemMem, buf+1, bufSz );
      m_elements.front()->SetValue(buf);
//			xmlTextWriterWriteString( writer, (xmlChar*)buf );
		}
	}
	if ( attrNum != -1 )
	{
//		xmlTextWriterEndAttribute( writer );
	}
	if ( buf != atomicTypeBuf )
	{
		delete[] buf;
	}
}

#endif // DOM_INCLUDE_TINYXML
