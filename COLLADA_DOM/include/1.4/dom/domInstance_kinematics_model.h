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
#ifndef __domInstance_kinematics_model_h__
#define __domInstance_kinematics_model_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

#include <dom/domRotate.h>
#include <dom/domTranslate.h>
#include <dom/domChannel.h>

class domInstance_kinematics_model : public daeElement
{
public:
	COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::INSTANCE_KINEMATICS_MODEL; }
public:
	class domAttach;

	typedef daeSmartRef<domAttach> domAttachRef;
	typedef daeTArray<domAttachRef> domAttach_Array;

	class domAttach : public daeElement
	{
	public:
		COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::ATTACH; }
	protected:  // Attributes
		domToken attrPredecessor;
		domToken attrSuccessor;


	public:	//Accessors and Mutators
		/**
		 * Gets the predecessor attribute.
		 * @return Returns a domToken of the predecessor attribute.
		 */
		domToken getPredecessor() const { return attrPredecessor; }
		/**
		 * Sets the predecessor attribute.
		 * @param atPredecessor The new value for the predecessor attribute.
		 */
		void setPredecessor( domToken atPredecessor ) { attrPredecessor = atPredecessor; _validAttributeArray[0] = true; }

		/**
		 * Gets the successor attribute.
		 * @return Returns a domToken of the successor attribute.
		 */
		domToken getSuccessor() const { return attrSuccessor; }
		/**
		 * Sets the successor attribute.
		 * @param atSuccessor The new value for the successor attribute.
		 */
		void setSuccessor( domToken atSuccessor ) { attrSuccessor = atSuccessor; _validAttributeArray[1] = true; }

	protected:
		/**
		 * Constructor
		 */
		domAttach() : attrPredecessor(), attrSuccessor() {}
		/**
		 * Destructor
		 */
		virtual ~domAttach() {}
		/**
		 * Copy Constructor
		 */
		domAttach( const domAttach &cpy ) : daeElement() { (void)cpy; }
		/**
		 * Overloaded assignment operator
		 */
		virtual domAttach &operator=( const domAttach &cpy ) { (void)cpy; return *this; }

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

	class domBind_joint;

	typedef daeSmartRef<domBind_joint> domBind_jointRef;
	typedef daeTArray<domBind_jointRef> domBind_joint_Array;

	class domBind_joint : public daeElement
	{
	public:
		COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::BIND_JOINT; }
	public:
		class domValue;

		typedef daeSmartRef<domValue> domValueRef;
		typedef daeTArray<domValueRef> domValue_Array;

		class domValue : public daeElement
		{
		public:
			COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::VALUE; }
		protected:  // Attribute
			domToken attrTarget;

		protected:  // Value
			/**
			 * The domFloat value of the text data of this element. 
			 */
			domFloat _value;

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
			 * Gets the value of this element.
			 * @return a domFloat of the value.
			 */
			domFloat getValue() const { return _value; }
			/**
			 * Sets the _value of this element.
			 * @param val The new value for this element.
			 */
			void setValue( domFloat val ) { _value = val; }

		protected:
			/**
			 * Constructor
			 */
			domValue() : attrTarget(), _value() {}
			/**
			 * Destructor
			 */
			virtual ~domValue() {}
			/**
			 * Copy Constructor
			 */
			domValue( const domValue &cpy ) : daeElement() { (void)cpy; }
			/**
			 * Overloaded assignment operator
			 */
			virtual domValue &operator=( const domValue &cpy ) { (void)cpy; return *this; }

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


	protected:  // Attribute
		xsToken attrSource;

	protected:  // Elements
		domValueRef elemValue;
		domChannelRef elemChannel;

	public:	//Accessors and Mutators
		/**
		 * Gets the source attribute.
		 * @return Returns a xsToken of the source attribute.
		 */
		xsToken getSource() const { return attrSource; }
		/**
		 * Sets the source attribute.
		 * @param atSource The new value for the source attribute.
		 */
		void setSource( xsToken atSource ) { *(daeStringRef*)&attrSource = atSource; _validAttributeArray[0] = true; }

		/**
		 * Gets the value element.
		 * @return a daeSmartRef to the value element.
		 */
		const domValueRef getValue() const { return elemValue; }
		/**
		 * Gets the channel element.
		 * @return a daeSmartRef to the channel element.
		 */
		const domChannelRef getChannel() const { return elemChannel; }
	protected:
		/**
		 * Constructor
		 */
		domBind_joint() : attrSource(), elemValue(), elemChannel() {}
		/**
		 * Destructor
		 */
		virtual ~domBind_joint() {}
		/**
		 * Copy Constructor
		 */
		domBind_joint( const domBind_joint &cpy ) : daeElement() { (void)cpy; }
		/**
		 * Overloaded assignment operator
		 */
		virtual domBind_joint &operator=( const domBind_joint &cpy ) { (void)cpy; return *this; }

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

	class domBind_link;

	typedef daeSmartRef<domBind_link> domBind_linkRef;
	typedef daeTArray<domBind_linkRef> domBind_link_Array;

	class domBind_link : public daeElement
	{
	public:
		COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::BIND_LINK; }
	protected:  // Attributes
		xsToken attrTarget;
		xsToken attrSource;


	public:	//Accessors and Mutators
		/**
		 * Gets the target attribute.
		 * @return Returns a xsToken of the target attribute.
		 */
		xsToken getTarget() const { return attrTarget; }
		/**
		 * Sets the target attribute.
		 * @param atTarget The new value for the target attribute.
		 */
		void setTarget( xsToken atTarget ) { *(daeStringRef*)&attrTarget = atTarget; _validAttributeArray[0] = true; }

		/**
		 * Gets the source attribute.
		 * @return Returns a xsToken of the source attribute.
		 */
		xsToken getSource() const { return attrSource; }
		/**
		 * Sets the source attribute.
		 * @param atSource The new value for the source attribute.
		 */
		void setSource( xsToken atSource ) { *(daeStringRef*)&attrSource = atSource; _validAttributeArray[1] = true; }

	protected:
		/**
		 * Constructor
		 */
		domBind_link() : attrTarget(), attrSource() {}
		/**
		 * Destructor
		 */
		virtual ~domBind_link() {}
		/**
		 * Copy Constructor
		 */
		domBind_link( const domBind_link &cpy ) : daeElement() { (void)cpy; }
		/**
		 * Overloaded assignment operator
		 */
		virtual domBind_link &operator=( const domBind_link &cpy ) { (void)cpy; return *this; }

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
	xsAnyURI attrUrl;

