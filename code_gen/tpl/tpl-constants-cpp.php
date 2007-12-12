<?php
/* Copyright Sony Computer Entertainment Inc., 2006.
   All Rights Reserved.
   CONFIDENTIAL INFORMATION */

if ( $_globals['copyright'] ) {
print $_globals['copyright_text'];
}
else {
?>/* --- DO NOT REMOVE THIS LINE --- SNIP_SDK_COPYRIGHT_C_BEGIN
 * --- DO NOT REMOVE THIS LINE --- SNIP_SDK_COPYRIGHT_C_END */
<?php 
} ?>

#include <dom/domConstants.h>

<?php
	foreach ($bag as $name => $val ) {
		if ( is_int($name) ) {
			print $val;
			continue;
		}
		print "DLLSPEC daeString ". $name ." = ". $val;
	}
	print "\n";
	
	foreach ($_globals['elementTypes'] as $num => $val )
	{
		print "DLLSPEC daeString COLLADA_TYPE_". strtoupper( $val ) ." = \"". $val ."\";\n";
	}
	print "\n";
	
	foreach ($_globals['elementNames'] as $num => $val )
	{
		print "DLLSPEC daeString COLLADA_ELEMENT_". strtoupper( $val ) ." = \"". $val ."\";\n";
	}
?>
