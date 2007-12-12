<?php
/* Copyright Sony Computer Entertainment Inc., 2006.
   All Rights Reserved.
   CONFIDENTIAL INFORMATION */

class xsExtension extends _elementSet
{
  function xsExtension()
  {
    $this->_addElement( 'xsAttribute', array( 'minOccurs' => '0', 'maxOccurs' => 'unbounded' ) );
    $this->_addElement( 'xsSequence', array( 'minOccurs' => '0', 'maxOccurs' => 'unbounded' ) );

    $this->_addAttribute( 'base', array( 'type' => 'xs:string' ) );

    $this->type[] = 'xsExtension';
    parent::_elementSet();
  }
}

?>