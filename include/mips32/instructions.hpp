/**
 * @file instructions.hpp
 *
 * @todo Add description
 *
 * @author Matthew Rodusek (matthew.rodusek@gmail.com)
 * @date   Jan 24, 2016
 *
 */

/*
 * Change Log:
 *
 * Jan 24, 2016: 
 * - instructions.hpp created
 */
#ifndef MIPS32_INSTRUCTIONS_HPP_
#define MIPS32_INSTRUCTIONS_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

namespace mips32{

	//-------------------------------------------------------------------------
	// Instructions
	//-------------------------------------------------------------------------

	///
	/// @enum mips32::instruction_type
	///
	///
	///
	enum instruction_type{
		r_type_instruction, //!< r-type mips instruction (register)
		i_type_instruction, //!< i-type mips instruction (immediate)
		j_type_instruction  //!< j-type mips instruction (jump)
	};

	///
	/// @struct mips32::r_instruction
	///
	///
	///
	struct r_instruction{
		u32 opcode   : 6;
		u32 rs       : 5;
		u32 rt       : 5;
		u32 rd       : 5;
		u32 shift    : 5;
		u32 function : 6;
	};

	///
	/// @struct mips32::i_instruction
	///
	///
	///
	struct i_instruction{
		u32 opcode    : 6;
		u32 rs        : 5;
		u32 rt        : 5;
		u32 immediate : 16;
	};

	///
	/// @struct mips32::j_instruction
	///
	///
	///
	struct j_instruction{
		u32 opcode : 6;
		u32 target : 26;
	};

	///
	/// @struct mips::instruction
	///
	///
	///
	struct Instruction{
		instruction_type type;
		union{
			r_instruction r; //!< Register instruction
			i_instruction i; //!< Immediate instruction
			j_instruction j; //!< Jump instruction
		};
	};

	//-------------------------------------------------------------------------
	// Instruction operation codes
	//-------------------------------------------------------------------------

	const u32 halt;

	///
	/// @enum mips32::reg
	///
	///
	///
	enum reg{
		reg_zero = 0, //!< named register 0
		reg_jump = 31 //!< named register jump
	};

	//--------------------------------------------------------------------------

	///
	/// @enum mips32::bit_masks
	///
	///
	///
	enum bit_masks{
		bits_op   = 0xFC000000, //!< Opcode bits
		bits_rs   = 0x03E00000, //!< register s bits
		bits_rt   = 0x001F0000, //!< register t bits
		bits_rd   = 0x0000F800, //!< register d bits
		bits_shf  = 0x000007C0, //!< shift amount bits
		bits_fnc  = 0x0000003F, //!< function bits

		bits_imm  = 0x0000FFFF, //!< immediate bits
		bits_jmp  = 0x03FFFFFF  //!< jump target bits
	};

	//--------------------------------------------------------------------------

	///
	/// @enum mips32::r_opcode
	///
	/// Register operations
	///
	enum r_opcode{
		op_sll  = 0x00, //!< op_sll
		op_srl  = 0x02, //!< op_srl
		op_add  = 0x20, //!< op_add
		op_addu = 0x21, //!< op_addu
		op_sub  = 0x22, //!< op_sub
		op_subu = 0x23, //!< op_subu
		op_and  = 0x24, //!< op_and
		op_or   = 0x25, //!< op_or
		op_nor  = 0x27, //!< op_nor
		op_slt  = 0x2A, //!< op_slt
		op_sltu = 0x2B, //!< op_sltu
		op_div,         //!< op_div
		op_divu,        //!< op_divu
		op_mul,         //!< op_mul
		op_mulu         //!< op_mulu
	};

	//--------------------------------------------------------------------------

	///
	/// @enum mips32::i_opcode
	///
	/// Immediate opcodes
	///
	enum i_opcode{
		op_beq   = 0x04, //!< op_beq
		op_bne   = 0x05, //!< op_bne
		op_addi  = 0x08, //!< op_addi
		op_addui = 0x09, //!< op_addui
		op_andi  = 0x0c, //!< op_andi
		op_divi,         //!< op_divi
		op_diviu,        //!< op_diviu
		op_muli,         //!< op_muli
		op_muliu,        //!< op_muliu
		op_lw    = 0x23, //!< op_lw
		op_sw    = 0x2b  //!< op_sw

	};

	//--------------------------------------------------------------------------

	///
	/// @enum mips32::j_opcode
	///
	/// Jump operations
	///
	enum j_opcode{
		op_jump  = 0x02, //!< op_jump
		op_jumpl = 0x03, //!< op_jumpl
		op_jumpr = 0x08  //!< op_jumpr
	};

} // namespace mips32

#endif /* MIPS32_INSTRUCTIONS_HPP_ */
