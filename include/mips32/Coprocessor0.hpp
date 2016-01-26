/**
 * @file Coprocessor0.hpp
 *
 * @todo Add description
 *
 * @author Matthew Rodusek (matthew.rodusek@gmail.com)
 * @date   Jan 26, 2016
 *
 */

/*
 * Change Log:
 *
 * Jan 26, 2016: 
 * - Coprocessor0.hpp created
 */
#ifndef INCLUDE_MIPS32_COPROCESSOR0_HPP_
#define INCLUDE_MIPS32_COPROCESSOR0_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include "../datatypes.hpp"
#include "instructions.hpp"

namespace mips32{

	struct Coprocessor0{
		u32 context;
		u32 random;
		u32 entryLo0;
		u32 entryLo1;
		u32 context;
		u32 pageMask;
		u32 wired;
		u32 entryHi;

	};

}




#endif /* INCLUDE_MIPS32_COPROCESSOR0_HPP_ */
