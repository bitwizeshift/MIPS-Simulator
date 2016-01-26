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
#include <fstream>

#include <boost/program_options.hpp>
#include <string>
#include <vector>

#include <version.hpp>
#include <Simulator.hpp>
#include <mips32/Mips32Simulator.hpp>

//----------------------------------------------------------------------------
// Static Constants
//----------------------------------------------------------------------------

namespace po = boost::program_options;
typedef std::vector< std::string > string_vector;

int main( int argc, char** argv ){

	// Handle argument options

	po::variables_map vm;
	po::options_description cmds("Options");

	cmds.add_options()
		("help,h", "Display help message")
		("version,v", "Display simulator version information")
		("run,r", po::value<std::string>(), "Run the specified MIPS bin file")
		("arch", po::value<std::string>()->default_value("mips32"), "The mips architecture type")
		("output-file,o", po::value<std::string>()->default_value("a.bin"), "Place the output file into <arg>")
		("input-file,i", po::value< string_vector >(),"Input files to assemble")
		("stepped,s", "Stepped run")
		("verbose", "Verbose register printing per step")
	;

	po::positional_options_description pd;
	pd.add("input-file", -1);

	po::parsed_options parsed = po::command_line_parser(argc, argv).options(cmds).allow_unregistered().positional(pd).run();
	po::store(parsed, vm);
	po::notify(vm);

	//--------------------------------------------------------------------------

	// Help
	if(vm.count("help")){
		std::cout << cmds << std::endl;
		return 0;
	}

	//--------------------------------------------------------------------------

	// Version
	if(vm.count("version")){
		std::cout << "MIPS-Simulator version " VERSION_STRING << '\n';
		return 0;
	}

	//--------------------------------------------------------------------------

	try{
		// Assemble
		if(vm.count("input-file")){
			std::string output = vm["output-file"].as< std::string >();
			std::string arch   = vm["arch"].as< std::string >();

			string_vector values(vm["input-file"].as< string_vector>() );

			// do: assemble
		}

		//--------------------------------------------------------------------------

		if(vm.count("run")){
			std::string runfile = vm["run"].as< std::string >();
			std::string arch    = vm["arch"].as< std::string >();
			bool is_stepped     = vm.count("stepped") > 0 ? true : false;
			bool is_verbose     = vm.count("verbose") > 0 ? true : false;

			std::ifstream file( runfile.c_str(), std::ios::binary | std::ios::ate );

			if( !file.is_open() ){
				std::cout << "Error opening file: \"" << runfile << "\"";
				return 1;
			}

			std::streamsize size = file.tellg();
			file.seekg(0, std::ios::beg);

			std::vector<char> buffer(size);
			if (file.read(buffer.data(), size)){
				// Construct the buffer
				mips32::Mips32Simulator sim( buffer.data(), buffer.size(), 0 );

				sim.run( is_stepped, is_verbose );
			}else{

			}
		}

	}catch(std::exception& e){
		std::cout << "Error: " << e.what() << '\n';
	}

	return 0;
}
