#include "Demon_S.h"
#include <stdio.h>

Demon_S::Demon_S()
{
	
}

Demon_S::~Demon_S()
{
	
}

void Demon_S::init()
{
	charNo = 11;

	animationSpeed = 12;

	charSpeed = 15;

	Character::init();
}

void Demon_S::draw()
{
	Character::init();
}

void Demon_S::fixUpdate()
{
	Character::fixUpdate();
}

void Demon_S::update()
{
	Character::update();
}

void Demon_S::release()
{
	Character::release();
}