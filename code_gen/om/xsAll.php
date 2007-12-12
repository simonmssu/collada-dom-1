<?php
/* Copyright Sony Computer Entertainment Inc., 2006.
   All Rights Reserved.
   CONFIDENTIAL INFORMATION */

class xsAll extends _elementSet
{
  function xsAll()
  {
    $this->_addElement( 'xsElement', array( 'minOccurs' => '0', 'maxOccurs' => 'unbounded' ) );
    $this->_addElement( 'xsAttribute', array( 'minOccurs' => '0', 'maxOccurs' => 'unbounded' ) );
    
    $this->type[] = "xsAll";
    parent::_elementSet();
  }

  function addAllElement( & $e )
  {
    $this->addElement( $e );
  }  
}

?>