<?php
/* Copyright Sony Computer Entertainment Inc., 2006.
   All Rights Reserved.
   CONFIDENTIAL INFORMATION */

class xsImport extends _typedData
{
  function xsImport()
  {
    $this->_addAttribute( 'namespace', array( 'type' => 'xs:string' ) );
    $this->_addAttribute( 'schemaLocation', array( 'type' => 'xs:string' ) );

    $this->type[] = 'xsImport';
    parent::_typedData();
  }
}

?>