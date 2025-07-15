#pragma once

#include <iostream>

namespace Utils
{
	void clearScreen();
	void pauseScreen();

	template<typename Func>
	bool handleDatabaseOperation(Func&& func)
	{
		try
		{
			func();
			return true;
		}
		catch (const std::invalid_argument& e)
		{
			std::cerr << "\n" << e.what();
			pauseScreen();
			clearScreen();
			return false;
		}
		catch (const std::out_of_range& e)
		{
			std::cerr << "\n" << e.what();
			pauseScreen();
			clearScreen();
			return false;
		}
	}
}