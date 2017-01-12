
#include "testobject.h"
#include <iostream>

void TestObject::OnCreate ( void )
{
	std::cout << "Created object." << std::endl;
}

void TestObject::OnDestroy (void) 
{
	std::cout << "Destroyed object." << std::endl;
}

void TestObject::Update	(void)
{
	std::cout << "Updated object." << std::endl;
}

void TestObject::LateUpdate	(void)
{
	std::cout << "Late updated object." << std::endl;
}

void TestObject::Draw (void)
{
	std::cout << "Drew object." << std::endl;
}