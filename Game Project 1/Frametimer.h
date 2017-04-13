#pragma once

#include <chrono>

class Frametimer
{
private:
	std::chrono::steady_clock::time_point last;
public:

	float Mark();
	Frametimer();
	~Frametimer();
};

