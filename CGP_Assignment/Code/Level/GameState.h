#pragma once
class GameState
{
public:
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void fixUpdate() = 0;
	virtual void draw() = 0;
	virtual void release() = 0;
};

#pragma once
