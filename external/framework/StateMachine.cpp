/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <StateMachine.hpp>

namespace CGF_NAMESPACE
{
	State* StateMachine::createState( state_id_t id )
	{
		auto result = factories.find( id );

		// There is no states registered / cannot find state of that id
		assert( !( result == factories.end() ) );

		return result->second();
	}

	void StateMachine::run()
	{
		state_id_t nextState = actualState;

		stack.resize( factories.size() );

		while ( actualState != EXIT_STATE )
		{
			stack[actualState].reset( createState( actualState ) );

			stack[actualState]->onStart();
			nextState = stack[actualState]->run();
			stack[actualState]->onStop();

			actualState = nextState;
		}
	}
}