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

		Logger() = delete;

		static void Initialize();
		static void Shutdown();

		static void Log( const std::string& msg, prefix_t prefix = INFO, output_t output = BOTH );

	private:
		static std::ofstream file;
	};
}
