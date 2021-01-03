
// This is the part of source code of SirTet - FREE SOFTWARE -

// You are free to use it in any posible way
// include commercial or educational
// W/O ANY POSIBLE WARANTY of PROFITability or USENESS

// !!!CAUTION!!! This software may or may not cause of
// potential damage of personal computer or OS
// or other software

// Author DOES NOT CARRY ANY DIRECT OR INDIRECT LIABILITY
// INCLUDE POTENTIAL DAMAGE OF YOUR OR YOUR CONSUMER's
// PERSONAL COMPUTERS OR/AND OPERATIONAL SYSTEMS

// !!!Please, If you do not agree with Author's declaration,
// DO NOT COMPILE or/and EXECUTE THIS SOFTWARE ON YOUR OR THIRD PERSONS PC's!!!

// Any proposition? suggestion? question?
// mail-to: handrix@yandex.ru

//=============================================================
// This code is typical C/C99 code. 100% buildable with PellesC
// Mostly buildable with MinGW. (sometimes with little changes)
// To build with Lcc-WinXX or tcc - you must use QPC definition
// Code is buildable with tcc, but timer don't work properly :(
// Probably because of incorrect win headers
// Truly says I didn't check it in MSVC. You may try it by self 
// But something tell me that it's would be a hard experience
//=============================================================

#include "timer.h"

#define QPC

//#pragma warn(disable: 2096)
Time Timer::GetTicks(void)
{
#ifdef QPC
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return li.QuadPart;
#else
__asm
	{
    	_emit 0x0F
    	_emit 0x31
	}

#endif
}

//#pragma warn(enable: 2096)


void Timer::Init()
{
	start = GetTicks();

#ifdef QPC
	LARGE_INTEGER li;
	QueryPerformanceFrequency(&li);
	freq = li.QuadPart;
#else
	Sleep(1000);
	freq = GetTicks()- start;
#endif

	freqMS = freq/1000;
	last_delta = start;
}

double Timer::NewDelta()
{
	double delta;
	Time ticks = GetTicks();
	delta = (double)(ticks - last_delta)/(double)freq;
	last_delta = ticks;
	return delta;
}
Time Timer::DeltaMS()
{
	Time delta;
	Time ticks = GetTicks();
	delta =  (ticks - last_delta)/freqMS;
	last_delta = ticks;
	return delta;
}

void Timer::Start()
{
	start = GetTicks();
	last_delta = start;
}

double Timer::Secs()
{
	Time ticks = GetTicks();
	return (double)(ticks-start)/(double)freq;
}

Time Timer::MSecs()
{
	Time ticks = GetTicks();
	Time msecs = (Time)((double)( ticks - start)/ freqMS);
	return msecs;
}

void Timer::SetWatch(double seconds)
{
	Start();
	_wSecs = Secs()+seconds;
}

bool Timer::Watch()
{
	if(Secs()>= _wSecs)
		return true;
	return false;
}