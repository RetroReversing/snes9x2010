/***********************************************************************************
  Snes9x - Portable Super Nintendo Entertainment System (TM) emulator.

  (c) Copyright 1996 - 2002  Gary Henderson (gary.henderson@ntlworld.com),
                             Jerremy Koot (jkoot@snes9x.com)

  (c) Copyright 2002 - 2004  Matthew Kendora

  (c) Copyright 2002 - 2005  Peter Bortas (peter@bortas.org)

  (c) Copyright 2004 - 2005  Joel Yliluoma (http://iki.fi/bisqwit/)

  (c) Copyright 2001 - 2006  John Weidman (jweidman@slip.net)

  (c) Copyright 2002 - 2006  funkyass (funkyass@spam.shaw.ca),
                             Kris Bleakley (codeviolation@hotmail.com)

  (c) Copyright 2002 - 2010  Brad Jorsch (anomie@users.sourceforge.net),
                             Nach (n-a-c-h@users.sourceforge.net),
                             zones (kasumitokoduck@yahoo.com)

  (c) Copyright 2006 - 2007  nitsuja

  (c) Copyright 2009 - 2010  BearOso,
                             OV2


  BS-X C emulator code
  (c) Copyright 2005 - 2006  Dreamer Nom,
                             zones

  C4 x86 assembler and some C emulation code
  (c) Copyright 2000 - 2003  _Demo_ (_demo_@zsnes.com),
                             Nach,
                             zsKnight (zsknight@zsnes.com)

  C4 C++ code
  (c) Copyright 2003 - 2006  Brad Jorsch,
                             Nach

  DSP-1 emulator code
  (c) Copyright 1998 - 2006  _Demo_,
                             Andreas Naive (andreasnaive@gmail.com),
                             Gary Henderson,
                             Ivar (ivar@snes9x.com),
                             John Weidman,
                             Kris Bleakley,
                             Matthew Kendora,
                             Nach,
                             neviksti (neviksti@hotmail.com)

  DSP-2 emulator code
  (c) Copyright 2003         John Weidman,
                             Kris Bleakley,
                             Lord Nightmare (lord_nightmare@users.sourceforge.net),
                             Matthew Kendora,
                             neviksti

  DSP-3 emulator code
  (c) Copyright 2003 - 2006  John Weidman,
                             Kris Bleakley,
                             Lancer,
                             z80 gaiden

  DSP-4 emulator code
  (c) Copyright 2004 - 2006  Dreamer Nom,
                             John Weidman,
                             Kris Bleakley,
                             Nach,
                             z80 gaiden

  OBC1 emulator code
  (c) Copyright 2001 - 2004  zsKnight,
                             pagefault (pagefault@zsnes.com),
                             Kris Bleakley
                             Ported from x86 assembler to C by sanmaiwashi

  SPC7110 and RTC C++ emulator code used in 1.39-1.51
  (c) Copyright 2002         Matthew Kendora with research by
                             zsKnight,
                             John Weidman,
                             Dark Force

  SPC7110 and RTC C++ emulator code used in 1.52+
  (c) Copyright 2009         byuu,
                             neviksti

  S-DD1 C emulator code
  (c) Copyright 2003         Brad Jorsch with research by
                             Andreas Naive,
                             John Weidman

  S-RTC C emulator code
  (c) Copyright 2001 - 2006  byuu,
                             John Weidman

  ST010 C++ emulator code
  (c) Copyright 2003         Feather,
                             John Weidman,
                             Kris Bleakley,
                             Matthew Kendora

  Super FX x86 assembler emulator code
  (c) Copyright 1998 - 2003  _Demo_,
                             pagefault,
                             zsKnight

  Super FX C emulator code
  (c) Copyright 1997 - 1999  Ivar,
                             Gary Henderson,
                             John Weidman

  Sound emulator code used in 1.5-1.51
  (c) Copyright 1998 - 2003  Brad Martin
  (c) Copyright 1998 - 2006  Charles Bilyue'

  Sound emulator code used in 1.52+
  (c) Copyright 2004 - 2007  Shay Green (gblargg@gmail.com)

  SH assembler code partly based on x86 assembler code
  (c) Copyright 2002 - 2004  Marcus Comstedt (marcus@mc.pp.se)

  2xSaI filter
  (c) Copyright 1999 - 2001  Derek Liauw Kie Fa

  HQ2x, HQ3x, HQ4x filters
  (c) Copyright 2003         Maxim Stepin (maxim@hiend3d.com)

  NTSC filter
  (c) Copyright 2006 - 2007  Shay Green

  GTK+ GUI code
  (c) Copyright 2004 - 2010  BearOso

  Win32 GUI code
  (c) Copyright 2003 - 2006  blip,
                             funkyass,
                             Matthew Kendora,
                             Nach,
                             nitsuja
  (c) Copyright 2009 - 2010  OV2

  Mac OS GUI code
  (c) Copyright 1998 - 2001  John Stiles
  (c) Copyright 2001 - 2010  zones

  (c) Copyright 2010 - 2016 Daniel De Matteis. (UNDER NO CIRCUMSTANCE 
  WILL COMMERCIAL RIGHTS EVER BE APPROPRIATED TO ANY PARTY)

  Specific ports contains the works of other authors. See headers in
  individual files.


  Snes9x homepage: http://www.snes9x.com/

  Permission to use, copy, modify and/or distribute Snes9x in both binary
  and source form, for non-commercial purposes, is hereby granted without
  fee, providing that this license information and copyright notice appear
  with all copies and any derived work.

  This software is provided 'as-is', without any express or implied
  warranty. In no event shall the authors be held liable for any damages
  arising from the use of this software or it's derivatives.

  Snes9x is freeware for PERSONAL USE only. Commercial users should
  seek permission of the copyright holders first. Commercial use includes,
  but is not limited to, charging money for Snes9x or software derived from
  Snes9x, including Snes9x or derivatives in commercial game bundles, and/or
  using Snes9x as a promotion for your commercial product.

  The copyright holders request that bug fixes and improvements to the code
  should be forwarded to them so everyone can benefit from the modifications
  in future versions.

  Super NES and Super Nintendo Entertainment System are trademarks of
  Nintendo Co., Limited and its subsidiary companies.
 ***********************************************************************************/

#include "apu.h"

/* for "Magic WDM" features */

#ifdef SA1_OPCODES
#define AddCycles(n)	{ }
#else
#if (S9X_ACCURACY_LEVEL >= 3)
#define AddCycles(n)	{ CPU.Cycles += (n); while (CPU.Cycles >= CPU.NextEvent) S9xDoHEventProcessing(); }
#else
#define AddCycles(n)	{ CPU.Cycles += (n); }
#endif
#endif

#include "cpuaddr.h"
#include "cpuops.h"
#include "cpumacro.h"


/* ADC ********************************************************************* */

static void Op69M1 (void)
{
	uint32 libRR_temp = Immediate8(READ);
	libRR_log_instruction_1int(Registers.PCw - 2, "adc %int%", 0x69, 2, libRR_temp);
	ADC8(libRR_temp);
}

static void Op69M0 (void)
{
	uint32 libRR_temp = Immediate16(READ);
	libRR_log_instruction_1int(Registers.PCw - 1, "adc %int%", 0x69, 3, libRR_temp);
	ADC16(libRR_temp);
}

static void Op69Slow (void)
{
	libRR_log_instruction(Registers.PCw - 1, "ADC slow", 0x69, 2);
	if (CheckMemory())
		{ADC8(Immediate8Slow(READ));}
	else
		{ADC16(Immediate16Slow(READ));}
}

libRR_rOP8("adc ", 65M1,     Direct,                           WRAP_BANK, ADC)
libRR_rOP16("adc ", 65M0,     Direct,                           WRAP_BANK, ADC16)
libRR_rOPM("adc ropM", 65Slow,   DirectSlow,                       WRAP_BANK, ADC)

libRR_rOP8("adc ", 75E1,     DirectIndexedXE1,                 WRAP_BANK, ADC)
libRR_rOP8("adc ", 75E0M1,   DirectIndexedXE0,                 WRAP_BANK, ADC)
libRR_rOP16("adc ", 75E0M0,   DirectIndexedXE0,                 WRAP_BANK, ADC16)
libRR_rOPM("adc ropM", 75Slow,   DirectIndexedXSlow,               WRAP_BANK, ADC)

libRR_rOP8("adc ", 72E1,     DirectIndirectE1,                 WRAP_NONE, ADC)
libRR_rOP8("adc ", 72E0M1,   DirectIndirectE0,                 WRAP_NONE, ADC)
libRR_rOP16("adc ", 72E0M0,   DirectIndirectE0,                 WRAP_NONE, ADC16)
libRR_rOPM("adc ropM", 72Slow,   DirectIndirectSlow,               WRAP_NONE, ADC)

libRR_rOP8("adc ", 61E1,     DirectIndexedIndirectE1,          WRAP_NONE, ADC)
libRR_rOP8("adc ", 61E0M1,   DirectIndexedIndirectE0,          WRAP_NONE, ADC)
libRR_rOP16("adc ", 61E0M0,   DirectIndexedIndirectE0,          WRAP_NONE, ADC16)
libRR_rOPM("adc ropM", 61Slow,   DirectIndexedIndirectSlow,        WRAP_NONE, ADC)

libRR_rOP8("adc ", 71E1,     DirectIndirectIndexedE1,          WRAP_NONE, ADC)
libRR_rOP8("adc ", 71E0M1X1, DirectIndirectIndexedE0X1,        WRAP_NONE, ADC)
libRR_rOP16("adc ", 71E0M0X1, DirectIndirectIndexedE0X1,        WRAP_NONE, ADC16)
libRR_rOP8("adc ", 71E0M1X0, DirectIndirectIndexedE0X0,        WRAP_NONE, ADC)
libRR_rOP16("adc ", 71E0M0X0, DirectIndirectIndexedE0X0,        WRAP_NONE, ADC16)
libRR_rOPM("adc ropM", 71Slow,   DirectIndirectIndexedSlow,        WRAP_NONE, ADC)

libRR_rOP8("adc ", 67M1,     DirectIndirectLong,               WRAP_NONE, ADC)
libRR_rOP16("adc ", 67M0,     DirectIndirectLong,               WRAP_NONE, ADC16)
libRR_rOPM("adc ropM", 67Slow,   DirectIndirectLongSlow,           WRAP_NONE, ADC)

libRR_rOP8("adc ", 77M1,     DirectIndirectIndexedLong,        WRAP_NONE, ADC)
libRR_rOP16("adc ", 77M0,     DirectIndirectIndexedLong,        WRAP_NONE, ADC16)
libRR_rOPM("adc ropM", 77Slow,   DirectIndirectIndexedLongSlow,    WRAP_NONE, ADC)

libRR_rOP8("adc ", 6DM1,     Absolute,                         WRAP_NONE, ADC)
libRR_rOP16("adc ", 6DM0,     Absolute,                         WRAP_NONE, ADC16)
libRR_rOPM("adc ropM", 6DSlow,   AbsoluteSlow,                     WRAP_NONE, ADC)

libRR_rOP8("adc ", 7DM1X1,   AbsoluteIndexedXX1,               WRAP_NONE, ADC)
libRR_rOP16("adc ", 7DM0X1,   AbsoluteIndexedXX1,               WRAP_NONE, ADC16)
libRR_rOP8("adc ", 7DM1X0,   AbsoluteIndexedXX0,               WRAP_NONE, ADC)
libRR_rOP16("adc ", 7DM0X0,   AbsoluteIndexedXX0,               WRAP_NONE, ADC16)
libRR_rOPM("adc ropM", 7DSlow,   AbsoluteIndexedXSlow,             WRAP_NONE, ADC)

libRR_rOP8("adc ", 79M1X1,   AbsoluteIndexedYX1,               WRAP_NONE, ADC)
libRR_rOP16("adc ", 79M0X1,   AbsoluteIndexedYX1,               WRAP_NONE, ADC16)
libRR_rOP8("adc ", 79M1X0,   AbsoluteIndexedYX0,               WRAP_NONE, ADC)
libRR_rOP16("adc ", 79M0X0,   AbsoluteIndexedYX0,               WRAP_NONE, ADC16)
libRR_rOPM("adc ropM", 79Slow,   AbsoluteIndexedYSlow,             WRAP_NONE, ADC)

libRR_rOP8("adc ", 6FM1,     AbsoluteLong,                     WRAP_NONE, ADC)
libRR_rOP16("adc ", 6FM0,     AbsoluteLong,                     WRAP_NONE, ADC16)
libRR_rOPM("adc ropM", 6FSlow,   AbsoluteLongSlow,                 WRAP_NONE, ADC)

libRR_rOP8("adc ", 7FM1,     AbsoluteLongIndexedX,             WRAP_NONE, ADC)
libRR_rOP16("adc ", 7FM0,     AbsoluteLongIndexedX,             WRAP_NONE, ADC16)
libRR_rOPM("adc ropM", 7FSlow,   AbsoluteLongIndexedXSlow,         WRAP_NONE, ADC)

libRR_rOP8("adc ", 63M1,     StackRelative,                    WRAP_NONE, ADC)
libRR_rOP16("adc ", 63M0,     StackRelative,                    WRAP_NONE, ADC16)
libRR_rOPM("adc ropM", 63Slow,   StackRelativeSlow,                WRAP_NONE, ADC)

libRR_rOP8("adc ", 73M1,     StackRelativeIndirectIndexed,     WRAP_NONE, ADC)
libRR_rOP16("adc ", 73M0,     StackRelativeIndirectIndexed,     WRAP_NONE, ADC16)
libRR_rOPM("ropM", 73Slow,   StackRelativeIndirectIndexedSlow, WRAP_NONE, ADC)

/* AND ********************************************************************* */

static void Op29M1 (void)
{
	uint32 libRR_temp = Immediate8(READ);
	Registers.AL &= libRR_temp;
	libRR_log_instruction_1int(Registers.PCw - 2, "AND %int%", 0x29, 2, libRR_temp);
	SetZN8(Registers.AL);
}

static void Op29M0 (void)
{
	uint32 libRR_temp = Immediate16(READ);
	Registers.A.W &= libRR_temp;
	libRR_log_instruction_1int(Registers.PCw - 3, "AND %int%", 0x29, 3, libRR_temp);
	SetZN16(Registers.A.W);
}

static void Op29Slow (void)
{
	if (CheckMemory())
	{
		uint32 libRR_temp = Immediate8Slow(READ);
		Registers.AL &= libRR_temp;
		libRR_log_instruction_1int(Registers.PCw - 2, "AND %int%", 0x29, 2, libRR_temp);
		SetZN8(Registers.AL);
	}
	else
	{
		uint32 libRR_temp = Immediate16Slow(READ);
		Registers.A.W &= libRR_temp;
		libRR_log_instruction_1int(Registers.PCw - 3, "AND %int%", 0x29, 3, libRR_temp);
		SetZN16(Registers.A.W);
	}
}

libRR_rOP8("and ", 25M1,     Direct,                           WRAP_BANK, AND)
libRR_rOP16("and u16", 25M0,     Direct,                           WRAP_BANK, AND16)
libRR_rOPM("and ropM", 25Slow,   DirectSlow,                       WRAP_BANK, AND)

libRR_rOP8("and ", 35E1,     DirectIndexedXE1,                 WRAP_BANK, AND)
libRR_rOP8("and ", 35E0M1,   DirectIndexedXE0,                 WRAP_BANK, AND)
libRR_rOP16("and u16", 35E0M0,   DirectIndexedXE0,                 WRAP_BANK, AND16)
libRR_rOPM("and ropM", 35Slow,   DirectIndexedXSlow,               WRAP_BANK, AND)

libRR_rOP8("and ", 32E1,     DirectIndirectE1,                 WRAP_NONE, AND)
libRR_rOP8("and ", 32E0M1,   DirectIndirectE0,                 WRAP_NONE, AND)
libRR_rOP16("and u16", 32E0M0,   DirectIndirectE0,                 WRAP_NONE, AND16)
libRR_rOPM("and ropM", 32Slow,   DirectIndirectSlow,               WRAP_NONE, AND)

libRR_rOP8("and ", 21E1,     DirectIndexedIndirectE1,          WRAP_NONE, AND)
libRR_rOP8("and ", 21E0M1,   DirectIndexedIndirectE0,          WRAP_NONE, AND)
libRR_rOP16("and u16", 21E0M0,   DirectIndexedIndirectE0,          WRAP_NONE, AND16)
libRR_rOPM("and ropM", 21Slow,   DirectIndexedIndirectSlow,        WRAP_NONE, AND)

libRR_rOP8("and ", 31E1,     DirectIndirectIndexedE1,          WRAP_NONE, AND)
libRR_rOP8("and ", 31E0M1X1, DirectIndirectIndexedE0X1,        WRAP_NONE, AND)
libRR_rOP16("and u16", 31E0M0X1, DirectIndirectIndexedE0X1,        WRAP_NONE, AND16)
libRR_rOP8("and ", 31E0M1X0, DirectIndirectIndexedE0X0,        WRAP_NONE, AND)
libRR_rOP16("and u16", 31E0M0X0, DirectIndirectIndexedE0X0,        WRAP_NONE, AND16)
libRR_rOPM("and ropM", 31Slow,   DirectIndirectIndexedSlow,        WRAP_NONE, AND)

libRR_rOP8("and ", 27M1,     DirectIndirectLong,               WRAP_NONE, AND)
libRR_rOP16("and u16", 27M0,     DirectIndirectLong,               WRAP_NONE, AND16)
libRR_rOPM("and ropM", 27Slow,   DirectIndirectLongSlow,           WRAP_NONE, AND)

libRR_rOP8("and ", 37M1,     DirectIndirectIndexedLong,        WRAP_NONE, AND)
libRR_rOP16("and u16", 37M0,     DirectIndirectIndexedLong,        WRAP_NONE, AND16)
libRR_rOPM("and ropM", 37Slow,   DirectIndirectIndexedLongSlow,    WRAP_NONE, AND)

libRR_rOP8("and ", 2DM1,     Absolute,                         WRAP_NONE, AND)
libRR_rOP16("and u16", 2DM0,     Absolute,                         WRAP_NONE, AND16)
libRR_rOPM("and ropM", 2DSlow,   AbsoluteSlow,                     WRAP_NONE, AND)

libRR_rOP8("and ", 3DM1X1,   AbsoluteIndexedXX1,               WRAP_NONE, AND)
libRR_rOP16("and u16", 3DM0X1,   AbsoluteIndexedXX1,               WRAP_NONE, AND16)
libRR_rOP8("and ", 3DM1X0,   AbsoluteIndexedXX0,               WRAP_NONE, AND)
libRR_rOP16("and u16", 3DM0X0,   AbsoluteIndexedXX0,               WRAP_NONE, AND16)
libRR_rOPM("and ropM", 3DSlow,   AbsoluteIndexedXSlow,             WRAP_NONE, AND)

libRR_rOP8("and ", 39M1X1,   AbsoluteIndexedYX1,               WRAP_NONE, AND)
libRR_rOP16("and u16", 39M0X1,   AbsoluteIndexedYX1,               WRAP_NONE, AND16)
libRR_rOP8("and ", 39M1X0,   AbsoluteIndexedYX0,               WRAP_NONE, AND)
libRR_rOP16("and u16", 39M0X0,   AbsoluteIndexedYX0,               WRAP_NONE, AND16)
libRR_rOPM("and ropM", 39Slow,   AbsoluteIndexedYSlow,             WRAP_NONE, AND)

libRR_rOP8("and ", 2FM1,     AbsoluteLong,                     WRAP_NONE, AND)
libRR_rOP16("and u16", 2FM0,     AbsoluteLong,                     WRAP_NONE, AND16)
libRR_rOPM("and ropM", 2FSlow,   AbsoluteLongSlow,                 WRAP_NONE, AND)

libRR_rOP8("and ", 3FM1,     AbsoluteLongIndexedX,             WRAP_NONE, AND)
libRR_rOP16("and u16", 3FM0,     AbsoluteLongIndexedX,             WRAP_NONE, AND16)
libRR_rOPM("and ropM", 3FSlow,   AbsoluteLongIndexedXSlow,         WRAP_NONE, AND)

libRR_rOP8("and ", 23M1,     StackRelative,                    WRAP_NONE, AND)
libRR_rOP16("and u16", 23M0,     StackRelative,                    WRAP_NONE, AND16)
libRR_rOPM("and ropM", 23Slow,   StackRelativeSlow,                WRAP_NONE, AND)

libRR_rOP8("and ", 33M1,     StackRelativeIndirectIndexed,     WRAP_NONE, AND)
libRR_rOP16("and u16", 33M0,     StackRelativeIndirectIndexed,     WRAP_NONE, AND16)
libRR_rOPM("and ropM", 33Slow,   StackRelativeIndirectIndexedSlow, WRAP_NONE, AND)

/* ASL ********************************************************************* */

static void Op0AM1 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "ASL", 0x0A, 1);
	ICPU._Carry = (Registers.AL & 0x80) != 0;
	Registers.AL <<= 1;
	SetZN8(Registers.AL);
}

static void Op0AM0 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "ASL", 0x0A, 1);
	ICPU._Carry = (Registers.AH & 0x80) != 0;
	Registers.A.W <<= 1;
	SetZN16(Registers.A.W);
}

static void Op0ASlow (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "ASL", 0x0A, 1);

	if (CheckMemory())
	{
		ICPU._Carry = (Registers.AL & 0x80) != 0;
		Registers.AL <<= 1;
		SetZN8(Registers.AL);
	}
	else
	{
		ICPU._Carry = (Registers.AH & 0x80) != 0;
		Registers.A.W <<= 1;
		SetZN16(Registers.A.W);
	}
}

libRR_mOP8("asl, mop8", 06M1,     Direct,                           WRAP_BANK, ASL)
libRR_mOP16("asl, mop16", 06M0,     Direct,                           WRAP_BANK, ASL)
libRR_mOPM("asl, mopM", 06Slow,   DirectSlow,                       WRAP_BANK, ASL)

libRR_mOP8("asl, mop8", 16E1,     DirectIndexedXE1,                 WRAP_BANK, ASL)
libRR_mOP8("asl, mop8", 16E0M1,   DirectIndexedXE0,                 WRAP_BANK, ASL)
libRR_mOP16("asl, mop16", 16E0M0,   DirectIndexedXE0,                 WRAP_BANK, ASL)
libRR_mOPM("asl, mopM", 16Slow,   DirectIndexedXSlow,               WRAP_BANK, ASL)

libRR_mOP8("asl, mop8", 0EM1,     Absolute,                         WRAP_NONE, ASL)
libRR_mOP16("asl, mop16", 0EM0,     Absolute,                         WRAP_NONE, ASL)
libRR_mOPM("asl, mopM", 0ESlow,   AbsoluteSlow,                     WRAP_NONE, ASL)

libRR_mOP8("asl, mop8", 1EM1X1,   AbsoluteIndexedXX1,               WRAP_NONE, ASL)
libRR_mOP16("asl, mop16", 1EM0X1,   AbsoluteIndexedXX1,               WRAP_NONE, ASL)
libRR_mOP8("asl, mop8", 1EM1X0,   AbsoluteIndexedXX0,               WRAP_NONE, ASL)
libRR_mOP16("asl, mop16", 1EM0X0,   AbsoluteIndexedXX0,               WRAP_NONE, ASL)
libRR_mOPM("asl, mopM", 1ESlow,   AbsoluteIndexedXSlow,             WRAP_NONE, ASL)

/* BIT ********************************************************************* */

static void Op89M1 (void)
{
	libRR_log_instruction(Registers.PCw - 1, "BIT", 0x89, 1);
	ICPU._Zero = Registers.AL & Immediate8(READ);
}

static void Op89M0 (void)
{
	libRR_log_instruction(Registers.PCw - 1, "BIT", 0x89, 1);
	ICPU._Zero = (Registers.A.W & Immediate16(READ)) != 0;
}

