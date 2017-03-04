/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <StateMachine.hpp>

namespace CGF_NAMESPACE
{
	std::unique_ptr<State> StateMachine::createState( state_id_t id )
	{
		auto result = this->factories.find( id );

		// There is no states registered / cannot find state of that id
		assert( !( result == this->factories.end() ) );

		return std::move( result->second() );
	}

	void StateMachine::Run()
	{
		state_id_t nextState = this->actualState;

		this->stack.resize( this->factories.size() );

		while ( this->actualState != EXIT_STATE )
		{
			this->stack[actualState] = std::move( this->createState( this->actualState ) );

			this->stack[actualState]->OnStart();
			nextState = this->stack[actualState]->Run();
			this->stack[actualState]->OnStop();

			this->actualState = nextState;
		}
	}
}