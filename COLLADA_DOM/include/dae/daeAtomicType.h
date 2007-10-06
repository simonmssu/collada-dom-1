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

#ifndef __DAE_ATOMIC_TYPE_H__
#define __DAE_ATOMIC_TYPE_H__

#include <sstream>
#include <dae/daeTypes.h>
#include <dae/daeStringRef.h>
#include <dae/daeArray.h>
#include <dae/daeElement.h>

#ifndef _WIN32
#include <stdint.h>
#endif 

class daeAtomicType;
class daeMetaElement;

typedef daeTArray<daeAtomicType*> daeAtomicTypeArray;
class daeMetaAttribute;
typedef daeSmartRef<daeMetaAttribute> daeMetaAttributeRef;

/**
 * The @c daeAtomicType class implements a standard interface for
 * data elements in the reflective object system.
 *
 * @c daeAtomicType provides a central virtual interface that can be
 * used by the rest of the reflective object system.
 *
 * The atomic type system if very useful for file IO and building
 * automatic tools for data inspection and manipulation,
 * such as hierarchy examiners and object editors.
 *
 * Types provide the following symantic operations:
 * - @c print()
 * - @c memoryToString()
 * - @c stringToMemory()
 * - @c resolve()
 *
 * Types are also able to align data pointers appropriately.
 */
class daeAtomicType
{
public:
	/**
	 * destructor
	 */
	virtual ~daeAtomicType() {}

	/**
	 * constructor
	 */
	daeAtomicType();
	
public:
	/**
	 * Prints an atomic typed element into a destination string.
	 * @param src Source of the raw data from which to get the typed items.
	 * @param dst Destination to output the string version of the elements to.
	 * @return Returns true if the operation was successful, false if not successful.  
	 */
	virtual daeBool memoryToString(daeChar* src, std::ostringstream& dst) = 0;

	/**
	 * Reads an atomic typed item into the destination runtime memory.
	 * @param src Source string.
	 * @param dst Raw binary location to store the resulting value.
	 * @return Returns true if the operation was successful, false if not successful.
	 */
	virtual daeBool stringToMemory(daeChar* src, daeChar* dst);

	/**
	 * Converts an array of atomic items into a whitespace separated string.
	 * @param array The array of data.
	 * @param buffer The buffer to write into.
	 */
	virtual void arrayToString(daeArray& array, std::ostringstream& buffer);

	/**
	 * Reads a whitespace separated list of atomic items into an array. The array is
	 * cleared before writing into it.
	 * @param src Whitespace separated list of items.
	 * @param array The output array of data.
	 * @return Returns true if the operation was successful, false otherwise.
	 */
	virtual daeBool stringToArray(daeChar* src, daeArray& array);

	/**
	 * Creates a new object of the appropriate type for this daeAtomicType and returns it
	 * as a pointer. The return value must be freed by calling destroy.
	 * @return Returns a pointer to a new value. The memory must be freed by calling destroy.
	 */
	virtual daeMemoryRef create() = 0;

	/**
	 * Deletes an object previously allocated with create.
	 * @param obj The object previously allocated with create.
	 */
	virtual void destroy(daeMemoryRef obj) = 0;

	/**
	 * Creates a daeTArray of the appropriate type (e.g. daeTArray<int>, daeTArray<daeIDRef>)
	 * and returns it as a daeArray*.
	 * @return Returns a daeArray*. This array should be freed by the caller with
	 * operator delete.
	 */
	virtual daeArray* createArray() = 0;

	/**
	 * Performs a virtual comparison operation between two values of the same atomic type.
	 * @param value1 Memory location of the first value.
	 * @param value2 Memory location of the second value.
	 * @return Returns a positive integer if value1 > value2, a negative integer if 
	 * value1 < value2, and 0 if value1 == value2.
	 */
	virtual daeInt compare(daeChar* value1, daeChar* value2);

