#ifndef _WORLD_OBJECT_H_
#define _WORLD_OBJECT_H_

#include "BaseObject.h"
#include "Box2D/Box2D.h"

//The World object should handle the environment and stuff like that. It will eventually have to take data from
//other classes to modify the landscape it's showing.
class WorldObject: public BaseObject
{
public:

	WorldObject (void);
	~WorldObject (void);

	void OnCreate	(void) override;
	void OnDestroy	(void) override;

	void Update		(void) override;
	void LateUpdate (void) override;
	void Draw		(void) override;
};

#endif