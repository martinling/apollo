/**
 * Code for basic FPGA interfacing.
 *
 * This file is part of LUNA.
 *
 * Copyright (c) 2020-2023 Great Scott Gadgets <info@greatscottgadgets.com>
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdbool.h>

#include <bsp/board_api.h>
#include <hal/include/hal_gpio.h>

#include <apollo_board.h>

/**
 * Sets up the I/O pins needed to configure the FPGA.
 */
void fpga_io_init(void)
{
	// By default, keep PROGRAM_N from being driven.
	gpio_set_pin_level(FPGA_PROGRAM, true);
	gpio_set_pin_direction(FPGA_PROGRAM, GPIO_DIRECTION_IN);
}

/*
 * Allows or disallows the FPGA from configuring from flash. When disallowed,
 * initialization (erasing of configuration memory) takes place, but the FPGA
 * does not proceed to the configuration phase.
 */
void permit_fpga_configuration(bool enable)
{
#if ((_BOARD_REVISION_MAJOR_ == 1) && (_BOARD_REVISION_MINOR_ > 2))
	gpio_set_pin_level(FPGA_INITN, enable);
	gpio_set_pin_direction(FPGA_INITN, GPIO_DIRECTION_OUT);

	/*
	 * Delay a bit (in case the FPGA is already initializing) because
	 * TN-02039 says that PROGRAMN should not have a falling edge during
	 * initialization.
	 */
	board_delay(1);
#endif
}

/**
 * Requests that the FPGA clear its configuration and try to reconfigure.
 */
void trigger_fpga_reconfiguration(void)
{
	permit_fpga_configuration(true);

	gpio_set_pin_direction(FPGA_PROGRAM, GPIO_DIRECTION_OUT);
	gpio_set_pin_level(FPGA_PROGRAM, false);

	board_delay(1);

	gpio_set_pin_level(FPGA_PROGRAM, true);
	gpio_set_pin_direction(FPGA_PROGRAM, GPIO_DIRECTION_IN);
}

/**
 * Requests that we hold the FPGA in an unconfigured state.
 */
void force_fpga_offline(void)
{
	permit_fpga_configuration(false);

	gpio_set_pin_direction(FPGA_PROGRAM, GPIO_DIRECTION_OUT);
	gpio_set_pin_level(FPGA_PROGRAM, false);
}
