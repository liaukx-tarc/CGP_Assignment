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
	charNo = 12;

	animationSpeed = 12;

	charSpeed = 15;

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