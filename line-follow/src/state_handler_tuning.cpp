#include "state_handler_tuning.h"

TuningMode::TuningMode()
{
    m_stateName = TUNING_MODE;
}

TuningMode::~TuningMode()
{
}

void TuningMode::init()
{
    clear_screen();
    print_string("Tuning");
}

void TuningMode::periodic()
{
    if (m_editMode)
    {
        switch (m_calibrationState)
        {
        case CALIBRATE_LEFT_WHITE:
            lcd_cursor(0, 3);
            print_string(" ");
            lcd_cursor(0, 1);
            print_num(get_left_IR_raw());
            break;
        case CALIBRATE_LEFT_BLACK:
            lcd_cursor(0, 3);
            print_string(" ");
            lcd_cursor(0, 1);
            print_num(get_left_IR_raw());
            break;
        case CALIBRATE_RIGHT_WHITE:
            lcd_cursor(0, 3);
            print_string(" ");
            lcd_cursor(0, 1);
            print_num(get_right_IR_raw());
            break;
        case CALIBRATE_RIGHT_BLACK:
            lcd_cursor(0, 3);
            print_string(" ");
            lcd_cursor(0, 1);
            print_num(get_right_IR_raw());
            break;
        case CONFIRM_CALIBRATION:
            break;
        default:
            break;
        }
    }
    _delay_ms(10);
}

void TuningMode::postPeriodic()
{
}

bool TuningMode::btnPressed()
{
    if (m_editMode)
    {
        switch (m_calibrationState)
        {
        case CALIBRATE_LEFT_WHITE:
            m_leftWhite = get_left_IR_raw();
            m_calibrationState = CALIBRATE_LEFT_BLACK;
            clear_screen();
            print_string("Cal LB");
            break;
        case CALIBRATE_LEFT_BLACK:
            m_leftBlack = get_left_IR_raw();
            m_calibrationState = CALIBRATE_RIGHT_WHITE;
            clear_screen();
            print_string("Cal RW");
            break;
        case CALIBRATE_RIGHT_WHITE:
            m_rightWhite = get_right_IR_raw();
            m_calibrationState = CALIBRATE_RIGHT_BLACK;
            clear_screen();
            print_string("Cal RB");
            break;
        case CALIBRATE_RIGHT_BLACK:
            m_rightBlack = get_right_IR_raw();
            m_calibrationState = CONFIRM_CALIBRATION;
            clear_screen();
            print_string("Confirm?");
            break;
        case CONFIRM_CALIBRATION:
            CalibrationData::LEFT_WHITE = m_leftWhite;
            CalibrationData::LEFT_BLACK = m_leftBlack;
            CalibrationData::RIGHT_WHITE = m_rightWhite;
            CalibrationData::RIGHT_BLACK = m_rightBlack;
            m_calibrationState = CALIBRATE_LEFT_WHITE;
            m_editMode = false;
            clear_screen();
            print_string("Tuning");
            break;
        default:
            break;
        }

        return false;
    }
    else
    {
        return true;
    }
}

void TuningMode::btnHeld()
{
    m_editMode = !m_editMode;

    if (m_editMode)
    {
        clear_screen();
        print_string("Cal LW");
    }
    else
    {
        m_calibrationState = CALIBRATE_LEFT_WHITE;
        clear_screen();
        print_string("Tuning");
    }
}
