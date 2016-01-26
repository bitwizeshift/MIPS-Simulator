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
#ifndef INCLUDE_SIMULATOR_HPP_
#define INCLUDE_SIMULATOR_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

///
///
///
///
///
template<class In>
class Simulator{

	//--------------------------------------------------------------------------
	// Public Member Types
	//--------------------------------------------------------------------------
public:

	typedef In instruction_type;

	//--------------------------------------------------------------------------
	// Constructor
	//--------------------------------------------------------------------------
public:

	virtual ~Simulator() = 0;

	//--------------------------------------------------------------------------
	// Public API
	//--------------------------------------------------------------------------
public:

	/// Run the program
	void run();

	/// Decodes the instruction into its parts
	virtual void decode( const void* instruction ) = 0;

	/// Executes the desired instruction
	virtual void execute() = 0;

	/// Increases the program counter by 1 instruction
	virtual void step() = 0;

	/// Prints the contents of the registers
	virtual void printRegisters() const = 0;

	/// clears the contents of the registers
	virtual void clearRegisters() = 0;
};

template<class In> inline Simulator<In>::~Simulator(){}

template<class In>
inline void Simulator<In>::run(){

}


#endif /* INCLUDE_SIMULATOR_HPP_ */
