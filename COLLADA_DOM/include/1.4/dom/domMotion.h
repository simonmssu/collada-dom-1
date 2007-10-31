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
#ifndef __domMotion_h__
#define __domMotion_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

#include <dom/domInstance_articulated_system.h>
#include <dom/domSource.h>
#include <dom/domExtra.h>
#include <dom/domInputLocal.h>

class domMotion : public daeElement
{
public:
	COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::MOTION; }
public:
	class domAxis_infos;

	typedef daeSmartRef<domAxis_infos> domAxis_infosRef;
	typedef daeTArray<domAxis_infosRef> domAxis_infos_Array;

	class domAxis_infos : public daeElement
	{
	public:
		COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::AXIS_INFOS; }

	protected:  // Element
		domInputLocal_Array elemInput_array;

	public:	//Accessors and Mutators
		/**
		 * Gets the input element array.
		 * @return Returns a reference to the array of input elements.
		 */
		domInputLocal_Array &getInput_array() { return elemInput_array; }
		/**
		 * Gets the input element array.
		 * @return Returns a constant reference to the array of input elements.
		 */
		const domInputLocal_Array &getInput_array() const { return elemInput_array; }
	protected:
		/**
		 * Constructor
		 */
		domAxis_infos() : elemInput_array() {}
		/**
		 * Destructor
		 */
		virtual ~domAxis_infos() {}
		/**
		 * Copy Constructor
		 */
		domAxis_infos( const domAxis_infos &cpy ) : daeElement() { (void)cpy; }
		/**
		 * Overloaded assignment operator
		 */
		virtual domAxis_infos &operator=( const domAxis_infos &cpy ) { (void)cpy; return *this; }

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

	class domEffector_info;

	typedef daeSmartRef<domEffector_info> domEffector_infoRef;
	typedef daeTArray<domEffector_infoRef> domEffector_info_Array;

	class domEffector_info : public daeElement
	{
	public:
		COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::EFFECTOR_INFO; }
	public:
		class domSpeed;

		typedef daeSmartRef<domSpeed> domSpeedRef;
		typedef daeTArray<domSpeedRef> domSpeed_Array;

		class domSpeed : public daeElement
		{
		public:
			COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::SPEED; }

		protected:  // Value
			/**
			 * The domDynamicLimitType value of the text data of this element. 
			 */
			domDynamicLimitType _value;

		public:	//Accessors and Mutators
			/**
			 * Gets the _value array.
			 * @return Returns a domDynamicLimitType reference of the _value array.
			 */
			domDynamicLimitType &getValue() { return _value; }
			/**
			 * Gets the _value array.
			 * @return Returns a constant domDynamicLimitType reference of the _value array.
			 */
			const domDynamicLimitType &getValue() const { return _value; }
			/**
			 * Sets the _value array.
			 * @param val The new value for the _value array.
			 */
			void setValue( const domDynamicLimitType &val ) { _value = val; }

		protected:
			/**
			 * Constructor
			 */
			domSpeed() : _value() {}
			/**
			 * Destructor
			 */
			virtual ~domSpeed() {}
			/**
			 * Copy Constructor
			 */
			domSpeed( const domSpeed &cpy ) : daeElement() { (void)cpy; }
			/**
			 * Overloaded assignment operator
			 */
			virtual domSpeed &operator=( const domSpeed &cpy ) { (void)cpy; return *this; }

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

		class domAcceleration;

		typedef daeSmartRef<domAcceleration> domAccelerationRef;
		typedef daeTArray<domAccelerationRef> domAcceleration_Array;

		class domAcceleration : public daeElement
		{
		public:
			COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::ACCELERATION; }

		protected:  // Value
			/**
			 * The domDynamicLimitType value of the text data of this element. 
			 */
			domDynamicLimitType _value;

		public:	//Accessors and Mutators
			/**
			 * Gets the _value array.
			 * @return Returns a domDynamicLimitType reference of the _value array.
			 */
			domDynamicLimitType &getValue() { return _value; }
			/**
			 * Gets the _value array.
			 * @return Returns a constant domDynamicLimitType reference of the _value array.
			 */
			const domDynamicLimitType &getValue() const { return _value; }
			/**
			 * Sets the _value array.
			 * @param val The new value for the _value array.
			 */
			void setValue( const domDynamicLimitType &val ) { _value = val; }

		protected:
			/**
			 * Constructor
			 */
			domAcceleration() : _value() {}
			/**
			 * Destructor
			 */
			virtual ~domAcceleration() {}
			/**
			 * Copy Constructor
			 */
			domAcceleration( const domAcceleration &cpy ) : daeElement() { (void)cpy; }
			/**
			 * Overloaded assignment operator
			 */
			virtual domAcceleration &operator=( const domAcceleration &cpy ) { (void)cpy; return *this; }

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

		class domDeceleration;

		typedef daeSmartRef<domDeceleration> domDecelerationRef;
		typedef daeTArray<domDecelerationRef> domDeceleration_Array;

		class domDeceleration : public daeElement
		{
		public:
			COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::DECELERATION; }

		protected:  // Value
			/**
			 * The domDynamicLimitType value of the text data of this element. 
			 */
			domDynamicLimitType _value;

		public:	//Accessors and Mutators
			/**
			 * Gets the _value array.
			 * @return Returns a domDynamicLimitType reference of the _value array.
			 */
			domDynamicLimitType &getValue() { return _value; }
			/**
			 * Gets the _value array.
			 * @return Returns a constant domDynamicLimitType reference of the _value array.
			 */
			const domDynamicLimitType &getValue() const { return _value; }
			/**
			 * Sets the _value array.
			 * @param val The new value for the _value array.
			 */
			void setValue( const domDynamicLimitType &val ) { _value = val; }

		protected:
			/**
			 * Constructor
			 */
			domDeceleration() : _value() {}
			/**
			 * Destructor
			 */
			virtual ~domDeceleration() {}
			/**
			 * Copy Constructor
			 */
			domDeceleration( const domDeceleration &cpy ) : daeElement() { (void)cpy; }
			/**
			 * Overloaded assignment operator
			 */
			virtual domDeceleration &operator=( const domDeceleration &cpy ) { (void)cpy; return *this; }

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

		class domJerk;

		typedef daeSmartRef<domJerk> domJerkRef;
		typedef daeTArray<domJerkRef> domJerk_Array;

		class domJerk : public daeElement
		{
		public:
			COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::JERK; }

		protected:  // Value
			/**
			 * The domDynamicLimitType value of the text data of this element. 
			 */
			domDynamicLimitType _value;

		public:	//Accessors and Mutators
			/**
			 * Gets the _value array.
			 * @return Returns a domDynamicLimitType reference of the _value array.
			 */
			domDynamicLimitType &getValue() { return _value; }
			/**
			 * Gets the _value array.
			 * @return Returns a constant domDynamicLimitType reference of the _value array.
			 */
			const domDynamicLimitType &getValue() const { return _value; }
			/**
			 * Sets the _value array.
			 * @param val The new value for the _value array.
			 */
			void setValue( const domDynamicLimitType &val ) { _value = val; }

		protected:
			/**
			 * Constructor
			 */
			domJerk() : _value() {}
			/**
			 * Destructor
			 */
			virtual ~domJerk() {}
			/**
			 * Copy Constructor
			 */
			domJerk( const domJerk &cpy ) : daeElement() { (void)cpy; }
			/**
			 * Overloaded assignment operator
			 */
			virtual domJerk &operator=( const domJerk &cpy ) { (void)cpy; return *this; }

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
		domSpeedRef elemSpeed;
		domAccelerationRef elemAcceleration;
		domDecelerationRef elemDeceleration;
		domJerkRef elemJerk;

	public:	//Accessors and Mutators
		/**
		 * Gets the speed element.
		 * @return a daeSmartRef to the speed element.
		 */
		const domSpeedRef getSpeed() const { return elemSpeed; }
		/**
		 * Gets the acceleration element.
		 * @return a daeSmartRef to the acceleration element.
		 */
		const domAccelerationRef getAcceleration() const { return elemAcceleration; }
		/**
		 * Gets the deceleration element.
		 * @return a daeSmartRef to the deceleration element.
		 */
		const domDecelerationRef getDeceleration() const { return elemDeceleration; }
		/**
		 * Gets the jerk element.
		 * @return a daeSmartRef to the jerk element.
		 */
		const domJerkRef getJerk() const { return elemJerk; }
	protected:
		/**
		 * Constructor
		 */
		domEffector_info() : elemSpeed(), elemAcceleration(), elemDeceleration(), elemJerk() {}
		/**
		 * Destructor
		 */
		virtual ~domEffector_info() {}
		/**
		 * Copy Constructor
		 */
		domEffector_info( const domEffector_info &cpy ) : daeElement() { (void)cpy; }
		/**
		 * Overloaded assignment operator
		 */
		virtual domEffector_info &operator=( const domEffector_info &cpy ) { (void)cpy; return *this; }

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
	domInstance_articulated_systemRef elemInstance_articulated_system;
	domSource_Array elemSource_array;
	domAxis_infosRef elemAxis_infos;
	domEffector_infoRef elemEffector_info;
	domExtra_Array elemExtra_array;

