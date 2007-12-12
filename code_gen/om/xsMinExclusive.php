<?php
/* Copyright Sony Computer Entertainment Inc., 2006.
   All Rights Reserved.
   CONFIDENTIAL INFORMATION */

class xsMinExclusive extends _typedData
{
  function xsMinExclusive()
  {
    $this->_addAttribute( 'value', array( 'type' => 'xs:float' ) );

    $this->type[] = 'xsMinExclusive';
    parent::_typedData();
  }
}

?>