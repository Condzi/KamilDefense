/*
	The MIT License

	Copyright (c) 2017 PiGames ( https://github.com/PiGames )

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.
*/

#pragma once

#include <algorithm>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>

namespace pi
{
	/*
	===============================================================================
	Created by: Condzi
		Simple struct created for delivering messages about 'INIFile' class errors.

	===============================================================================
	*/
	struct ini_error_t
	{
		std::string what = "";
	};

	/*
	===============================================================================
	Created by: Condzi
		Class created for manipulating INI files. Almost every method has additional 
		parameter 'ini_error_t*' - it's a pointer to error message. For example if 
		Parse() method return false, the ini_error_t::what will contain information 
		about error.

	===============================================================================
	*/
	class INIFile final
	{
	public:
		INIFile() :
			loaded( false ),
			parsed( false )
		{}

		bool IsLoaded() const { return this->loaded; }
		bool IsParsed() const { return this->parsed; }

		bool LoadFromFile( const std::string& path, ini_error_t* errorOutput = nullptr );
		bool Parse( ini_error_t* errorOutput = nullptr );

		void Clear();

		bool GetBool( const std::string& section, const std::string& name, ini_error_t* errorOutput = nullptr );
		int GetInt( const std::string& section, const std::string& name, ini_error_t* errorOutput = nullptr );
		double GetDouble( const std::string& section, const std::string& name, ini_error_t* errorOutput = nullptr );
		std::string GetString( const std::string& section, const std::string& name, ini_error_t* errorOutput = nullptr );

	private:
		bool loaded;
		bool parsed;

		std::vector<std::string> rawData;
		//					<section name					<variable name, data>>
		std::unordered_map<std::string, std::unordered_map<std::string, std::string>> parsedString;
		std::unordered_map<std::string, std::unordered_map<std::string, int>> parsedInt;
		std::unordered_map<std::string, std::unordered_map<std::string, double>> parsedDouble;
		std::unordered_map<std::string, std::unordered_map<std::string, bool>> parsedBool;

	private:
		bool isInt( const std::string& value );
		bool isDouble( const std::string& value );
		bool isBool( const std::string& value );

		void clearMaps();
		void removeBlanks( std::string& str );
		void removeFirstBlanks( std::string& str );
		void removeEscapeSeq( std::string& str );
	};

	/*
	XXXXXXXXXX	==========	XXXXXXXXXX
	XXXXXXXXXX	DEFINITIONS	XXXXXXXXXX
	XXXXXXXXXX	==========	XXXXXXXXXX
	*/

	bool INIFile::LoadFromFile( const std::string& path, ini_error_t* errorOutput )
	{
		std::ifstream file( path );
		std::string temp = "";

		if ( !file.good() || !file.is_open() )
		{
			if ( errorOutput )
				errorOutput->what = "Cannot open file (" + path + ") \n";

			this->loaded = false;
			return false;
		}

		this->rawData.clear();

		while ( !file.eof() )
		{
			std::getline( file, temp );

			// Line is a comment or line is empty
			if ( ( temp.size() >= 1 && temp[0] == ';' ) ||
				( !temp.size() ) )
				continue;

			this->rawData.push_back( temp );
		}

		this->loaded = true;
		return true;
	}

	bool INIFile::Parse( ini_error_t* errorOutput )
	{
		this->parsed = false;

		this->clearMaps();

		std::string tempSectionName = "";
		int tempInt = 0;
		double tempDouble = 0;
		bool tempBool = 0;
		// name and value
		std::pair<std::string, std::string> data( "", "" );

		for ( auto& str : rawData )
		{
			// Removes \n etc from line
			this->removeEscapeSeq( str );

			// Line is section name
			if ( str.find( '[' ) != std::string::npos || str[str.size() - 1] == ']' )
			{
				this->removeBlanks( str );
				// cutting from [ to ] (size - 1 = last string char, size - 2 is string without last char)
				tempSectionName = str.substr( str.find( '[' ) + 1, str.size() - 2 );

				continue;
			}

			// If no section name
			if ( tempSectionName == "" )
			{
				if ( errorOutput )
					errorOutput->what = "No section name \n";

				return false;
			}

			// If there is no '=' in "value data" (should be "value = data")
			if ( str.find( '=' ) == std::string::npos )
			{
				if ( errorOutput )
					errorOutput->what = "No '=' in data line \n";

				return false;
			}

			// value name is part before '=' (name = value)
			data.first = str.substr( 0, str.find( '=' ) );
			// "a b C" -> "abC"
			this->removeBlanks( data.first );

			// data part is after '=' (name = data)
			data.second = str.substr( str.find( '=' ) + 1 );
			// "   data" -> "data"
			this->removeFirstBlanks( data.second );

			if ( isInt( data.second ) )
			{
				tempInt = std::stoi( data.second );

				this->parsedInt[tempSectionName][data.first] = tempInt;

				continue;
			}

			if ( isDouble( data.second ) )
			{
				tempDouble = std::stod( data.second );

				this->parsedDouble[tempSectionName][data.first] = tempDouble;

				continue;
			}

			if ( isBool( data.second ) )
			{
				tempBool = ( data.second == "true" );

				this->parsedBool[tempSectionName][data.first] = tempBool;

				continue;
			}

			// We are assuming that if it's none of above types it must be string
			this->parsedString[tempSectionName][data.first] = data.second;
		}

		this->parsed = true;

		return true;
	}