	/**
	 * Array version of the compare function.
	 * @param value1 First array to compare.
	 * @param value2 Second array to compare.
	 * @return Returns a positive integer if value1 > value2, a negative integer if 
	 * value1 < value2, and 0 if value1 == value2.
	 */
	virtual daeInt compareArray(daeArray& value1, daeArray& value2);

	/**
	 * Performs a virtual copy operation.
	 * @param src Memory location of the value to copy from.
	 * @param dst Memory location of the value to copy to.
	 */
	virtual void copy(daeChar* src, daeChar* dst) = 0;

	/**
	 * Array version of the copy function.
	 * @param src Array to copy from.
	 * @param dst Array to copy to.
	 */
	virtual void copyArray(daeArray& src, daeArray& dst);

	/**
	 * Resolves a reference, if indeed this type is a reference type.
	 * @param element The containing element.
	 * @param src Source of the raw data to resolve.
	 */
	virtual void resolve(daeElementRef element, daeChar* src);
	
	/**
	 * Gets the array of strings as name bindings for this type.
	 * @return Returns the array of strings.
	 */
	daeStringRefArray&	getNameBindings() { return _nameBindings; }

	/**
	 * Gets the enum associated with this atomic type. This is not scalable and only
	 * works for base types, otherwise 'extension' is used.
	 * @return Returns the enum associated with this atomic type.
	 */
	daeEnum				getTypeEnum() { return _typeEnum; }

	/**
	 * Gets the size in bytes for this atomic type.
	 * @return Returns the size of the atomic type in bytes.
	 */
	daeInt				getSize() { return _size; }

	/**
	 * Gets the scanf format used for this type. 
	 * @return Returns the scanf format.
	 * @note
	 * Warning - this field is only for convenience and may not always work.
	 * It is used only when the read functions are left to the base
	 * implementation.
	 */
	daeStringRef		getScanFormat() { return _scanFormat; }

	/**
	 * Gets the printf format used for this type.
	 * @return Returns the printf format.
	 * @note
	 * Warning - this field is only for convenience and may not always work.
	 * It is used only when the print functions are left to the base
	 * implementation.
	 */
	daeStringRef		getPrintFormat() { return _printFormat; }

	/**
	 * Gets the alignment in bytes necessary for this type on this
	 * platform.
	 * @return Returns the alignment in bytes.
	 */
	daeInt				getAlignment() { return _alignment; }

	/**
	 * Gets the string associated with this type.
	 * @return Returns the string associated with this type.
	 */
	daeStringRef		getTypeString() { return _typeString; }

	/**
	 * Performs an alignment based on the alignment for this type.
	 * @param ptr Pointer to be aligned.
	 * @return Returns the aligned pointer computed via
	 * <tt> (ptr+alignment-1)&(~(alignment-1).	</tt>
	 * 
	 */
	daeChar*			align(daeChar* ptr) {
		return (daeChar*)(((intptr_t)(ptr+_alignment-1))&(~(_alignment - 1))); }
	
protected:	
	daeInt					_size;
	daeInt					_alignment;
	daeEnum					_typeEnum;
	daeStringRef			_typeString;
	daeStringRef			_printFormat;
	daeStringRef			_scanFormat;
	//daeStringRefArray		_nameBindings;
	daeInt					_maxStringLength;
	
public:
	/**
	 * An array of strings as name bindings for this type.
	 */
	daeStringRefArray		_nameBindings;

private: // Static Members
	static daeAtomicTypeArray*	_Types;
	static daeBool				_TypesInitialized;
public: // Static Interface
	/** An enum for identifying the different atomic types */
	enum daeAtomicTypes {
		/** bool atomic type */
		BoolType,
		/** enum atomic type */
		EnumType,
		/** character atomic type */
		CharType,
		/** short integer atomic type */
		ShortType,
		/** integer atomic type */
		IntType,
		/** unsigned integer atomic type */
		UIntType,
		/** long integer atomic type */
		LongType,
		/** unsigned long integer atomic type */
		ULongType,
		/** floating point atomic type */
		FloatType,
		/** double precision floating point atomic type */
		DoubleType,
		/** string reference atomic type */
		StringRefType,
		/** element reference atomic type */
		ElementRefType,
		/** memory reference atomic type */
		MemoryRefType,
		/** void reference atomic type */
		RawRefType,
		/** resolver  atomic type */
		ResolverType,
		/** ID resolver atomic type */
		IDResolverType,
		/** string token atomic type */
		TokenType,
		/** extension atomic type */
		ExtensionType
	};

public: // STATIC INTERFACE
	/**
	 * Appends a new type to the global list of types.
	 * @param t Type to append.
	 * @return Returns the index of the type in the list of types.
	 */
	static daeInt				append(daeAtomicType* t);

