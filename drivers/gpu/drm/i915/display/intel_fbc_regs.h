/* SPDX-License-Identifier: MIT */
/* Copyright © 2024 Intel Corporation */

#ifndef __INTEL_FBC_REGS__
#define __INTEL_FBC_REGS__

#include "intel_display_reg_defs.h"

#define FBC_CFB_BASE		_MMIO(0x3200) /* 4k page aligned */
#define FBC_LL_BASE		_MMIO(0x3204) /* 4k page aligned */
#define FBC_CONTROL		_MMIO(0x3208)
#define   FBC_CTL_EN			REG_BIT(31)
#define   FBC_CTL_PERIODIC		REG_BIT(30)
#define   FBC_CTL_INTERVAL_MASK		REG_GENMASK(29, 16)
#define   FBC_CTL_INTERVAL(x)		REG_FIELD_PREP(FBC_CTL_INTERVAL_MASK, (x))
#define   FBC_CTL_STOP_ON_MOD		REG_BIT(15)
#define   FBC_CTL_UNCOMPRESSIBLE	REG_BIT(14) /* i915+ */
#define   FBC_CTL_C3_IDLE		REG_BIT(13) /* i945gm only */
#define   FBC_CTL_STRIDE_MASK		REG_GENMASK(12, 5)
#define   FBC_CTL_STRIDE(x)		REG_FIELD_PREP(FBC_CTL_STRIDE_MASK, (x))
#define   FBC_CTL_FENCENO_MASK		REG_GENMASK(3, 0)
#define   FBC_CTL_FENCENO(x)		REG_FIELD_PREP(FBC_CTL_FENCENO_MASK, (x))
#define FBC_COMMAND		_MMIO(0x320c)
#define   FBC_CMD_COMPRESS		REG_BIT(0)
#define FBC_STATUS		_MMIO(0x3210)
#define   FBC_STAT_COMPRESSING		REG_BIT(31)
#define   FBC_STAT_COMPRESSED		REG_BIT(30)
#define   FBC_STAT_MODIFIED		REG_BIT(29)
#define   FBC_STAT_CURRENT_LINE_MASK	REG_GENMASK(10, 0)
#define FBC_CONTROL2		_MMIO(0x3214) /* i965gm only */
#define   FBC_CTL_FENCE_DBL		REG_BIT(4)
#define   FBC_CTL_IDLE_MASK		REG_GENMASK(3, 2)
#define   FBC_CTL_IDLE_IMM		REG_FIELD_PREP(FBC_CTL_IDLE_MASK, 0)
#define   FBC_CTL_IDLE_FULL		REG_FIELD_PREP(FBC_CTL_IDLE_MASK, 1)
#define   FBC_CTL_IDLE_LINE		REG_FIELD_PREP(FBC_CTL_IDLE_MASK, 2)
#define   FBC_CTL_IDLE_DEBUG		REG_FIELD_PREP(FBC_CTL_IDLE_MASK, 3)
#define   FBC_CTL_CPU_FENCE_EN		REG_BIT(1)
#define   FBC_CTL_PLANE_MASK		REG_GENMASK(1, 0)
#define   FBC_CTL_PLANE(i9xx_plane)	REG_FIELD_PREP(FBC_CTL_PLANE_MASK, (i9xx_plane))
#define FBC_FENCE_OFF		_MMIO(0x3218)  /* i965gm only, BSpec typo has 321Bh */
#define FBC_MOD_NUM		_MMIO(0x3220)  /* i965gm only */
#define   FBC_MOD_NUM_MASK		REG_GENMASK(31, 1)
#define   FBC_MOD_NUM_VALID		REG_BIT(0)
#define FBC_TAG(i)		_MMIO(0x3300 + (i) * 4) /* 49 reisters */
#define   FBC_TAG_MASK			REG_GENMASK(1, 0) /* 16 tags per register */
#define   FBC_TAG_MODIFIED		REG_FIELD_PREP(FBC_TAG_MASK, 0)
#define   FBC_TAG_UNCOMPRESSED		REG_FIELD_PREP(FBC_TAG_MASK, 1)
#define   FBC_TAG_UNCOMPRESSIBLE	REG_FIELD_PREP(FBC_TAG_MASK, 2)
#define   FBC_TAG_COMPRESSED		REG_FIELD_PREP(FBC_TAG_MASK, 3)

#define FBC_LL_SIZE		(1536)

