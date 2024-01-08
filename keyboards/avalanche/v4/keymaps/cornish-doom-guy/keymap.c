// Copyright 2022 Viatly Volkov (@vlkv)
// SPDX-License-Identifier: GPL-2.0-or-later

/*
qmk compile -kb avalanche/v4 -km cornish
qmk flash -kb avalanche/v4 -km cornish
*/

#include QMK_KEYBOARD_H
#include "doom-guy.c"

enum layer {
  _ALPHA,
  _SYMBOLS,
  _NAVIGATION,
};

// Layers
#define LSY_ENT LT(_SYMBOLS, KC_ENT)
#define LFN_DEL LT(_NAVIGATION, KC_DEL)

// Left-hand home row mods
#define HOME_A LGUI_T(KC_A)
#define HOME_R LALT_T(KC_R)
#define HOME_S LSFT_T(KC_S)
#define HOME_T LCTL_T(KC_T)

// Right-hand home row mods
#define HOME_N RCTL_T(KC_N)
#define HOME_E RSFT_T(KC_E)
#define HOME_I LALT_T(KC_I)
#define HOME_O RGUI_T(KC_O)

// Modifiers
#define GUI_TAB GUI_T(KC_TAB)
#define C_CAPS  CTL_T(KC_CAPS)
#define GUI_ESC GUI_T(KC_ESC)
#define A_QUOTE OPT_T(KC_QUOT)
#define C_SLASH LCTL_T(KC_SLSH)

// Fancy keys
#define SGUI_1  SGUI_T(KC_LBRC)
#define LCAG_1  LCAG_T(KC_RBRC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_ALPHA] = LAYOUT(
             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX,    XXXXXXX,   XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
             GUI_TAB, KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                                        KC_J,       KC_L,      KC_U,       KC_Y,       KC_SCLN,    GUI_ESC,
    XXXXXXX, C_CAPS,  HOME_A,  HOME_R,  HOME_S,  HOME_T,  KC_G,                                        KC_M,       HOME_N,    HOME_E,     HOME_I,     HOME_O,     C_SLASH, XXXXXXX,
             KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_K,       KC_H,      KC_GRV,     KC_COMM,    KC_DOT,     A_QUOTE,
                                        KC_MUTE, SGUI_1,  KC_SPC,  LSY_ENT, XXXXXXX, XXXXXXX, KC_BSPC, LFN_DEL,    LCAG_1,    KC_HOME
  ),
  [_SYMBOLS] = LAYOUT(
             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX,    XXXXXXX,   XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
             _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                        KC_6,       KC_7,      KC_8,       KC_9,       KC_0,       _______,
    XXXXXXX, _______, _______, _______, _______, _______, XXXXXXX,                                     KC_MINS,    KC_EQL,    KC_BSLS,    KC_LBRC,    KC_RBRC,    _______, XXXXXXX,
             _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, S(KC_MINS), S(KC_EQL), S(KC_BSLS), S(KC_LBRC), S(KC_RBRC), _______,
                                        _______, _______, _______, _______, XXXXXXX, XXXXXXX, _______, _______,    _______,   _______
  ),
  [_NAVIGATION] = LAYOUT(
             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX,    XXXXXXX,   XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
             _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                       KC_F6,      KC_F7,     KC_F8,      KC_F9,      KC_F10,     _______,
    XXXXXXX, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,                                     XXXXXXX,    _______,   _______,    _______,    _______,    _______, XXXXXXX,
             _______, RGB_MOD, RGB_HUI, RGB_M_P, RGB_M_SW,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,   XXXXXXX,    XXXXXXX,    XXXXXXX,    _______,
                                        RGB_TOG, _______, _______, _______, XXXXXXX, XXXXXXX, _______, _______,    _______,   _______
  )
};

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { // Encoder on master side
    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }
  }

  else if (index == 1) { // Encoder on slave side
    if(IS_LAYER_ON(_SYMBOLS)) {
      if (clockwise) {
          tap_code(KC_PGUP);
      } else {
          tap_code(KC_PGDN);
      }
    }

    else {
      if (clockwise) {
          tap_code(KC_WH_U);
      } else {
          tap_code(KC_WH_D);
      }
    }
  }

  return true;
}
#endif

#ifdef OLED_ENABLE
  oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
      if (is_keyboard_left()) {
        return OLED_ROTATION_180;
      }

      else {
        return OLED_ROTATION_180;
      }

    } else {
      return OLED_ROTATION_180;
    }
  }

  bool oled_task_user(void) {
    if (is_keyboard_master()) {
      oled_render_anim();
    } else {
      oled_write("Secondary\n", false);
    }
    return false;
  }

#endif
