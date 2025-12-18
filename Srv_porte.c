// door.c
#include "Srv_porte.h"
#include "driver/gpio.h"
#include "esp_timer.h"

static int door_gpio = -1;
static bool last_state = false;
static int64_t open_time = 0;
static int64_t duration = 0;

void door_init(int gpio_num) {
    door_gpio = gpio_num;
    gpio_set_direction(door_gpio, GPIO_MODE_INPUT);
}

void door_update(void) {
    bool state = gpio_get_level(door_gpio);

    if (state && !last_state) {
        // Door just opened
        open_time = esp_timer_get_time();
        duration = 0;
    }

    if (state) {
        duration = (esp_timer_get_time() - open_time) / 1000; // ms
    }

    if (!state && last_state) {
        // Door just closed
        duration = 0;
    }

    last_state = state;
}

bool door_is_open(void) {
    return gpio_get_level(door_gpio);
}

int64_t door_get_open_duration(void) {
    return duration;
}
