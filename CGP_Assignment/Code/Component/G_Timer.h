#pragma once
#include <Windows.h>

class G_Timer {

public:
	G_Timer();
	~G_Timer();
	void init(int);
	int framesToUpdate();

private:
	LARGE_INTEGER timerFreq;
	LARGE_INTEGER timeNow;
	LARGE_INTEGER timePrevious;
	int Requested_FPS, frameToUpdate;
	float intervalsPerFrame, intervalsSinceLastUpdate;

};