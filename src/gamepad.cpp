/*
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: Copyright (c) 2021 Jason Skuby (mytechtoybox.com)
 */

// GP2040 Libraries
#include "gamepad.h"
#include "GamepadStorage.h"

#include "FlashPROM.h"
#include "CRC32.h"

// MUST BE DEFINED for mpgs
uint32_t getMillis() {
	return to_ms_since_boot(get_absolute_time());
}

uint64_t getMicro() {
	return to_us_since_boot(get_absolute_time());
}

void Gamepad::setup()
{
	load(); // MPGS loads
}

void Gamepad::process()
{
	memcpy(&rawState, &state, sizeof(GamepadState));
	MPGS::process();
}

void Gamepad::read()
{
	state.dpad = 3;

	state.buttons = 0;

	// state.lx = GAMEPAD_JOYSTICK_MID;
	state.lx = 0;
	state.ly = GAMEPAD_JOYSTICK_MID;
	state.rx = GAMEPAD_JOYSTICK_MID;
	state.ry = GAMEPAD_JOYSTICK_MID;
	state.lt = 0;
	state.rt = 0;
}


/* Gamepad stuffs */
void GamepadStorage::start()
{
	EEPROM.start();
}

void GamepadStorage::save()
{
	EEPROM.commit();
}

GamepadOptions GamepadStorage::getGamepadOptions()
{
	GamepadOptions options;
	return options;
}

void GamepadStorage::setGamepadOptions(GamepadOptions options)
{
}

