/**
 * @file Simulator.hpp
 *
 * @todo Add description
 *
 * @author Matthew Rodusek (matthew.rodusek@gmail.com)
 * @date   Jan 24, 2016
 *
 */
#ifndef MIPS32_MIPS32SIMULATOR_HPP_
#define MIPS32_MIPS32SIMULATOR_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include "../datatypes.hpp"
#include "../Simulator.hpp"

#include "instructions.hpp"

namespace mips32{

	class Mips32Simulator : public Simulator<Instruction>{

		//--------------------------------------------------------------------------
		// Constructor
		//--------------------------------------------------------------------------
	public:

		Mips32Simulator( void* program, int size, int pc = 0 );

		virtual ~Mips32Simulator();

		//--------------------------------------------------------------------------
		// Public API
		//--------------------------------------------------------------------------
	public:

		/// Decodes the instruction into its parts
		virtual void decode( const void* instruction );

		/// Executes the desired instruction
		virtual void execute();

		/// Increases the program counter by 1 instruction
		virtual void step();

		/// Prints the contents of the registers
		virtual void printRegisters() const;

		/// clears the contents of the registers
		virtual void clearRegisters();

		//--------------------------------------------------------------------------
		// Private Members
		//--------------------------------------------------------------------------
	private:

		static const int REGISTER_COUNT;

		ubyte* m_code;
		u32    m_size;

		Instruction m_instruction; //!< The current instruction being executed
		Word32  m_f[16];       //!< Floating point registers
		Word32  m_r[32];       //!< The 32 mips registers
		Word32  m_hi;          //!< HI register for multiply/divide
		Word32  m_lo;          //!< LO register for multiply/divide
		Word32& m_zero;        //!< The zero register $0
		Word32& m_at;          //!< Assembler Temporary
		Word32& m_gp;          //!< Global pointer $28
		Word32& m_sp;          //!< Stack pointer $29
		Word32& m_fp;          //!< Frame Pointer $30
		Word32& m_ra;          //!< The jump register $31
		const Word32* m_v[2];  //!< Value registers
		const Word32* m_a[4];  //!< Argument registers
		const Word32* m_t[10]; //!< Temporary registers
		const Word32* m_s[9];  //!< Saved registers
		const Word32* m_k[2];  //!< Kernel registers
		u32     m_pc;          //!< The program counter

		//--------------------------------------------------------------------------
		// Private Methods
		//--------------------------------------------------------------------------
	private:

		void exec_r_instruction();
		void exec_i_instruction();
		void exec_j_instruction();
		void exec_trap();

	};



} // namespace mips32

#endif /* MIPS32_MIPS32SIMULATOR_HPP_ */
