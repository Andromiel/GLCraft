#pragma once

#include <unordered_map>
#include "../Profiler/Profiler.h"

template<typename T>
class Registry
{
private:
	short nextAvailableId = 0;
	std::unordered_map<short, T*> registry;

	std::pair<short, T*> GetPair(short id, T *value)
	{
		return std::pair<short, T*>(id, value);
	}

	short GetNextId()
	{
		return nextAvailableId++;
	}

public:
	short Register(T *value)
	{
		short id = GetNextId();
		registry.insert(GetPair(id, value));
		return id;
	}

	T* GetFromRegistry(short id)
	{
		auto value = registry.find(id);
		if (value != registry.end()) {
			return value->second;
		}
		else {
			return registry.begin()->second;
		}
	}

	Registry() {}

	~Registry() {
		typename std::unordered_map<short, T*>::iterator it;
		for (it = registry.begin(); it != registry.end(); it++) {
			delete it->second;
		}
	}
};
