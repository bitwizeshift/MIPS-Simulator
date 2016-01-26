/**
 * @file Simulator.hpp
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
 * - Simulator.hpp created
 */
#ifndef SIMULATOR_HPP_
#define SIMULATOR_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

namespace mips32{

	////////////////////////////////////////////////////////////////////////////
	/// @class Simulator
	///
	///
	///
	////////////////////////////////////////////////////////////////////////////
	template<class In>
	class Simulator{

		//------------------------------------------------------------------------
		// Public Member Types
		//------------------------------------------------------------------------
	public:

		typedef In instruction_type;

		//------------------------------------------------------------------------
		// Constructor
		//------------------------------------------------------------------------
	public:

		virtual ~Simulator() = 0;

		//------------------------------------------------------------------------
		// Run
		//------------------------------------------------------------------------
	public:

		/// Run the program
		void run( bool is_stepped, bool is_verbose );

		//------------------------------------------------------------------------
		// Public API
		//------------------------------------------------------------------------
	protected:

		/// Fetches the next instruction
		virtual void fetch() = 0;

		/// Decodes the instruction into its parts
		virtual void decode() = 0;

		/// Executes the desired instruction
		virtual void execute() = 0;

		/// Increases the program counter by 1 instruction
		virtual void step() = 0;

		/// Prints the contents of the registers
		virtual void print_registers() const = 0;

		/// clears the contents of the registers
		virtual void clear_registers() = 0;
	};

	template<class In> inline Simulator<In>::~Simulator(){}

	template<class In>
	inline void Simulator<In>::run( bool is_stepped, bool is_verbose ){
		bool is_halted = false;

		while(!is_halted){
			fetch();
			decode();
			execute();
			step();

			if( is_stepped ){
				// print instruction
				// step
			}
			if( is_verbose ){
				print_registers();
			}
		}
	}
}

#endif /* SIMULATOR_HPP_ */
