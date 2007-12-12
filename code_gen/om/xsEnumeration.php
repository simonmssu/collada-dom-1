<?php
/* Copyright Sony Computer Entertainment Inc., 2006.
   All Rights Reserved.
   CONFIDENTIAL INFORMATION */

class xsEnumeration extends _elementSet
{
  function xsEnumeration()
  {
    $this->_addAttribute( 'value', array( 'type' => 'xs:integer' ) );
	
	$this->_addElement( 'xsAnnotation', array( 'minOccurs' => '0', 'maxOccurs' => 'unbounded' ) );
	
    $this->type[] = 'xsEnumeration';
    parent::_typedData();
  }
}

?>