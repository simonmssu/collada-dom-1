<?php
/* Copyright Sony Computer Entertainment Inc., 2006.
   All Rights Reserved.
   CONFIDENTIAL INFORMATION */

// Grab the file name and save the output
$_file = $_globals['int_prefix'] . ucfirst( $bag['element_name'] ) . ".h";
$_bytes = file_put_contents( ($_globals['int_dir'] . $_file), applyTemplate( 'HEADER_INT', $bag ) );

$_globals['include_list'][] = "#include \"$_file\"";

//if ( $_bytes > 0 ) { print "dom/" . $_globals['prefix'] . ucfirst( $bag['element_name'] ) . ".obj "; }

?>