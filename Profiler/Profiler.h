#pragma once

#include <stack>
#include <chrono>
#include "Frame.h"

class Profiler
{
public:
	static Profiler PROFILER;
	void Push(std::string name);
	void Pop();
	void PopAndPush(std::string name);
	Frame ExtractFrame();
private:
	std::stack<std::pair<std::string, std::chrono::time_point<std::chrono::steady_clock>>*> stack;
	Frame currentFrame;
};