protected:  // Elements
	domAttachRef elemAttach;
	domRotate_Array elemRotate_array;
	domTranslateRef elemTranslate;
	domBind_jointRef elemBind_joint;
	domBind_linkRef elemBind_link;
	/**
	 * Used to preserve order in elements that do not specify strict sequencing of sub-elements.
	 */
	daeElementRefArray _contents;
	/**
	 * Used to preserve order in elements that have a complex content model.
	 */
	daeUIntArray       _contentsOrder;

	/**
	 * Used to store information needed for some content model objects.
	 */
	daeTArray< daeCharArray * > _CMData;


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
	 * Gets the url attribute.
	 * @return Returns a xsAnyURI reference of the url attribute.
	 */
	xsAnyURI &getUrl() { return attrUrl; }
	/**
	 * Gets the url attribute.
	 * @return Returns a constant xsAnyURI reference of the url attribute.
	 */
	const xsAnyURI &getUrl() const { return attrUrl; }
	/**
	 * Sets the url attribute.
	 * @param atUrl The new value for the url attribute.
	 */
	void setUrl( const xsAnyURI &atUrl ) { attrUrl = atUrl; _validAttributeArray[2] = true; }

	/**
	 * Gets the attach element.
	 * @return a daeSmartRef to the attach element.
	 */
	const domAttachRef getAttach() const { return elemAttach; }
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
	/**
	 * Gets the bind_joint element.
	 * @return a daeSmartRef to the bind_joint element.
	 */
	const domBind_jointRef getBind_joint() const { return elemBind_joint; }
	/**
	 * Gets the bind_link element.
	 * @return a daeSmartRef to the bind_link element.
	 */
	const domBind_linkRef getBind_link() const { return elemBind_link; }
	/**
	 * Gets the _contents array.
	 * @return Returns a reference to the _contents element array.
	 */
	daeElementRefArray &getContents() { return _contents; }
	/**
	 * Gets the _contents array.
	 * @return Returns a constant reference to the _contents element array.
	 */
	const daeElementRefArray &getContents() const { return _contents; }

protected:
	/**
	 * Constructor
	 */
	domInstance_kinematics_model() : attrSid(), attrName(), attrUrl(), elemAttach(), elemRotate_array(), elemTranslate(), elemBind_joint(), elemBind_link() {}
	/**
	 * Destructor
	 */
	virtual ~domInstance_kinematics_model() { daeElement::deleteCMDataArray(_CMData); }
	/**
	 * Copy Constructor
	 */
	domInstance_kinematics_model( const domInstance_kinematics_model &cpy ) : daeElement() { (void)cpy; }
	/**
	 * Overloaded assignment operator
	 */
	virtual domInstance_kinematics_model &operator=( const domInstance_kinematics_model &cpy ) { (void)cpy; return *this; }

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
