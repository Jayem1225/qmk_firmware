#include QMK_KEYBOARD_H
#include "layers.h"
#include "tapdance.h"
#include "keycodes.h"

// Create a global instance of the tapdance state type
static td_state_t td_state = TD_NONE;
static td_state_t ctrlesc_td_state = TD_NONE;
static td_state_t bspdel_td_state = TD_NONE;
static td_state_t guieq_td_state = TD_NONE;

static bool bspdel_registered;

uint8_t mod_state;
uint8_t oneshot_mod_state;

// Determine the tapdance state to return
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    }

    if (state->count == 2) {
      if (!state->pressed) return TD_DOUBLE_TAP;
      else return TD_DOUBLE_HOLD;
    }
    else return TD_UNKNOWN; // Any number higher than the maximum state value you return above
}

void dance_sen_par(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
      SEND_STRING(". ");
      add_oneshot_mods(MOD_BIT(KC_LSFT));
    } else if (state->count == 2) {
      SEND_STRING(".");
      SEND_STRING(SS_LSFT(SS_TAP(X_ENT) SS_TAP(X_ENT)));
      add_oneshot_mods(MOD_BIT(KC_LSFT));
    }
    reset_tap_dance(state);
}

void dance_dir(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
      SEND_STRING("./");
    } else if (state->count == 2) {
      SEND_STRING("../");
    } else if (state->count == 3) {
      SEND_STRING("~/");
    }
    reset_tap_dance(state);
}

void dance_hom_end(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
      SEND_STRING(SS_TAP(X_HOME));
    } else if (state->count == 2) {
      SEND_STRING(SS_TAP(X_END));
    }
    reset_tap_dance(state);
}

void dance_pg_up_dn(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
      SEND_STRING(SS_TAP(X_PGUP));
    } else if (state->count == 2) {
      SEND_STRING(SS_TAP(X_PGDN));
    }
    reset_tap_dance(state);
}

void dance_pg_cut_copy(tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
      SEND_STRING(SS_LCTL("c"));
  } else if (state->count == 2) {
      SEND_STRING(SS_LCTL("x"));
  }
  reset_tap_dance(state);
}

void dance_eq_neq(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
      SEND_STRING("==");
    } else if (state->count == 2) {
      SEND_STRING("!=");
    }
    reset_tap_dance(state);
}

void dance_dec_inc(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
      SEND_STRING("--");
    } else if (state->count == 2) {
      SEND_STRING("++");
    }
    reset_tap_dance(state);
}

void dance_and_or(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
      SEND_STRING("&&");
    } else if (state->count == 2) {
      SEND_STRING("||");
    }
    reset_tap_dance(state);
}

void guiquote_finished(tap_dance_state_t *state, void *user_data) {
    mod_state = get_mods();
    oneshot_mod_state = get_oneshot_mods();
    bool ctrl_mod = ((mod_state | oneshot_mod_state) & MOD_MASK_CTRL);
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
            if (ctrl_mod) {
                del_mods(MOD_MASK_CTRL);
                del_oneshot_mods(MOD_MASK_CTRL);
                register_code16(KC_GRV);
                set_mods(mod_state);
                set_oneshot_mods(oneshot_mod_state);
            } else {
                register_code16(KC_QUOT);
            }
            break;
        case TD_SINGLE_HOLD:
        case TD_DOUBLE_HOLD:
            register_mods(MOD_BIT(KC_LGUI)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        default:
            break;
    }
}

void guiquote_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
            unregister_code16(KC_GRV);
            unregister_code16(KC_QUOT);
            break;
        case TD_SINGLE_HOLD:
        case TD_DOUBLE_HOLD:
            unregister_mods(MOD_BIT(KC_LGUI)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        default:
            break;
    }
}

void shiftlead_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            leader_start();
            break;
        case TD_SINGLE_HOLD:
        case TD_DOUBLE_HOLD:
            register_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case TD_DOUBLE_TAP:
            caps_word_toggle();
            break;
        default:
            break;
    }
}

void shiftlead_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            break;
        case TD_SINGLE_HOLD:
        case TD_DOUBLE_HOLD:
            unregister_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        default:
            break;
    }
}

void altlead_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(KC_ENT);
            break;
        case TD_SINGLE_HOLD:
        case TD_DOUBLE_HOLD:
            register_mods(MOD_BIT(KC_LALT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case TD_DOUBLE_TAP:
            leader_start();
            break;
        default:
            break;
    }
}

void altlead_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_ENT);
            break;
        case TD_SINGLE_HOLD:
        case TD_DOUBLE_HOLD:
            unregister_mods(MOD_BIT(KC_LALT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        default:
            break;
    }
}

void twolead_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            leader_start();
            break;
        case TD_SINGLE_HOLD:
        case TD_DOUBLE_HOLD:
            layer_on(L_2); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        default:
            break;
    }
}

void twolead_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_HOLD:
        case TD_DOUBLE_HOLD:
            layer_off(L_2); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        default:
            break;
    }
}

