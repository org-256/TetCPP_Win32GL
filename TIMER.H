
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
