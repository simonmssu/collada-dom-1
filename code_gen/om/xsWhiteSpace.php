<?php
/* Copyright Sony Computer Entertainment Inc., 2006.
   All Rights Reserved.
   CONFIDENTIAL INFORMATION */

class xsWhiteSpace extends _typedData
{
  function xsWhiteSpace()
  {
    $this->_addAttribute( 'value', array( 'type' => 'xs:string' ) );

    $this->type[] = 'xsWhiteSpace';
    parent::_typedData();
  }
}

?>