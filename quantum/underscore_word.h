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

#pragma once

#include "quantum.h"

#ifndef UNDERSCORE_WORD_IDLE_TIMEOUT
#    define UNDERSCORE_WORD_IDLE_TIMEOUT 5000 // Default timeout of 5 seconds.
#endif                                  // UNDERSCORE_WORD_IDLE_TIMEOUT

#if UNDERSCORE_WORD_IDLE_TIMEOUT > 0
/** @brief Matrix scan task for UNDERSCORE Word feature */
void underscore_word_task(void);

/** @brief Resets timer for underscore Word idle timeout. */
void underscore_word_reset_idle_timer(void);
#else
static inline void underscore_word_task(void) {}
#endif // underscore_WORD_IDLE_TIMEOUT > 0

void underscore_word_on(void);     /**< Activates underscore Word. */
void underscore_word_off(void);    /**< Deactivates underscore Word. */
void underscore_word_toggle(void); /**< Toggles underscore Word. */
bool is_underscore_word_on(void);  /**< Gets whether currently active. */

/**
 * @brief underscore Word set callback.
 *
 * @param active True if underscore Word is active, false otherwise
 */
void underscore_word_set_user(bool active);
