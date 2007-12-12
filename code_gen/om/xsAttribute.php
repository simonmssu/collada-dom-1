<?php
/* Copyright Sony Computer Entertainment Inc., 2006.
   All Rights Reserved.
   CONFIDENTIAL INFORMATION */

class xsAttribute extends _elementSet
{
  function xsAttribute()
  {
    $this->_addAttribute( 'name', array( 'type' => 'xs:string' ) );
    $this->_addAttribute( 'type', array( 'type' => 'xs:string' ) );
    $this->_addAttribute( 'use', array( 'type' => 'xs:string' ) );
    $this->_addAttribute( 'default', array( 'type' => 'xs:string' ) );
    $this->_addAttribute( 'ref', array( 'type' => 'xs:string' ) );
    
    $this->_addElement( 'xsAnnotation', array( 'minOccurs' => '0', 'maxOccurs' => 'unbounded' ) );

    $this->type[] = 'xsAttribute';
    parent::_typedData();
  }
}

?>