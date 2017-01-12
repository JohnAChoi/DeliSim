#ifndef _TEST_ROOM_2_H_
#define _TEST_ROOM_2_H_

#include "../Room.h"

class TestRoom2: public Room
{
public:
	TestRoom2 (void);
	TestRoom2 (SDL_Rect pos);
	TestRoom2 (int height, int width);

	~TestRoom2 (void);

	void OnCreate	(void) override;
	void OnDestroy	(void) override;

	void Update		(void) override;
	void LateUpdate (void) override;
	//void Draw		(void) override;
};

#endif