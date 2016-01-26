/**
 * @file Mips32Simulator.cpp
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
 * - Mips32Simulator.cpp created
 */

#include <iostream>

#include "mips32/Mips32Simulator.hpp"


namespace mips32{

	const int Mips32Simulator::REGISTER_COUNT = 32;

	Mips32Simulator::Mips32Simulator( void* program, int size, int pc )
		:	m_code( (ubyte*) program),
			m_size( size ),
			m_data( 0 ),
			m_zero( m_r[reg_zero] ),
			m_at( m_r[reg_at] ),
			m_gp( m_r[reg_gp] ),
			m_sp( m_r[reg_sp] ),
			m_fp( m_r[reg_fp] ),
			m_ra( m_r[reg_jump] ),
			m_pc( pc )
	{
		// Variable Registers
		m_v[0] = &m_r[2];   m_v[1] = &m_r[3];

		// Argument Registers
		m_a[0] = &m_r[4];   m_a[1] = &m_r[5];
		m_a[2] = &m_r[6];   m_a[3] = &m_r[7];

		// Temp Registers
		m_t[0] = &m_r[ 8];  m_t[1] = &m_r[ 9];
		m_t[2] = &m_r[10];  m_t[3] = &m_r[11];
		m_t[4] = &m_r[12];  m_t[5] = &m_r[13];
		m_t[6] = &m_r[14];  m_t[7] = &m_r[15];
		m_t[8] = &m_r[24];  m_t[9] = &m_r[25];

		// Saved Registers
		m_s[0] = &m_r[16];  m_s[1] = &m_r[17];
		m_s[2] = &m_r[18];  m_s[3] = &m_r[19];
		m_s[4] = &m_r[20];  m_s[5] = &m_r[21];
		m_s[6] = &m_r[22];  m_s[7] = &m_r[23];
		m_s[8] = &m_r[30];

		// Kernel Registers
		m_k[0] = &m_r[26];  m_k[1] = &m_r[27];
	}

	Mips32Simulator::~Mips32Simulator(){

	}

	//--------------------------------------------------------------------------

	void Mips32Simulator::fetch(){
		ubyte* ptr = m_code;
		m_data = *((const u32*) (ptr + m_pc));
	}

	void Mips32Simulator::decode(){
		u32 instr = m_data;

		u32 opcode = (instr & bits_op) >> 26;

		// Determine instruction type
		switch(opcode){
		// Jump Instructions
		case op_j:
		case op_jal:
		case op_trap:
			m_instruction.type = type_j_instruction;
			break;
		// Register Instructions
		case op_r_logic:
		case op_r_proc:
			m_instruction.type = type_r_instruction;
			break;
		// Immediate Instructions
		case op_beq:
		case op_bne:
		case op_blez:
		case op_bgtz:
		case op_addi:
		case op_addui:
		case op_slti:
		case op_sltiu:
		case op_andi:
		case op_ori:
		case op_xori:
		case op_lui:
		case op_llo:
		case op_lhi:
		case op_lb:
		case op_lh:
		case op_lw:
		case op_lbu:
		case op_lhu:
		case op_sb:
		case op_sh:
		case op_sw:
			m_instruction.type = type_i_instruction;
			break;
		default:
			break;
		}

		// Decode into various parts
		switch(m_instruction.type){
		case type_r_instruction:
			m_instruction.r.opcode   = opcode;
			m_instruction.r.rs       = (instr & bits_rs) >> 21;
			m_instruction.r.rt	     = (instr & bits_rt) >> 16;
			m_instruction.r.rd	     = (instr & bits_rd) >> 11;
			m_instruction.r.shift    = (instr & bits_shf)  >> 6;
			m_instruction.r.function = (instr & bits_fnc);
			break;
		case type_i_instruction:
			m_instruction.i.opcode    = opcode;
			m_instruction.i.rs        = (instr & bits_rs) >> 21;
			m_instruction.i.rt	      = (instr & bits_rt) >> 16;
			m_instruction.i.immediate	= (instr & bits_imm);
			break;
		case type_j_instruction:
			m_instruction.j.opcode = opcode;
			m_instruction.j.target = (instr & bits_jmp);
			break;
		}

	}

