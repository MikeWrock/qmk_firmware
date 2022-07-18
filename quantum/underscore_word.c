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

#include "underscore_word.h"

/** @brief True when Caps Word is active. */
static bool underscore_word_active = false;

#if UNDERSCORE_WORD_IDLE_TIMEOUT > 0
// Constrain timeout to a sensible range. With 16-bit timers, the longest
// timeout possible is 32768 ms, rounded here to 30000 ms = half a minute.
#    if UNDERSCORE_WORD_IDLE_TIMEOUT < 100 || UNDERSCORE_WORD_IDLE_TIMEOUT > 30000
#        error "UNDERSCORE_WORD_IDLE_TIMEOUT must be between 100 and 30000 ms"
#    endif

/** @brief Deadline for idle timeout. */
static uint16_t idle_timer = 0;

void underscore_word_task(void) {
    if (underscore_word_active && timer_expired(timer_read(), idle_timer)) {
        underscore_word_off();
    }
}

void underscore_word_reset_idle_timer(void) {
    idle_timer = timer_read() + UNDERSCORE_WORD_IDLE_TIMEOUT;
}
#endif // UNDERSCORE_WORD_IDLE_TIMEOUT > 0

void underscore_word_on(void) {
    if (underscore_word_active) {
        return;
    }

    clear_mods();
#ifndef NO_ACTION_ONESHOT
    clear_oneshot_mods();
#endif // NO_ACTION_ONESHOT
#if UNDERSCORE_WORD_IDLE_TIMEOUT > 0
    underscore_word_reset_idle_timer();
#endif // UNDERSCORE_WORD_IDLE_TIMEOUT > 0

    underscore_word_active = true;
    underscore_word_set_user(true);
}

void underscore_word_off(void) {
    if (!underscore_word_active) {
        return;
    }

    unregister_weak_mods(MOD_MASK_SHIFT); // Make sure weak shift is off.
    underscore_word_active = false;
    underscore_word_set_user(false);
}

void underscore_word_toggle(void) {
    if (underscore_word_active) {
        underscore_word_off();
    } else {
        underscore_word_on();
    }
}

bool is_underscore_word_on(void) {
    return underscore_word_active;
}

__attribute__((weak)) void underscore_word_set_user(bool active) {}
