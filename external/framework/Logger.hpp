/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <fstream>
#include <string>

#include <Config.hpp>

namespace CGF_NAMESPACE
{
	class Logger final
	{
	public:
		enum prefix_t
		{
			NONE = -1,
			INFO = 0,
			WARNING,
			ERROR
		};

		enum output_t
		{
			FILE = 0,
			CONSOLE,
			BOTH
		};

	private:
		static std::ofstream file;

	public:
		Logger() = delete;

		static void initialize();
		static void shutdown();

		static void log( const std::string& msg, prefix_t prefix = INFO, output_t output = BOTH );
	};
}
