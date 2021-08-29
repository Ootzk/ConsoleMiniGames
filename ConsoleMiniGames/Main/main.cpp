#include <iostream>

#include "core.h"
#include "screens.h"

int main() {
	std::cout << "hello world!" << std::endl;
	MainScreen M;
	M.loop();

	return 0;
}