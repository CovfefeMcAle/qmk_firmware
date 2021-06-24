#include QMK_KEYBOARD_H

enum layers{
  _BASE,
  _NUM_SYM,
  _NAV,
  _NUMPAD,
};


enum combo_events {
  combo_ESC,
  combo_BACK,
  combo_TAB,
  combo_DELETE,
  combo_QUOT,
  combo_MINS,
  combo_PLUS,
  combo_EMDASH,
  combo_ENT,
  
};

const uint16_t PROGMEM esc_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM bspc_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM tab_combo[] = {KC_A, KC_S, COMBO_END};
const uint16_t PROGMEM del_combo[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM quot_combo[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM mins_combo[] = {KC_U, KC_O, COMBO_END};
const uint16_t PROGMEM plus_combo[] = {KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM emdash_combo[] = {KC_Y, KC_P, COMBO_END};
const uint16_t PROGMEM ent_combo[] = {KC_L, KC_SCLN, COMBO_END};


combo_t key_combos[COMBO_COUNT] = {
  [combo_ESC] = COMBO(esc_combo, KC_ESC),
   [combo_BACK] = COMBO(bspc_combo, KC_BSPC),
    [combo_TAB] = COMBO(tab_combo, KC_TAB),
     [combo_DELETE] = COMBO(del_combo, KC_DEL), 
       [combo_QUOT] = COMBO(quot_combo, KC_QUOT),
        [combo_MINS] = COMBO(mins_combo, KC_MINS),
         [combo_PLUS] = COMBO(plus_combo, KC_PLUS),
          [combo_EMDASH] = COMBO(emdash_combo, LSFT(LALT(KC_MINS))),
           [combo_ENT] = COMBO(ent_combo, KC_ENT),
            

};


#define KC_SZ LSFT_T(KC_Z)
#define KC_CB LCTL_T(KC_B)
#define KC_SSLSH RSFT_T(KC_SLSH)
#define BASE TO(_BASE)
#define NUMPAD TO(_NUMPAD)
#define NUM MO(_NUM_SYM)
#define xxx KC_TRNS


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,  KC_MPLY,  KC_Y,   KC_U,    KC_I,   KC_O,     KC_P,
    KC_A,   KC_S,   KC_D,   KC_F,   KC_G,            KC_H,   KC_J,    KC_K,   KC_L,    KC_SCLN,
    KC_SZ,  KC_X,   KC_C,   KC_V,   KC_CB,           KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SSLSH,
                           KC_LCMD, NUM,     LT(_NAV, KC_SPC), KC_RALT
  ),

  [_NUM_SYM] = LAYOUT(
  KC_1,  KC_2,     KC_3,     KC_4,      KC_5,   NUMPAD,  KC_6,     KC_7,     KC_8,    KC_9,     KC_0,
  KC_EXLM, KC_AT,  KC_HASH,  KC_DLR,  KC_PERC,        KC_CIRC,  KC_AMPR,  KC_ASTR, KC_EQUAL,  KC_MINS,
  KC_BSLS,  KC_LCBR, KC_LBRC, KC_UNDS,  KC_LPRN,        KC_RPRN, KC_RBRC,  KC_RCBR, KC_DOT,   KC_PLUS,
                              KC_CAPS,  KC_TRNS,        KC_TRNS,  KC_TRNS
  ),

  [_NAV] = LAYOUT(
      RESET,  _______,  AG_NORM,  AG_SWAP,  DEBUG, KC_TRNS,   KC_TILD,  KC_PGDN,    KC_UP,  KC_PGUP,  KC_BSPC,
    RGB_TOG,  RGB_HUI,  RGB_SAI,  RGB_VAI,  KC_NO,           KC_HOME,  KC_LEFT,  KC_DOWN,  KC_RGHT,   KC_END,
    RGB_MOD,  RGB_HUD,  RGB_SAD,  RGB_VAD,  KC_NO,           KC_MINS,  KC_RO,    KC_COMM,  KC_DOT,  KC_BSLS,
                                  KC_TRNS,  KC_TRNS,         KC_TRNS,  KC_TRNS
  ),

[_NUMPAD] = LAYOUT(
  	xxx, xxx, xxx, xxx, xxx, BASE, KC_BSPC, KC_P7, KC_P8, KC_P9, KC_PMNS,
  	xxx, xxx, xxx, xxx, xxx,       KC_PSLS, KC_P4, KC_P5, KC_P6, KC_PPLS,
  	xxx, xxx, xxx, xxx, xxx,       KC_PAST, KC_P1, KC_P2, KC_P3, KC_PEQL, 
  	               xxx, KC_PENT,       KC_P0, KC_PDOT
   ),
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(_NAV, KC_SPC):
            return TAPPING_TERM + 400;
        case KC_CB:
            return TAPPING_TERM + 350;
        case KC_SZ:
            return TAPPING_TERM + 75;
        case KC_SSLSH:
            return TAPPING_TERM + 75;
        default:
            return TAPPING_TERM;
    }
}
bool get_permiSSLSHsive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_SZ:
            return true;
	 case KC_SSLSH:
	    return true;
        default:
             return false;
    }
}
bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_SZ:
            return true;
	 case KC_SSLSH:
	    return true;
        default:
             return false;
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true;
}  



#ifdef OLED_DRIVER_ENABLE  //Special thanks to Sickbabies for this great OLED widget!
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_90;  // rotates for proper orientation
}

