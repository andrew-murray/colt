#ifndef __COLT__HELP__HPP__
#define __COLT__HELP__HPP__

#include <string>

#include <boost/optional.hpp>
#include <colt/command.hpp>

namespace colt {
	namespace help {
				
		inline const std::string pad_to(const std::string& a, const size_t len)
		{
			if(a.size() > len){
				throw std::invalid_argument(std::string(__FUNCTION__) + " string " + a + " is greater than length " + std::to_string( len ) );
			}
			return a + std::string(len - a.size(), ' ');
		}

		inline std::vector<std::string> normalise(const std::vector<std::string>& input_vector, const boost::optional<size_t>& min_length)
		{
			if(input_vector.size() == 0)
			{
				return std::vector<std::string>();
			}
			auto max_length_string = std::max_element(
				input_vector.begin(), 
				input_vector.end(), 
				[](const std::string& a, const std::string& b){
					return a.size() > b.size();
				}
			);
			const size_t string_length = bool(min_length) ? std::max(max_length_string->size(), *min_length)
														  : max_length_string->size();	 
			std::vector<std::string> output_vector;
			output_vector.reserve( input_vector.size() );
			std::transform(
				input_vector.begin(),
				input_vector.end(), 
				std::back_inserter( output_vector ),
				[&](const std::string& a){ return pad_to(a, string_length); }
			);
			return output_vector;
		}

		inline std::string contents(const std::vector<std::unique_ptr<colt::command>>& commands)
		{
			std::vector<std::string> command_names;
			std::vector<std::string> command_descriptions;
			for(auto comm_it = commands.begin(); comm_it != commands.end(); ++comm_it)
			{
				const std::unique_ptr<colt::command>& command_pointer = *comm_it;
				const colt::command& command_instance = *command_pointer;
				command_names.push_back(command_instance.name());
				command_descriptions.push_back(command_instance.description());
			}
			
			/*
				this will deal with padding out command names
				it won't deal with splitting description over multiple lines
				TODO
			*/
			command_names = normalise(command_names, 14);
			command_descriptions = normalise(command_descriptions, boost::none);

			std::stringstream output_stream;
			const std::string indent(2,' ');
			output_stream << "available commands:\n\n";
			for(int i = 0; i < commands.size(); ++i)
			{
				output_stream 
					<< indent 
					<< command_names[i]  
					<< command_descriptions[i] << '\n';
			}
			return output_stream.str();
		}
	}
}















#endif