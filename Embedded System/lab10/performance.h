#ifndef PERFORMANCE_H
#define	PERFORMANCE_H

#define W1 0.01    // 6 digits
#define W2 0.01 // 6 digits
#define DT 0.02  // 20ms

void calcQEI(double Xset, double Xfilt, double Yset, double Yfilt);
unsigned int getQEI();
void setMotorDuty(uint8_t chan, uint16_t duty_us);

#endif
