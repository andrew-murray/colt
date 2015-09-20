#include <boost/program_options.hpp>

namespace po = boost::program_options;

#include "colt/command.hpp"

int main(int argc, const char* argv[])
{
	try{
		const char* command_argument = "command";


		po::options_description global("Global options");
		global.add_options()
			(command_argument, po::value<std::string>(), "command to execute")
			("subargs", po::value<std::vector<std::string> >(), "Arguments for command");

		// add positional arguments 
		// command is limited to one token
		// and subargs can accept unlimited tokens
		po::positional_options_description positional_arguments;
		positional_arguments.add("command", 1)
							.add("subargs", -1);
	
		po::parsed_options parsed = po::command_line_parser(argc, argv)
			.options(global)
			.positional(positional_arguments)
			.allow_unregistered()
			.run();
	
		po::variables_map variable_map;
		po::store(parsed, variable_map);
	
		if(variable_map.count(command_argument) == 0)
		{
			// no arguments provided

			// output help listing commands
			// (note: this can't be the normal boost::po help)
			return 0;
		}


		const std::string selected_command = variable_map[command_argument].as<std::string>();

		auto make_unique_command = [](colt::command* implicitly_converted)
		{
			return std::unique_ptr<colt::command>( implicitly_converted );
		};

		const std::unique_ptr<colt::command> available_commands[] = {
			make_unique_command( new example_command )
		};

		auto available_commands_end = available_commands + sizeof(available_commands) / sizeof(std::unique_ptr<colt::command>);

		auto found_command = std::find_if(
			available_commands, 
			available_commands_end,
			[&](const std::unique_ptr<colt::command>& comm){
				return comm->name() == selected_command;
			}
		);

		if( found_command == available_commands_end)
		{
			std::cout << "we don't recognize the command" << std::endl;
			// output help about not recognizing selected_command
			return 1;
		}
	
		std::vector<std::string> collected_arguments = po::collect_unrecognized(parsed.options, po::include_positional);
		// remove command argument
		collected_arguments.erase(collected_arguments.begin());

		const std::unique_ptr<colt::command>& command_object = *found_command;

		po::variables_map sub_variables;
		auto parser = po::command_line_parser(collected_arguments)
				.options(command_object->named_arguments())
				.positional(command_object->positional_arguments());
		if( command_object->allow_unregistered() )
		{
			parser = parser.allow_unregistered();
		}
		po::store(parser.run(), sub_variables);
		(*command_object)(sub_variables);
	}
	catch(std::exception& e)
	{
		std::cerr << "Uncaught exception : " << e.what() << std::endl;
	}

}