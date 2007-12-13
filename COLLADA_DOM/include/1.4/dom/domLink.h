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
#ifndef __domLink_h__
#define __domLink_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

#include <dom/domTranslate.h>
#include <dom/domRotate.h>
#include <dom/domLink.h>

class domLink : public daeElement
{
public:
	COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::LINK; }
public:
	class domAttachment_full;

	typedef daeSmartRef<domAttachment_full> domAttachment_fullRef;
	typedef daeTArray<domAttachment_fullRef> domAttachment_full_Array;

	class domAttachment_full : public daeElement
	{
	public:
		COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::ATTACHMENT_FULL; }
	protected:  // Attribute
		domToken attrJoint;

	protected:  // Elements
		domTranslateRef elemTranslate;
		domRotate_Array elemRotate_array;
		domLinkRef elemLink;

	public:	//Accessors and Mutators
		/**
		 * Gets the joint attribute.
		 * @return Returns a domToken of the joint attribute.
		 */
		domToken getJoint() const { return attrJoint; }
		/**
		 * Sets the joint attribute.
		 * @param atJoint The new value for the joint attribute.
		 */
		void setJoint( domToken atJoint ) { attrJoint = atJoint; _validAttributeArray[0] = true; }

		/**
		 * Gets the translate element.
		 * @return a daeSmartRef to the translate element.
		 */
		const domTranslateRef getTranslate() const { return elemTranslate; }
		/**
		 * Gets the rotate element array.
		 * @return Returns a reference to the array of rotate elements.
		 */
		domRotate_Array &getRotate_array() { return elemRotate_array; }
		/**
		 * Gets the rotate element array.
		 * @return Returns a constant reference to the array of rotate elements.
		 */
		const domRotate_Array &getRotate_array() const { return elemRotate_array; }
		/**
		 * Gets the link element.
		 * @return a daeSmartRef to the link element.
		 */
		const domLinkRef getLink() const { return elemLink; }
	protected:
		/**
		 * Constructor
		 */
		domAttachment_full() : attrJoint(), elemTranslate(), elemRotate_array(), elemLink() {}
		/**
		 * Destructor
		 */
		virtual ~domAttachment_full() {}
		/**
		 * Copy Constructor
		 */
		domAttachment_full( const domAttachment_full &cpy ) : daeElement() { (void)cpy; }
		/**
		 * Overloaded assignment operator
		 */
		virtual domAttachment_full &operator=( const domAttachment_full &cpy ) { (void)cpy; return *this; }

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

	class domAttachment_start;

	typedef daeSmartRef<domAttachment_start> domAttachment_startRef;
	typedef daeTArray<domAttachment_startRef> domAttachment_start_Array;

	class domAttachment_start : public daeElement
	{
	public:
		COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::ATTACHMENT_START; }
	protected:  // Attribute
		domToken attrJoint;

	protected:  // Elements
		domTranslateRef elemTranslate;
		domRotate_Array elemRotate_array;

	public:	//Accessors and Mutators
		/**
		 * Gets the joint attribute.
		 * @return Returns a domToken of the joint attribute.
		 */
		domToken getJoint() const { return attrJoint; }
		/**
		 * Sets the joint attribute.
		 * @param atJoint The new value for the joint attribute.
		 */
		void setJoint( domToken atJoint ) { attrJoint = atJoint; _validAttributeArray[0] = true; }

		/**
		 * Gets the translate element.
		 * @return a daeSmartRef to the translate element.
		 */
		const domTranslateRef getTranslate() const { return elemTranslate; }
		/**
		 * Gets the rotate element array.
		 * @return Returns a reference to the array of rotate elements.
		 */
		domRotate_Array &getRotate_array() { return elemRotate_array; }
		/**
		 * Gets the rotate element array.
		 * @return Returns a constant reference to the array of rotate elements.
		 */
		const domRotate_Array &getRotate_array() const { return elemRotate_array; }
	protected:
		/**
		 * Constructor
		 */
		domAttachment_start() : attrJoint(), elemTranslate(), elemRotate_array() {}
		/**
		 * Destructor
		 */
		virtual ~domAttachment_start() {}
		/**
		 * Copy Constructor
		 */
		domAttachment_start( const domAttachment_start &cpy ) : daeElement() { (void)cpy; }
		/**
		 * Overloaded assignment operator
		 */
		virtual domAttachment_start &operator=( const domAttachment_start &cpy ) { (void)cpy; return *this; }

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

	class domAttachment_end;

	typedef daeSmartRef<domAttachment_end> domAttachment_endRef;
	typedef daeTArray<domAttachment_endRef> domAttachment_end_Array;

	class domAttachment_end : public daeElement
	{
	public:
		COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::ATTACHMENT_END; }
	protected:  // Attribute
		domToken attrJoint;

	protected:  // Elements
		domTranslateRef elemTranslate;
		domRotate_Array elemRotate_array;

	public:	//Accessors and Mutators
		/**
		 * Gets the joint attribute.
		 * @return Returns a domToken of the joint attribute.
		 */
		domToken getJoint() const { return attrJoint; }
		/**
		 * Sets the joint attribute.
		 * @param atJoint The new value for the joint attribute.
		 */
		void setJoint( domToken atJoint ) { attrJoint = atJoint; _validAttributeArray[0] = true; }

		/**
		 * Gets the translate element.
		 * @return a daeSmartRef to the translate element.
		 */
		const domTranslateRef getTranslate() const { return elemTranslate; }
		/**
		 * Gets the rotate element array.
		 * @return Returns a reference to the array of rotate elements.
		 */
		domRotate_Array &getRotate_array() { return elemRotate_array; }
		/**
		 * Gets the rotate element array.
		 * @return Returns a constant reference to the array of rotate elements.
		 */
		const domRotate_Array &getRotate_array() const { return elemRotate_array; }
	protected:
		/**
		 * Constructor
		 */
		domAttachment_end() : attrJoint(), elemTranslate(), elemRotate_array() {}
		/**
		 * Destructor
		 */
		virtual ~domAttachment_end() {}
		/**
		 * Copy Constructor
		 */
		domAttachment_end( const domAttachment_end &cpy ) : daeElement() { (void)cpy; }
		/**
		 * Overloaded assignment operator
		 */
		virtual domAttachment_end &operator=( const domAttachment_end &cpy ) { (void)cpy; return *this; }

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
	xsNCName attrSid;
	xsNCName attrName;

