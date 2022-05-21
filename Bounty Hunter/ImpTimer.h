#ifndef IMP_TIMER_H_
#define IMP_TIMER_H_

class ImpTimer
{
public:
    ImpTimer();
    ~ImpTimer();

    void start();
    void paused();
    void stop();
    void resume();

    int get_ticks();

    bool is_started();
    bool is_paused();

private:
    int start_tick;
    int paused_tick;

    bool is_paused_;
    bool is_started_;
};


#endif // IMP_TIMER_H_
