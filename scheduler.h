/* scheduler.h
 * Cyclic executive scheduler definitions.
 * CMPE311 Embedded System Design — Project#1 Revision
 *
 * Defines the number of tasks, convenience macros, and pin assignments.
 * The task list (taskList[]) is declared in cyclicExec.ino and populated
 * with function pointers to the three task functions in tasks.h.
 *
 * To add a task:
 *   1. Write a void f(void) function in tasks.h / tasks.c
 *   2. Append its pointer to taskList[] in cyclicExec.ino
 *   3. Increment NUM_TASKS
 *
 * Who:  Aissatou Diallo, UMBC — Spring 2026
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

/* ---- Scheduler constants ----------------------------------------------- */
#define NUM_TASKS   3           /* Number of tasks in the cyclic executive   */

/* ---- Boolean aliases --------------------------------------------------- */
#define TRUE        1
#define FALSE       0

/* ---- Hardware pin assignments (per Educational Constraint E.3) --------- */
#define PIN_LED2    2           /* LED#1 — digital output pin 2              */
#define PIN_LED3    3           /* LED#2 — digital output pin 3              */

/* ---- Global state shared between scheduler and tasks ------------------- */
/*
 * Declared extern here; defined once in tasks.c so any translation unit
 * that includes scheduler.h can read/write the shared state.
 *
 * In the Arduino build system all .ino, .c, and .h files in the sketch
 * folder are compiled together, so the linker resolves these automatically.
 */
extern unsigned long delayStart2;       /* Timestamp of last LED2 toggle     */
extern unsigned long delayStart3;       /* Timestamp of last LED3 toggle     */
extern int           ledOn2;            /* TRUE if LED2 is currently on      */
extern int           ledOn3;            /* TRUE if LED3 is currently on      */
extern unsigned long intervalLed[13];   /* Blink half-period per LED index   */
extern int           waiting4led;       /* Serial SM: waiting for LED#       */
extern int           waiting4interval;  /* Serial SM: waiting for interval   */
extern int           interval;          /* Last parsed interval value        */
extern int           setLedNum;         /* Last parsed LED number            */

#endif /* SCHEDULER_H */
