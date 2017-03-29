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
		Global settings structure with modificators of Gameplay and other application
		parameters. Everything is changable in configuration file.

	===============================================================================
	*/
	struct
	{
		struct
		{
			const std::string WINDOW_TITLE = "Kamil Defense";
		} INTERNAL;

		struct
		{
			// Note: All float values must end up with .NON-ZERO! Otherwise it'll save as int not float value!

			// Textures are very small so they must be scaled up.
			const float SCALE = 10.1f;
			const float GRAVITY = 10.1f;
			const float DEFAULT_OBJECT_WEIGHT = 50.1f;

			const uint8_t MAX_HEALTH = 200ui8;
			const uint8_t MAX_ARMOR = 100ui8;
			const seconds_t DAMAGE_BLOCK_TIME = 0.32f;
			const seconds_t ENEMY_SHOOT_COOLDOWN = 0.5f;

			const float PLAYER_MISSILE_SPEED_X = 400.1f;
			const float PLAYER_MISSILE_START_SPEED_Y = -250.1f;
			const float PLAYER_MISSILE_WEIGHT = 60.1f;

			const float ENEMY_MISSILE_SPEED_X = 375.1f;
			const float ENEMY_MISSILE_WEIGHT = 10.1f;

			seconds_t IMMORTAL_EFFECT_TIME = 10.0f;
		} GAMEPLAY;

		struct
		{
			const bool DEBUG_DRAW_BORDERS = false;
			const uint16_t WINDOW_SIZE_X = static_cast<uint16_t>( 64 + 3 );
			const uint16_t WINDOW_SIZE_Y = static_cast<uint16_t>( 64 + 5 );
			const uint32_t FPS_LIMIT = 64ui32;
		} GLOBAL;

		struct
		{
			const std::string FONT = "data/fonts/wendy.ttf";
			const std::string PLAYER_TEXTURE = "data/textures/player.png";
			const std::string ENEMY_TEXTURE = "data/textures/enemy.png";
		} RESOURCES_PATHES;

		inline void Load( const std::string& path )
		{
			pi::INIFile file;
			pi::ini_error_t error;

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

			const_cast<std::string&>( this->INTERNAL.WINDOW_TITLE ) = file.GetString( "INTERNAL", "WINDOW_TITLE" );

			const_cast<bool&>( this->GLOBAL.DEBUG_DRAW_BORDERS ) = file.GetBool( "GLOBAL", "DEBUG_DRAW_BORDERS" );
			const_cast<uint16_t&>( this->GLOBAL.WINDOW_SIZE_X ) = file.GetInt( "GLOBAL", "WINDOW_SIZE_X" );
			const_cast<uint16_t&>( this->GLOBAL.WINDOW_SIZE_Y ) = file.GetInt( "GLOBAL", "WINDOW_SIZE_Y" );
			const_cast<uint32_t&>( this->GLOBAL.FPS_LIMIT ) = file.GetInt( "GLOBAL", "FPS_LIMIT" );

			const_cast<float&>( this->GAMEPLAY.SCALE ) = file.GetDouble( "GAMEPLAY", "SCALE" );
			const_cast<float&>( this->GAMEPLAY.GRAVITY ) = file.GetDouble( "GAMEPLAY", "GRAVITY" );
			const_cast<float&>( this->GAMEPLAY.DEFAULT_OBJECT_WEIGHT ) = file.GetDouble( "GAMEPLAY", "DEFAULT_OBJECT_WEIGHT" );

			const_cast<uint8_t&>( this->GAMEPLAY.MAX_HEALTH ) = file.GetInt( "GAMEPLAY", "MAX_HEALTH" );
			const_cast<uint8_t&>( this->GAMEPLAY.MAX_ARMOR ) = file.GetInt( "GAMEPLAY", "MAX_ARMOR" );
			const_cast<seconds_t&>( this->GAMEPLAY.DAMAGE_BLOCK_TIME ) = file.GetDouble( "GAMEPLAY", "DAMAGE_BLOCK_TIME" );
			const_cast<seconds_t&>( this->GAMEPLAY.ENEMY_SHOOT_COOLDOWN ) = file.GetDouble( "GAMEPLAY", "ENEMY_SHOOT_COOLDOWN" );

			const_cast<float&>( this->GAMEPLAY.PLAYER_MISSILE_SPEED_X ) = file.GetDouble( "GAMEPLAY", "PLAYER_MISSILE_SPEED_X" );
			const_cast<float&>( this->GAMEPLAY.PLAYER_MISSILE_START_SPEED_Y ) = file.GetDouble( "GAMEPLAY", "PLAYER_MISSILE_START_SPEED_Y" );
			const_cast<float&>( this->GAMEPLAY.PLAYER_MISSILE_WEIGHT ) = file.GetDouble( "GAMEPLAY", "PLAYER_MISSILE_WEIGHT" );

			const_cast<float&>( this->GAMEPLAY.ENEMY_MISSILE_SPEED_X ) = file.GetDouble( "GAMEPLAY", "ENEMY_MISSILE_SPEED_X" );
			const_cast<float&>( this->GAMEPLAY.ENEMY_MISSILE_WEIGHT ) = file.GetDouble( "GAMEPLAY", "ENEMY_MISSILE_WEIGHT" );
			const_cast<seconds_t&>( this->GAMEPLAY.IMMORTAL_EFFECT_TIME ) = file.GetDouble( "GAMEPLAY", "IMMORTAL_EFFECT_TIME" );


			const_cast<std::string&>( this->RESOURCES_PATHES.FONT ) = file.GetString( "RESOURCES_PATHES", "FONT" );
			const_cast<std::string&>( this->RESOURCES_PATHES.PLAYER_TEXTURE ) = file.GetString( "RESOURCES_PATHES", "PLAYER_TEXTURE" );
			const_cast<std::string&>( this->RESOURCES_PATHES.ENEMY_TEXTURE ) = file.GetString( "RESOURCES_PATHES", "ENEMY_TEXTURE" );

			cgf::Logger::Log( "Settings file read" );
		}

		inline void Save( const std::string& path )
		{
			std::ofstream file( path );

			file
				<< "[INTERNAL]\n" <<
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

	} static SETTINGS;
}