void leftshift_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            add_oneshot_mods(MOD_BIT(KC_LSFT));
            break;
        case TD_DOUBLE_TAP:
            add_oneshot_mods(MOD_BIT(KC_LGUI));
            add_oneshot_mods(MOD_BIT(KC_LSFT));
            tap_code(KC_S);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case TD_DOUBLE_HOLD:
            register_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            register_mods(MOD_BIT(KC_LCTL)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        default:
            break;
    }
}

void leftshift_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case TD_DOUBLE_HOLD:
            unregister_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            unregister_mods(MOD_BIT(KC_LCTL)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        default:
            break;
    }
}

void rightshift_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            caps_word_on();
            break;
        case TD_DOUBLE_TAP:
            caps_word_off();
            add_oneshot_mods(MOD_BIT(KC_LGUI));
            tap_code(KC_EQL);
            break;
        case TD_SINGLE_HOLD:
            caps_word_off();
            register_mods(MOD_BIT(KC_RSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case TD_DOUBLE_HOLD:
            caps_word_off();
            register_mods(MOD_BIT(KC_RSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            register_mods(MOD_BIT(KC_RCTL)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        default:
            break;
    }
}

void rightshift_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_RSFT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case TD_DOUBLE_HOLD:
            unregister_mods(MOD_BIT(KC_RSFT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            unregister_mods(MOD_BIT(KC_RCTL)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        default:
            break;
    }
}

void ctrlesc_finished(tap_dance_state_t *state, void *user_data) {
    ctrlesc_td_state = cur_dance(state);
    switch (ctrlesc_td_state) {
        case TD_DOUBLE_TAP:
        case TD_SINGLE_TAP:
            tap_code(KC_ESC);
            break;
        case TD_DOUBLE_HOLD:
            register_mods(MOD_BIT(KC_LALT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            register_mods(MOD_BIT(KC_LCTL));
            register_mods(MOD_BIT(KC_LSFT));
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LCTL)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        default:
            break;
    }
}

void ctrlesc_reset(tap_dance_state_t *state, void *user_data) {
    switch (ctrlesc_td_state) {
        case TD_DOUBLE_HOLD:
            unregister_mods(MOD_BIT(KC_LALT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            unregister_mods(MOD_BIT(KC_LCTL)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            unregister_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LCTL)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        default:
            break;
    }
}

void onetab_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_DOUBLE_TAP:
            SEND_STRING(SS_LSFT("\t"));
            break;
        case TD_SINGLE_TAP:
            tap_code(KC_TAB);
            break;
        case TD_SINGLE_HOLD:
        case TD_DOUBLE_HOLD:
            layer_on(L_1); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        default:
            break;
    }
}

void onetab_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_HOLD:
        case TD_DOUBLE_HOLD:
            layer_off(L_1); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        default:
            break;
    }
}

void bspdel_finished(tap_dance_state_t *state, void *user_data) {
    const uint8_t mod_state = get_mods();
    /* const uint8_t oneshot_mod_state = get_oneshot_mods(); */
    const uint8_t mods = get_mods() | get_oneshot_mods();
    bspdel_td_state = cur_dance(state);
    switch (bspdel_td_state) {
        case TD_DOUBLE_TAP:
        case TD_SINGLE_TAP:
            if(mods & MOD_MASK_SHIFT) {
              del_oneshot_mods(MOD_MASK_SHIFT);
              unregister_mods(MOD_MASK_SHIFT);
              tap_code(KC_DEL);
              register_mods(mod_state);
            } else {
              tap_code(KC_BSPC);
            }
            break;
        case TD_SINGLE_HOLD:
            layer_on(L_1); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case TD_DOUBLE_HOLD:
            if(mods & MOD_MASK_SHIFT) {
              del_oneshot_mods(MOD_MASK_SHIFT);
              unregister_mods(MOD_MASK_SHIFT);
              bspdel_registered = true;
              register_code(KC_DEL);
              register_mods(mod_state);
            } else {
              bspdel_registered = false;
              register_code(KC_BSPC);
            }
            break;
        default:
            break;
    }
}

void bspdel_reset(tap_dance_state_t *state, void *user_data) {
    switch (bspdel_td_state) {
        case TD_SINGLE_HOLD:
            layer_off(L_1); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case TD_DOUBLE_HOLD:
            if(bspdel_registered) {
              unregister_code(KC_DEL);
            } else {
              unregister_code(KC_BSPC);
            }
            break;
        default:
            break;
    }
}

void copypaste_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_DOUBLE_TAP:
            SEND_STRING(SS_LCTL("x"));
            break;
        case TD_SINGLE_TAP:
            SEND_STRING(SS_LCTL("c"));
            break;
        case TD_SINGLE_HOLD:
        case TD_DOUBLE_HOLD:
            SEND_STRING(SS_LCTL("v"));
            break;
        default:
            break;
    }
}

void copypaste_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        default:
            break;
    }
}

