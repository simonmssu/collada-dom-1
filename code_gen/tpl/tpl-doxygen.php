<?php
/* Copyright Sony Computer Entertainment Inc., 2006.
   All Rights Reserved.
   CONFIDENTIAL INFORMATION */

global $indent;
// Add doxygen formatted comments

print $indent ."/**\n";

//$_local_doc = $bag['documentation'][ $_globals['language'] ];
$_local_doc = str_replace( "\n", " ", $bag );
$_local_doc = str_replace( "\t", "", $_local_doc );
while( strlen( $_local_doc ) > 0 )
{
  if ( preg_match( "/(.{0,70}[^\s]*)(\s*)/", $_local_doc, $matches ) )
  {
    // Print blocks of 70 chars thru the next word
    print $indent ." * " . $matches[1] . "\n";
    
    // Account for any newlines
    /*$n_newlines = preg_match_all( "/\n/", $matches[2], $buf );
    if ( $n_newlines > 0 )
    {
      for( $i=0; $i<$n_newlines; $i++ ) { print " * \n"; }
    }*/
        
    // Find more lines...
    $_local_doc = substr( $_local_doc, strlen( $matches[0] ) );
  }
}

print $indent ." */\n";
?>