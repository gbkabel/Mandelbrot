// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ComplexPlane.h"

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
	// Get the desktop resolution
	VideoMode::getDesktopMode().width;
	VideoMode::getDesktopMode().height;

	//Calculate the aspect ratio of the monitor
	double aspectRatio = VideoMode::getDesktopMode().height / VideoMode::getDesktopMode().width;




	// Create a video mode object
	VideoMode vm(1920, 1080);

	// Create and open a window for the game
	RenderWindow window(vm, "Mandelbrot", Style::Default);

	return 0;
}


