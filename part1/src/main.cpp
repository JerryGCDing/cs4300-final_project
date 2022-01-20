#include "SDLGraphicsProgram.h"
#include <iostream>

int main(int argc, char** argv) {
	SDLGraphicsProgram mySDLGraphicsProgram(1280, 720);
	std::cout << "===============================================================\n";
	std::cout << "Use mouse wheel to zoom in/out.\n";
	std::cout << "Use Number keys to switch through different visual effects:\n";
	std::cout << "1 - PLAIN effect (default)\n";
	std::cout << "2 - GALATIC effect\n";
	std::cout << "3 - GLOOM effect\n";
	std::cout << "4 - FLUID effect\n";
	std::cout << "===============================================================\n";

	mySDLGraphicsProgram.Loop();
	return 0;
}
