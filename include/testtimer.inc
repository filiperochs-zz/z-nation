
stock exSetTimer(func[],time,repeat)
	return SetTimer(func,time,repeat);
//#define exSetTimerEx(%0,%1,%2,%3,%4) SetTimerEx(%0,%1,%2,%3,%4)

#define SetTimer exSetTimer
//#define SetTimerEx exSetTimerEx
