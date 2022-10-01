// Include important C++ libraries here
#include <iostream>
#include <complex>
#include <vector>
#include <SFML/Graphics.hpp>
#include "ComplexPlane.h"

// Make code easier to type with "using namespace"
using namespace std;
using namespace sf;

size_t threader(size_t pixlr); 
int main()
{
	// Get the desktop resolution
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width; //this is the width of the monitor
	resolution.y = VideoMode::getDesktopMode().height; // height of the monitor

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
	backgrounder.resize(resolution.x * resolution.y);
	
	enum class state {CALCULATING, DISPLAYING}; // Create enum class
	state stateOfProgram = state::CALCULATING;  // Set the state to calculating

	Vector2f pixels; //vector of pixels
	size_t numberOfIters = 0; // this is the number of iterations required for z to be less than 2 or the max iteration count

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event)) // Poll window queue events
		{
			if (event.type == sf::Event::Closed)  // Close the window
			{
				window.close();
				break;
			}
			if (event.type == sf::Event::Resized) // Resize the window
			{
				resolution.x = VideoMode::getDesktopMode().width; //had to do this again because we resized the window, and that changes things
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
					Vector2i mouser = Mouse::getPosition();
					ComplexPlane.setCenter(window.mapPixelToCoords(Mouse::getPosition(), ComplexPlane.getView())); //this sets the center of the new view at whatever point the user clicks on
					break;
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
			for (int j = 0; j < static_cast<int>(resolution.x); j++) //had to do the static_cast<int> to make sure that the 
			{					
				for (int i = 0; i < static_cast<int>(resolution.y); i++)		// Double for loop to loop through all pixels
				{
					backgrounder[j + i * resolution.x].position = { (float)j, (float)i }; 
					pixels = window.mapPixelToCoords(Vector2i(j, i), ComplexPlane.getView());
					numberOfIters = ComplexPlane.countIterations(pixels);
					Uint8 r, g, b;
					ComplexPlane.iterationsToRGB(numberOfIters, r,g,b);
					backgrounder[j + i * resolution.x].color = {r,g,b};
					//cout << backgrounder[i].position.x << endl;
					//cout << static_cast<int>(backgrounder[j + i * resolution.x].color.r) << endl;
					//cout << static_cast<int>(backgrounder[j + i * resolution.x].color.g) << endl;
					//cout << static_cast<int>(backgrounder[j + i * resolution.x].color.b) << endl;
				}
			}
			stateOfProgram = state::DISPLAYING;
			ComplexPlane.loadText(mytext);
		}
		window.clear(); //clears the window
		window.draw(backgrounder); //draws our vertex array!
		window.draw(mytext); //draws the text that we put
		window.display();
	}
		
	return 0;
}
size_t threader(size_t pixlr) {
	size_t totalIterations;
	ComplexPlane.countIterations(pixlr);

}


