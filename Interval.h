#ifndef INTERVAL
#define INTERVAL
#define INITIAL_TIMERS_COUNT 5

class Interval {
  private:
    struct timer {
      unsigned long counter;
      unsigned long ms;
      void (*f)(void);
      int timer_number;
      int timer_type;
      int cycles;
      int initialMillis;
    };

    int timers_count = 0;
    int timers_max = INITIAL_TIMERS_COUNT;
    timer* timers = new timer[timers_max];
    int timer_number_inc = 0;
    void expand_timers();
    int createTimer(unsigned long ms, void (*f)(void), int type, int cycles);

  public:
    Interval();
    int setInterval(unsigned long ms, void (*f)(void));
    int setInterval(unsigned long ms, void (*f)(void), int cycles);
    int setTimeout(unsigned long ms, void (*f)(void));
    void deleteTimer(int);
    void fire();
    void debug_timer(const char*);
    int timersCount();
};
#endif