#define DPFC_CB_BASE			_MMIO(0x3200)
#define ILK_DPFC_CB_BASE(fbc_id)	_MMIO_PIPE((fbc_id), 0x43200, 0x43240)
#define DPFC_CONTROL			_MMIO(0x3208)
#define ILK_DPFC_CONTROL(fbc_id)	_MMIO_PIPE((fbc_id), 0x43208, 0x43248)
#define   DPFC_CTL_EN				REG_BIT(31)
#define   DPFC_CTL_PLANE_MASK_G4X		REG_BIT(30) /* g4x-snb */
#define   DPFC_CTL_PLANE_G4X(i9xx_plane)	REG_FIELD_PREP(DPFC_CTL_PLANE_MASK_G4X, (i9xx_plane))
#define   DPFC_CTL_FENCE_EN_G4X			REG_BIT(29) /* g4x-snb */
#define   DPFC_CTL_PLANE_MASK_IVB		REG_GENMASK(30, 29) /* ivb only */
#define   DPFC_CTL_PLANE_IVB(i9xx_plane)	REG_FIELD_PREP(DPFC_CTL_PLANE_MASK_IVB, (i9xx_plane))
#define   DPFC_CTL_FENCE_EN_IVB			REG_BIT(28) /* ivb+ */
#define   DPFC_CTL_PERSISTENT_MODE		REG_BIT(25) /* g4x-snb */
#define   DPFC_CTL_PLANE_BINDING_MASK		REG_GENMASK(12, 11) /* lnl+ */
#define   DPFC_CTL_PLANE_BINDING(plane_id)	REG_FIELD_PREP(DPFC_CTL_PLANE_BINDING_MASK, (plane_id))
#define   DPFC_CTL_FALSE_COLOR			REG_BIT(10) /* ivb+ */
#define   DPFC_CTL_SR_EN			REG_BIT(10) /* g4x only */
#define   DPFC_CTL_SR_EXIT_DIS			REG_BIT(9) /* g4x only */
#define   DPFC_CTL_LIMIT_MASK			REG_GENMASK(7, 6)
#define   DPFC_CTL_LIMIT_1X			REG_FIELD_PREP(DPFC_CTL_LIMIT_MASK, 0)
#define   DPFC_CTL_LIMIT_2X			REG_FIELD_PREP(DPFC_CTL_LIMIT_MASK, 1)
#define   DPFC_CTL_LIMIT_4X			REG_FIELD_PREP(DPFC_CTL_LIMIT_MASK, 2)
#define   DPFC_CTL_FENCENO_MASK			REG_GENMASK(3, 0)
#define   DPFC_CTL_FENCENO(fence)		REG_FIELD_PREP(DPFC_CTL_FENCENO_MASK, (fence))
#define DPFC_RECOMP_CTL			_MMIO(0x320c)
#define ILK_DPFC_RECOMP_CTL(fbc_id)	_MMIO_PIPE((fbc_id), 0x4320c, 0x4324c)
#define   DPFC_RECOMP_STALL_EN			REG_BIT(27)
#define   DPFC_RECOMP_STALL_WM_MASK		REG_GENMASK(26, 16)
#define   DPFC_RECOMP_TIMER_COUNT_MASK		REG_GENMASK(5, 0)
#define DPFC_STATUS			_MMIO(0x3210)
#define ILK_DPFC_STATUS(fbc_id)		_MMIO_PIPE((fbc_id), 0x43210, 0x43250)
#define   DPFC_INVAL_SEG_MASK			REG_GENMASK(26, 16)
#define   DPFC_COMP_SEG_MASK			REG_GENMASK(10, 0)
#define DPFC_STATUS2			_MMIO(0x3214)
#define ILK_DPFC_STATUS2(fbc_id)	_MMIO_PIPE((fbc_id), 0x43214, 0x43254)
#define   DPFC_COMP_SEG_MASK_IVB		REG_GENMASK(11, 0)
#define DPFC_FENCE_YOFF			_MMIO(0x3218)
#define ILK_DPFC_FENCE_YOFF(fbc_id)	_MMIO_PIPE((fbc_id), 0x43218, 0x43258)
#define DPFC_CHICKEN			_MMIO(0x3224)
#define ILK_DPFC_CHICKEN(fbc_id)	_MMIO_PIPE((fbc_id), 0x43224, 0x43264)
#define   DPFC_HT_MODIFY			REG_BIT(31) /* pre-ivb */
#define   DPFC_NUKE_ON_ANY_MODIFICATION		REG_BIT(23) /* bdw+ */
#define   DPFC_CHICKEN_COMP_DUMMY_PIXEL		REG_BIT(14) /* glk+ */
#define   DPFC_CHICKEN_FORCE_SLB_INVALIDATION	REG_BIT(13) /* icl+ */
#define   DPFC_DISABLE_DUMMY0			REG_BIT(8) /* ivb+ */

#define GLK_FBC_STRIDE(fbc_id)	_MMIO_PIPE((fbc_id), 0x43228, 0x43268)
#define   FBC_STRIDE_OVERRIDE	REG_BIT(15)
#define   FBC_STRIDE_MASK	REG_GENMASK(14, 0)
#define   FBC_STRIDE(x)		REG_FIELD_PREP(FBC_STRIDE_MASK, (x))

#define ILK_FBC_RT_BASE		_MMIO(0x2128)
#define   ILK_FBC_RT_VALID	REG_BIT(0)
#define   SNB_FBC_FRONT_BUFFER	REG_BIT(1)

#define SNB_DPFC_CTL_SA		_MMIO(0x100100)
#define   SNB_DPFC_FENCE_EN		REG_BIT(29)
#define   SNB_DPFC_FENCENO_MASK		REG_GENMASK(4, 0)
#define   SNB_DPFC_FENCENO(fence)	REG_FIELD_PREP(SNB_DPFC_FENCENO_MASK, (fence))
#define SNB_DPFC_CPU_FENCE_OFFSET	_MMIO(0x100104)

#define IVB_FBC_RT_BASE			_MMIO(0x7020)
#define IVB_FBC_RT_BASE_UPPER		_MMIO(0x7024)

#define MSG_FBC_REND_STATE(fbc_id)	_MMIO_PIPE((fbc_id), 0x50380, 0x50384)
#define   FBC_REND_NUKE			REG_BIT(2)
#define   FBC_REND_CACHE_CLEAN		REG_BIT(1)

#endif /* __INTEL_FBC_REGS__ */
