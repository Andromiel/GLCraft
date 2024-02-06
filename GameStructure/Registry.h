#pragma once

#include <map>

template<typename T>
class Registry
{
private:
	short nextAvailableId = 0;
	std::map<short, T> registry;

	std::pair<short, T> GetPair(short id, T value)
	{
		return std::pair<short, T>(id, value);
	}

	short GetNextId()
	{
		return nextAvailableId++;
	}

public:
	short Register(T value)
	{
		short id = GetNextId();
		registry.insert(GetPair(id, value));
		return id;
	}

	T GetFromRegistry(short id)
	{
		return registry.find(id)->second;
	}
};
