/* 
 * Forked from <salman@pcgamingrace.com> ( Copyright 2021 Glorious, LLC )
 * Thank you, sir "salman", for you service.
 * Unfortunately for "salman", this software is now under my license.
 * It's called the NOBMAYM license. I just made it right now!
 * No One But Me And Your Mom license actually means only your mother and myself (Jayem1225 AKA "Final Form Luigi") can use this shit, ok.
*/

#include QMK_KEYBOARD_H
#define L_D 0
#define L_Q 1
#define L_P 2
#define L_H 3
#define L_V 4
#define L_G 5
#define L_A 15


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// Default Layout
// ==============	
// KEY
//	_______  F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     _______           Rotary(Play/Pause)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           _______
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 _______
//      L_Q/Esc  A        S        D        F        G        H        J        K        L        ;        "                 Enter             _______
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       _______
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    _______  Ct_R     Left     Down     Right
//
// RGB
//      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___               ___
//      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___               ___
//      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___               ___
//      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___               ___               ___
//      ___               ___      ___      ___      ___      ___      ___      ___      ___      ___      ___               ___      ___      ___
//      ___      ___      ___                                 ___                                 ___      ___      ___      ___      ___      ___
    [L_D] = LAYOUT(
	_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,          KC_MPLY,
	KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          _______,
	KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          _______,
	LT(L_Q, KC_ESC),KC_A,KC_S, KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           _______,
	KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   _______,
	KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, _______, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),


// Quick Layout
// ============	
// KEY
//	ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt               Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right
//
// RGB
//      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___               ___
//      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___               ___
//      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___               ___
//      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___               ___               ___
//      ___               ___      ___      ___      ___      ___      ___      ___      ___      ___      ___               ___      ___      ___
//      ___      ___      ___                                 ___                                 ___      ___      ___      ___      ___      ___
    [L_Q] = LAYOUT(
        TG(L_A), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PSCR,          RGB_TOG,
        _______, RGB_TOG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,           _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_INS,           _______,
        _______, _______, _______, _______, _______, TG(L_G), _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, NK_TOGG, _______, _______, _______, _______,          _______, KC_PGUP, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, KC_HOME, KC_PGDN, KC_END
    ),


// Admin Layout
// ===========	
// KEY
//	ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	  Prt               Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	  BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right
//
// RGB
//      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___               ___
//      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___               ___
//      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___               ___
//      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___               ___               ___
//      ___               ___      ___      ___      ___      ___      ___      ___      ___      ___      ___               ___      ___      ___
//      ___      ___      ___                                 ___                                 ___      ___      ___      ___      ___      ___
    [L_A] = LAYOUT(
        TG(L_D), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),
    

// Python Layout
// =============
// KEY
//	ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	  Prt               Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	  BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right
//
// RGB
//      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___               ___
//      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___               ___
//      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___               ___
//      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___               ___               ___
//      ___               ___      ___      ___      ___      ___      ___      ___      ___      ___      ___               ___      ___      ___
//      ___      ___      ___                                 ___                                 ___      ___      ___      ___      ___      ___
    [L_P] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),
    
    
// HTML Layout
// ===========	
// KEY
//	ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	  Prt               Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	  BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right
//
// RGB
//      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___               ___
//      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___               ___
//      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___               ___
//      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___               ___               ___
//      ___               ___      ___      ___      ___      ___      ___      ___      ___      ___      ___               ___      ___      ___
//      ___      ___      ___                                 ___                                 ___      ___      ___      ___      ___      ___
    [L_H] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),


// VIM Layout
// ==========
// KEY
//	ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	  Prt               Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	  BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right
//
// RGB
//      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___               ___
//      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___               ___
//      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___               ___
//      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___               ___               ___
//      ___               ___      ___      ___      ___      ___      ___      ___      ___      ___      ___               ___      ___      ___
//      ___      ___      ___                                 ___                                 ___      ___      ___      ___      ___      ___
    [L_V] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),


// Game Layout
// ===========	
// KEY
//	ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	  Prt               Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	  BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right
//
// RGB
//      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___               ___
//      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___               ___
//      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___               ___
//      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___      ___               ___               ___
//      ___               ___      ___      ___      ___      ___      ___      ___      ___      ___      ___               ___      ___      ___
//      ___      ___      ___                                 ___                                 ___      ___      ___      ___      ___      ___
    [L_G] = LAYOUT(
        TG(L_D), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    _______, _______, _______, _______, _______, _______,          _______,
        _______,  KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______,    _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

};
// clang-format on

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    switch(biton32(layer_state)){
        case L_Q:
            if (clockwise) {
                tap_code16(RGB_VAI);
            } else { // counter
                tap_code16(RGB_VAD);
            }
            break;
        default:
            if (clockwise) {
                tap_code(KC_VOLU);
            } else { // counter
                tap_code(KC_VOLD);
            }
            break;
    }
    return false;
}
#endif // ENCODER_ENABLE

//void rgb_matrix_indicators_user(void) {
//  if (IS_LAYER_ON(_NUMBER));
//  else if (IS_LAY
//    rgb_matrix_set_color(0, 255, 255, 255);
//    ...
//    }
//  ...
//}

    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the QK_BOOT key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    //
    // This keyboard defaults to 6KRO instead of NKRO for compatibility reasons (some KVMs and BIOSes are incompatible with NKRO).
    // Since this is, among other things, a "gaming" keyboard, a key combination to enable NKRO on the fly is provided for convenience.
    // Press Fn+N to toggle between 6KRO and NKRO. This setting is persisted to the EEPROM and thus persists between restarts.
