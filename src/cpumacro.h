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


#ifndef _CPUMACRO_H_
#define _CPUMACRO_H_

#define libRR_AbsoluteLong() READ_3WORD(CPU.PCBase + Registers.PCw)
#define libRR_AbsoluteLongIndexedX() READ_3WORD(CPU.PCBase + Registers.PCw)
#define libRR_AbsoluteIndexedIndirect() S9xGetWord(Registers.PBPC, WRAP_BANK)
#define libRR_AbsoluteIndexedYX0() READ_WORD(CPU.PCBase + Registers.PCw)
#define libRR_AbsoluteIndexedYX1() READ_WORD(CPU.PCBase + Registers.PCw)
#define libRR_StackRelative() CPU.PCBase[Registers.PCw]
#define libRR_StackRelativeIndirectIndexed() S9xGetByte(Registers.PBPC)
#define libRR_Direct() CPU.PCBase[Registers.PCw]
#define libRR_DirectSlow() CPU.PCBase[Registers.PCw]
#define libRR_DirectIndirectLong() CPU.PCBase[Registers.PCw]
#define libRR_DirectIndirectIndexedLong() CPU.PCBase[Registers.PCw]
#define libRR_DirectIndirectIndexedE0X0() CPU.PCBase[Registers.PCw]
#define libRR_DirectIndirectIndexedE0X1() CPU.PCBase[Registers.PCw]
#define libRR_DirectIndirectIndexedE1() CPU.PCBase[Registers.PCw]
#define libRR_DirectIndexedIndirectE0() CPU.PCBase[Registers.PCw]
#define libRR_DirectIndexedIndirectE1() CPU.PCBase[Registers.PCw]
#define libRR_DirectIndirectE0() CPU.PCBase[Registers.PCw]
#define libRR_DirectIndirectE1() CPU.PCBase[Registers.PCw]
#define libRR_DirectIndexedXE0() CPU.PCBase[Registers.PCw]
#define libRR_DirectIndexedYE0() CPU.PCBase[Registers.PCw]
#define libRR_DirectIndexedYE1() CPU.PCBase[Registers.PCw]
#define libRR_DirectIndexedXE1() CPU.PCBase[Registers.PCw]
#define libRR_DirectIndexedYSlow() CPU.PCBase[Registers.PCw]
#define libRR_Absolute() READ_WORD(CPU.PCBase + Registers.PCw)
#define libRR_AbsoluteSlow() READ_WORD(CPU.PCBase + Registers.PCw)
#define libRR_AbsoluteIndexedXX1() READ_WORD(CPU.PCBase + Registers.PCw)
#define libRR_AbsoluteIndexedXSlow() READ_WORD(CPU.PCBase + Registers.PCw)
#define libRR_AbsoluteIndexedXX0() READ_WORD(CPU.PCBase + Registers.PCw)

// Stack lengths
#define libRR_StackRelative_len 3
#define libRR_StackRelativeSlow_len 3
#define libRR_StackRelativeIndirectIndexed_len 3
#define libRR_StackRelativeIndirectIndexedSlow_len 3
// Direct lengths
#define libRR_Direct_len 2
#define libRR_DirectSlow_len 2
#define libRR_DirectIndexedXSlow_len 2
#define libRR_DirectIndexedYSlow_len 2
#define libRR_DirectIndirectSlow_len 2
#define libRR_DirectIndirectLong_len 2
#define libRR_DirectIndirectLongSlow_len 2
#define libRR_DirectIndirectIndexedE0X0_len 2
#define libRR_DirectIndirectIndexedE0X1_len 2
#define libRR_DirectIndirectIndexedE1_len 2
#define libRR_DirectIndirectIndexedSlow_len 2
#define libRR_DirectIndirectIndexedLong_len 2
#define libRR_DirectIndirectIndexedLongSlow_len 2
#define libRR_DirectIndexedIndirectE0_len 2
#define libRR_DirectIndexedIndirectE1_len 2
#define libRR_DirectIndexedIndirectSlow_len 2
#define libRR_DirectIndirectE0_len 2
#define libRR_DirectIndirectE1_len 2
#define libRR_DirectIndexedXE0_len 2
#define libRR_DirectIndexedYE0_len 2
#define libRR_DirectIndexedYE1_len 2
#define libRR_DirectIndexedXE1_len 2
// Absolute lengths
#define libRR_AbsoluteLong_len 4
#define libRR_AbsoluteLongIndexedX_len 4 // correct
#define libRR_AbsoluteIndexedYX0_len 3
#define libRR_AbsoluteIndexedYX1_len 3
#define libRR_Absolute_len 3
#define libRR_AbsoluteSlow_len 3
#define libRR_AbsoluteLongSlow_len 3
#define libRR_AbsoluteLongIndexedXSlow_len 3
#define libRR_AbsoluteIndexedYSlow_len 3
#define libRR_AbsoluteIndexedXX1_len 3
#define libRR_AbsoluteIndexedXX0_len 3
#define libRR_AbsoluteIndexedXSlow_len 3