static void Op89Slow (void)
{
	libRR_log_instruction(Registers.PCw - 1, "BIT", 0x89, 1);
	if (CheckMemory())
		ICPU._Zero = Registers.AL & Immediate8Slow(READ);
	else
		ICPU._Zero = (Registers.A.W & Immediate16Slow(READ)) != 0;
}

libRR_rOP8("bit ", 24M1,     Direct,                           WRAP_BANK, BIT)
libRR_rOP16("bit u16", 24M0,     Direct,                           WRAP_BANK, BIT16)
libRR_rOPM("bit ropM", 24Slow,   DirectSlow,                       WRAP_BANK, BIT)

libRR_rOP8("bit ", 34E1,     DirectIndexedXE1,                 WRAP_BANK, BIT)
libRR_rOP8("bit ", 34E0M1,   DirectIndexedXE0,                 WRAP_BANK, BIT)
libRR_rOP16("bit u16", 34E0M0,   DirectIndexedXE0,                 WRAP_BANK, BIT16)
libRR_rOPM("bit ropM", 34Slow,   DirectIndexedXSlow,               WRAP_BANK, BIT)

libRR_rOP8("bit ", 2CM1,     Absolute,                         WRAP_NONE, BIT)
libRR_rOP16("bit u16", 2CM0,     Absolute,                         WRAP_NONE, BIT16)
libRR_rOPM("bit ropM", 2CSlow,   AbsoluteSlow,                     WRAP_NONE, BIT)

libRR_rOP8("bit ", 3CM1X1,   AbsoluteIndexedXX1,               WRAP_NONE, BIT)
libRR_rOP16("bit u16", 3CM0X1,   AbsoluteIndexedXX1,               WRAP_NONE, BIT16)
libRR_rOP8("bit ", 3CM1X0,   AbsoluteIndexedXX0,               WRAP_NONE, BIT)
libRR_rOP16("bit u16", 3CM0X0,   AbsoluteIndexedXX0,               WRAP_NONE, BIT16)
libRR_rOPM("bit ropM", 3CSlow,   AbsoluteIndexedXSlow,             WRAP_NONE, BIT)

/* CMP ********************************************************************* */

static void OpC9M1 (void)
{
	int16 Int16;

	uint32 libRR_temp = Immediate8(READ);
	Int16 = (int16) Registers.AL - (int16) libRR_temp;
	libRR_log_instruction_1int(Registers.PCw - 2, "CMP %int%", 0xC9, 2, libRR_temp);
	ICPU._Carry = Int16 >= 0;
	SetZN8((uint8) Int16);
}

static void OpC9M0 (void)
{
	int32 Int32;
	uint32 libRR_temp = Immediate16(READ);
	Int32 = (int32) Registers.A.W - (int32) libRR_temp;
	libRR_log_instruction_1int(Registers.PCw - 3, "CMP %int%", 0xC9, 3, libRR_temp);
	ICPU._Carry = Int32 >= 0;
	SetZN16((uint16) Int32);
}

static void OpC9Slow (void)
{
	if (CheckMemory())
	{
		uint32 libRR_temp = Immediate8(READ);
		int16	Int16 = (int16) Registers.AL - (int16) libRR_temp;
		libRR_log_instruction_1int(Registers.PCw - 2, "CMP %int%", 0xC9, 2, libRR_temp);
		ICPU._Carry = Int16 >= 0;
		SetZN8((uint8) Int16);
	}
	else
	{
		uint32 libRR_temp = Immediate16(READ);
		int32	Int32 = (int32) Registers.A.W - (int32) Immediate16Slow(READ);
		libRR_log_instruction_1int(Registers.PCw - 3, "CMP %int%", 0xC9, 3, libRR_temp);
		ICPU._Carry = Int32 >= 0;
		SetZN16((uint16) Int32);
	}
}

libRR_rOP8("cmp ", C5M1,     Direct,                           WRAP_BANK, CMP)
libRR_rOP16("cmp ", C5M0,     Direct,                           WRAP_BANK, CMP16)
libRR_rOPM("cmp ropM", C5Slow,   DirectSlow,                       WRAP_BANK, CMP)

libRR_rOP8("cmp ", D5E1,     DirectIndexedXE1,                 WRAP_BANK, CMP)
libRR_rOP8("cmp ", D5E0M1,   DirectIndexedXE0,                 WRAP_BANK, CMP)
libRR_rOP16("cmp ", D5E0M0,   DirectIndexedXE0,                 WRAP_BANK, CMP16)
libRR_rOPM("cmp ropM", D5Slow,   DirectIndexedXSlow,               WRAP_BANK, CMP)

libRR_rOP8("cmp ", D2E1,     DirectIndirectE1,                 WRAP_NONE, CMP)
libRR_rOP8("cmp ", D2E0M1,   DirectIndirectE0,                 WRAP_NONE, CMP)
libRR_rOP16("cmp ", D2E0M0,   DirectIndirectE0,                 WRAP_NONE, CMP16)
libRR_rOPM("cmp ropM", D2Slow,   DirectIndirectSlow,               WRAP_NONE, CMP)

libRR_rOP8("cmp ", C1E1,     DirectIndexedIndirectE1,          WRAP_NONE, CMP)
libRR_rOP8("cmp ", C1E0M1,   DirectIndexedIndirectE0,          WRAP_NONE, CMP)
libRR_rOP16("cmp ", C1E0M0,   DirectIndexedIndirectE0,          WRAP_NONE, CMP16)
libRR_rOPM("cmp ropM", C1Slow,   DirectIndexedIndirectSlow,        WRAP_NONE, CMP)

libRR_rOP8("cmp ", D1E1,     DirectIndirectIndexedE1,          WRAP_NONE, CMP)
libRR_rOP8("cmp ", D1E0M1X1, DirectIndirectIndexedE0X1,        WRAP_NONE, CMP)
libRR_rOP16("cmp ", D1E0M0X1, DirectIndirectIndexedE0X1,        WRAP_NONE, CMP16)
libRR_rOP8("cmp ", D1E0M1X0, DirectIndirectIndexedE0X0,        WRAP_NONE, CMP)
libRR_rOP16("cmp ", D1E0M0X0, DirectIndirectIndexedE0X0,        WRAP_NONE, CMP16)
libRR_rOPM("cmp ropM", D1Slow,   DirectIndirectIndexedSlow,        WRAP_NONE, CMP)

libRR_rOP8("cmp ", C7M1,     DirectIndirectLong,               WRAP_NONE, CMP)
libRR_rOP16("cmp ", C7M0,     DirectIndirectLong,               WRAP_NONE, CMP16)
libRR_rOPM("cmp ropM", C7Slow,   DirectIndirectLongSlow,           WRAP_NONE, CMP)

libRR_rOP8("cmp ", D7M1,     DirectIndirectIndexedLong,        WRAP_NONE, CMP)
libRR_rOP16("cmp ", D7M0,     DirectIndirectIndexedLong,        WRAP_NONE, CMP16)
libRR_rOPM("cmp ropM", D7Slow,   DirectIndirectIndexedLongSlow,    WRAP_NONE, CMP)

libRR_rOP8("cmp ", CDM1,     Absolute,                         WRAP_NONE, CMP)
libRR_rOP16("cmp ", CDM0,     Absolute,                         WRAP_NONE, CMP16)
libRR_rOPM("cmp ropM", CDSlow,   AbsoluteSlow,                     WRAP_NONE, CMP)

libRR_rOP8("cmp ", DDM1X1,   AbsoluteIndexedXX1,               WRAP_NONE, CMP)
libRR_rOP16("cmp ", DDM0X1,   AbsoluteIndexedXX1,               WRAP_NONE, CMP16)
libRR_rOP8("cmp ", DDM1X0,   AbsoluteIndexedXX0,               WRAP_NONE, CMP)
libRR_rOP16("cmp ", DDM0X0,   AbsoluteIndexedXX0,               WRAP_NONE, CMP16)
libRR_rOPM("cmp ropM", DDSlow,   AbsoluteIndexedXSlow,             WRAP_NONE, CMP)

libRR_rOP8("cmp ", D9M1X1,   AbsoluteIndexedYX1,               WRAP_NONE, CMP)
libRR_rOP16("cmp ", D9M0X1,   AbsoluteIndexedYX1,               WRAP_NONE, CMP16)
libRR_rOP8("cmp ", D9M1X0,   AbsoluteIndexedYX0,               WRAP_NONE, CMP)
libRR_rOP16("cmp ", D9M0X0,   AbsoluteIndexedYX0,               WRAP_NONE, CMP16)
libRR_rOPM("cmp ropM", D9Slow,   AbsoluteIndexedYSlow,             WRAP_NONE, CMP)

libRR_rOP8("cmp ", CFM1,     AbsoluteLong,                     WRAP_NONE, CMP)
libRR_rOP16("cmp ", CFM0,     AbsoluteLong,                     WRAP_NONE, CMP16)
libRR_rOPM("cmp ropM", CFSlow,   AbsoluteLongSlow,                 WRAP_NONE, CMP)

libRR_rOP8("cmp ", DFM1,     AbsoluteLongIndexedX,             WRAP_NONE, CMP)
libRR_rOP16("cmp ", DFM0,     AbsoluteLongIndexedX,             WRAP_NONE, CMP16)
libRR_rOPM("cmp ropM", DFSlow,   AbsoluteLongIndexedXSlow,         WRAP_NONE, CMP)

libRR_rOP8("cmp ", C3M1,     StackRelative,                    WRAP_NONE, CMP)
libRR_rOP16("cmp ", C3M0,     StackRelative,                    WRAP_NONE, CMP16)
libRR_rOPM("cmp ropM", C3Slow,   StackRelativeSlow,                WRAP_NONE, CMP)

libRR_rOP8("cmp ", D3M1,     StackRelativeIndirectIndexed,     WRAP_NONE, CMP)
libRR_rOP16("cmp ", D3M0,     StackRelativeIndirectIndexed,     WRAP_NONE, CMP16)
libRR_rOPM("cmp ropM", D3Slow,   StackRelativeIndirectIndexedSlow, WRAP_NONE, CMP)

/* CPX ********************************************************************* */

static void OpE0X1 (void)
{
	uint32 libRR_temp = Immediate8(READ);
	int16	Int16 = (int16) Registers.XL - (int16) libRR_temp;
	libRR_log_instruction_1int(Registers.PCw - 2, "CPX %int%", 0xE0, 2, libRR_temp);
	ICPU._Carry = Int16 >= 0;
	SetZN8((uint8) Int16);
}

static void OpE0X0 (void)
{
	uint32 libRR_temp = Immediate16(READ);
	int32	Int32 = (int32) Registers.X.W - (int32) libRR_temp;
	libRR_log_instruction_1int(Registers.PCw - 3, "CPX %int%", 0xE0, 3, libRR_temp);
	ICPU._Carry = Int32 >= 0;
	SetZN16((uint16) Int32);
}

static void OpE0Slow (void)
{
	if (CheckIndex())
	{
		uint32 libRR_temp = Immediate8Slow(READ);
		int16	Int16 = (int16) Registers.XL - (int16) libRR_temp;
		libRR_log_instruction_1int(Registers.PCw - 2, "CPX %int%", 0xE0, 2, libRR_temp);
		ICPU._Carry = Int16 >= 0;
		SetZN8((uint8) Int16);
	}
	else
	{
		uint32 libRR_temp = Immediate16Slow(READ);
		int32	Int32 = (int32) Registers.X.W - (int32) libRR_temp;
		libRR_log_instruction_1int(Registers.PCw - 3, "CPX %int%", 0xE0, 3, libRR_temp);
		ICPU._Carry = Int32 >= 0;
		SetZN16((uint16) Int32);
	}
}

libRR_rOP8("cpx ", E4X1,     Direct,                           WRAP_BANK, CPX)
libRR_rOP16("cpx ", E4X0,     Direct,                           WRAP_BANK, CPX16)
libRR_rOPX("cpx ropX", E4Slow,   DirectSlow,                       WRAP_BANK, CPX)

libRR_rOP8("cpx ", ECX1,     Absolute,                         WRAP_NONE, CPX)
libRR_rOP16("cpx ", ECX0,     Absolute,                         WRAP_NONE, CPX16)
libRR_rOPX("cpx ropX", ECSlow,   AbsoluteSlow,                     WRAP_NONE, CPX)

/* CPY ********************************************************************* */

static void OpC0X1 (void)
{
	uint32 libRR_temp = Immediate8(READ);
	int16	Int16 = (int16) Registers.YL - (int16) libRR_temp;
	libRR_log_instruction_1int(Registers.PCw - 2, "CPY %int%", 0xC0, 2, libRR_temp);
	ICPU._Carry = Int16 >= 0;
	SetZN8((uint8) Int16);
}

static void OpC0X0 (void)
{
	uint32 libRR_temp = Immediate16(READ);
	int32	Int32 = (int32) Registers.Y.W - (int32) libRR_temp;
	libRR_log_instruction_1int(Registers.PCw - 3, "CPY %int%", 0xC0, 3, libRR_temp);
	ICPU._Carry = Int32 >= 0;
	SetZN16((uint16) Int32);
}

static void OpC0Slow (void)
{
	if (CheckIndex())
	{
		uint32 libRR_temp = Immediate8Slow(READ);
		int16	Int16 = (int16) Registers.YL - (int16) libRR_temp;
		libRR_log_instruction_1int(Registers.PCw - 2, "CPY %int%", 0xC0, 2, libRR_temp);
		ICPU._Carry = Int16 >= 0;
		SetZN8((uint8) Int16);
	}
	else
	{
		uint32 libRR_temp = Immediate16Slow(READ);
		int32	Int32 = (int32) Registers.Y.W - (int32) libRR_temp;
		libRR_log_instruction_1int(Registers.PCw - 3, "CPY %int%", 0xC0, 3, libRR_temp);
		ICPU._Carry = Int32 >= 0;
		SetZN16((uint16) Int32);
	}
}

libRR_rOP8("cpy ", C4X1,     Direct,                           WRAP_BANK, CPY)
libRR_rOP16("cpy ", C4X0,     Direct,                           WRAP_BANK, CPY16)
libRR_rOPX("cpy ropX", C4Slow,   DirectSlow,                       WRAP_BANK, CPY)

libRR_rOP8("cpy ", CCX1,     Absolute,                         WRAP_NONE, CPY)
libRR_rOP16("cpy ", CCX0,     Absolute,                         WRAP_NONE, CPY16)
libRR_rOPX("cpy ropX", CCSlow,   AbsoluteSlow,                     WRAP_NONE, CPY)

/* DEC ********************************************************************* */

static void Op3AM1 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "DEC AL", 0x3A, 1);
	Registers.AL--;
	SetZN8(Registers.AL);
}

static void Op3AM0 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "DEC A", 0x3A, 1);
	Registers.A.W--;
	SetZN16(Registers.A.W);
}

static void Op3ASlow (void)
{
	AddCycles(ONE_CYCLE);

	if (CheckMemory())
	{
		libRR_log_instruction(Registers.PCw - 1, "DEC AL", 0x3A, 1);
		Registers.AL--;
		SetZN8(Registers.AL);
	}
	else
	{
		libRR_log_instruction(Registers.PCw - 1, "DEC A", 0x3A, 1);
		Registers.A.W--;
		SetZN16(Registers.A.W);
	}
}

libRR_mOP8("dec mop8", C6M1,     Direct,                           WRAP_BANK, DEC)
libRR_mOP16("dec mop16", C6M0,     Direct,                           WRAP_BANK, DEC)
libRR_mOPM("dec mopM", C6Slow,   DirectSlow,                       WRAP_BANK, DEC)

libRR_mOP8("dec mop8", D6E1,     DirectIndexedXE1,                 WRAP_BANK, DEC)
libRR_mOP8("dec mop8", D6E0M1,   DirectIndexedXE0,                 WRAP_BANK, DEC)
libRR_mOP16("dec mop16", D6E0M0,   DirectIndexedXE0,                 WRAP_BANK, DEC)
libRR_mOPM("dec mopM", D6Slow,   DirectIndexedXSlow,               WRAP_BANK, DEC)

libRR_mOP8("dec mop8", CEM1,     Absolute,                         WRAP_NONE, DEC)
libRR_mOP16("dec mop16", CEM0,     Absolute,                         WRAP_NONE, DEC)
libRR_mOPM("dec mopM", CESlow,   AbsoluteSlow,                     WRAP_NONE, DEC)

libRR_mOP8("dec mop8", DEM1X1,   AbsoluteIndexedXX1,               WRAP_NONE, DEC)
libRR_mOP16("dec mop16", DEM0X1,   AbsoluteIndexedXX1,               WRAP_NONE, DEC)
libRR_mOP8("dec mop8", DEM1X0,   AbsoluteIndexedXX0,               WRAP_NONE, DEC)
libRR_mOP16("dec mop16", DEM0X0,   AbsoluteIndexedXX0,               WRAP_NONE, DEC)
libRR_mOPM("dec mopM", DESlow,   AbsoluteIndexedXSlow,             WRAP_NONE, DEC)

/* EOR ********************************************************************* */

static void Op49M1 (void)
{
	Registers.AL ^= Immediate8(READ);
	libRR_log_instruction(Registers.PCw - 1, "EOR", 0x49, 1);
	SetZN8(Registers.AL);
}

static void Op49M0 (void)
{
	Registers.A.W ^= Immediate16(READ);
	libRR_log_instruction(Registers.PCw - 1, "EOR", 0x49, 1);
	SetZN16(Registers.A.W);
}

static void Op49Slow (void)
{
	libRR_log_instruction(Registers.PCw - 1, "EOR", 0x49, 1);
	if (CheckMemory())
	{
		Registers.AL ^= Immediate8Slow(READ);
		SetZN8(Registers.AL);
	}
	else
	{
		Registers.A.W ^= Immediate16Slow(READ);
		SetZN16(Registers.A.W);
	}
}

libRR_rOP8("eor ", 45M1,     Direct,                           WRAP_BANK, EOR)
libRR_rOP16("eor ", 45M0,     Direct,                           WRAP_BANK, EOR16)
libRR_rOPM("eor ropM", 45Slow,   DirectSlow,                       WRAP_BANK, EOR)

libRR_rOP8("eor ", 55E1,     DirectIndexedXE1,                 WRAP_BANK, EOR)
libRR_rOP8("eor ", 55E0M1,   DirectIndexedXE0,                 WRAP_BANK, EOR)
libRR_rOP16("eor ", 55E0M0,   DirectIndexedXE0,                 WRAP_BANK, EOR16)
libRR_rOPM("eor ropM", 55Slow,   DirectIndexedXSlow,               WRAP_BANK, EOR)

libRR_rOP8("eor ", 52E1,     DirectIndirectE1,                 WRAP_NONE, EOR)
libRR_rOP8("eor ", 52E0M1,   DirectIndirectE0,                 WRAP_NONE, EOR)
libRR_rOP16("eor ", 52E0M0,   DirectIndirectE0,                 WRAP_NONE, EOR16)
libRR_rOPM("eor ropM", 52Slow,   DirectIndirectSlow,               WRAP_NONE, EOR)

libRR_rOP8("eor ", 41E1,     DirectIndexedIndirectE1,          WRAP_NONE, EOR)
libRR_rOP8("eor ", 41E0M1,   DirectIndexedIndirectE0,          WRAP_NONE, EOR)
libRR_rOP16("eor ", 41E0M0,   DirectIndexedIndirectE0,          WRAP_NONE, EOR16)
libRR_rOPM("eor ropM", 41Slow,   DirectIndexedIndirectSlow,        WRAP_NONE, EOR)

libRR_rOP8("eor ", 51E1,     DirectIndirectIndexedE1,          WRAP_NONE, EOR)
libRR_rOP8("eor ", 51E0M1X1, DirectIndirectIndexedE0X1,        WRAP_NONE, EOR)
libRR_rOP16("eor ", 51E0M0X1, DirectIndirectIndexedE0X1,        WRAP_NONE, EOR16)
libRR_rOP8("eor ", 51E0M1X0, DirectIndirectIndexedE0X0,        WRAP_NONE, EOR)
libRR_rOP16("eor ", 51E0M0X0, DirectIndirectIndexedE0X0,        WRAP_NONE, EOR16)
libRR_rOPM("eor ropM", 51Slow,   DirectIndirectIndexedSlow,        WRAP_NONE, EOR)

libRR_rOP8("eor ", 47M1,     DirectIndirectLong,               WRAP_NONE, EOR)
libRR_rOP16("eor ", 47M0,     DirectIndirectLong,               WRAP_NONE, EOR16)
libRR_rOPM("eor ropM", 47Slow,   DirectIndirectLongSlow,           WRAP_NONE, EOR)

libRR_rOP8("eor ", 57M1,     DirectIndirectIndexedLong,        WRAP_NONE, EOR)
libRR_rOP16("eor ", 57M0,     DirectIndirectIndexedLong,        WRAP_NONE, EOR16)
libRR_rOPM("eor ropM", 57Slow,   DirectIndirectIndexedLongSlow,    WRAP_NONE, EOR)

libRR_rOP8("eor ", 4DM1,     Absolute,                         WRAP_NONE, EOR)
libRR_rOP16("eor ", 4DM0,     Absolute,                         WRAP_NONE, EOR16)
libRR_rOPM("eor ropM", 4DSlow,   AbsoluteSlow,                     WRAP_NONE, EOR)

libRR_rOP8("eor ", 5DM1X1,   AbsoluteIndexedXX1,               WRAP_NONE, EOR)
libRR_rOP16("eor ", 5DM0X1,   AbsoluteIndexedXX1,               WRAP_NONE, EOR16)
libRR_rOP8("eor ", 5DM1X0,   AbsoluteIndexedXX0,               WRAP_NONE, EOR)
libRR_rOP16("eor ", 5DM0X0,   AbsoluteIndexedXX0,               WRAP_NONE, EOR16)
libRR_rOPM("eor ropM", 5DSlow,   AbsoluteIndexedXSlow,             WRAP_NONE, EOR)

libRR_rOP8("eor ", 59M1X1,   AbsoluteIndexedYX1,               WRAP_NONE, EOR)
libRR_rOP16("eor ", 59M0X1,   AbsoluteIndexedYX1,               WRAP_NONE, EOR16)
libRR_rOP8("eor ", 59M1X0,   AbsoluteIndexedYX0,               WRAP_NONE, EOR)
libRR_rOP16("eor ", 59M0X0,   AbsoluteIndexedYX0,               WRAP_NONE, EOR16)
libRR_rOPM("eor ropM", 59Slow,   AbsoluteIndexedYSlow,             WRAP_NONE, EOR)

libRR_rOP8("eor ", 4FM1,     AbsoluteLong,                     WRAP_NONE, EOR)
libRR_rOP16("eor ", 4FM0,     AbsoluteLong,                     WRAP_NONE, EOR16)
libRR_rOPM("eor ropM", 4FSlow,   AbsoluteLongSlow,                 WRAP_NONE, EOR)

libRR_rOP8("eor ", 5FM1,     AbsoluteLongIndexedX,             WRAP_NONE, EOR)
libRR_rOP16("eor ", 5FM0,     AbsoluteLongIndexedX,             WRAP_NONE, EOR16)
libRR_rOPM("eor ropM", 5FSlow,   AbsoluteLongIndexedXSlow,         WRAP_NONE, EOR)

libRR_rOP8("eor ", 43M1,     StackRelative,                    WRAP_NONE, EOR)
libRR_rOP16("eor ", 43M0,     StackRelative,                    WRAP_NONE, EOR16)
libRR_rOPM("eor ropM", 43Slow,   StackRelativeSlow,                WRAP_NONE, EOR)

libRR_rOP8("eor ", 53M1,     StackRelativeIndirectIndexed,     WRAP_NONE, EOR)
libRR_rOP16("eor ", 53M0,     StackRelativeIndirectIndexed,     WRAP_NONE, EOR16)
libRR_rOPM("eor ropM", 53Slow,   StackRelativeIndirectIndexedSlow, WRAP_NONE, EOR)

/* INC ********************************************************************* */

static void Op1AM1 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "INC AL", 0x1A, 1);
	Registers.AL++;
	SetZN8(Registers.AL);
}

