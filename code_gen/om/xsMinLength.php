<?php
/* Copyright Sony Computer Entertainment Inc., 2006.
   All Rights Reserved.
   CONFIDENTIAL INFORMATION */

class xsMinLength extends _typedData
{
  function xsMinLength()
  {
    $this->_addAttribute( 'value', array( 'type' => 'xs:integer' ) );

    $this->type[] = 'xsMinLength';
    parent::_typedData();
  }
}

?>