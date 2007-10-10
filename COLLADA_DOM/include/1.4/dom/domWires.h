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
#ifndef __domWires_h__
#define __domWires_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

#include <dom/domP.h>
#include <dom/domInputLocalOffset.h>

/**
 * This element defines all the wires used in the brep     structure.
 */
class domWires : public daeElement
{
public:
	COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::WIRES; }
public:
	class domVcount;

	typedef daeSmartRef<domVcount> domVcountRef;
	typedef daeTArray<domVcountRef> domVcount_Array;

	class domVcount : public daeElement
	{
	public:
		COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::VCOUNT; }

	protected:  // Value
		/**
		 * The domListOfUInts value of the text data of this element. 
		 */
		domListOfUInts _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a domListOfUInts reference of the _value array.
		 */
		domListOfUInts &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant domListOfUInts reference of the _value array.
		 */
		const domListOfUInts &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const domListOfUInts &val ) { _value = val; }

	protected:
		/**
		 * Constructor
		 */
		domVcount() : _value() {}
		/**
		 * Destructor
		 */
		virtual ~domVcount() {}
		/**
		 * Copy Constructor
		 */
		domVcount( const domVcount &cpy ) : daeElement() { (void)cpy; }
		/**
		 * Overloaded assignment operator
		 */
		virtual domVcount &operator=( const domVcount &cpy ) { (void)cpy; return *this; }

	public: // STATIC METHODS
		/**
		 * Creates an instance of this class and returns a daeElementRef referencing it.
		 * @param bytes The size allocated for this instance.
		 * @return a daeElementRef referencing an instance of this object.
		 */
		static DLLSPEC daeElementRef create(daeInt bytes);
		/**
		 * Creates a daeMetaElement object that describes this element in the meta object reflection framework.
		 * If a daeMetaElement already exists it will return that instead of creating a new one. 
		 * @return A daeMetaElement describing this COLLADA element.
		 */
		static DLLSPEC daeMetaElement* registerElement();

	public: // STATIC MEMBERS
		/**
		 * The daeMetaElement that describes this element in the meta object reflection framework.
		 */
		static DLLSPEC daeMetaElement* _Meta;
	};


protected:  // Attributes
	xsID attrId;
	xsNCName attrName;
	domUint attrCount;

protected:  // Elements
/**
 * One input elements is needed to define a wire by its edges. @see domInput
 */
	domInputLocalOffset_Array elemInput_array;
	domVcountRef elemVcount;
/**
 *  The indeces of the edges for each wire.  @see domP
 */
	domPRef elemP;

public:	//Accessors and Mutators
	/**
	 * Gets the id attribute.
	 * @return Returns a xsID of the id attribute.
	 */
	xsID getId() const { return attrId; }
	/**
	 * Sets the id attribute.
	 * @param atId The new value for the id attribute.
	 */
	void setId( xsID atId ) { *(daeStringRef*)&attrId = atId; _validAttributeArray[0] = true; 
		if( _document != NULL ) _document->changeElementID( this, attrId );
	}

	/**
	 * Gets the name attribute.
	 * @return Returns a xsNCName of the name attribute.
	 */
	xsNCName getName() const { return attrName; }
	/**
	 * Sets the name attribute.
	 * @param atName The new value for the name attribute.
	 */
	void setName( xsNCName atName ) { *(daeStringRef*)&attrName = atName; _validAttributeArray[1] = true; }

	/**
	 * Gets the count attribute.
	 * @return Returns a domUint of the count attribute.
	 */
	domUint getCount() const { return attrCount; }
	/**
	 * Sets the count attribute.
	 * @param atCount The new value for the count attribute.
	 */
	void setCount( domUint atCount ) { attrCount = atCount; _validAttributeArray[2] = true; }

	/**
	 * Gets the input element array.
	 * @return Returns a reference to the array of input elements.
	 */
	domInputLocalOffset_Array &getInput_array() { return elemInput_array; }
	/**
	 * Gets the input element array.
	 * @return Returns a constant reference to the array of input elements.
	 */
	const domInputLocalOffset_Array &getInput_array() const { return elemInput_array; }
	/**
	 * Gets the vcount element.
	 * @return a daeSmartRef to the vcount element.
	 */
	const domVcountRef getVcount() const { return elemVcount; }
	/**
	 * Gets the p element.
	 * @return a daeSmartRef to the p element.
	 */
	const domPRef getP() const { return elemP; }
protected:
	/**
	 * Constructor
	 */
	domWires() : attrId(), attrName(), attrCount(), elemInput_array(), elemVcount(), elemP() {}
	/**
	 * Destructor
	 */
	virtual ~domWires() {}
	/**
	 * Copy Constructor
	 */
	domWires( const domWires &cpy ) : daeElement() { (void)cpy; }
	/**
	 * Overloaded assignment operator
	 */
	virtual domWires &operator=( const domWires &cpy ) { (void)cpy; return *this; }

public: // STATIC METHODS
	/**
	 * Creates an instance of this class and returns a daeElementRef referencing it.
	 * @param bytes The size allocated for this instance.
	 * @return a daeElementRef referencing an instance of this object.
	 */
	static DLLSPEC daeElementRef create(daeInt bytes);
	/**
	 * Creates a daeMetaElement object that describes this element in the meta object reflection framework.
	 * If a daeMetaElement already exists it will return that instead of creating a new one. 
	 * @return A daeMetaElement describing this COLLADA element.
	 */
	static DLLSPEC daeMetaElement* registerElement();

public: // STATIC MEMBERS
	/**
	 * The daeMetaElement that describes this element in the meta object reflection framework.
	 */
	static DLLSPEC daeMetaElement* _Meta;
};


#endif
