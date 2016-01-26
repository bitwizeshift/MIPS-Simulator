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

		Instruction m_instruction; //!< The current instruction being executed
		Word32  m_fregisterss[16]; //!< Floating point registers
		Word32  m_registers[32];   //!< The 32 mips registers
		Word32& m_zero;            //!< The zero register $0
		Word32& m_gp;              //!< Global pointer
		Word32& m_sp;              //!< Stack pointer
		Word32& m_fp;              //!< Frame Pointer $30
		Word32& m_ra;              //!< The jump register $31
		Word32& m_at;              //!< Assembler Temporary
		Word32* const m_v[2];      //!< Value registers
		Word32* const m_a[4];      //!< Argument registers
		Word32* const m_t[10];     //!< Temporary registers
		Word32* const m_s[9];      //!< Saved registers
		Word32* const m_k[2];      //!< Kernel registers
		u32     m_pc;              //!< The program counter

	};



} // namespace mips32

#endif /* MIPS32_MIPS32SIMULATOR_HPP_ */
