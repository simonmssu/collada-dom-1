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
#ifndef __domKinematics_h__
#define __domKinematics_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

#include <dom/domExtra.h>
#include <dom/domFormula.h>
#include <dom/domLimitsType.h>
#include <dom/domRotate.h>
#include <dom/domTranslate.h>

class domKinematics : public daeElement
{
public:
	COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::KINEMATICS; }
public:
	class domAxis_info;

	typedef daeSmartRef<domAxis_info> domAxis_infoRef;
	typedef daeTArray<domAxis_infoRef> domAxis_info_Array;

	class domAxis_info : public daeElement
	{
	public:
		COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::AXIS_INFO; }
	protected:  // Attributes
		xsNCName attrSid;
		xsNCName attrName;
		xsToken attrTarget;
		domBool attrLocked;
		domBool attrActive;
		domUint attrIndex;

	protected:  // Elements
		domLimitsTypeRef elemLimits;
		domFormulaRef elemFormula;

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
		 * Gets the target attribute.
		 * @return Returns a xsToken of the target attribute.
		 */
		xsToken getTarget() const { return attrTarget; }
		/**
		 * Sets the target attribute.
		 * @param atTarget The new value for the target attribute.
		 */
		void setTarget( xsToken atTarget ) { *(daeStringRef*)&attrTarget = atTarget; _validAttributeArray[2] = true; }

		/**
		 * Gets the locked attribute.
		 * @return Returns a domBool of the locked attribute.
		 */
		domBool getLocked() const { return attrLocked; }
		/**
		 * Sets the locked attribute.
		 * @param atLocked The new value for the locked attribute.
		 */
		void setLocked( domBool atLocked ) { attrLocked = atLocked; _validAttributeArray[3] = true; }

		/**
		 * Gets the active attribute.
		 * @return Returns a domBool of the active attribute.
		 */
		domBool getActive() const { return attrActive; }
		/**
		 * Sets the active attribute.
		 * @param atActive The new value for the active attribute.
		 */
		void setActive( domBool atActive ) { attrActive = atActive; _validAttributeArray[4] = true; }

		/**
		 * Gets the index attribute.
		 * @return Returns a domUint of the index attribute.
		 */
		domUint getIndex() const { return attrIndex; }
		/**
		 * Sets the index attribute.
		 * @param atIndex The new value for the index attribute.
		 */
		void setIndex( domUint atIndex ) { attrIndex = atIndex; _validAttributeArray[5] = true; }

		/**
		 * Gets the limits element.
		 * @return a daeSmartRef to the limits element.
		 */
		const domLimitsTypeRef getLimits() const { return elemLimits; }
		/**
		 * Gets the formula element.
		 * @return a daeSmartRef to the formula element.
		 */
		const domFormulaRef getFormula() const { return elemFormula; }
	protected:
		/**
		 * Constructor
		 */
		domAxis_info() : attrSid(), attrName(), attrTarget(), attrLocked(), attrActive(), attrIndex(), elemLimits(), elemFormula() {}
		/**
		 * Destructor
		 */
		virtual ~domAxis_info() {}
		/**
		 * Copy Constructor
		 */
		domAxis_info( const domAxis_info &cpy ) : daeElement() { (void)cpy; }
		/**
		 * Overloaded assignment operator
		 */
		virtual domAxis_info &operator=( const domAxis_info &cpy ) { (void)cpy; return *this; }

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

	class domKinematics_frame;

	typedef daeSmartRef<domKinematics_frame> domKinematics_frameRef;
	typedef daeTArray<domKinematics_frameRef> domKinematics_frame_Array;

	class domKinematics_frame : public daeElement
	{
	public:
		COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::KINEMATICS_FRAME; }
	public:
		class domOrigin;

		typedef daeSmartRef<domOrigin> domOriginRef;
		typedef daeTArray<domOriginRef> domOrigin_Array;

		class domOrigin : public daeElement
		{
		public:
			COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::ORIGIN; }
		protected:  // Attribute
			xsToken attrRef;

		protected:  // Elements
			domRotate_Array elemRotate_array;
			domTranslateRef elemTranslate;

		public:	//Accessors and Mutators
			/**
			 * Gets the ref attribute.
			 * @return Returns a xsToken of the ref attribute.
			 */
			xsToken getRef() const { return attrRef; }
			/**
			 * Sets the ref attribute.
			 * @param atRef The new value for the ref attribute.
			 */
			void setRef( xsToken atRef ) { *(daeStringRef*)&attrRef = atRef; _validAttributeArray[0] = true; }

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
			domOrigin() : attrRef(), elemRotate_array(), elemTranslate() {}
			/**
			 * Destructor
			 */
			virtual ~domOrigin() {}
			/**
			 * Copy Constructor
			 */
			domOrigin( const domOrigin &cpy ) : daeElement() { (void)cpy; }
			/**
			 * Overloaded assignment operator
			 */
			virtual domOrigin &operator=( const domOrigin &cpy ) { (void)cpy; return *this; }

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

		class domTip;

		typedef daeSmartRef<domTip> domTipRef;
		typedef daeTArray<domTipRef> domTip_Array;

		class domTip : public daeElement
		{
		public:
			COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::TIP; }
		protected:  // Attribute
			domToken attrRef;

		protected:  // Elements
			domRotate_Array elemRotate_array;
			domTranslateRef elemTranslate;

		public:	//Accessors and Mutators
			/**
			 * Gets the ref attribute.
			 * @return Returns a domToken of the ref attribute.
			 */
			domToken getRef() const { return attrRef; }
			/**
			 * Sets the ref attribute.
			 * @param atRef The new value for the ref attribute.
			 */
			void setRef( domToken atRef ) { attrRef = atRef; _validAttributeArray[0] = true; }

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
			domTip() : attrRef(), elemRotate_array(), elemTranslate() {}
			/**
			 * Destructor
			 */
			virtual ~domTip() {}
			/**
			 * Copy Constructor
			 */
			domTip( const domTip &cpy ) : daeElement() { (void)cpy; }
			/**
			 * Overloaded assignment operator
			 */
			virtual domTip &operator=( const domTip &cpy ) { (void)cpy; return *this; }

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



	protected:  // Elements
		domOriginRef elemOrigin;
		domTipRef elemTip;

	public:	//Accessors and Mutators
		/**
		 * Gets the origin element.
		 * @return a daeSmartRef to the origin element.
		 */
		const domOriginRef getOrigin() const { return elemOrigin; }
		/**
		 * Gets the tip element.
		 * @return a daeSmartRef to the tip element.
		 */
		const domTipRef getTip() const { return elemTip; }
	protected:
		/**
		 * Constructor
		 */
		domKinematics_frame() : elemOrigin(), elemTip() {}
		/**
		 * Destructor
		 */
		virtual ~domKinematics_frame() {}
		/**
		 * Copy Constructor
		 */
		domKinematics_frame( const domKinematics_frame &cpy ) : daeElement() { (void)cpy; }
		/**
		 * Overloaded assignment operator
		 */
		virtual domKinematics_frame &operator=( const domKinematics_frame &cpy ) { (void)cpy; return *this; }

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
	xsAnyURI attrSource;

