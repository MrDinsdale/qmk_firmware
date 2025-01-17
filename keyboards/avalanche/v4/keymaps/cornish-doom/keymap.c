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
#define HOME_LB LALT_T(KC_LBRC)
#define HOME_RB RGUI_T(KC_RBRC)

// Fancy keys
#define SGUI_1  SGUI_T(KC_LBRC)
#define LCAG_1  LCAG_T(KC_RBRC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_ALPHA] = LAYOUT(
             KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                        KC_6,       KC_7,      KC_8,       KC_9,    KC_0,    XXXXXXX,
             KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                                        KC_J,       KC_L,      KC_U,       KC_Y,    KC_SCLN, KC_ESC,
    XXXXXXX, KC_CAPS, HOME_A,  HOME_R,  HOME_S,  HOME_T,  KC_G,                                        KC_M,       HOME_N,    HOME_E,     HOME_I,  HOME_O,  KC_SLSH, XXXXXXX,
             KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_K,       KC_H,      KC_GRV,     KC_COMM, KC_DOT,  KC_QUOT,
                                        KC_MUTE, SGUI_1,  KC_SPC,  LSY_ENT, XXXXXXX, XXXXXXX, KC_BSPC, LFN_DEL,    LCAG_1,    KC_HOME
  ),
  [_SYMBOLS] = LAYOUT(
             _______, _______, _______, _______, _______, _______,                                     _______,    _______,   _______,    _______, _______, XXXXXXX,
             _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                        KC_6,       KC_7,      KC_8,       KC_9,    KC_0,    _______,
    XXXXXXX, _______, _______, _______, _______, _______, XXXXXXX,                                     KC_MINS,    HOME_EQ,   HOME_BS,    HOME_LB, HOME_RB, _______, XXXXXXX,
             _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, S(KC_MINS), S(KC_EQL), S(KC_BSLS), _______, _______, _______,
                                        _______, _______, _______, _______, XXXXXXX, XXXXXXX, _______, _______,    _______,   _______
  ),
  [_NAVIGATION] = LAYOUT(
             _______, _______, _______, _______, _______, _______,                                     _______,    _______,   _______,    _______, _______, _______,
             _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                       KC_F6,      KC_F7,     KC_F8,      KC_F9,   KC_F10,  _______,
    XXXXXXX, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,                                     XXXXXXX,    _______,   _______,    _______, _______, _______, XXXXXXX,
             _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_VAI, RGB_SPI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,   XXXXXXX,    XXXXXXX, XXXXXXX, _______,
                                        RGB_TOG, _______, _______, _______, XXXXXXX, XXXXXXX, _______, _______,    _______,   _______
  )
};

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { // Encoder on master side
    if (clockwise) {
      tap_code(KC_PGUP);
    } else {
      tap_code(KC_PGDN);
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
  /* KEYBOARD PET START */

  /* settings */
  #    define MIN_WALK_SPEED      15
  #    define MIN_fast_SPEED       35

  /* advanced settings */
  #    define ANIM_FRAME_DURATION 1000  // how long each frame lasts in ms
  #    define ANIM_SIZE           320   // number of bytes in array. If you change sprites, minimize for adequate firmware size. max is 1024

  /* timers */
  uint32_t anim_timer = 0;

  /* current frame */
  uint8_t current_frame = 0;

  /* status variables */
  int current_wpm = 0;
  led_t led_usb_state;

  bool isJumping  = false;
  bool showedJump = true;


  /* logic */
  static void render_doom_guy(int DOOM_X, int DOOM_Y) {
      /* idle */
      static const char PROGMEM idle[3][ANIM_SIZE] = {
      {
        0x00, 0x88, 0x22, 0x80, 0x04, 0x50, 0x02, 0x00, 0x10, 0x44, 0x00, 0x20, 0x04, 0x10, 0x00, 0x04,
        0x80, 0x20, 0x80, 0x64, 0x80, 0x60, 0xa0, 0x20, 0xc0, 0x10, 0x60, 0xd2, 0xe0, 0xd0, 0x20, 0x48,
        0x20, 0x41, 0xa2, 0x01, 0x02, 0x80, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x94, 0x00, 0x48, 0x02, 0x20, 0x08, 0x01, 0x44, 0x00, 0x42, 0xd0, 0x74, 0xe8, 0x3f, 0xec,
        0xbb, 0x06, 0xad, 0xff, 0xae, 0xdf, 0x3e, 0x5f, 0x7e, 0xfd, 0xfb, 0xef, 0xfe, 0x81, 0x2f, 0x0c,
        0x11, 0x00, 0x00, 0xa0, 0x70, 0xff, 0xbf, 0xfe, 0x2d, 0xdb, 0xa6, 0x28, 0x41, 0x00, 0x10, 0x44,
        0x00, 0x28, 0x54, 0xa1, 0xda, 0xa8, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x88, 0x22, 0x00, 0x14, 0x41, 0x00, 0x44, 0x11, 0xa5, 0x7b, 0xff, 0x7d, 0xde, 0x01, 0xf6,
        0xff, 0x08, 0x53, 0xff, 0xeb, 0x56, 0x00, 0x14, 0xa9, 0x7e, 0xbf, 0xff, 0xfe, 0xdf, 0x3c, 0x2a,
        0x1c, 0x28, 0x00, 0x18, 0xa5, 0xfd, 0x4b, 0x94, 0x63, 0x9c, 0x62, 0x9d, 0x60, 0x80, 0x40, 0x00,
        0x04, 0x49, 0x12, 0x24, 0x8b, 0x76, 0x5b, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x24, 0x80, 0x09, 0x20, 0x02, 0x48, 0x00, 0x82, 0x10, 0x01, 0x05, 0x17, 0x2e, 0x3d, 0xea,
        0x1f, 0xf0, 0xa9, 0x7f, 0xf5, 0x7b, 0xfe, 0x3e, 0xfd, 0x3f, 0xef, 0x7f, 0xf3, 0x8c, 0x71, 0xb8,
        0x44, 0xe0, 0x00, 0x02, 0x0f, 0xff, 0xfd, 0x3f, 0xec, 0x5b, 0xa4, 0x4a, 0x11, 0x24, 0x02, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x04, 0x03, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x92, 0x00, 0x24, 0x81, 0x08, 0x20, 0x82, 0x00, 0x28, 0x01, 0x00, 0x48, 0x02, 0x00, 0x20,
        0x00, 0x04, 0x01, 0x42, 0x05, 0x02, 0x06, 0x01, 0x04, 0x03, 0x04, 0x93, 0x07, 0x85, 0x02, 0x06,
        0x10, 0xc2, 0x01, 0xc0, 0x00, 0x04, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
      },
      {
        0x00, 0x88, 0x22, 0x80, 0x04, 0x50, 0x02, 0x00, 0x10, 0x44, 0x00, 0x20, 0x04, 0x10, 0x00, 0x04,
        0x80, 0x20, 0x80, 0x64, 0x80, 0x60, 0xa0, 0x20, 0xc0, 0x10, 0x60, 0xd2, 0xa0, 0xf0, 0x40, 0x28,
        0x20, 0x41, 0x82, 0x41, 0x02, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x94, 0x00, 0x48, 0x02, 0x20, 0x08, 0x01, 0x44, 0x00, 0xa2, 0xc0, 0x74, 0xf4, 0x5d, 0xb6,
        0xed, 0x16, 0x4b, 0xbf, 0xee, 0xdf, 0x2e, 0x3f, 0xfe, 0x7d, 0xfb, 0xef, 0xfb, 0x86, 0x4d, 0x1d,
        0x10, 0x10, 0x00, 0x80, 0xc0, 0xe0, 0xfa, 0x3d, 0xef, 0x1a, 0xe5, 0x2a, 0x41, 0x00, 0x10, 0x40,
        0x04, 0x28, 0x50, 0x25, 0xfa, 0xa0, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x88, 0x22, 0x00, 0x94, 0x01, 0x40, 0x14, 0x01, 0x6a, 0xdd, 0x7f, 0xff, 0x5c, 0x81, 0x6e,
        0xff, 0x20, 0x4b, 0xff, 0xf5, 0x4b, 0x00, 0x94, 0x2a, 0xfd, 0xbf, 0xff, 0xfd, 0x3e, 0xac, 0x1a,
        0x00, 0x00, 0x18, 0xad, 0xfd, 0xbf, 0xea, 0x01, 0xde, 0x21, 0xde, 0x22, 0xe8, 0x00, 0x40, 0x08,
        0x04, 0x41, 0x0a, 0x15, 0xa6, 0x55, 0xbf, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x88, 0x22, 0x00, 0x94, 0x00, 0x42, 0x10, 0x01, 0x20, 0x02, 0x05, 0x1b, 0x2f, 0x1c, 0xf7,
        0x1b, 0xf0, 0xad, 0x7b, 0xf7, 0x7d, 0xfa, 0x3c, 0xff, 0x3e, 0xef, 0xff, 0x73, 0xc5, 0x38, 0xf8,
        0x20, 0x50, 0x00, 0x05, 0x07, 0xff, 0x7d, 0xff, 0x2c, 0xfb, 0x04, 0x79, 0x02, 0x24, 0x01, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x0a, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x48, 0x02, 0x10, 0x44, 0x00, 0x12, 0x80, 0x08, 0x41, 0x04, 0x20, 0x00, 0x09, 0x40, 0x00,
        0x20, 0x04, 0x01, 0x02, 0x86, 0x01, 0x06, 0x80, 0x03, 0x04, 0x02, 0x97, 0x05, 0x83, 0x16, 0x02,
        0x04, 0xc2, 0x05, 0xc0, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
      }
    };

      /* Walk */
      static const char PROGMEM walk[2][ANIM_SIZE] =  {
        {
          0x00, 0x88, 0x22, 0x80, 0x04, 0x50, 0x02, 0x00, 0x10, 0x44, 0x00, 0x20, 0x04, 0x10, 0x00, 0x84,
          0x20, 0x00, 0x60, 0x84, 0x70, 0x88, 0x60, 0xa8, 0xe0, 0xd8, 0x60, 0xa8, 0x41, 0x32, 0x40, 0xa2,
          0xc0, 0xc1, 0x02, 0xc1, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x80,
          0x40, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x94, 0x00, 0x48, 0x02, 0x20, 0x08, 0x01, 0x64, 0x40, 0x32, 0x6c, 0x78, 0x27, 0x9a, 0x25,
          0x4e, 0x3b, 0x1f, 0x1e, 0xbf, 0x5d, 0xff, 0xff, 0xeb, 0x84, 0x25, 0x0c, 0x03, 0x02, 0x1d, 0x03,
          0x0f, 0x02, 0x01, 0x40, 0x88, 0x90, 0xa0, 0x18, 0x68, 0x90, 0x68, 0xb0, 0xe8, 0xd0, 0xa7, 0xa8,
          0xed, 0xda, 0xa5, 0x7a, 0xc5, 0x3c, 0xc1, 0x90, 0x80, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x88, 0x22, 0x80, 0x08, 0x21, 0x08, 0x14, 0x1c, 0x3c, 0xbd, 0x08, 0x00, 0x3e, 0x88, 0x00,
          0x00, 0x10, 0x3c, 0x5e, 0xbd, 0x7f, 0xff, 0xff, 0xff, 0xff, 0x14, 0x0a, 0x00, 0x40, 0x70, 0x08,
          0x14, 0x8c, 0x08, 0x85, 0x08, 0xc0, 0x00, 0xa1, 0x52, 0xa1, 0xda, 0xa5, 0xda, 0x7f, 0xee, 0x7f,
          0xff, 0x7e, 0xff, 0x57, 0xbd, 0xf3, 0xa4, 0x69, 0x80, 0x61, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x94, 0x00, 0x08, 0xa2, 0x00, 0x10, 0x00, 0x22, 0x86, 0x0b, 0x1e, 0x36, 0x5a, 0xa4, 0x58,
          0xe6, 0x3a, 0xfc, 0xb8, 0x7e, 0xbd, 0xff, 0xff, 0xb6, 0x41, 0xb4, 0x28, 0xc0, 0x40, 0x37, 0xfd,
          0xfe, 0xff, 0x8a, 0x02, 0x01, 0x00, 0x09, 0x00, 0x09, 0x05, 0x49, 0x0e, 0x49, 0x17, 0x68, 0x07,
          0x59, 0x27, 0x88, 0x23, 0x95, 0x48, 0x25, 0x08, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x88, 0x22, 0x00, 0x14, 0x40, 0x01, 0x04, 0x50, 0x00, 0x02, 0x90, 0x01, 0x08, 0x80, 0x00,
          0x22, 0x00, 0x06, 0x10, 0x07, 0x08, 0x07, 0x11, 0x07, 0x0b, 0x86, 0x09, 0x56, 0x80, 0x43, 0x05,
          0x83, 0x40, 0x85, 0x41, 0xc0, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x02,
          0x04, 0x01, 0x04, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
        {
          0x00, 0x88, 0x22, 0x80, 0x04, 0x50, 0x02, 0x00, 0x10, 0x44, 0x00, 0x20, 0x84, 0x80, 0x20, 0xc4,
          0xa0, 0x40, 0xe0, 0xa4, 0xd0, 0xe8, 0xe0, 0xe8, 0xe0, 0x28, 0x50, 0x24, 0x10, 0x00, 0x34, 0x00,
          0x90, 0xe0, 0xa8, 0x40, 0x10, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x10, 0xa0, 0x50,
          0x80, 0x60, 0x80, 0x20, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x94, 0x00, 0x48, 0x02, 0x20, 0x08, 0x01, 0x10, 0x1a, 0x94, 0x1d, 0x16, 0x99, 0x27, 0x00,
          0x1f, 0x13, 0x0f, 0x87, 0x3f, 0xdf, 0xff, 0xff, 0xf5, 0xe0, 0x0c, 0x04, 0x00, 0x00, 0x10, 0x06,
          0x0c, 0x01, 0x00, 0x20, 0x48, 0x24, 0x48, 0x24, 0x9e, 0x60, 0x9e, 0xb8, 0x72, 0xec, 0xb1, 0xea,
          0xf5, 0xda, 0xf7, 0x58, 0xf7, 0x88, 0x72, 0xa4, 0x40, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x48, 0x02, 0x10, 0x40, 0x05, 0x08, 0x02, 0x8f, 0x0f, 0xde, 0x82, 0x00, 0xae, 0x05, 0x00,
          0x80, 0x04, 0x0f, 0x2e, 0x9f, 0xbf, 0x5f, 0xff, 0xff, 0x7f, 0x05, 0x0a, 0x00, 0x10, 0xec, 0x0a,
          0xc6, 0x83, 0x62, 0x82, 0x40, 0x52, 0x20, 0x48, 0x70, 0x8d, 0x70, 0x6e, 0xd3, 0x7f, 0x96, 0xff,
          0x7f, 0xaf, 0x7f, 0x95, 0x7f, 0xd4, 0x39, 0x54, 0x22, 0x89, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x44, 0x11, 0x80, 0x24, 0x01, 0x08, 0xa0, 0x01, 0x05, 0x21, 0x0f, 0x17, 0x2a, 0x15, 0x2c,
          0x59, 0xbf, 0x16, 0xbf, 0xbe, 0x2f, 0xff, 0x7f, 0xfd, 0xe8, 0x51, 0x82, 0x00, 0x84, 0x79, 0x6f,
          0xff, 0x4f, 0x55, 0x40, 0x80, 0x00, 0x02, 0x00, 0x02, 0x04, 0x23, 0x02, 0x17, 0x22, 0x15, 0x25,
          0x19, 0x02, 0xad, 0x40, 0x15, 0xa2, 0x08, 0x0b, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x12, 0x40, 0x04, 0x90, 0x01, 0x48, 0x00, 0x24, 0x00, 0x81, 0x08, 0x20, 0x01, 0x10, 0x04,
          0x00, 0x40, 0x01, 0x08, 0x03, 0x24, 0x01, 0x0a, 0x25, 0x01, 0x2d, 0x13, 0xe4, 0x19, 0x42, 0x0d,
          0x4a, 0x18, 0xa9, 0x60, 0x40, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        }
      };

      static const char PROGMEM fast[2][ANIM_SIZE] = {
      {
        0x00, 0x88, 0x22, 0x80, 0x04, 0x50, 0x02, 0x00, 0x10, 0x44, 0x00, 0x20, 0x04, 0x10, 0x00, 0x04,
        0x80, 0x00, 0xa0, 0x44, 0xa0, 0x00, 0x60, 0x80, 0xd0, 0x20, 0xe0, 0x20, 0x02, 0x80, 0x20, 0xc0,
        0x00, 0x80, 0x01, 0x82, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x94, 0x00, 0x48, 0x02, 0x20, 0x08, 0x01, 0x04, 0x00, 0x32, 0x60, 0x70, 0x00, 0x13, 0x00,
        0x02, 0x11, 0x12, 0x2d, 0x1c, 0x76, 0xfd, 0xfb, 0xd4, 0x81, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x90, 0x10, 0x60, 0x90, 0x60, 0x90, 0xe0, 0x02, 0xc8,
        0xa2, 0xed, 0x10, 0xe5, 0x48, 0x94, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x88, 0x22, 0x00, 0x48, 0x01, 0x00, 0x00, 0x00, 0x00, 0xbc, 0x00, 0x00, 0x14, 0x08, 0x00,
        0x00, 0x00, 0x1c, 0x3a, 0x3c, 0xff, 0xbe, 0xff, 0xff, 0x7e, 0x08, 0x00, 0x00, 0x00, 0xe0, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x20, 0xc2, 0x10, 0xc5, 0x3a, 0xe5, 0x1e, 0xef,
        0x7e, 0xdf, 0x3b, 0xee, 0x11, 0xf6, 0x40, 0xa2, 0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x88, 0x22, 0x00, 0x89, 0x20, 0x00, 0x10, 0x81, 0x02, 0x0e, 0x02, 0x0f, 0x00, 0x00, 0x40,
        0x80, 0x40, 0x40, 0x40, 0xc0, 0x26, 0xcb, 0xdf, 0xc5, 0x01, 0x80, 0x00, 0x00, 0x80, 0x02, 0x40,
        0x80, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x09, 0x0a, 0x05, 0x18, 0x47, 0x02,
        0x15, 0x21, 0x04, 0x01, 0x84, 0x21, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x88, 0x22, 0x80, 0x08, 0x22, 0x00, 0x48, 0x02, 0x80, 0x10, 0x42, 0x00, 0x08, 0x40, 0x04,
        0x00, 0x40, 0x01, 0x06, 0x00, 0x45, 0x00, 0x03, 0x04, 0x03, 0x04, 0x03, 0x88, 0x00, 0x82, 0x01,
        0x04, 0x00, 0x80, 0x40, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
      },
      {
        0x00, 0x88, 0x22, 0x80, 0x04, 0x50, 0x02, 0x00, 0x10, 0x44, 0x00, 0x20, 0x04, 0x80, 0x00, 0xa4,
        0x40, 0x80, 0xe0, 0x84, 0x20, 0xe0, 0x60, 0xe0, 0xa0, 0x20, 0x40, 0x20, 0x00, 0x00, 0x20, 0x00,
        0x00, 0x20, 0x40, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00,
        0x40, 0x00, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x94, 0x00, 0x48, 0x02, 0x10, 0x00, 0x01, 0x10, 0x00, 0x1c, 0x18, 0x14, 0x08, 0x10, 0x00,
        0x05, 0x00, 0x0e, 0x05, 0x8f, 0x5f, 0xfd, 0xff, 0x74, 0xc0, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x20, 0x04, 0x48, 0x14, 0xa8, 0x10, 0xf4, 0x48, 0xb0, 0xc3,
        0xf8, 0xa7, 0xd8, 0x62, 0x95, 0x68, 0x80, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x88, 0x22, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x88, 0x97, 0x80, 0x80, 0x06, 0x08, 0x00,
        0x00, 0x00, 0x0e, 0x07, 0x3e, 0x8f, 0xbf, 0xff, 0xef, 0x3f, 0x02, 0x00, 0x00, 0x00, 0xb8, 0x00,
        0x00, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x20, 0x50, 0x08, 0x64, 0x51, 0xaa, 0x77, 0x8a, 0xbf,
        0x6f, 0x56, 0x3f, 0x4b, 0x34, 0x6d, 0x10, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x88, 0x22, 0x00, 0x89, 0x20, 0x00, 0x84, 0x20, 0x00, 0x03, 0x02, 0x07, 0x00, 0x30, 0x00,
        0x30, 0x40, 0xb0, 0x20, 0x50, 0x34, 0x31, 0xff, 0xb0, 0xe1, 0x40, 0x00, 0x10, 0x00, 0xa0, 0x30,
        0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x02, 0x26, 0x01, 0x22,
        0x09, 0x01, 0x08, 0x41, 0x00, 0x24, 0x01, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x48, 0x02, 0x88, 0x20, 0x02, 0x48, 0x00, 0x24, 0x00, 0x11, 0x80, 0x04, 0x20, 0x00, 0x08,
        0x00, 0x40, 0x04, 0x01, 0x80, 0x01, 0x08, 0x01, 0x00, 0x05, 0x01, 0x15, 0x60, 0x11, 0x04, 0x08,
        0x09, 0x18, 0x20, 0x20, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
      }
    };

      static const char PROGMEM bark[2][ANIM_SIZE] = {
        {
          0x00, 0x88, 0x22, 0x80, 0x04, 0x50, 0x02, 0x00, 0x10, 0x44, 0x00, 0x20, 0x04, 0x10, 0x80, 0x04,
          0xa0, 0x40, 0x20, 0x64, 0x00, 0xa0, 0x10, 0x40, 0x20, 0xd0, 0xa0, 0x62, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x42, 0x81, 0x40, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x94, 0x00, 0x48, 0x02, 0x20, 0x08, 0x81, 0x24, 0x50, 0x20, 0x1c, 0x42, 0x1c, 0x23, 0x84,
          0x0b, 0x00, 0x07, 0x0d, 0x66, 0x2b, 0x8f, 0x2e, 0x1d, 0xf6, 0x7c, 0x01, 0x02, 0x00, 0x00, 0x60,
          0xc0, 0xf4, 0xff, 0x5e, 0xbb, 0x44, 0x35, 0x08, 0x14, 0x00, 0x04, 0x80, 0x00, 0x80, 0x00, 0xa0,
          0x4a, 0xd0, 0x24, 0xc9, 0x34, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x48, 0x02, 0x10, 0x40, 0x05, 0x10, 0x44, 0x18, 0xbf, 0x3c, 0x28, 0x08, 0x00, 0xb5, 0x5e,
          0xff, 0x22, 0x1c, 0x62, 0x1e, 0x6c, 0x3b, 0x7e, 0x7f, 0x9c, 0x7d, 0x08, 0x20, 0x00, 0x00, 0x28,
          0xbd, 0xd2, 0xad, 0x41, 0xa2, 0x08, 0x90, 0x08, 0x08, 0x00, 0x00, 0x80, 0x00, 0x42, 0x00, 0x2c,
          0x53, 0x04, 0xfb, 0x04, 0xbb, 0x48, 0x12, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0xa4, 0x01, 0x44, 0x10, 0x01, 0x44, 0x10, 0x01, 0x8e, 0x00, 0x1c, 0x22, 0x58, 0xa0, 0x69,
          0x80, 0x60, 0x90, 0x72, 0xa4, 0xfa, 0x31, 0xfa, 0x2c, 0xbb, 0xaf, 0x40, 0x00, 0x40, 0x00, 0x02,
          0x07, 0x15, 0xff, 0xbe, 0x75, 0x4a, 0x90, 0x29, 0x04, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x01, 0x2a, 0x04, 0x21, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x44, 0x10, 0x02, 0xa0, 0x09, 0x00, 0x90, 0x02, 0x48, 0x00, 0x20, 0x02, 0x08, 0x00, 0x44,
          0x01, 0x02, 0x84, 0x03, 0x04, 0x02, 0x40, 0x04, 0x03, 0x04, 0x03, 0x44, 0x02, 0x80, 0x00, 0x00,
          0x00, 0x40, 0x82, 0x40, 0x81, 0x04, 0x00, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        },
        {
          0x00, 0x88, 0x22, 0x80, 0x04, 0x50, 0x02, 0x00, 0x10, 0x44, 0x00, 0x20, 0x04, 0x10, 0x80, 0x04,
          0xa0, 0x40, 0x20, 0xe4, 0x80, 0x20, 0x90, 0xc0, 0xa0, 0x50, 0x20, 0xe2, 0x80, 0x80, 0x00, 0x00,
          0x00, 0x42, 0x81, 0x40, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x94, 0x00, 0x48, 0x02, 0xa0, 0xc8, 0xc1, 0xa4, 0x50, 0x28, 0x1c, 0x42, 0x1c, 0x23, 0x85,
          0x0b, 0x00, 0x0e, 0x1c, 0x66, 0x2b, 0x0f, 0x2e, 0x1d, 0xf6, 0x7c, 0x01, 0x02, 0x10, 0x00, 0x40,
          0xe0, 0xe0, 0xff, 0x1e, 0x5b, 0x24, 0x35, 0x08, 0x14, 0x00, 0x04, 0x80, 0x00, 0x88, 0x00, 0xa0,
          0x4a, 0xd0, 0x24, 0xc9, 0xa4, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x48, 0x02, 0x10, 0xbc, 0xfd, 0xf7, 0xc5, 0x7b, 0x81, 0x80, 0x00, 0x00, 0x00, 0xa5, 0x46,
          0xff, 0x20, 0x22, 0x5e, 0x10, 0x6c, 0x3a, 0x7e, 0x7f, 0x9c, 0xfd, 0x88, 0x20, 0x00, 0x00, 0x28,
          0x3d, 0x2c, 0x73, 0x51, 0xad, 0x08, 0x50, 0x88, 0x08, 0x00, 0x00, 0x80, 0x00, 0x52, 0x00, 0x2c,
          0x57, 0x04, 0x03, 0x03, 0xa4, 0xe9, 0xf3, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0xa4, 0x01, 0x44, 0x13, 0x07, 0x4b, 0x0a, 0x36, 0xae, 0x34, 0x6c, 0x7a, 0x38, 0xc0, 0x69,
          0x80, 0x60, 0x90, 0x72, 0xa4, 0xfa, 0x31, 0xfa, 0x2c, 0xbb, 0xa0, 0x5d, 0x29, 0x60, 0x00, 0x00,
          0x06, 0x19, 0xff, 0xbe, 0x75, 0x4a, 0x90, 0x28, 0x04, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x01, 0x2a, 0x04, 0x20, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x44, 0x10, 0x02, 0xa0, 0x09, 0x00, 0x90, 0x02, 0x48, 0x00, 0x20, 0x02, 0x08, 0x00, 0x44,
          0x01, 0x02, 0x84, 0x03, 0x04, 0x02, 0x40, 0x04, 0x03, 0x04, 0x03, 0x44, 0x00, 0x82, 0x04, 0x06,
          0x00, 0x40, 0x82, 0x40, 0x81, 0x04, 0x00, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        }
      };

    /* animation */
    void animate_doom_guy(void) {
      /* jump */
      if (isJumping || !showedJump) {
        /* clear */
        oled_set_cursor(DOOM_X, DOOM_Y + 2);
        oled_write("     ", false);

        oled_set_cursor(DOOM_X, DOOM_Y - 1);

        showedJump = true;
      } else {
        /* clear */
        oled_set_cursor(DOOM_X, DOOM_Y - 1);
        oled_write("     ", false);

        oled_set_cursor(DOOM_X, DOOM_Y);
      }

      /* switch frame */
      current_frame = (current_frame + 1) % 2;

      /* current status */
      if (led_usb_state.caps_lock) {
        oled_write_raw_P(bark[current_frame], ANIM_SIZE);
      } else
      if (current_wpm <= MIN_WALK_SPEED) {
        oled_write_raw_P(idle[current_frame], ANIM_SIZE);

      } else if (current_wpm <= MIN_fast_SPEED) {
        oled_write_raw_P(walk[current_frame], ANIM_SIZE);

      } else {
        oled_write_raw_P(fast[current_frame], ANIM_SIZE);
      }
    }

    #if OLED_TIMEOUT > 0
      if (last_input_activity_elapsed() > OLED_TIMEOUT && last_led_activity_elapsed() > OLED_TIMEOUT) {
        oled_off();
        return;
      } else {
        oled_on();
      }
    #endif

    /* animation timer */
    if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
      anim_timer = timer_read32();
      animate_doom_guy();
    }
  }

  void render_logo(void){
    static const char PROGMEM layer_logo[] = {
        0x00, 0x88, 0x22, 0x80, 0x04, 0x50, 0x02, 0x00, 0x10, 0x44, 0x00, 0xa2, 0x7e, 0x7e, 0xde, 0xfc,
        0xf8, 0x78, 0xf8, 0xf8, 0x58, 0xf0, 0xb0, 0xf0, 0xe0, 0x70, 0xe0, 0xa0, 0x60, 0xc0, 0x00, 0xc0,
        0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x94, 0x00, 0x48, 0x02, 0x20, 0x08, 0x01, 0x44, 0x00, 0x08, 0x41, 0x05, 0x0b, 0x1d, 0x26,
        0xc3, 0xe8, 0x7b, 0x5f, 0xff, 0x3b, 0x6f, 0xff, 0xfe, 0xf7, 0xbf, 0xff, 0xcc, 0xf7, 0x2c, 0xd9,
        0xaa, 0x58, 0x14, 0x19, 0x12, 0x3a, 0x15, 0x32, 0x24, 0x31, 0x2a, 0x60, 0x54, 0x40, 0x48, 0xc0,
        0xc0, 0x20, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x88, 0x22, 0x00, 0x14, 0x41, 0x00, 0x84, 0x11, 0x80, 0x08, 0x42, 0x00, 0x01, 0x48, 0x00,
        0x20, 0x01, 0x05, 0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0xa5, 0x1f, 0x3f, 0x3a, 0x3f, 0x37, 0x2e,
        0x3d, 0x71, 0x3d, 0x42, 0x75, 0x40, 0x4a, 0x50, 0xa0, 0xc2, 0x8c, 0xd0, 0xa4, 0xd0, 0x84, 0x40,
        0x84, 0x87, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x24, 0x00, 0x49, 0x00, 0x92, 0x00, 0x20, 0x04, 0x90, 0x00, 0x08, 0x42, 0x00, 0x00, 0x48,
        0x02, 0x00, 0x40, 0x08, 0x00, 0x00, 0x04, 0xc0, 0xe0, 0xd0, 0xf8, 0xec, 0xfe, 0xff, 0xbb, 0xef,
        0xb7, 0xfa, 0x4d, 0x76, 0x4a, 0x44, 0x52, 0x44, 0x40, 0x40, 0xd0, 0x20, 0xcc, 0xd0, 0x84, 0xd1,
        0x80, 0x81, 0x01, 0x01, 0x01, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x89, 0x20, 0x82, 0x08, 0x20, 0x02, 0x48, 0x00, 0x82, 0x10, 0x40, 0x02, 0x10, 0x00, 0x02,
        0x20, 0x00, 0x04, 0x40, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x1d, 0x1f, 0x7e, 0xef, 0xbf, 0xf6,
        0x4f, 0x94, 0x04, 0xa4, 0x44, 0xd4, 0x14, 0xd4, 0x14, 0x44, 0x38, 0x44, 0x04, 0x08, 0x84, 0x08,
        0x04, 0x07, 0x00, 0x00, 0x00, 0x80, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x44, 0x10, 0x04, 0x40, 0x09, 0x80, 0x24, 0x00, 0x10, 0x84, 0x00, 0x42, 0x00, 0x11, 0x00,
        0x80, 0x11, 0x00, 0x08, 0x00, 0x00, 0x01, 0x10, 0x00, 0x88, 0xc4, 0x6c, 0xf4, 0xfc, 0xad, 0xfd,
        0x55, 0xb4, 0x45, 0x0d, 0x55, 0xb5, 0x45, 0xb5, 0x55, 0xa5, 0x4d, 0x91, 0x45, 0x15, 0x84, 0x45,
        0x05, 0x05, 0x05, 0x01, 0x05, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x24, 0x81, 0x08, 0x22, 0x00, 0x44, 0x00, 0x12, 0x00, 0x20, 0x04, 0x10, 0x00, 0x89, 0x00,
        0x00, 0x20, 0x04, 0x00, 0x80, 0x00, 0x04, 0x0c, 0x17, 0x3f, 0xf7, 0xff, 0xf7, 0xff, 0xbd, 0xf7,
        0x7f, 0xd9, 0xb1, 0x71, 0x90, 0x31, 0x91, 0x11, 0x10, 0x11, 0x11, 0xb1, 0x19, 0xd1, 0x18, 0x01,
        0x1d, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x22, 0x08, 0x40, 0x05, 0x90, 0x00, 0x21, 0x04, 0x10, 0x81, 0x08, 0x00, 0x22, 0x00, 0x00,
        0x24, 0x00, 0x01, 0x00, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x80, 0xc0, 0xe3, 0x66, 0xe3, 0x67,
        0xe1, 0xe3, 0x63, 0xb0, 0xe3, 0x30, 0xa2, 0x31, 0x90, 0x30, 0x10, 0x10, 0x52, 0x90, 0x51, 0x18,
        0x10, 0x08, 0x18, 0x0a, 0x08, 0x0c, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x49, 0x00, 0x92, 0x00, 0x24, 0x00, 0x88, 0x01, 0x24, 0x00, 0x00, 0x48, 0x01, 0x84, 0x40,
        0x00, 0x89, 0x80, 0x04, 0x00, 0x00, 0x00, 0x04, 0x89, 0x8e, 0x87, 0xcf, 0xc6, 0x47, 0xe3, 0x67,
        0xe3, 0xb6, 0x71, 0x1b, 0x68, 0x0d, 0x8c, 0x26, 0x44, 0xb6, 0x08, 0x53, 0x2a, 0x88, 0x22, 0x09,
        0xb0, 0x20, 0x28, 0x20, 0x24, 0x40, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x92, 0x00, 0x24, 0x00, 0x49, 0x00, 0x24, 0x80, 0x90, 0xe1, 0xd4, 0x78, 0xfa, 0xff, 0xbe,
        0xf5, 0xf6, 0xef, 0xf4, 0xee, 0x70, 0xf1, 0xf1, 0xf0, 0xb1, 0x70, 0xd9, 0x71, 0x99, 0x79, 0x89,
        0x78, 0x8f, 0x28, 0xed, 0x94, 0x6e, 0x91, 0x2e, 0x51, 0xa6, 0x09, 0x44, 0x11, 0x24, 0x10, 0x24,
        0x00, 0x28, 0x00, 0x20, 0x00, 0x20, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x24, 0x80, 0x09, 0x20, 0x02, 0x48, 0x00, 0x02, 0xb5, 0x79, 0x7f, 0x3f, 0x3f, 0x1f, 0x9f,
        0x1f, 0x15, 0x1f, 0x8f, 0x0b, 0x17, 0x0d, 0x0a, 0x07, 0x0a, 0x05, 0x05, 0x03, 0x02, 0x01, 0x02,
        0x00, 0x03, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    oled_set_cursor(0, 0);
    oled_write_raw_P(layer_logo, sizeof(layer_logo));
  }

  static void print_doom_guy_wpm(void) {
    render_doom_guy(0, 11);
  }

  oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
      if (is_keyboard_left()) {
        return OLED_ROTATION_270;
      }

      else {
        return OLED_ROTATION_270;
      }

    } else {
      return OLED_ROTATION_270;
    }
  }

  bool oled_task_user(void) {
      current_wpm   = get_current_wpm();

      print_doom_guy_wpm();
      render_logo();

      return false;
  }
#endif
