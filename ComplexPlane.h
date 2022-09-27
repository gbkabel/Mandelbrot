#pragma once
#include <SFML/Graphics.hpp>


using namespace sf;

class ComplexPlane
{
public:

	void zoomIn();
	void zoomOut();
	void setCenter(Vector2f);
	View getView();
	void setMouseLocation(Vector2f);
	void loadText(Text&);

	void iterationsToRGB();
private:
	Vector2f m_mouseLocation;
	View m_view;
	int m_zoomCount;
	float m_aspectRatio;
};
	