	/**
	 * Performs a static initialization of all known atomic types.
	 */
	static void					initializeKnownTypes();

	/**
	 * Performs an uninitialization for all known types, freeing associated memory.
	 */
	static void					uninitializeKnownTypes();
	/**
	 * Performs a static initialization of all known base atomic types.
	 */
	static void					initializeKnownBaseTypes();

	/**
	 * Gets a type from the list of types, based on its index.
	 * @param index Index of the type to retrieve.
	 * @return Returns the @c daeAtomicType indicated by index.
	 */
	static const daeAtomicType*	getByIndex(daeInt index);

	/**
	 * Gets the number of known atomic types.
	 * @return Returns the number of known atomic types.
	 */
	static daeInt				getCount();

	/**
	 * Finds a type by its string name.
	 * @param type String name of the type.
	 * @return Returns the type with the corresponding name.
	 */
	static daeAtomicType*		get(daeStringRef type);

	/**
	 * Finds a type by its enum.
	 * @param type Enum representing the desired type.
	 * @return Returns the type with the corresponding enum.
	 */
	static daeAtomicType*		get(daeEnum type);
};

/**
 * The @c daeBoolType class is derived from @c daeAtomicType, and implements
 * the reflective system for objects of type @c daeBool.
 */
class daeBoolType : public daeAtomicType
{
public:
	/**
	 * Constructor
	 */
	daeBoolType();
public:
	virtual daeBool memoryToString(daeChar* src, std::ostringstream& dst);
	
	virtual daeBool stringToMemory(daeChar* src, daeChar* dst);

	virtual daeMemoryRef create();

	virtual void destroy(daeMemoryRef obj);

	virtual void copy(daeChar* src, daeChar* dst);

	virtual daeArray* createArray();
};

/**
 * The @c daeIntType class is derived from @c daeAtomicType, and implements
 * the reflective system for objects of type @c daeInt.
 */
class daeIntType : public daeAtomicType
{
public:
	/**
	 * Constructor
	 */
	daeIntType();
public:
	virtual daeBool memoryToString(daeChar* src, std::ostringstream& dst);

	virtual daeMemoryRef create();

	virtual void destroy(daeMemoryRef obj);

	virtual void copy(daeChar* src, daeChar* dst);

	virtual daeArray* createArray();
};

/**
 * The @c daeLongType class is derived from @c daeAtomicType, and implements
 * the reflective system for objects of type @c daeLong.
 */
class daeLongType : public daeAtomicType
{
public:
	/**
	 * Constructor
	 */
	daeLongType();
public:
	virtual daeBool memoryToString(daeChar* src, std::ostringstream& dst);

	virtual daeMemoryRef create();

	virtual void destroy(daeMemoryRef obj);

	virtual void copy(daeChar* src, daeChar* dst);

	virtual daeArray* createArray();
};

/**
 * The @c daeUIntType class is derived from @c daeAtomicType, and implements
 * the reflective system for objects of type @c daeUInt.
 */
