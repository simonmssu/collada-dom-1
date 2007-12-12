<?php
/* Copyright Sony Computer Entertainment Inc., 2006.
   All Rights Reserved.
   CONFIDENTIAL INFORMATION */

class xsSchema extends _elementSet
{
  function xsSchema()
  {
    $this->_addElement( 'xsAnnotation', array( 'minOccurs' => '0', 'maxOccurs' => 'unbounded' ) );
    $this->_addElement( 'xsElement', array( 'minOccurs' => '0', 'maxOccurs' => 'unbounded' ) );
    $this->_addElement( 'xsSimpleType', array( 'minOccurs' => '0', 'maxOccurs' => 'unbounded' ) );
    $this->_addElement( 'xsComplexType', array( 'minOccurs' => '0', 'maxOccurs' => 'unbounded' ) );
    $this->_addElement( 'xsGroup', array( 'minOccurs' => '0', 'maxOccurs' => 'unbounded' ) );
    $this->_addElement( 'xsImport', array( 'minOccurs' => '0', 'maxOccurs' => 'unbounded' ) );

    $this->_addAttribute( 'targetNamespace', array( 'type' => 'xs:string' ) );
    $this->_addAttribute( 'elementFormDefault', array( 'type' => 'xs:string' ) );
    $this->_addAttribute( 'xmlns:xs', array( 'type' => 'xs:string' ) );
    $this->_addAttribute( 'xmlns', array( 'type' => 'xs:string' ) );
    $this->_addAttribute( 'version', array( 'type' => 'xs:string' ) );

    $this->type[] = 'xsSchema';
    parent::_elementSet();
  }
}

?>