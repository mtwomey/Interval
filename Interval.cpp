/*
Interval v1.5

Fire void functions from your loop() function at set intervals.
The number of intervals is only restricted by memory.

Functions are added with: add(unsigned long ms, void (*f)(void))
Add Interval::fire() to your main loop()

Example:

Interval interval;

void a(){
  Serial.println("1000ms");
}
void setup(){
  Serial.begin(9600);
  interval.add(1000, &a);
}
void loop(){
  interval.fire();
}

*/

#include "Interval.h"
#include "application.h"

void Interval::debug_timer(const char* label){
  Serial.println("---");
  Serial.println(label);
  Serial.println("---");
  Serial.print("timer_number_inc: ");Serial.println(timer_number_inc);
  Serial.print("timers_count: ");Serial.println(timers_count);
  Serial.print("timers_max: ");Serial.println(timers_max);
  for (int i = 0; i < timers_count; i++){
    Serial.print("Timer ");Serial.print(i);Serial.print(": ");
    Serial.println(timers[i].timer_number);
  }
}

Interval::Interval() {}

void Interval::expand_timers(){ // Expand the number of timers
  int timers_max_old = timers_max;
  timers_max += INITIAL_TIMERS_COUNT;
  timer* new_timers = new timer[timers_max];
  for (int i = 0; i < timers_max_old; i++){
    new_timers[i] = timers[i];
  }
  delete [] timers;
  timers = new_timers;
}

int Interval::createTimer(unsigned long ms, void (*f)(void), int type, int cycles){
  if (timers_count == timers_max){ // Expand the number of timers if needed
    expand_timers();
  }
  timers[timers_count].ms = ms;
  timers[timers_count].counter = ms;
  timers[timers_count].f = f;
  timers[timers_count].timer_number = timer_number_inc++;
  timers[timers_count].timer_type = type;
  timers[timers_count].cycles = cycles;
  timers[timers_count].initialMillis = millis();
  timers_count++;
  return timers[timers_count - 1].timer_number;
}

int Interval::setInterval(unsigned long ms, void (*f)(void)){
  return Interval::createTimer(ms, f, 0, 0);
}

int Interval::setInterval(unsigned long ms, void (*f)(void), int cycles){
  return Interval::createTimer(ms, f, 1, cycles);
}

int Interval::setTimeout(unsigned long ms, void (*f)(void)){
  return Interval::createTimer(ms, f, 1, 1);
}

void Interval::deleteTimer(int n){
  timer* new_timers = new timer[timers_max];
  int target_location = 0;
  for (int i = 0; i < timers_count; i++){
    if (timers[i].timer_number != n){
      new_timers[target_location] = timers[i];
      target_location += 1;
    }
  }
  delete [] timers;
  timers = new_timers;
  timers_count--;
}

int Interval::timersCount(){
  return timers_count;
}

void Interval::fire(){ // Fire / cycle through all timers
  for (int i = 0; i < timers_count; i++){
    if (millis() - timers[i].initialMillis > timers[i].counter){
      timers[i].f();
      timers[i].counter += timers[i].ms;
      if (timers[i].timer_type == 1){
        timers[i].cycles--;
        if (timers[i].cycles == 0)
          Interval::deleteTimer(timers[i].timer_number);
      }
    }
  }
}
