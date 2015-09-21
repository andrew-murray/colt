#ifndef __COLT__COMMAND__HPP__
#define __COLT__COMMAND__HPP__

#include <boost/program_options.hpp>

#include <iostream>

namespace colt {
	class command {
	public:


		virtual std::string name() const = 0;
		virtual std::string description() const = 0;

		virtual bool allow_unregistered() const { return false; };

		virtual boost::program_options::positional_options_description positional_arguments() const = 0;
		virtual boost::program_options::options_description named_arguments() const = 0;

		virtual int operator()(const boost::program_options::variables_map& inputs) const  = 0;

	};
}

class example_command : public colt::command 
{
	virtual std::string name() const { return "example"; }
	virtual std::string description() const { return "I don't really exist. but I am a fucking long string and I better be split up properly"; }

	virtual bool allow_unregistered() const { return true; }

	virtual boost::program_options::positional_options_description positional_arguments() const {
		return boost::program_options::positional_options_description();
	}

	virtual boost::program_options::options_description named_arguments() const
	{
		auto t = boost::program_options::options_description("named");
		t.add_options()("arbitrary","no desc");
		return t;
	}
	
	virtual int operator()(const boost::program_options::variables_map& inputs) const
	{
		for(auto& var : inputs)
		{
			std::cout << var.first << ":" << var.second.as<std::string>() << std::endl;
		}
		return 0;
	}
};


#endif