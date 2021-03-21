#include "Button.h"
#include "../Component/GameWindows.h"

Button::Button()
{
	r = g = b = 255;
	isClick = false;
	isAni = false;
}

Button::~Button()
{
}

void Button::init()
{
	buttonRect.top = buttonRect.left = 0;
	buttonRect.bottom = size.y;
	buttonRect.right = size.x;


	positionRect.top = position.y - size.y/2;
	positionRect.left = position.x - size.x/2;
	positionRect.bottom = positionRect.top + size.y;
	positionRect.right = positionRect.left + size.x;
}

void Button::fixUpdate()
{
	
}

void Button::update()
{
	mousePos = GameWindows::getInstance()->mousePos;

	if (mousePos.x > positionRect.left && mousePos.x < positionRect.right &&
		mousePos.y > positionRect.top && mousePos.y < positionRect.bottom)
	{
		isClick = true;
	}

	else
	{
		isClick = false;
	}

	buttonRect.left = frame * (345 + 1);
	buttonRect.right = buttonRect.left + 345;
}

void Button::draw()
{

}

void Button::release()
{

}