// Suffix start
// Stack suffix
#define libRR_StackRelative_suffix " %int%, s ;"
#define libRR_StackRelativeSlow_suffix " %int%, s ;"
#define libRR_StackRelativeIndirectIndexedSlow_suffix " [%int%,x], s ;"
#define libRR_StackRelativeIndirectIndexed_suffix " [%int%,x], s ;"
// Direct suffix (1 byte operand)
#define libRR_Direct_suffix " %int% ;"
#define libRR_DirectSlow_suffix " %int% ;"
#define libRR_DirectIndexedXSlow_suffix " %int%, x ;"
#define libRR_DirectIndexedYSlow_suffix " %int%, y ;"
// Long indirect use []
#define libRR_DirectIndirectLong_suffix ".B [%int%] ;"
#define libRR_DirectIndirectLongSlow_suffix ".B [%int%] ;"
// Long Indexed versions use []
#define libRR_DirectIndirectIndexedLong_suffix ".B [%int%], y ;"
#define libRR_DirectIndirectIndexedLongSlow_suffix ".B [%int%], y ;"
// Non-long Indexed use ()
#define libRR_DirectIndirectIndexedE0X0_suffix " (%int%), y ;"
#define libRR_DirectIndirectIndexedE0X1_suffix " (%int%), y ;"
#define libRR_DirectIndirectIndexedE1_suffix " (%int%), y ;"
#define libRR_DirectIndirectIndexedSlow_suffix " (%int%), y ;"

// DirectIndexedIndirect use ()
#define libRR_DirectIndexedIndirectE0_suffix " (%int%,X) ;"
#define libRR_DirectIndexedIndirectE1_suffix " (%int%,X) ;"
#define libRR_DirectIndexedIndirectSlow_suffix " (%int%,X) ;"
// Direct indirect use ()
#define libRR_DirectIndirectE0_suffix " (%int%) ;"
#define libRR_DirectIndirectE1_suffix " (%int%) ;"
#define libRR_DirectIndirectSlow_suffix " (%int%) ;"
// DirectIndexed 
#define libRR_DirectIndexedXE0_suffix " %int%, x ;"
#define libRR_DirectIndexedXE1_suffix " %int%, x ;"
#define libRR_DirectIndexedYE0_suffix " %int%, y ;"
#define libRR_DirectIndexedYE1_suffix " %int%, y ;"
// Absolute suffix (2 byte operand)
#define libRR_AbsoluteLong_suffix ".L %int% ;"
#define libRR_AbsoluteLongSlow_suffix ".L %int% ;"
#define libRR_AbsoluteLongIndexedXSlow_suffix ".L %int%, x ;"
#define libRR_AbsoluteLongIndexedX_suffix ".L %int%, x ;"
#define libRR_AbsoluteIndexedYX0_suffix ".W %int%, y ;"
#define libRR_AbsoluteIndexedYX1_suffix ".W %int%, y ;"
#define libRR_AbsoluteIndexedXX1_suffix ".W %int%, x ;"
#define libRR_AbsoluteIndexedXX0_suffix ".W %int%, x ;"
#define libRR_AbsoluteIndexedXSlow_suffix ".W %int%, x ;"
#define libRR_AbsoluteIndexedYSlow_suffix ".W %int%, y ;"
#define libRR_Absolute_suffix ".W %int% ;"
#define libRR_AbsoluteSlow_suffix ".W %int% ;"

