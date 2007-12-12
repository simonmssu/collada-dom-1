<?php
/* Copyright Sony Computer Entertainment Inc., 2006.
   All Rights Reserved.
   CONFIDENTIAL INFORMATION */

class xsComplexContent extends _elementSet
{
  function xsComplexContent()
  {
    $this->_addElement( 'xsRestriction', array( 'minOccurs' => '1', 'maxOccurs' => '1' ) );
    $this->_addElement( 'xsExtension', array( 'minOccurs' => '1', 'maxOccurs' => '1' ) );

//    $this->_addAttribute( 'name', array( 'type' => 'xs:string' ) );

    $this->type[] = 'xsComplexContent';
    parent::_elementSet();
  }
}

?>