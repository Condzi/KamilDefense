/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

/*
	Header-only Simple type INI file parser.
	File should have following format:
	[Section_Name]
	varStr = My super_string!
	; int values are stored as... int
	varInt = 123
	; only true or false
	varBool = false
	; only double type variables
	varDoubleA = 1.23
*/

#include <algorithm>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

#include <Config.hpp>

namespace CGF_NAMESPACE
{
	struct ini_error_t
	{
		std::string what = "";
	};

	/*
		INIFile class
		Almost every method have additional pointer to ini_error_t object for more error informations.
	*/
	class INIFile final
	{
	private:
		bool isInt(const std::string& value);
		bool isDouble(const std::string& value);
		bool isBool(const std::string& value);

		void clearMaps();
		void removeBlanks(std::string& str);
		void removeFirstBlanks(std::string& str);
		void removeEscapeSeq(std::string& str);

	public:
		INIFile() :
			loaded(false),
			parsed(false)
		{}

		bool isLoaded() { return loaded; }
		bool isParsed() { return parsed; }
		
		bool loadFromFile(const std::string& path, ini_error_t* errorOutput = nullptr);
		bool parse(ini_error_t* errorOutput = nullptr);

		void clear();

		std::string getString(const std::string& section, const std::string& name, ini_error_t* errorOutput = nullptr);
		int getInt(const std::string& section, const std::string& name, ini_error_t* errorOutput = nullptr);
		double getDouble(const std::string& section, const std::string& name, ini_error_t* errorOutput = nullptr);
		bool getBool(const std::string& section, const std::string& name, ini_error_t* errorOutput = nullptr);

	private:
		bool loaded;
		bool parsed;

		std::vector<std::string> rawData;
		//					<section name					<variable name, data>>
		std::unordered_map<std::string, std::unordered_map<std::string, std::string>> parsedString;
		std::unordered_map<std::string, std::unordered_map<std::string, int>> parsedInt;
		std::unordered_map<std::string, std::unordered_map<std::string, double>> parsedDouble;
		std::unordered_map<std::string, std::unordered_map<std::string, bool>> parsedBool;
	};

	/*
		XXXXXXXXXX	==========	XXXXXXXXXX
		XXXXXXXXXX	DEFINITIONS	XXXXXXXXXX
		XXXXXXXXXX	==========	XXXXXXXXXX
	*/

	bool INIFile::isInt(const std::string& value)
	{
		return std::all_of(value.begin(), value.end(), ::isdigit);
	}

	bool INIFile::isDouble(const std::string& value)
	{
		// There is more than one '.' (1.123.abc)
		if (std::count(value.begin(), value.end(), '.') != 1)
			return false;

		size_t dotPos = value.find('.');
		
		// There is dot at end (123.)
		if (dotPos == value.size() - 1)
			return false;

		// there are other characters than '.' and numbers
		for (size_t i = 0; i < value.size(); i++)
			if (i != dotPos && !::isdigit(static_cast<unsigned char>(value[i])))
				return false;

		return true;
	}

	bool INIFile::isBool(const std::string& value)
	{
		std::string valLower = value;
		std::transform(valLower.begin(), valLower.end(), valLower.begin(), ::tolower);

		return (valLower == "true" || valLower == "false");
	}

	void INIFile::clearMaps()
	{
		parsedString.clear();
		parsedInt.clear();
		parsedDouble.clear();
		parsedBool.clear();
	}

	void INIFile::removeBlanks(std::string& str)
	{
		while (str.find(' ') != std::string::npos)
			str.erase(str.find(' '), 1);
	}

	void INIFile::removeFirstBlanks(std::string& str)
	{
		for (size_t i = 0; i < str.size(); i++)
		{
			if (str[i] != ' ')
				return;

			str.erase(i, 1);
		}
	}

	void INIFile::removeEscapeSeq(std::string& str)
	{
		for (int32_t i = 0; static_cast<size_t>(i) < str.size(); i++)
		{
			// checking for escape sequences
			if (str[i] != '\a' &&
				str[i] != '\b' &&
				str[i] != '\f' &&
				str[i] != '\n' &&
				str[i] != '\r' &&
				str[i] != '\t' &&
				str[i] != '\v' &&
				str[i] != '\\' &&
				str[i] != '\'' &&
				str[i] != '\"' &&
				str[i] != '\?')
				continue;

			str.erase(i, 1);
			// i-- because if str have: "\n\n" the second \n would be passed 
			i--;
		}
	}

