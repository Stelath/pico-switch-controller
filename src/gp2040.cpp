// GP2040 includes
#include "gp2040.h"

// Pico includes
#include "pico/bootrom.h"

// TinyUSB
#include "usb_driver.h"
#include "tusb.h"

#define GAMEPAD_DEBOUNCE_MILLIS 5 // make this a class object

GP2040::GP2040() {}

GP2040::~GP2040() {
}

void GP2040::setup() {
    // Setup Gamepad and Gamepad Storage
	gamepad = new Gamepad(GAMEPAD_DEBOUNCE_MILLIS);
	gamepad->setup();

	// Check for Config or Regular Input (w/ Button Combos)
	InputMode inputMode = gamepad->options.inputMode;
	gamepad->read();
	
	// inputMode = INPUT_MODE_HID;
	// inputMode = INPUT_MODE_SWITCH;
	inputMode = INPUT_MODE_XINPUT;
	gamepad->options.inputMode = inputMode;
	gamepad->save();
	initialize_driver(inputMode);
}

void GP2040::run() {
	while (1) { // LOOP
		if (nextRuntime > getMicro()) { // fix for unsigned
			sleep_us(50); // Give some time back to our CPU (lower power consumption)
			continue;
		}

		// Gamepad Features
		gamepad->read(); 	// gpio pin reads
	#if GAMEPAD_DEBOUNCE_MILLIS > 0
		gamepad->debounce();
	#endif
		gamepad->process(); // process through MPGS

		// USB FEATURES : Send/Get USB Features (including Player LEDs on X-Input)
		send_report(gamepad->getReport(), gamepad->getReportSize());
		
		tud_task(); // TinyUSB Task update

		nextRuntime = getMicro() + GAMEPAD_POLL_MICRO;
	}
}
