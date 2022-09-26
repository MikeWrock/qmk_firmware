#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
#    ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE

static HSV SOLID_REACTIVE2_math(HSV hsv, uint16_t offset) {
    hsv.h += qsub8(50, offset);
    return hsv;
}

bool SOLID_REACTIVE2(effect_params_t* params) {
    return effect_runner_reactive(params, &SOLID_REACTIVE2_math);
}

#    endif     // ENABLE_RGB_MATRIX_SOLID_REACTIVE
#endif         // RGB_MATRIX_KEYREACTIVE_ENABLED
