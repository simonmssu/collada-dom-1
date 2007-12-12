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

#include <<?= $_globals['meta_prefix'] ?>/daeDom.h>
#include "<?= $_globals['int_prefix'] . ucfirst( $bag['element_name'] ) . ".h" ?>"
#include <<?= $_globals['prefix'] ?>/<?= $_globals['prefix'] . ucfirst( $bag['element_name'] ) . ".h" ?>>

<?= applyTemplate( 'CPP_STATIC_INT', $bag ) ?>

// ********************************************************
// ***** GENERATED INTERFACE - do NOT touch ***************
// ********************************************************

<?= applyTemplate( 'CPP_INTEGRATORS_INT', $bag ) ?>

// ********************************************************
// ***** INTEGRATION INTERFACE ****************************
// ********************************************************

<?= applyTemplate( 'CPP_INTERFACE_INT', $bag ) ?>

