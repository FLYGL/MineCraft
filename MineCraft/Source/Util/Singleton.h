#pragma once
class Singleton
{
public:
	Singleton(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;

	Singleton& operator=(const Singleton&) = delete;
	Singleton& operator=(Singleton&&) = delete;
protected:
	Singleton() = default;
};