<?php
/* Copyright Sony Computer Entertainment Inc., 2006.
   All Rights Reserved.
   CONFIDENTIAL INFORMATION */

class xsRestriction extends _elementSet
{
  function xsRestriction()
  {
    $this->_addElement( 'xsAttribute', array( 'minOccurs' => '0', 'maxOccurs' => 'unbounded' ) );
    $this->_addElement( 'xsMinLength', array( 'minOccurs' => '0', 'maxOccurs' => 'unbounded' ) );
    $this->_addElement( 'xsMaxLength', array( 'minOccurs' => '0', 'maxOccurs' => 'unbounded' ) );
    $this->_addElement( 'xsMinInclusive', array( 'minOccurs' => '0', 'maxOccurs' => 'unbounded' ) );
    $this->_addElement( 'xsMaxInclusive', array( 'minOccurs' => '0', 'maxOccurs' => 'unbounded' ) );
    $this->_addElement( 'xsMinExclusive', array( 'minOccurs' => '0', 'maxOccurs' => 'unbounded' ) );
    $this->_addElement( 'xsMaxExclusive', array( 'minOccurs' => '0', 'maxOccurs' => 'unbounded' ) );
    $this->_addElement( 'xsEnumeration', array( 'minOccurs' => '0', 'maxOccurs' => 'unbounded' ) );
    $this->_addElement( 'xsWhiteSpace', array( 'minOccurs' => '0', 'maxOccurs' => 'unbounded' ) );
    $this->_addElement( 'xsPattern', array( 'minOccurs' => '0', 'maxOccurs' => 'unbounded' ) );

    $this->_addAttribute( 'base', array( 'type' => 'xs:string' ) );

    $this->type[] = 'xsRestriction';
    parent::_elementSet();
  }
}

?>