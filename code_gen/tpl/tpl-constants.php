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

#ifndef __DOM_CONSTANTS_H__
#define __DOM_CONSTANTS_H__

#include <dae/daeDomTypes.h>

<?php
	foreach ($bag as $name => $val ) {
		if ( is_int($name) ) {
			print $val;
			continue;
		}
		print "extern DLLSPEC daeString ". $name .";\n";
	}
	print "\n";
	
	foreach ($_globals['elementTypes'] as $num => $val )
	{
		print "extern DLLSPEC daeString COLLADA_TYPE_". strtoupper( $val ) .";\n";
	}
	print "\n";
	
	foreach ($_globals['elementNames'] as $num => $val )
	{
		print "extern DLLSPEC daeString COLLADA_ELEMENT_". strtoupper( $val ) .";\n";
	}
?>

#endif //__DOM_CONSTANTS_H__

