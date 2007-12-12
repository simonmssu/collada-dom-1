<?php
/* Copyright Sony Computer Entertainment Inc., 2006.
   All Rights Reserved.
   CONFIDENTIAL INFORMATION */

class xsAny extends _typedData
{
  function xsAny()
  {
    $this->_addAttribute( 'namespace', array( 'type' => 'xs:anyURI' ) );
    $this->_addAttribute( 'processContents', array( 'type' => 'xs:string' ) );

	$this->_addAttribute( 'minOccurs', array( 'type' => 'xs:integer' ) );
    $this->setAttribute( 'minOccurs', '1' );
    $this->_addAttribute( 'maxOccurs', array( 'type' => 'xs:integer' ) );
    $this->setAttribute( 'maxOccurs', '1' );
    
    $this->type[] = 'xsAny';
    parent::_typedData();
  }
}

?>