/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <Logger.hpp>

namespace CGF_NAMESPACE
{
	std::ofstream Logger::file;


	void Logger::Initialize()
	{
		if ( !Logger::file.is_open() )
		{
			Logger::file.open( LOG_FILE_PATH );
			Logger::Log( "Logger initialized!" );
		} else
			Logger::Log( "Logger already initialized!" );
	}

	void Logger::Shutdown()
	{
		Logger::Log( "Logger shutdown!" );
		Logger::file.close();
	}

	void Logger::Log( const std::string& msg, prefix_t prefix, output_t output )
	{
		if ( output == FILE || output == BOTH )
		{
			if ( prefix != NONE )
				Logger::file << "[" << LOGGER_PREFIX[prefix] << "]";

			Logger::file << msg << "\n";
		}

		if ( output == CONSOLE || output == BOTH )
		{
			if ( prefix != NONE )
				LOGGER_STREAM << "[" << LOGGER_PREFIX[prefix] << "]";

			LOGGER_STREAM << msg << "\n";
		}
	}
}