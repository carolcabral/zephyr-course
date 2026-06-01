#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include "my_driver.h"

#define DT_DRV_COMPAT our_driver

LOG_MODULE_REGISTER(our_driver, LOG_LEVEL_INF);

struct led_sensor_data {
    uint32_t blink_interval_ms;
};

struct led_sensor_config {
    struct gpio_dt_spec led;
};

static int sample_fetch_impl(const struct device *dev, enum sensor_channel chan)
{
    const struct led_sensor_config *cfg = dev->config;

    LOG_INF("sample_fetch: turning LED ON, channel %d", chan);
    return gpio_pin_set_dt(&cfg->led, 1);
}

static int channel_get_impl(const struct device *dev,
                            enum sensor_channel chan,
                            struct sensor_value *val)
{
    const struct led_sensor_config *cfg = dev->config;

    LOG_INF("channel_get: turning LED OFF, channel %d", chan);
    val->val1 = 0;
    val->val2 = 0;
    return gpio_pin_set_dt(&cfg->led, 0);
}

int led_sensor_set_blink_interval(const struct device *dev, uint32_t interval_ms)
{
    struct led_sensor_data *data = dev->data;

    LOG_INF("Setting blink interval to %u ms", interval_ms);
    data->blink_interval_ms = interval_ms;
    return 0;
}

static DEVICE_API(sensor, led_sensor_api) = {
    .sample_fetch = sample_fetch_impl,
    .channel_get  = channel_get_impl,
};

static int led_sensor_init(const struct device *dev)
{
    const struct led_sensor_config *cfg = dev->config;

    if (!gpio_is_ready_dt(&cfg->led)) {
        LOG_ERR("LED GPIO not ready");
        return -ENODEV;
    }

    gpio_pin_configure_dt(&cfg->led, GPIO_OUTPUT_INACTIVE);
    LOG_INF("Device initialized");
    return 0;
}

/*
 * Init Levels:
 * PRE_KERNEL_1  - basic hw (clocks, pinmux, gpio controllers)
 * PRE_KERNEL_2  - hw depending on kernel drivers (SPI bus)
 * POST_KERNEL   - kernel is running (most drivers)
 * APPLICATION   - after POST_KERNEL (high-level subsystems)
 */
#define LED_SENSOR_INST(inst)                                                   \
    static struct led_sensor_data led_sensor_data_##inst;                       \
    static const struct led_sensor_config led_sensor_cfg_##inst = {             \
        .led = GPIO_DT_SPEC_INST_GET(inst, led_gpios),                          \
    };                                                                          \
    DEVICE_DT_INST_DEFINE(inst, led_sensor_init, NULL,                          \
                          &led_sensor_data_##inst, &led_sensor_cfg_##inst,      \
                          POST_KERNEL, 80, &led_sensor_api);

DT_INST_FOREACH_STATUS_OKAY(LED_SENSOR_INST)
