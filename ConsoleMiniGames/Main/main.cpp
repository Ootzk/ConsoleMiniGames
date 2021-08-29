#include <iostream>

#include "core.h"

int main() {
	std::cout << "hello world!" << std::endl;

	while (true) {
		KEY key = getKEY();
		if (key == KEY::SELECT) std::cout << "something selected!" << endl;
	}

	return 0;
}