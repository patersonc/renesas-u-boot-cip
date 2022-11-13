/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * include/configs/rcar-gen3-common.h
 *	This file is R-Car Gen3 common configuration file.
 *
 * Copyright (C) 2015-2017 Renesas Electronics Corporation
 */

#ifndef __RCAR_GEN3_COMMON_H
#define __RCAR_GEN3_COMMON_H

#include <asm/arch/rmobile.h>

#define CONFIG_REMAKE_ELF

#ifdef CONFIG_SPL
#define CONFIG_SPL_TARGET	"spl/u-boot-spl.scif"
#endif

#define CONFIG_SYS_BOOTPARAMS_LEN	SZ_128K

/* boot option */

#define CONFIG_CMDLINE_TAG
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG

/* Generic Interrupt Controller Definitions */
#define CONFIG_GICV2
#define GICD_BASE	0xF1010000
#define GICC_BASE	0xF1020000

/* console */
#define CONFIG_SYS_CBSIZE		2048
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE
#define CONFIG_SYS_MAXARGS		64
#define CONFIG_SYS_BAUDRATE_TABLE	{ 115200, 38400 }

/* PHY needs a longer autoneg timeout */
#define PHY_ANEG_TIMEOUT		20000

/* MEMORY */
#define CONFIG_SYS_INIT_SP_ADDR		CONFIG_SYS_TEXT_BASE

#define DRAM_RSV_SIZE			0x08000000
#define CONFIG_SYS_SDRAM_BASE		(0x40000000 + DRAM_RSV_SIZE)
#define CONFIG_SYS_SDRAM_SIZE		(0x80000000u - DRAM_RSV_SIZE)
#define CONFIG_SYS_LOAD_ADDR		0x58000000
#define CONFIG_LOADADDR			CONFIG_SYS_LOAD_ADDR
#define CONFIG_VERY_BIG_RAM
#define CONFIG_MAX_MEM_MAPPED		(0x80000000u - DRAM_RSV_SIZE)

#define CONFIG_SYS_MONITOR_BASE		0x00000000
#define CONFIG_SYS_MONITOR_LEN		(1 * 1024 * 1024)
#define CONFIG_SYS_MALLOC_LEN		(64 * 1024 * 1024)
#define CONFIG_SYS_BOOTM_LEN		(64 << 20)

/* The HF/QSPI layout permits up to 1 MiB large bootloader blob */
#define CONFIG_BOARD_SIZE_LIMIT		2097152

/* ENV setting */

#define CONFIG_EXTRA_ENV_SETTINGS	\
	"fdt_addr_r=0x48000000\0" \
	"fdtfile=r8a774a1-hihope-rzg2m.dtb\0" \
	"kernel_addr_r=0x48080000\0" \
	"boot_efi_binary=efi/boot/"BOOTEFI_NAME"\0" \
	"scan_boot_efi=" \
		"part list ${devtype} ${devnum} devplist; "  \
		"env exists devplist || setenv devplist 1; " \
		"for distro_bootpart in ${devplist}; do " \
			"if test -e ${devtype} ${devnum}:${distro_bootpart} ${boot_efi_binary}; then " \
				"load ${devtype} ${devnum}:${distro_bootpart} " \
				"${kernel_addr_r} ${boot_efi_binary};"          \
				"echo BootEFI from <${devtype}> [${devnum}:${distro_bootpart}]; "\
				"bootefi ${kernel_addr_r};"                     \
			"fi;" \
		"done;\0" \
	"mmc0=" \
			"setenv devnum 0;" \
			"setenv devtype mmc;" \
			"run scan_boot_efi;\0" \
	"mmc1=" \
			"setenv devnum 1;" \
			"setenv devtype mmc;" \
			"run scan_boot_efi;\0" \
	"usb0=" \
			"usb start;" \
			"setenv devnum 0;" \
			"setenv devtype usb;" \
			"run scan_boot_efi;\0"\
	"usb1=" \
			"usb start;" \
			"setenv devnum 1;" \
			"setenv devtype usb;" \
			"run scan_boot_efi;\0" \
	"boot_targets=" \
			"mmc0 mmc1 usb0 usb1\0" \
	"distro_bootcmd=" \
			"env exists boot_targets || setenv boot_targets mmc0 mmc1 usb0 usb1; " \
			"for target in ${boot_targets}; do "\
				"run ${target};" \
			"done;" \
	"bootcmd=run distro_bootcmd\0" \


#ifndef CONFIG_SPL_BUILD
#define BOOT_TARGET_DEVICES(func) \
        func(MMC, mmc, 1) \
        func(MMC, mmc, 0) \
        func(USB, usb, 0) \
        func(PXE, pxe, na) \
        func(DHCP, dhcp, na)
#include <config_distro_bootcmd.h>
#endif

/* SPL support */
#if defined(CONFIG_R8A7795) || defined(CONFIG_R8A7796) || defined(CONFIG_R8A77965)
#define CONFIG_SPL_BSS_START_ADDR	0xe633f000
#define CONFIG_SPL_BSS_MAX_SIZE		0x1000
#else
#define CONFIG_SPL_BSS_START_ADDR	0xe631f000
#define CONFIG_SPL_BSS_MAX_SIZE		0x1000
#endif
#define CONFIG_SPL_STACK		0xe6304000
#define CONFIG_SPL_MAX_SIZE		0x7000
#ifdef CONFIG_SPL_BUILD
#define CONFIG_CONS_SCIF2
#define CONFIG_SH_SCIF_CLK_FREQ		65000000
#endif

#endif	/* __RCAR_GEN3_COMMON_H */
