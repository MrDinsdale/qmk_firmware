#pragma once

#define MASTER_LEFT

#define LAYER_STATE_8BIT

#define SPLIT_WPM_ENABLE

#ifdef RGB_MATRIX_ENABLE
#   define RGB_MATRIX_HUE_STEP 8
#   define RGB_MATRIX_SAT_STEP 16
#   define RGB_MATRIX_VAL_STEP 16
#   define RGB_MATRIX_SPD_STEP 10

#   define ENABLE_RGB_MATRIX_ALPHAS_MODS
#   define ENABLE_RGB_MATRIX_BREATHING

#   define RGB_MATRIX_KEYPRESSES
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#   define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#endif
