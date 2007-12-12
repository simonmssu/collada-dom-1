<?php
/* Copyright Sony Computer Entertainment Inc., 2006.
   All Rights Reserved.
   CONFIDENTIAL INFORMATION */

class xsMaxExclusive extends _typedData
{
  function xsMaxExclusive()
  {
    $this->_addAttribute( 'value', array( 'type' => 'xs:float' ) );

    $this->type[] = 'xsMaxExclusive';
    parent::_typedData();
  }
}

?>