void render_lechiffre_logo(void) {
    static const char PROGMEM lechiffre_logo[] = {
	// 'lechiffre_logo', 32x20px
   0x00, 0x3e, 0x20, 0x20, 0x00, 0x18, 0x2c, 0xa8, 0x80, 0x00, 0x1c, 0x22, 0x22, 0x00, 0x3e, 0x08,
0x30, 0x00, 0x34, 0x00, 0x3c, 0x0a, 0x00, 0xbc, 0x8a, 0x00, 0x38, 0x08, 0x00, 0x18, 0x2c, 0x28,
0x00, 0xb6, 0xb6, 0x00, 0xdb, 0xdb, 0x00, 0x6d, 0x6d, 0x00, 0xdb, 0xdb, 0x00, 0xdb, 0xdb, 0x00,
0x00, 0xdb, 0xdb, 0x00, 0xdb, 0xdb, 0x00, 0x6d, 0x6d, 0x00, 0xdb, 0xdb, 0x00, 0xb6, 0xb6, 0x00,
0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x06, 0x06, 0x06, 0x00, 0x06, 0x06, 0x06, 0x06, 0x06, 0x00,
0x00, 0x06, 0x06, 0x06, 0x06, 0x06, 0x00, 0x06, 0x06, 0x06, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00
};

  oled_write_raw_P(lechiffre_logo, sizeof(lechiffre_logo));
}

static void render_layer_status(void) {
    oled_write_P(PSTR("-----"), false);
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_ln_P(PSTR("BASE"), false);
            break;
        case _NUM_SYM:
            oled_write_ln_P(PSTR(" SYM"), false);
            break;
        case _NAV:
            oled_write_ln_P(PSTR(" NAV"), false);
            break;
        default:
            oled_write_ln_P(PSTR("?????"), false);
    }
}

#    define KEYLOG_LEN 11
char     keylog_str[KEYLOG_LEN] = {};
uint8_t  keylogs_str_idx        = 0;
uint16_t log_timer              = 0;

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void add_keylog(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
        keycode = keycode & 0xFF;
    }

    for (uint8_t i = KEYLOG_LEN - 1; i > 0; i--) {
        keylog_str[i] = keylog_str[i - 1];
    }
    if (keycode < 60) {
        keylog_str[0] = code_to_name[keycode];
    }
    keylog_str[KEYLOG_LEN - 1] = 0;

    log_timer = timer_read();
}

void update_log(void) {
    if (timer_elapsed(log_timer) > 750) {
        add_keylog(0);
    }
}

//Text only renders
void render_keylogger_status(void) {
    oled_write_P(PSTR("-----"), false);
    oled_write(keylog_str, false);
}

void render_keylock_status(led_t led_state) {
    oled_write_P(PSTR("-----"), false);
    oled_write_P(PSTR("C"), led_state.caps_lock);
	oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("N"), led_state.num_lock);
	oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("S"), led_state.scroll_lock);
    //oled_write_ln_P(PSTR(" "), false);
}

void render_mod_status(uint8_t modifiers) {
       oled_write_P(PSTR("-----"), false);
    oled_write_ln_P(PSTR("SHFT"), (modifiers & MOD_MASK_SHIFT));
    oled_write_ln_P(PSTR("ALT"), (modifiers & MOD_MASK_ALT));
    oled_write_ln_P(PSTR("CTRL"), (modifiers & MOD_MASK_CTRL));
    oled_write_ln_P(PSTR("GUI"), (modifiers & MOD_MASK_GUI));
}

void oled_task_user(void) {
    render_lechiffre_logo();
    oled_set_cursor(0,3);
    render_layer_status();	// Renders the current keyboard state (layer, lock, caps, scroll, etc)
	render_mod_status(get_mods()|get_oneshot_mods());
	render_keylock_status(host_keyboard_led_state());
	render_keylogger_status();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
      add_keylog(keycode);
    }
    return true;
  }
void rgb_matrix_helper(uint8_t hue, uint8_t sat, uint8_t val, uint8_t i, uint8_t mode) {
    HSV hsv = {hue, sat, val};
    if (hsv.v > rgb_matrix_get_val()) {
        hsv.v = rgb_matrix_get_val();
    }
    switch (mode) {
        case 1:  // breathing
        {
            uint8_t speed = rgb_matrix_config.speed;
            uint16_t time = scale16by8(g_rgb_timer, speed / 8);
            hsv.v         = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
            RGB rgb       = hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);

            break;
        }
        default:  // Solid Color
        {
            RGB rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
            //RGB_MATRIX_INDICATOR_SET_COLOR(i, rgb.r, rgb.g, rgb.b);
            break;
        }
    }
}

void rgb_matrix_indicators_user() {
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_helper(21, 255, 100, 9, 1);
        rgb_matrix_helper(21, 255, 100, 10, 1);
    } else {
        rgb_matrix_helper(0, 0, 0, 9, 0);
        rgb_matrix_helper(0, 0, 0, 10, 0);
    }
    
switch (get_highest_layer(layer_state)) {
    case _NUM_SYM:
        rgb_matrix_helper(148, 255, 70, 9, 0);
        break;
    case _NAV:
        rgb_matrix_helper(85, 255, 70, 10, 0);
        break;
    case _META:
        rgb_matrix_helper(148, 255, 70, 9, 0);
        rgb_matrix_helper(85, 255, 70, 10, 0);
        break;
    }
}
#endif
