<?php
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

  // shorthand:
  $full_element_name = $_globals['int_prefix'] . ucfirst( $bag['element_name'] );
?>
class <?= $full_element_name ?>;

typedef daeSmartRef<<?= $full_element_name ?>> <?= $full_element_name ?>Ref;
typedef daeTArray<<?= $full_element_name ?>Ref> <?= $full_element_name ?>Array;

<?php
  // DOCUMENTATION
  if ( isset( $bag['documentation'][ $_globals['language'] ] ) )
  {
    print applyTemplate( 'DOXYGEN', $bag['documentation'][ $_globals['language'] ] );
  }
?>
class <?= $full_element_name ?> : public daeIntegrationObject
{
public: // Constuctor and Destructor
	/**
	 * Default Constructor.
	 */
	<?= $full_element_name ?>();
	 
	/**
	 * Default Destructor.
	 */
	~<?= $full_element_name ?>();
	 
protected: // VIRTUAL INTEGRATION INTERFACE

// IMPORT FROM COLLADA	
	// This Method is used to create tool/runtime object
	virtual void createFrom(daeElementRef element);

	// This method translate from COLLADA to tool/runtime object
	virtual void fromCOLLADA();

	// This method is used as a second pass post process on tool/runtime objs
	virtual void fromCOLLADAPostProcess();

// EXPORT TO COLLADA	
	// This Method is used to create COLLADA objects
	virtual void createTo(void* userData);

	// This method translate to COLLADA from tool/runtime object
	virtual void toCOLLADA();

	// This method is used as a second pass post process on COLLADA dom
	virtual void toCOLLADAPostProcess();

public: // STATIC METHODS
	static <?= $_globals['meta_prefix'] ?>ElementRef create();
	static <?= $_globals['meta_prefix'] ?>MetaElement* registerElement(DAE& dae);
	
public: // STATIC MEMBERS
	static <?= $_globals['meta_prefix'] ?>MetaElement* _Meta;

<?php
  // INTERNAL CLASSES
  if ( $_globals['full_code'] )
  {
    $result = '';
    $inlines = array_keys( $bag['inline_elements'] );
    for( $i=0; $i<count( $inlines ); $i++ )
    {
      $inner = $bag['inline_elements'][ $inlines[$i] ];
      if ( !$inner['complex_type'] || $inner['isRestriction'] || $inner['isExtension'] ) {
		$result .= applyTemplate( 'CLASS_INT', $inner );
	  }
    }
    if ( strlen( $result ) > 0 ) { print "public:\n$result\n"; }
  }
?>
};
