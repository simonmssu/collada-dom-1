<?php
/* Copyright Sony Computer Entertainment Inc., 2007.
   All Rights Reserved.
   CONFIDENTIAL INFORMATION */

  global $meta;
  
  $_context = $bag['context'];
  $_domContext = $bag['context'];
  for( $i=0; $i<count( $_context ); $i++ )
  {
    $_context[$i] = $_globals['int_prefix'] . ucfirst( $_context[$i] );
    $_domContext[$i] = $_globals['prefix'] . ucfirst( $_domContext[$i] );
  }
  $scoped_element = implode( '::', $_context );
  $dom_scoped_element = implode( '::', $_domContext );
  
?>
// CONSTRUCTOR AND DESTRUCTOR
<?= $scoped_element ?>::int<?= ucfirst($bag['element_name']) ?>() {
}

<?= $scoped_element ?>::~int<?= ucfirst($bag['element_name']) ?>() {
}

// IMPORT

void
<?= $scoped_element ?>::createFrom(<?= $_globals['meta_prefix'] ?>ElementRef element)
{
	// INSERT CODE TO CREATE YOUR USER DATA HERE
	// _object = new myRuntimeClass;
}

void
<?= $scoped_element ?>::fromCOLLADA()
{
	// INSERT CODE TO TRANSLATE TO YOUR RUNTIME HERE
	// myRuntimeClassType* local = (myRuntimeClassType*)_object;
	// local->foo = element->foo;
	// local->bar = element->subelem[0]->bar;
}

void
<?= $scoped_element ?>::fromCOLLADAPostProcess()
{
	// INSERT CODE TO POST PROCESS HERE
	// myRuntimeClassType* local = (myRuntimeClassType*)_object;
	// local->renderingContext = MYGLOBAL::getRenderingContext;
	// MYGLOBAL::registerInstance(local);
}

// EXPORT

void
<?= $scoped_element ?>::createTo(void* userData)
{
	// INSERT CODE TO CREATE COLLADA DOM OBJECTS HERE
	// _element = new domGeometry;
	// _object = userData;
}

void
<?= $scoped_element ?>::toCOLLADA()
{
	// INSERT CODE TO TRANSLATE TO YOUR RUNTIME HERE
	// myRuntimeClassType* local = (myRuntimeClassType*)_object;
	// element->foo = local->foo;
	// element->subelem[0]->bar = local->bar;
}

void
<?= $scoped_element ?>::toCOLLADAPostProcess()
{
	// INSERT CODE TO POST PROCESS HERE
	// myRuntimeClassType* local = (myRuntimeClassType*)_object;
	// local->renderingContext = MYGLOBAL::getRenderingContext;
	// MYGLOBAL::registerInstance(local);
}

<?php
  if ( $_globals['full_code'] )
  {
    $_keys = array_keys( $bag['inline_elements'] );
    if ( count( $_keys ) > 0 )
    {
      foreach( $_keys as $_k )
      {
        $inner = $bag['inline_elements'][ $_k ];
        if ( !$inner['complex_type'] || $inner['isRestriction'] || $inner['isExtension'] ) {
			print applyTemplate( 'CPP_INTERFACE_INT', $inner );
		}
      }
    }
  }
?>