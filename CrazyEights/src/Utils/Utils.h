#pragma once
#include <thread>
#include <chrono>

namespace Utils
{
	/**
	* Sleep this thread for the given milliseconds.
	* \param ms How long to sleep for, in milliseconds.
	*/
	static void SleepForMs(const int ms)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(ms));
	}

	/**
	* Sleep this thread for the given seconds.
	* \param s How long to sleep for, in seconds.
	*/
	static void SleepForS(const int s)
	{
		std::this_thread::sleep_for(std::chrono::seconds(s));
	}
}