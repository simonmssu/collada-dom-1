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

#ifndef __DAE_ELEMENT_H__
#define __DAE_ELEMENT_H__
#include <string>
#include <dae/daeTypes.h>
#include <dae/daeMemorySystem.h>
#include <wchar.h>
#include <dae/daeArray.h>
#include <dae/daeRefCountedObj.h>

//#ifndef NO_MALLOC_HEADER
//#include <malloc.h>
//#endif

namespace COLLADA_TYPE
{
#ifdef _MSC_VER
	enum TypeEnum;
#else
	typedef const int TypeEnum;
#endif
};

class daeMetaElement;
class daeMetaAttribute;
class daeIntegrationObject;
class daeDocument;
class daeURI;

template <typename T> class daeSmartRef;

//Contributed by Nus - Wed, 08 Nov 2006
/**
 * Initializing resolve array.
 */
extern "C" void initializeResolveArray(void);

/**
 * Terminating resolve array.
 */
extern "C" void terminateResolveArray(void);
//-------------------

/**
 * The @c daeElement class represents an instance of a COLLADA "Element";
 * it is the main base class for the COLLADA Dom.
 * Features of this class include:
 * - Uses factory concepts defined via daeMetaElement
 * - Composed of attributes, content elements and content values
 * - Reference counted via daeSmartRef
 * - Contains information for XML base URI, and XML containing element
 */
class daeElement : public daeRefCountedObj
{
public:
	/**
	 * Macro that defines new and delete overrides for this class
	 */
	DAE_ALLOC;
protected:
	daeIntegrationObject*	_intObject;
	daeElement*				_parent;
	daeDocument*			_document;
	daeMetaElement*			_meta;
	daeString				_elementName;
	daeBoolArray			_validAttributeArray;

public:
	/** An enum that describes the state of user integration with this object */
	DLLSPEC enum IntegrationState {
		/** The user integration is not initialized */
		int_uninitialized,
		/** The user integration object has been created */
		int_created,
		/** The user integration object has been converted */
		int_converted,
		/** The user integration object is completed */
		int_finished
	};
protected:
	daeElement( const daeElement &cpy ) : daeRefCountedObj() { (void)cpy; };
	virtual daeElement &operator=( const daeElement &cpy ) { (void)cpy; return *this; }

	// This function is called internally.
	DLLSPEC void setDocument( daeDocument* c, bool notifyDocument );

public:
	/**
	 * Element Constructor.
	 * @note This should not be used externally.
	 * Use factories to create elements
	 */
	DLLSPEC daeElement();
	/**
	 * Element Destructor.
	 * @note This should not be used externally, 
	 * if daeSmartRefs are being used.
	 */
	virtual DLLSPEC ~daeElement();

	// sthomas (see https://collada.org/public_forum/viewtopic.php?t=325&)
	static void releaseElements();

	/**
	 * Resolves all fields of type daeURI and IDRef.
	 * This is done via database query of the URI or IDRef.
	 */
	DLLSPEC void resolve();

	/**
	 * Sets up a @c daeElement. Called on all @c daeElements as part of their initialization.
	 * @param meta Meta element to use to configure this element.
	 * @note Should not be called externally.
	 */
	DLLSPEC void setup(daeMetaElement* meta);

	/**
	 * Places an element as a child of @c this element. 
	 * This function searches through the list of potential child element
	 * fields in @c this element, checking for a matching element type where the new element can be added.
	 * If a match of type is found, the element* is assigned or appended to
	 * that field, based on whether it is a single child or an array of
	 * children. This automatically adds the new element to the <tt><i> _contents </i></tt> of its parent, if the parent has one.  
	 *
	 * @param element Element to be placed in the @c this container.
	 * @return Returns true if the element was successfully placed, false otherwise.
	 */
	DLLSPEC daeBool placeElement(daeElement* element);
	
	/**
	 * This function searches through the list of potential child elements
	 * (fields) checking for a matching element type where this element can be added.
	 * If a match of type is found, the element* is assigned or appended to
	 * that field (based on whether it is a single child or an array of
	 * children. 
	 * If the parent element contains a _contents array, element will be placed at the specified index,
	 * otherwise element gets placed among elements of the same type.
	 *
	 * @param index is the place in the _contents array to insert element.
	 * @param element is the element to be placed in the 'this' container.
	 * @return return whether or not the element was successfully placed.
	 */
	DLLSPEC daeBool placeElementAt(daeInt index, daeElement* element);

