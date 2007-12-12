<?php
/* Copyright Sony Computer Entertainment Inc., 2006.
   All Rights Reserved.
   CONFIDENTIAL INFORMATION */

class xsSimpleContent extends _elementSet
{
  function xsSimpleContent()
  {
    $this->_addElement( 'xsRestriction', array( 'minOccurs' => '1', 'maxOccurs' => '1' ) );
    $this->_addElement( 'xsExtension', array( 'minOccurs' => '1', 'maxOccurs' => '1' ) );

//    $this->_addAttribute( 'name', array( 'type' => 'xs:string' ) );

    $this->type[] = 'xsSimpleContent';
    parent::_elementSet();
  }
}

?>