	bool INIFile::loadFromFile(const std::string& path, ini_error_t* errorOutput)
	{
		std::ifstream file(path);
		std::string temp = "";

		if (!file.good() || !file.is_open())
		{
			if (errorOutput)
				errorOutput->what = "Cannot open file (" + path + ") \n";
			
			loaded = false;
			return false;
		}

		rawData.clear();

		while (!file.eof())
		{
			std::getline(file, temp);

			// Line is a comment or line is empty
			if ((temp.size() >= 1 && temp[0] == ';') ||
				(!temp.size()))
				continue;

			rawData.push_back(temp);
		}

		loaded = true;
		return true;
	}

	bool INIFile::parse(ini_error_t* errorOutput)
	{
		parsed = false;

		clearMaps();

		std::string tempSectionName = "";
		int tempInt = 0;
		double tempDouble = 0;
		bool tempBool = 0;
		// name and value
		std::pair<std::string, std::string> data("", "");

		for (auto& str : rawData)
		{	
			// Removes \n etc from line
			removeEscapeSeq(str);

			// Line is section name
			if (str.find('[') != std::string::npos || str[str.size() - 1] == ']')
			{
				removeBlanks(str);
				// cutting from [ to ] (size - 1 = last string char, size - 2 is string without last char)
				tempSectionName = str.substr(str.find('[') + 1, str.size() - 2);

				continue;
			}

			// If no section name
			if (tempSectionName == "")
			{
				if (errorOutput)
					errorOutput->what = "No section name \n";

				return false;
			}

			// If there is no '=' in "value data" (should be "value = data")
			if (str.find('=') == std::string::npos)
			{
				if (errorOutput)
					errorOutput->what = "No '=' in data line \n";

				return false;
			}

			// value name is part before '=' (name = value)
			data.first = str.substr(0, str.find('='));
			// "a b C" -> "abC"
			removeBlanks(data.first);

			// data part is after '=' (name = data)
			data.second = str.substr(str.find('=') + 1);
			// "   data" -> "data"
			removeFirstBlanks(data.second);

			if (isInt(data.second))
			{
				tempInt = std::stoi(data.second);

				parsedInt[tempSectionName][data.first] = tempInt;

				continue;
			}

			if (isDouble(data.second))
			{
				tempDouble = std::stod(data.second);

				parsedDouble[tempSectionName][data.first] = tempDouble;

				continue;
			}

			if (isBool(data.second))
			{
				tempBool = (data.second == "true");

				parsedBool[tempSectionName][data.first] = tempBool;
			
				continue;
			}

			parsedString[tempSectionName][data.first] = data.second;
		}

		parsed = true;

		return true;
	}

	void INIFile::clear()
	{
		rawData.clear();
		
		clearMaps();
	}

	std::string INIFile::getString(const std::string& section, const std::string& name, ini_error_t* errorOutput)
	{
		if (parsedString.find(section) == parsedString.end())
		{
			if (errorOutput)
				errorOutput->what = "Cannot find string section name (" + section + ") \n";

			return "";
		}

		if (parsedString[section].find(name) == parsedString[section].end())
		{
			if (errorOutput)
				errorOutput->what = "Cannot find string in section " + section + " (" + name + ") \n";
			
			return "";
		}

		return parsedString[section][name];
	}
	int INIFile::getInt(const std::string & section, const std::string & name, ini_error_t * errorOutput)
	{
		if (parsedInt.find(section) == parsedInt.end())
		{
			if (errorOutput)
				errorOutput->what = "Cannot find int section name (" + section + ") \n";

			return 0;
		}

		if (parsedInt[section].find(name) == parsedInt[section].end())
		{
			if (errorOutput)
				errorOutput->what = "Cannot find int in section " + section + " (" + name + ") \n";

			return 0;
		}

		return parsedInt[section][name];
	}

	double INIFile::getDouble(const std::string & section, const std::string & name, ini_error_t * errorOutput)
	{
		if (parsedDouble.find(section) == parsedDouble.end())
		{
			if (errorOutput)
				errorOutput->what = "Cannot find double section name (" + section + ") \n";

			return 0.0;
		}

		if (parsedDouble[section].find(name) == parsedDouble[section].end())
		{
			if (errorOutput)
				errorOutput->what = "Cannot find double in section " + section + " (" + name + ") \n";

			return 0.0;
		}

		return parsedDouble[section][name];
	}

	bool INIFile::getBool(const std::string& section, const std::string& name, ini_error_t* errorOutput)
	{

		if (parsedBool.find(section) == parsedBool.end())
		{
			if (errorOutput)
				errorOutput->what = "Cannot find bool section name (" + section + ") \n";

			return false;
		}

		if (parsedBool[section].find(name) == parsedBool[section].end())
		{
			if (errorOutput)
				errorOutput->what = "Cannot find bool in section " + section + " (" + name + ") \n";

			return false;
		}

		return parsedBool[section][name];
	}
}