	/**
	 * Places an element as a child of @c this element. 
	 * This function inserts the new element before the element specified as marker.
	 * This automatically adds the new element to the <tt><i> _contents </i></tt> of its parent, if the parent has one.  
	 * @param marker The daeElement used to determine where the new child will be placed.
	 * @param element Element to be placed in the @c this container.
	 * @return Returns true if the element was successfully placed, false otherwise.
	 */
	DLLSPEC daeBool placeElementBefore( daeElement* marker, daeElement *element );

	/**
	 * Places an element as a child of @c this element. 
	 * This function inserts the new element After the element specified as marker.
	 * This automatically adds the new element to the <tt><i> _contents </i></tt> of its parent, if the parent has one.  
	 * @param marker The daeElement used to determine where the new child will be placed.
	 * @param element Element to be placed in the @c this container.
	 * @return Returns true if the element was successfully placed, false otherwise.
	 */
	DLLSPEC daeBool placeElementAfter( daeElement* marker, daeElement *element );

	/**
	 * Finds the last index into the array of children of the name specified.
	 * @param elementName The name to look for.
	 * @return Returns the index into the children array of the last element with name elementName. -1 if
	 *         there are no children of name elementName.
	 */
	DLLSPEC daeInt findLastIndexOf( daeString elementName );

	/**
	 * Removes the specified element from it parent, the @c this element.
	 * This function is the opposite of @c placeElement().  It removes the specified
	 * element from the <tt><i> _contents </i></tt> array, and from wherever else it appears
	 * inside of the @c this element.  Use this function instead of @c clear(), @c remove() or @c delete()
	 * if you want to keep the <tt><i> _contents </i></tt> field up-to-date.
	 *
	 * @param element Element to be removed in the @c this container.
	 * @return Returns true if the element was successfully removed, false otherwise.
	 */
	DLLSPEC daeBool removeChildElement(daeElement* element);
	
	/**
	 * Removes the specified element from its parent element. 
	 * This function is the opposite of @c placeElement().  It removes the specified
	 * element from both the <tt><i> _contents </i></tt> array and from wherever else it appears
	 * inside of its parent. The function itself finds the parent, and is defined as a static method,
	 * since removing the element from its parent may result in the deletion of the element.
	 * If the element has no parent, nothing is done.
	 *
	 * Use this function instead of @c clear(), @c remove() or @c delete()
	 * if you want to keep <tt><i> _contents </i></tt> up-to-date.
	 *
	 * @param element Element to remove from its parent container, the function finds the parent element.
	 * @return Returns true if the element was successfully removed, false otherwise.
	 */
	static daeBool removeFromParent(daeElement* element)
	{
		if(element != NULL && element->_parent != NULL) 
			return(element->_parent->removeChildElement(element));
		return false;
	};

	/**
	 * Returns the number of attributes in this element.
	 * @return The number of attributes this element has.
	 */
	DLLSPEC size_t getAttributeCount();
	
	/**
	 * Returns the daeMetaAttribute object corresponding to the attribute specified.
	 * @param name The name of the attribute to find.
	 * @return Returns the corresponding daeMetaAttribute object or NULL if this element
	 * doesn't have the specified attribute.
	 */
	DLLSPEC daeMetaAttribute* getAttributeObject(daeString name);

	/**
	 * Returns the daeMetaAttribute object corresponding to attribute i.
	 * @param i The index of the attribute to find.
	 * @return Returns the corresponding daeMetaAttribute object
	 */
	DLLSPEC daeMetaAttribute* getAttributeObject(size_t i);

	/**
	 * Returns the name of the attribute at the specified index.
	 * @param i The index of the attribute whose name should be retrieved.
	 * @return Returns the name of the attribute, or "" if the index is out of range.
	 */
	DLLSPEC std::string getAttributeName(size_t i);

	/**
	 * Checks if this element can have the attribute specified.
	 * @param name The name of the attribute to look for.
	 * @return Returns true is this element can have an attribute with the name specified. False otherwise.
	 */
	DLLSPEC daeBool hasAttribute(daeString name);

