<?php
/* Copyright Sony Computer Entertainment Inc., 2006.
   All Rights Reserved.
   CONFIDENTIAL INFORMATION */

// Grab the file name and save the output
$_file = $_globals['prefix'] . ucfirst( $bag['element_name'] ) . ".h";
$_bytes = file_put_contents( ($_globals['target_dir'] . $_globals['dom_dir'] . 'include/' . $_file), applyTemplate( 'HEADER', $bag ) );

//if ( $_bytes > 0 ) { print "dom/" . $_globals['prefix'] . ucfirst( $bag['element_name'] ) . ".obj "; }

?>