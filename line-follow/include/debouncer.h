#pragma once

#include "timer.h"

class ButtonDebouncer
{
public:
    ButtonDebouncer(unsigned long interval) : interval_(interval), last_press_time_(0), button_state_(false), last_button_state_(false) {}

    bool get()
    {
        bool current_state = get_btn();

        if (current_state != last_button_state_)
        {
            last_press_time_ = millis();
        }

        if (millis() - last_press_time_ > interval_ && current_state != button_state_)
        {
            button_state_ = current_state;

            if (button_state_ == true)
            {
                last_button_state_ = current_state;
                return true;
            }
        }

        last_button_state_ = current_state;
        return false;
    }

private:
    unsigned long interval_;
    unsigned long last_press_time_;
    bool button_state_;
    bool last_button_state_;
};
