<?php
/* Copyright Sony Computer Entertainment Inc., 2006.
   All Rights Reserved.
   CONFIDENTIAL INFORMATION */

// Grab the file name and save the output
$_file = $_globals['int_prefix'] . ucfirst( $bag['element_name'] ) . ".cpp";
$_bytes = file_put_contents( ($_globals['target_dir'] . $_globals['int_dir'] . $_file), applyTemplate( 'CPP_INT', $bag ) );

//if ( $_bytes > 0 ) { print "Wrote $_bytes bytes to file '$_file'\n"; }

?>