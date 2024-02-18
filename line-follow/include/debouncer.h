#pragma once

#include "timer.h"

class ButtonDebouncer
{
public:
    ButtonDebouncer(unsigned long interval) : interval_(interval), last_press_time_(0), button_state_(false), last_button_state_(false), stableSince(0) {}

    bool get()
    {
        bool current_state = get_btn();

        if (current_state != last_button_state_)
        {
            last_press_time_ = millis();
            last_button_state_ = current_state;
            stableSince = 0; // Reset stableSince whenever the button_state_ changes
        }
        else if ((millis() - last_press_time_) >= interval_)
        {
            button_state_ = current_state; // Update the button_state_ after the interval_ has passed without changes
        }

        return button_state_;
    }

private:
    unsigned long interval_;
    unsigned long last_press_time_;
    bool button_state_;
    bool last_button_state_;
    unsigned long stableSince;
};
