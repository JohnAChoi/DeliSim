#ifndef _TEST_ROOM_H_
#define _TEST_ROOM_H_

#include "../Room.h"

class TestRoom: public Room
{
public:
	TestRoom (void);
	TestRoom (SDL_Rect pos);
	TestRoom (int height, int width);

	~TestRoom (void);

	void OnCreate	(void) override;
	void OnDestroy	(void) override;

	void Update		(void) override;
	void LateUpdate (void) override;
	//void Draw		(void) override;
};

#endif