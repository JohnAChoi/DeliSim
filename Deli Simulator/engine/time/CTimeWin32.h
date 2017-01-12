// CTime class
// controls shiz

#ifndef _C_TIME_
#define _C_TIME_

// Include
#include <ctime>
#include "types/floattype.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN

#include "types/standard_types.h"

// Namespace for the lulz

// Class Definition
class CTime
{
public:
	static void Init();
	static void Tick();

	static ftype CurrentTime ( void );

	static ftype TrainerFactor ( ftype );
	static ftype SqrtTrainerFactor ( ftype );
public:
	static ftype deltaTime;
	static ftype limitedDeltaTime;
	static ftype smoothDeltaTime;

	static ftype fixedTime;
	static ftype targetFixedTime;

	static ftype currentTime;

private:
	static LARGE_INTEGER iLastTick;
	static LARGE_INTEGER iCurrentTick;

	static LARGE_INTEGER iFrequency;

	static ftype fDeltaTimes[10];

};

typedef CTime Time;

#endif