static void Op1AM0 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "INC A", 0x1A, 1);
	Registers.A.W++;
	SetZN16(Registers.A.W);
}

static void Op1ASlow (void)
{
	AddCycles(ONE_CYCLE);

	if (CheckMemory())
	{
		libRR_log_instruction(Registers.PCw - 1, "INC AL", 0x1A, 1);
		Registers.AL++;
		SetZN8(Registers.AL);
	}
	else
	{
		libRR_log_instruction(Registers.PCw - 1, "INC A", 0x1A, 1);
		Registers.A.W++;
		SetZN16(Registers.A.W);
	}
}

libRR_mOP8("inc mop8", E6M1,     Direct,                           WRAP_BANK, INC)
libRR_mOP16("inc mop16", E6M0,     Direct,                           WRAP_BANK, INC)
libRR_mOPM("inc mopM", E6Slow,   DirectSlow,                       WRAP_BANK, INC)

libRR_mOP8("inc mop8", F6E1,     DirectIndexedXE1,                 WRAP_BANK, INC)
libRR_mOP8("inc mop8", F6E0M1,   DirectIndexedXE0,                 WRAP_BANK, INC)
libRR_mOP16("inc mop16", F6E0M0,   DirectIndexedXE0,                 WRAP_BANK, INC)
libRR_mOPM("inc mopM", F6Slow,   DirectIndexedXSlow,               WRAP_BANK, INC)

libRR_mOP8("inc mop8", EEM1,     Absolute,                         WRAP_NONE, INC)
libRR_mOP16("inc mop16", EEM0,     Absolute,                         WRAP_NONE, INC)
libRR_mOPM("inc mopM", EESlow,   AbsoluteSlow,                     WRAP_NONE, INC)

libRR_mOP8("inc mop8", FEM1X1,   AbsoluteIndexedXX1,               WRAP_NONE, INC)
libRR_mOP16("inc mop16", FEM0X1,   AbsoluteIndexedXX1,               WRAP_NONE, INC)
libRR_mOP8("inc mop8", FEM1X0,   AbsoluteIndexedXX0,               WRAP_NONE, INC)
libRR_mOP16("inc mop16", FEM0X0,   AbsoluteIndexedXX0,               WRAP_NONE, INC)
libRR_mOPM("inc mopM", FESlow,   AbsoluteIndexedXSlow,             WRAP_NONE, INC)

/* LDA ********************************************************************* */

static void OpA9M1 (void)
{
	Registers.AL = Immediate8(READ);
	libRR_log_instruction_1int(Registers.PCw - 2, "LDA %int%", 0xA9, S9xOpLengthsM1X0[0xA9], Registers.AL);
	SetZN8(Registers.AL);
}

static void OpA9M0 (void)
{
	Registers.A.W = Immediate16(READ);
	libRR_log_instruction_1int(Registers.PCw - 3, "LDA %int%", 0xA9, S9xOpLengthsM0X0[0xA9], Registers.A.W);
	SetZN16(Registers.A.W);
}

static void OpA9Slow (void)
{
	libRR_log_instruction(Registers.PCw - 1, "LDA Slow", 0xA9, ICPU.S9xOpLengths[0xA9]);
	if (CheckMemory())
	{
		Registers.AL = Immediate8Slow(READ);
		SetZN8(Registers.AL);
	}
	else
	{
		Registers.A.W = Immediate16Slow(READ);
		SetZN16(Registers.A.W);
	}
}

libRR_rOP8("lda ", A5M1,     Direct,                           WRAP_BANK, LDA)
libRR_rOP16("lda ", A5M0,     Direct,                           WRAP_BANK, LDA16)
libRR_rOPM("ropM", A5Slow,   DirectSlow,                       WRAP_BANK, LDA)

libRR_rOP8("lda ", B5E1,     DirectIndexedXE1,                 WRAP_BANK, LDA)
libRR_rOP8("lda ", B5E0M1,   DirectIndexedXE0,                 WRAP_BANK, LDA)
libRR_rOP16("lda ", B5E0M0,   DirectIndexedXE0,                 WRAP_BANK, LDA16)
libRR_rOPM("ropM", B5Slow,   DirectIndexedXSlow,               WRAP_BANK, LDA)

libRR_rOP8("lda ", B2E1,     DirectIndirectE1,                 WRAP_NONE, LDA)
libRR_rOP8("lda ", B2E0M1,   DirectIndirectE0,                 WRAP_NONE, LDA)
libRR_rOP16("lda ", B2E0M0,   DirectIndirectE0,                 WRAP_NONE, LDA16)
libRR_rOPM("ropM", B2Slow,   DirectIndirectSlow,               WRAP_NONE, LDA)

libRR_rOP8("lda ", A1E1,     DirectIndexedIndirectE1,          WRAP_NONE, LDA)
libRR_rOP8("lda ", A1E0M1,   DirectIndexedIndirectE0,          WRAP_NONE, LDA)
libRR_rOP16("lda ", A1E0M0,   DirectIndexedIndirectE0,          WRAP_NONE, LDA16)
libRR_rOPM("ropM", A1Slow,   DirectIndexedIndirectSlow,        WRAP_NONE, LDA)

libRR_rOP8("lda ", B1E1,     DirectIndirectIndexedE1,          WRAP_NONE, LDA)
libRR_rOP8("lda ", B1E0M1X1, DirectIndirectIndexedE0X1,        WRAP_NONE, LDA)
libRR_rOP16("lda ", B1E0M0X1, DirectIndirectIndexedE0X1,        WRAP_NONE, LDA16)
libRR_rOP8("lda ", B1E0M1X0, DirectIndirectIndexedE0X0,        WRAP_NONE, LDA)
libRR_rOP16("lda ", B1E0M0X0, DirectIndirectIndexedE0X0,        WRAP_NONE, LDA16)
libRR_rOPM("ropM", B1Slow,   DirectIndirectIndexedSlow,        WRAP_NONE, LDA)

libRR_rOP8("lda ", A7M1,     DirectIndirectLong,               WRAP_NONE, LDA)
libRR_rOP16("lda ", A7M0,     DirectIndirectLong,               WRAP_NONE, LDA16)
libRR_rOPM("ropM", A7Slow,   DirectIndirectLongSlow,           WRAP_NONE, LDA)

libRR_rOP8("lda ", B7M1,     DirectIndirectIndexedLong,        WRAP_NONE, LDA)
libRR_rOP16("lda ", B7M0,     DirectIndirectIndexedLong,        WRAP_NONE, LDA16)
libRR_rOPM("ropM", B7Slow,   DirectIndirectIndexedLongSlow,    WRAP_NONE, LDA)

libRR_rOP8("lda ", ADM1,     Absolute,                         WRAP_NONE, LDA)
libRR_rOP16("lda ", ADM0,     Absolute,                         WRAP_NONE, LDA16)
libRR_rOPM("ropM", ADSlow,   AbsoluteSlow,                     WRAP_NONE, LDA)

libRR_rOP8("lda ", BDM1X1,   AbsoluteIndexedXX1,               WRAP_NONE, LDA)
libRR_rOP16("lda ", BDM0X1,   AbsoluteIndexedXX1,               WRAP_NONE, LDA16)
libRR_rOP8("lda ", BDM1X0,   AbsoluteIndexedXX0,               WRAP_NONE, LDA)
libRR_rOP16("lda ", BDM0X0,   AbsoluteIndexedXX0,               WRAP_NONE, LDA16)
libRR_rOPM("ropM", BDSlow,   AbsoluteIndexedXSlow,             WRAP_NONE, LDA)

libRR_rOP8("lda ", B9M1X1,   AbsoluteIndexedYX1,               WRAP_NONE, LDA)
libRR_rOP16("lda ", B9M0X1,   AbsoluteIndexedYX1,               WRAP_NONE, LDA16)
libRR_rOP8("lda ", B9M1X0,   AbsoluteIndexedYX0,               WRAP_NONE, LDA)
libRR_rOP16("lda ", B9M0X0,   AbsoluteIndexedYX0,               WRAP_NONE, LDA16)
libRR_rOPM("ropM", B9Slow,   AbsoluteIndexedYSlow,             WRAP_NONE, LDA)

libRR_rOP8("lda ", AFM1,     AbsoluteLong,                     WRAP_NONE, LDA)
libRR_rOP16("lda ", AFM0,     AbsoluteLong,                     WRAP_NONE, LDA16)
libRR_rOPM("ropM", AFSlow,   AbsoluteLongSlow,                 WRAP_NONE, LDA)

libRR_rOP8("lda ", BFM1,     AbsoluteLongIndexedX,             WRAP_NONE, LDA)
libRR_rOP16("lda ", BFM0,     AbsoluteLongIndexedX,             WRAP_NONE, LDA16)
libRR_rOPM("ropM", BFSlow,   AbsoluteLongIndexedXSlow,         WRAP_NONE, LDA)

libRR_rOP8("lda ", A3M1,     StackRelative,                    WRAP_NONE, LDA)
libRR_rOP16("lda ", A3M0,     StackRelative,                    WRAP_NONE, LDA16)
libRR_rOPM("ropM", A3Slow,   StackRelativeSlow,                WRAP_NONE, LDA)

libRR_rOP8("lda ", B3M1,     StackRelativeIndirectIndexed,     WRAP_NONE, LDA)
libRR_rOP16("lda ", B3M0,     StackRelativeIndirectIndexed,     WRAP_NONE, LDA16)
libRR_rOPM("ropM", B3Slow,   StackRelativeIndirectIndexedSlow, WRAP_NONE, LDA)

/* LDX ********************************************************************* */

static void OpA2X1 (void)
{
	Registers.XL = Immediate8(READ);
	libRR_log_instruction_1int(Registers.PCw - 2, "LDX %int%", 0xA2, 2, Registers.XL);
	SetZN8(Registers.XL);
}

static void OpA2X0 (void)
{
	Registers.X.W = Immediate16(READ);
	libRR_log_instruction_1int(Registers.PCw - 3, "LDX %int%", 0xA2, 3, Registers.X.W);
	SetZN16(Registers.X.W);
}

static void OpA2Slow (void)
{
	if (CheckIndex())
	{
		Registers.XL = Immediate8Slow(READ);
		libRR_log_instruction_1int(Registers.PCw - 2, "LDX %int%", 0xA2, 2, Registers.XL);
		SetZN8(Registers.XL);
	}
	else
	{
		Registers.X.W = Immediate16Slow(READ);
		libRR_log_instruction_1int(Registers.PCw - 3, "LDX %int%", 0xA2, 3, Registers.X.W);
		SetZN16(Registers.X.W);
	}
}

libRR_rOP8("ldx ", A6X1,     Direct,                           WRAP_BANK, LDX)
libRR_rOP16("ldx ", A6X0,     Direct,                           WRAP_BANK, LDX16)
libRR_rOPX("ropX", A6Slow,   DirectSlow,                       WRAP_BANK, LDX)

libRR_rOP8("ldx ", B6E1,     DirectIndexedYE1,                 WRAP_BANK, LDX)
libRR_rOP8("ldx ", B6E0X1,   DirectIndexedYE0,                 WRAP_BANK, LDX)
libRR_rOP16("ldx ", B6E0X0,   DirectIndexedYE0,                 WRAP_BANK, LDX16)
libRR_rOPX("ropX", B6Slow,   DirectIndexedYSlow,               WRAP_BANK, LDX)

libRR_rOP8("ldx ", AEX1,     Absolute,                         WRAP_BANK, LDX)
libRR_rOP16("ldx ", AEX0,     Absolute,                         WRAP_BANK, LDX16)
libRR_rOPX("ropX", AESlow,   AbsoluteSlow,                     WRAP_BANK, LDX)

libRR_rOP8("ldx ", BEX1,     AbsoluteIndexedYX1,               WRAP_BANK, LDX)
libRR_rOP16("ldx ", BEX0,     AbsoluteIndexedYX0,               WRAP_BANK, LDX16)
libRR_rOPX("ropX", BESlow,   AbsoluteIndexedYSlow,             WRAP_BANK, LDX)

/* LDY ********************************************************************* */

static void OpA0X1 (void)
{
	Registers.YL = Immediate8(READ);
	libRR_log_instruction_1int(Registers.PCw - 2, "LDY %int%", 0xA0, 2, Registers.YL);
	SetZN8(Registers.YL);
}

static void OpA0X0 (void)
{
	Registers.Y.W = Immediate16(READ);
	libRR_log_instruction_1int(Registers.PCw - 3, "LDY %int%", 0xA0, 3, Registers.Y.W);
	SetZN16(Registers.Y.W);
}

static void OpA0Slow (void)
{
	if (CheckIndex())
	{
		Registers.YL = Immediate8Slow(READ);
		libRR_log_instruction_1int(Registers.PCw - 2, "LDY %int%", 0xA0, 2, Registers.YL);
		SetZN8(Registers.YL);
	}
	else
	{
		Registers.Y.W = Immediate16Slow(READ);
		libRR_log_instruction_1int(Registers.PCw - 3, "LDY %int%", 0xA0, 3, Registers.Y.W);
		SetZN16(Registers.Y.W);
	}
}

libRR_rOP8("ldy ", A4X1,     Direct,                           WRAP_BANK, LDY)
libRR_rOP16("ldy ", A4X0,     Direct,                           WRAP_BANK, LDY16)
libRR_rOPX("ropX", A4Slow,   DirectSlow,                       WRAP_BANK, LDY)

libRR_rOP8("ldy ", B4E1,     DirectIndexedXE1,                 WRAP_BANK, LDY)
libRR_rOP8("ldy ", B4E0X1,   DirectIndexedXE0,                 WRAP_BANK, LDY)
libRR_rOP16("ldy ", B4E0X0,   DirectIndexedXE0,                 WRAP_BANK, LDY16)
libRR_rOPX("ropX", B4Slow,   DirectIndexedXSlow,               WRAP_BANK, LDY)

libRR_rOP8("ldy ", ACX1,     Absolute,                         WRAP_BANK, LDY)
libRR_rOP16("ldy ", ACX0,     Absolute,                         WRAP_BANK, LDY16)
libRR_rOPX("ropX", ACSlow,   AbsoluteSlow,                     WRAP_BANK, LDY)

libRR_rOP8("ldy ", BCX1,     AbsoluteIndexedXX1,               WRAP_BANK, LDY)
libRR_rOP16("ldy ", BCX0,     AbsoluteIndexedXX0,               WRAP_BANK, LDY16)
libRR_rOPX("ropX", BCSlow,   AbsoluteIndexedXSlow,             WRAP_BANK, LDY)

/* LSR ********************************************************************* */

static void Op4AM1 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "LSR", 0x4A, 1);
	ICPU._Carry = Registers.AL & 1;
	Registers.AL >>= 1;
	SetZN8(Registers.AL);
}

static void Op4AM0 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "LSR", 0x4A, 1);
	ICPU._Carry = Registers.A.W & 1;
	Registers.A.W >>= 1;
	SetZN16(Registers.A.W);
}

static void Op4ASlow (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "LSR", 0x4A, 1);

	if (CheckMemory())
	{
		ICPU._Carry = Registers.AL & 1;
		Registers.AL >>= 1;
		SetZN8(Registers.AL);
	}
	else
	{
		ICPU._Carry = Registers.A.W & 1;
		Registers.A.W >>= 1;
		SetZN16(Registers.A.W);
	}
}

libRR_mOP8("lsr mop8", 46M1,     Direct,                           WRAP_BANK, LSR)
libRR_mOP16("lsr mop16", 46M0,     Direct,                           WRAP_BANK, LSR)
libRR_mOPM("lsr mopM", 46Slow,   DirectSlow,                       WRAP_BANK, LSR)

libRR_mOP8("lsr mop8", 56E1,     DirectIndexedXE1,                 WRAP_BANK, LSR)
libRR_mOP8("lsr mop8", 56E0M1,   DirectIndexedXE0,                 WRAP_BANK, LSR)
libRR_mOP16("lsr mop16", 56E0M0,   DirectIndexedXE0,                 WRAP_BANK, LSR)
libRR_mOPM("lsr mopM", 56Slow,   DirectIndexedXSlow,               WRAP_BANK, LSR)

libRR_mOP8("lsr mop8", 4EM1,     Absolute,                         WRAP_NONE, LSR)
libRR_mOP16("lsr mop16", 4EM0,     Absolute,                         WRAP_NONE, LSR)
libRR_mOPM("lsr mopM", 4ESlow,   AbsoluteSlow,                     WRAP_NONE, LSR)

libRR_mOP8("lsr mop8", 5EM1X1,   AbsoluteIndexedXX1,               WRAP_NONE, LSR)
libRR_mOP16("lsr mop16", 5EM0X1,   AbsoluteIndexedXX1,               WRAP_NONE, LSR)
libRR_mOP8("lsr mop8", 5EM1X0,   AbsoluteIndexedXX0,               WRAP_NONE, LSR)
libRR_mOP16("lsr mop16", 5EM0X0,   AbsoluteIndexedXX0,               WRAP_NONE, LSR)
libRR_mOPM("lsr mopM", 5ESlow,   AbsoluteIndexedXSlow,             WRAP_NONE, LSR)

/* ORA ********************************************************************* */

static void Op09M1 (void)
{
	libRR_log_instruction(Registers.PCw - 1, "ORA", 0x09, 1);
	Registers.AL |= Immediate8(READ);
	SetZN8(Registers.AL);
}

static void Op09M0 (void)
{
	libRR_log_instruction(Registers.PCw - 1, "ORA", 0x09, 1);
	Registers.A.W |= Immediate16(READ);
	SetZN16(Registers.A.W);
}

static void Op09Slow (void)
{
	libRR_log_instruction(Registers.PCw - 1, "ORA", 0x09, 1);
	if (CheckMemory())
	{
		Registers.AL |= Immediate8Slow(READ);
		SetZN8(Registers.AL);
	}
	else
	{
		Registers.A.W |= Immediate16Slow(READ);
		SetZN16(Registers.A.W);
	}
}

libRR_rOP8("ora 05", 05M1,     Direct,                           WRAP_BANK, ORA)
libRR_rOP16("ora ", 05M0,     Direct,                           WRAP_BANK, ORA16)
libRR_rOPM( "ora opm", 05Slow,   DirectSlow,                       WRAP_BANK, ORA)

libRR_rOP8("ora 15 E1",15E1,     DirectIndexedXE1,                 WRAP_BANK, ORA)
libRR_rOP8( "ora 15 E0",15E0M1,   DirectIndexedXE0,                 WRAP_BANK, ORA)
libRR_rOP16("ora 15 16bit", 15E0M0,   DirectIndexedXE0,                 WRAP_BANK, ORA16)
libRR_rOPM("ora 15 slow", 15Slow,   DirectIndexedXSlow,               WRAP_BANK, ORA)

libRR_rOP8( "ora ", 12E1,     DirectIndirectE1,                 WRAP_NONE, ORA)
libRR_rOP8("ora ", 12E0M1,   DirectIndirectE0,                 WRAP_NONE, ORA)
libRR_rOP16("ora ", 12E0M0,   DirectIndirectE0,                 WRAP_NONE, ORA16)
libRR_rOPM("ora ropM", 12Slow,   DirectIndirectSlow,               WRAP_NONE, ORA)

libRR_rOP8("ora ", 01E1,     DirectIndexedIndirectE1,          WRAP_NONE, ORA)
libRR_rOP8("ora ", 01E0M1,   DirectIndexedIndirectE0,          WRAP_NONE, ORA)
libRR_rOP16("ora ", 01E0M0,   DirectIndexedIndirectE0,          WRAP_NONE, ORA16)
libRR_rOPM("ora ropM", 01Slow,   DirectIndexedIndirectSlow,        WRAP_NONE, ORA)

libRR_rOP8("ora ", 11E1,     DirectIndirectIndexedE1,          WRAP_NONE, ORA)
libRR_rOP8("ora ", 11E0M1X1, DirectIndirectIndexedE0X1,        WRAP_NONE, ORA)
libRR_rOP16("ora ", 11E0M0X1, DirectIndirectIndexedE0X1,        WRAP_NONE, ORA16)
libRR_rOP8("ora ", 11E0M1X0, DirectIndirectIndexedE0X0,        WRAP_NONE, ORA)
libRR_rOP16("ora ", 11E0M0X0, DirectIndirectIndexedE0X0,        WRAP_NONE, ORA16)
libRR_rOPM("ora ropM", 11Slow,   DirectIndirectIndexedSlow,        WRAP_NONE, ORA)

libRR_rOP8("ora ", 07M1,     DirectIndirectLong,               WRAP_NONE, ORA)
libRR_rOP16("ora ", 07M0,     DirectIndirectLong,               WRAP_NONE, ORA16)
libRR_rOPM("ora ropM", 07Slow,   DirectIndirectLongSlow,           WRAP_NONE, ORA)

libRR_rOP8("ora ", 17M1,     DirectIndirectIndexedLong,        WRAP_NONE, ORA)
libRR_rOP16("ora ", 17M0,     DirectIndirectIndexedLong,        WRAP_NONE, ORA16)
libRR_rOPM("ora ropM", 17Slow,   DirectIndirectIndexedLongSlow,    WRAP_NONE, ORA)

libRR_rOP8("ora ", 0DM1,     Absolute,                         WRAP_NONE, ORA)
libRR_rOP16("ora ", 0DM0,     Absolute,                         WRAP_NONE, ORA16)
libRR_rOPM("ora ropM", 0DSlow,   AbsoluteSlow,                     WRAP_NONE, ORA)

libRR_rOP8("ora ", 1DM1X1,   AbsoluteIndexedXX1,               WRAP_NONE, ORA)
libRR_rOP16("ora ", 1DM0X1,   AbsoluteIndexedXX1,               WRAP_NONE, ORA16)
libRR_rOP8("ora ", 1DM1X0,   AbsoluteIndexedXX0,               WRAP_NONE, ORA)
libRR_rOP16("ora ", 1DM0X0,   AbsoluteIndexedXX0,               WRAP_NONE, ORA16)
libRR_rOPM("ora ropM", 1DSlow,   AbsoluteIndexedXSlow,             WRAP_NONE, ORA)

libRR_rOP8("ora ", 19M1X1,   AbsoluteIndexedYX1,               WRAP_NONE, ORA)
libRR_rOP16("ora ", 19M0X1,   AbsoluteIndexedYX1,               WRAP_NONE, ORA16)
libRR_rOP8("ora ", 19M1X0,   AbsoluteIndexedYX0,               WRAP_NONE, ORA)
libRR_rOP16("ora ", 19M0X0,   AbsoluteIndexedYX0,               WRAP_NONE, ORA16)
libRR_rOPM("ora ropM", 19Slow,   AbsoluteIndexedYSlow,             WRAP_NONE, ORA)

libRR_rOP8("ora ", 0FM1,     AbsoluteLong,                     WRAP_NONE, ORA)
libRR_rOP16("ora ", 0FM0,     AbsoluteLong,                     WRAP_NONE, ORA16)
libRR_rOPM("ora ropM", 0FSlow,   AbsoluteLongSlow,                 WRAP_NONE, ORA)

libRR_rOP8("ora ", 1FM1,     AbsoluteLongIndexedX,             WRAP_NONE, ORA)
libRR_rOP16("ora ", 1FM0,     AbsoluteLongIndexedX,             WRAP_NONE, ORA16)
libRR_rOPM("ora ropM", 1FSlow,   AbsoluteLongIndexedXSlow,         WRAP_NONE, ORA)

libRR_rOP8("ora ", 03M1,     StackRelative,                    WRAP_NONE, ORA)
libRR_rOP16("ora ", 03M0,     StackRelative,                    WRAP_NONE, ORA16)
libRR_rOPM("ora ropM", 03Slow,   StackRelativeSlow,                WRAP_NONE, ORA)

libRR_rOP8("ora ", 13M1,     StackRelativeIndirectIndexed,     WRAP_NONE, ORA)
libRR_rOP16("ora ", 13M0,     StackRelativeIndirectIndexed,     WRAP_NONE, ORA16)
libRR_rOPM("ora ropM", 13Slow,   StackRelativeIndirectIndexedSlow, WRAP_NONE, ORA)

