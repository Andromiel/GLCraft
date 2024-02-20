#include "Profiler.h"

#include <string>

Profiler Profiler::PROFILER;

void Profiler::Push(std::string name)
{
	std::pair<std::string, std::chrono::time_point<std::chrono::steady_clock>>* pair = new std::pair<std::string, std::chrono::time_point<std::chrono::steady_clock>>(name, std::chrono::steady_clock::now());
	stack.push(pair);
	currentFrame.Push(name);
}

void Profiler::Pop()
{
	std::pair<std::string, std::chrono::time_point<std::chrono::steady_clock>>* pair = stack.top();
	stack.pop();
	currentFrame.Pop(std::chrono::duration<double, std::micro>(std::chrono::steady_clock::now() - pair->second).count() / 1000.0f);
	delete pair;
}

void Profiler::PopAndPush(std::string name)
{
	Pop();
	Push(name);
}

Frame Profiler::ExtractFrame()
{
	return Frame(currentFrame);
}
