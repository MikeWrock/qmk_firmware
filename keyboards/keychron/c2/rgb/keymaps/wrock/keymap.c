/*
Copyright 2020 Dimitris Mantzouranis

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_names {
    WIN_BASE    = 0,
    WIN_FN      = 1,
    WIN_ALT_FN  = 2,
    MAC_BASE    = 3,
    MAC_FN      = 4,
};


enum custom_keycodes {
    SOURCE_WORKSPACE = SAFE_RANGE,
    COLCON_TEST,
};

// Tap Dance declarations
enum {
    TD_COLON,
};


#define KC_TASK LGUI(KC_TAB)        // Task viewer
#define KC_FLXP LGUI(KC_E)          // Windows file explorer
#define KC_CRTN LGUI(KC_C)          // Cortana | Microsoft Teams
#define KC_SNIP LGUI(LSFT(KC_S))    // Windows snip tool

#define KC_MSSN LGUI(KC_F3)         // Mission Control
#define KC_FIND LALT(LGUI(KC_SPC))  // Finder
#define KC_SIRI LGUI(KC_SPC)        // Siri
#define KC_MSCR LSFT(LGUI(KC_3))    // Mac screenshot
#define KC_MSNP LSFT(LGUI(KC_4))    // Mac snip tool

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for '.', twice for ':'
    [TD_COLON] = ACTION_TAP_DANCE_DOUBLE(KC_PDOT, KC_COLN),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

    case SOURCE_WORKSPACE:
        if (record->event.pressed) {
            // when keycode SOURCE_WORKSPACE is pressed
            send_string_with_delay_P("source /opt/ros/foxy/setup.bash && source install/setup.bash"SS_TAP(X_ENT), 232);
            // SEND_STRING("source /opt/ros/foxy/setup.bash && source install/setup.bash"SS_TAP(X_ENT));
        } else {
            // when keycode SOURCE_WORKSPACE is released
        }
        break;

    case COLCON_TEST:
        if (record->event.pressed) {
            // when keycode COLCON_TEST is pressed
            send_string_with_delay_P("source /opt/ros/foxy/setup.bash && source install/setup.bash"SS_TAP(X_ENT), 232);
            send_string_with_delay_P("colcon test --event-handlers console_direct+ desktop_notification- --packages-select pounce && colcon test-result --verbose"SS_TAP(X_ENT),232);
            // SEND_STRING("source /opt/ros/foxy/setup.bash && source install/setup.bash"SS_TAP(X_ENT));
            // SEND_STRING("colcon test --event-handlers console_direct+ desktop_notification- --packages-select pounce && colcon test-result --verbose"SS_TAP(X_ENT));
            // SEND_STRING(SS_TAP(SOURCE_WORKSPACE)"colcon test --event-handlers console_direct+ desktop_notification- --packages-select pounce && colcon test-result --verbose"SS_TAP(X_ENT));
        } else {
            // when keycode COLCON_TEST is released
        }
        break;

    }
    return true;
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /*  Windows layout
    +-----------------------------------------------------------------------------------------------------------------+
    | ESC |  | F1 | F2 | F3 | F4 | | F5 | F6 | F7 | F8 | | F9| F10| F11| F12|  | |PSCR|CORT|RGB |                     |
    +--------------------------------------------------------------------------+ +--------------+ +-------------------+
    |  ~  |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |  0 |  - |  = | BACKSP | |INS |HOME|PGUP| |NLCK| P/ | P* | P- |
    +--------------------------------------------------------------------------+ +--------------+ +-------------------+
    |  TAB  |  Q |  W |  E |  R |  T |  Y |  U |  I |  O |  P |  [ |  ] |   \  | |DEL |END |PGDN| | P7 | P8 | P9 |    |
    +--------------------------------------------------------------------------+ +--------------+ +--------------+ P+ |
    | CAPSLCK  |  A |  S |  D |  F |  G |  H |  J |  K |  L | ; | ' |  RETURN  |                  | P4 | P5 | P6 |    |
    +--------------------------------------------------------------------------+      +----+      +-------------------+
    | LSHIFT     |  Z |  X |  C |  V |  B |  N |  M | , | . |  / |   RSHIFT    |      | UP |      | P1 | P2 | P3 |    |
    +--------------------------------------------------------------------------+ +--------------+ +---------------PRET|
    |LCTRL| LGUI| LALT |            SPACE            | RALT| RGUI | FN | RCTRL | |LFT |DWN |RGT | |   P0    | .  |    |
    +-----------------------------------------------------------------------------------------------------------------+
    */

    [WIN_BASE] = { // Windows base layout
        /*  0         1         2         3         4         5         6         7         8         9         10        11        12        13        14        15        16       17       18       19       20      */
        {   KC_ESC,   KC_BRID,  KC_BRIU,  DM_PLY1,  DM_PLY2,   BL_INC,   BL_DEC,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_SNIP,  KC_PSCR,  CAPSWRD,  RGB_MOD                                     },
        {   KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS },
        {   KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_DEL,   KC_END,   KC_PGDN, KC_P7,   KC_P8,   KC_P9,   KC_PPLS },
        {   KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NO,    KC_ENT,   KC_NO,    KC_NO,    KC_NO,   KC_P4,   KC_P5,   KC_P6,   KC_NO   },
        {   KC_LSFT,  KC_NO,    KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_NO,    KC_RSFT,  KC_NO,    KC_UP,    KC_NO,   KC_P1,   KC_P2,   KC_P3,   KC_PENT },
        {   KC_LCTL,  KC_LGUI,  KC_LALT,  KC_NO,    KC_NO,    KC_NO,    KC_SPC,   KC_NO,    KC_NO,    KC_RALT,  KC_RGUI,  MO(1),    KC_NO,    KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT, KC_NO,   KC_P0,   TD(TD_COLON), KC_NO }
    },

    [WIN_FN] = { // Windows Fn overlay
        /*  0         1         2         3         4         5         6         7         8         9         10        11        12        13        14        15        16       17        18        19        20      */
        {   RESET,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  _______,  _______,  RGB_TOG, _______,  _______,  _______,  _______ },
        {   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_HUI,  RGB_VAI,  RGB_SAI, RGB_M_TW, _______,  _______,  _______ },
        {   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_HUD,  RGB_VAD,  RGB_SAD, RGB_M_X,  RGB_M_G,  RGB_M_T,  _______ },
        {   _______,  KC_A,     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______, RGB_M_SW, RGB_M_SN, RGB_M_K,  _______ },
        {   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_SPI,  _______, RGB_M_P,  RGB_M_B,  RGB_M_R,  _______ },
        {   _______,  _______,  MO(2),    _______,  _______,  _______,  _______,  _______,  _______,  MO(2),    _______,  _______,  _______,  _______,  RGB_RMOD, RGB_SPD,  RGB_MOD, _______,  _______,  _______,  _______ }
    },
    [WIN_ALT_FN] = { // Windows Fn overlay
        /*  0         1         2         3         4         5         6         7         8         9         10        11        12        13        14        15        16       17        18        19        20      */
        {   DM_RSTP,KC_F1,  KC_F2,    DM_REC1,  DM_REC2,SOURCE_WORKSPACE,COLCON_TEST,KC_F7,   KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12, _______,  _______,  _______,  RGB_TOG, _______,  _______,  _______,  _______ },
        {   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_HUI,  RGB_VAI,  RGB_SAI, RGB_M_TW, _______,  _______,  _______ },
        {   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_HUD,  RGB_VAD,  RGB_SAD, RGB_M_X,  RGB_M_G,  RGB_M_T,  _______ },
        {   _______,  KC_B,     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______, RGB_M_SW, RGB_M_SN, RGB_M_K,  _______ },
        {   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_SPI,  _______, RGB_M_P,  RGB_M_B,  RGB_M_R,  _______ },
        {   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_RMOD, RGB_SPD,  RGB_MOD, _______,  _______,  _______,  _______ }
    },


    /*  Mac layout
    +-----------------------------------------------------------------------------------------------------------------+
    | ESC |  | F1 | F2 | F3 | F4 | | F5 | F6 | F7 | F8 | | F9| F10| F11| F12|  | |PSCR|SIRI|RGB |                     |
    +--------------------------------------------------------------------------+ +--------------+ +-------------------+
    |  ~  |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |  0 |  - |  = | BACKSP | |INS |HOME|PGUP| |NLCK| P/ | P* | P- |
    +--------------------------------------------------------------------------+ +--------------+ +-------------------+
    |  TAB  |  Q |  W |  E |  R |  T |  Y |  U |  I |  O |  P |  [ |  ] |   \  | |DEL |END |PGDN| | P7 | P8 | P9 |    |
    +--------------------------------------------------------------------------+ +--------------+ +--------------+ P+ |
    | CAPSLCK  |  A |  S |  D |  F |  G |  H |  J |  K |  L | ; | ' |  RETURN  |                  | P4 | P5 | P6 |    |
    +--------------------------------------------------------------------------+      +----+      +-------------------+
    | LSHIFT     |  Z |  X |  C |  V |  B |  N |  M | , | . |  / |   RSHIFT    |      | UP |      | P1 | P2 | P3 |    |
    +--------------------------------------------------------------------------+ +--------------+ +---------------PRET|
    |LCTRL| LALT| LGUI |            SPACE            | RGUI| RALT | FN | RCTRL | |LFT |DWN |RGT | |   P0    | .  |    |
    +-----------------------------------------------------------------------------------------------------------------+
    */

    [MAC_BASE] = { // Mac base layout
        /*  0         1         2         3         4         5         6         7         8         9         10        11        12        13        14        15        16       17       18       19       20      */
        {   KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_NO,    KC_MSCR,  KC_SIRI,  RGB_TOG                                     },
        {   KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS },
        {   KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_DEL,   KC_END,   KC_PGDN, KC_P7,   KC_P8,   KC_P9,   KC_PPLS },
        {   KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NO,    KC_ENT,   KC_NO,    KC_NO,    KC_NO,   KC_P4,   KC_P5,   KC_P6,   KC_NO   },
        {   KC_LSFT,  KC_NO,    KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_NO,    KC_RSFT,  KC_NO,    KC_UP,    KC_NO,   KC_P1,   KC_P2,   KC_P3,   KC_PENT },
        {   KC_LCTL,  KC_LALT,  KC_LGUI,  KC_NO,    KC_NO,    KC_NO,    KC_SPC,   KC_NO,    KC_NO,    KC_RGUI,  KC_RALT,  MO(3),    KC_NO,    KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT, KC_NO,   KC_P0,   KC_PDOT, KC_NO   }
    },

    [MAC_FN] = { // Mac Fn overlay
        /*  0         1         2         3         4         5         6         7         8         9         10        11        12        13        14        15        16       17        18        19        20     */
        {   RESET,    KC_BRID,  KC_BRIU,  KC_MSSN,  KC_FIND,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  KC_MSNP,  _______,  RGB_TOG, _______,  _______,  _______,  _______ },
        {   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_HUI,  RGB_VAI,  RGB_SAI, RGB_M_TW, _______,  _______,  _______ },
        {   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_HUD,  RGB_VAD,  RGB_SAD, RGB_M_X,  RGB_M_G,  RGB_M_T,  _______ },
        {   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______, RGB_M_SW, RGB_M_SN, RGB_M_K,  _______ },
        {   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_SPI,  _______, RGB_M_P,  RGB_M_B,  RGB_M_R,  _______ },
        {   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_RMOD, RGB_SPD,  RGB_MOD, _______,  _______,  _______,  _______ }
    }
};
