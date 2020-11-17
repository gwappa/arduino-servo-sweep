/*
*  Copyright (c) 2019-2020 Keisuke Sehara
*
*  Permission is hereby granted, free of charge, to any person obtaining a copy
*  of this software and associated documentation files (the "Software"), to deal
*  in the Software without restriction, including without limitation the rights
*  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*  copies of the Software, and to permit persons to whom the Software is
*  furnished to do so, subject to the following conditions:
*  
*  The above copyright notice and this permission notice shall be included in all
*  copies or substantial portions of the Software.
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*  SOFTWARE.
*/

#include <Servo.h>

// where the white / orange wire goes
#define SERVO_PIN 9

// red wire --> +5V
// black wire --> GND

#define CLOCK 20
#define INTER_TRIAL 1000

#define START 130
#define STOP 142

//#define ENABLE_0Hz1
//#define ENABLE_0Hz4
//#define ENABLE_1Hz
//#define ENABLE_12Hz

Servo servo;

int cycle = 0;
int pos = 0;

void setup() {
  Serial.begin(9600);
  servo.attach(SERVO_PIN);
  servo.write(START);
}

void loop() {
  if (Serial.available()) {
    int c = Serial.read();
    if (c > 0) {
      #ifdef ENABLE_0Hz1
      run_with_settings(START, STOP, 1, 5, 300); // 0.139 Hz
      delay(INTER_TRIAL);
      #endif
      #ifdef ENABLE_0Hz4
      run_with_settings(START, STOP, 1, 5, 100); // 0.417 Hz
      delay(INTER_TRIAL);
      #endif
      #ifdef ENABLE_1Hz
      run_with_settings(START, STOP, 1, 5, 40); // 1.04 Hz
      delay(INTER_TRIAL);
      #endif
      run_with_settings(START, STOP, 1, 10, 20); // 2.08 Hz
      delay(INTER_TRIAL);
      run_with_settings(START, STOP, 2, 20, 20); // 4.17 Hz
      delay(INTER_TRIAL);
      run_with_settings(START, STOP, 3, 20, 20); // 6.25 Hz
      delay(INTER_TRIAL);
      run_with_settings(START, STOP, 4, 40, 20); // 8.33 Hz
      delay(INTER_TRIAL);
      #ifdef ENABLE_12Hz
      run_with_settings(START, STOP, 6, 40, 20); // 12.5 Hz
      delay(INTER_TRIAL);
      run_with_settings(START, STOP, 6, 40, 20); // 12.5 Hz
      delay(INTER_TRIAL);
      #endif
      run_with_settings(START, STOP, 4, 40, 20); // 8.33 Hz
      delay(INTER_TRIAL);
      run_with_settings(START, STOP, 3, 20, 20); // 6.25 Hz
      delay(INTER_TRIAL);
      run_with_settings(START, STOP, 2, 20, 20); // 4.17 Hz
      delay(INTER_TRIAL);
      run_with_settings(START, STOP, 1, 10, 20); // 2.08 Hz
      #ifdef ENABLE_1Hz
      delay(INTER_TRIAL);
      run_with_settings(START, STOP, 1, 5, 40); // 1.04 Hz
      #endif
      #ifdef ENABLE_0Hz4
      delay(INTER_TRIAL);
      run_with_settings(START, STOP, 1, 5, 100); // 0.417 Hz
      #endif
      #ifdef ENABLE_0Hz1
      delay(INTER_TRIAL);
      run_with_settings(START, STOP, 1, 5, 300); // 0.139 Hz
      #endif
    }
    Serial.println(".");
  }
}

void run_with_settings(const int start_pos, const int stop_pos, const int step_pos, const int cycles, const int pwm_dur) {
  for (cycle=0; cycle<cycles; cycle++) {
    for (pos=start_pos;pos<=stop_pos;pos+=step_pos) {
      servo.write(pos);
      delay(pwm_dur);
    }
    for (pos=stop_pos;pos>=start_pos; pos-=step_pos) {
      servo.write(pos);
      delay(pwm_dur);
    }
  }
}
