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
#include <<?= $_globals['prefix'] ?>/<?= $_globals['prefix'] . ucfirst( $bag['element_name'] ) . ".h" ?>>
#include <<?= $_globals['meta_prefix'] ?>/daeMetaCMPolicy.h>
#include <<?= $_globals['meta_prefix'] ?>/daeMetaSequence.h>
#include <<?= $_globals['meta_prefix'] ?>/daeMetaChoice.h>
#include <<?= $_globals['meta_prefix'] ?>/daeMetaGroup.h>
#include <<?= $_globals['meta_prefix'] ?>/daeMetaAny.h>
#include <<?= $_globals['meta_prefix'] ?>/daeMetaElementAttribute.h>

<?= applyTemplate( 'CPP_METHODS', $bag ) ?>

<?= applyTemplate( 'CPP_STATIC', $bag ) ?>


