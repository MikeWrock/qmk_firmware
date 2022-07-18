// Copyright 2021-2022 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "process_underscore_word.h"

bool process_underscore_word(uint16_t keycode, keyrecord_t* record) {
    if (keycode == UNDRWRD) { // Pressing UNDRWRD toggles Caps Word.
        if (record->event.pressed) {
            underscore_word_toggle();
        }
        return false;
    }

#ifndef NO_ACTION_ONESHOT
    const uint8_t mods = get_mods() | get_oneshot_mods();
#else
    const uint8_t mods = get_mods();
#endif // NO_ACTION_ONESHOT

#if UNDERSCORE_WORD_IDLE_TIMEOUT > 0
    underscore_word_reset_idle_timer();
#endif // UNDERSCORE_WORD_IDLE_TIMEOUT > 0

    // From here on, we only take action on press events.
    if (!record->event.pressed) {
        return true;
    }

    if (!(mods & ~(MOD_MASK_SHIFT | MOD_BIT(KC_RALT)))) {
        switch (keycode) {
            // Ignore MO, TO, TG, TT, and OSL layer switch keys.
            case QK_MOMENTARY ... QK_MOMENTARY_MAX:
            case QK_TO ... QK_TO_MAX:
            case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
            case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
            case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
            // Ignore AltGr.
            case KC_RALT:
            case OSM(MOD_RALT):
                return true;

#ifndef NO_ACTION_TAPPING
            case QK_MOD_TAP ... QK_MOD_TAP_MAX:
                if (record->tap.count == 0) {
                    // Deactivate if a mod becomes active through holding
                    // a mod-tap key.
                    underscore_word_off();
                    return true;
                }
                keycode &= 0xff;
                break;

#    ifndef NO_ACTION_LAYER
            case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
#    endif // NO_ACTION_LAYER
                if (record->tap.count == 0) {
                    return true;
                }
                keycode &= 0xff;
                break;
#endif // NO_ACTION_TAPPING

#ifdef SWAP_HANDS_ENABLE
            case QK_SWAP_HANDS ... QK_SWAP_HANDS_MAX:
                if (keycode > 0x56F0 || record->tap.count == 0) {
                    return true;
                }
                keycode &= 0xff;
                break;
#endif // SWAP_HANDS_ENABLE
        }

        clear_weak_mods();
        if (underscore_word_press_user(keycode)) {
            send_keyboard_report();
            return true;
        }
    }

    underscore_word_off();
    return true;
}

__attribute__((weak)) bool underscore_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;
        case KC_SPACE:
            add_weak_mods(MOD_BIT(MO(3))); // Apply shift to next key.
            return true;


        default:
            return false; // Deactivate Caps Word.
    }
}
