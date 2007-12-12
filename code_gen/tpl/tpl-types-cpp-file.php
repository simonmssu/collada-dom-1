<?php
/* Copyright Sony Computer Entertainment Inc., 2006.
   All Rights Reserved.
   CONFIDENTIAL INFORMATION */

// Grab the file name and save the output
$_file = $_globals['prefix'] . "Types.cpp";
$_bytes = file_put_contents( ($_globals['target_dir'] . $_globals['dom_dir'] . 'src/' . $_file), applyTemplate( 'TYPES_CPP', $bag ) );

//if ( $_bytes > 0 ) { print "Wrote $_bytes bytes to file '$_file'\n"; }

?>