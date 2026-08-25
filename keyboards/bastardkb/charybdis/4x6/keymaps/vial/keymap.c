#include QMK_KEYBOARD_H

#ifdef AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_LOWER,
};

/** \brief Automatically enable sniping-mode on the pointer layer. */
#define AUTO_SNIPING_ON_LAYER LAYER_LOWER

#ifdef AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif // AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif // AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // AUTO_POINTER_LAYER_TRIGGER_ENABLE

#define LOWER MO(LAYER_LOWER)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_charybdis_4x6(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_DEL,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_BSPC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LALT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_ESC,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                   MS_BTN1,  LOWER,  KC_SPC,     KC_ENT,  KC_RSFT,
                                           DRGSCRL, KC_LCTL,     KC_RGUI
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_LOWER] = LAYOUT_charybdis_4x6(
  // ╭────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       XXXXXXX,   KC_F1,   KC_F2,      KC_F3,      KC_F4,   KC_F5,    KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, _______,
  // ├────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPLY,
  // ├────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, KC_MINS, KC_EQL,     KC_LBRC,    KC_RBRC, XXXXXXX,    KC_LEFT, KC_DOWN, KC_UP,  KC_RIGHT, XXXXXXX, KC_VOLU,
  // ├────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, XXXXXXX, XXXXXXX, G(KC_LBRC), G(KC_RBRC), XXXXXXX,    KC_HOME, KC_PGDN, KC_PGUP,  KC_END, XXXXXXX, KC_VOLD,
  // ╰────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, _______,
                                           XXXXXXX, _______,          _______
  //                            ╰─────────────────────────────────╯ ╰──────────────────╯
  ),

};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(LAYER_LOWER);
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_user(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(LAYER_LOWER);
    }
}
#    endif // AUTO_POINTER_LAYER_TRIGGER_ENABLE

#    ifdef AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

