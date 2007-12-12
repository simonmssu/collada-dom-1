<?php
/* Copyright Sony Computer Entertainment Inc., 2006.
   All Rights Reserved.
   CONFIDENTIAL INFORMATION */

class xsPattern extends _elementSet
{
  function xsPattern()
  {
    $this->_addAttribute( 'value', array( 'type' => 'xs:string' ) );
	
	$this->_addElement( 'xsAnnotation', array( 'minOccurs' => '0', 'maxOccurs' => 'unbounded' ) );
	
    $this->type[] = 'xsPattern';
    parent::_typedData();
  }
}

?>