	void Mips32Simulator::execute(){

		switch(m_instruction.type){
		case type_j_instruction:
			exec_j_instruction();
			break;
		case type_i_instruction:
			exec_i_instruction();
			break;
		case type_r_instruction:
			exec_r_instruction();
			break;
		}
	}

	void Mips32Simulator::step(){
		m_pc += 4;
	}

	void Mips32Simulator::print_registers() const{
		for( int i = 0; i < REGISTER_COUNT; ++i){
			printf("%02d: %08X ", i, m_r[i].u);
			if((1+i)%8==0)
				printf("\n");
		}
	}

	void Mips32Simulator::clear_registers(){
		for( int i = 0; i < 32; ++i ){
			m_r[i].u = 0;
		}
	}

	//--------------------------------------------------------------------------

	void Mips32Simulator::exec_r_instruction(){
		r_instruction& instr = m_instruction.r;

		union{
			u64 mult_uresult;
			s64 mult_sresult;
		};

		if( instr.opcode == op_r_logic ){

			switch( m_instruction.r.function ){

			//------------------------------------------------------------------------
			// Shift Operation
			//------------------------------------------------------------------------

			case func_sll: // $d = $t << a
				m_r[ instr.rd ].u = m_r[ instr.rt ].u << instr.shift;
				break;
			case func_srl: // $d = $t >> a
				m_r[ instr.rd ].u = m_r[ instr.rt ].u >> instr.shift;
				break;
			case func_sra: // $d = $t >>> a
				// TODO: Implement arithmetic shift
				m_r[ instr.rd ].u = m_r[ instr.rt ].u >> instr.shift;
				break;

			//------------------------------------------------------------------------
			// Jump Operation
			//------------------------------------------------------------------------

			case func_jr: // pc = $s
				m_pc = m_r[ instr.rs ].u;
				break;
			case func_jalr:
				m_ra.u = m_pc;
				m_pc += m_r[ instr.rs ].u;
				break;

			//------------------------------------------------------------------------
			// Move Operation
			//------------------------------------------------------------------------

			case func_mfhi: // $d = hi
				m_r[ instr.rd ].u = m_hi.u;
				break;
			case func_mthi: // hi = $s
				m_hi.u = m_r[ instr.rs ].u;
				break;
			case func_mflo: // $d = lo
				m_r[ instr.rd ].u = m_lo.u;
				break;
			case func_mtlo: // lo = $s
				m_lo.u = m_r[ instr.rs ].u;
				break;

			//------------------------------------------------------------------------
			// Math Operations
			//------------------------------------------------------------------------

			case func_mult: // hi:lo = $s * $t
				mult_sresult = m_r[ instr.rs ].s * m_r[ instr.rt ].s;
				m_hi.u = (mult_uresult >> 32);
				m_lo.u = mult_uresult & 0xffffffff;
				break;
			case func_multu: // hi:lo = $s * $t
				mult_uresult = m_r[ instr.rs ].u * m_r[ instr.rt ].u;
				m_hi.u = (mult_uresult >> 32);
				m_lo.u = mult_uresult & 0xffffffff;
				break;
			case func_div:  // lo = $s / $t; hi = $s % $t
				m_hi.s = m_r[ instr.rs ].s / m_r[ instr.rt ].s;
				m_lo.s = m_r[ instr.rs ].s % m_r[ instr.rt ].s;
				break;
			case func_divu: // lo = $s / $t; hi = $s % $t
				m_hi.u = m_r[ instr.rs ].u / m_r[ instr.rt ].u;
				m_lo.u = m_r[ instr.rs ].u % m_r[ instr.rt ].u;
				break;
			case func_add:  // $d = $s + $t
				m_r[ instr.rd ].s = m_r[ instr.rs ].s + m_r[ instr.rt ].s;
				break;
			case func_addu: // $d = $s + $t
				m_r[ instr.rd ].u = m_r[ instr.rs ].u + m_r[ instr.rt ].u;
				break;
			case func_sub:  // $d = $s - $t
				m_r[ instr.rd ].s = m_r[ instr.rs ].s - m_r[ instr.rt ].s;
				break;
			case func_subu: // $d = $s - $t
				m_r[ instr.rd ].u = m_r[ instr.rs ].u - m_r[ instr.rt ].u;
				break;
			case func_and:  // $d = $s & $t
				m_r[ instr.rd ].u = m_r[ instr.rs ].u & m_r[ instr.rt ].u;
				break;

			//------------------------------------------------------------------------
			// Bitwise Operations
			//------------------------------------------------------------------------

			case func_or:   // $d = $s | $t
				m_r[ instr.rd ].u = m_r[ instr.rs ].u | m_r[ instr.rt ].u;
				break;
			case func_xor:  // $d = $s ^ $t
				m_r[ instr.rd ].u = m_r[ instr.rs ].u ^ m_r[ instr.rt ].u;
				break;
			case func_nor:  // $d = ~($s | $t)
				m_r[ instr.rd ].u = ~(m_r[ instr.rs ].u | m_r[ instr.rt ].u);
				break;

			//------------------------------------------------------------------------
			// Comparison Operations
			//------------------------------------------------------------------------

			case func_slt:  // $d = $s < $t
				m_r[ instr.rd ].u = ((m_r[ instr.rs ].s < m_r[ instr.rt ].s) ? 1 : 0);
				break;
			case func_sltu: // $d = $s < $t
				m_r[ instr.rd ].u = ((m_r[ instr.rs ].u < m_r[ instr.rt ].u) ? 1 : 0);
				break;

			default:
				break;

			}
		}else if( instr.opcode == op_r_proc ){
			// todo: add coprocessor
		}
	}