	void INIFile::Clear()
	{
		this->rawData.clear();
		this->clearMaps();
	}

	bool INIFile::GetBool( const std::string& section, const std::string& name, ini_error_t* errorOutput )
	{
		if ( this->parsedBool.find( section ) == this->parsedBool.end() )
		{
			if ( errorOutput )
				errorOutput->what = "Cannot find bool section name (" + section + ") \n";

			return false;
		}

		if ( this->parsedBool[section].find( name ) == this->parsedBool[section].end() )
		{
			if ( errorOutput )
				errorOutput->what = "Cannot find bool in section " + section + " (" + name + ") \n";

			return false;
		}

		return this->parsedBool[section][name];
	}

	int INIFile::GetInt( const std::string& section, const std::string& name, ini_error_t * errorOutput )
	{
		if ( this->parsedInt.find( section ) == this->parsedInt.end() )
		{
			if ( errorOutput )
				errorOutput->what = "Cannot find int section name (" + section + ") \n";

			return 0;
		}

		if ( this->parsedInt[section].find( name ) == this->parsedInt[section].end() )
		{
			if ( errorOutput )
				errorOutput->what = "Cannot find int in section " + section + " (" + name + ") \n";

			return 0;
		}

		return this->parsedInt[section][name];
	}

	double INIFile::GetDouble( const std::string& section, const std::string& name, ini_error_t * errorOutput )
	{
		if ( this->parsedDouble.find( section ) == this->parsedDouble.end() )
		{
			if ( errorOutput )
				errorOutput->what = "Cannot find double section name (" + section + ") \n";

			return 0.0;
		}

		if ( this->parsedDouble[section].find( name ) == this->parsedDouble[section].end() )
		{
			if ( errorOutput )
				errorOutput->what = "Cannot find double in section " + section + " (" + name + ") \n";

			return 0.0;
		}

		return this->parsedDouble[section][name];
	}

	std::string INIFile::GetString( const std::string& section, const std::string& name, ini_error_t* errorOutput )
	{
		if ( this->parsedString.find( section ) == this->parsedString.end() )
		{
			if ( errorOutput )
				errorOutput->what = "Cannot find string section name (" + section + ") \n";

			return "";
		}

		if ( this->parsedString[section].find( name ) == this->parsedString[section].end() )
		{
			if ( errorOutput )
				errorOutput->what = "Cannot find string in section " + section + " (" + name + ") \n";

			return "";
		}

		return this->parsedString[section][name];
	}


	bool INIFile::isInt( const std::string& value )
	{
		return std::all_of( value.begin(), value.end(), ::isdigit );
	}

	bool INIFile::isDouble( const std::string& value )
	{
		// There is more than one '.' (1.123.abc)
		if ( std::count( value.begin(), value.end(), '.' ) != 1 )
			return false;

		size_t dotPos = value.find( '.' );

		// There is dot at end (123.)
		if ( dotPos == value.size() - 1 )
			return false;

		// there are other characters than '.' and numbers
		for ( size_t i = 0; i < value.size(); i++ )
			if ( i != dotPos && !::isdigit( static_cast<unsigned char>( value[i] ) ) )
				return false;

		return true;
	}

	bool INIFile::isBool( const std::string& value )
	{
		std::string valLower = value;
		std::transform( valLower.begin(), valLower.end(), valLower.begin(), ::tolower );

		return ( valLower == "true" || valLower == "false" );
	}

	void INIFile::clearMaps()
	{
		this->parsedString.clear();
		this->parsedInt.clear();
		this->parsedDouble.clear();
		this->parsedBool.clear();
	}

	void INIFile::removeBlanks( std::string& str )
	{
		while ( str.find( ' ' ) != std::string::npos )
			str.erase( str.find( ' ' ), 1 );
	}

	void INIFile::removeFirstBlanks( std::string& str )
	{
		for ( size_t i = 0; i < str.size(); i++ )
		{
			if ( str[i] != ' ' )
				return;

			str.erase( i, 1 );
		}
	}

	void INIFile::removeEscapeSeq( std::string& str )
	{
		for ( int32_t i = 0; static_cast<size_t>( i ) < str.size(); i++ )
		{
			// checking for escape sequences
			if ( str[i] != '\a' &&
				str[i] != '\b' &&
				str[i] != '\f' &&
				str[i] != '\n' &&
				str[i] != '\r' &&
				str[i] != '\t' &&
				str[i] != '\v' &&
				str[i] != '\\' &&
				str[i] != '\'' &&
				str[i] != '\"' &&
				str[i] != '\?' )
				continue;

			str.erase( i, 1 );
			// i-- because if str have: "\n\n" the second \n would be passed 
			i--;
		}
	}
}