/* ROL ********************************************************************* */

static void Op2AM1 (void)
{
	uint16 w;
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "ROL", 0x2A, 1);
	w = (((uint16) Registers.AL) << 1) | CheckCarry();
	ICPU._Carry = w >= 0x100;
	Registers.AL = (uint8) w;
	SetZN8(Registers.AL);
}

static void Op2AM0 (void)
{
	uint32 w;
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "ROL", 0x2A, 1);
	w = (((uint32) Registers.A.W) << 1) | CheckCarry();
	ICPU._Carry = w >= 0x10000;
	Registers.A.W = (uint16) w;
	SetZN16(Registers.A.W);
}

static void Op2ASlow (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "ROL", 0x2A, 1);

	if (CheckMemory())
	{
		uint16	w = (((uint16) Registers.AL) << 1) | CheckCarry();
		ICPU._Carry = w >= 0x100;
		Registers.AL = (uint8) w;
		SetZN8(Registers.AL);
	}
	else
	{
		uint32	w = (((uint32) Registers.A.W) << 1) | CheckCarry();
		ICPU._Carry = w >= 0x10000;
		Registers.A.W = (uint16) w;
		SetZN16(Registers.A.W);
	}
}

libRR_mOP8("rol mop8", 26M1,     Direct,                           WRAP_BANK, ROL)
libRR_mOP16("rol mop16", 26M0,     Direct,                           WRAP_BANK, ROL)
libRR_mOPM("rol mopM", 26Slow,   DirectSlow,                       WRAP_BANK, ROL)

libRR_mOP8("rol mop8", 36E1,     DirectIndexedXE1,                 WRAP_BANK, ROL)
libRR_mOP8("rol mop8", 36E0M1,   DirectIndexedXE0,                 WRAP_BANK, ROL)
libRR_mOP16("rol mop16", 36E0M0,   DirectIndexedXE0,                 WRAP_BANK, ROL)
libRR_mOPM("rol mopM", 36Slow,   DirectIndexedXSlow,               WRAP_BANK, ROL)

libRR_mOP8("rol mop8", 2EM1,     Absolute,                         WRAP_NONE, ROL)
libRR_mOP16("rol mop16", 2EM0,     Absolute,                         WRAP_NONE, ROL)
libRR_mOPM("rol mopM", 2ESlow,   AbsoluteSlow,                     WRAP_NONE, ROL)

libRR_mOP8("rol mop8", 3EM1X1,   AbsoluteIndexedXX1,               WRAP_NONE, ROL)
libRR_mOP16("rol mop16", 3EM0X1,   AbsoluteIndexedXX1,               WRAP_NONE, ROL)
libRR_mOP8("rol mop8", 3EM1X0,   AbsoluteIndexedXX0,               WRAP_NONE, ROL)
libRR_mOP16("rol mop16", 3EM0X0,   AbsoluteIndexedXX0,               WRAP_NONE, ROL)
libRR_mOPM("rol mopM", 3ESlow,   AbsoluteIndexedXSlow,             WRAP_NONE, ROL)

/* ROR ********************************************************************* */

static void Op6AM1 (void)
{
	uint16 w;
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "ROR", 0x6A, 1);
	w = ((uint16) Registers.AL) | (((uint16) CheckCarry()) << 8);
	ICPU._Carry = w & 1;
	w >>= 1;
	Registers.AL = (uint8) w;
	SetZN8(Registers.AL);
}

static void Op6AM0 (void)
{
	uint32 w;
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "ROR", 0x6A, 1);
	w = ((uint32) Registers.A.W) | (((uint32) CheckCarry()) << 16);
	ICPU._Carry = w & 1;
	w >>= 1;
	Registers.A.W = (uint16) w;
	SetZN16(Registers.A.W);
}

static void Op6ASlow (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "ROR", 0x6A, 1);

	if (CheckMemory())
	{
		uint16	w = ((uint16) Registers.AL) | (((uint16) CheckCarry()) << 8);
		ICPU._Carry = w & 1;
		w >>= 1;
		Registers.AL = (uint8) w;
		SetZN8(Registers.AL);
	}
	else
	{
		uint32	w = ((uint32) Registers.A.W) | (((uint32) CheckCarry()) << 16);
		ICPU._Carry = w & 1;
		w >>= 1;
		Registers.A.W = (uint16) w;
		SetZN16(Registers.A.W);
	}
}

libRR_mOP8("ror mop8", 66M1,     Direct,                           WRAP_BANK, ROR)
libRR_mOP16("ror mop16", 66M0,     Direct,                           WRAP_BANK, ROR)
libRR_mOPM("ror mopM", 66Slow,   DirectSlow,                       WRAP_BANK, ROR)

libRR_mOP8("ror mop8", 76E1,     DirectIndexedXE1,                 WRAP_BANK, ROR)
libRR_mOP8("ror mop8", 76E0M1,   DirectIndexedXE0,                 WRAP_BANK, ROR)
libRR_mOP16("ror mop16", 76E0M0,   DirectIndexedXE0,                 WRAP_BANK, ROR)
libRR_mOPM("ror mopM", 76Slow,   DirectIndexedXSlow,               WRAP_BANK, ROR)

libRR_mOP8("ror mop8", 6EM1,     Absolute,                         WRAP_NONE, ROR)
libRR_mOP16("ror mop16", 6EM0,     Absolute,                         WRAP_NONE, ROR)
libRR_mOPM("ror mopM", 6ESlow,   AbsoluteSlow,                     WRAP_NONE, ROR)

libRR_mOP8("ror mop8", 7EM1X1,   AbsoluteIndexedXX1,               WRAP_NONE, ROR)
libRR_mOP16("ror mop16", 7EM0X1,   AbsoluteIndexedXX1,               WRAP_NONE, ROR)
libRR_mOP8("ror mop8", 7EM1X0,   AbsoluteIndexedXX0,               WRAP_NONE, ROR)
libRR_mOP16("ror mop16", 7EM0X0,   AbsoluteIndexedXX0,               WRAP_NONE, ROR)
libRR_mOPM("ror mopM", 7ESlow,   AbsoluteIndexedXSlow,             WRAP_NONE, ROR)

/* SBC ********************************************************************* */

static void OpE9M1 (void)
{
	uint32 libRR_temp = Immediate8(READ);
	libRR_log_instruction_1int(Registers.PCw - 2, "SBC %int%", 0xE9, 2, libRR_temp);
	SBC8(libRR_temp);
}

static void OpE9M0 (void)
{
	uint32 libRR_temp = Immediate16(READ);
	libRR_log_instruction_1int(Registers.PCw - 3, "SBC %int%", 0xE9, 3,libRR_temp);
	SBC16(libRR_temp);
}

static void OpE9Slow (void)
{
	if (CheckMemory())
	{	
		uint32 libRR_temp = Immediate8Slow(READ);
		libRR_log_instruction_1int(Registers.PCw - 2, "SBC %int%", 0xE9, 2, libRR_temp);
		SBC8(libRR_temp); 
	}
	else
	{	
		uint32 libRR_temp = Immediate16Slow(READ);
		libRR_log_instruction_1int(Registers.PCw - 3, "SBC %int%", 0xE9, 3,libRR_temp);
		SBC16(libRR_temp); 
		}
}

libRR_rOP8("sbc ", E5M1,     Direct,                           WRAP_BANK, SBC)
libRR_rOP16("sbc ", E5M0,     Direct,                           WRAP_BANK, SBC16)
libRR_rOPM("sbc ropM", E5Slow,   DirectSlow,                       WRAP_BANK, SBC)

libRR_rOP8("sbc ", F5E1,     DirectIndexedXE1,                 WRAP_BANK, SBC)
libRR_rOP8("sbc ", F5E0M1,   DirectIndexedXE0,                 WRAP_BANK, SBC)
libRR_rOP16("sbc ", F5E0M0,   DirectIndexedXE0,                 WRAP_BANK, SBC16)
libRR_rOPM("sbc ropM", F5Slow,   DirectIndexedXSlow,               WRAP_BANK, SBC)

libRR_rOP8("sbc ", F2E1,     DirectIndirectE1,                 WRAP_NONE, SBC)
libRR_rOP8("sbc ", F2E0M1,   DirectIndirectE0,                 WRAP_NONE, SBC)
libRR_rOP16("sbc ", F2E0M0,   DirectIndirectE0,                 WRAP_NONE, SBC16)
libRR_rOPM("sbc ropM", F2Slow,   DirectIndirectSlow,               WRAP_NONE, SBC)

libRR_rOP8("sbc ", E1E1,     DirectIndexedIndirectE1,          WRAP_NONE, SBC)
libRR_rOP8("sbc ", E1E0M1,   DirectIndexedIndirectE0,          WRAP_NONE, SBC)
libRR_rOP16("sbc ", E1E0M0,   DirectIndexedIndirectE0,          WRAP_NONE, SBC16)
libRR_rOPM("sbc ropM", E1Slow,   DirectIndexedIndirectSlow,        WRAP_NONE, SBC)

libRR_rOP8("sbc ", F1E1,     DirectIndirectIndexedE1,          WRAP_NONE, SBC)
libRR_rOP8("sbc ", F1E0M1X1, DirectIndirectIndexedE0X1,        WRAP_NONE, SBC)
libRR_rOP16("sbc ", F1E0M0X1, DirectIndirectIndexedE0X1,        WRAP_NONE, SBC16)
libRR_rOP8("sbc ", F1E0M1X0, DirectIndirectIndexedE0X0,        WRAP_NONE, SBC)
libRR_rOP16("sbc ", F1E0M0X0, DirectIndirectIndexedE0X0,        WRAP_NONE, SBC16)
libRR_rOPM("sbc ropM", F1Slow,   DirectIndirectIndexedSlow,        WRAP_NONE, SBC)

libRR_rOP8("sbc ", E7M1,     DirectIndirectLong,               WRAP_NONE, SBC)
libRR_rOP16("sbc ", E7M0,     DirectIndirectLong,               WRAP_NONE, SBC16)
libRR_rOPM("sbc ropM", E7Slow,   DirectIndirectLongSlow,           WRAP_NONE, SBC)

libRR_rOP8("sbc ", F7M1,     DirectIndirectIndexedLong,        WRAP_NONE, SBC)
libRR_rOP16("sbc ", F7M0,     DirectIndirectIndexedLong,        WRAP_NONE, SBC16)
libRR_rOPM("sbc ropM", F7Slow,   DirectIndirectIndexedLongSlow,    WRAP_NONE, SBC)

libRR_rOP8("sbc ", EDM1,     Absolute,                         WRAP_NONE, SBC)
libRR_rOP16("sbc ", EDM0,     Absolute,                         WRAP_NONE, SBC16)
libRR_rOPM("sbc ropM", EDSlow,   AbsoluteSlow,                     WRAP_NONE, SBC)

libRR_rOP8("sbc ", FDM1X1,   AbsoluteIndexedXX1,               WRAP_NONE, SBC)
libRR_rOP16("sbc ", FDM0X1,   AbsoluteIndexedXX1,               WRAP_NONE, SBC16)
libRR_rOP8("sbc ", FDM1X0,   AbsoluteIndexedXX0,               WRAP_NONE, SBC)
libRR_rOP16("sbc ", FDM0X0,   AbsoluteIndexedXX0,               WRAP_NONE, SBC16)
libRR_rOPM("sbc ropM", FDSlow,   AbsoluteIndexedXSlow,             WRAP_NONE, SBC)

libRR_rOP8("sbc ", F9M1X1,   AbsoluteIndexedYX1,               WRAP_NONE, SBC)
libRR_rOP16("sbc ", F9M0X1,   AbsoluteIndexedYX1,               WRAP_NONE, SBC16)
libRR_rOP8("sbc ", F9M1X0,   AbsoluteIndexedYX0,               WRAP_NONE, SBC)
libRR_rOP16("sbc ", F9M0X0,   AbsoluteIndexedYX0,               WRAP_NONE, SBC16)
libRR_rOPM("sbc ropM", F9Slow,   AbsoluteIndexedYSlow,             WRAP_NONE, SBC)

libRR_rOP8("sbc ", EFM1,     AbsoluteLong,                     WRAP_NONE, SBC)
libRR_rOP16("sbc ", EFM0,     AbsoluteLong,                     WRAP_NONE, SBC16)
libRR_rOPM("sbc ropM", EFSlow,   AbsoluteLongSlow,                 WRAP_NONE, SBC)

libRR_rOP8("sbc ", FFM1,     AbsoluteLongIndexedX,             WRAP_NONE, SBC)
libRR_rOP16("sbc ", FFM0,     AbsoluteLongIndexedX,             WRAP_NONE, SBC16)
libRR_rOPM("sbc ropM", FFSlow,   AbsoluteLongIndexedXSlow,         WRAP_NONE, SBC)

libRR_rOP8("sbc ", E3M1,     StackRelative,                    WRAP_NONE, SBC)
libRR_rOP16("sbc ", E3M0,     StackRelative,                    WRAP_NONE, SBC16)
libRR_rOPM("sbc ropM", E3Slow,   StackRelativeSlow,                WRAP_NONE, SBC)

libRR_rOP8("sbc ", F3M1,     StackRelativeIndirectIndexed,     WRAP_NONE, SBC)
libRR_rOP16("sbc ", F3M0,     StackRelativeIndirectIndexed,     WRAP_NONE, SBC16)
libRR_rOPM("sbc ropM", F3Slow,   StackRelativeIndirectIndexedSlow, WRAP_NONE, SBC)

/* STA ********************************************************************* */

libRR_wOP8 ("sta ", 85M1,     Direct,                           WRAP_BANK, STA)
libRR_wOP16("sta ", 85M0,     Direct,                           WRAP_BANK, STA)
libRR_wOPX("sta wopM", 85Slow,   DirectSlow,                       WRAP_BANK, STA)

libRR_wOP8 ("sta ", 95E1,     DirectIndexedXE1,                 WRAP_BANK, STA)
libRR_wOP8 ("sta ", 95E0M1,   DirectIndexedXE0,                 WRAP_BANK, STA)
libRR_wOP16("sta ", 95E0M0,   DirectIndexedXE0,                 WRAP_BANK, STA)
libRR_wOPX("sta wopM", 95Slow,   DirectIndexedXSlow,               WRAP_BANK, STA)

libRR_wOP8 ("sta ", 92E1,     DirectIndirectE1,                 WRAP_NONE, STA)
libRR_wOP8 ("sta ", 92E0M1,   DirectIndirectE0,                 WRAP_NONE, STA)
libRR_wOP16("sta ", 92E0M0,   DirectIndirectE0,                 WRAP_NONE, STA)
libRR_wOPX("sta wopM", 92Slow,   DirectIndirectSlow,               WRAP_NONE, STA)

libRR_wOP8 ("sta ", 81E1,     DirectIndexedIndirectE1,          WRAP_NONE, STA)
libRR_wOP8 ("sta ", 81E0M1,   DirectIndexedIndirectE0,          WRAP_NONE, STA)
libRR_wOP16("sta ", 81E0M0,   DirectIndexedIndirectE0,          WRAP_NONE, STA)
libRR_wOPX("sta wopM", 81Slow,   DirectIndexedIndirectSlow,        WRAP_NONE, STA)

libRR_wOP8 ("sta ", 91E1,     DirectIndirectIndexedE1,          WRAP_NONE, STA)
libRR_wOP8 ("sta ", 91E0M1X1, DirectIndirectIndexedE0X1,        WRAP_NONE, STA)
libRR_wOP16("sta ", 91E0M0X1, DirectIndirectIndexedE0X1,        WRAP_NONE, STA)
libRR_wOP8 ("sta ", 91E0M1X0, DirectIndirectIndexedE0X0,        WRAP_NONE, STA)
libRR_wOP16("sta ", 91E0M0X0, DirectIndirectIndexedE0X0,        WRAP_NONE, STA)
libRR_wOPX("sta wopM", 91Slow,   DirectIndirectIndexedSlow,        WRAP_NONE, STA)

libRR_wOP8 ("sta ", 87M1,     DirectIndirectLong,               WRAP_NONE, STA)
libRR_wOP16("sta ", 87M0,     DirectIndirectLong,               WRAP_NONE, STA)
libRR_wOPX("sta wopM", 87Slow,   DirectIndirectLongSlow,           WRAP_NONE, STA)

libRR_wOP8 ("sta ", 97M1,     DirectIndirectIndexedLong,        WRAP_NONE, STA)
libRR_wOP16("sta ", 97M0,     DirectIndirectIndexedLong,        WRAP_NONE, STA)
libRR_wOPX("sta wopM", 97Slow,   DirectIndirectIndexedLongSlow,    WRAP_NONE, STA)

libRR_wOP8 ("sta ", 8DM1,     Absolute,                         WRAP_NONE, STA)
libRR_wOP16("sta ", 8DM0,     Absolute,                         WRAP_NONE, STA)
libRR_wOPX("sta wopM", 8DSlow,   AbsoluteSlow,                     WRAP_NONE, STA)

libRR_wOP8 ("sta ", 9DM1X1,   AbsoluteIndexedXX1,               WRAP_NONE, STA)
libRR_wOP16("sta ", 9DM0X1,   AbsoluteIndexedXX1,               WRAP_NONE, STA)
libRR_wOP8 ("sta ", 9DM1X0,   AbsoluteIndexedXX0,               WRAP_NONE, STA)
libRR_wOP16("sta ", 9DM0X0,   AbsoluteIndexedXX0,               WRAP_NONE, STA)
libRR_wOPX("sta wopM", 9DSlow,   AbsoluteIndexedXSlow,             WRAP_NONE, STA)

libRR_wOP8 ("sta ", 99M1X1,   AbsoluteIndexedYX1,               WRAP_NONE, STA)
libRR_wOP16("sta ", 99M0X1,   AbsoluteIndexedYX1,               WRAP_NONE, STA)
libRR_wOP8 ("sta ", 99M1X0,   AbsoluteIndexedYX0,               WRAP_NONE, STA)
libRR_wOP16("sta ", 99M0X0,   AbsoluteIndexedYX0,               WRAP_NONE, STA)
libRR_wOPX("sta wopM", 99Slow,   AbsoluteIndexedYSlow,             WRAP_NONE, STA)

libRR_wOP8 ("sta ", 8FM1,     AbsoluteLong,                     WRAP_NONE, STA)
libRR_wOP16("sta ", 8FM0,     AbsoluteLong,                     WRAP_NONE, STA)
libRR_wOPX("sta wopM", 8FSlow,   AbsoluteLongSlow,                 WRAP_NONE, STA)

libRR_wOP8 ("sta ", 9FM1,     AbsoluteLongIndexedX,             WRAP_NONE, STA)
libRR_wOP16("sta ", 9FM0,     AbsoluteLongIndexedX,             WRAP_NONE, STA)
libRR_wOPX("sta wopM", 9FSlow,   AbsoluteLongIndexedXSlow,         WRAP_NONE, STA)

libRR_wOP8 ("sta ", 83M1,     StackRelative,                    WRAP_NONE, STA)
libRR_wOP16("sta ", 83M0,     StackRelative,                    WRAP_NONE, STA)
libRR_wOPX("sta wopM", 83Slow,   StackRelativeSlow,                WRAP_NONE, STA)

libRR_wOP8 ("sta ", 93M1,     StackRelativeIndirectIndexed,     WRAP_NONE, STA)
libRR_wOP16("sta ", 93M0,     StackRelativeIndirectIndexed,     WRAP_NONE, STA)
libRR_wOPX("sta wopM", 93Slow,   StackRelativeIndirectIndexedSlow, WRAP_NONE, STA)

/* STX ********************************************************************* */

libRR_wOP8 ("stx ", 86X1,     Direct,                           WRAP_BANK, STX)
libRR_wOP16("stx ", 86X0,     Direct,                           WRAP_BANK, STX)
libRR_wOPX("stx wopX", 86Slow,   DirectSlow,                       WRAP_BANK, STX)

libRR_wOP8 ("stx ", 96E1,     DirectIndexedYE1,                 WRAP_BANK, STX)
libRR_wOP8 ("stx ", 96E0X1,   DirectIndexedYE0,                 WRAP_BANK, STX)
libRR_wOP16("stx ", 96E0X0,   DirectIndexedYE0,                 WRAP_BANK, STX)
libRR_wOPX("stx wopX", 96Slow,   DirectIndexedYSlow,               WRAP_BANK, STX)

libRR_wOP8 ("stx ", 8EX1,     Absolute,                         WRAP_BANK, STX)
libRR_wOP16("stx ", 8EX0,     Absolute,                         WRAP_BANK, STX)
libRR_wOPX("stx wopX", 8ESlow,   AbsoluteSlow,                     WRAP_BANK, STX)

/* STY ********************************************************************* */

libRR_wOP8 ("sty ", 84X1,     Direct,                           WRAP_BANK, STY)
libRR_wOP16("sty ", 84X0,     Direct,                           WRAP_BANK, STY)
libRR_wOPX("sty wopX", 84Slow,   DirectSlow,                       WRAP_BANK, STY)

libRR_wOP8 ("sty ", 94E1,     DirectIndexedXE1,                 WRAP_BANK, STY)
libRR_wOP8 ("sty ", 94E0X1,   DirectIndexedXE0,                 WRAP_BANK, STY)
libRR_wOP16("sty ", 94E0X0,   DirectIndexedXE0,                 WRAP_BANK, STY)
libRR_wOPX("sty wopX", 94Slow,   DirectIndexedXSlow,               WRAP_BANK, STY)

libRR_wOP8 ("sty ", 8CX1,     Absolute,                         WRAP_BANK, STY)
libRR_wOP16("sty ", 8CX0,     Absolute,                         WRAP_BANK, STY)
libRR_wOPX("sty wopX", 8CSlow,   AbsoluteSlow,                     WRAP_BANK, STY)

/* STZ ********************************************************************* */

libRR_wOP8 ("stz ", 64M1,     Direct,                           WRAP_BANK, STZ)
libRR_wOP16("stz ", 64M0,     Direct,                           WRAP_BANK, STZ)
libRR_wOPX("stz wopM", 64Slow,   DirectSlow,                       WRAP_BANK, STZ)

libRR_wOP8 ("stz ", 74E1,     DirectIndexedXE1,                 WRAP_BANK, STZ)
libRR_wOP8 ("stz ", 74E0M1,   DirectIndexedXE0,                 WRAP_BANK, STZ)
libRR_wOP16("stz ", 74E0M0,   DirectIndexedXE0,                 WRAP_BANK, STZ)
libRR_wOPX("stz wopM", 74Slow,   DirectIndexedXSlow,               WRAP_BANK, STZ)

libRR_wOP8 ("stz ", 9CM1,     Absolute,                         WRAP_NONE, STZ)
libRR_wOP16("stz ", 9CM0,     Absolute,                         WRAP_NONE, STZ)
libRR_wOPX("stz wopM", 9CSlow,   AbsoluteSlow,                     WRAP_NONE, STZ)

libRR_wOP8 ("stz ", 9EM1X1,   AbsoluteIndexedXX1,               WRAP_NONE, STZ)
libRR_wOP16("stz ", 9EM0X1,   AbsoluteIndexedXX1,               WRAP_NONE, STZ)
libRR_wOP8 ("stz ", 9EM1X0,   AbsoluteIndexedXX0,               WRAP_NONE, STZ)
libRR_wOP16("stz ", 9EM0X0,   AbsoluteIndexedXX0,               WRAP_NONE, STZ)
libRR_wOPX("stz wopM", 9ESlow,   AbsoluteIndexedXSlow,             WRAP_NONE, STZ)

/* TRB ********************************************************************* */

libRR_mOP8("trb mop8", 14M1,     Direct,                           WRAP_BANK, TRB)
libRR_mOP16("trb mop16", 14M0,     Direct,                           WRAP_BANK, TRB)
libRR_mOPM("trb mopM", 14Slow,   DirectSlow,                       WRAP_BANK, TRB)

