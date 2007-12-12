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
}
?>#ifndef __<?= $_globals['prefix'] . ucfirst( $bag['element_name'] ) ?>_h__
#define __<?= $_globals['prefix'] . ucfirst( $bag['element_name'] ) ?>_h__

#include <dae/daeDocument.h>
#include <<?= $_globals['prefix'] . '/' . $_globals['prefix'] ?>Types.h>
#include <<?= $_globals['prefix'] . '/' . $_globals['prefix'] ?>Elements.h>

<?php
global $includeList;
$includeList = array();
print applyTemplate( 'INCLUDES', $bag ) ?>

<?= applyTemplate( 'CLASS', $bag ) ?>

#endif
