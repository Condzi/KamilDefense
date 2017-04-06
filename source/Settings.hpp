/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#if defined ( _MSC_VER )
#pragma warning ( disable : 4244 )
#endif

#include <iomanip>

#include <framework/Logger.hpp>
#include <framework/INIparser.hpp>

namespace kd
{
	/*
	===============================================================================
		Global settings class with modificators of Gameplay and other application
		parameters. Everything is changable in configuration file. To get settings
		use settings_t::GetInstance().

	===============================================================================
	*/
	class settings_t
	{
	public:
		struct
		{
			std::string WINDOW_TITLE;
		} INTERNAL;

		struct
		{
			// Textures are very small so they must be scaled up.
			float SCALE;
			float GRAVITY;
			float DEFAULT_OBJECT_WEIGHT;

			uint8_t MAX_HEALTH;
			uint8_t MAX_ARMOR;
			seconds_t DAMAGE_BLOCK_TIME;
			seconds_t ENEMY_SHOOT_COOLDOWN;

			float PLAYER_MISSILE_SPEED_X;
			float PLAYER_MISSILE_START_SPEED_Y;
			float PLAYER_MISSILE_WEIGHT;

			float ENEMY_MISSILE_SPEED_X;
			float ENEMY_MISSILE_WEIGHT;

			seconds_t IMMORTAL_EFFECT_TIME;
		} GAMEPLAY;

		struct
		{
			bool DEBUG_DRAW_BORDERS;
			uint16_t WINDOW_SIZE_X;
			uint16_t WINDOW_SIZE_Y;
			uint32_t FPS_LIMIT;
		} GLOBAL;

		struct
		{
			std::string FONT;
			std::string PLAYER_TEXTURE;
			std::string ENEMY_TEXTURE;
		} RESOURCES_PATHES;

		inline void Load( const std::string& path )
		{
			pi::INIFile file;
			pi::INIError_t error;

			if ( !file.LoadFromFile( path, &error ) )
			{
				cgf::Logger::Log( "Error loading settings: \"" + error.what + "\", generating default file...", cgf::Logger::ERROR );
				// Saves default data
				this->Save( path );
				this->Load( path );
				return;
			}

			if ( !file.Parse( &error ) )
			{
				cgf::Logger::Log( "Error parsing settings: \"" + error.what + "\".", cgf::Logger::ERROR );
				return;
			}

			// Loading fields in order they are that defined in Settings.hpp.

			this->INTERNAL.WINDOW_TITLE = file.GetString( "INTERNAL", "WINDOW_TITLE" );

			this->GLOBAL.DEBUG_DRAW_BORDERS = file.GetBool( "GLOBAL", "DEBUG_DRAW_BORDERS" );
			this->GLOBAL.WINDOW_SIZE_X = file.GetInt( "GLOBAL", "WINDOW_SIZE_X" );
			this->GLOBAL.WINDOW_SIZE_Y = file.GetInt( "GLOBAL", "WINDOW_SIZE_Y" );
			this->GLOBAL.FPS_LIMIT = file.GetInt( "GLOBAL", "FPS_LIMIT" );

			this->GAMEPLAY.SCALE = file.GetDouble( "GAMEPLAY", "SCALE" );
			this->GAMEPLAY.GRAVITY = file.GetDouble( "GAMEPLAY", "GRAVITY" );
			this->GAMEPLAY.DEFAULT_OBJECT_WEIGHT = file.GetDouble( "GAMEPLAY", "DEFAULT_OBJECT_WEIGHT" );

			this->GAMEPLAY.MAX_HEALTH = file.GetInt( "GAMEPLAY", "MAX_HEALTH" );
			this->GAMEPLAY.MAX_ARMOR = file.GetInt( "GAMEPLAY", "MAX_ARMOR" );
			this->GAMEPLAY.DAMAGE_BLOCK_TIME = file.GetDouble( "GAMEPLAY", "DAMAGE_BLOCK_TIME" );
			this->GAMEPLAY.ENEMY_SHOOT_COOLDOWN = file.GetDouble( "GAMEPLAY", "ENEMY_SHOOT_COOLDOWN" );

			this->GAMEPLAY.PLAYER_MISSILE_SPEED_X = file.GetDouble( "GAMEPLAY", "PLAYER_MISSILE_SPEED_X" );
			this->GAMEPLAY.PLAYER_MISSILE_START_SPEED_Y = file.GetDouble( "GAMEPLAY", "PLAYER_MISSILE_START_SPEED_Y" );
			this->GAMEPLAY.PLAYER_MISSILE_WEIGHT = file.GetDouble( "GAMEPLAY", "PLAYER_MISSILE_WEIGHT" );

			this->GAMEPLAY.ENEMY_MISSILE_SPEED_X = file.GetDouble( "GAMEPLAY", "ENEMY_MISSILE_SPEED_X" );
			this->GAMEPLAY.ENEMY_MISSILE_WEIGHT = file.GetDouble( "GAMEPLAY", "ENEMY_MISSILE_WEIGHT" );
			this->GAMEPLAY.IMMORTAL_EFFECT_TIME = file.GetDouble( "GAMEPLAY", "IMMORTAL_EFFECT_TIME" );


			this->RESOURCES_PATHES.FONT = file.GetString( "RESOURCES_PATHES", "FONT" );
			this->RESOURCES_PATHES.PLAYER_TEXTURE = file.GetString( "RESOURCES_PATHES", "PLAYER_TEXTURE" );
			this->RESOURCES_PATHES.ENEMY_TEXTURE = file.GetString( "RESOURCES_PATHES", "ENEMY_TEXTURE" );

			cgf::Logger::Log( "Settings file read correctly" );
		}

