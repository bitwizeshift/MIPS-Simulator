/**
 * @file main.cpp
 *
 * @todo Add description
 *
 * @author Matthew Rodusek (matthew.rodusek@gmail.com)
 * @date   Jan 24, 2016
 *
 */

#include <string>
#include <iostream>

#include <boost/program_options.hpp>
#include <string>

//----------------------------------------------------------------------------
// Static Constants
//----------------------------------------------------------------------------

static boost::program_options::options_description g_desc("Options");
static boost::program_options::variables_map       g_options;

///
/// @param argc
/// @param argv
///
void parse_options( int argc, char** argv ){
	using namespace boost::program_options;

	// Add all mips options
	g_desc.add_options()
		("help,h", "Display help message")
		("version,v", "Display simulator version information")
		("run,r","Run the specified MIPS bin file")
		(",o", value<std::string>()->default_value("a.bin"), "Place the output file into <arg>")
		("arch", value<std::string>()->default_value("mips32"), "The mips architecture type")
		;

	store(parse_command_line(argc, argv, g_desc), g_options);
	notify(g_options);
}


int main( int argc, char** argv ){
	parse_options( argc, argv );

	if( g_options.count("help") ){
		std::cout << "Usage: " << argv[0] << " [options] file...\n";
		std::cout << g_desc << "\n";
	}



	return 0;
}
