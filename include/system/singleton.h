#pragma once
#include <memory>

class Singleton
{
public:
	Singleton* instance();

private:
	Singleton() {}
	Singleton(const Singleton&) = delete;
	Singleton(const Singleton&&) = delete;

	static std::unique_ptr<Singleton> _instance;
};