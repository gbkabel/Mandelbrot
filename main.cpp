// Include important C++ libraries here
#include <iostream>
#include <complex>
#include <SFML/Graphics.hpp>
#include "ComplexPlane.h"

// Make code easier to type with "using namespace"
using namespace std;
using namespace sf;

int main()
{
	// Get the desktop resolution
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	//Calculate the aspect ratio of the monitor
	float aspectRatio = resolution.y / resolution.x;

	// Create and open a window for the game
	RenderWindow window(VideoMode(resolution.x, resolution.y), "Mandelbrot", Style::Default); 
	ComplexPlane ComplexPlane(aspectRatio); //creates the complex plane object we needed
	Font font; //creates font
	font.loadFromFile("calibri-regular.ttf"); //loads the font
	Text mytext;
	mytext.setFont(font);
	VertexArray backgrounder; //vertex array creation
	backgrounder.setPrimitiveType(Points);
	backgrounder.resize(VideoMode::getDesktopMode().width * VideoMode::getDesktopMode().height);
	
	enum class state {CALCULATING, DISPLAYING}; // Create enum class
	state stateOfProgram = state::CALCULATING;  // Set the state to calculating

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event)) // Poll windows queue events
		{
			if (event.type == sf::Event::Closed)  // Close the window
			{
				window.close();
				break;
			}
			if (event.type == sf::Event::Resized) // Resize the window
			{
				resolution.x = VideoMode::getDesktopMode().width;
				resolution.y = VideoMode::getDesktopMode().height;
				aspectRatio = resolution.y / resolution.x;
				backgrounder.resize(VideoMode::getDesktopMode().width* VideoMode::getDesktopMode().height);
				break;
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				stateOfProgram = state::CALCULATING;
				if (event.mouseButton.button == sf::Mouse::Left) // Left-click zooms in
				{
					ComplexPlane.zoomIn(); //this accesses the class function that makes the whole thing zoom in
					ComplexPlane.setCenter(window.mapPixelToCoords(Mouse::getPosition(), ComplexPlane.getView())); //this sets the center of the new view at whatever point the user clicks on
				}
				else if (event.mouseButton.button == sf::Mouse::Right) // Right-click zooms out
				{
					ComplexPlane.zoomOut(); //ditto with zoom out
					ComplexPlane.setCenter(window.mapPixelToCoords(Mouse::getPosition(), ComplexPlane.getView())); // ditto
				}
				break;
			}
			if (event.type == sf::Event::MouseMoved) // Mouse move gets current coords
			{
				ComplexPlane.setMouseLocation(window.mapPixelToCoords(Mouse::getPosition(), ComplexPlane.getView())); //This is used to display the mouse coordinates as it moves
				break;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) // Escape key closes program
		{
			window.close();
		}
		if (stateOfProgram == state::CALCULATING) // Checks to if the state of our enum class is calculating
		{
			for (int j = 0; j < resolution.x; j++) 
			{					
				for (int i = 0; i < resolution.y; i++)		// Double for loop to loop through all pixels
				{
					backgrounder[j + i * 1].position = { (float)j, (float)i };

				}
			}
		}
		window.clear();
		window.draw(backgrounder);
		window.draw(mytext);
		window.display();
	}
	
	return 0;
}


