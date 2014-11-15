#include <pebble.h>

#include "pebble.h"

  
static Window *window;
static MenuLayer *menu_layer;

static char *friday_events[7];
static char *friday_times[7];
static int friday_hours[7] = {9, 10, 11, 12, 14, 14, 15};

static char *saturday_events[4];
static char *saturday_times[4];
static int saturday_hours[4] = {9, 10, 10, 12};

static char *sunday_events[5];
static char *sunday_times[5];
static int sunday_hours[5] = {9, 11, 12, 14, 14};
/*
static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  strap_log_action("/Select");
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  strap_log_action("/Up");
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  strap_log_action("/Down");
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}
*/
static void create_data () {

    // Friday
    friday_events[0] = "Bring on the Sponsors!";
    friday_events[1] = "YOU (hackers) arrive!";
    friday_events[2] = "Opening Ceremony. And intro from our title sponsor: IT@UC.";
    friday_events[3] = "Get your space set up! And some tasty pizza from our friends at Adriatico's.";
    friday_events[4] = "Idea forming workshop and team building. (Optional)";
    friday_events[5] = "HACKS ON HACKS! Hacking begins.";
    friday_events[6] = "Midnight snack! Cake pops provided by Major League Hacking";

    
    friday_times[0] = "18:00";
    friday_times[1] = "19:00";
    friday_times[2] = "20:00";
    friday_times[3] = "21:30";
    friday_times[4] = "22:00";
    friday_times[5] = "23:00";
    friday_times[6] = "02:00";
    
    // Saturday
    saturday_events[0] = "Breakfast! From the delicious Panera Bread";
    saturday_events[1] = "Lunch by the tasty Currito Burrito";
    saturday_events[2] = "Dinner! Alabama-Q";
    saturday_events[3] = "Delicious air popped POPCORN!";
    
    saturday_times[0] = "8:00";
    saturday_times[1] = "13:00";
    saturday_times[2] = "19:00";
    saturday_times[3] = "01:00";

    
    // Sunday
    sunday_events[0] = "Breakfast of tasty Panera!";
    sunday_events[1] = "Your 36 Hours are up! Hacking ends.";
    sunday_events[2] = "Lunch. Freaky fast... Jimmy John's!";
    sunday_events[3] = "Show us what you hacked! Demos.";
    sunday_events[4] = "Did you win? Closing ceremony.";

    
    sunday_times[0] = "8:00";
    sunday_times[1] = "11:00";
    sunday_times[2] = "11:01";
    sunday_times[3] = "12:00";
    sunday_times[4] = "14:00";


}

static uint16_t menu_get_num_sections_callback(MenuLayer *menu_layer, void *data) {
    return 5;
}

static uint16_t menu_get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
    if (section_index == 0) {
        return 1;
    } else if (section_index == 2) {
        return 7;
    } else if (section_index == 3) {
        return 4;
    } else if (section_index == 4) {
        return 5;
    } else {
        return 0;
    }
}

static int16_t menu_layer_get_cell_height_callback(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context) {
    if (cell_index->section == 0) {
        return 98;
    } else {
        return 44;
    }
}

static int16_t menu_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
    return MENU_CELL_BASIC_HEADER_HEIGHT;
}

static void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
    if (section_index == 0) {
        menu_cell_basic_header_draw(ctx, cell_layer, "Location/Contact");
    } else if (section_index == 2) {
        menu_cell_basic_header_draw(ctx, cell_layer, "Friday 3");
    } else if (section_index == 3) {
        menu_cell_basic_header_draw(ctx, cell_layer, "Saturday 4");
    } else if (section_index == 4) {
        menu_cell_basic_header_draw(ctx, cell_layer, "Sunday 5");
    }
}

