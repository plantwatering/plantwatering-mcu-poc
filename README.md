# Plantwatering MCU - POC

![](https://github.com/plantwatering/plantwatering-mcu-poc/workflows/CI/badge.svg)

This is only a quick made proof of concept.
It is based on [this file](https://github.com/adafruit/Adafruit_nRF52_Arduino/blob/master/libraries/Bluefruit52Lib/examples/Peripheral/custom_hrm/custom_hrm.ino)

## Hardware

We are using an [Adafruit Feather nRF52840 Express](https://www.adafruit.com/product/4062).

## Software

As this is a POC, we are using the Arduino/Adafruit libraries. Please follow [this link](https://learn.adafruit.com/introducing-the-adafruit-nrf52840-feather/arduino-bsp-setup)
to setup sources.

### Design

Code source which is not part of the Arduino sdk is inspired from the linux devices/drivers
in a easier way. This is an example with valve subsystem:
```c
struct valve {
    int (*set)(struct valve *v, bool value);
    int (*get)(const struct valve *v, bool *value);
    void (*notificate)(const struct valve *v, bool value);
    struct valve_driver *drv;
};
```
That what the valve subsystem is, and a corresponding driver is ``valve_console_driver``
for instance. This last implements the ``valve_driver`` c interface which is:
```c
struct valve_driver {
    int (*open)(struct valve_driver* drv);
    int (*close)(struct valve_driver* drv);
    int (*get_state)(const struct valve_driver* drv, bool *value);
    void *priv;
};
```
To use all this together, you can do the following:
```c
int ret;
struct valve_driver *drv;
struct valve *v;

ret = valve_console_init(drv);
/* do somthing with ret */
ret = valve_init(v, drv);
/* do somehting with ret */

/* you can call valve methods now */
bool status;
ret = v->get(v, &status);
/* do somehting with ret */

static void notificate_custom(const struct valve *v, bool value)
{
    printf("New value of valve %p: %d", value);
}

v->notificate = notificate_custom;
ret = v->set(v, true); /* <-- will call notificate_custom with true as a value */
/* do somehting with ret */
```
