#include "Timer.h"


Timer::Timer()
{
	Reset();
}


float Timer::GetElapsed() const
{
	high_res_clock::time_point t2 = high_res_clock::now();
	double_duration time_span = std::chrono::duration_cast<double_duration>(t2 - start_);

	return static_cast<float>(time_span.count());
}


void Timer::Reset() 
{ 
	start_ = high_res_clock::now();
}