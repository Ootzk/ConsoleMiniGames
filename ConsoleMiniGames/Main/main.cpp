#include "engine.h"

int main() {
	std::ifstream textfile("text.txt", std::fstream::in);
	std::ifstream fontfile("font.txt", std::fstream::in);
	std::ifstream backfile("back.txt", std::fstream::in);

	draw(textfile, fontfile, backfile);

	//Engine e;
	//e.run();

	return 0;
}