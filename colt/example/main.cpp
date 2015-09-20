#include "colt/main.hpp"

int main(int argc, const char** argv)
{
	std::vector<std::unique_ptr<colt::command>> command_vector;
	command_vector.emplace_back( new example_command );
	try
	{
		return colt::main(argc, argv, command_vector);
	}
	catch(...)
	{
		// I can handle exceptions here, but 
		// maybe it's better to handle known exceptions
		// within my functions?
		std::cerr 
			<< "A serious but unknown error has occurred.\n" 
			<< "Let's never speak of this again."
			<< std::endl;
		const int command_error = 1;
		return command_error;
	}
}