class daeUIntType : public daeAtomicType
{
public:
	/**
	 * Constructor
	 */
	daeUIntType();
public:
	virtual daeBool memoryToString(daeChar* src, std::ostringstream& dst);

	virtual daeMemoryRef create();

	virtual void destroy(daeMemoryRef obj);

	virtual void copy(daeChar* src, daeChar* dst);

	virtual daeArray* createArray();
};

/**
 * The @c daeUIntType class is derived from @c daeAtomicType, and implements
 * the reflective system for objects of type @c daeUInt.
 */
class daeULongType : public daeAtomicType
{
public:
	/**
	 * Constructor
	 */
	daeULongType();
public:
	virtual daeBool memoryToString(daeChar* src, std::ostringstream& dst);

	virtual daeMemoryRef create();

	virtual void destroy(daeMemoryRef obj);

	virtual void copy(daeChar* src, daeChar* dst);

	virtual daeArray* createArray();
};

/**
 * The @c daeShortType is  derived from @c daeAtomicType, and implements
 * the reflective system for objects of type @c daeShort.
 */
class daeShortType : public daeAtomicType
{
public:
	/**
	 * Constructor
	 */
	daeShortType();
public:
	virtual daeBool memoryToString(daeChar* src, std::ostringstream& dst);

	virtual daeMemoryRef create();

	virtual void destroy(daeMemoryRef obj);

	virtual void copy(daeChar* src, daeChar* dst);

	virtual daeArray* createArray();
};

/**
 * The @c daeFloatType is derived from @c daeAtomicType, and implements
 * the reflective system for objects of type @c daeFloat.
 */
class daeFloatType : public daeAtomicType
{
public:
	/**
	 * Constructor
	 */
	daeFloatType();
public:
	virtual daeBool memoryToString(daeChar* src, std::ostringstream& dst);

	virtual daeBool stringToMemory(daeChar* src, daeChar* dst);

	virtual daeMemoryRef create();

	virtual void destroy(daeMemoryRef obj);

	virtual void copy(daeChar* src, daeChar* dst);

	virtual daeArray* createArray();
};

/**
 * The @c daeDoubleType is derived from @c daeAtomicType, and implements
 * the reflective system for objects of type @c daeDouble.
 */
class daeDoubleType : public daeAtomicType
{
public:
	/**
	 * Constructor
	 */
	daeDoubleType();
public:
	virtual daeBool memoryToString(daeChar* src, std::ostringstream& dst);

	virtual daeBool stringToMemory(daeChar* src, daeChar* dst);

	virtual daeMemoryRef create();

	virtual void destroy(daeMemoryRef obj);

	virtual void copy(daeChar* src, daeChar* dst);

	virtual daeArray* createArray();
};

/**
 * The @c daeStringRefType class is derived from @c daeAtomicType, and implements
 * the reflective system for objects of type @c daeStringRef.
 */
class daeStringRefType : public daeAtomicType
{
public:
	/**
	 * Constructor
	 */
	daeStringRefType();
public:
	virtual daeBool memoryToString(daeChar* src, std::ostringstream& dst);

	virtual daeBool stringToMemory(daeChar* src, daeChar* dst);

	virtual daeInt compare(daeChar* value1, daeChar* value2);

	virtual daeMemoryRef create();

	virtual void destroy(daeMemoryRef obj);

	virtual void copy(daeChar* src, daeChar* dst);

	virtual daeArray* createArray();
};

/**
 * The @c daeTokenType class is derived from @c daeStringRefType, and implements
 * the reflective system for objects of type daeStringRef, with specialized
 * treatment from the parser.
 */
class daeTokenType : public daeStringRefType
{
public:
	/**
	 * Constructor
	 */
	daeTokenType();
	
public:
	virtual daeBool stringToMemory(daeChar* src, daeChar* dst);
	
	virtual daeMemoryRef create();

	virtual void destroy(daeMemoryRef obj);

