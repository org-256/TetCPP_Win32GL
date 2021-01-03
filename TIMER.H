
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
// DO NOT COMPILE or/and EXECUTE THIS SOFTWARE ON YOUR OR THIRD PERSONS PCs!!!

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

#include "windows.h"

typedef  __int64 Time;

class Timer
{	
private:
	Time start;
	Time freq;
	Time freqMS;
	Time last_delta;
	double _wSecs;

public:

	Time GetTicks(void);
	void Init();
	double NewDelta();
	Time DeltaMS();
	void Start();
	double Secs();
	Time MSecs();

	void SetWatch(double seconds);
	bool Watch();
};
