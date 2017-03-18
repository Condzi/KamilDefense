/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <StateMachine.hpp>

#include "GameConfig.hpp"
#include "PlayState.hpp"
//
//int main()
//{
//	cgf::Logger::Initialize();
//	kd::ResourceHolder::Initialize();
//
//	window_t window( { kd::WINDOW_SIZE.x, kd::WINDOW_SIZE.y }, kd::WINDOW_TITLE );
//	window.setFramerateLimit( kd::FPS_LIMIT );
//
//	cgf::StateMachine stateMachine;
//
//	stateMachine.RegisterState<kd::PlayState>( static_cast<int16_t>( kd::state_t::MENU ), &window );
//
//	stateMachine.Run();
//
//	kd::ResourceHolder::Shutdown();
//	cgf::Logger::Shutdown();
//
//	return 0;
//}

#include "Level.hpp"

int main()
{
	// level saving

	//kd::Level lvl;
	//kd::internal::levelData_t lvlDat;

	//lvlDat.backgroundTexturePath = "data/textures/base.png";
	//lvlDat.playerSpawnPosition = { static_cast<float>( kd::WINDOW_SIZE.x / 2 ), static_cast<float>( kd::WINDOW_SIZE.y / 2 ) };
	//lvlDat.bordersRects =
	//{
	//	{ 0, 31 * 2 * kd::SCALE, 32 * 2 * kd::SCALE, 2.0f * kd::SCALE },
	//	{ 32 * 2 * kd::SCALE, 0, 2.0f * kd::SCALE, 32 * 2 * kd::SCALE },
	//	{ -( 2.0f * kd::SCALE ) , 0.0f, 2.0f * kd::SCALE, 32 * 2 * kd::SCALE },
	//	{ 0.0f, 21 * kd::SCALE * 2, 8 * kd::SCALE * 2, 2.0f * kd::SCALE },
	//	{ 11.0f * 2 * kd::SCALE, 15 * kd::SCALE * 2, 10 * kd::SCALE * 2,  2.0f * kd::SCALE },
	//	{ 24 * 2 * kd::SCALE, 21 * kd::SCALE * 2, 8 * kd::SCALE * 2, 2.0f * kd::SCALE }
	//};
	//lvlDat.spawnersData =
	//{
	//	{ { 1 * 2 * kd::SCALE, 10 * 2 * kd::SCALE }, { 250.0f, -250.0f }, 5.0f },
	//	{ { 28 * 2 * kd::SCALE, 10 * 2 * kd::SCALE }, { -250.0f, -250.0f }, 5.0f }
	//};

	//lvl.SetLevelData( lvlDat );
	//lvl.Save( "data/TestLevel.lvl" );

	// level loading
	kd::Level lvl;

	lvl.Load( "data/TestLevel.lvl" );

	return 0;
}