		inline void Save( const std::string& path )
		{
			std::ofstream file( path );

			file <<
				"[INTERNAL]\n" <<
				"WINDOW_TITLE = " << this->INTERNAL.WINDOW_TITLE << "\n\n" <<

				"[GAMEPLAY]\n" <<
				"SCALE = " << this->GAMEPLAY.SCALE << "\n" <<
				"GRAVITY = " << this->GAMEPLAY.GRAVITY << "\n" <<
				"DEFAULT_OBJECT_WEIGHT = " << this->GAMEPLAY.DEFAULT_OBJECT_WEIGHT << "\n\n" <<

				"MAX_HEALTH = " << ( int32_t )this->GAMEPLAY.MAX_HEALTH << "\n" <<
				"MAX_ARMOR = " << ( int32_t )this->GAMEPLAY.MAX_ARMOR << "\n" <<
				"DAMAGE_BLOCK_TIME = " << this->GAMEPLAY.DAMAGE_BLOCK_TIME << "\n" <<
				"ENEMY_SHOOT_COOLDOWN = " << this->GAMEPLAY.ENEMY_SHOOT_COOLDOWN << "\n\n" <<

				"PLAYER_MISSILE_SPEED_X = " << this->GAMEPLAY.PLAYER_MISSILE_SPEED_X << "\n" <<
				"PLAYER_MISSILE_START_SPEED_Y = " << this->GAMEPLAY.PLAYER_MISSILE_START_SPEED_Y << "\n" <<
				"PLAYER_MISSILE_WEIGHT = " << this->GAMEPLAY.PLAYER_MISSILE_WEIGHT << "\n\n" <<

				"ENEMY_MISSILE_SPEED_X = " << this->GAMEPLAY.ENEMY_MISSILE_SPEED_X << "\n" <<
				"ENEMY_MISSILE_WEIGHT = " << this->GAMEPLAY.ENEMY_MISSILE_WEIGHT << "\n" <<
				"IMMORTAL_EFFECT_TIME = " << this->GAMEPLAY.IMMORTAL_EFFECT_TIME << "\n\n" <<

				"[GLOBAL]\n" <<
				"DEBUG_DRAW_BORDERS = " << std::boolalpha << this->GLOBAL.DEBUG_DRAW_BORDERS << "\n" <<
				"WINDOW_SIZE_X = " << this->GLOBAL.WINDOW_SIZE_X << "\n" <<
				"WINDOW_SIZE_Y = " << this->GLOBAL.WINDOW_SIZE_Y << "\n" <<
				"FPS_LIMIT = " << this->GLOBAL.FPS_LIMIT << "\n\n" <<

				"[RESOURCES_PATHES]\n" <<
				"FONT = " << this->RESOURCES_PATHES.FONT << "\n" <<
				"PLAYER_TEXTURE = " << this->RESOURCES_PATHES.PLAYER_TEXTURE << "\n" <<
				"ENEMY_TEXTURE = " << this->RESOURCES_PATHES.ENEMY_TEXTURE;
		}

		static settings_t& GetInstance();

	private:
		settings_t()
		{
			// Note: All float values must end up with .NON-ZERO! Otherwise it'll save as int not float value!

			INTERNAL.WINDOW_TITLE = "Kamil Defense";

			GAMEPLAY.SCALE = 10.01f;
			GAMEPLAY.GRAVITY = 10.01f;
			GAMEPLAY.DEFAULT_OBJECT_WEIGHT = 50.01f;

			GAMEPLAY.MAX_HEALTH = 200ui8;
			GAMEPLAY.MAX_ARMOR = 100ui8;
			GAMEPLAY.DAMAGE_BLOCK_TIME = 0.32f;
			GAMEPLAY.ENEMY_SHOOT_COOLDOWN = 0.5f;

			GAMEPLAY.PLAYER_MISSILE_SPEED_X = 400.01f;
			GAMEPLAY.PLAYER_MISSILE_START_SPEED_Y = -250.01f;
			GAMEPLAY.PLAYER_MISSILE_WEIGHT = 60.01f;

			GAMEPLAY.ENEMY_MISSILE_SPEED_X = 375.01f;
			GAMEPLAY.ENEMY_MISSILE_WEIGHT = 10.01f;

			GAMEPLAY.IMMORTAL_EFFECT_TIME = 10.01f;

			GLOBAL.DEBUG_DRAW_BORDERS = false;
			GLOBAL.WINDOW_SIZE_X = uint16_t( 128 );
			GLOBAL.WINDOW_SIZE_Y = uint16_t( 92 );
			GLOBAL.FPS_LIMIT = 64ui32;

			RESOURCES_PATHES.FONT = "data/fonts/wendy.ttf";
			RESOURCES_PATHES.PLAYER_TEXTURE = "data/textures/player.png";
			RESOURCES_PATHES.ENEMY_TEXTURE = "data/textures/enemy.png";
		}
	};
}