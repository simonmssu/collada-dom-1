<?php
/* Copyright Sony Computer Entertainment Inc., 2006.
   All Rights Reserved.
   CONFIDENTIAL INFORMATION */

class xsSequence extends _elementSet
{
  function xsSequence()
  {
    $this->_addElement( 'xsElement', array( 'minOccurs' => '0', 'maxOccurs' => 'unbounded' ) );
    $this->_addElement( 'xsAttribute', array( 'minOccurs' => '0', 'maxOccurs' => 'unbounded' ) );
    $this->_addElement( 'xsChoice', array( 'minOccurs' => '0', 'maxOccurs' => 'unbounded' ) );
    $this->_addElement( 'xsSequence', array( 'minOccurs' => '0', 'maxOccurs' => 'unbounded' ) );
    $this->_addElement( 'xsGroup', array( 'minOccurs' => '0', 'maxOccurs' => 'unbounded' ) );
    $this->_addElement( 'xsAny', array( 'minOccurs' => '0', 'maxOccurs' => 'unbounded' ) );
    $this->_addElement( 'xsAnnotation', array( 'minOccurs' => '0', 'maxOccurs' => 'unbounded' ) );
    
    $this->type[] = "xsSequence";
    parent::_elementSet();
  }

  function addSequenceElement( & $e )
  {
    $this->addElement( $e );
  }  
}

?>