protected:  // Elements
	domAttachment_full_Array elemAttachment_full_array;
	domAttachment_start_Array elemAttachment_start_array;
	domAttachment_end_Array elemAttachment_end_array;

public:	//Accessors and Mutators
	/**
	 * Gets the sid attribute.
	 * @return Returns a xsNCName of the sid attribute.
	 */
	xsNCName getSid() const { return attrSid; }
	/**
	 * Sets the sid attribute.
	 * @param atSid The new value for the sid attribute.
	 */
	void setSid( xsNCName atSid ) { *(daeStringRef*)&attrSid = atSid; _validAttributeArray[0] = true; }

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
	 * Gets the attachment_full element array.
	 * @return Returns a reference to the array of attachment_full elements.
	 */
	domAttachment_full_Array &getAttachment_full_array() { return elemAttachment_full_array; }
	/**
	 * Gets the attachment_full element array.
	 * @return Returns a constant reference to the array of attachment_full elements.
	 */
	const domAttachment_full_Array &getAttachment_full_array() const { return elemAttachment_full_array; }
	/**
	 * Gets the attachment_start element array.
	 * @return Returns a reference to the array of attachment_start elements.
	 */
	domAttachment_start_Array &getAttachment_start_array() { return elemAttachment_start_array; }
	/**
	 * Gets the attachment_start element array.
	 * @return Returns a constant reference to the array of attachment_start elements.
	 */
	const domAttachment_start_Array &getAttachment_start_array() const { return elemAttachment_start_array; }
	/**
	 * Gets the attachment_end element array.
	 * @return Returns a reference to the array of attachment_end elements.
	 */
	domAttachment_end_Array &getAttachment_end_array() { return elemAttachment_end_array; }
	/**
	 * Gets the attachment_end element array.
	 * @return Returns a constant reference to the array of attachment_end elements.
	 */
	const domAttachment_end_Array &getAttachment_end_array() const { return elemAttachment_end_array; }
protected:
	/**
	 * Constructor
	 */
	domLink() : attrSid(), attrName(), elemAttachment_full_array(), elemAttachment_start_array(), elemAttachment_end_array() {}
	/**
	 * Destructor
	 */
	virtual ~domLink() {}
	/**
	 * Copy Constructor
	 */
	domLink( const domLink &cpy ) : daeElement() { (void)cpy; }
	/**
	 * Overloaded assignment operator
	 */
	virtual domLink &operator=( const domLink &cpy ) { (void)cpy; return *this; }

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
