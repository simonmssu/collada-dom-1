<?php
/* Copyright Sony Computer Entertainment Inc., 2006.
   All Rights Reserved.
   CONFIDENTIAL INFORMATION */

class xsAnnotation extends _elementSet
{
  function xsAnnotation()
  {
    $this->_addElement( 'xsDocumentation', array( 'minOccurs' => '0', 'maxOccurs' => 'unbounded' ) );
    $this->_addElement( 'xsAppinfo', array( 'minOccurs' => '0', 'maxOccurs' => 'unbounded' ) );

    $this->type[] = "xsAnnotation";
    parent::_elementSet();

    // Set bounds on number of elements allowable in annotation element
    $this->setAttribute( 'minOccurs', '0' );
    $this->setAttribute( 'maxOccurs', 'unbounded' );
  }

  function addAnnotationElement( & $e )
  {
    $this->addElement( $e );
  }  
}

?>