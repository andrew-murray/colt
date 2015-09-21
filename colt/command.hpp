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

#endif