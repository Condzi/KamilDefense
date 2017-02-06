/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <iostream>
#include <string>

#include <Logger.hpp>

int main()
{
	cgf::Logger::initialize();

	cgf::Logger::log("==========", cgf::Logger::NONE, cgf::Logger::CONSOLE);
	cgf::Logger::log("Hello!");
	cgf::Logger::log("==========", cgf::Logger::NONE, cgf::Logger::CONSOLE);

	cgf::Logger::shutdown();
	std::cin.get();
}