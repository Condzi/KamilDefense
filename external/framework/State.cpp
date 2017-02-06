/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <State.hpp>

namespace CGF_NAMESPACE
{
	void State::startThread()
	{
		lockWindowContext();
		threadRunning = true;

		thread = std::thread(&State::threadMethod, this);
	}

	void State::endThread()
	{
		threadRunning = false;
		thread.join();

		unlockWindowContext();
	}

	void State::threadMethod()
	{
		unlockWindowContext();

		while (threadRunning)
		{
			updateThread(1 / 30.f, *windowPtr);
		}

		lockWindowContext();
	}
}