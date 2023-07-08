// based: https://docs.qmk.fm/#/ja/feature_macros

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;
bool is_feature_key_pressed = false;

bool process_record_user_super_alt_tab(uint16_t feature_keycode, uint16_t keycode, keyrecord_t *record) {
  if(keycode == feature_keycode) {
    if (record->event.pressed) {
      if (!is_alt_tab_active) {
        is_alt_tab_active = true;
        register_code(KC_LALT);
      }
      alt_tab_timer = timer_read();
      register_code(KC_TAB);
    } else {
      unregister_code(KC_TAB);
    }

    is_feature_key_pressed = record->event.pressed;
  }

  return true;
}

void matrix_scan_user_super_alt_tab(void) {
  if (is_alt_tab_active) {
    if (is_feature_key_pressed) {
      alt_tab_timer = timer_read();
    } else {
      if (timer_elapsed(alt_tab_timer) > 300) {
        unregister_code(KC_LALT);
        is_alt_tab_active = false;
      }
    }
  }
}
