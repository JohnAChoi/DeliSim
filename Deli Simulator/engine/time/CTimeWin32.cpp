
// Includes
#include "CTimeWin32.h"

// Static variable declares
ftype CTime::deltaTime;
ftype CTime::limitedDeltaTime;
ftype CTime::smoothDeltaTime;

ftype CTime::fixedTime;
ftype CTime::targetFixedTime;

ftype CTime::currentTime;

LARGE_INTEGER CTime::iLastTick;
LARGE_INTEGER CTime::iCurrentTick;

LARGE_INTEGER CTime::iFrequency;

ftype CTime::fDeltaTimes [10];

// Timer initialization
//  Sets default timer values
//  Grabs current tick
void CTime::Init ( void )
{
	deltaTime = 0.01f;
	limitedDeltaTime = 0.01f;
	smoothDeltaTime = 0.01f;
	fixedTime = 0.01f;
	targetFixedTime = 0.01f;
	//targetFixedTime = 1/60.0f;
	//targetFixedTime = 1/15.0f;
	currentTime = 0.0f;

	for ( char i = 0; i < 10; i += 1 )
	{
		fDeltaTimes[i] = 0.01f;
	}

	//iLastTick = clock();
	//iCurrentTick = clock();
	QueryPerformanceCounter( &iLastTick );
	QueryPerformanceCounter( &iCurrentTick );
	QueryPerformanceFrequency( &iFrequency );
}

// Timer Tick
//  updates delta time values
void CTime::Tick ( void )
{
	iLastTick = iCurrentTick;
	QueryPerformanceCounter( &iCurrentTick );

	smoothDeltaTime = 0.0f;
	for ( char i = 9; i > 0; i -= 1 )
	{
		fDeltaTimes[i] = fDeltaTimes[i-1];
		smoothDeltaTime += fDeltaTimes[i];
	}
	fDeltaTimes[0] = min( 1.0f/5.0f, ftype( ftype( iCurrentTick.QuadPart-iLastTick.QuadPart )/iFrequency.QuadPart ) );
	smoothDeltaTime += fDeltaTimes[0];

	// Set output
	deltaTime = fDeltaTimes[0];
	smoothDeltaTime = smoothDeltaTime * 0.1f;

	currentTime += deltaTime;
}

// Timer get trainer factor.
//   Returns factor for "a+=(t-a)*f" expressions
#include <algorithm>
ftype CTime::TrainerFactor ( ftype input )
{
	return std::min<ftype>( input*smoothDeltaTime*40.0f, 0.95f );
}
ftype CTime::SqrtTrainerFactor ( ftype input )
{
	return std::min<ftype>( input*sqrt(smoothDeltaTime)*6.3f, 0.96f );
}


// Timer return current CPU time in seconds
ftype CTime::CurrentTime ( void )
{
	LARGE_INTEGER tempTime;
	QueryPerformanceCounter( &tempTime );

	return ftype(tempTime.QuadPart)/iFrequency.QuadPart;
}