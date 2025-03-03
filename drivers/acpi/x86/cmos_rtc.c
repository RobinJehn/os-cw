// SPDX-License-Identifier: GPL-2.0-only
/*
 * ACPI support for CMOS RTC Address Space access
 *
 * Copyright (C) 2013, Intel Corporation
 * Authors: Lan Tianyu <tianyu.lan@intel.com>
 */

#define pr_fmt(fmt) "ACPI: " fmt

#include <linux/acpi.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mc146818rtc.h>

#include "../internal.h"

static const struct acpi_device_id acpi_cmos_rtc_ids[] = {
	{ "PNP0B00" },
	{ "PNP0B01" },
	{ "PNP0B02" },
	{}
};

static acpi_status
acpi_cmos_rtc_space_handler(u32 function, acpi_physical_address address,
		      u32 bits, u64 *value64,
		      void *handler_context, void *region_context)
{
	int i;
	u8 *value = (u8 *)value64;

	if (address > 0xff || !value64)
		return AE_BAD_PARAMETER;

	if (function != ACPI_WRITE && function != ACPI_READ)
		return AE_BAD_PARAMETER;

	spin_lock_irq(&rtc_lock);

	for (i = 0; i < DIV_ROUND_UP(bits, 8); ++i, ++address, ++value)
		if (function == ACPI_READ)
			*value = CMOS_READ(address);
		else
			CMOS_WRITE(*value, address);

	spin_unlock_irq(&rtc_lock);

	return AE_OK;
}

int acpi_install_cmos_rtc_space_handler(acpi_handle handle)
{
	acpi_status status;

	status = acpi_install_address_space_handler(handle,
			ACPI_ADR_SPACE_CMOS,
			&acpi_cmos_rtc_space_handler,
			NULL, NULL);
	if (ACPI_FAILURE(status)) {
		pr_err("Error installing CMOS-RTC region handler\n");
		return -ENODEV;
	}

	return 1;
}
EXPORT_SYMBOL_GPL(acpi_install_cmos_rtc_space_handler);

void acpi_remove_cmos_rtc_space_handler(acpi_handle handle)
{
	if (ACPI_FAILURE(acpi_remove_address_space_handler(handle,
			ACPI_ADR_SPACE_CMOS, &acpi_cmos_rtc_space_handler)))
		pr_err("Error removing CMOS-RTC region handler\n");
}
EXPORT_SYMBOL_GPL(acpi_remove_cmos_rtc_space_handler);

static int acpi_cmos_rtc_attach_handler(struct acpi_device *adev, const struct acpi_device_id *id)
{
	return acpi_install_cmos_rtc_space_handler(adev->handle);
}

static void acpi_cmos_rtc_detach_handler(struct acpi_device *adev)
{
	acpi_remove_cmos_rtc_space_handler(adev->handle);
}

static struct acpi_scan_handler cmos_rtc_handler = {
	.ids = acpi_cmos_rtc_ids,
	.attach = acpi_cmos_rtc_attach_handler,
	.detach = acpi_cmos_rtc_detach_handler,
};

void __init acpi_cmos_rtc_init(void)
{
	acpi_scan_add_handler(&cmos_rtc_handler);
}
