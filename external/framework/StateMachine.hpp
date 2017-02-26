/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <cassert>
#include <unordered_map>
#include <memory>
#include <vector>

#include <State.hpp>

namespace CGF_NAMESPACE
{
	class StateMachine final
	{
	private:
		State* createState( state_id_t id );

	public:
		StateMachine( state_id_t startState = 0 ) :
			actualState( startState )
		{}

		StateMachine( const StateMachine& ) = delete;
		const StateMachine& operator=( const StateMachine& ) = delete;

		void setCurrentStateID( state_id_t id ) { actualState = id; }

		template<class T, typename... Args>
		void registerState( state_id_t id, Args&&... args )
		{
			static_assert( std::is_base_of<State, T>::value, "T must derive from State class" );

			factories[id] = [&args..., this]()
			{
				return new T( std::forward<Args>( args )... );
			};
		}

		void run();

	private:
		std::vector<std::unique_ptr<State>> stack;
		std::unordered_map<state_id_t, std::function<State*( )>> factories;

		state_id_t actualState;
	};
}