public:	//Accessors and Mutators
	/**
	 * Gets the instance_articulated_system element.
	 * @return a daeSmartRef to the instance_articulated_system element.
	 */
	const domInstance_articulated_systemRef getInstance_articulated_system() const { return elemInstance_articulated_system; }
	/**
	 * Gets the source element array.
	 * @return Returns a reference to the array of source elements.
	 */
	domSource_Array &getSource_array() { return elemSource_array; }
	/**
	 * Gets the source element array.
	 * @return Returns a constant reference to the array of source elements.
	 */
	const domSource_Array &getSource_array() const { return elemSource_array; }
	/**
	 * Gets the axis_infos element.
	 * @return a daeSmartRef to the axis_infos element.
	 */
	const domAxis_infosRef getAxis_infos() const { return elemAxis_infos; }
	/**
	 * Gets the effector_info element.
	 * @return a daeSmartRef to the effector_info element.
	 */
	const domEffector_infoRef getEffector_info() const { return elemEffector_info; }
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
	domMotion() : elemInstance_articulated_system(), elemSource_array(), elemAxis_infos(), elemEffector_info(), elemExtra_array() {}
	/**
	 * Destructor
	 */
	virtual ~domMotion() {}
	/**
	 * Copy Constructor
	 */
	domMotion( const domMotion &cpy ) : daeElement() { (void)cpy; }
	/**
	 * Overloaded assignment operator
	 */
	virtual domMotion &operator=( const domMotion &cpy ) { (void)cpy; return *this; }

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
