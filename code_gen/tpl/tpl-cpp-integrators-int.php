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

?><?= $_globals['meta_prefix'] ?>ElementRef
<?= $scoped_element ?>::create(<?= $_globals['meta_prefix'] ?>Int)
{
	<?= $scoped_element ?>Ref ref = new <?= $scoped_element ?>;
	return ref;
}

<?= $_globals['meta_prefix'] ?>MetaElement *
<?= $scoped_element ?>::registerElement()
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement;
    _Meta->setName( "<?= $bag['element_name'] ?>" );
	_Meta->registerClass(<?= $scoped_element ?>::create, &_Meta);

	<?= $dom_scoped_element ?>::_Meta->setMetaIntegration(_Meta);

	_Meta->setElementSize(sizeof(<?= $scoped_element ?>));
	_Meta->validate();

	return _Meta;
}

<?php
  // Add registerElement() call to global list for later use:
  $_globals['register_list'][] = '  ' . $scoped_element . '::registerElement();';

  // Recurse
  if ( $_globals['full_code'] )
  {
    $_keys = array_keys( $bag['inline_elements'] );
    if ( count( $_keys ) > 0 )
    {
      foreach( $_keys as $_k )
      {
        $inner = $bag['inline_elements'][ $_k ];
        if ( !$inner['complex_type'] || $inner['isRestriction'] || $inner['isExtension'] ) {
			print applyTemplate( 'CPP_INTEGRATORS_INT', $inner );
		}
      }
    }
  }
?>