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

#include <dom/domRotate.h>
#include <dom/domTranslate.h>

class domLink : public daeElement
{
public:
	COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::LINK; }
public:
	class domRef_attachment;

	typedef daeSmartRef<domRef_attachment> domRef_attachmentRef;
	typedef daeTArray<domRef_attachmentRef> domRef_attachment_Array;

	class domRef_attachment : public daeElement
	{
	public:
		COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::REF_ATTACHMENT; }
	protected:  // Attribute
		domToken attrTarget;

	protected:  // Elements
		domRotate_Array elemRotate_array;
		domTranslateRef elemTranslate;

	public:	//Accessors and Mutators
		/**
		 * Gets the target attribute.
		 * @return Returns a domToken of the target attribute.
		 */
		domToken getTarget() const { return attrTarget; }
		/**
		 * Sets the target attribute.
		 * @param atTarget The new value for the target attribute.
		 */
		void setTarget( domToken atTarget ) { attrTarget = atTarget; _validAttributeArray[0] = true; }

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
		 * Gets the translate element.
		 * @return a daeSmartRef to the translate element.
		 */
		const domTranslateRef getTranslate() const { return elemTranslate; }
	protected:
		/**
		 * Constructor
		 */
		domRef_attachment() : attrTarget(), elemRotate_array(), elemTranslate() {}
		/**
		 * Destructor
		 */
		virtual ~domRef_attachment() {}
		/**
		 * Copy Constructor
		 */
		domRef_attachment( const domRef_attachment &cpy ) : daeElement() { (void)cpy; }
		/**
		 * Overloaded assignment operator
		 */
		virtual domRef_attachment &operator=( const domRef_attachment &cpy ) { (void)cpy; return *this; }

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

	class domAttachment;

	typedef daeSmartRef<domAttachment> domAttachmentRef;
	typedef daeTArray<domAttachmentRef> domAttachment_Array;

	class domAttachment : public daeElement
	{
	public:
		COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::ATTACHMENT; }
	protected:  // Attribute
		domToken attrTarget;

	protected:  // Elements
		domRotate_Array elemRotate_array;
		domTranslateRef elemTranslate;

	public:	//Accessors and Mutators
		/**
		 * Gets the target attribute.
		 * @return Returns a domToken of the target attribute.
		 */
		domToken getTarget() const { return attrTarget; }
		/**
		 * Sets the target attribute.
		 * @param atTarget The new value for the target attribute.
		 */
		void setTarget( domToken atTarget ) { attrTarget = atTarget; _validAttributeArray[0] = true; }

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
		 * Gets the translate element.
		 * @return a daeSmartRef to the translate element.
		 */
		const domTranslateRef getTranslate() const { return elemTranslate; }
	protected:
		/**
		 * Constructor
		 */
		domAttachment() : attrTarget(), elemRotate_array(), elemTranslate() {}
		/**
		 * Destructor
		 */
		virtual ~domAttachment() {}
		/**
		 * Copy Constructor
		 */
		domAttachment( const domAttachment &cpy ) : daeElement() { (void)cpy; }
		/**
		 * Overloaded assignment operator
		 */
		virtual domAttachment &operator=( const domAttachment &cpy ) { (void)cpy; return *this; }

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
	domRef_attachment_Array elemRef_attachment_array;
	domAttachment_Array elemAttachment_array;

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
	 * Gets the ref_attachment element array.
	 * @return Returns a reference to the array of ref_attachment elements.
	 */
	domRef_attachment_Array &getRef_attachment_array() { return elemRef_attachment_array; }
	/**
	 * Gets the ref_attachment element array.
	 * @return Returns a constant reference to the array of ref_attachment elements.
	 */
	const domRef_attachment_Array &getRef_attachment_array() const { return elemRef_attachment_array; }
	/**
	 * Gets the attachment element array.
	 * @return Returns a reference to the array of attachment elements.
	 */
	domAttachment_Array &getAttachment_array() { return elemAttachment_array; }
	/**
	 * Gets the attachment element array.
	 * @return Returns a constant reference to the array of attachment elements.
	 */
	const domAttachment_Array &getAttachment_array() const { return elemAttachment_array; }
protected:
	/**
	 * Constructor
	 */
	domLink() : attrSid(), attrName(), elemRef_attachment_array(), elemAttachment_array() {}
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
