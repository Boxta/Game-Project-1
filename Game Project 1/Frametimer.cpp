#include "Frametimer.h"



float Frametimer::Mark()
{
	const auto old = last;

	last = std::chrono::steady_clock::now();

	const std::chrono::duration<float> frameTime = last - old;

	return frameTime.count();
}

Frametimer::Frametimer()
{
	last = std::chrono::steady_clock::now();
}


Frametimer::~Frametimer()
{
}