libRR_mOP8("trb mop8", 1CM1,     Absolute,                         WRAP_BANK, TRB)
libRR_mOP16("trb mop16", 1CM0,     Absolute,                         WRAP_BANK, TRB)
libRR_mOPM("trb mopM", 1CSlow,   AbsoluteSlow,                     WRAP_BANK, TRB)

/* TSB ********************************************************************* */

libRR_mOP8("tsb mop8", 04M1,     Direct,                           WRAP_BANK, TSB)
libRR_mOP16("tsb mop16", 04M0,     Direct,                           WRAP_BANK, TSB)
libRR_mOPM("tsb mopM", 04Slow,   DirectSlow,                       WRAP_BANK, TSB)

libRR_mOP8("tsb mop8", 0CM1,     Absolute,                         WRAP_BANK, TSB)
libRR_mOP16("tsb mop16", 0CM0,     Absolute,                         WRAP_BANK, TSB)
libRR_mOPM("tsb mopM", 0CSlow,   AbsoluteSlow,                     WRAP_BANK, TSB)

/* Branch Instructions ***************************************************** */

/* BCC */
libRR_bOP("bcc %r%", 90E0,   Relative,     !CheckCarry(),    0, 0)
libRR_bOP("bcc %r%", 90E1,   Relative,     !CheckCarry(),    0, 1)
libRR_bOP("bcc %r%", 90Slow, RelativeSlow, !CheckCarry(),    0, CheckEmulation())

/* BCS*/
libRR_bOP("bcs %r%", B0E0,   Relative,      CheckCarry(),    0, 0)
libRR_bOP("bcs %r%", B0E1,   Relative,      CheckCarry(),    0, 1)
libRR_bOP("bcs %r%", B0Slow, RelativeSlow,  CheckCarry(),    0, CheckEmulation())

/* BEQ*/
libRR_bOP("beq %r%", F0E0,   Relative,      CheckZero(),     2, 0)
libRR_bOP("beq %r%", F0E1,   Relative,      CheckZero(),     2, 1)
libRR_bOP("beq %r%", F0Slow, RelativeSlow,  CheckZero(),     2, CheckEmulation())

/* BMI*/
libRR_bOP("bmi %r%", 30E0,   Relative,      CheckNegative(), 1, 0)
libRR_bOP("bmi %r%", 30E1,   Relative,      CheckNegative(), 1, 1)
libRR_bOP("bmi %r%", 30Slow, RelativeSlow,  CheckNegative(), 1, CheckEmulation())

/* BNE*/
libRR_bOP("bne %r%", D0E0,   Relative,     !CheckZero(),     1, 0)
libRR_bOP("bne %r%", D0E1,   Relative,     !CheckZero(),     1, 1)
libRR_bOP("bne %r%", D0Slow, RelativeSlow, !CheckZero(),     1, CheckEmulation())

/* BPL*/
libRR_bOP("bpl %r%", 10E0,   Relative,     !CheckNegative(), 1, 0)
libRR_bOP("bpl %r%", 10E1,   Relative,     !CheckNegative(), 1, 1)
libRR_bOP("bpl %r%", 10Slow, RelativeSlow, !CheckNegative(), 1, CheckEmulation())

/* BRA*/
libRR_bOP("bra %r%", 80E0,   Relative,     1,                X, 0)
libRR_bOP("bra %r%", 80E1,   Relative,     1,                X, 1)
libRR_bOP("bra %r%", 80Slow, RelativeSlow, 1,                X, CheckEmulation())

/* BVC*/
libRR_bOP("bvc %r%", 50E0,   Relative,     !CheckOverflow(), 0, 0)
libRR_bOP("bvc %r%", 50E1,   Relative,     !CheckOverflow(), 0, 1)
libRR_bOP("bvc %r%", 50Slow, RelativeSlow, !CheckOverflow(), 0, CheckEmulation())

/* BVS*/
libRR_bOP("bvs %r%", 70E0,   Relative,      CheckOverflow(), 0, 0)
libRR_bOP("bvs %r%", 70E1,   Relative,      CheckOverflow(), 0, 1)
libRR_bOP("bvs %r%", 70Slow, RelativeSlow,  CheckOverflow(), 0, CheckEmulation())

/* BRL*/
static void Op82 (void)
{
	libRR_log_instruction(Registers.PCw - 1, "BRL", 0x82, 1);
	S9xSetPCBase(ICPU.ShiftedPB + RelativeLong(JUMP));
}

static void Op82Slow (void)
{
	libRR_log_instruction(Registers.PCw - 1, "BRL", 0x82, 1);
	S9xSetPCBase(ICPU.ShiftedPB + RelativeLongSlow(JUMP));
}

/* Flag Instructions ******************************************************* */

/* CLC*/
static void Op18 (void)
{
	libRR_log_instruction(Registers.PCw - 1, "CLC", 0x18, 1);
	ClearCarry();
	AddCycles(ONE_CYCLE);
}

/* SEC*/
static void Op38 (void)
{
	libRR_log_instruction(Registers.PCw - 1, "SEC", 0x38, 1);
	SetCarry();
	AddCycles(ONE_CYCLE);
}

/* CLD*/
static void OpD8 (void)
{
	libRR_log_instruction(Registers.PCw - 1, "CLD", 0xD8, 1);
	ClearDecimal();
	AddCycles(ONE_CYCLE);
}

/* SED*/
static void OpF8 (void)
{
	libRR_log_instruction(Registers.PCw - 1, "SED", 0xF8, 1);
	SetDecimal();
	AddCycles(ONE_CYCLE);
}

/* CLI*/
static void Op58 (void)
{
	libRR_log_instruction(Registers.PCw - 1, "CLI", 0x58, 1);
	ClearIRQ();
	AddCycles(ONE_CYCLE);
}

/* SEI*/
static void Op78 (void)
{
	libRR_log_instruction(Registers.PCw - 1, "SEI", 0x78, 1);
	SetIRQ();
	AddCycles(ONE_CYCLE);
}

/* CLV*/
static void OpB8 (void)
{
	libRR_log_instruction(Registers.PCw - 1, "CLV", 0xB8, 1);
	ClearOverflow();
	AddCycles(ONE_CYCLE);
}

/* DEX/DEY ***************************************************************** */

static void OpCAX1 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "DEX", 0xCA, 1);
	Registers.XL--;
	SetZN8(Registers.XL);
}

static void OpCAX0 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "DEX", 0xCA, 1);
	Registers.X.W--;
	SetZN16(Registers.X.W);
}

static void OpCASlow (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "DEX", 0xCA, 1);

	if (CheckIndex())
	{
		Registers.XL--;
		SetZN8(Registers.XL);
	}
	else
	{
		Registers.X.W--;
		SetZN16(Registers.X.W);
	}
}

static void Op88X1 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "DEY", 0x88, 1);
	Registers.YL--;
	SetZN8(Registers.YL);
}

static void Op88X0 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "DEY", 0x88, 1);
	Registers.Y.W--;
	SetZN16(Registers.Y.W);
}

static void Op88Slow (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "DEY", 0x88, 1);

	if (CheckIndex())
	{
		Registers.YL--;
		SetZN8(Registers.YL);
	}
	else
	{
		Registers.Y.W--;
		SetZN16(Registers.Y.W);
	}
}

/* INX/INY ***************************************************************** */

static void OpE8X1 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "INX", 0xE8, 1);
	Registers.XL++;
	SetZN8(Registers.XL);
}

static void OpE8X0 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "INX", 0xE8, 1);
	Registers.X.W++;
	SetZN16(Registers.X.W);
}

static void OpE8Slow (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "INX", 0xE8, 1);

	if (CheckIndex())
	{
		Registers.XL++;
		SetZN8(Registers.XL);
	}
	else
	{
		Registers.X.W++;
		SetZN16(Registers.X.W);
	}
}
// Op C8 = INY
static void OpC8X1 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "INY", 0xC8, 1);
	Registers.YL++;
	SetZN8(Registers.YL);
}

static void OpC8X0 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "INY", 0xC8, 1);
	Registers.Y.W++;
	SetZN16(Registers.Y.W);
}

static void OpC8Slow (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "INY", 0xC8, 1);

	if (CheckIndex())
	{
		Registers.YL++;
		SetZN8(Registers.YL);
	}
	else
	{
		Registers.Y.W++;
		SetZN16(Registers.Y.W);
	}
}

/* NOP ********************************************************************* */

static void OpEA (void)
{
	libRR_log_instruction(Registers.PCw - 1, "NOP", 0xEA, 1);
	AddCycles(ONE_CYCLE);
}

/* PUSH Instructions ******************************************************* */

#define PushW(w) \
	S9xSetWord_Write1(w, Registers.S.W - 1, WRAP_BANK); \
	Registers.S.W -= 2;

#define PushWE(w) \
	Registers.SL--; \
	S9xSetWord_Write1(w, Registers.S.W, WRAP_PAGE); \
	Registers.SL--;

#define PushB(b) \
	S9xSetByte(b, Registers.S.W--);

#define PushBE(b) \
	S9xSetByte(b, Registers.S.W); \
	Registers.SL--;

/* PEA*/
static void OpF4E0 (void)
{
	uint16	val = (uint16) ABSOLUTE_MACRO(NONE);
	libRR_log_instruction(Registers.PCw - 1, "PEA", 0xF4E0, 1);
	PushW(val);
	OpenBus = val & 0xff;
}

static void OpF4E1 (void)
{
	/* Note: PEA is a new instruction,*/
	/* and so doesn't respect the emu-mode stack bounds.*/
	uint16	val = (uint16) ABSOLUTE_MACRO(NONE);
	libRR_log_instruction(Registers.PCw - 1, "PEA", 0xF4E1, 1);
	PushW(val);
	OpenBus = val & 0xff;
	Registers.SH = 1;
}

static void OpF4Slow (void)
{
	uint16	val = (uint16) ABSOLUTESLOW_MACRO(NONE);
	libRR_log_instruction(Registers.PCw - 1, "PEA", 0xF4, 1);
	PushW(val);
	OpenBus = val & 0xff;
	if (CheckEmulation())
		Registers.SH = 1;
}

/* PEI*/
static void OpD4E0 (void)
{
	uint16	val = (uint16) DirectIndirectE0(NONE);
	libRR_log_instruction(Registers.PCw - 1, "PEI", 0xD4E1, 1);
	PushW(val);
	OpenBus = val & 0xff;
}

static void OpD4E1 (void)
{
	/* Note: PEI is a new instruction,*/
	/* and so doesn't respect the emu-mode stack bounds.*/
	uint16	val = (uint16) DirectIndirectE1(NONE);
	libRR_log_instruction(Registers.PCw - 1, "PEI", 0xD4E1, 1);
	PushW(val);
	OpenBus = val & 0xff;
	Registers.SH = 1;
}

static void OpD4Slow (void)
{
	uint16	val = (uint16) DirectIndirectSlow(NONE);
	libRR_log_instruction(Registers.PCw - 1, "PEI", 0xD4, 1);
	PushW(val);
	OpenBus = val & 0xff;
	if (CheckEmulation())
		Registers.SH = 1;
}

/* PER*/
static void Op62E0 (void)
{
	uint16	val = (uint16) RelativeLong(NONE);
	libRR_log_instruction(Registers.PCw - 1, "PER", 0x62E0, 1);
	PushW(val);
	OpenBus = val & 0xff;
}

static void Op62E1 (void)
{
	/* Note: PER is a new instruction,*/
	/* and so doesn't respect the emu-mode stack bounds.*/
	uint16	val = (uint16) RelativeLong(NONE);
	libRR_log_instruction(Registers.PCw - 1, "PER", 0x62E1, 1);
	PushW(val);
	OpenBus = val & 0xff;
	Registers.SH = 1;
}

static void Op62Slow (void)
{
	uint16	val = (uint16) RelativeLongSlow(NONE);
	libRR_log_instruction(Registers.PCw - 1, "PER", 0x62, 1);
	PushW(val);
	OpenBus = val & 0xff;
	if (CheckEmulation())
		Registers.SH = 1;
}

/* PHA*/
static void Op48E1 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "PHA", 0x48E1, 1);
	PushBE(Registers.AL);
	OpenBus = Registers.AL;
}

static void Op48E0M1 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "PHA", 0x48E0, 1);
	PushB(Registers.AL);
	OpenBus = Registers.AL;
}

static void Op48E0M0 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "PHA", 0x48E0, 1);
	PushW(Registers.A.W);
	OpenBus = Registers.AL;
}

static void Op48Slow (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "PHA", 0x48, 1);

	if (CheckEmulation())
	{
		PushBE(Registers.AL);
	}
	else
	if (CheckMemory())
	{
		PushB(Registers.AL);
	}
	else
	{
		PushW(Registers.A.W);
	}

	OpenBus = Registers.AL;
}

/* PHB*/
static void Op8BE1 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "PHB", 0x8BE1, 1);
	PushBE(Registers.DB);
	OpenBus = Registers.DB;
}

static void Op8BE0 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "PHB", 0x8BE0, 1);
	PushB(Registers.DB);
	OpenBus = Registers.DB;
}

static void Op8BSlow (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "PHB", 0x8B, 1);

	if (CheckEmulation())
	{
		PushBE(Registers.DB);
	}
	else
	{
		PushB(Registers.DB);
	}

	OpenBus = Registers.DB;
}

/* PHD*/
static void Op0BE0 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "PHD", 0x0BE0, 1);
	PushW(Registers.D.W);
	OpenBus = Registers.DL;
}

static void Op0BE1 (void)
{
	/* Note: PHD is a new instruction,*/
	/* and so doesn't respect the emu-mode stack bounds.*/
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "PHD", 0x0BE1, 1);
	PushW(Registers.D.W);
	OpenBus = Registers.DL;
	Registers.SH = 1;
}

static void Op0BSlow (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "PHD", 0x0B, 1);
	PushW(Registers.D.W);
	OpenBus = Registers.DL;
	if (CheckEmulation())
		Registers.SH = 1;
}

/* PHK*/
static void Op4BE1 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "PHK", 0x4BE1, 1);
	PushBE(Registers.PB);
	OpenBus = Registers.PB;
}

static void Op4BE0 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "PHK", 0x4BE0, 1);
	PushB(Registers.PB);
	OpenBus = Registers.PB;
}

static void Op4BSlow (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "PHK", 0x4B, 1);

	if (CheckEmulation())
	{
		PushBE(Registers.PB);
	}
	else
	{
		PushB(Registers.PB);
	}

	OpenBus = Registers.PB;
}

/* PHP*/
static void Op08E0 (void)
{
	S9xPackStatus();
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "PHP", 0x08E0, 1);
	PushB(Registers.PL);
	OpenBus = Registers.PL;
}

static void Op08E1 (void)
{
	S9xPackStatus();
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "PHP", 0x08E1, 1);
	PushBE(Registers.PL);
	OpenBus = Registers.PL;
}

static void Op08Slow (void)
{
	S9xPackStatus();
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "PHP", 0x08, 1);

	if (CheckEmulation())
	{
		PushBE(Registers.PL);
	}
	else
	{
		PushB(Registers.PL);
	}

	OpenBus = Registers.PL;
}

/* PHX*/
static void OpDAE1 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "PHX", 0xDAE1, 1);
	PushBE(Registers.XL);
	OpenBus = Registers.XL;
}

static void OpDAE0X1 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "PHX", 0xDAE0, 1);
	PushB(Registers.XL);
	OpenBus = Registers.XL;
}

static void OpDAE0X0 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "PHX", 0xDAE0, 1);
	PushW(Registers.X.W);
	OpenBus = Registers.XL;
}

static void OpDASlow (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "PHX", 0xDA, 1);

	if (CheckEmulation())
	{
		PushBE(Registers.XL);
	}
	else
	if (CheckIndex())
	{
		PushB(Registers.XL);
	}
	else
	{
		PushW(Registers.X.W);
	}

	OpenBus = Registers.XL;
}

/* PHY*/
static void Op5AE1 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "PHY", 0x5A, 1);
	PushBE(Registers.YL);
	OpenBus = Registers.YL;
}

static void Op5AE0X1 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "PHY", 0x5A, 1);
	PushB(Registers.YL);
	OpenBus = Registers.YL;
}

static void Op5AE0X0 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "PHY", 0x5A, 1);
	PushW(Registers.Y.W);
	OpenBus = Registers.YL;
}

static void Op5ASlow (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "PHY", 0x5A, 1);

	if (CheckEmulation())
	{
		PushBE(Registers.YL);
	}
	else
	if (CheckIndex())
	{
		PushB(Registers.YL);
	}
	else
	{
		PushW(Registers.Y.W);
	}

	OpenBus = Registers.YL;
}

/* PULL Instructions ******************************************************* */

#define PullW(w) \
	w = S9xGetWord(Registers.S.W + 1, WRAP_BANK); \
	Registers.S.W += 2;

#define PullWE(w) \
	Registers.SL++; \
	w = S9xGetWord(Registers.S.W, WRAP_PAGE); \
	Registers.SL++;

#define PullB(b) \
	b = S9xGetByte(++Registers.S.W);

#define PullBE(b) \
	Registers.SL++; \
	b = S9xGetByte(Registers.S.W);

/* PLA*/
static void Op68E1 (void)
{
	AddCycles(TWO_CYCLES);
	libRR_log_instruction(Registers.PCw - 1, "PLA", 0x68, 1);
	PullBE(Registers.AL);
	SetZN8(Registers.AL);
	OpenBus = Registers.AL;
}

static void Op68E0M1 (void)
{
	AddCycles(TWO_CYCLES);
	libRR_log_instruction(Registers.PCw - 1, "PLA", 0x68, 1);
	PullB(Registers.AL);
	SetZN8(Registers.AL);
	OpenBus = Registers.AL;
}

static void Op68E0M0 (void)
{
	AddCycles(TWO_CYCLES);
	libRR_log_instruction(Registers.PCw - 1, "PLA", 0x68, 1);
	PullW(Registers.A.W);
	SetZN16(Registers.A.W);
	OpenBus = Registers.AH;
}

static void Op68Slow (void)
{
	AddCycles(TWO_CYCLES);
	libRR_log_instruction(Registers.PCw - 1, "PLA", 0x68, 1);

	if (CheckEmulation())
	{
		PullBE(Registers.AL);
		SetZN8(Registers.AL);
		OpenBus = Registers.AL;
	}
	else
	if (CheckMemory())
	{
		PullB(Registers.AL);
		SetZN8(Registers.AL);
		OpenBus = Registers.AL;
	}
	else
	{
		PullW(Registers.A.W);
		SetZN16(Registers.A.W);
		OpenBus = Registers.AH;
	}
}

/* PLB*/
static void OpABE1 (void)
{
	AddCycles(TWO_CYCLES);
	libRR_log_instruction(Registers.PCw - 1, "PLB", 0xAB, 1);
	PullBE(Registers.DB);
	SetZN8(Registers.DB);
	ICPU.ShiftedDB = Registers.DB << 16;
	OpenBus = Registers.DB;
}

static void OpABE0 (void)
{
	AddCycles(TWO_CYCLES);
	libRR_log_instruction(Registers.PCw - 1, "PLB", 0xAB, 1);
	PullB(Registers.DB);
	SetZN8(Registers.DB);
	ICPU.ShiftedDB = Registers.DB << 16;
	OpenBus = Registers.DB;
}

static void OpABSlow (void)
{
	AddCycles(TWO_CYCLES);
	libRR_log_instruction(Registers.PCw - 1, "PLB", 0xAB, 1);

	if (CheckEmulation())
	{
		PullBE(Registers.DB);
	}
	else
	{
		PullB(Registers.DB);
	}

	SetZN8(Registers.DB);
	ICPU.ShiftedDB = Registers.DB << 16;
	OpenBus = Registers.DB;
}

/* PLD*/
static void Op2BE0 (void)
{
	AddCycles(TWO_CYCLES);
	libRR_log_instruction(Registers.PCw - 1, "PLD", 0x2B, 1);
	PullW(Registers.D.W);
	SetZN16(Registers.D.W);
	OpenBus = Registers.DH;
}

static void Op2BE1 (void)
{
	/* Note: PLD is a new instruction,*/
	/* and so doesn't respect the emu-mode stack bounds.*/
	AddCycles(TWO_CYCLES);
	libRR_log_instruction(Registers.PCw - 1, "PLD", 0x2B, 1);
	PullW(Registers.D.W);
	SetZN16(Registers.D.W);
	OpenBus = Registers.DH;
	Registers.SH = 1;
}

static void Op2BSlow (void)
{
	AddCycles(TWO_CYCLES);
	libRR_log_instruction(Registers.PCw - 1, "PLD", 0x2B, 1);
	PullW(Registers.D.W);
	SetZN16(Registers.D.W);
	OpenBus = Registers.DH;
	if (CheckEmulation())
		Registers.SH = 1;
}

/* PLP*/
static void Op28E1 (void)
{
	AddCycles(TWO_CYCLES);
	libRR_log_instruction(Registers.PCw - 1, "PLP", 0x28, 1);
	PullBE(Registers.PL);
	OpenBus = Registers.PL;
	SetFlags(MemoryFlag | IndexFlag);
	S9xUnpackStatus();
	S9xFixCycles();
}

static void Op28E0 (void)
{
	AddCycles(TWO_CYCLES);
	libRR_log_instruction(Registers.PCw - 1, "PLP", 0x28, 1);
	PullB(Registers.PL);
	OpenBus = Registers.PL;
	S9xUnpackStatus();

	if (CheckIndex())
	{
		Registers.XH = 0;
		Registers.YH = 0;
	}

	S9xFixCycles();
}

static void Op28Slow (void)
{
	AddCycles(TWO_CYCLES);
	libRR_log_instruction(Registers.PCw - 1, "PLP", 0x28, 1);

	if (CheckEmulation())
	{
		PullBE(Registers.PL);
		OpenBus = Registers.PL;
		SetFlags(MemoryFlag | IndexFlag);
	}
	else
	{
		PullB(Registers.PL);
		OpenBus = Registers.PL;
	}

	S9xUnpackStatus();

	if (CheckIndex())
	{
		Registers.XH = 0;
		Registers.YH = 0;
	}

	S9xFixCycles();
}

/* PLX*/
static void OpFAE1 (void)
{
	AddCycles(TWO_CYCLES);
	libRR_log_instruction(Registers.PCw - 1, "PLX", 0xFA, 1);
	PullBE(Registers.XL);
	SetZN8(Registers.XL);
	OpenBus = Registers.XL;
}

static void OpFAE0X1 (void)
{
	AddCycles(TWO_CYCLES);
	libRR_log_instruction(Registers.PCw - 1, "PLX", 0xFA, 1);
	PullB(Registers.XL);
	SetZN8(Registers.XL);
	OpenBus = Registers.XL;
}

static void OpFAE0X0 (void)
{
	AddCycles(TWO_CYCLES);
	libRR_log_instruction(Registers.PCw - 1, "PLX", 0xFA, 1);
	PullW(Registers.X.W);
	SetZN16(Registers.X.W);
	OpenBus = Registers.XH;
}

static void OpFASlow (void)
{
	AddCycles(TWO_CYCLES);
	libRR_log_instruction(Registers.PCw - 1, "PLX", 0xFA, 1);

	if (CheckEmulation())
	{
		PullBE(Registers.XL);
		SetZN8(Registers.XL);
		OpenBus = Registers.XL;
	}
	else
	if (CheckIndex())
	{
		PullB(Registers.XL);
		SetZN8(Registers.XL);
		OpenBus = Registers.XL;
	}
	else
	{
		PullW(Registers.X.W);
		SetZN16(Registers.X.W);
		OpenBus = Registers.XH;
	}
}

/* PLY*/
static void Op7AE1 (void)
{
	AddCycles(TWO_CYCLES);
	libRR_log_instruction(Registers.PCw - 1, "PLY", 0x7A, 1);
	PullBE(Registers.YL);
	SetZN8(Registers.YL);
	OpenBus = Registers.YL;
}

