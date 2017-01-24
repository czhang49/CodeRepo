#include "flexmotor.h"
#include "performance.h"
#include "math.h"

volatile double duration = 0;
volatile double errorIdx = 0;
volatile int16_t Tx = 0;  // theta x
volatile int16_t Ty = 0;  // theta y

void calcQEI(double Xset, double Xfilt, double Yset, double Yfilt) {
    double posError = W1 * (pow(Xset - Xfilt, 2) + pow(Yset - Yfilt, 2));
    double controlError = W2 * (pow(Tx, 2) + pow(Ty, 2));

    duration += DT;  // 20 ms
    errorIdx += (posError+controlError) * DT;
}

unsigned int getQEI() {
    return errorIdx / duration;
}

void setMotorDuty(uint8_t chan, uint16_t duty_us) {
  switch (chan) {
  case MOTOR_X_CHAN:
    Tx = duty_us - 1500;
    break;
  case MOTOR_Y_CHAN:
    Ty = duty_us - 1500;
    break;
  }

  motor_set_duty(chan, duty_us);
}