	virtual void copy(daeChar* src, daeChar* dst);

	virtual daeArray* createArray();
};

/**
 * The @c daeElementRefType class is derived from @c  daeAtomicType, and implements
 * the reflective system for objects of type @c daeElementRef.
 */
class daeElementRefType : public daeAtomicType
{
public:
	/**
	 * The @c daeMetaElement for the type this @c daeElementRefType represents.
	 */
	daeMetaElement* _elementType;

public:
	/**
	 * Constructor
	 */
	daeElementRefType();
public:
	virtual daeBool memoryToString(daeChar* src, std::ostringstream& dst);

	virtual daeMemoryRef create();

	virtual void destroy(daeMemoryRef obj);

	virtual void copy(daeChar* src, daeChar* dst);

	virtual daeArray* createArray();
};

/**
 * The @c daeEnumType class is  derived from @c  daeAtomicType, and implements
 * the reflective system for objects of type daeEnum.
 */
class daeEnumType: public daeAtomicType
{
public:
	/**
	 * The array which contains the values used in this enum.
	 */
	daeEnumArray*		_values;
	/**
	 * The array which contains the strings to associate with the values used in this enum.
	 */
	daeStringRefArray*	_strings;
	
public:
	/**
	 * Constructor
	 */
	daeEnumType();

	/**
	 * Destructor
	 */
	~daeEnumType();
	
public:
	virtual daeBool memoryToString(daeChar* src, std::ostringstream& dst);

	virtual daeBool stringToMemory(daeChar* src, daeChar* dst);

	virtual daeMemoryRef create();

	virtual void destroy(daeMemoryRef obj);

	virtual void copy(daeChar* src, daeChar* dst);

	virtual daeArray* createArray();
};

/**
 * The @c daeRawRefType class is  derived from @c daeAtomicType, and implements
 * the reflective system for objects of type @c daeRawRef.
 */
class daeRawRefType: public daeAtomicType
{
public:
	/** 
	*  Constructor.
	*/	
	daeRawRefType();
	
public:
	virtual daeBool memoryToString(daeChar* src, std::ostringstream& dst);

	virtual daeMemoryRef create();

	virtual void destroy(daeMemoryRef obj);

	virtual void copy(daeChar* src, daeChar* dst);

	virtual daeArray* createArray();
};

/**
 * The @c daeResolverType class is derived from @c daeAtomicType, and  implements
 * the reflective system for objects of type @c daeResolver.
 */
class daeResolverType : public daeAtomicType
{
public:
	/** 
	*  Constructor.
	*/	
	daeResolverType();
public:
	virtual daeBool memoryToString(daeChar* src, std::ostringstream& dst);

	virtual daeBool stringToMemory(daeChar* src, daeChar* dst);
	
	virtual void resolve(daeElementRef element, daeChar* src);

	virtual daeMemoryRef create();

	virtual void destroy(daeMemoryRef obj);

	virtual void copy(daeChar* src, daeChar* dst);

	virtual daeArray* createArray();
};

/**
 * The @c daeIDResolverType class is  derived from @c daeAtomicType, and implements
 * the reflective system for objects of type @c daeIDResolver.
 */
class daeIDResolverType : public daeAtomicType
{
public:
	/** 
	*  Constructor.
	*/	
	daeIDResolverType();
public:
	virtual daeBool memoryToString(daeChar* src, std::ostringstream& dst);

	virtual daeBool stringToMemory(daeChar* src, daeChar* dst);
	
	virtual void resolve(daeElementRef element, daeChar* src);

	virtual daeInt compare(daeChar* value1, daeChar* value2);

	virtual daeMemoryRef create();

	virtual void destroy(daeMemoryRef obj);

	virtual void copy(daeChar* src, daeChar* dst);

	virtual daeArray* createArray();
};



#endif // __DAE_ATOMIC_TYPE_H__



