// Copyright 2022 Viatly Volkov (@vlkv)
// SPDX-License-Identifier: GPL-2.0-or-later

/*
qmk compile -kb avalanche/v4 -km cornish
qmk flash -kb avalanche/v4 -km cornish
*/

#include QMK_KEYBOARD_H

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
#define HOME_EQ RCTL_T(KC_EQL)
#define HOME_BS RSFT_T(KC_BSLS)

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
             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX,    XXXXXXX,   XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX,
             GUI_TAB, KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                                        KC_J,       KC_L,      KC_U,       KC_Y,    KC_SCLN, GUI_ESC,
    XXXXXXX, C_CAPS,  HOME_A,  HOME_R,  HOME_S,  HOME_T,  KC_G,                                        KC_M,       HOME_N,    HOME_E,     HOME_I,  HOME_O,  C_SLASH, XXXXXXX,
             KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_K,       KC_H,      KC_GRV,     KC_COMM, KC_DOT,  A_QUOTE,
                                        KC_MUTE, SGUI_1,  KC_SPC,  LSY_ENT, XXXXXXX, XXXXXXX, KC_BSPC, LFN_DEL,    LCAG_1,    KC_HOME
  ),
  [_SYMBOLS] = LAYOUT(
             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX,    XXXXXXX,   XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX,
             _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                        KC_6,       KC_7,      KC_8,       KC_9,    KC_0,    _______,
    XXXXXXX, _______, _______, _______, _______, _______, XXXXXXX,                                     KC_MINS,    HOME_EQ,   HOME_BS,    _______, _______, _______, XXXXXXX,
             _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, S(KC_MINS), S(KC_EQL), S(KC_BSLS), _______, _______, _______,
                                        _______, _______, _______, _______, XXXXXXX, XXXXXXX, _______, _______,    _______,   _______
  ),
  [_NAVIGATION] = LAYOUT(
             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX,    XXXXXXX,   XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX,
             _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                       KC_F6,      KC_F7,     KC_F8,      KC_F9,   KC_F10,  _______,
    XXXXXXX, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,                                     XXXXXXX,    _______,   _______,    _______, _______, _______, XXXXXXX,
             _______, RGB_MOD, RGB_HUI, RGB_M_P, RGB_M_SW,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,   XXXXXXX,    XXXXXXX, XXXXXXX, _______,
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

  void render_layer_alpha(void){
    static const char PROGMEM layer_logo[] = {
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80,
      0xc0, 0xe0, 0x60, 0x70, 0x30, 0x38, 0x30, 0x30, 0x60, 0xe0, 0xc0, 0xc0, 0x80, 0x80, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x78, 0x78, 0xcc, 0xce, 0x86, 0x87, 0x03, 0x01, 0x01,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x86,
      0x86, 0xcc, 0xfc, 0x78, 0x78, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xe0, 0xe0, 0xf0, 0xb0, 0x19, 0x1d, 0x0f, 0x0f, 0x07, 0x0e,
      0x0c, 0x1c, 0x18, 0x38, 0x70, 0x70, 0x70, 0x30, 0x38, 0x1c, 0x1c, 0x0e, 0x06, 0x07, 0x0f, 0x0d,
      0x19, 0x38, 0xb0, 0xf0, 0xe0, 0xc0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xf8,
      0x1c, 0x3c, 0xf8, 0xc0, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0xfc, 0xfc, 0xcc, 0xcc, 0xcc, 0xcc, 0xf8, 0x38, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0xe0,
      0x60, 0x60, 0x60, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xf8, 0x1c, 0x3c, 0xf8, 0xc0,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xc1, 0xe3, 0xe3, 0xf7, 0xfe, 0xfc, 0xfc, 0xfc,
      0xf8, 0xf0, 0xf0, 0xe0, 0xe0, 0xc0, 0xc0, 0xe0, 0xf0, 0xf0, 0xf8, 0xf8, 0xfc, 0xfc, 0xfe, 0xf6,
      0xf3, 0xe3, 0xe1, 0xc1, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0f, 0x07, 0x03,
      0x03, 0x03, 0x03, 0x0f, 0x0e, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x00,
      0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x00,
      0x00, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x0c, 0x0f, 0x07, 0x03, 0x03, 0x03, 0x03, 0x0f,
      0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x07, 0x07, 0x0f, 0x0f, 0x1f, 0x1f, 0x3f, 0x7f,
      0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0x3f, 0x3f, 0x1f, 0x1f,
      0x0f, 0x07, 0x07, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    oled_write_raw_P(layer_logo, sizeof(layer_logo));
  }

  void render_layer_symbols(void){
    static const char PROGMEM layer_logo[] = {
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80,
      0xc0, 0xe0, 0x60, 0x70, 0x30, 0x38, 0x30, 0x30, 0x60, 0xe0, 0xc0, 0xc0, 0x80, 0x80, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x78, 0x78, 0xcc, 0xce, 0x86, 0x87, 0x03, 0x01, 0x01,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x86,
      0x86, 0xcc, 0xfc, 0x78, 0x78, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xe0, 0xe0, 0xf0, 0xf0, 0xf9, 0xfd, 0xff, 0xff, 0xff, 0xfe,
      0xfc, 0xfc, 0xf8, 0xf8, 0xf0, 0xf0, 0xf0, 0xf0, 0xf8, 0xfc, 0xfc, 0xfe, 0xfe, 0xff, 0xff, 0xfd,
      0xf9, 0xf8, 0xf0, 0xf0, 0xe0, 0xc0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x7c, 0x64,
      0xe4, 0xcc, 0xcc, 0xc8, 0x00, 0x00, 0x00, 0x0c, 0x1c, 0x78, 0xf0, 0xe0, 0xf0, 0x3c, 0x1c, 0x04,
      0x00, 0x00, 0x00, 0xfc, 0xfc, 0x7c, 0xf0, 0x80, 0x80, 0xf0, 0x7c, 0xfc, 0xfc, 0x00, 0x00, 0x00,
      0x00, 0xfc, 0xfc, 0x4c, 0x4c, 0x4c, 0xec, 0xfc, 0x98, 0x00, 0x00, 0x00, 0xe0, 0xf8, 0x38, 0x0c,
      0x0c, 0x0c, 0x0c, 0x1c, 0xf8, 0xf0, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x38, 0x7c, 0x64, 0xe4, 0xcc, 0xcc, 0xc8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xc1, 0x63, 0x63, 0x37, 0x3f, 0x1f, 0x1f, 0x1f,
      0x3f, 0x3f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0x3f, 0x1f, 0x1f, 0x1f, 0x1f, 0x37,
      0x73, 0x63, 0xe1, 0xc1, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0e, 0x0c,
      0x0c, 0x0c, 0x0d, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x03, 0x0f, 0x0f, 0x03, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x00,
      0x00, 0x0f, 0x0f, 0x0c, 0x0c, 0x0c, 0x0c, 0x0f, 0x07, 0x00, 0x00, 0x00, 0x01, 0x07, 0x07, 0x0c,
      0x0c, 0x0c, 0x0c, 0x0e, 0x07, 0x01, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
      0x00, 0x00, 0x00, 0x07, 0x0e, 0x0c, 0x0c, 0x0c, 0x0d, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x07, 0x06, 0x0e, 0x0c, 0x18, 0x18, 0x30, 0x70,
      0x60, 0xe0, 0xc0, 0x80, 0x80, 0x01, 0x80, 0x80, 0xc0, 0xc0, 0x60, 0x60, 0x30, 0x38, 0x18, 0x1c,
      0x0c, 0x06, 0x06, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    oled_write_raw_P(layer_logo, sizeof(layer_logo));
  }

  void render_layer_navigation(void){
    static const char PROGMEM layer_logo[] = {
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80,
      0xc0, 0xe0, 0xe0, 0xf0, 0xf0, 0xf8, 0xf0, 0xf0, 0xe0, 0xe0, 0xc0, 0xc0, 0x80, 0x80, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x78, 0x78, 0xfc, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff,
      0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
      0xfe, 0xfc, 0xfc, 0x78, 0x78, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xe0, 0xe0, 0xf0, 0xb0, 0x19, 0x1d, 0x0f, 0x0f, 0x07, 0x0f,
      0x0f, 0x1f, 0x1f, 0x3f, 0x7f, 0x7f, 0x7f, 0x3f, 0x3f, 0x1f, 0x1f, 0x0f, 0x07, 0x07, 0x0f, 0x0d,
      0x19, 0x38, 0xb0, 0xf0, 0xe0, 0xc0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0x38,
      0x70, 0xc0, 0x80, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xf8, 0x1c, 0x3c, 0xf8, 0xc0,
      0x00, 0x00, 0x00, 0x1c, 0xfc, 0xf0, 0x80, 0x00, 0xe0, 0xfc, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xc1, 0x63, 0x63, 0x37, 0x3e, 0x1c, 0x1c, 0x1c,
      0x38, 0x30, 0x70, 0x60, 0xe0, 0xc0, 0xc0, 0xe0, 0x70, 0x70, 0x38, 0x18, 0x1c, 0x1c, 0x1e, 0x36,
      0x73, 0x63, 0xe1, 0xc1, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x00,
      0x00, 0x01, 0x07, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x0c, 0x0f, 0x07, 0x03, 0x03, 0x03, 0x03, 0x0f,
      0x0e, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0f, 0x0f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x07, 0x06, 0x0e, 0x0c, 0x18, 0x18, 0x30, 0x70,
      0x60, 0xe0, 0xc0, 0x80, 0x80, 0x01, 0x80, 0x80, 0xc0, 0xc0, 0x60, 0x60, 0x30, 0x38, 0x18, 0x1c,
      0x0c, 0x06, 0x06, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    oled_write_raw_P(layer_logo, sizeof(layer_logo));
  }

  void process_layer_state(void) {
    switch (get_highest_layer(layer_state)) {
      case _ALPHA:
        render_layer_alpha();
        break;
      case _SYMBOLS:
        render_layer_symbols();
        break;
      case _NAVIGATION:
        render_layer_navigation();
        break;
    }
}

  static void render_status(void) {
    oled_write_P(PSTR(" ------------------\n"), false);
    oled_write_P(PSTR("  Avalanche v4\n"), false);
    oled_write_P(PSTR(" ------------------\n"), false);

    led_t led_state = host_keyboard_led_state();

    oled_write_P(led_state.num_lock ? PSTR("  Num Lock    : /\n") : PSTR("  Num Lock    : X\n"), false);
    oled_write_P(led_state.caps_lock ? PSTR("  Caps Lock   : /\n") : PSTR("  Caps Lock   : X\n"), false);
    oled_write_P(led_state.scroll_lock ? PSTR("  Scroll Lock : /\n") : PSTR("  Scroll Lock : X\n"), false);

    oled_write_P(PSTR("\n\n"), false);
  }

  bool oled_task_kb(void) {
    if (!oled_task_user()) { return false; }
      process_layer_state();
    if (is_keyboard_master()) {
    } else {
      render_status();
    }

    return false;
  }
#endif
