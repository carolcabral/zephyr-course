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

## Lecture 03 - App configuration KConfig

### Config file roles

| File  | Purpose |
|------|----------|
| `prj.conf` | App-specific options; checked into repo; survives board changes |
| `defconfig` | Hardware defaults for a specific board/SoC; don't edit unless writing a board port |
| `build/zephyr/.config` | Merged result of all sources; edited by menuconfig |
| `build/zephyr/include/generated/zephyr/autoconf.h` | C macros generated from `.config`; updated only on rebuild |

**Merge order** (last wins):
```
Kconfig defaults → defconfig → prj.conf → menuconfig (.config)
```
- `prj.conf` overrides `defconfig`, and a manual `menuconfig` change overrides both — but only until the next pristine build wipes `.config.`

### Menuconfig

```sh
west build -t menuconfig   # opens the interactive config UI
west build                 # rebuild to apply changes to autoconf.h
```

Menuconfig saves choices to `build/zephyr/.config`. **`autoconf.h` is only updated when you rebuild** — changing an option in menuconfig without rebuilding has no effect on the compiled binary.
- `-p always` deletes the entire build directory!
