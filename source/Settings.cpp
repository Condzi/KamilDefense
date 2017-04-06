/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "Settings.hpp"

namespace kd
{
	settings_t& settings_t::GetInstance()
	{
		static settings_t instance;

		return instance;
	}
}