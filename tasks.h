/* tasks.h
 * Task function declarations and global state definitions.
 * CMPE311 Embedded System Design — Project#1 Revision
 *
 * Each task is a non-blocking void function that performs one unit of work
 * per call and returns immediately. All tasks share the global state defined
 * below (and declared extern in scheduler.h).
 *
 * Who:  Aissatou Diallo, UMBC — Spring 2026
 */

#ifndef TASKS_H
#define TASKS_H

#include "scheduler.h"

/* ---- Global state definitions ------------------------------------------ */
/* Defined here (once); declared extern in scheduler.h                       */

unsigned long delayStart2    = 0;
unsigned long delayStart3    = 0;
int           ledOn2         = FALSE;
int           ledOn3         = FALSE;
unsigned long intervalLed[13]= {1000}; /* index 2 and 3 used; rest unused   */
int           waiting4led    = FALSE;
int           waiting4interval = FALSE;
int           interval       = 0;
int           setLedNum      = 1;      /* default; avoids uninitialized read */

/* ---- Task function declarations ---------------------------------------- */

/*
 * taskSerial()
 * Polls Serial.available(). When data is present, reads either an LED number
 * or a blink interval depending on the current state (waiting4led / waiting4interval).
 * Updates intervalLed[setLedNum] after a complete LED# + interval pair is received.
 * Uses Serial.parseInt() only after data is confirmed available, minimizing
 * its internal timeout and avoiding any meaningful blocking.
 */
void taskSerial(void);

/*
 * taskBlinkLED2()
 * Checks whether (millis() - delayStart2) > intervalLed[2].
 * If so, toggles LED2 (pin PIN_LED2) and records a new delayStart2.
 * No blocking calls. Safe against millis() rollover via unsigned subtraction.
 */
void taskBlinkLED2(void);

/*
 * taskBlinkLED3()
 * Same as taskBlinkLED2() but for LED3 (pin PIN_LED3), delayStart3,
 * and intervalLed[3].
 */
void taskBlinkLED3(void);

/* ---- Task function implementations ------------------------------------- */
/* Defined inline here so the Arduino build system picks them up without    */
/* requiring a separate .cpp compilation unit.                               */

void taskSerial(void) {
    if (Serial.available() != 0) {
        if (waiting4led == TRUE) {
            setLedNum = Serial.parseInt();
            Serial.print("What interval (ms)");
            waiting4led      = FALSE;
            waiting4interval = TRUE;
        } else if (waiting4interval == TRUE) {
            interval = Serial.parseInt();
            intervalLed[setLedNum] = interval;
            Serial.print("What LED?");
            waiting4interval = FALSE;
            waiting4led      = TRUE;
        } else {
            /* Should never reach — defensive assert */
            Serial.print("***ASSERT: Input neither ledNum nor interval!!!");
            Serial.println();
        }
    }
}

void taskBlinkLED2(void) {
    if ((millis() - delayStart2) > intervalLed[2]) {
        if (ledOn2 == TRUE) {
            ledOn2 = FALSE;
            digitalWrite(PIN_LED2, LOW);
        } else {
            ledOn2 = TRUE;
            digitalWrite(PIN_LED2, HIGH);
        }
        delayStart2 = millis();
    }
}

void taskBlinkLED3(void) {
    if ((millis() - delayStart3) > intervalLed[3]) {
        if (ledOn3 == TRUE) {
            ledOn3 = FALSE;
            digitalWrite(PIN_LED3, LOW);
        } else {
            ledOn3 = TRUE;
            digitalWrite(PIN_LED3, HIGH);
        }
        delayStart3 = millis();
    }
}

#endif /* TASKS_H */
