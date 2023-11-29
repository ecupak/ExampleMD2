#pragma once

#include <chrono>


// [Credit] From the 'original' tmpl8.
class Timer
{
public:
	Timer();


	void Reset();
	
	
	float GetElapsed() const;


private:
	using high_res_clock = std::chrono::high_resolution_clock;
	using double_duration = std::chrono::duration<double>;

	std::chrono::high_resolution_clock::time_point start_;
};