	void Mips32Simulator::exec_i_instruction(){
		i_instruction& instr = m_instruction.i;

		union{
			u8*  ptr8;
			u16* ptr16;
			u32* ptr32;
		};

		switch( instr.opcode ){

		//------------------------------------------------------------------------
		// Immediate Branch Operations
		//------------------------------------------------------------------------

		case op_beq: // if ($s == $t) pc += i << 2
			if( m_r[ instr.rs ].u == m_r[ instr.rt ].u ){
				m_pc += instr.immediate << 2;
			}
			break;
		case op_bne: // if ($s != $t) pc += i << 2
			if( m_r[ instr.rs ].u != m_r[ instr.rt ].u ){
				m_pc += instr.immediate << 2;
			}
			break;
		case op_blez: // if ($s <= 0) pc += i << 2
			if( m_r[ instr.rs ].u <= m_r[ instr.rt ].u ){
				m_pc += instr.immediate << 2;
			}
			break;
		case op_bgtz: // if ($s > 0) pc += i << 2
			if( m_r[ instr.rs ].u > m_r[ instr.rt ].u ){
				m_pc += instr.immediate << 2;
			}
			break;

		//------------------------------------------------------------------------
		// Immediate Arithmetic Operations
		//------------------------------------------------------------------------

		case op_addi:  // $d = $s + SE(i)
			m_r[ instr.rt ].s = m_r[ instr.rs ].s + (s32) sign_extend<16>(instr.immediate);
			break;
		case op_addui: // $d = $s + SE(i)
			m_r[ instr.rt ].s = m_r[ instr.rs ].u + (s32) sign_extend<16>(instr.immediate);
			break;

		//------------------------------------------------------------------------
		// Immediate Shift Operations
		//------------------------------------------------------------------------

		case op_slti:  // $t = ($s < SE(i))
			m_r[ instr.rt ].s = ((m_r[ instr.rs ].s < (s32) sign_extend<16>(instr.immediate)) ? 1 : 0);
			break;
		case op_sltiu: // $t = ($s < SE(i))
			m_r[ instr.rt ].u = ((m_r[ instr.rs ].u < (u32) sign_extend<16>(instr.immediate)) ? 1 : 0);
			break;

		//------------------------------------------------------------------------
		// Immediate Bitwise Operations
		//------------------------------------------------------------------------

		case op_andi:  // $t = $s & ZE(i)
			m_r[ instr.rt ].u = m_r[ instr.rs ].u & (u32) zero_extend<16>(instr.immediate);
			break;
		case op_ori:   // $t = $s | ZE(i)
			m_r[ instr.rt ].u = m_r[ instr.rs ].u | (u32) zero_extend<16>(instr.immediate);
			break;
		case op_xori:  // $d = $s ^ ZE(i)
			m_r[ instr.rt ].u = m_r[ instr.rs ].u ^ (u32) zero_extend<16>(instr.immediate);
			break;

		case op_lui:

			// Can't find what this is supposed to do?

			break;

		//------------------------------------------------------------------------
		// Load operations
		//------------------------------------------------------------------------

		case op_llo:  // LL ($t) = i
			m_r[ instr.rt ].u &= 0x0000ffff;
			m_r[ instr.rt ].u |= (instr.immediate << 16);
			break;
		case op_lhi:  // LH ($t) = i
			m_r[ instr.rt ].u &= 0xffff0000;
			m_r[ instr.rt ].u |= instr.immediate;
			break;
		case op_lb:   // $t = SE (MEM [$s + i]:1)
			ptr8 = m_code + m_r[ instr.rs ].s + instr.immediate;
			m_r[ instr.rt ].s = (s8) sign_extend<8>( *ptr8 );
			break;
		case op_lh:   // $t = SE (MEM [$s + i]:2)
			ptr16 = (u16*) (m_code + m_r[ instr.rs ].s + instr.immediate);
			m_r[ instr.rt ].s = (s16) sign_extend<16>( *ptr16 );
			break;
		case op_lw:   // $t = MEM [$s + i]:4
			ptr32 = (u32*) (m_code + m_r[ instr.rs ].s + instr.immediate);
			m_r[ instr.rt ].u = *ptr32;
			break;
		case op_lbu:  // $t = ZE (MEM [$s + i]:1)
			ptr8 = m_code + m_r[ instr.rs ].s + instr.immediate;
			m_r[ instr.rt ].u = (u8) zero_extend<8>( *ptr8 );
			break;
		case op_lhu:  // $t = ZE (MEM [$s + i]:2)
			ptr8 = m_code + m_r[ instr.rs ].s + instr.immediate;
			m_r[ instr.rt ].u = (u16) zero_extend<16>( *ptr16 );
			break;

		//----------------------------------------------------------------------
		// Store operations
		//----------------------------------------------------------------------

		case op_sb:   // MEM [$s + i]:1 = $t
			ptr8 = m_code + m_r[ instr.rs ].s + instr.immediate;
			*ptr8 = m_r[ instr.rt ].u & 0xff;
			break;
		case op_sh:   // MEM [$s + i]:2 = $t
			ptr16 = (u16*) (m_code + m_r[ instr.rs ].s + instr.immediate);
			*ptr16 = m_r[ instr.rt ].u & 0xffff;
			break;
		case op_sw:   // MEM [$s + i]:4 = $t
			ptr32 = (u32*) (m_code + m_r[ instr.rs ].s + instr.immediate);
			*ptr8 = m_r[ instr.rt ].u;
			break;
		}

	}

	void Mips32Simulator::exec_j_instruction(){
		j_instruction& instr = m_instruction.j;

		switch( instr.opcode ){

		//------------------------------------------------------------------------
		// Jump operations
		//------------------------------------------------------------------------

		case op_j:   // pc += i << 2
			m_pc += instr.target << 2;
			break;
		case op_jal: // $31 = pc; pc += i << 2
			m_ra.u = m_pc;
			m_pc += instr.target << 2;
			break;

		//------------------------------------------------------------------------
		// Trap Operation
		//------------------------------------------------------------------------

		case op_trap: // OS dependent trap instruction
			exec_trap();
			break;
		}
	}

	void Mips32Simulator::exec_trap(){

	}

} // namespace mips32

