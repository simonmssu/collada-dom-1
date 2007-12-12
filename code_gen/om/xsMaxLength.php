<?php
/* Copyright Sony Computer Entertainment Inc., 2006.
   All Rights Reserved.
   CONFIDENTIAL INFORMATION */

class xsMaxLength extends _typedData
{
  function xsMaxLength()
  {
    $this->_addAttribute( 'value', array( 'type' => 'xs:integer' ) );

    $this->type[] = 'xsMaxLength';
    parent::_typedData();
  }
}

?>