static void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
    
    graphics_context_set_text_color(ctx, GColorBlack);
  
    if (cell_index->section == 0) {
        graphics_draw_text(ctx, "Revolution UC", fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD), GRect(5, -4, 139, 98), GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft, NULL);
        graphics_draw_text(ctx, "Rhodes Hall 801", fonts_get_system_font(FONT_KEY_GOTHIC_18), GRect(5, 20, 139, 78), GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft, NULL);
        graphics_draw_text(ctx, "info@revolutionuc.com", fonts_get_system_font(FONT_KEY_GOTHIC_14), GRect(5, 76, 139, 22), GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft, NULL);
    } else if (cell_index->section == 2) {
        float text_height = graphics_text_layout_get_content_size(friday_events[cell_index->row], fonts_get_system_font(FONT_KEY_GOTHIC_14), GRect(3, 0, 100, 44), GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft).h;
        graphics_draw_text(ctx, friday_events[cell_index->row], fonts_get_system_font(FONT_KEY_GOTHIC_14), GRect(3, (44 / 2) - (text_height / 2) - 3, 100, text_height), GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft, NULL);
        graphics_draw_text(ctx, friday_times[cell_index->row], fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD), GRect(100, 10, 41, 20), GTextOverflowModeTrailingEllipsis, GTextAlignmentRight, NULL);
    } else if (cell_index->section == 3) {
        float text_height = graphics_text_layout_get_content_size(saturday_events[cell_index->row], fonts_get_system_font(FONT_KEY_GOTHIC_14), GRect(3, 0, 100, 44), GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft).h;
        graphics_draw_text(ctx, saturday_events[cell_index->row], fonts_get_system_font(FONT_KEY_GOTHIC_14), GRect(3, (44 / 2) - (text_height / 2) - 3, 100, text_height), GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft, NULL);
        graphics_draw_text(ctx, saturday_times[cell_index->row], fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD), GRect(100, 10, 41, 20), GTextOverflowModeTrailingEllipsis, GTextAlignmentRight, NULL);
    } else if (cell_index->section == 4) {
        float text_height = graphics_text_layout_get_content_size(sunday_events[cell_index->row], fonts_get_system_font(FONT_KEY_GOTHIC_14), GRect(3, 0, 100, 44), GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft).h;
        graphics_draw_text(ctx, sunday_events[cell_index->row], fonts_get_system_font(FONT_KEY_GOTHIC_14), GRect(3, (44 / 2) - (text_height / 2) - 3, 100, text_height), GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft, NULL);
        graphics_draw_text(ctx, sunday_times[cell_index->row], fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD), GRect(100, 10, 41, 20), GTextOverflowModeTrailingEllipsis, GTextAlignmentRight, NULL);
    }
}

void window_load(Window *window) {
  
    create_data();

    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_frame(window_layer);

    menu_layer = menu_layer_create(bounds);

    menu_layer_set_callbacks(menu_layer, NULL, (MenuLayerCallbacks){
        .get_num_sections = menu_get_num_sections_callback,
        .get_num_rows = menu_get_num_rows_callback,
        .get_header_height = menu_get_header_height_callback,
        .draw_header = menu_draw_header_callback,
        .draw_row = menu_draw_row_callback,
        .get_cell_height = menu_layer_get_cell_height_callback,
    });

    menu_layer_set_click_config_onto_window(menu_layer, window);

    layer_add_child(window_layer, menu_layer_get_layer(menu_layer));
    
    time_t now = time(NULL);
    struct tm *tick_time = localtime(&now);
    
    int hour = tick_time->tm_hour;
    int day = tick_time->tm_mday;
    
    if (day == 3 || day == 4 || day == 5) {
        MenuIndex selected;
        selected.section = day - 1;

        if (day == 3) {
            for (int i = 0; i < 13; i++) {
                int event_hour = friday_hours[i];
                if (event_hour < hour) {
                    selected.row = i;
                } else if (event_hour == hour) {
                    selected.row = i;
                    break;
                }
            }
        } else if (day == 4) {
            for (int i = 0; i < 8; i++) {
                int event_hour = saturday_hours[i];
                if (event_hour < hour) {
                    selected.row = i;
                } else if (event_hour == hour) {
                    selected.row = i;
                    break;
                }
            }
        } else if (day == 5) {
            for (int i = 0; i < 5; i++) {
                int event_hour = sunday_hours[i];
                if (event_hour < hour) {
                    selected.row = i;
                } else if (event_hour == hour) {
                    selected.row = i;
                    break;
                }
            }
        }
        
        menu_layer_set_selected_index(menu_layer, selected, MenuRowAlignCenter, false);
    }
}

void window_unload(Window *window) {
    menu_layer_destroy(menu_layer);
}

int main(void) {
    window = window_create();
//    window_set_click_config_provider(window, click_config_provider);
    window_set_window_handlers(window, (WindowHandlers) {
        .load = window_load,
        .unload = window_unload,
    });
    window_stack_push(window, true);
    app_event_loop();
    window_destroy(window);
}