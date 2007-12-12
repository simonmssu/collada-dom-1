<?php
/* Copyright Sony Computer Entertainment Inc., 2006.
   All Rights Reserved.
   CONFIDENTIAL INFORMATION */

class xsMinInclusive extends _typedData
{
  function xsMinInclusive()
  {
    $this->_addAttribute( 'value', array( 'type' => 'xs:float' ) );

    $this->type[] = 'xsMinInclusive';
    parent::_typedData();
  }
}

?>