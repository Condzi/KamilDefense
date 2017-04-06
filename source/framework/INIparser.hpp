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
	struct INIError_t
	{
		std::string what = "";
	};

	/*
	===============================================================================
	Created by: Condzi
		Class created for manipulating INI files. Almost every method has additional
		parameter 'INIError_t*' - it's a pointer to error message. For example if
		Parse() method return false, the INIError_t::what will contain information
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

		bool LoadFromFile( const std::string& path, INIError_t* errorOutput = nullptr );
		bool Parse( INIError_t* errorOutput = nullptr );

		void Clear();

		bool GetBool( const std::string& section, const std::string& name, INIError_t* errorOutput = nullptr );
		int GetInt( const std::string& section, const std::string& name, INIError_t* errorOutput = nullptr );
		double GetDouble( const std::string& section, const std::string& name, INIError_t* errorOutput = nullptr );
		std::string GetString( const std::string& section, const std::string& name, INIError_t* errorOutput = nullptr );

	private:
		bool loaded;
		bool parsed;

		std::vector<std::string> rawData;
		//					<section name					<variable name, data>>
		std::unordered_map<std::string, std::unordered_map<std::string, std::string>> parsedString;
		std::unordered_map<std::string, std::unordered_map<std::string, int>> parsedInt;
		std::unordered_map<std::string, std::unordered_map<std::string, double>> parsedDouble;
		std::unordered_map<std::string, std::unordered_map<std::string, bool>> parsedBool;

		bool isInt( const std::string& value );
		bool isDouble( const std::string& value );
		bool isBool( const std::string& value );

		void clearMaps();
		void removeBlanks( std::string& str );
		void removeFirstBlanks( std::string& str );
		void removeEscapeSeq( std::string& str );
	};
}