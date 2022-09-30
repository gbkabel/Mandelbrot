#include <vector>
#include <cmath>
#include <complex>
#include <sstream>
#include "ComplexPlane.h"

using namespace std;
using namespace sf;

ComplexPlane::ComplexPlane(float aspectRatio)
{
	m_aspectRatio = aspectRatio;
	m_view.setSize(BASE_WIDTH, BASE_HEIGHT * m_aspectRatio);
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
	m_view.setSize(coord);
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
	textBox << "\nCenter: (";
	textBox << "\nCursor: (";
	textBox << "Left-click to Zoom in";
	textBox << "Right-click to Zoom out";
	
}

size_t ComplexPlane::countIterations(Vector2f coord)
{
	float x = coord.x;
	float y = coord.y;

	size_t count = 0;
	complex<float> c(x, y);
	complex<float> z(0.0, 0.0);

	while (count < MAX_ITER && abs(z) < 2.0)
	{
		z = z * z + c;
		count++;
	}
	return count;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
	for (count = 0; count < MAX_ITER; count++)
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
		else
		{
			r = 255;
			g = 0;
			b = 8;
		}
	}
}