	/**
	 * Checks if an attribute has been set either by being loaded from the COLLADA document or set
	 * programmatically.
	 * @param name The name of the attribute to check.
	 * @return Returns true if the attribute has been set. False if the attribute hasn't been set 
	 * or doesn't exist for this element.
	 */
	DLLSPEC daeBool isAttributeSet(daeString name);

	/**
	 * Gets an attribute's value as a string.
	 * @param name The name of the attribute.
	 * @return The value of the attribute. Returns an empty string if this element doesn't
	 * have the specified attribute.
	 */
	DLLSPEC std::string getAttribute(daeString name);

	/**
	 * Just like the previous method, this method gets an attribute's value as a string. It
	 * takes the string as a reference parameter instead of returning it, for extra efficiency.
	 * @param name The name of the attribute.
	 * @param A string in which to store the value of the attribute. This will be set to an empty 
	 * string if this element doesn't have the specified attribute.
	 */
	DLLSPEC void getAttribute(daeString name, std::string& value);

	/**
	 * Gets an attribute's value as a string.
	 * @param i The index of the attribute to retrieve.
	 * @return The value of the attribute.
	 */
	DLLSPEC std::string getAttribute(size_t i);

	/**
	 * Just like the previous method, this method gets an attribute's value as a string. It
	 * takes the string as a reference parameter instead of returning it, for extra efficiency.
	 * @param i The index of the attribute to retrieve.
	 * @param A string in which to store the value of the attribute.
	 */
	DLLSPEC void getAttribute(size_t i, std::string& value);

	struct DLLSPEC attr {
		attr();
		attr(const std::string& name, const std::string& value);

		std::string name;
		std::string value;
	};
	
	/**
	 * Returns an array containing all the attributes of this element.
	 * @return A daeArray of attr objects.
	 */
	DLLSPEC daeTArray<attr> getAttributes();

	/**
	 * Just like the previous method, this method returns an array containing all the attributes
	 * of this element. It returns the result via a reference parameter for extra efficiency.
	 * @param attrs The array of attr objects to return.
	 */
	DLLSPEC void getAttributes(daeTArray<attr>& attrs);

	/**
	 * Sets the attribute to the specified value.
	 * @param name Attribute to set.
	 * @param value Value to apply to the attribute.
	 * @return Returns true if the attribute was found and the value was set, false otherwise.
	 */
	virtual DLLSPEC daeBool setAttribute(daeString name, daeString value);

	/**
	 * Sets the attribute at the specified index to the given value.
	 * @param i Index of the attribute to set.
	 * @param value Value to apply to the attribute.
	 * @return Returns true if the attribute was found and the value was set, false otherwise.
	 */
	virtual DLLSPEC daeBool setAttribute(size_t i, daeString value);

	/**
	 * Returns the daeMetaAttribute object corresponding to the character data for this element.
	 * @return Returns a daeMetaAttribute object or NULL if this element doesn't have
	 * character data.
	 */
	DLLSPEC daeMetaAttribute* getCharDataObject();

	/**
	 * Checks if this element can have character data.
	 * @return Returns true if this element can have character data, false otherwise.
	 */
	DLLSPEC daeBool hasCharData();

	/**
	 * Returns this element's character data as a string.
	 * @return A string containing this element's character data, or an empty string
	 * if this element can't have character data.
	 */
	DLLSPEC std::string getCharData();

	/**
	 * Similar to the previous method, but fills a string passed in by the user for efficiency.
	 * @param data The string to be filled with this element's character content. The
	 * string is set to an empty string if this element can't have character data.
	 */
	DLLSPEC void getCharData(std::string& data);

	/**
	 * Sets this element's character data.
	 * @param data The new character data of this element.
	 * @return Returns true if this element can have character data and the character data
	 * was successfully changed, false otherwise.
	 */
	DLLSPEC daeBool setCharData(const std::string& data);

	// These functions are deprecated.
	DLLSPEC daeMemoryRef getAttributeValue(daeString name); // Use getAttribute or getAttributeObject instead.
	DLLSPEC daeBool hasValue(); // Use hasCharData instead.
	DLLSPEC daeMemoryRef getValuePointer(); // Use getCharData or getCharDataObject instead.