void bracedance_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            if (IS_LAYER_ON(L_2)) {
              SEND_STRING("[");
            } else if (IS_LAYER_ON(L_1)) {
              SEND_STRING("{");
            } else {
              SEND_STRING("(");
            }
            break;
        case TD_DOUBLE_TAP:
            if (IS_LAYER_ON(L_2)) {
              SEND_STRING("]");
            } else if (IS_LAYER_ON(L_1)) {
              SEND_STRING("}");
            } else {
              SEND_STRING(")");
            }
            break;
        case TD_SINGLE_HOLD:
        case TD_DOUBLE_HOLD:
            break;
        default:
            break;
    }
}

void bracedance_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        default:
            break;
    }
}

void openbrace_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            SEND_STRING("{");
            break;
        case TD_DOUBLE_TAP:
            SEND_STRING("[");
            break;
        case TD_SINGLE_HOLD:
            SEND_STRING("(");
            break;
        case TD_DOUBLE_HOLD:
            SEND_STRING("<");
            break;
        default:
            break;
    }
}

void openbrace_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        default:
            break;
    }
}

void closebrace_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            SEND_STRING("}");
            break;
        case TD_DOUBLE_TAP:
            SEND_STRING("]");
            break;
        case TD_SINGLE_HOLD:
            SEND_STRING(")");
            break;
        case TD_DOUBLE_HOLD:
            SEND_STRING(">");
            break;
        default:
            break;
    }
}

void closebrace_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        default:
            break;
    }
}

void guieq_finished(tap_dance_state_t *state, void *user_data) {
    guieq_td_state = cur_dance(state);
    switch (guieq_td_state) {
        case TD_SINGLE_TAP:
            tap_code(KC_EQL);
            break;
        case TD_DOUBLE_TAP:
            tap_code(KC_EQL);
            tap_code(KC_EQL);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LGUI));
            break;
        case TD_DOUBLE_HOLD:
            unregister_mods(MOD_BIT(KC_LGUI));
            SEND_STRING("!=");
            break;
        default:
            break;
    }
}

void guieq_reset(tap_dance_state_t *state, void *user_data) {
    switch (guieq_td_state) {
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LGUI));
            break;
        default:
            break;
    }
}

tap_dance_action_t tap_dance_actions[] = {
  //Tap once for semicolon, twice for colon
  [T_CN] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLN),
  //Tap once for next sentence, twice for next paragraph
  [T_NS] = ACTION_TAP_DANCE_FN(dance_sen_par),
  //Tap once for current directory, twice for up a directory
  [T_DR] = ACTION_TAP_DANCE_FN(dance_dir),
  //Tap once for home, twice for end
  [T_HE] = ACTION_TAP_DANCE_FN(dance_hom_end),
  //Tap once for page up, twice for page down
  [T_UD] = ACTION_TAP_DANCE_FN(dance_pg_up_dn),
  //Tap once for copy selection, twice for cut selection
  [T_CC] = ACTION_TAP_DANCE_FN(dance_pg_cut_copy),
  //Tap once for equals, twice for not equals
  [T_EQ] = ACTION_TAP_DANCE_FN(dance_eq_neq),
  //Tap once for decrement, twice for increment
  [T_IN] = ACTION_TAP_DANCE_FN(dance_dec_inc),
  //Tap once for and, twice for or
  [T_AO] = ACTION_TAP_DANCE_FN(dance_and_or),
  //Hold for GUI, tap for leader
  [T_GQ] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, guiquote_finished, guiquote_reset),
  //Hold for Shift, tap for leader
  [T_SL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shiftlead_finished, shiftlead_reset),
  //Hold for Alt, tap for leader
  [T_AL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, altlead_finished, altlead_reset),
  //Hold for Layer 2, tap for leader
  [T_2L] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, twolead_finished, twolead_reset),
  //Hold for shift, single tap for OSM shift, double tap for open paren
  [T_LS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, leftshift_finished, leftshift_reset),
  //Hold for shift, single tap for Caps Word, double tap for close paren
  [T_RS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rightshift_finished, rightshift_reset),
  //Hold for Control, single tap for escape, double tap and hold for Control+Alt
  [T_CE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctrlesc_finished, ctrlesc_reset),
  //Hold for Layer 1, tap for tab, double tap for shift+tab
  [T_1T] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, onetab_finished, onetab_reset),
  //Hold for Layer 1, double tap and hold for backspace/delete
  [T_BD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, bspdel_finished, bspdel_reset),
  //Hold for paste, single tap for copy, double tap for cut
  [T_CP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, copypaste_finished, copypaste_reset),
  //Hold for paste, single tap for open par/bra, double tap for close par/bra
  [T_BR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, bracedance_finished, bracedance_reset),
  //Hold for open curly, single tap for open paren, double tap for open brace, double hold for open angle brack
  [T_OB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, openbrace_finished, openbrace_reset),
  //Hold for close curly, single tap for close paren, double tap for close brace, double hold for close angle brack
  [T_CB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, closebrace_finished, closebrace_reset),
  //Hold for close curly, single tap for close paren, double tap for close brace, double hold for close angle brack
  //Hold for GUI, tap for =, double hold for !=
  [T_GE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, guieq_finished, guieq_reset),
};
