#include "TestLevel.h"
#include "Tile.h"

TestLevel::TestLevel()
{

}

TestLevel::~TestLevel()
{
	delete levelFile;
}

void TestLevel::init()
{
	//load map
	std::string name = "level/Test_Level.txt";

	levelFile = new char[name.size() + 1];
	std::copy(name.begin(), name.end(), levelFile);
	levelFile[name.size()] = '\0';

	Tile::getInstance()->loadMap(levelFile);
}

void TestLevel::fixUpdate()
{
	
}

void TestLevel::update()
{
	
}

void TestLevel::draw()
{
	Tile::getInstance()->drawMap();
}

void TestLevel::release()
{
	
}