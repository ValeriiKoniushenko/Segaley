#include "DebugActions.h"
#include "Window.h"
#include "Program.h"

#include <iostream>

int main()
{
	try
	{
		#ifdef DEBUG
		DebugActions::copyAssets();
		#endif

		Window::instance();

		auto program = std::make_unique< Program >();
		program->launch();
	}
	catch ( const std::runtime_error& ex )
	{
		std::cout << "Fatal error: " << ex.what() << std::endl;
	}
	catch ( const std::out_of_range& ex )
	{
		std::cout << "Our of range: " << ex.what() << std::endl;
	}

	return 0;
}
