// Copyright 2022 Diego Palacios (@diepala)
// SPDX-License-Identifier: GPL-2.0

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
      * ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
      * │Tab│ Q │ W │ E │ R │ T │       │ Y │ U │ I │ O │ P │Bsp│
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │Ctl│ A │ S │ D │ F │ G │       │ H │ J │ K │ L │ ; │ ' │
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │Sft│ Z │ X │ C │ V │ B │       │ N │ M │ , │ . │ / │Sft│
      * └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
      *               ┌───┐                   ┌───┐
      *               │GUI├───┐           ┌───┤Alt│
      *               └───┤   ├───┐   ┌───┤   ├───┘
      *                   └───┤Bsp│   │Ent├───┘
      *                       └───┘   └───┘
      */
    [0] = LAYOUT_split_3x6_3(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,     KC_T,                           KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_DEL,
        KC_BSPC, KC_A,    KC_S,    KC_D,    KC_F,     KC_G,                           KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
        KC_LALT, KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,                           KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_ESC,
                                            KC_LCTL,  MO(1),  KC_SPC,        KC_ENT,  KC_RSFT,  KC_RGUI
    ),

    [1] = LAYOUT_split_3x6_3(
        KC_GRV,  KC_1,    KC_2,    KC_3,       KC_4,       KC_5,                      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,          KC_MPLY,
        KC_TRNS, KC_MINS, KC_EQL,  KC_LBRC,    KC_RBRC,    KC_NO,                     KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT, LSFT(KC_BSLS), KC_VOLU,
        KC_TRNS, MO(2),   KC_NO,   LSFT(KC_9), LSFT(KC_0), KC_NO,                     KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   KC_BSLS,       KC_VOLD,
                                            KC_TRNS,  KC_NO,  KC_TRNS,       KC_TRNS, KC_TRNS,  KC_TRNS
    ),

    [2] = LAYOUT_split_3x6_3(
        KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,                          KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,                          KC_MS_L,  KC_MS_D,  KC_MS_U,  KC_MS_R,  KC_NO,    KC_F12,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,                          KC_WH_L,  KC_WH_U,  KC_WH_D,  KC_WH_R,  KC_NO,    KC_NO,
                                            KC_NO,    KC_NO,  KC_BTN2,       KC_BTN1, KC_NO,    KC_NO
    ),

    [3] = LAYOUT_split_3x6_3(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,                          KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,                          KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,                          KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
                                            KC_NO,    KC_NO,  KC_NO,         KC_NO,   KC_NO,    KC_NO
    )
};

#ifdef RGBLIGHT_ENABLE

const rgblight_segment_t PROGMEM layer0_colors[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, 85, 255, 75}
);
const rgblight_segment_t PROGMEM layer1_colors[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, 170, 255, 75}
);
const rgblight_segment_t PROGMEM layer2_colors[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, 0, 255, 75}
);
const rgblight_segment_t PROGMEM layer3_colors[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, 191, 255, 75}
);
const rgblight_segment_t PROGMEM layer4_colors[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, 30, 218, 75}
);
const rgblight_segment_t PROGMEM layer5_colors[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, 11, 176, 75}
);
const rgblight_segment_t PROGMEM layer6_colors[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, 106, 255, 75}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer0_colors,
    layer1_colors,
    layer2_colors,
    layer3_colors,
    layer4_colors,
    layer5_colors,
    layer6_colors
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = rgb_layers;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
    rgblight_set_layer_state(4, layer_state_cmp(state, 4));
    rgblight_set_layer_state(5, layer_state_cmp(state, 5));
    rgblight_set_layer_state(6, layer_state_cmp(state, 6));
    return state;
}

#endif
