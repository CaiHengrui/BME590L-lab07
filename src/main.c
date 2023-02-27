/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS 1000

#define LED_ON_TIME_MS 1000
#define DEC_ON_TIME_MS 100
#define INC_ON_TIME_MS 100

#define MIN_ON_TIME_MS 100
#define MAX_ON_TIME_MS 2000


/* The devicetree node identifier for the "led0" alias. */
// #define LED0_NODE DT_ALIAS(led0)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */

//static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

//LEDs//
static const struct gpio_dt_spec heartbeat_led = GPIO_DT_SPEC_GET(DT_ALIAS(heartbeat), gpios);
static const struct gpio_dt_spec buzzer_led = GPIO_DT_SPEC_GET(DT_ALIAS(buzzer), gpios);
static const struct gpio_dt_spec ivdrip_led = GPIO_DT_SPEC_GET(DT_ALIAS(ivdrip), gpios);
static const struct gpio_dt_spec alarm_led = GPIO_DT_SPEC_GET(DT_ALIAS(alarm), gpios);
static const struct gpio_dt_spec error_led = GPIO_DT_SPEC_GET(DT_ALIAS(error), gpios);

//buttons//
static const struct gpio_dt_spec sleep = GPIO_DT_SPEC_GET(DT_ALIAS(button0), gpios);
static const struct gpio_dt_spec freq_up = GPIO_DT_SPEC_GET(DT_ALIAS(button1), gpios);
static const struct gpio_dt_spec freq_down = GPIO_DT_SPEC_GET(DT_ALIAS(button2), gpios);
static const struct gpio_dt_spec reset = GPIO_DT_SPEC_GET(DT_ALIAS(button3), gpios);

//Initialize GPIO Callback struct
static struct gpio_callback sleep_cb;
static struct gpio_callback freq_up_cb;
static struct gpio_callback freq_down_cb;
static struct gpio_callback reset_cb;

/* Declarations */
int check_interfaces_ready(void);
int setup_channels_and_pins(void);
    //declare callback function
void sleep_callback(const struct device *dev, struct gpio_callback *cb, uint32_t pins);
void freq_up_callback(const struct device *dev, struct gpio_callback *cb, uint32_t pins);
void freq_down_callback(const struct device *dev, struct gpio_callback *cb, uint32_t pins);
void reset_callback(const struct device *dev, struct gpio_callback *cb, uint32_t pins);


/* Callbacks */
void sleep_callback(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{

}

void freq_up_callback(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{

}

void freq_down_callback(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{

}

void reset_callback(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
(

)




void main(void)
{
/*	int ret;
//? This is the equivalent of the setup function from an Arduino perspective.
	if (!device_is_ready(led.port)) {
		return;
	}

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return;
	}
/*/

	int err;

	err = check_interfaces_ready();
	if (err) {
		LOG_ERR("Device interfaces not ready (err = %d)",err);
	}

	err = setup_channels_and_pins();
	if (err) {
		LOG_ERR("Error configuring IO channels / pins (err = %d)", err);
	}
    


	while (1) {
		err = gpio_pin_toggle_dt(&heartbeat_led); //??How to define lED is on /off
		if (err < 0) {
			return;
		}
		k_msleep(SLEEP_TIME_MS);
	}//The heartbeat LED blinks at a fixed 1 Hz while main() is being executed ???

    /* Setup callbacks *//*callback for limits*/
    err = gpio_pin_interrupt_configure_dt(&sleep, GPIO_INT_EDGE_TO_ACTIVE);		
	gpio_init_callback(&sleep_cb, sleep_callback, BIT(sleep.pin));
	gpio_add_callback(sleep.port, &sleep_cb);

    err = gpio_pin_interrupt_configure_dt(&freq_up, GPIO_INT_EDGE_TO_ACTIVE);		
	gpio_init_callback(&freq_up, freq_up_callback, BIT(freq_up.pin));
	gpio_add_callback(freq_up.port, &freq_up_cb);

	err = gpio_pin_interrupt_configure_dt(&freq_down, GPIO_INT_EDGE_TO_ACTIVE);		
	gpio_init_callback(&freq_down_cb, freq_down_callback, BIT(freq_down.pin));
	gpio_add_callback(freq_down.port, &freq_down_cb);
/*callback for limits*/
	err = gpio_pin_interrupt_configure_dt(&reset, GPIO_INT_EDGE_TO_ACTIVE);		
	gpio_init_callback(&reset_cb, reset_callback, BIT(reset.pin));
	gpio_add_callback(reset.port, &reset_cb);
}

int check_interfaces_ready(void)
{
	/* Check if all devices are ready to go */
//Why need only one???
	/* This should check for the entire gpio0 interface */
	if (!device_is_ready(heartbeat_led.port)) {
		LOG_ERR("gpio0 interface not ready.");
		return -1;
	}
	
	/* This should check for the entire gpio1 interface */
	if (!device_is_ready(error_led.port)) {
		LOG_ERR("gpio1 interface not ready.");
		return -1;
	}

	return 0;
}

int setup_channels_and_pins(void)
{
	int err;

	/* Configure  GPIO pins */
	err = gpio_pin_configure_dt(&heartbeat_led, GPIO_ACTIVE_LOW);
	if (err < 0) {
		LOG_ERR("Cannot configure heartbeat LED.");
		return err;
	}

	err = gpio_pin_configure_dt(&buzzer_led, GPIO_ACTIVE_LOW);
	if (err < 0) {
		LOG_ERR("Cannot configure buzzer LED.");
		return err;
	}

	err = gpio_pin_configure_dt(&ivdrip_led, GPIO_ACTIVE_LOW);
	if (err < 0) {
		LOG_ERR("Cannot configure ivdrip LED.");
		return err;
	}

	err = gpio_pin_configure_dt(&alarm_led, GPIO_ACTIVE_LOW);
	if (err < 0) {
		LOG_ERR("Cannot configure alarm LED.");
		return err;
	}

	err = gpio_pin_configure_dt(&error_led, GPIO_ACTIVE_LOW);
	if (err < 0) {
		LOG_ERR("Cannot configure error LED.");
		return err;
	}

	err = gpio_pin_configure_dt(&sleep, GPIO_INPUT);
	if (err < 0) {
		LOG_ERR("Cannot configure sleep button.");
		return err;
	}
	
	err = gpio_pin_configure_dt(&freq_up, GPIO_INPUT);
		if (err < 0) {
		LOG_ERR("Cannot configure frequency up button.");
		return err;
	}

	err = gpio_pin_configure_dt(&freq_down, GPIO_INPUT);
		if (err < 0) {
		LOG_ERR("Cannot configure frequency down button.");
		return err;
	}

	err = gpio_pin_configure_dt(&reset, GPIO_INPUT);
	if (err < 0) {
		LOG_ERR("Cannot configure reset button.");
		return err;
	}

	return 0;
}