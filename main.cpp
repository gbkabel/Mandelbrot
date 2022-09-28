// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ComplexPlane.h"
#include <complex>

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
	// Get the desktop resolution
	int widthOfScreen = VideoMode::getDesktopMode().width;
	int heightOfScreen = VideoMode::getDesktopMode().height;

	//Calculate the aspect ratio of the monitor
	double aspectRatio = VideoMode::getDesktopMode().height / VideoMode::getDesktopMode().width;

	// Create a video mode object
	VideoMode vm(1920, 1080);

	// Create and open a window for the game
	RenderWindow window(vm, "Mandelbrot", Style::Default);
	ComplexPlane ComplexPlane; //creates the complex plane object we needed
	Font font; //creates font
	font.loadFromFile("calibri-regular.ttf"); //loads the font
	Text mytext;
	mytext.setFont(font);
	VertexArray backgrounder; //vertex array creation
	backgrounder.setPrimitiveType(Points);
	backgrounder.resize(widthOfScreen * heightOfScreen);
	
	enum class state {CALCULATING, DISPLAYING};
	state stateOfProgram = state::CALCULATING;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				stateOfProgram = state::CALCULATING;
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					ComplexPlane.zoomIn(); //this accesses the class function that makes the whole thing zoom in
					ComplexPlane.setCenter(window.mapPixelToCoords(Mouse::getPosition(), ComplexPlane.getView())); //this sets the center of the new view at whatever point the user clicks on
				}
				else if (event.mouseButton.button == sf::Mouse::Right) {
					ComplexPlane.zoomOut(); //ditto with zoom out
					ComplexPlane.setCenter(window.mapPixelToCoords(Mouse::getPosition(), ComplexPlane.getView())); // ditto
				}
			}
			if (event.type == sf::Event::MouseMoved)
			{
				ComplexPlane.setMouseLocation(window.mapPixelToCoords(Mouse::getPosition(), ComplexPlane.getView())); //ig this is used to display the mouse coordinates as it moves
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		if (stateOfProgram == state::CALCULATING) {
			for (int j = 0; j < widthOfScreen; j++) {
				for (int i = 0; i < heightOfScreen; i++) {

					backgrounder[j + i * 1].position = { (float)j, (float)i };
				}
			}
		}
	}

	return 0;
}


