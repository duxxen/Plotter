#include "../include/system/singleton.h"

std::unique_ptr<Singleton> Singleton::_instance = nullptr;

Singleton* Singleton::instance()
{
	if (_instance == nullptr)
		_instance.reset(new Singleton);
	return _instance.get();
}