static void Op7AE0X1 (void)
{
	AddCycles(TWO_CYCLES);
	libRR_log_instruction(Registers.PCw - 1, "PLY", 0x7A, 1);
	PullB(Registers.YL);
	SetZN8(Registers.YL);
	OpenBus = Registers.YL;
}

static void Op7AE0X0 (void)
{
	AddCycles(TWO_CYCLES);
	libRR_log_instruction(Registers.PCw - 1, "PLY", 0x7A, 1);
	PullW(Registers.Y.W);
	SetZN16(Registers.Y.W);
	OpenBus = Registers.YH;
}

static void Op7ASlow (void)
{
	AddCycles(TWO_CYCLES);
	libRR_log_instruction(Registers.PCw - 1, "PLY", 0x7A, 1);

	if (CheckEmulation())
	{
		PullBE(Registers.YL);
		SetZN8(Registers.YL);
		OpenBus = Registers.YL;
	}
	else
	if (CheckIndex())
	{
		PullB(Registers.YL);
		SetZN8(Registers.YL);
		OpenBus = Registers.YL;
	}
	else
	{
		PullW(Registers.Y.W);
		SetZN16(Registers.Y.W);
		OpenBus = Registers.YH;
	}
}

/* Transfer Instructions *************************************************** */

/* TAX*/
static void OpAAX1 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "TAX", 0xAA, 1);
	Registers.XL = Registers.AL;
	SetZN8(Registers.XL);
}

static void OpAAX0 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "TAX", 0xAA, 1);
	Registers.X.W = Registers.A.W;
	SetZN16(Registers.X.W);
}

static void OpAASlow (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "TAX", 0xAA, 1);

	if (CheckIndex())
	{
		Registers.XL = Registers.AL;
		SetZN8(Registers.XL);
	}
	else
	{
		Registers.X.W = Registers.A.W;
		SetZN16(Registers.X.W);
	}
}

/* TAY*/
static void OpA8X1 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "TAY", 0xA8, 1);
	Registers.YL = Registers.AL;
	SetZN8(Registers.YL);
}

static void OpA8X0 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "TAY", 0xA8, 1);
	Registers.Y.W = Registers.A.W;
	SetZN16(Registers.Y.W);
}

static void OpA8Slow (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "TAY", 0xA8, 1);

	if (CheckIndex())
	{
		Registers.YL = Registers.AL;
		SetZN8(Registers.YL);
	}
	else
	{
		Registers.Y.W = Registers.A.W;
		SetZN16(Registers.Y.W);
	}
}

/* TCD*/
static void Op5B (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "TCD", 0x5B, 1);
	Registers.D.W = Registers.A.W;
	SetZN16(Registers.D.W);
}

/* TCS*/
static void Op1B (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "TCS", 0x1B, 1);
	Registers.S.W = Registers.A.W;
	if (CheckEmulation())
		Registers.SH = 1;
}

/* TDC*/
static void Op7B (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "TDC", 0x7B, 1);
	Registers.A.W = Registers.D.W;
	SetZN16(Registers.A.W);
}

/* TSC*/
static void Op3B (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "TSC", 0x3B, 1);
	Registers.A.W = Registers.S.W;
	SetZN16(Registers.A.W);
}

/* TSX*/
static void OpBAX1 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "TSX", 0xBA, 1);
	Registers.XL = Registers.SL;
	SetZN8(Registers.XL);
}

static void OpBAX0 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "TSX", 0xBA, 1);
	Registers.X.W = Registers.S.W;
	SetZN16(Registers.X.W);
}

static void OpBASlow (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "TSX", 0xBA, 1);

	if (CheckIndex())
	{
		Registers.XL = Registers.SL;
		SetZN8(Registers.XL);
	}
	else
	{
		Registers.X.W = Registers.S.W;
		SetZN16(Registers.X.W);
	}
}

/* TXA*/
static void Op8AM1 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "TXA", 0x8A, 1);
	Registers.AL = Registers.XL;
	SetZN8(Registers.AL);
}

static void Op8AM0 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "TXA", 0x8A, 1);
	Registers.A.W = Registers.X.W;
	SetZN16(Registers.A.W);
}

static void Op8ASlow (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "TXA", 0x8A, 1);

	if (CheckMemory())
	{
		Registers.AL = Registers.XL;
		SetZN8(Registers.AL);
	}
	else
	{
		Registers.A.W = Registers.X.W;
		SetZN16(Registers.A.W);
	}
}

/* TXS*/
static void Op9A (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "TXS", 0x9A, 1);
	Registers.S.W = Registers.X.W;
	if (CheckEmulation())
		Registers.SH = 1;
}

/* TXY*/
static void Op9BX1 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "TXY", 0x9B, 1);
	Registers.YL = Registers.XL;
	SetZN8(Registers.YL);
}

static void Op9BX0 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "TXY", 0x9B, 1);
	Registers.Y.W = Registers.X.W;
	SetZN16(Registers.Y.W);
}

static void Op9BSlow (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "TXY", 0x9B, 1);

	if (CheckIndex())
	{
		Registers.YL = Registers.XL;
		SetZN8(Registers.YL);
	}
	else
	{
		Registers.Y.W = Registers.X.W;
		SetZN16(Registers.Y.W);
	}
}

/* TYA*/
static void Op98M1 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "TYA", 0x98, 1);
	Registers.AL = Registers.YL;
	SetZN8(Registers.AL);
}

static void Op98M0 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "TYA", 0x98, 1);
	Registers.A.W = Registers.Y.W;
	SetZN16(Registers.A.W);
}

static void Op98Slow (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "TYA", 0x98, 1);

	if (CheckMemory())
	{
		Registers.AL = Registers.YL;
		SetZN8(Registers.AL);
	}
	else
	{
		Registers.A.W = Registers.Y.W;
		SetZN16(Registers.A.W);
	}
}

/* TYX*/
static void OpBBX1 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "TYX", 0xbb, 1);
	Registers.XL = Registers.YL;
	SetZN8(Registers.XL);
}

static void OpBBX0 (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "TYX", 0xbb, 1);
	Registers.X.W = Registers.Y.W;
	SetZN16(Registers.X.W);
}

static void OpBBSlow (void)
{
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "TYX", 0xbb, 1);

	if (CheckIndex())
	{
		Registers.XL = Registers.YL;
		SetZN8(Registers.XL);
	}
	else
	{
		Registers.X.W = Registers.Y.W;
		SetZN16(Registers.X.W);
	}
}

/* XCE ********************************************************************* */

static void OpFB (void)
{
	uint8 A1, A2;
	AddCycles(ONE_CYCLE);
	libRR_log_instruction(Registers.PCw - 1, "XCE", 0xfb, 1);

	A1 = ICPU._Carry;
	A2 = Registers.PH;

	ICPU._Carry = A2 & 1;
	Registers.PH = A1;

	if (CheckEmulation())
	{
		SetFlags(MemoryFlag | IndexFlag);
		Registers.SH = 1;
	}

	if (CheckIndex())
	{
		Registers.XH = 0;
		Registers.YH = 0;
	}

	S9xFixCycles();
}

/* BRK ********************************************************************* */

static void Op00 (void)
{
	uint16 addr;
	AddCycles(CPU.MemSpeed);
	libRR_log_instruction(Registers.PCw - 1, "BRK", 0x00, 1);

	if (!CheckEmulation())
	{
		PushB(Registers.PB);
		PushW(Registers.PCw + 1);
		S9xPackStatus();
		PushB(Registers.PL);
		OpenBus = Registers.PL;
		ClearDecimal();
		SetIRQ();

		addr = S9xGetWord(0xFFE6, WRAP_NONE);
	}
	else
	{
		PushWE(Registers.PCw + 1);
		S9xPackStatus();
		PushBE(Registers.PL);
		OpenBus = Registers.PL;
		ClearDecimal();
		SetIRQ();

		addr = S9xGetWord(0xFFFE, WRAP_NONE);
	}

	S9xSetPCBase(addr);
	OpenBus = addr >> 8;
}

/* IRQ ********************************************************************* */

void S9xOpcode_IRQ (void)
{
	libRR_log_instruction(Registers.PCw - 1, "IRQ", 0x00, 1);
	/* IRQ and NMI do an opcode fetch as their first "IO" cycle.*/
	AddCycles(CPU.MemSpeed + ONE_CYCLE);

	if (!CheckEmulation())
	{
		PushB(Registers.PB);
		PushW(Registers.PCw);
		S9xPackStatus();
		PushB(Registers.PL);
		OpenBus = Registers.PL;
		ClearDecimal();
		SetIRQ();

	#ifdef SA1_OPCODES
		OpenBus = Memory.FillRAM[0x2208];
		AddCycles(2 * SLOW_ONE_CYCLE);
		S9xSA1SetPCBase(Memory.FillRAM[0x2207] | (Memory.FillRAM[0x2208] << 8));
	#else
		if (Settings.SA1 && (Memory.FillRAM[0x2209] & 0x40))
		{
			OpenBus = Memory.FillRAM[0x220f];
			AddCycles(2 * SLOW_ONE_CYCLE);
			S9xSetPCBase(Memory.FillRAM[0x220e] | (Memory.FillRAM[0x220f] << 8));
		}
		else
		{
			uint16	addr = S9xGetWord(0xFFEE, WRAP_NONE);
			OpenBus = addr >> 8;
			S9xSetPCBase(addr);
		}
	#endif
	}
	else
	{
		PushWE(Registers.PCw);
		S9xPackStatus();
		PushBE(Registers.PL);
		OpenBus = Registers.PL;
		ClearDecimal();
		SetIRQ();

	#ifdef SA1_OPCODES
		OpenBus = Memory.FillRAM[0x2208];
		AddCycles(2 * SLOW_ONE_CYCLE);
		S9xSA1SetPCBase(Memory.FillRAM[0x2207] | (Memory.FillRAM[0x2208] << 8));
	#else
		if (Settings.SA1 && (Memory.FillRAM[0x2209] & 0x40))
		{
			OpenBus = Memory.FillRAM[0x220f];
			AddCycles(2 * SLOW_ONE_CYCLE);
			S9xSetPCBase(Memory.FillRAM[0x220e] | (Memory.FillRAM[0x220f] << 8));
		}
		else
		{
			uint16	addr = S9xGetWord(0xFFFE, WRAP_NONE);
			OpenBus = addr >> 8;
			S9xSetPCBase(addr);
		}
	#endif
	}
}

/* NMI ********************************************************************* */

void S9xOpcode_NMI (void)
{
	libRR_log_instruction(Registers.PCw - 1, "NMI", 0x00, 1);
	/* IRQ and NMI do an opcode fetch as their first "IO" cycle.*/
	AddCycles(CPU.MemSpeed + ONE_CYCLE);

	if (!CheckEmulation())
	{
		PushB(Registers.PB);
		PushW(Registers.PCw);
		S9xPackStatus();
		PushB(Registers.PL);
		OpenBus = Registers.PL;
		ClearDecimal();
		SetIRQ();

	#ifdef SA1_OPCODES
		OpenBus = Memory.FillRAM[0x2206];
		AddCycles(2 * SLOW_ONE_CYCLE);
		S9xSA1SetPCBase(Memory.FillRAM[0x2205] | (Memory.FillRAM[0x2206] << 8));
	#else
		if (Settings.SA1 && (Memory.FillRAM[0x2209] & 0x10))
		{
			OpenBus = Memory.FillRAM[0x220d];
			AddCycles(2 * SLOW_ONE_CYCLE);
			S9xSetPCBase(Memory.FillRAM[0x220c] | (Memory.FillRAM[0x220d] << 8));
		}
		else
		{
			uint16	addr = S9xGetWord(0xFFEA, WRAP_NONE);
			OpenBus = addr >> 8;
			S9xSetPCBase(addr);
		}
	#endif
	}
	else
	{
		PushWE(Registers.PCw);
		S9xPackStatus();
		PushBE(Registers.PL);
		OpenBus = Registers.PL;
		ClearDecimal();
		SetIRQ();

	#ifdef SA1_OPCODES
		OpenBus = Memory.FillRAM[0x2206];
		AddCycles(2 * SLOW_ONE_CYCLE);
		S9xSA1SetPCBase(Memory.FillRAM[0x2205] | (Memory.FillRAM[0x2206] << 8));
	#else
		if (Settings.SA1 && (Memory.FillRAM[0x2209] & 0x10))
		{
			OpenBus = Memory.FillRAM[0x220d];
			AddCycles(2 * SLOW_ONE_CYCLE);
			S9xSetPCBase(Memory.FillRAM[0x220c] | (Memory.FillRAM[0x220d] << 8));
		}
		else
		{
			uint16	addr = S9xGetWord(0xFFFA, WRAP_NONE);
			OpenBus = addr >> 8;
			S9xSetPCBase(addr);
		}
	#endif
	}
}

/* COP ********************************************************************* */

static void Op02 (void)
{
	libRR_log_instruction(Registers.PCw - 1, "COP", 0x02, 1);
	uint16 addr;
	AddCycles(CPU.MemSpeed);

	if (!CheckEmulation())
	{
		PushB(Registers.PB);
		PushW(Registers.PCw + 1);
		S9xPackStatus();
		PushB(Registers.PL);
		OpenBus = Registers.PL;
		ClearDecimal();
		SetIRQ();

		addr = S9xGetWord(0xFFE4, WRAP_NONE);
	}
	else
	{
		PushWE(Registers.PCw + 1);
		S9xPackStatus();
		PushBE(Registers.PL);
		OpenBus = Registers.PL;
		ClearDecimal();
		SetIRQ();

		addr = S9xGetWord(0xFFF4, WRAP_NONE);
	}

	S9xSetPCBase(addr);
	OpenBus = addr >> 8;
}

/* JML ********************************************************************* */

static void OpDC (void)
{
	libRR_log_instruction_1int(Registers.PCw - 1, "JML [%int%]", 0xdc, 2, READ_WORD(CPU.PCBase + Registers.PCw));
	S9xSetPCBase(AbsoluteIndirectLong(JUMP));
}

static void OpDCSlow (void)
{
	libRR_log_instruction_1int(Registers.PCw - 1, "JML [%int%]", 0xdc, 2, S9xGetWord(Registers.PBPC, WRAP_BANK));
	S9xSetPCBase(AbsoluteIndirectLongSlow(JUMP));
}

static void Op5C (void)
{
	libRR_log_instruction_1int(Registers.PCw - 1, "JML %int%", 0x5c, 4, READ_3WORD(CPU.PCBase + Registers.PCw));
	S9xSetPCBase(AbsoluteLong(JUMP));
}

static void Op5CSlow (void)
{
	libRR_log_instruction_1int(Registers.PCw - 1, "JML %int%", 0x5c, 4, S9xGetWord(Registers.PBPC, WRAP_BANK));
	S9xSetPCBase(AbsoluteLongSlow(JUMP));
}

/* JMP ********************************************************************* */

static void Op4C (void)
{
	libRR_log_instruction_1int(Registers.PCw - 1, "JMP %int%", 0x4c, 1, READ_WORD(CPU.PCBase + Registers.PCw));
	S9xSetPCBase(ICPU.ShiftedPB + ((uint16) ABSOLUTE_MACRO(JUMP)));
}

static void Op4CSlow (void)
{
	libRR_log_instruction_1int(Registers.PCw - 1, "JMP %int%", 0x4c, 1, S9xGetWord(Registers.PBPC, WRAP_BANK));
	S9xSetPCBase(ICPU.ShiftedPB + ((uint16) ABSOLUTESLOW_MACRO(JUMP)));
}

static void Op6C (void)
{
	libRR_log_instruction_1int(Registers.PCw - 1, "jmp (%int%)", 0x6c, 1, READ_WORD(CPU.PCBase + Registers.PCw));
	S9xSetPCBase(ICPU.ShiftedPB + ((uint16) AbsoluteIndirect(JUMP)));
}

static void Op6CSlow (void)
{
	libRR_log_instruction_1int(Registers.PCw - 1, "jmp (%int%)", 0x6c, 1, S9xGetWord(Registers.PBPC, WRAP_BANK));
	S9xSetPCBase(ICPU.ShiftedPB + ((uint16) AbsoluteIndirectSlow(JUMP)));
}

static void Op7C (void)
{
	libRR_log_instruction_1int(Registers.PCw - 1, "JMP (%int%,X)", 0x7c, 1, S9xGetWord(Registers.PBPC, WRAP_BANK));
	S9xSetPCBase(ICPU.ShiftedPB + ((uint16) AbsoluteIndexedIndirect(JUMP)));
}

static void Op7CSlow (void)
{
	libRR_log_instruction_1int(Registers.PCw - 1, "JMP (%int%,X)", 0x7c, 1, S9xGetWord(Registers.PBPC, WRAP_BANK));
	S9xSetPCBase(ICPU.ShiftedPB + ((uint16) AbsoluteIndexedIndirectSlow(JUMP)));
}

/* JSL/RTL ***************************************************************** */
// JSL - Jump to Subroutine
static void Op22E1 (void)
{
	/* Note: JSL is a new instruction,*/
	/* and so doesn't respect the emu-mode stack bounds.*/
	uint32	addr = AbsoluteLong(JSR);
	libRR_log_function_call(Registers.PCw - 1, addr, 0x00);
	libRR_log_instruction_1int(Registers.PCw - 1, "jsl %int%", 0x00, 1, addr);
	PushB(Registers.PB);
	PushW(Registers.PCw - 1);
	Registers.SH = 1;
	S9xSetPCBase(addr);
}

static void Op22E0 (void)
{
	uint32	addr = AbsoluteLong(JSR);
	libRR_log_function_call(Registers.PCw - 1, addr, 0x00);
	libRR_log_instruction_1int(Registers.PCw - 1, "jsl %int%", 0x00, 1, addr);
	PushB(Registers.PB);
	PushW(Registers.PCw - 1);
	S9xSetPCBase(addr);
}

static void Op22Slow (void)
{
	uint32	addr = AbsoluteLongSlow(JSR);
	printf("PB: %d\n", Registers.PB);
	libRR_log_function_call(Registers.PCw - 1, addr, 0x00);
	libRR_log_instruction_1int(Registers.PCw - 1, "jsl %int%", 0x00, 1, addr);
	PushB(Registers.PB);
	PushW(Registers.PCw - 1);
	if (CheckEmulation())
		Registers.SH = 1;
	S9xSetPCBase(addr);
}

// op6B = RTL
static void Op6BE1 (void)
{
	/* Note: RTL is a new instruction,*/
	/* and so doesn't respect the emu-mode stack bounds.*/
	AddCycles(TWO_CYCLES);
	libRR_log_instruction(Registers.PCw - 1, "rtl", 0x00, 1);
	PullW(Registers.PCw);
	PullB(Registers.PB);
	Registers.SH = 1;
	Registers.PCw++;
	S9xSetPCBase(Registers.PBPC);
}

static void Op6BE0 (void)
{
	AddCycles(TWO_CYCLES);
	libRR_log_instruction(Registers.PCw - 1, "rtl", 0x00, 1);
	PullW(Registers.PCw);
	PullB(Registers.PB);
	Registers.PCw++;
	S9xSetPCBase(Registers.PBPC);
}

static void Op6BSlow (void)
{
	AddCycles(TWO_CYCLES);
	libRR_log_instruction(Registers.PCw - 1, "rtl", 0x00, 1);
	PullW(Registers.PCw);
	PullB(Registers.PB);
	if (CheckEmulation())
		Registers.SH = 1;
	Registers.PCw++;
	S9xSetPCBase(Registers.PBPC);
}

/* JSR/RTS ***************************************************************** */
// JSR - Jump to Subroutine
static void Op20E1 (void)
{
	uint16	addr = ABSOLUTE_MACRO(JSR);
	libRR_log_function_call(Registers.PCw - 3, addr, 0x00);
	libRR_log_instruction_1int(Registers.PCw - 3, "jsr %int%", 0x00, 3, addr);
	AddCycles(ONE_CYCLE);
	PushWE(Registers.PCw - 1);
	S9xSetPCBase(ICPU.ShiftedPB + addr);
}

static void Op20E0 (void)
{
	uint16	addr = ABSOLUTE_MACRO(JSR);
	libRR_log_function_call(Registers.PCw - 3, addr, 0x00);
	libRR_log_instruction_1int(Registers.PCw - 3, "jsr %int%", 0x00, 3, addr);
	AddCycles(ONE_CYCLE);
	PushW(Registers.PCw - 1);
	S9xSetPCBase(ICPU.ShiftedPB + addr);
}

static void Op20Slow (void)
{
	uint16	addr = ABSOLUTESLOW_MACRO(JSR);
	libRR_log_function_call(Registers.PCw - 3, addr, 0x00);
	libRR_log_instruction_1int(Registers.PCw - 3, "jsr %int%", 0x00, 3, addr);

	AddCycles(ONE_CYCLE);

	if (CheckEmulation())
	{
		PushWE(Registers.PCw - 1);
	}
	else
	{
		PushW(Registers.PCw - 1);
	}

	S9xSetPCBase(ICPU.ShiftedPB + addr);
}

static void OpFCE1 (void)
{
	/* Note: JSR (a,X) is a new instruction,*/
	/* and so doesn't respect the emu-mode stack bounds.*/
	uint16	libRR_temp = libRR_AbsoluteIndexedIndirect();
	uint16	addr = AbsoluteIndexedIndirect(JSR);
	libRR_log_function_call(Registers.PCw - 3, addr, 0x00);
	libRR_log_instruction_1int(Registers.PCw - 3, "jsr %int%", 0x00, 3, libRR_temp);
	PushW(Registers.PCw - 1);
	Registers.SH = 1;
	S9xSetPCBase(ICPU.ShiftedPB + addr);
}


static void OpFCE0 (void)
{
	uint16	addr = AbsoluteIndexedIndirect(JSR);
	libRR_log_function_call(Registers.PCw - 3, addr, 0x00);
	libRR_log_instruction(Registers.PCw - 3, "jsr %int%", 0x00, 3);
	PushW(Registers.PCw - 1);
	S9xSetPCBase(ICPU.ShiftedPB + addr);
}

static void OpFCSlow (void)
{
	uint16	addr = AbsoluteIndexedIndirectSlow(JSR);
	libRR_log_function_call(Registers.PCw - 3, addr, 0x00);
	libRR_log_instruction(Registers.PCw - 3, "jsr %int%", 0x00, 3);
	PushW(Registers.PCw - 1);
	if (CheckEmulation())
		Registers.SH = 1;
	S9xSetPCBase(ICPU.ShiftedPB + addr);
}

// OP60 = RTS
static void Op60E1 (void)
{
	AddCycles(TWO_CYCLES);
	libRR_log_instruction(Registers.PCw - 1, "rts", 0x60, 1);
	PullWE(Registers.PCw);
	AddCycles(ONE_CYCLE);
	Registers.PCw++;
	S9xSetPCBase(Registers.PBPC);
}

static void Op60E0 (void)
{
	AddCycles(TWO_CYCLES);
	libRR_log_instruction(Registers.PCw - 1, "rts", 0x60, 1);
	PullW(Registers.PCw);
	AddCycles(ONE_CYCLE);
	Registers.PCw++;
	S9xSetPCBase(Registers.PBPC);
}

static void Op60Slow (void)
{
	AddCycles(TWO_CYCLES);
	libRR_log_instruction(Registers.PCw - 1, "rts", 0x60, 1);

	if (CheckEmulation())
	{
		PullWE(Registers.PCw);
	}
	else
	{
		PullW(Registers.PCw);
	}

	AddCycles(ONE_CYCLE);
	Registers.PCw++;
	S9xSetPCBase(Registers.PBPC);
}

/* MVN/MVP ***************************************************************** */

static void Op54X1 (void)
{
	uint32	SrcBank;
	libRR_log_instruction(Registers.PCw - 1, "mvn", 0x00, 1);

	Registers.DB = Immediate8(NONE);
	ICPU.ShiftedDB = Registers.DB << 16;
	OpenBus = SrcBank = Immediate8(NONE);

	S9xSetByte(OpenBus = S9xGetByte((SrcBank << 16) + Registers.X.W), ICPU.ShiftedDB + Registers.Y.W);

	Registers.XL++;
	Registers.YL++;
	Registers.A.W--;
	if (Registers.A.W != 0xffff)
		Registers.PCw -= 3;

	AddCycles(TWO_CYCLES);
}

