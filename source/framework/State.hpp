/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <atomic>
#include <thread>

#include <framework/Config.hpp>

namespace CGF_NAMESPACE
{
	class State
	{
	public:
		State( window_t* window ) :
			windowPtr( window ),
			threadRunning( false )
		{}

		State( const State& ) = delete;
		const State& operator =( const State& ) = delete;

		virtual ~State() = default;

		void SetWindowPtr( window_t* window ) { this->windowPtr = window; }

		virtual void OnStart() = 0;
		virtual void OnStop() = 0;
		virtual int16_t Run() = 0;

		// Call it when you need to load resources and you don't want to freeze window
		// Don't forget to call EndThread() 
		void StartThread();
		void EndThread();
		// updates thread (like update method in entities)
		virtual void UpdateThread( seconds_t time, window_t& window ) = 0;
		// This method is called when thread is stared - it is its loop
		virtual void ThreadMethod();

	protected:
		virtual void unlockWindowContext() = 0;
		virtual void lockWindowContext() = 0;

	protected:
		window_t* windowPtr;

	private:
		std::thread thread;
		std::atomic_bool threadRunning;
	};
}