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

namespace mips32{

	const int Mips32Simulator::REGISTER_COUNT = 32;

	Mips32Simulator::Mips32Simulator( void* program, int size, int pc )
		:	m_zero(m_registers[0]),
			m_at(m_registers[1]),
			m_gp(m_registers[28]),
			m_sp(m_registers[29]),
			m_fp(m_registers[30]),
			m_ra(m_registers[31]),
			m_pc(pc)
	{
		// Variable Registers
		m_v[0] = &m_registers[2];   m_v[1] = &m_registers[3];

		// Argument Registers
		m_a[0] = &m_registers[4];   m_a[1] = &m_registers[5];
		m_a[2] = &m_registers[6];   m_a[3] = &m_registers[7];

		// Temp Registers
		m_t[0] = &m_registers[ 8];  m_t[1] = &m_registers[ 9];
		m_t[2] = &m_registers[10];  m_t[3] = &m_registers[11];
		m_t[4] = &m_registers[12];  m_t[5] = &m_registers[13];
		m_t[6] = &m_registers[14];  m_t[7] = &m_registers[15];
		m_t[8] = &m_registers[24];  m_t[9] = &m_registers[25];

		// Saved Registers
		m_s[0] = &m_registers[16];  m_s[1] = &m_registers[17];
		m_s[2] = &m_registers[18];  m_s[3] = &m_registers[19];
		m_s[4] = &m_registers[20];  m_s[5] = &m_registers[21];
		m_s[6] = &m_registers[22];  m_s[7] = &m_registers[23];
		m_s[8] = &m_registers[30];

		// Kernel Registers
		m_k[0] = &m_registers[26];  m_k[1] = &m_registers[27];
	}

	Mips32Simulator::~Mips32Simulator(){

	}

	//--------------------------------------------------------------------------

	void Mips32Simulator::decode( const void* instruction ){
		u32 instr = *((const u32*) instruction);

		u32 opcode = (instr & bits_op) >> 26;

		// Determine instruction type
		switch(opcode){
		// Register Instructions
		case op_sll:
		case op_srl:
		case op_add:
		case op_addu:
		case op_sub:
		case op_subu:
		case op_and:
		case op_or:
		case op_nor:
		case op_slt:
		case op_sltu:
		case op_div:
		case op_divu:
		case op_mul:
		case op_mulu:
			m_instruction.type = r_type_instruction;
			break;
		// Immediate Instructions
		case op_beq:
		case op_bne:
		case op_addi:
		case op_addui:
		case op_andi:
		case op_divi:
		case op_diviu:
		case op_muli:
		case op_muliu:
		case op_lw:
		case op_sw:
			m_instruction.type = i_type_instruction;
			break;
		// Jump Instructions
		case op_jump:
		case op_jumpl:
		case op_jumpr:
			m_instruction.type = j_type_instruction;
			break;
		default:
			break;
		}

		// Decode into various parts
		switch(m_instruction.type){
		case r_type_instruction:
			m_instruction.r.opcode   = opcode;
			m_instruction.r.rs       = (instr & bits_rs) >> 21;
			m_instruction.r.rt	     = (instr & bits_rt) >> 16;
			m_instruction.r.rd	     = (instr & bits_rd) >> 11;
			m_instruction.r.shift    = (instr & bits_shf)  >> 6;
			m_instruction.r.function = (instr & bits_fnc);
			break;
		case i_type_instruction:
			m_instruction.i.opcode    = opcode;
			m_instruction.i.rs        = (instr & bits_rs) >> 21;
			m_instruction.i.rt	      = (instr & bits_rt) >> 16;
			m_instruction.i.immediate	= (instr & bits_imm);
			break;
		case j_type_instruction:
			m_instruction.j.opcode = opcode;
			m_instruction.j.target = (instr & bits_jmp);
			break;
		}

	}

	void Mips32Simulator::execute(){


		// Do the actual operation
	}

	void Mips32Simulator::step(){
	}

	void Mips32Simulator::printRegisters() const{
		for( int i = 0; i < REGISTER_COUNT; ++i){
			printf("%02d: %08X ", i, m_registers[i].u);
			if((1+i)%8==0)
				printf("\n");
		}
	}

	void Mips32Simulator::clearRegisters(){
		for( int i = 0; i < 32; ++i ){
			m_registers[i].u = 0;
		}
	}

} // namespace mips32

