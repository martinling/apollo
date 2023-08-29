/*
 * switch control for USB port shared by Apollo and FPGA
 *
 * This file is part of Apollo.
 *
 * Copyright (c) 2023 Great Scott Gadgets <info@greatscottgadgets.com>
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __USB_SWITCH_H__
#define __USB_SWITCH_H__

/**
 * Initialize USB switch control
 */
void usb_switch_init(void);

/**
 * Hand off shared USB port to FPGA.
 */
void hand_off_usb(void);

/**
 * Take control of USB port from FPGA.
 */
void take_over_usb(void);

/**
 * Honor requests from FPGA_ADV again
 */
void honor_fpga_adv(void);

/**
 * Handle switch control user request.
 */
void switch_control_task(void);


#endif
