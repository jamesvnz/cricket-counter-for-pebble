#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"
#include "cricket.h"
#include "mini-printf.h"

#define PEBBLE_WIDTH 144 - ACTION_BAR_WIDTH
#define HORIZONTAL_MARGIN 4
#define VERTICAL_MARGIN 6


#define MY_UUID { 0xA4, 0x73, 0xDD, 0xEB, 0xDA, 0xF1, 0x44, 0x2B, 0x8A, 0xF9, 0x7B, 0xC6, 0x0A, 0x20, 0x53, 0x39 }
PBL_APP_INFO(MY_UUID,
             "Cricket Counter", "Adam Harvey",
             0, 1, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_STANDARD_APP);

struct {
    Layer top;
    ActionBarLayer actionBar;
    TextLayer ball;
    TextLayer over;
    TextLayer wicket;
} layers;

AppTimerHandle timer;
Window window;
Innings innings;

char ballBuffer[8];
char overBuffer[17];
char wicketBuffer[12];

void update_text() {
    mini_snprintf(ballBuffer, sizeof(ballBuffer), "Ball: %u", innings_get_ball(&innings));
    text_layer_set_text(&layers.ball, ballBuffer);

    mini_snprintf(overBuffer, sizeof(overBuffer), "Over: %u", innings_get_over(&innings));
    text_layer_set_text(&layers.over, overBuffer);

    mini_snprintf(wicketBuffer, sizeof(wicketBuffer), "Wickets: %u", innings_get_wicket(&innings));
    text_layer_set_text(&layers.wicket, wicketBuffer);
}

void handle_down(ClickRecognizerRef recognizer, void *ctx) {
    (void) recognizer;
    (void) ctx;

    innings_decrement_ball(&innings);
    update_text();
}

void handle_select(ClickRecognizerRef recognizer, void *ctx) {
    (void) recognizer;
    (void) ctx;

    innings_increment_wicket(&innings);
    update_text();
}

void handle_up(ClickRecognizerRef recognizer, void *ctx) {
    (void) recognizer;
    (void) ctx;

    innings_increment_ball(&innings);
    update_text();
}

void click_config_provider(ClickConfig **config, void *ctx) {
    (void) ctx;

    config[BUTTON_ID_UP]->click.handler = handle_up;
    config[BUTTON_ID_UP]->click.repeat_interval_ms = 100;
    config[BUTTON_ID_DOWN]->click.handler = handle_down;
    config[BUTTON_ID_DOWN]->click.repeat_interval_ms = 100;
    config[BUTTON_ID_SELECT]->click.handler = handle_select;
    config[BUTTON_ID_SELECT]->click.repeat_interval_ms = 100;
}

void update_top_callback(Layer *me, GContext *ctx) {
    (void) me;

    update_text();
}

void handle_init(AppContextRef ctx) {
    resource_init_current_app(&CRICKET_COUNTER_RESOURCES);

    window_init(&window, "Cricket Counter");
    window_set_background_color(&window, GColorBlack);
    window_stack_push(&window, true /* Animated */);

    innings_init(&innings);

    layer_init(&layers.top, window.layer.frame);
    layers.top.update_proc = update_top_callback;
    layer_add_child(&window.layer, &layers.top);

    action_bar_layer_init(&layers.actionBar);
    action_bar_layer_add_to_window(&layers.actionBar, &window);
    action_bar_layer_set_click_config_provider(&layers.actionBar, click_config_provider);

    text_layer_init(&layers.ball, GRect(HORIZONTAL_MARGIN, VERTICAL_MARGIN, PEBBLE_WIDTH - 2 * VERTICAL_MARGIN, 50));
    text_layer_set_background_color(&layers.ball, GColorBlack);
    text_layer_set_font(&layers.ball, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_40)));
    text_layer_set_text_alignment(&layers.ball, GTextAlignmentCenter);
    text_layer_set_text_color(&layers.ball, GColorWhite);
    layer_add_child(&layers.top, &layers.ball.layer);

    text_layer_init(&layers.over, GRect(HORIZONTAL_MARGIN, 3 * VERTICAL_MARGIN + 50, PEBBLE_WIDTH - 2 * VERTICAL_MARGIN, 32));
    text_layer_set_background_color(&layers.over, GColorBlack);
    text_layer_set_font(&layers.over, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_24)));
    text_layer_set_text_alignment(&layers.over, GTextAlignmentCenter);
    text_layer_set_text_color(&layers.over, GColorWhite);
    layer_add_child(&layers.top, &layers.over.layer);

    text_layer_init(&layers.wicket, GRect(HORIZONTAL_MARGIN, 5 * VERTICAL_MARGIN + 82, PEBBLE_WIDTH - 2 * VERTICAL_MARGIN, 28));
    text_layer_set_background_color(&layers.wicket, GColorBlack);
    text_layer_set_font(&layers.wicket, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_20)));
    text_layer_set_text_alignment(&layers.wicket, GTextAlignmentCenter);
    text_layer_set_text_color(&layers.wicket, GColorWhite);
    layer_add_child(&layers.top, &layers.wicket.layer);
}

void pbl_main(void *params) {
    PebbleAppHandlers handlers = {
        .init_handler = &handle_init
    };

    app_event_loop(params, &handlers);
}