	/**
	 * Finds the database document associated with @c this element.
	 * @return Returns the @c daeDocument representing the containing file or database
	 * group.
	 */
	daeDocument*	getDocument() const { return _document; }

	/**
	 * Deprecated.
	 */
	daeDocument*	getCollection() const { return _document; }
	
	/**
	 * Sets the database document associated with this element.
	 * @param c The daeDocument to associate with this element.
	 */
	DLLSPEC void setDocument(daeDocument* c) { setDocument( c, true ); }
	/**
	 * Deprecated.
	 */
	DLLSPEC void setCollection(daeDocument* c );

	/**
	 * Gets the URI of the document containing this element, note that this is NOT the URI of the element.
	 * @return Returns a pointer to the daeURI of the document containing this element.
	 */
	DLLSPEC daeURI*	getDocumentURI() const;

	/**
	 * Creates an element via the element factory system.  This creation
	 * is based @em only on potential child elements of this element.
	 * @param elementName Class name of the subelement to create.
	 * @return Returns the created @c daeElement, if it was successfully created.
	 */
	DLLSPEC daeSmartRef<daeElement> createElement(daeString elementName);

	/**
	 * Creates a subelement via @c createElement() and places it via @c placeElement().
	 * Automatically adds the new element to the <tt><i> _contents </i></tt> of its parent, if the parent has one.  
	 * This is the primary method used to construct the COLLADA dom hierarchy.
	 * @param elementName - Class name of the subelement to create.
	 * @return Returns the created @c daeElement, if it was successfully created.
	 */
	DLLSPEC daeElement* createAndPlace(daeString elementName);

	/**
	 * Create a sub-element via #createElement and place it via #placeElementAt
	 * This also automatically inserts the new element at the specified index in the _contents of it's 
	 * parent, if the parent has one.  
	 * This is useful when constructing the COLLADA dom hierarchy
	 * @param index the position in the _contents array the newly created element is to be placed at
	 * @param elementName - the className of the sub-element to be created
	 * @return the created element if it was in fact successfully created.
	 */
	DLLSPEC daeElement* createAndPlaceAt(daeInt index, daeString elementName);

	/**
	 * Gets the container element for @c this element.
	 * If @c createAndPlace() was used to create the element, its parent is the the caller of @c createAndPlace().
	 * @return Returns the parent element, if @c this is not the top level element.
	 */
	daeElement* getParentElement() { return _parent;}
	/**
	 * Deprecated. Use getParentElement()
	 * @deprecated
	 */
	daeElement* getXMLParentElement() { return _parent;}
	/**
	 * Sets the parent element for this element.
	 * @param newParent The element which is the new parent element for this element.
	 * @note This function is called internally and not meant to be called form the client application. 
	 */
	void setParentElement( daeElement *parent ) { _parent = parent; }

	/**
	 * Gets the associated Meta information for this element.  This
	 * Meta also acts as a factory.  See @c daeMetaElement documentation for more
	 * information.
	 * @return Returns the associated meta information.
	 */
	inline daeMetaElement* getMeta() { return _meta; }

	/**
	 * Gets the integration object associated with this @c daeElement object.
	 * See @c daeIntegrationObject for more details.
	 * Integration Objects can be automatically created and associated
	 * with the COLLADA dom via the meta-factory mechanism and
	 * can be very useful for using the API to integrate with COLLADA.
	 * @param from_state Specifies where in the conversion process from COLLADA you are interested. A full conversion is the default.
	 * @param to_state Specifies where in the conversion process to COLLADA you are interested. No conversion is the default.
	 * @return Returns the @c daeIntegrationObject associated with this COLLADA element
	 * instance.
	 */
	DLLSPEC daeIntegrationObject* getIntObject( IntegrationState from_state = int_converted, IntegrationState to_state = int_uninitialized );

	/**
	 * Gets the element type.
	 * @return Returns the COLLADA_TYPE::TypeEnum value corresponding to this element's type.
	 */
	virtual COLLADA_TYPE::TypeEnum getElementType() const { return (COLLADA_TYPE::TypeEnum)0; }
	/**
	 * Gets the element type name for this element.
	 * @return Returns the string for the type name.
	 */
	DLLSPEC daeString getTypeName() const;

