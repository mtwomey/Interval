# Interval
Timing library for Particle Photon

There are other usable libraries that acieve similar results, however, I wanted to be able to customize some specific capabilities. One unique aspect of this library is that it can dynamically create new timers (limited only by memory).

**Versions**

V1.5 First released version

**Public Methods**

######int setInterval(unsigned long ms, void (*f)(void))######

Creates a timer which will fire repeatedly (unless it is later deleted). Returns an int identifying the timer.

|Parameter|Description|
|---------|:----------|
|f|pointer to a void function|
|ms|function will fire every ms milliseconds|

######int setInterval(unsigned long ms, void (*f)(void), int cycles)######

Creates a time which will fire a certain number of times and then delete itself. Returns an int identifying the timer.

|Parameter|Description|
|---------|:----------|
|f|pointer to a void function|
|ms|function will fire every ms milliseconds|
|cycles|After this number of times, the timer will be deleted|

######int setTimeout(unsigned long ms, void (*f)(void))######

Creates a timer which will fire one time, and then delete itself. Returns an int identifying the timer.

|Parameter|Description|
|---------|:----------|
|f|pointer to a void function|
|ms|function will fire once, after ms milliseconds|

f: pointer to a void function<br>
ms: function will fire ever ms milliseconds<br>

######void deleteTimer(int id)######

Deletes a timer.

|Parameter|Description|
|---------|:----------|
|id|ID of the timer to delete|

######void fire()######

Include this in your loop() function. This is what makes the whole thing work :-)
