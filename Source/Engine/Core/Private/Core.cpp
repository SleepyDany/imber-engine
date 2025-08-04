//
#include "Core.h"

#include <format>
#include <iostream>

void Test::Do()
{
	std::cout << std::format("Do");
}

void Test::StaticDo()
{
	std::cout << std::format("StaticDo");
}