// libRR read opcode 8bit
#define libRR_rOP8(DISASM, OP, ADDR, WRAP, FUNC) \
static void Op##OP (void) \
{ \
	uint32 libRR_temp = libRR_##ADDR (); \
	libRR_log_instruction_1int(Registers.PCw - 1, DISASM libRR_##ADDR##_suffix #ADDR , 0x00, libRR_##ADDR##_len, libRR_temp); \
	uint8	val = OpenBus = S9xGetByte(ADDR(READ)); \
	FUNC##8(val); \
}

#define rOP8(OP, ADDR, WRAP, FUNC) \
static void Op##OP (void) \
{ \
	uint8	val = OpenBus = S9xGetByte(ADDR(READ)); \
	FUNC##8(val); \
}

// libRR read opcode 16bit
#define libRR_rOP16(DISASM, OP, ADDR, WRAP, FUNC) \
static void Op##OP (void) \
{ \
	uint32 libRR_temp = libRR_##ADDR (); \
	libRR_log_instruction_1int(Registers.PCw - 1, DISASM libRR_##ADDR##_suffix #ADDR , 0x00, libRR_##ADDR##_len, libRR_temp); \
	uint16	val = S9xGetWord(ADDR(READ), WRAP); \
	OpenBus = (uint8) (val >> 8); \
	FUNC(val); \
}

#define rOP16(OP, ADDR, WRAP, FUNC) \
static void Op##OP (void) \
{ \
	uint16	val = S9xGetWord(ADDR(READ), WRAP); \
	OpenBus = (uint8) (val >> 8); \
	FUNC(val); \
}

// libRR read opcode Conditional
#define libRR_rOPC(DISASM, OP, COND, ADDR, WRAP, FUNC) \
static void Op##OP (void) \
{ \
	libRR_log_instruction(Registers.PCw - 1, DISASM libRR_##ADDR##_suffix #ADDR, 0x00, libRR_##ADDR##_len); \
	if (Check##COND()) \
	{ \
		uint8	val = OpenBus = S9xGetByte(ADDR(READ)); \
		FUNC##8(val); \
	} \
	else \
	{ \
		uint16	val = S9xGetWord(ADDR(READ), WRAP); \
		OpenBus = (uint8) (val >> 8); \
		FUNC##16(val); \
	} \
}

#define rOPC(OP, COND, ADDR, WRAP, FUNC) \
static void Op##OP (void) \
{ \
	if (Check##COND()) \
	{ \
		uint8	val = OpenBus = S9xGetByte(ADDR(READ)); \
		FUNC##8(val); \
	} \
	else \
	{ \
		uint16	val = S9xGetWord(ADDR(READ), WRAP); \
		OpenBus = (uint8) (val >> 8); \
		FUNC##16(val); \
	} \
}

// libRR read opcode M
#define libRR_rOPM(DISASM, OP, ADDR, WRAP, FUNC) \
libRR_rOPC(DISASM, OP, Memory, ADDR, WRAP, FUNC)

#define rOPM(OP, ADDR, WRAP, FUNC) \
rOPC(OP, Memory, ADDR, WRAP, FUNC)

// LibRR read opcode X
#define libRR_rOPX(DISASM, OP, ADDR, WRAP, FUNC) \
libRR_rOPC(DISASM, OP, Index, ADDR, WRAP, FUNC)

#define rOPX(OP, ADDR, WRAP, FUNC) \
rOPC(OP, Index, ADDR, WRAP, FUNC)



// LibRR write opcode 8bit
#define libRR_wOP8(DISASM, OP, ADDR, WRAP, FUNC) \
static void Op##OP (void) \
{ \
	uint32 libRR_temp = libRR_##ADDR (); \
	libRR_log_instruction_1int(Registers.PCw - 1, DISASM libRR_##ADDR##_suffix #ADDR , 0x00, libRR_##ADDR##_len, libRR_temp); \
	FUNC##8(ADDR(WRITE)); \
}

#define wOP8(OP, ADDR, WRAP, FUNC) \
static void Op##OP (void) \
{ \
	FUNC##8(ADDR(WRITE)); \
}

// libRR write opcode 16bit
#define libRR_wOP16(DISASM, OP, ADDR, WRAP, FUNC) \
static void Op##OP (void) \
{ \
	uint32 libRR_temp = libRR_##ADDR (); \
	libRR_log_instruction_1int(Registers.PCw - 1, DISASM libRR_##ADDR##_suffix #ADDR , 0x00, libRR_##ADDR##_len, libRR_temp); \
	FUNC##16(ADDR(WRITE), WRAP); \
}

#define wOP16(OP, ADDR, WRAP, FUNC) \
static void Op##OP (void) \
{ \
	FUNC##16(ADDR(WRITE), WRAP); \
}

// libRR write opcode conditional
#define libRR_wOPC(DISASM, OP, COND, ADDR, WRAP, FUNC) \
static void Op##OP (void) \
{ \
	libRR_log_instruction(Registers.PCw - 1, DISASM libRR_##ADDR##_suffix #ADDR, 0x00, libRR_##ADDR##_len); \
	if (Check##COND()) {\
		FUNC##8(ADDR(WRITE)); }\
	else {\
		FUNC##16(ADDR(WRITE), WRAP); }\
}

#define wOPC(OP, COND, ADDR, WRAP, FUNC) \
static void Op##OP (void) \
{ \
	if (Check##COND()) \
		FUNC##8(ADDR(WRITE)); \
	else \
		FUNC##16(ADDR(WRITE), WRAP); \
}

// libRR write opcode M
#define libRR_wOPM(DISASM, OP, ADDR, WRAP, FUNC) \
libRR_wOPC(DISASM, OP, Memory, ADDR, WRAP, FUNC)

#define wOPM(OP, ADDR, WRAP, FUNC) \
wOPC(OP, Memory, ADDR, WRAP, FUNC)

// libRR write opcode X
#define libRR_wOPX(DISASM, OP, ADDR, WRAP, FUNC) \
libRR_wOPC(DISASM, OP, Index, ADDR, WRAP, FUNC)

#define wOPX(OP, ADDR, WRAP, FUNC) \
wOPC(OP, Index, ADDR, WRAP, FUNC)

// libRR modify opcode 8
#define libRR_mOP8(DISASM, OP, ADDR, WRAP, FUNC) \
static void Op##OP (void) \
{ \
	uint32 libRR_temp = libRR_##ADDR (); \
	libRR_log_instruction_1int(Registers.PCw - 1, DISASM libRR_##ADDR##_suffix #ADDR , 0x00, libRR_##ADDR##_len, libRR_temp); \
	FUNC##8(ADDR(MODIFY)); \
}

#define mOP8(OP, ADDR, WRAP, FUNC) \
static void Op##OP (void) \
{ \
	FUNC##8(ADDR(MODIFY)); \
}

// libRR modify opcode 16
#define libRR_mOP16(DISASM, OP, ADDR, WRAP, FUNC) \
static void Op##OP (void) \
{ \
	uint32 libRR_temp = libRR_##ADDR (); \
	libRR_log_instruction_1int(Registers.PCw - 1, DISASM libRR_##ADDR##_suffix #ADDR, 0x00, libRR_##ADDR##_len, libRR_temp); \
	FUNC##16(ADDR(MODIFY), WRAP); \
}
#define mOP16(OP, ADDR, WRAP, FUNC) \
static void Op##OP (void) \
{ \
	FUNC##16(ADDR(MODIFY), WRAP); \
}

// libRR modify opcode conditional
#define libRR_mOPC(DISASM, OP, COND, ADDR, WRAP, FUNC) \
static void Op##OP (void) \
{ \
	libRR_log_instruction(Registers.PCw - 1, DISASM libRR_##ADDR##_suffix #ADDR, 0x00, libRR_##ADDR##_len); \
	if (Check##COND()) \
	{	FUNC##8(ADDR(MODIFY)); }\
	else \
	{	FUNC##16(ADDR(MODIFY), WRAP); } \
}
#define mOPC(OP, COND, ADDR, WRAP, FUNC) \
static void Op##OP (void) \
{ \
	if (Check##COND()) \
		FUNC##8(ADDR(MODIFY)); \
	else \
		FUNC##16(ADDR(MODIFY), WRAP); \
}

// libRR modify opcode M
#define libRR_mOPM(DISASM, OP, ADDR, WRAP, FUNC) \
libRR_mOPC(DISASM, OP, Memory, ADDR, WRAP, FUNC)

#define mOPM(OP, ADDR, WRAP, FUNC) \
mOPC(OP, Memory, ADDR, WRAP, FUNC)

// libRR branch opcode
#define libRR_bOP(DISASM, OP, REL, COND, CHK, E) \
static void Op##OP (void) \
{ \
	pair	newPC; \
	newPC.W = REL(JUMP); \
	const char* label_name = libRR_log_jump_label(newPC.W, Registers.PCw-1); \
	libRR_log_instruction_1int_registername(Registers.PCw - 2, DISASM, 0x00, 2, newPC.W, label_name); \
	if (COND) \
	{ \
		AddCycles(ONE_CYCLE); \
		if (E && Registers.PCh != newPC.B.h) \
			AddCycles(ONE_CYCLE); \
		if ((Registers.PCw & ~MEMMAP_MASK) != (newPC.W & ~MEMMAP_MASK)) \
			S9xSetPCBase(ICPU.ShiftedPB + newPC.W); \
		else \
			Registers.PCw = newPC.W; \
	} \
}

#define bOP(OP, REL, COND, CHK, E) \
static void Op##OP (void) \
{ \
	pair	newPC; \
	newPC.W = REL(JUMP); \
	if (COND) \
	{ \
		AddCycles(ONE_CYCLE); \
		if (E && Registers.PCh != newPC.B.h) \
			AddCycles(ONE_CYCLE); \
		if ((Registers.PCw & ~MEMMAP_MASK) != (newPC.W & ~MEMMAP_MASK)) \
			S9xSetPCBase(ICPU.ShiftedPB + newPC.W); \
		else \
			Registers.PCw = newPC.W; \
	} \
}


#define SetZN16(Work16) \
	ICPU._Zero = Work16 != 0; \
	ICPU._Negative = (uint8) (Work16 >> 8);

#define SetZN8(Work8) \
	ICPU._Zero = Work8; \
	ICPU._Negative = Work8;
	
static INLINE void ADC16(uint16 Work16)
{
	if (CheckDecimal())
	{
		uint16 Ans16;
		uint16	A1 = Registers.A.W & 0x000F;
		uint16	A2 = Registers.A.W & 0x00F0;
		uint16	A3 = Registers.A.W & 0x0F00;
		uint32	A4 = Registers.A.W & 0xF000;
		uint16	W1 = Work16 & 0x000F;
		uint16	W2 = Work16 & 0x00F0;
		uint16	W3 = Work16 & 0x0F00;
		uint16	W4 = Work16 & 0xF000;

		A1 += W1 + CheckCarry();
		if (A1 > 0x0009)
		{
			A1 -= 0x000A;
			A1 &= 0x000F;
			A2 += 0x0010;
		}

		A2 += W2;
		if (A2 > 0x0090)
		{
			A2 -= 0x00A0;
			A2 &= 0x00F0;
			A3 += 0x0100;
		}

		A3 += W3;
		if (A3 > 0x0900)
		{
			A3 -= 0x0A00;
			A3 &= 0x0F00;
			A4 += 0x1000;
		}

		A4 += W4;
		if (A4 > 0x9000)
		{
			A4 -= 0xA000;
			A4 &= 0xF000;
			SetCarry();
		}
		else
			ClearCarry();

		Ans16 = A4 | A3 | A2 | A1;

		if (~(Registers.A.W ^ Work16) & (Work16 ^ Ans16) & 0x8000)
			SetOverflow();
		else
			ClearOverflow();

		Registers.A.W = Ans16;
	}
	else
	{
		uint32	Ans32 = Registers.A.W + Work16 + CheckCarry();

		ICPU._Carry = Ans32 >= 0x10000;

		if (~(Registers.A.W ^ Work16) & (Work16 ^ (uint16) Ans32) & 0x8000)
			SetOverflow();
		else
			ClearOverflow();

		Registers.A.W = (uint16) Ans32;
	}
	SetZN16(Registers.A.W);
}

static INLINE void ADC8(uint8 Work8)
{
	if (CheckDecimal())
	{
		uint8 A1, W1, W2, Ans8;
		uint16 A2;

		A1 = Registers.A.W & 0x0F;
		A2 = Registers.A.W & 0xF0;
		W1 = Work8 & 0x0F;
		W2 = Work8 & 0xF0;

		A1 += W1 + CheckCarry();
		if (A1 > 0x09)
		{
			A1 -= 0x0A;
			A1 &= 0x0F;
			A2 += 0x10;
		}

		A2 += W2;
		if (A2 > 0x90)
		{
			A2 -= 0xA0;
			A2 &= 0xF0;
			SetCarry();
		}
		else
			ClearCarry();

		Ans8 = A2 | A1;

		if (~(Registers.AL ^ Work8) & (Work8 ^ Ans8) & 0x80)
			SetOverflow();
		else
			ClearOverflow();

		Registers.AL = Ans8;
	}
	else
	{
		uint16	Ans16 = Registers.AL + Work8 + CheckCarry();

		ICPU._Carry = Ans16 >= 0x100;

		if (~(Registers.AL ^ Work8) & (Work8 ^ (uint8) Ans16) & 0x80)
			SetOverflow();
		else
			ClearOverflow();

		Registers.AL = (uint8) Ans16;
	}
	SetZN8(Registers.AL);
}

static INLINE void AND16(uint16 Work16)
{
	Registers.A.W &= Work16;
	SetZN16(Registers.A.W);
}

static INLINE void AND8(uint8 Work8)
{
	Registers.AL &= Work8;
	SetZN8(Registers.AL);
}

static INLINE void ASL16 (uint32 OpAddress, uint32 w)
{
	uint16	Work16 = S9xGetWord(OpAddress, w);
	ICPU._Carry = (Work16 & 0x8000) != 0;
	Work16 <<= 1;
	AddCycles(ONE_CYCLE);
	S9xSetWord_Write1(Work16, OpAddress, w);
	OpenBus = Work16 & 0xff;
	SetZN16(Work16);
}

static INLINE void ASL8 (uint32 OpAddress)
{
	uint8	Work8 = S9xGetByte(OpAddress);
	ICPU._Carry = (Work8 & 0x80) != 0;
	Work8 <<= 1;
	AddCycles(ONE_CYCLE);
	S9xSetByte(Work8, OpAddress);
	OpenBus = Work8;
	SetZN8(Work8);
}

static INLINE void BIT16(uint16 Work16)
{
	ICPU._Overflow = (Work16 & 0x4000) != 0;
	ICPU._Negative = (uint8) (Work16 >> 8);
	ICPU._Zero = (Work16 & Registers.A.W) != 0;
}

static INLINE void BIT8(uint8 Work8)
{
	ICPU._Overflow = (Work8 & 0x40) != 0;
	ICPU._Negative = Work8;
	ICPU._Zero = Work8 & Registers.AL;
}

static INLINE void CMP16(uint16 val)
{
	int16 Int16;
	int32 Int32;

	Int32 = (int32) Registers.A.W - (int32) val;
	ICPU._Carry = Int32 >= 0;
	Int16 = Int32;
	SetZN16(Int16);
}

static INLINE void CMP8(uint8 val)
{
	int16 Int16;
	uint8 Int8;

	Int16 = (int16) Registers.AL - (int16) val;
	ICPU._Carry = Int16 >= 0;
	Int8 = Int16;
	SetZN8(Int8);
}

static INLINE void CPX16(uint16 val)
{
	int32 Int32;
	uint16 Int16;

	Int32 = (int32) Registers.X.W - (int32) val;
	ICPU._Carry = Int32 >= 0;
	Int16 = Int32;
	SetZN16(Int16);
}

static INLINE void CPX8(uint8 val)
{
	int16 Int16;
	uint8 Int8;

	Int16 = (int16) Registers.XL - (int16) val;
	ICPU._Carry = Int16 >= 0;
	Int8 = Int16;
	SetZN8(Int8);
}

static INLINE void CPY16(uint16 val)
{
	int32 Int32;
	uint16 Int16;

	Int32 = (int32) Registers.Y.W - (int32) val;
	ICPU._Carry = Int32 >= 0;
	Int16 = Int32;
	SetZN16(Int16);
}

static INLINE void CPY8(uint8 val)
{
	int16 Int16;
	uint8 Int8;

	Int16 = (int16) Registers.YL - (int16) val;
	ICPU._Carry = Int16 >= 0;
	Int8 = Int16;
	SetZN8(Int8);
}

static INLINE void DEC16 (uint32 OpAddress, uint32 w)
{
	uint16 Work16;

	Work16 = S9xGetWord(OpAddress, w) - 1;
	AddCycles(ONE_CYCLE);
	S9xSetWord_Write1(Work16, OpAddress, w);
	OpenBus = Work16 & 0xff;
	SetZN16(Work16);
}

static INLINE void DEC8 (uint32 OpAddress)
{
	uint8	Work8 = S9xGetByte(OpAddress) - 1;
	AddCycles(ONE_CYCLE);
	S9xSetByte(Work8, OpAddress);
	OpenBus = Work8;
	SetZN8(Work8);
}

static INLINE void EOR16(uint16 val)
{
	Registers.A.W ^= val;
	SetZN16(Registers.A.W);
}

static INLINE void EOR8(uint8 val)
{
	Registers.AL ^= val;
	SetZN8(Registers.AL);
}

static INLINE void INC16 (uint32 OpAddress, uint32 w)
{
	uint16	Work16 = S9xGetWord(OpAddress, w) + 1;
	AddCycles(ONE_CYCLE);
	S9xSetWord_Write1(Work16, OpAddress, w);
	OpenBus = Work16 & 0xff;
	SetZN16(Work16);
}

static INLINE void INC8 (uint32 OpAddress)
{
	uint8	Work8 = S9xGetByte(OpAddress) + 1;
	AddCycles(ONE_CYCLE);
	S9xSetByte(Work8, OpAddress);
	OpenBus = Work8;
	SetZN8(Work8);
}

static INLINE void LDA16(uint16 val)
{
	Registers.A.W = val;
	SetZN16(Registers.A.W);
}

static INLINE void LDA8(uint8 val)
{
	Registers.AL = val;
	SetZN8(Registers.AL);
}

static INLINE void LDX16(uint16 val)
{
	Registers.X.W = val;
	SetZN16(Registers.X.W);
}

static INLINE void LDX8(uint8 val)
{
	Registers.XL = val;
	SetZN8(Registers.XL);
}

static INLINE void LDY16(uint16 val)
{
	Registers.Y.W = val;
	SetZN16(Registers.Y.W);
}

static INLINE void LDY8(uint8 val)
{
	Registers.YL = val;
	SetZN8(Registers.YL);
}

static INLINE void LSR16 (uint32 OpAddress, uint32 w)
{
	uint16	Work16 = S9xGetWord(OpAddress, w);
	ICPU._Carry = Work16 & 1;
	Work16 >>= 1;
	AddCycles(ONE_CYCLE);
	S9xSetWord_Write1(Work16, OpAddress, w);
	OpenBus = Work16 & 0xff;
	SetZN16(Work16);
}

static INLINE void LSR8 (uint32 OpAddress)
{
	uint8	Work8 = S9xGetByte(OpAddress);
	ICPU._Carry = Work8 & 1;
	Work8 >>= 1;
	AddCycles(ONE_CYCLE);
	S9xSetByte(Work8, OpAddress);
	OpenBus = Work8;
	SetZN8(Work8);
}

static INLINE void ORA16(uint16 val)
{
	Registers.A.W |= val;
	SetZN16(Registers.A.W);
}

static INLINE void ORA8(uint8 val)
{
	Registers.AL |= val;
	SetZN8(Registers.AL);
}

static INLINE void ROL16 (uint32 OpAddress, uint32 w)
{
	uint32	Work32 = (((uint32) S9xGetWord(OpAddress, w)) << 1) | CheckCarry();
	ICPU._Carry = Work32 >= 0x10000;
	AddCycles(ONE_CYCLE);
	S9xSetWord_Write1((uint16) Work32, OpAddress, w);
	OpenBus = Work32 & 0xff;
	SetZN16((uint16) Work32);
}

static INLINE void ROL8 (uint32 OpAddress)
{
	uint16	Work16 = (((uint16) S9xGetByte(OpAddress)) << 1) | CheckCarry();
	ICPU._Carry = Work16 >= 0x100;
	AddCycles(ONE_CYCLE);
	S9xSetByte((uint8) Work16, OpAddress);
	OpenBus = Work16 & 0xff;
	SetZN8((uint8) Work16);
}

static INLINE void ROR16 (uint32 OpAddress, uint32 w)
{
	uint32	Work32 = ((uint32) S9xGetWord(OpAddress, w)) | (((uint32) CheckCarry()) << 16);
	ICPU._Carry = Work32 & 1;
	Work32 >>= 1;
	AddCycles(ONE_CYCLE);
	S9xSetWord_Write1((uint16) Work32, OpAddress, w);
	OpenBus = Work32 & 0xff;
	SetZN16((uint16) Work32);
}

static INLINE void ROR8 (uint32 OpAddress)
{
	uint16	Work16 = ((uint16) S9xGetByte(OpAddress)) | (((uint16) CheckCarry()) << 8);
	ICPU._Carry = Work16 & 1;
	Work16 >>= 1;
	AddCycles(ONE_CYCLE);
	S9xSetByte((uint8) Work16, OpAddress);
	OpenBus = Work16 & 0xff;
	SetZN8((uint8) Work16);
}

static INLINE void SBC16(uint16 Work16)
{
	if (CheckDecimal())
	{
		uint16 Ans16;
		uint16	A1 = Registers.A.W & 0x000F;
		uint16	A2 = Registers.A.W & 0x00F0;
		uint16	A3 = Registers.A.W & 0x0F00;
		uint32	A4 = Registers.A.W & 0xF000;
		uint16	W1 = Work16 & 0x000F;
		uint16	W2 = Work16 & 0x00F0;
		uint16	W3 = Work16 & 0x0F00;
		uint16	W4 = Work16 & 0xF000;

		A1 -= W1 + !CheckCarry();
		A2 -= W2;
		A3 -= W3;
		A4 -= W4;

		if (A1 > 0x000F)
		{
			A1 += 0x000A;
			A1 &= 0x000F;
			A2 -= 0x0010;
		}

		if (A2 > 0x00F0)
		{
			A2 += 0x00A0;
			A2 &= 0x00F0;
			A3 -= 0x0100;
		}

		if (A3 > 0x0F00)
		{
			A3 += 0x0A00;
			A3 &= 0x0F00;
			A4 -= 0x1000;
		}

		if (A4 > 0xF000)
		{
			A4 += 0xA000;
			A4 &= 0xF000;
			ClearCarry();
		}
		else
			SetCarry();

		Ans16 = A4 | A3 | A2 | A1;

		if ((Registers.A.W ^ Work16) & (Registers.A.W ^ Ans16) & 0x8000)
			SetOverflow();
		else
			ClearOverflow();

		Registers.A.W = Ans16;
	}
	else
	{
		int32	Int32 = (int32) Registers.A.W - (int32) Work16 + (int32) CheckCarry() - 1;

		ICPU._Carry = Int32 >= 0;

		if ((Registers.A.W ^ Work16) & (Registers.A.W ^ (uint16) Int32) & 0x8000)
			SetOverflow();
		else
			ClearOverflow();

		Registers.A.W = (uint16) Int32;
	}
	SetZN16(Registers.A.W);
}

static INLINE void SBC8(uint8 Work8)
{
	if (CheckDecimal())
	{
		uint8 A1, W1, W2, Ans8;
		uint16 A2;

		A1 = Registers.A.W & 0x0F;
		A2 = Registers.A.W & 0xF0;
		W1 = Work8 & 0x0F;
		W2 = Work8 & 0xF0;

		A1 -= W1 + !CheckCarry();
		A2 -= W2;

		if (A1 > 0x0F)
		{
			A1 += 0x0A;
			A1 &= 0x0F;
			A2 -= 0x10;
		}

		if (A2 > 0xF0)
		{
			A2 += 0xA0;
			A2 &= 0xF0;
			ClearCarry();
		}
		else
			SetCarry();

		Ans8 = A2 | A1;

		if ((Registers.AL ^ Work8) & (Registers.AL ^ Ans8) & 0x80)
			SetOverflow();
		else
			ClearOverflow();

		Registers.AL = Ans8;
	}
	else
	{
		int16	Int16 = (int16) Registers.AL - (int16) Work8 + (int16) CheckCarry() - 1;

		ICPU._Carry = Int16 >= 0;

		if ((Registers.AL ^ Work8) & (Registers.AL ^ (uint8) Int16) & 0x80)
			SetOverflow();
		else
			ClearOverflow();

		Registers.AL = (uint8) Int16;
	}
	SetZN8(Registers.AL);
}

static INLINE void STA16 (uint32 OpAddress, uint32 w)
{
	S9xSetWord_Write0(Registers.A.W, OpAddress, w);
	OpenBus = Registers.AH;
}

static INLINE void STA8 (uint32 OpAddress)
{
	S9xSetByte(Registers.AL, OpAddress);
	OpenBus = Registers.AL;
}

static INLINE void STX16 (uint32 OpAddress, uint32 w)
{
	S9xSetWord_Write0(Registers.X.W, OpAddress, w);
	OpenBus = Registers.XH;
}

static INLINE void STX8 (uint32 OpAddress)
{
	S9xSetByte(Registers.XL, OpAddress);
	OpenBus = Registers.XL;
}

static INLINE void STY16 (uint32 OpAddress, uint32 w)
{
	S9xSetWord_Write0(Registers.Y.W, OpAddress, w);
	OpenBus = Registers.YH;
}

static INLINE void STY8 (uint32 OpAddress)
{
	S9xSetByte(Registers.YL, OpAddress);
	OpenBus = Registers.YL;
}

static INLINE void STZ16 (uint32 OpAddress, uint32 w)
{
	S9xSetWord_Write0(0, OpAddress, w);
	OpenBus = 0;
}

static INLINE void STZ8 (uint32 OpAddress)
{
	S9xSetByte(0, OpAddress);
	OpenBus = 0;
}

static INLINE void TSB16 (uint32 OpAddress, uint32 w)
{
	uint16 Work16;

	Work16 = S9xGetWord(OpAddress, w);
	ICPU._Zero = (Work16 & Registers.A.W) != 0;
	Work16 |= Registers.A.W;
	AddCycles(ONE_CYCLE);
	S9xSetWord_Write1(Work16, OpAddress, w);
	OpenBus = Work16 & 0xff;
}

static INLINE void TSB8 (uint32 OpAddress)
{
	uint8 Work8;

	Work8 = S9xGetByte(OpAddress);
	ICPU._Zero = Work8 & Registers.AL;
	Work8 |= Registers.AL;
	AddCycles(ONE_CYCLE);
	S9xSetByte(Work8, OpAddress);
	OpenBus = Work8;
}

static INLINE void TRB16 (uint32 OpAddress, uint32 w)
{
	uint16 Work16;

	Work16 = S9xGetWord(OpAddress, w);
	ICPU._Zero = (Work16 & Registers.A.W) != 0;
	Work16 &= ~Registers.A.W;
	AddCycles(ONE_CYCLE);
	S9xSetWord_Write1(Work16, OpAddress, w);
	OpenBus = Work16 & 0xff;
}

static INLINE void TRB8 (uint32 OpAddress)
{
	uint8 Work8;

	Work8 = S9xGetByte(OpAddress);
	ICPU._Zero = Work8 & Registers.AL;
	Work8 &= ~Registers.AL;
	AddCycles(ONE_CYCLE);
	S9xSetByte(Work8, OpAddress);
	OpenBus = Work8;
}

#endif
