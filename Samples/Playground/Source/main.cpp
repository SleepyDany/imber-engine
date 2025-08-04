#include "Core.h"

#include <iostream>

int main()
{
	Test test;

	test.Do();
	std::cout << '\n';
	Test::StaticDo();

	return 0;
}