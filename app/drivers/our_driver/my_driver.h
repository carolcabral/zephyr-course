#ifndef MY_DRIVER_H
#define MY_DRIVER_H

#include <zephyr/device.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Set the blink interval stored in the driver's runtime data. */
int led_sensor_set_blink_interval(const struct device *dev, uint32_t interval_ms);

#ifdef __cplusplus
}
#endif

#endif /* MY_DRIVER_H */
