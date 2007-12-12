<?php
/* Copyright Sony Computer Entertainment Inc., 2006.
   All Rights Reserved.
   CONFIDENTIAL INFORMATION */

class xsUnion extends _typedData
{
  function xsUnion()
  {
    $this->_addAttribute( 'memberTypes', array( 'type' => 'xs:string' ) );

    $this->type[] = 'xsUnion';
    parent::_typedData();
  }
}

?>