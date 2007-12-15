<?php
/*
 * Copyright 2007 Sony Computer Entertainment Inc.
 *
 * Licensed under the SCEA Shared Source License, Version 1.0 (the "License"); you may not use this 
 * file except in compliance with the License. You may obtain a copy of the License at:
 * http://research.scea.com/scea_shared_source_license.html
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License 
 * is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or 
 * implied. See the License for the specific language governing permissions and limitations under the 
 * License. 
 */

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
<?= $scoped_element ?>::create(DAE& dae)
{
	<?= $scoped_element ?>Ref ref = new <?= $scoped_element ?>;
	return ref;
}

<?= $_globals['meta_prefix'] ?>MetaElement *
<?= $scoped_element ?>::registerElement(DAE& dae)
{
    if ( _Meta != NULL ) return _Meta;
    
    _Meta = new daeMetaElement(dae);
    _Meta->setName( "<?= $bag['element_name'] ?>" );
	_Meta->registerClass(<?= $scoped_element ?>::create);

	<?= $dom_scoped_element ?>::_Meta->setMetaIntegration(_Meta);

	_Meta->setElementSize(sizeof(<?= $scoped_element ?>));
	_Meta->validate();

	return _Meta;
}

<?php
  // Add registerElement() call to global list for later use:
  $_globals['register_list'][] = '  ' . $scoped_element . '::registerElement(dae);';

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