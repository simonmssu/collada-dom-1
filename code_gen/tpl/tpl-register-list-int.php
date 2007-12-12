<?php
/* Copyright Sony Computer Entertainment Inc., 2006.
   All Rights Reserved.
   CONFIDENTIAL INFORMATION */
?>/* --- DO NOT REMOVE THIS LINE --- SNIP_SDK_COPYRIGHT_C_BEGIN
 * --- DO NOT REMOVE THIS LINE --- SNIP_SDK_COPYRIGHT_C_END */

#include "<?= $_globals['int_prefix'] ?>Includes.h"

void
registerElements()
{
<?= implode( "\n", $_globals['register_list'] ) ?>

}
