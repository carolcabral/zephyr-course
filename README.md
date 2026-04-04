# Zephyr Training Environment

Welcome to the Zephyr RTOS training! This repository includes a ready-to-use
development environment based on Zephyr 4.3.0, which you can set up in one of
three ways:

---

## Manual Zephyr Setup

Follow the following guide:
- [Getting Started Guide](https://docs.zephyrproject.org/latest/develop/getting_started/index.html#).

Make sure to select appropriate OS and to perform all steps till
[Build the Blinky Sample](https://docs.zephyrproject.org/latest/develop/getting_started/index.html#build-the-blinky-sample).


## Boards

**Nucleo L423KC**

[Nucleo L432KC Zephyr Documentation](https://docs.zephyrproject.org/latest/boards/st/nucleo_l432kc/doc/index.html)

```
west build -b nucleo_l432kc -p always app
west flash --runner stm32cubeprogrammer
```

