#include QMK_KEYBOARD_H
#include "version.h"
#define MOON_LED_LEVEL LED_LEVEL
#ifndef ZSA_SAFE_RANGE
#define ZSA_SAFE_RANGE SAFE_RANGE
#endif

enum custom_keycodes {
  RGB_SLD = ZSA_SAFE_RANGE,
};




const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_voyager(
    KC_GRAVE,       KC_1,           KC_2,           KC_3,           KC_4,           KC_5,                                           KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_BSLS,
    KC_MINUS,       KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,                                           KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_EQUAL,
    MT(MOD_LCTL, KC_ESCAPE),KC_A,           KC_S,           KC_D,           KC_F,           KC_G,                                           KC_H,           KC_J,           KC_K,           KC_L,           KC_SCLN,        KC_QUOTE,       
    KC_LEFT_SHIFT,  KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,                                           KC_N,           MT(MOD_LGUI, KC_M),MT(MOD_LALT, KC_COMMA),MT(MOD_LCTL, KC_DOT),KC_SLASH,       KC_RIGHT_SHIFT, 
                                                    KC_BSPC,        MT(MOD_LGUI, KC_TAB),                                MT(MOD_RGUI, KC_ENTER),LT(1, KC_SPACE)
  ),
  [1] = LAYOUT_voyager(
    KC_TRANSPARENT, KC_EXLM,        KC_AT,          KC_HASH,        KC_DLR,         KC_PERC,                                        KC_CIRC,        KC_AMPR,        KC_ASTR,        LGUI(KC_LBRC),  KC_MEDIA_PREV_TRACK,KC_MEDIA_PLAY_PAUSE,
    LALT(LSFT(KC_MINUS)),LGUI(LSFT(KC_1)),LGUI(LSFT(KC_2)),LGUI(LSFT(KC_3)),LGUI(LSFT(KC_4)),LGUI(LSFT(KC_5)),                                LGUI(LSFT(KC_C)),KC_NO,          LALT(LGUI(KC_I)),KC_NO,          KC_NO,          KC_AUDIO_VOL_UP,
    KC_TRANSPARENT, LALT(LCTL(LSFT(KC_A))),LALT(LCTL(LSFT(KC_S))),LALT(LCTL(LSFT(KC_D))),LALT(LCTL(LSFT(KC_F))),LALT(LCTL(LSFT(KC_G))),                                KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT,       KC_ENTER,       KC_AUDIO_VOL_DOWN,
    KC_LEFT_SHIFT,  KC_LEFT_SHIFT,  KC_LEFT_CTRL,   KC_LEFT_ALT,    KC_LEFT_GUI,    KC_RIGHT_GUI,                                   KC_SPACE,       KC_LEFT_GUI,    KC_LEFT_ALT,    KC_LEFT_CTRL,   KC_NO,          KC_RIGHT_SHIFT, 
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
  ),
};



uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MT(MOD_LGUI, KC_TAB):
            return TAPPING_TERM -45;
        case MT(MOD_RGUI, KC_ENTER):
            return TAPPING_TERM -45;
        default:
            return TAPPING_TERM;
    }
}


extern rgb_config_t rgb_matrix_config;

RGB hsv_to_rgb_with_value(HSV hsv) {
  RGB rgb = hsv_to_rgb( hsv );
  float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
  return (RGB){ f * rgb.r, f * rgb.g, f * rgb.b };
}

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [0] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {131,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {131,255,255}, {20,255,255}, {219,255,255}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,0} },

    [1] = { {0,0,0}, {74,255,255}, {74,255,255}, {74,255,255}, {74,255,255}, {74,255,255}, {74,255,255}, {152,255,255}, {0,0,255}, {0,0,255}, {0,0,255}, {41,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {74,255,255}, {219,255,255}, {20,255,255}, {131,255,255}, {0,0,255}, {0,0,0}, {131,255,255}, {74,255,255}, {74,255,255}, {74,255,255}, {0,0,255}, {131,255,255}, {41,255,255}, {0,0,255}, {0,0,0}, {0,0,255}, {0,0,0}, {0,0,0}, {0,245,245}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {0,0,255}, {131,255,255}, {0,0,255}, {131,255,255}, {20,255,255}, {219,255,255}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,0} },

};

void set_layer_color(int layer) {
  for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb_with_value(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
  }
}

bool rgb_matrix_indicators_user(void) {
  if (!keyboard_config.disable_layer_led) {
    switch (biton32(layer_state)) {
      case 0:
        set_layer_color(0);
        break;
      case 1:
        set_layer_color(1);
        break;
     default:
        if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
          rgb_matrix_set_color_all(0, 0, 0);
        }
    }
  } else {
    if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
      rgb_matrix_set_color_all(0, 0, 0);
    }
  }

  return true;
}





bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
  }
  return true;
}








// ---
// custom qmk
// ---
// Shift 2 is {
const key_override_t two_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_2, KC_LCBR);
// Shift 3 is (
const key_override_t three_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_3, KC_LPRN);
// Shift 4 is [
const key_override_t four_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_4, KC_LBRC);
// Shift 5 is $
const key_override_t five_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_5, KC_DLR);
// Shift 6 is *
const key_override_t six_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_6, KC_ASTR);
// Shift 7 is ]
const key_override_t seven_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_7, KC_RBRC);
// Shift 8 is )
const key_override_t eight_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_8, KC_RPRN);
// Shift 9 is }
const key_override_t nine_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_9, KC_RCBR);
// Shift 0 is &
const key_override_t zero_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_0, KC_AMPR);

const key_override_t *key_overrides[] = {
  &two_key_override,
  &three_key_override,
  &four_key_override,
  &five_key_override,
  &six_key_override,
  &seven_key_override,
  &eight_key_override,
  &nine_key_override,
  &zero_key_override,
  NULL
};