static void Op54X0 (void)
{
	uint32	SrcBank;
	libRR_log_instruction(Registers.PCw - 1, "mvn", 0x00, 1);

	Registers.DB = Immediate8(NONE);
	ICPU.ShiftedDB = Registers.DB << 16;
	OpenBus = SrcBank = Immediate8(NONE);

	S9xSetByte(OpenBus = S9xGetByte((SrcBank << 16) + Registers.X.W), ICPU.ShiftedDB + Registers.Y.W);

	Registers.X.W++;
	Registers.Y.W++;
	Registers.A.W--;
	if (Registers.A.W != 0xffff)
		Registers.PCw -= 3;

	AddCycles(TWO_CYCLES);
}

static void Op54Slow (void)
{
	uint32	SrcBank;
	libRR_log_instruction(Registers.PCw - 1, "mvn", 0x00, 1);
	OpenBus = Registers.DB = Immediate8Slow(NONE);
	ICPU.ShiftedDB = Registers.DB << 16;
	OpenBus = SrcBank = Immediate8Slow(NONE);

	S9xSetByte(OpenBus = S9xGetByte((SrcBank << 16) + Registers.X.W), ICPU.ShiftedDB + Registers.Y.W);

	if (CheckIndex())
	{
		Registers.XL++;
		Registers.YL++;
	}
	else
	{
		Registers.X.W++;
		Registers.Y.W++;
	}

	Registers.A.W--;
	if (Registers.A.W != 0xffff)
		Registers.PCw -= 3;

	AddCycles(TWO_CYCLES);
}

static void Op44X1 (void)
{
	uint32	SrcBank;
	libRR_log_instruction(Registers.PCw - 1, "mvp", 0x00, 1);

	Registers.DB = Immediate8(NONE);
	ICPU.ShiftedDB = Registers.DB << 16;
	OpenBus = SrcBank = Immediate8(NONE);

	S9xSetByte(OpenBus = S9xGetByte((SrcBank << 16) + Registers.X.W), ICPU.ShiftedDB + Registers.Y.W);

	Registers.XL--;
	Registers.YL--;
	Registers.A.W--;
	if (Registers.A.W != 0xffff)
		Registers.PCw -= 3;

	AddCycles(TWO_CYCLES);
}

static void Op44X0 (void)
{
	uint32	SrcBank;
	libRR_log_instruction(Registers.PCw - 1, "mvp", 0x00, 1);

	Registers.DB = Immediate8(NONE);
	ICPU.ShiftedDB = Registers.DB << 16;
	OpenBus = SrcBank = Immediate8(NONE);

	S9xSetByte(OpenBus = S9xGetByte((SrcBank << 16) + Registers.X.W), ICPU.ShiftedDB + Registers.Y.W);

	Registers.X.W--;
	Registers.Y.W--;
	Registers.A.W--;
	if (Registers.A.W != 0xffff)
		Registers.PCw -= 3;

	AddCycles(TWO_CYCLES);
}

static void Op44Slow (void)
{
	uint32	SrcBank;
	libRR_log_instruction(Registers.PCw - 1, "mvp", 0x00, 1);

	OpenBus = Registers.DB = Immediate8Slow(NONE);
	ICPU.ShiftedDB = Registers.DB << 16;
	OpenBus = SrcBank = Immediate8Slow(NONE);

	S9xSetByte(OpenBus = S9xGetByte((SrcBank << 16) + Registers.X.W), ICPU.ShiftedDB + Registers.Y.W);

	if (CheckIndex())
	{
		Registers.XL--;
		Registers.YL--;
	}
	else
	{
		Registers.X.W--;
		Registers.Y.W--;
	}

	Registers.A.W--;
	if (Registers.A.W != 0xffff)
		Registers.PCw -= 3;

	AddCycles(TWO_CYCLES);
}

/* REP/SEP ***************************************************************** */

static void OpC2 (void)
{
	uint8 libRR_temp = Immediate8(READ);
	uint8	Work8 = ~libRR_temp;
	libRR_log_instruction_1int(Registers.PCw - 2, "rep #%int%", 0xc2, 2, libRR_temp);
	Registers.PL &= Work8;
	ICPU._Carry &= Work8;
	ICPU._Overflow &= (Work8 >> 6);
	ICPU._Negative &= Work8;
	ICPU._Zero |= ~Work8 & Zero;

	AddCycles(ONE_CYCLE);

	if (CheckEmulation())
	{
		SetFlags(MemoryFlag | IndexFlag);
	}

	if (CheckIndex())
	{
		Registers.XH = 0;
		Registers.YH = 0;
	}

	S9xFixCycles();
}

static void OpC2Slow (void)
{
	uint8 libRR_temp = Immediate8Slow(READ);
	uint8	Work8 = ~libRR_temp;
	libRR_log_instruction_1int(Registers.PCw - 2, "rep #%int%", 0xc2, 2, libRR_temp);
	Registers.PL &= Work8;
	ICPU._Carry &= Work8;
	ICPU._Overflow &= (Work8 >> 6);
	ICPU._Negative &= Work8;
	ICPU._Zero |= ~Work8 & Zero;

	AddCycles(ONE_CYCLE);

	if (CheckEmulation())
	{
		SetFlags(MemoryFlag | IndexFlag);
	}

	if (CheckIndex())
	{
		Registers.XH = 0;
		Registers.YH = 0;
	}

	S9xFixCycles();
}

static void OpE2 (void)
{
	uint8	Work8 = Immediate8(READ);
	libRR_log_instruction_1int(Registers.PCw - 2, "sep #%int%", 0xe2, 2, Work8);
	Registers.PL |= Work8;
	ICPU._Carry |= Work8 & 1;
	ICPU._Overflow |= (Work8 >> 6) & 1;
	ICPU._Negative |= Work8;
	if (Work8 & Zero)
		ICPU._Zero = 0;

	AddCycles(ONE_CYCLE);

	if (CheckEmulation())
	{
		SetFlags(MemoryFlag | IndexFlag);
	}

	if (CheckIndex())
	{
		Registers.XH = 0;
		Registers.YH = 0;
	}

	S9xFixCycles();
}

static void OpE2Slow (void)
{
	uint8	Work8 = Immediate8Slow(READ);
	libRR_log_instruction_1int(Registers.PCw - 2, "sep #%int%", 0xe2, 2, Work8);
	Registers.PL |= Work8;
	ICPU._Carry |= Work8 & 1;
	ICPU._Overflow |= (Work8 >> 6) & 1;
	ICPU._Negative |= Work8;
	if (Work8 & Zero)
		ICPU._Zero = 0;

	AddCycles(ONE_CYCLE);

	if (CheckEmulation())
	{
		SetFlags(MemoryFlag | IndexFlag);
	}

	if (CheckIndex())
	{
		Registers.XH = 0;
		Registers.YH = 0;
	}

	S9xFixCycles();
}

/* XBA ********************************************************************* */

static void OpEB (void)
{
	libRR_log_instruction(Registers.PCw - 1, "xba", 0xeb, 1);
	uint8	Work8 = Registers.AL;
	Registers.AL = Registers.AH;
	Registers.AH = Work8;
	SetZN8(Registers.AL);
	AddCycles(TWO_CYCLES);
}

/* RTI ********************************************************************* */

static void Op40Slow (void)
{
	AddCycles(TWO_CYCLES);
	libRR_log_instruction(Registers.PCw - 1, "rti", 0x40, 1);

	if (!CheckEmulation())
	{
		PullB(Registers.PL);
		S9xUnpackStatus();
		PullW(Registers.PCw);
		PullB(Registers.PB);
		OpenBus = Registers.PB;
		ICPU.ShiftedPB = Registers.PB << 16;
	}
	else
	{
		PullBE(Registers.PL);
		S9xUnpackStatus();
		PullWE(Registers.PCw);
		OpenBus = Registers.PCh;
		SetFlags(MemoryFlag | IndexFlag);
	}

	S9xSetPCBase(Registers.PBPC);

	if (CheckIndex())
	{
		Registers.XH = 0;
		Registers.YH = 0;
	}

	S9xFixCycles();
}

/* STP/WAI ***************************************************************** */

/* WAI*/
static void OpCB (void)
{
	/* Ok, let's just C-ify the ASM versions separately.*/
	libRR_log_instruction(Registers.PCw - 1, "wai", 0xcb, 1);
#ifdef SA1_OPCODES
	SA1.WaitingForInterrupt = TRUE;
	Registers.PCw--;
#else	/* SA1_OPCODES*/
	{
		CPU.WaitingForInterrupt = TRUE;
		Registers.PCw--;
		AddCycles(TWO_CYCLES);
	}
#endif	/* SA1_OPCODES*/
}

/* STP*/
static void OpDB (void)
{
	libRR_log_instruction(Registers.PCw - 1, "stp", 0xdb, 1);
	Registers.PCw--;
	CPU.Flags |= DEBUG_MODE_FLAG | HALTED_FLAG;
	AddCycles(ONE_CYCLE);
}

/* WDM (Reserved S9xOpcode) ************************************************ */


static void Op42 (void)
{
	libRR_log_instruction(Registers.PCw - 1, "wdm", 0x42, 1);
	S9xGetWord(Registers.PBPC, WRAP_NONE);
	Registers.PCw++;

}

/* CPU-S9xOpcodes Definitions ************************************************/

struct SOpcodes S9xOpcodesM1X1[256] =
{
	{ Op00 },        { Op01E0M1 },    { Op02 },        { Op03M1 },      { Op04M1 },
	{ Op05M1 },      { Op06M1 },      { Op07M1 },      { Op08E0 },      { Op09M1 },
	{ Op0AM1 },      { Op0BE0 },      { Op0CM1 },      { Op0DM1 },      { Op0EM1 },
	{ Op0FM1 },      { Op10E0 },      { Op11E0M1X1 },  { Op12E0M1 },    { Op13M1 },
	{ Op14M1 },      { Op15E0M1 },    { Op16E0M1 },    { Op17M1 },      { Op18 },
	{ Op19M1X1 },    { Op1AM1 },      { Op1B },        { Op1CM1 },      { Op1DM1X1 },
	{ Op1EM1X1 },    { Op1FM1 },      { Op20E0 },      { Op21E0M1 },    { Op22E0 },
	{ Op23M1 },      { Op24M1 },      { Op25M1 },      { Op26M1 },      { Op27M1 },
	{ Op28E0 },      { Op29M1 },      { Op2AM1 },      { Op2BE0 },      { Op2CM1 },
	{ Op2DM1 },      { Op2EM1 },      { Op2FM1 },      { Op30E0 },      { Op31E0M1X1 },
	{ Op32E0M1 },    { Op33M1 },      { Op34E0M1 },    { Op35E0M1 },    { Op36E0M1 },
	{ Op37M1 },      { Op38 },        { Op39M1X1 },    { Op3AM1 },      { Op3B },
	{ Op3CM1X1 },    { Op3DM1X1 },    { Op3EM1X1 },    { Op3FM1 },      { Op40Slow },
	{ Op41E0M1 },    { Op42 },        { Op43M1 },      { Op44X1 },      { Op45M1 },
	{ Op46M1 },      { Op47M1 },      { Op48E0M1 },    { Op49M1 },      { Op4AM1 },
	{ Op4BE0 },      { Op4C },        { Op4DM1 },      { Op4EM1 },      { Op4FM1 },
	{ Op50E0 },      { Op51E0M1X1 },  { Op52E0M1 },    { Op53M1 },      { Op54X1 },
	{ Op55E0M1 },    { Op56E0M1 },    { Op57M1 },      { Op58 },        { Op59M1X1 },
	{ Op5AE0X1 },    { Op5B },        { Op5C },        { Op5DM1X1 },    { Op5EM1X1 },
	{ Op5FM1 },      { Op60E0 },      { Op61E0M1 },    { Op62E0 },      { Op63M1 },
	{ Op64M1 },      { Op65M1 },      { Op66M1 },      { Op67M1 },      { Op68E0M1 },
	{ Op69M1 },      { Op6AM1 },      { Op6BE0 },      { Op6C },        { Op6DM1 },
	{ Op6EM1 },      { Op6FM1 },      { Op70E0 },      { Op71E0M1X1 },  { Op72E0M1 },
	{ Op73M1 },      { Op74E0M1 },    { Op75E0M1 },    { Op76E0M1 },    { Op77M1 },
	{ Op78 },        { Op79M1X1 },    { Op7AE0X1 },    { Op7B },        { Op7C },
	{ Op7DM1X1 },    { Op7EM1X1 },    { Op7FM1 },      { Op80E0 },      { Op81E0M1 },
	{ Op82 },        { Op83M1 },      { Op84X1 },      { Op85M1 },      { Op86X1 },
	{ Op87M1 },      { Op88X1 },      { Op89M1 },      { Op8AM1 },      { Op8BE0 },
	{ Op8CX1 },      { Op8DM1 },      { Op8EX1 },      { Op8FM1 },      { Op90E0 },
	{ Op91E0M1X1 },  { Op92E0M1 },    { Op93M1 },      { Op94E0X1 },    { Op95E0M1 },
	{ Op96E0X1 },    { Op97M1 },      { Op98M1 },      { Op99M1X1 },    { Op9A },
	{ Op9BX1 },      { Op9CM1 },      { Op9DM1X1 },    { Op9EM1X1 },    { Op9FM1 },
	{ OpA0X1 },      { OpA1E0M1 },    { OpA2X1 },      { OpA3M1 },      { OpA4X1 },
	{ OpA5M1 },      { OpA6X1 },      { OpA7M1 },      { OpA8X1 },      { OpA9M1 },
	{ OpAAX1 },      { OpABE0 },      { OpACX1 },      { OpADM1 },      { OpAEX1 },
	{ OpAFM1 },      { OpB0E0 },      { OpB1E0M1X1 },  { OpB2E0M1 },    { OpB3M1 },
	{ OpB4E0X1 },    { OpB5E0M1 },    { OpB6E0X1 },    { OpB7M1 },      { OpB8 },
	{ OpB9M1X1 },    { OpBAX1 },      { OpBBX1 },      { OpBCX1 },      { OpBDM1X1 },
	{ OpBEX1 },      { OpBFM1 },      { OpC0X1 },      { OpC1E0M1 },    { OpC2 },
	{ OpC3M1 },      { OpC4X1 },      { OpC5M1 },      { OpC6M1 },      { OpC7M1 },
	{ OpC8X1 },      { OpC9M1 },      { OpCAX1 },      { OpCB },        { OpCCX1 },
	{ OpCDM1 },      { OpCEM1 },      { OpCFM1 },      { OpD0E0 },      { OpD1E0M1X1 },
	{ OpD2E0M1 },    { OpD3M1 },      { OpD4E0 },      { OpD5E0M1 },    { OpD6E0M1 },
	{ OpD7M1 },      { OpD8 },        { OpD9M1X1 },    { OpDAE0X1 },    { OpDB },
	{ OpDC },        { OpDDM1X1 },    { OpDEM1X1 },    { OpDFM1 },      { OpE0X1 },
	{ OpE1E0M1 },    { OpE2 },        { OpE3M1 },      { OpE4X1 },      { OpE5M1 },
	{ OpE6M1 },      { OpE7M1 },      { OpE8X1 },      { OpE9M1 },      { OpEA },
	{ OpEB },        { OpECX1 },      { OpEDM1 },      { OpEEM1 },      { OpEFM1 },
	{ OpF0E0 },      { OpF1E0M1X1 },  { OpF2E0M1 },    { OpF3M1 },      { OpF4E0 },
	{ OpF5E0M1 },    { OpF6E0M1 },    { OpF7M1 },      { OpF8 },        { OpF9M1X1 },
	{ OpFAE0X1 },    { OpFB },        { OpFCE0 },      { OpFDM1X1 },    { OpFEM1X1 },
	{ OpFFM1 }
};

struct SOpcodes S9xOpcodesE1[256] =
{
	{ Op00 },        { Op01E1 },      { Op02 },        { Op03M1 },      { Op04M1 },
	{ Op05M1 },      { Op06M1 },      { Op07M1 },      { Op08E1 },      { Op09M1 },
	{ Op0AM1 },      { Op0BE1 },      { Op0CM1 },      { Op0DM1 },      { Op0EM1 },
	{ Op0FM1 },      { Op10E1 },      { Op11E1 },      { Op12E1 },      { Op13M1 },
	{ Op14M1 },      { Op15E1 },      { Op16E1 },      { Op17M1 },      { Op18 },
	{ Op19M1X1 },    { Op1AM1 },      { Op1B },        { Op1CM1 },      { Op1DM1X1 },
	{ Op1EM1X1 },    { Op1FM1 },      { Op20E1 },      { Op21E1 },      { Op22E1 },
	{ Op23M1 },      { Op24M1 },      { Op25M1 },      { Op26M1 },      { Op27M1 },
	{ Op28E1 },      { Op29M1 },      { Op2AM1 },      { Op2BE1 },      { Op2CM1 },
	{ Op2DM1 },      { Op2EM1 },      { Op2FM1 },      { Op30E1 },      { Op31E1 },
	{ Op32E1 },      { Op33M1 },      { Op34E1 },      { Op35E1 },      { Op36E1 },
	{ Op37M1 },      { Op38 },        { Op39M1X1 },    { Op3AM1 },      { Op3B },
	{ Op3CM1X1 },    { Op3DM1X1 },    { Op3EM1X1 },    { Op3FM1 },      { Op40Slow },
	{ Op41E1 },      { Op42 },        { Op43M1 },      { Op44X1 },      { Op45M1 },
	{ Op46M1 },      { Op47M1 },      { Op48E1 },      { Op49M1 },      { Op4AM1 },
	{ Op4BE1 },      { Op4C },        { Op4DM1 },      { Op4EM1 },      { Op4FM1 },
	{ Op50E1 },      { Op51E1 },      { Op52E1 },      { Op53M1 },      { Op54X1 },
	{ Op55E1 },      { Op56E1 },      { Op57M1 },      { Op58 },        { Op59M1X1 },
	{ Op5AE1 },      { Op5B },        { Op5C },        { Op5DM1X1 },    { Op5EM1X1 },
	{ Op5FM1 },      { Op60E1 },      { Op61E1 },      { Op62E1 },      { Op63M1 },
	{ Op64M1 },      { Op65M1 },      { Op66M1 },      { Op67M1 },      { Op68E1 },
	{ Op69M1 },      { Op6AM1 },      { Op6BE1 },      { Op6C },        { Op6DM1 },
	{ Op6EM1 },      { Op6FM1 },      { Op70E1 },      { Op71E1 },      { Op72E1 },
	{ Op73M1 },      { Op74E1 },      { Op75E1 },      { Op76E1 },      { Op77M1 },
	{ Op78 },        { Op79M1X1 },    { Op7AE1 },      { Op7B },        { Op7C },
	{ Op7DM1X1 },    { Op7EM1X1 },    { Op7FM1 },      { Op80E1 },      { Op81E1 },
	{ Op82 },        { Op83M1 },      { Op84X1 },      { Op85M1 },      { Op86X1 },
	{ Op87M1 },      { Op88X1 },      { Op89M1 },      { Op8AM1 },      { Op8BE1 },
	{ Op8CX1 },      { Op8DM1 },      { Op8EX1 },      { Op8FM1 },      { Op90E1 },
	{ Op91E1 },      { Op92E1 },      { Op93M1 },      { Op94E1 },      { Op95E1 },
	{ Op96E1 },      { Op97M1 },      { Op98M1 },      { Op99M1X1 },    { Op9A },
	{ Op9BX1 },      { Op9CM1 },      { Op9DM1X1 },    { Op9EM1X1 },    { Op9FM1 },
	{ OpA0X1 },      { OpA1E1 },      { OpA2X1 },      { OpA3M1 },      { OpA4X1 },
	{ OpA5M1 },      { OpA6X1 },      { OpA7M1 },      { OpA8X1 },      { OpA9M1 },
	{ OpAAX1 },      { OpABE1 },      { OpACX1 },      { OpADM1 },      { OpAEX1 },
	{ OpAFM1 },      { OpB0E1 },      { OpB1E1 },      { OpB2E1 },      { OpB3M1 },
	{ OpB4E1 },      { OpB5E1 },      { OpB6E1 },      { OpB7M1 },      { OpB8 },
	{ OpB9M1X1 },    { OpBAX1 },      { OpBBX1 },      { OpBCX1 },      { OpBDM1X1 },
	{ OpBEX1 },      { OpBFM1 },      { OpC0X1 },      { OpC1E1 },      { OpC2 },
	{ OpC3M1 },      { OpC4X1 },      { OpC5M1 },      { OpC6M1 },      { OpC7M1 },
	{ OpC8X1 },      { OpC9M1 },      { OpCAX1 },      { OpCB },        { OpCCX1 },
	{ OpCDM1 },      { OpCEM1 },      { OpCFM1 },      { OpD0E1 },      { OpD1E1 },
	{ OpD2E1 },      { OpD3M1 },      { OpD4E1 },      { OpD5E1 },      { OpD6E1 },
	{ OpD7M1 },      { OpD8 },        { OpD9M1X1 },    { OpDAE1 },      { OpDB },
	{ OpDC },        { OpDDM1X1 },    { OpDEM1X1 },    { OpDFM1 },      { OpE0X1 },
	{ OpE1E1 },      { OpE2 },        { OpE3M1 },      { OpE4X1 },      { OpE5M1 },
	{ OpE6M1 },      { OpE7M1 },      { OpE8X1 },      { OpE9M1 },      { OpEA },
	{ OpEB },        { OpECX1 },      { OpEDM1 },      { OpEEM1 },      { OpEFM1 },
	{ OpF0E1 },      { OpF1E1 },      { OpF2E1 },      { OpF3M1 },      { OpF4E1 },
	{ OpF5E1 },      { OpF6E1 },      { OpF7M1 },      { OpF8 },        { OpF9M1X1 },
	{ OpFAE1 },      { OpFB },        { OpFCE1 },      { OpFDM1X1 },    { OpFEM1X1 },
	{ OpFFM1 }
};

