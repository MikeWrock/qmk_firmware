// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(SOLID_REACTIVE2)
// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS
static HSV SOLID_REACTIVE_math2(HSV hsv, uint16_t offset) {
    hsv.h -= qsub8(80, offset);
    return hsv;
}



bool SOLID_REACTIVE2(effect_params_t* params) { return effect_runner_reactive(params, &SOLID_REACTIVE_math2); }

#endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
