/* cyclicExec.ino
 * Project#1 — Cyclic Executive Revision
 * CMPE311 Embedded System Design, Spring 2026
 *
 * Implements a cyclic executive scheduler using a function pointer array.
 * Three non-blocking tasks execute in fixed round-robin order every loop():
 *   [0] taskSerial()    — serial input state machine (LED# then interval)
 *   [1] taskBlinkLED2() — millis()-based blink for LED on pin 2
 *   [2] taskBlinkLED3() — millis()-based blink for LED on pin 3
 *
 * Behavior is functionally identical to the baseline (multiTaskBasic.ino).
 * No blocking calls (delay, busy-wait) are used anywhere.
 *
 * Who:  Aissatou Diallo, UMBC
 * When: Spring 2026
 * Ref:  Diallo, Aissatou.cmpe311.fall25.project#1-ECN-R1
 */

#include "scheduler.h"
#include "tasks.h"

/* --- Scheduler task list (cyclic executive) ----------------------------- */
void (*taskList[NUM_TASKS])(void) = {
    taskSerial,
    taskBlinkLED2,
    taskBlinkLED3
};

/* --- setup() ------------------------------------------------------------ */
void setup() {
    Serial.begin(9600);

    pinMode(PIN_LED2, OUTPUT);
    pinMode(PIN_LED3, OUTPUT);

    ledOn2 = FALSE;
    ledOn3 = FALSE;
    digitalWrite(PIN_LED2, LOW);
    digitalWrite(PIN_LED3, LOW);

    delayStart2 = millis();
    delayStart3 = millis();

    /* Initial blink intervals (msec per half-period) */
    intervalLed[2] = 1000;
    intervalLed[3] = 500;

    /* Prime the serial state machine */
    Serial.print("What LED?");
    waiting4led      = TRUE;
    waiting4interval = FALSE;
}

/* --- loop() — cyclic executive ------------------------------------------ */
void loop() {
    int i;
    for (i = 0; i < NUM_TASKS; i++) {
        taskList[i]();
    }
}
