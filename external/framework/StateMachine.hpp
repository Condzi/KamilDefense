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
		std::unique_ptr<State> createState( state_id_t id );

	public:
		StateMachine( state_id_t startState = 0 ) :
			actualState( startState )
		{}

		StateMachine( const StateMachine& ) = delete;
		const StateMachine& operator=( const StateMachine& ) = delete;

		void SetCurrentStateID( state_id_t id ) { this->actualState = id; }

		template<class T, typename... Args>
		void RegisterState( state_id_t id, Args&&... args )
		{
			static_assert( std::is_base_of<State, T>::value, "T must derive from State class" );

			this->factories[id] = [&args..., this]()
			{
				return std::make_unique<T>( std::forward<Args>( args )... );
			};
		}

		void Run();

	private:
		std::vector<std::unique_ptr<State>> stack;
		std::unordered_map<state_id_t, std::function<std::unique_ptr<State>()>> factories;

		state_id_t actualState;
	};
}
