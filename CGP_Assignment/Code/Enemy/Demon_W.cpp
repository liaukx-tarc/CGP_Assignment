#include "Demon_W.h"
#include <stdio.h>

Demon_W::Demon_W()
{

}

Demon_W::~Demon_W()
{

}

void Demon_W::init()
{
	objSize.x = 12;
	objSize.y = 17;

	charNo = 12;

	animationSpeed = 12;

	charSpeed = 10;

	Character::init();
}

void Demon_W::draw()
{
	Character::init();
}

void Demon_W::fixUpdate()
{
	Character::fixUpdate();
}

void Demon_W::update()
{
	Character::update();
}

void Demon_W::release()
{
	Character::release();
}