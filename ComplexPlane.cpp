#include "ComplexPlane.h"
#include <cmath>
#include <thread>
#include <future>
#include <SFML/System.hpp>

using namespace std;
using namespace sf;

ComplexPlane::ComplexPlane(float aspectRatio)
{
	m_aspectRatio = aspectRatio;
	m_view.setSize(BASE_WIDTH, -BASE_HEIGHT * m_aspectRatio);
	m_view.setCenter(0.0, 0.0);
	m_zoomCount = 0;
}

void ComplexPlane::zoomIn()
{
	m_zoomCount++;
	double x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	double y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_view.setSize(x, y);
}

void ComplexPlane::zoomOut()
{
	m_zoomCount--;
	double x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	double y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_view.setSize(x, y);
}

void ComplexPlane::setCenter(Vector2f coord)
{
	m_view.setCenter(coord);
}

View ComplexPlane::getView()
{
	return m_view;
}

void ComplexPlane::setMouseLocation(Vector2f coord)
{
	m_mouseLocation = coord;
}

void ComplexPlane::loadText(Text& text)
{
	stringstream textBox;
	textBox << "Mandelbrot Set";
	textBox << "\nCenter: (" << m_view.getCenter().x << "," << m_view.getCenter().y << ")";
	textBox << "\nCursor: (" << m_mouseLocation.x << "," << m_mouseLocation.y << ")";
	textBox << "\nLeft-click to Zoom in";
	textBox << "\nRight-click to Zoom out";
	text.setString(textBox.str());
}

size_t ComplexPlane::countIterations(Vector2f coord)
{
	/* The way this works is by taking the coordinates of x and y, that are fetched from
	the for loop that runs through the actual pixels and feeding them here and
	then it does the comparison*/
	
	float x = coord.x;
	float y = coord.y;

	size_t numberofIters = 0;
	complex<float> c(x, y);
	complex<float> z(0.0, 0.0);

	while (numberofIters < MAX_ITER && abs(z) < 2.0)
	{
		z = z * z + c;
		numberofIters++;
	}
	return numberofIters;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
		if (count < 12)
		{
			r = 89;
			g = 0;
			b = 255;
		}
		else if (count >= 12 && count < 24)
		{
			r = 0;
			g = 255;
			b = 255;
		}
		else if (count >= 24 && count < 36)
		{
			r = 0;
			g = 255;
			b = 0;
		}
		else if (count >= 36 && count < 48)
		{
			r = 251;
			g = 255;
			b = 0;
		}
		else if (count >= 48 && count < 60)
		{
			r = 89;
			g = 0;
			b = 255;
		}
		else if (count >= 60 && count <= 64)
		{
			r = 0;
			g = 0;
			b = 0;
		}
}