	/**
	 * Gets this element's name.
	 * @return Returns the string for the name.
	 * @remarks This function returns NULL if the element's name is identical to it's type's name.
	 */
	DLLSPEC daeString getElementName() const;
	/**
	 * Sets this element's name.
	 * @param nm Specifies the string to use as the element's name.
	 * @remarks Use caution when using this function since you can easily create invalid COLLADA documents.
	 */
	DLLSPEC void setElementName( daeString nm );
	
	/**
	 * Gets the element ID if it exists.
	 * @return Returns the value of the ID attribute, if there is such
	 * an attribute on this element type.
	 * @return the string for the element ID if it exists.
	 */
	DLLSPEC daeString getID() const;

	/**
	 * Gets the children/sub-elements of this element.
	 * This is a helper function used to easily access an element's children without the use of the
	 * _meta objects.  This function adds the convenience of the _contents array to elements that do
	 * not contain a _contents array.
	 * @return The return value.  An elementref array to append this element's children to.
	 */
	DLLSPEC daeTArray< daeSmartRef<daeElement> > getChildren();

	/**
	 * Same as the previous function, but returns the result via a parameter instead
	 * of a return value, for extra efficiency.
	 * @param array The return value.  An elementref array to append this element's children to.
	 */
	//void getChildren( daeElementRefArray &array );
	DLLSPEC void getChildren( daeTArray<daeSmartRef<daeElement> > &array );

	/**
	 * Clones/deep copies this @c daeElement and all of it's subtree.
	 * @param idSuffix A string to append to the copied element's ID, if one exists.
	 *        Default is no ID mangling.
	 * @param nameSuffix A string to append to the copied element's name, if one exists.
	 *        Default is no name mangling.
	 * @return Returns a @c daeElement smartref of the copy of this element.
	 */
	DLLSPEC daeSmartRef<daeElement> clone( daeString idSuffix = NULL, daeString nameSuffix = NULL );
	
public:
	/**
	 * Resolves all @c daeURIs yet to be resolved in all @c daeElements that have been
	 * created.
	 * This is used as part of post-parsing process of a COLLADA instance document, 
	 * which results in a new document in the database.
	 */
	static DLLSPEC void resolveAll();

	/**
	 * Clears the resolveArray.
	 */
	static DLLSPEC void clearResolveArray();
public:
	/**
	 * Releases the element passed in. This function is a static wrapper that invokes 
	 * <tt> elem->release() </tt> on the passed in element,
	 * if it is not NULL.
	 * @param elem Element to call @c release() for, if the element exists.
	 */
	static DLLSPEC void releaseElem(const daeElement* elem) {if (elem != NULL) elem->release();}
	
	/**
	 * Increments the reference counter for the element passed in. This function is a static wrapper
	 * that invokes <tt> elem->ref() </tt> on the passed in element,
	 * if it is not NULL.
	 * @param elem Element to call @c ref() for, if the element exists.
	 */
	static DLLSPEC void refElem(const daeElement* elem) { if (elem != NULL) elem->ref(); }

	/**
	 * Appends the passed in element to the list of elements that need to be resolved.
	 * The elements in this list will be resolved during @c resolveAll().
	 * @param elem Element to add to the list of elements
	 * waiting for their @c daeURIs to be resolved.
	 */
	static DLLSPEC void appendResolveElement(daeElement* elem);

	// This function is called internally
	static DLLSPEC void deleteCMDataArray(daeTArray<daeCharArray*>& cmData);
};
#include <dae/daeSmartRef.h>
typedef daeSmartRef<daeElement> daeElementRef;
typedef daeSmartRef<const daeElement> daeElementConstRef;
//#include <dae/daeArray.h>
typedef daeTArray<daeElementRef> daeElementRefArray;

extern daeElementRef DAECreateElement(int nbytes);

template <typename T> 
inline T *daeSafeCast( daeElement *element ) 
{ 
    if ( element && element->getMeta() == T::_Meta ) 
        return (T *)element; 
    return NULL; 
} 

#endif //__DAE_ELEMENT_H__
