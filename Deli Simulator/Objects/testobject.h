

#ifndef _TEST_OBJECT_H_
#define _TEST_OBJECT_H_

#include "engine\Behavior.h"


class TestObject : public Engine::Behavior
{
	ClassType(TestObject)
public:

	//These functions are necessary for the engine to do stuff with them
	void	OnCreate	(void) override;
	void	OnDestroy	(void) override;

	void	Update		(void) override;
	void	LateUpdate	(void) override;
	void	Draw		(void) override;
};

#endif//_TEST_OBJECT_H_