protected:  // Elements
	domAxis_infoRef elemAxis_info;
	domKinematics_frameRef elemKinematics_frame;
	domExtra_Array elemExtra_array;

public:	//Accessors and Mutators
	/**
	 * Gets the source attribute.
	 * @return Returns a xsAnyURI reference of the source attribute.
	 */
	xsAnyURI &getSource() { return attrSource; }
	/**
	 * Gets the source attribute.
	 * @return Returns a constant xsAnyURI reference of the source attribute.
	 */
	const xsAnyURI &getSource() const { return attrSource; }
	/**
	 * Sets the source attribute.
	 * @param atSource The new value for the source attribute.
	 */
	void setSource( const xsAnyURI &atSource ) { attrSource = atSource; _validAttributeArray[0] = true; }

	/**
	 * Gets the axis_info element.
	 * @return a daeSmartRef to the axis_info element.
	 */
	const domAxis_infoRef getAxis_info() const { return elemAxis_info; }
	/**
	 * Gets the kinematics_frame element.
	 * @return a daeSmartRef to the kinematics_frame element.
	 */
	const domKinematics_frameRef getKinematics_frame() const { return elemKinematics_frame; }
	/**
	 * Gets the extra element array.
	 * @return Returns a reference to the array of extra elements.
	 */
	domExtra_Array &getExtra_array() { return elemExtra_array; }
	/**
	 * Gets the extra element array.
	 * @return Returns a constant reference to the array of extra elements.
	 */
	const domExtra_Array &getExtra_array() const { return elemExtra_array; }
protected:
	/**
	 * Constructor
	 */
	domKinematics() : attrSource(), elemAxis_info(), elemKinematics_frame(), elemExtra_array() {}
	/**
	 * Destructor
	 */
	virtual ~domKinematics() {}
	/**
	 * Copy Constructor
	 */
	domKinematics( const domKinematics &cpy ) : daeElement() { (void)cpy; }
	/**
	 * Overloaded assignment operator
	 */
	virtual domKinematics &operator=( const domKinematics &cpy ) { (void)cpy; return *this; }

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
