#include "Demon.h"
#include <stdio.h>

Demon::Demon()
{

}

Demon::~Demon()
{

}

void Demon::init()
{
	objSize.x = 14;
	objSize.y = 21;

	charNo = 10;

	animationSpeed = 12;

	charSpeed = 10;

	Character::init();
}

void Demon::draw()
{
	Character::init();
}

void Demon::fixUpdate()
{
	Character::fixUpdate();
}

void Demon::update()
{
	Character::update();
}

void Demon::release()
{
	Character::release();
}