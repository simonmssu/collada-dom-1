<?php
/* Copyright Sony Computer Entertainment Inc., 2006.
   All Rights Reserved.
   CONFIDENTIAL INFORMATION */

class xsMaxInclusive extends _typedData
{
  function xsMaxInclusive()
  {
    $this->_addAttribute( 'value', array( 'type' => 'xs:float' ) );

    $this->type[] = 'xsMaxInclusive';
    parent::_typedData();
  }
}

?>