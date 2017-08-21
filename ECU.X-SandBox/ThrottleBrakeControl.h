

#ifndef THROTTLEBRAKECONTROL_H
#define	THROTTLEBRAKECONTROL_H

#define GETSAST1 1
#define GETSAST2 2
#define GETSASB1 3
#define GETSASB2 4
#define GETSASBP 5

#define GETSAST1RAW 6
#define GETSAST2RAW 7
#define GETSASB1RAW 8
#define GETSASB2RAW 9

unsigned int GetThrottleBrakeValue(char request);
char GetSASFalts();
void SetThrotteMax(int val);
void DeltaThrottle();

#endif	/* XC_HEADER_TEMPLATE_H */

