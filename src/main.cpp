/*
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: Copyright (c) 2021 Jason Skuby (mytechtoybox.com)
 */

// Pi Pico includes
#include "pico/multicore.h"

// GP2040 includes
#include "gp2040.h"

int main() {
	// Create GP2040 Main Core (core0), Core1 is dependent on Core0
	GP2040 * gp2040 = new GP2040();
	gp2040->setup();

	// Start Core0 Loop
	gp2040->run();
	return 0;
}
