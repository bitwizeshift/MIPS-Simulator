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
		type_r_instruction, //!< r-type mips instruction (register)
		type_i_instruction, //!< i-type mips instruction (immediate)
		type_j_instruction  //!< j-type mips instruction (jump)
	};

	///
	/// @enum mips32::instr_offset
	///
	/// The bit offsets for each portion of a mips32 instruction
	///
	enum instr_offset{
		offset_opcode = 25,//!< offset_opcode
		offset_func   = 0, //!< offset_func
		offset_shift  = 5, //!< offset_shift
		offset_rd     = 10,//!< offset_rd
		offset_rt     = 15,//!< offset_rt
		offset_rs     = 20,//!< offset_rs
		offset_jump   = 0, //!< offset_jump
		offset_imm    = 0  //!< offset_imm
	};

	///
	/// @enum mips32::instr_mask
	///
	/// The bit mask for each portion of a mips32 instruction
	///
	enum instr_mask{
		mask_opcode = 0xFC000000,
		mask_rs     = 0x03E00000,
		mask_rt     = 0x001F0000,
		mask_rd     = 0x0000F800,
		mask_shift  = 0x000007C0,
		mask_funct  = 0x0000003F,
		mask_jump   = 0x0000FFFF,
		mask_imm    = 0x03FFFFFF
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

	///
	/// @enum mips32::reg
	///
	///
	///
	enum reg{
		reg_zero = 0, //!< named register 0
		reg_at   = 1,
		reg_gp   = 28,
		reg_sp   = 29,
		reg_fp   = 30,
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

	enum r_opcodes{
		op_r_logic = 0x00,
		op_r_proc  = 0x10
	};

	///
	/// @enum mips32::r_opcode
	///
	/// Register operations
	///
	enum r_functions{
		func_sll   = 0x00, //!< func_sll
		func_srl   = 0x02, //!< func_srl
		func_sra   = 0x03, //!< func_sra
		func_jr    = 0x08, //!< func_jr
		func_jalr  = 0x09,
		func_mfhi  = 0x10,
		func_mthi  = 0x11,
		func_mflo  = 0x12,
		func_mtlo  = 0x13,
		func_mult  = 0x18, //!< func_mul
		func_multu = 0x19, //!< func_mulu
		func_div   = 0x1A, //!< func_div
		func_divu  = 0x1B, //!< func_divu
		func_add   = 0x20, //!< func_add
		func_addu  = 0x21, //!< func_addu
		func_sub   = 0x22, //!< func_sub
		func_subu  = 0x23, //!< func_subu
		func_and   = 0x24, //!< func_and
		func_or    = 0x25, //!< func_or
		func_xor   = 0x26, //!< func_xor
		func_nor   = 0x27, //!< func_nor
		func_slt   = 0x2A, //!< func_slt
		func_sltu  = 0x2B, //!< func_sltu
	};

	//--------------------------------------------------------------------------

	///
	/// @enum mips32::i_opcode
	///
	/// Immediate opcodes
	///
	enum i_opcode{
		op_beq   = 0x04,
		op_bne   = 0x05,
		op_blez  = 0x06,
		op_bgtz  = 0x07,
		op_addi  = 0x08,
		op_addui = 0x09,
		op_slti  = 0x0A,
		op_sltiu = 0x0B,
		op_andi  = 0x0C,
		op_ori   = 0x0D,
		op_xori  = 0x0E,
		op_lui   = 0x0F,

		op_llo   = 0x18,
		op_lhi   = 0x19,
		op_lb    = 0x20,
		op_lh    = 0x21,
		op_lw    = 0x23,

		op_lbu   = 0x24,
		op_lhu   = 0x25,

		op_sb    = 0x28,
		op_sh    = 0x29,
		op_sw    = 0x2B
	};

	//--------------------------------------------------------------------------

	///
	/// @enum mips32::j_opcode
	///
	/// Jump operations
	///
	enum j_opcode{
		op_j    = 0x02,
		op_jal  = 0x03,
		op_trap = 0x1A
	};


	template<u32 bit>
	s32 sign_extend( u32 value ){
		const u32 mask   = (2*(1 << bit)-1);
		const u32 extend = ~mask;
		const u32 result = (value & mask) | ((value & (1 << bit)) ? extend : 0);
		return static_cast<s32>(result);
	}

	template<u32 bit>
	u32 zero_extend( u32 value ){
		const u32 mask   = (2*(1 << bit)-1);
		const u32 result = (value & mask);
		return static_cast<u32>(result);
	}

} // namespace mips32

#endif /* MIPS32_INSTRUCTIONS_HPP_ */
