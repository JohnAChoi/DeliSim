#ifndef _ACTOR_H_
#define _ACTOR_H_

#include <Box2D.h>
#include "BaseObject.h"
#include "WorldObject.h"

class Actor: public BaseObject
{
public:
	Actor (void);
	~Actor (void);

	void OnCreate	(void) override;
	void OnDestroy	(void) override;

	void Update		(void) override;
	void LateUpdate (void) override;
	void Draw		(void) override;

	virtual void OnInteract (void);

	b2Body* GetBody (void);

protected:
	b2BodyDef sBodyDef;

	//Remember to save the pointer passed back from pEngine->gWorld->CreateBody() here.
	b2Body* pBody;

	//Keep track of which sprite image should be rendered
	int mSpriteIndex;
};
#endif