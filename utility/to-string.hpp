#pragma once
#include <sstream>

namespace Plotter
{
	static inline std::streamsize DEFAULT_PRECISION{ 3 };

	std::string toString(float value, std::streamsize precision = DEFAULT_PRECISION);
}

inline std::string Plotter::toString(float value, std::streamsize precision)
{
	//value = round(value * 100000) / 100000;
	std::stringstream ss;
	std::string str;
	ss.precision(precision);
	ss << value;
	ss >> str;

	return str;
}