struct SOpcodes S9xOpcodesM1X0[256] =
{
	{ Op00 },        { Op01E0M1 },    { Op02 },        { Op03M1 },      { Op04M1 },
	{ Op05M1 },      { Op06M1 },      { Op07M1 },      { Op08E0 },      { Op09M1 },
	{ Op0AM1 },      { Op0BE0 },      { Op0CM1 },      { Op0DM1 },      { Op0EM1 },
	{ Op0FM1 },      { Op10E0 },      { Op11E0M1X0 },  { Op12E0M1 },    { Op13M1 },
	{ Op14M1 },      { Op15E0M1 },    { Op16E0M1 },    { Op17M1 },      { Op18 },
	{ Op19M1X0 },    { Op1AM1 },      { Op1B },        { Op1CM1 },      { Op1DM1X0 },
	{ Op1EM1X0 },    { Op1FM1 },      { Op20E0 },      { Op21E0M1 },    { Op22E0 },
	{ Op23M1 },      { Op24M1 },      { Op25M1 },      { Op26M1 },      { Op27M1 },
	{ Op28E0 },      { Op29M1 },      { Op2AM1 },      { Op2BE0 },      { Op2CM1 },
	{ Op2DM1 },      { Op2EM1 },      { Op2FM1 },      { Op30E0 },      { Op31E0M1X0 },
	{ Op32E0M1 },    { Op33M1 },      { Op34E0M1 },    { Op35E0M1 },    { Op36E0M1 },
	{ Op37M1 },      { Op38 },        { Op39M1X0 },    { Op3AM1 },      { Op3B },
	{ Op3CM1X0 },    { Op3DM1X0 },    { Op3EM1X0 },    { Op3FM1 },      { Op40Slow },
	{ Op41E0M1 },    { Op42 },        { Op43M1 },      { Op44X0 },      { Op45M1 },
	{ Op46M1 },      { Op47M1 },      { Op48E0M1 },    { Op49M1 },      { Op4AM1 },
	{ Op4BE0 },      { Op4C },        { Op4DM1 },      { Op4EM1 },      { Op4FM1 },
	{ Op50E0 },      { Op51E0M1X0 },  { Op52E0M1 },    { Op53M1 },      { Op54X0 },
	{ Op55E0M1 },    { Op56E0M1 },    { Op57M1 },      { Op58 },        { Op59M1X0 },
	{ Op5AE0X0 },    { Op5B },        { Op5C },        { Op5DM1X0 },    { Op5EM1X0 },
	{ Op5FM1 },      { Op60E0 },      { Op61E0M1 },    { Op62E0 },      { Op63M1 },
	{ Op64M1 },      { Op65M1 },      { Op66M1 },      { Op67M1 },      { Op68E0M1 },
	{ Op69M1 },      { Op6AM1 },      { Op6BE0 },      { Op6C },        { Op6DM1 },
	{ Op6EM1 },      { Op6FM1 },      { Op70E0 },      { Op71E0M1X0 },  { Op72E0M1 },
	{ Op73M1 },      { Op74E0M1 },    { Op75E0M1 },    { Op76E0M1 },    { Op77M1 },
	{ Op78 },        { Op79M1X0 },    { Op7AE0X0 },    { Op7B },        { Op7C },
	{ Op7DM1X0 },    { Op7EM1X0 },    { Op7FM1 },      { Op80E0 },      { Op81E0M1 },
	{ Op82 },        { Op83M1 },      { Op84X0 },      { Op85M1 },      { Op86X0 },
	{ Op87M1 },      { Op88X0 },      { Op89M1 },      { Op8AM1 },      { Op8BE0 },
	{ Op8CX0 },      { Op8DM1 },      { Op8EX0 },      { Op8FM1 },      { Op90E0 },
	{ Op91E0M1X0 },  { Op92E0M1 },    { Op93M1 },      { Op94E0X0 },    { Op95E0M1 },
	{ Op96E0X0 },    { Op97M1 },      { Op98M1 },      { Op99M1X0 },    { Op9A },
	{ Op9BX0 },      { Op9CM1 },      { Op9DM1X0 },    { Op9EM1X0 },    { Op9FM1 },
	{ OpA0X0 },      { OpA1E0M1 },    { OpA2X0 },      { OpA3M1 },      { OpA4X0 },
	{ OpA5M1 },      { OpA6X0 },      { OpA7M1 },      { OpA8X0 },      { OpA9M1 },
	{ OpAAX0 },      { OpABE0 },      { OpACX0 },      { OpADM1 },      { OpAEX0 },
	{ OpAFM1 },      { OpB0E0 },      { OpB1E0M1X0 },  { OpB2E0M1 },    { OpB3M1 },
	{ OpB4E0X0 },    { OpB5E0M1 },    { OpB6E0X0 },    { OpB7M1 },      { OpB8 },
	{ OpB9M1X0 },    { OpBAX0 },      { OpBBX0 },      { OpBCX0 },      { OpBDM1X0 },
	{ OpBEX0 },      { OpBFM1 },      { OpC0X0 },      { OpC1E0M1 },    { OpC2 },
	{ OpC3M1 },      { OpC4X0 },      { OpC5M1 },      { OpC6M1 },      { OpC7M1 },
	{ OpC8X0 },      { OpC9M1 },      { OpCAX0 },      { OpCB },        { OpCCX0 },
	{ OpCDM1 },      { OpCEM1 },      { OpCFM1 },      { OpD0E0 },      { OpD1E0M1X0 },
	{ OpD2E0M1 },    { OpD3M1 },      { OpD4E0 },      { OpD5E0M1 },    { OpD6E0M1 },
	{ OpD7M1 },      { OpD8 },        { OpD9M1X0 },    { OpDAE0X0 },    { OpDB },
	{ OpDC },        { OpDDM1X0 },    { OpDEM1X0 },    { OpDFM1 },      { OpE0X0 },
	{ OpE1E0M1 },    { OpE2 },        { OpE3M1 },      { OpE4X0 },      { OpE5M1 },
	{ OpE6M1 },      { OpE7M1 },      { OpE8X0 },      { OpE9M1 },      { OpEA },
	{ OpEB },        { OpECX0 },      { OpEDM1 },      { OpEEM1 },      { OpEFM1 },
	{ OpF0E0 },      { OpF1E0M1X0 },  { OpF2E0M1 },    { OpF3M1 },      { OpF4E0 },
	{ OpF5E0M1 },    { OpF6E0M1 },    { OpF7M1 },      { OpF8 },        { OpF9M1X0 },
	{ OpFAE0X0 },    { OpFB },        { OpFCE0 },      { OpFDM1X0 },    { OpFEM1X0 },
	{ OpFFM1 }
};

struct SOpcodes S9xOpcodesM0X0[256] =
{
	{ Op00 },        { Op01E0M0 },    { Op02 },        { Op03M0 },      { Op04M0 },
	{ Op05M0 },      { Op06M0 },      { Op07M0 },      { Op08E0 },      { Op09M0 },
	{ Op0AM0 },      { Op0BE0 },      { Op0CM0 },      { Op0DM0 },      { Op0EM0 },
	{ Op0FM0 },      { Op10E0 },      { Op11E0M0X0 },  { Op12E0M0 },    { Op13M0 },
	{ Op14M0 },      { Op15E0M0 },    { Op16E0M0 },    { Op17M0 },      { Op18 },
	{ Op19M0X0 },    { Op1AM0 },      { Op1B },        { Op1CM0 },      { Op1DM0X0 },
	{ Op1EM0X0 },    { Op1FM0 },      { Op20E0 },      { Op21E0M0 },    { Op22E0 },
	{ Op23M0 },      { Op24M0 },      { Op25M0 },      { Op26M0 },      { Op27M0 },
	{ Op28E0 },      { Op29M0 },      { Op2AM0 },      { Op2BE0 },      { Op2CM0 },
	{ Op2DM0 },      { Op2EM0 },      { Op2FM0 },      { Op30E0 },      { Op31E0M0X0 },
	{ Op32E0M0 },    { Op33M0 },      { Op34E0M0 },    { Op35E0M0 },    { Op36E0M0 },
	{ Op37M0 },      { Op38 },        { Op39M0X0 },    { Op3AM0 },      { Op3B },
	{ Op3CM0X0 },    { Op3DM0X0 },    { Op3EM0X0 },    { Op3FM0 },      { Op40Slow },
	{ Op41E0M0 },    { Op42 },        { Op43M0 },      { Op44X0 },      { Op45M0 },
	{ Op46M0 },      { Op47M0 },      { Op48E0M0 },    { Op49M0 },      { Op4AM0 },
	{ Op4BE0 },      { Op4C },        { Op4DM0 },      { Op4EM0 },      { Op4FM0 },
	{ Op50E0 },      { Op51E0M0X0 },  { Op52E0M0 },    { Op53M0 },      { Op54X0 },
	{ Op55E0M0 },    { Op56E0M0 },    { Op57M0 },      { Op58 },        { Op59M0X0 },
	{ Op5AE0X0 },    { Op5B },        { Op5C },        { Op5DM0X0 },    { Op5EM0X0 },
	{ Op5FM0 },      { Op60E0 },      { Op61E0M0 },    { Op62E0 },      { Op63M0 },
	{ Op64M0 },      { Op65M0 },      { Op66M0 },      { Op67M0 },      { Op68E0M0 },
	{ Op69M0 },      { Op6AM0 },      { Op6BE0 },      { Op6C },        { Op6DM0 },
	{ Op6EM0 },      { Op6FM0 },      { Op70E0 },      { Op71E0M0X0 },  { Op72E0M0 },
	{ Op73M0 },      { Op74E0M0 },    { Op75E0M0 },    { Op76E0M0 },    { Op77M0 },
	{ Op78 },        { Op79M0X0 },    { Op7AE0X0 },    { Op7B },        { Op7C },
	{ Op7DM0X0 },    { Op7EM0X0 },    { Op7FM0 },      { Op80E0 },      { Op81E0M0 },
	{ Op82 },        { Op83M0 },      { Op84X0 },      { Op85M0 },      { Op86X0 },
	{ Op87M0 },      { Op88X0 },      { Op89M0 },      { Op8AM0 },      { Op8BE0 },
	{ Op8CX0 },      { Op8DM0 },      { Op8EX0 },      { Op8FM0 },      { Op90E0 },
	{ Op91E0M0X0 },  { Op92E0M0 },    { Op93M0 },      { Op94E0X0 },    { Op95E0M0 },
	{ Op96E0X0 },    { Op97M0 },      { Op98M0 },      { Op99M0X0 },    { Op9A },
	{ Op9BX0 },      { Op9CM0 },      { Op9DM0X0 },    { Op9EM0X0 },    { Op9FM0 },
	{ OpA0X0 },      { OpA1E0M0 },    { OpA2X0 },      { OpA3M0 },      { OpA4X0 },
	{ OpA5M0 },      { OpA6X0 },      { OpA7M0 },      { OpA8X0 },      { OpA9M0 },
	{ OpAAX0 },      { OpABE0 },      { OpACX0 },      { OpADM0 },      { OpAEX0 },
	{ OpAFM0 },      { OpB0E0 },      { OpB1E0M0X0 },  { OpB2E0M0 },    { OpB3M0 },
	{ OpB4E0X0 },    { OpB5E0M0 },    { OpB6E0X0 },    { OpB7M0 },      { OpB8 },
	{ OpB9M0X0 },    { OpBAX0 },      { OpBBX0 },      { OpBCX0 },      { OpBDM0X0 },
	{ OpBEX0 },      { OpBFM0 },      { OpC0X0 },      { OpC1E0M0 },    { OpC2 },
	{ OpC3M0 },      { OpC4X0 },      { OpC5M0 },      { OpC6M0 },      { OpC7M0 },
	{ OpC8X0 },      { OpC9M0 },      { OpCAX0 },      { OpCB },        { OpCCX0 },
	{ OpCDM0 },      { OpCEM0 },      { OpCFM0 },      { OpD0E0 },      { OpD1E0M0X0 },
	{ OpD2E0M0 },    { OpD3M0 },      { OpD4E0 },      { OpD5E0M0 },    { OpD6E0M0 },
	{ OpD7M0 },      { OpD8 },        { OpD9M0X0 },    { OpDAE0X0 },    { OpDB },
	{ OpDC },        { OpDDM0X0 },    { OpDEM0X0 },    { OpDFM0 },      { OpE0X0 },
	{ OpE1E0M0 },    { OpE2 },        { OpE3M0 },      { OpE4X0 },      { OpE5M0 },
	{ OpE6M0 },      { OpE7M0 },      { OpE8X0 },      { OpE9M0 },      { OpEA },
	{ OpEB },        { OpECX0 },      { OpEDM0 },      { OpEEM0 },      { OpEFM0 },
	{ OpF0E0 },      { OpF1E0M0X0 },  { OpF2E0M0 },    { OpF3M0 },      { OpF4E0 },
	{ OpF5E0M0 },    { OpF6E0M0 },    { OpF7M0 },      { OpF8 },        { OpF9M0X0 },
	{ OpFAE0X0 },    { OpFB },        { OpFCE0 },      { OpFDM0X0 },    { OpFEM0X0 },
	{ OpFFM0 }
};

struct SOpcodes S9xOpcodesM0X1[256] =
{
	{ Op00 },        { Op01E0M0 },    { Op02 },        { Op03M0 },      { Op04M0 },
	{ Op05M0 },      { Op06M0 },      { Op07M0 },      { Op08E0 },      { Op09M0 },
	{ Op0AM0 },      { Op0BE0 },      { Op0CM0 },      { Op0DM0 },      { Op0EM0 },
	{ Op0FM0 },      { Op10E0 },      { Op11E0M0X1 },  { Op12E0M0 },    { Op13M0 },
	{ Op14M0 },      { Op15E0M0 },    { Op16E0M0 },    { Op17M0 },      { Op18 },
	{ Op19M0X1 },    { Op1AM0 },      { Op1B },        { Op1CM0 },      { Op1DM0X1 },
	{ Op1EM0X1 },    { Op1FM0 },      { Op20E0 },      { Op21E0M0 },    { Op22E0 },
	{ Op23M0 },      { Op24M0 },      { Op25M0 },      { Op26M0 },      { Op27M0 },
	{ Op28E0 },      { Op29M0 },      { Op2AM0 },      { Op2BE0 },      { Op2CM0 },
	{ Op2DM0 },      { Op2EM0 },      { Op2FM0 },      { Op30E0 },      { Op31E0M0X1 },
	{ Op32E0M0 },    { Op33M0 },      { Op34E0M0 },    { Op35E0M0 },    { Op36E0M0 },
	{ Op37M0 },      { Op38 },        { Op39M0X1 },    { Op3AM0 },      { Op3B },
	{ Op3CM0X1 },    { Op3DM0X1 },    { Op3EM0X1 },    { Op3FM0 },      { Op40Slow },
	{ Op41E0M0 },    { Op42 },        { Op43M0 },      { Op44X1 },      { Op45M0 },
	{ Op46M0 },      { Op47M0 },      { Op48E0M0 },    { Op49M0 },      { Op4AM0 },
	{ Op4BE0 },      { Op4C },        { Op4DM0 },      { Op4EM0 },      { Op4FM0 },
	{ Op50E0 },      { Op51E0M0X1 },  { Op52E0M0 },    { Op53M0 },      { Op54X1 },
	{ Op55E0M0 },    { Op56E0M0 },    { Op57M0 },      { Op58 },        { Op59M0X1 },
	{ Op5AE0X1 },    { Op5B },        { Op5C },        { Op5DM0X1 },    { Op5EM0X1 },
	{ Op5FM0 },      { Op60E0 },      { Op61E0M0 },    { Op62E0 },      { Op63M0 },
	{ Op64M0 },      { Op65M0 },      { Op66M0 },      { Op67M0 },      { Op68E0M0 },
	{ Op69M0 },      { Op6AM0 },      { Op6BE0 },      { Op6C },        { Op6DM0 },
	{ Op6EM0 },      { Op6FM0 },      { Op70E0 },      { Op71E0M0X1 },  { Op72E0M0 },
	{ Op73M0 },      { Op74E0M0 },    { Op75E0M0 },    { Op76E0M0 },    { Op77M0 },
	{ Op78 },        { Op79M0X1 },    { Op7AE0X1 },    { Op7B },        { Op7C },
	{ Op7DM0X1 },    { Op7EM0X1 },    { Op7FM0 },      { Op80E0 },      { Op81E0M0 },
	{ Op82 },        { Op83M0 },      { Op84X1 },      { Op85M0 },      { Op86X1 },
	{ Op87M0 },      { Op88X1 },      { Op89M0 },      { Op8AM0 },      { Op8BE0 },
	{ Op8CX1 },      { Op8DM0 },      { Op8EX1 },      { Op8FM0 },      { Op90E0 },
	{ Op91E0M0X1 },  { Op92E0M0 },    { Op93M0 },      { Op94E0X1 },    { Op95E0M0 },
	{ Op96E0X1 },    { Op97M0 },      { Op98M0 },      { Op99M0X1 },    { Op9A },
	{ Op9BX1 },      { Op9CM0 },      { Op9DM0X1 },    { Op9EM0X1 },    { Op9FM0 },
	{ OpA0X1 },      { OpA1E0M0 },    { OpA2X1 },      { OpA3M0 },      { OpA4X1 },
	{ OpA5M0 },      { OpA6X1 },      { OpA7M0 },      { OpA8X1 },      { OpA9M0 },
	{ OpAAX1 },      { OpABE0 },      { OpACX1 },      { OpADM0 },      { OpAEX1 },
	{ OpAFM0 },      { OpB0E0 },      { OpB1E0M0X1 },  { OpB2E0M0 },    { OpB3M0 },
	{ OpB4E0X1 },    { OpB5E0M0 },    { OpB6E0X1 },    { OpB7M0 },      { OpB8 },
	{ OpB9M0X1 },    { OpBAX1 },      { OpBBX1 },      { OpBCX1 },      { OpBDM0X1 },
	{ OpBEX1 },      { OpBFM0 },      { OpC0X1 },      { OpC1E0M0 },    { OpC2 },
	{ OpC3M0 },      { OpC4X1 },      { OpC5M0 },      { OpC6M0 },      { OpC7M0 },
	{ OpC8X1 },      { OpC9M0 },      { OpCAX1 },      { OpCB },        { OpCCX1 },
	{ OpCDM0 },      { OpCEM0 },      { OpCFM0 },      { OpD0E0 },      { OpD1E0M0X1 },
	{ OpD2E0M0 },    { OpD3M0 },      { OpD4E0 },      { OpD5E0M0 },    { OpD6E0M0 },
	{ OpD7M0 },      { OpD8 },        { OpD9M0X1 },    { OpDAE0X1 },    { OpDB },
	{ OpDC },        { OpDDM0X1 },    { OpDEM0X1 },    { OpDFM0 },      { OpE0X1 },
	{ OpE1E0M0 },    { OpE2 },        { OpE3M0 },      { OpE4X1 },      { OpE5M0 },
	{ OpE6M0 },      { OpE7M0 },      { OpE8X1 },      { OpE9M0 },      { OpEA },
	{ OpEB },        { OpECX1 },      { OpEDM0 },      { OpEEM0 },      { OpEFM0 },
	{ OpF0E0 },      { OpF1E0M0X1 },  { OpF2E0M0 },    { OpF3M0 },      { OpF4E0 },
	{ OpF5E0M0 },    { OpF6E0M0 },    { OpF7M0 },      { OpF8 },        { OpF9M0X1 },
	{ OpFAE0X1 },    { OpFB },        { OpFCE0 },      { OpFDM0X1 },    { OpFEM0X1 },
	{ OpFFM0 }
};

struct SOpcodes S9xOpcodesSlow[256] =
{
	{ Op00 },        { Op01Slow },    { Op02 },        { Op03Slow },    { Op04Slow },
	{ Op05Slow },    { Op06Slow },    { Op07Slow },    { Op08Slow },    { Op09Slow },
	{ Op0ASlow },    { Op0BSlow },    { Op0CSlow },    { Op0DSlow },    { Op0ESlow },
	{ Op0FSlow },    { Op10Slow },    { Op11Slow },    { Op12Slow },    { Op13Slow },
	{ Op14Slow },    { Op15Slow },    { Op16Slow },    { Op17Slow },    { Op18 },
	{ Op19Slow },    { Op1ASlow },    { Op1B },        { Op1CSlow },    { Op1DSlow },
	{ Op1ESlow },    { Op1FSlow },    { Op20Slow },    { Op21Slow },    { Op22Slow },
	{ Op23Slow },    { Op24Slow },    { Op25Slow },    { Op26Slow },    { Op27Slow },
	{ Op28Slow },    { Op29Slow },    { Op2ASlow },    { Op2BSlow },    { Op2CSlow },
	{ Op2DSlow },    { Op2ESlow },    { Op2FSlow },    { Op30Slow },    { Op31Slow },
	{ Op32Slow },    { Op33Slow },    { Op34Slow },    { Op35Slow },    { Op36Slow },
	{ Op37Slow },    { Op38 },        { Op39Slow },    { Op3ASlow },    { Op3B },
	{ Op3CSlow },    { Op3DSlow },    { Op3ESlow },    { Op3FSlow },    { Op40Slow },
	{ Op41Slow },    { Op42 },        { Op43Slow },    { Op44Slow },    { Op45Slow },
	{ Op46Slow },    { Op47Slow },    { Op48Slow },    { Op49Slow },    { Op4ASlow },
	{ Op4BSlow },    { Op4CSlow },    { Op4DSlow },    { Op4ESlow },    { Op4FSlow },
	{ Op50Slow },    { Op51Slow },    { Op52Slow },    { Op53Slow },    { Op54Slow },
	{ Op55Slow },    { Op56Slow },    { Op57Slow },    { Op58 },        { Op59Slow },
	{ Op5ASlow },    { Op5B },        { Op5CSlow },    { Op5DSlow },    { Op5ESlow },
	{ Op5FSlow },    { Op60Slow },    { Op61Slow },    { Op62Slow },    { Op63Slow },
	{ Op64Slow },    { Op65Slow },    { Op66Slow },    { Op67Slow },    { Op68Slow },
	{ Op69Slow },    { Op6ASlow },    { Op6BSlow },    { Op6CSlow },    { Op6DSlow },
	{ Op6ESlow },    { Op6FSlow },    { Op70Slow },    { Op71Slow },    { Op72Slow },
	{ Op73Slow },    { Op74Slow },    { Op75Slow },    { Op76Slow },    { Op77Slow },
	{ Op78 },        { Op79Slow },    { Op7ASlow },    { Op7B },        { Op7CSlow },
	{ Op7DSlow },    { Op7ESlow },    { Op7FSlow },    { Op80Slow },    { Op81Slow },
	{ Op82Slow },    { Op83Slow },    { Op84Slow },    { Op85Slow },    { Op86Slow },
	{ Op87Slow },    { Op88Slow },    { Op89Slow },    { Op8ASlow },    { Op8BSlow },
	{ Op8CSlow },    { Op8DSlow },    { Op8ESlow },    { Op8FSlow },    { Op90Slow },
	{ Op91Slow },    { Op92Slow },    { Op93Slow },    { Op94Slow },    { Op95Slow },
	{ Op96Slow },    { Op97Slow },    { Op98Slow },    { Op99Slow },    { Op9A },
	{ Op9BSlow },    { Op9CSlow },    { Op9DSlow },    { Op9ESlow },    { Op9FSlow },
	{ OpA0Slow },    { OpA1Slow },    { OpA2Slow },    { OpA3Slow },    { OpA4Slow },
	{ OpA5Slow },    { OpA6Slow },    { OpA7Slow },    { OpA8Slow },    { OpA9Slow },
	{ OpAASlow },    { OpABSlow },    { OpACSlow },    { OpADSlow },    { OpAESlow },
	{ OpAFSlow },    { OpB0Slow },    { OpB1Slow },    { OpB2Slow },    { OpB3Slow },
	{ OpB4Slow },    { OpB5Slow },    { OpB6Slow },    { OpB7Slow },    { OpB8 },
	{ OpB9Slow },    { OpBASlow },    { OpBBSlow },    { OpBCSlow },    { OpBDSlow },
	{ OpBESlow },    { OpBFSlow },    { OpC0Slow },    { OpC1Slow },    { OpC2Slow },
	{ OpC3Slow },    { OpC4Slow },    { OpC5Slow },    { OpC6Slow },    { OpC7Slow },
	{ OpC8Slow },    { OpC9Slow },    { OpCASlow },    { OpCB },        { OpCCSlow },
	{ OpCDSlow },    { OpCESlow },    { OpCFSlow },    { OpD0Slow },    { OpD1Slow },
	{ OpD2Slow },    { OpD3Slow },    { OpD4Slow },    { OpD5Slow },    { OpD6Slow },
	{ OpD7Slow },    { OpD8 },        { OpD9Slow },    { OpDASlow },    { OpDB },
	{ OpDCSlow },    { OpDDSlow },    { OpDESlow },    { OpDFSlow },    { OpE0Slow },
	{ OpE1Slow },    { OpE2Slow },    { OpE3Slow },    { OpE4Slow },    { OpE5Slow },
	{ OpE6Slow },    { OpE7Slow },    { OpE8Slow },    { OpE9Slow },    { OpEA },
	{ OpEB },        { OpECSlow },    { OpEDSlow },    { OpEESlow },    { OpEFSlow },
	{ OpF0Slow },    { OpF1Slow },    { OpF2Slow },    { OpF3Slow },    { OpF4Slow },
	{ OpF5Slow },    { OpF6Slow },    { OpF7Slow },    { OpF8 },        { OpF9Slow },
	{ OpFASlow },    { OpFB },        { OpFCSlow },    { OpFDSlow },    { OpFESlow },
	{ OpFFSlow }
};
