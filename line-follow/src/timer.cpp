#include "timer.h"

volatile unsigned long timer1_millis;

ISR(TIMER1_COMPA_vect)
{
    timer1_millis++;
    servo_isr();
}

void init_millis(unsigned long f_cpu)
{
    unsigned long ctc_match_overflow;

    ctc_match_overflow = ((f_cpu / 1000) / 8) - 1; // calculate the value for 1ms
    TCCR1B |= (1 << WGM12) | (1 << CS11);          // Configure timer 1 for CTC mode with prescaler 8
    OCR1A = ctc_match_overflow;                    // Set CTC compare value
    TIMSK1 |= (1 << OCIE1A);                       // Enable CTC interrupt

    sei(); // Enable global interrupts
    timer1_millis = 0;
}

unsigned long millis()
{
    unsigned long millis_return;

    // Ensure this cannot be disrupted
    ATOMIC_BLOCK(ATOMIC_FORCEON)
    {
        millis_return = timer1_millis;
    }

    return millis_return;
}

unsigned long secs()
{
    return millis() / 1000;
}
