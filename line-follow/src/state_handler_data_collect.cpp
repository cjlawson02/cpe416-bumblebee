#include "state_handler_data_collect.h"

DataCollectMode::DataCollectMode(Drivetrain *drivetrain, PID *pidController, std::vector<struct TrainingData> data)
    : m_drivetrain(drivetrain), m_pidController(pidController), m_lastDataTime(0), m_data(data)
{
    m_stateName = DATA_COLLECT_MODE;
}

DataCollectMode::~DataCollectMode()
{
}

void DataCollectMode::init()
{
    m_drivetrain->stop();
    clear_screen();
    print_string("Data");
}

void DataCollectMode::periodic()
{
    u08 left_ir_reading;
    u08 right_ir_reading;

    if (millis() - m_lastDataTime > 300)
    {
        m_lastDataTime = millis();
        left_ir_reading = get_left_IR_raw();
        right_ir_reading = get_right_IR_raw();

        m_data.push_back({left_ir_reading,
                          right_ir_reading,
                          m_drivetrain->compute_proportional(m_pidController, 15, left_ir_reading, right_ir_reading)});

        clear_screen();
        print_string("Data");
        lcd_cursor(5, 0);
        print_num(m_data.size());
        lcd_cursor(0, 1);
        print_num(left_ir_reading);
        lcd_cursor(4, 1);
        print_num(right_ir_reading);
    }
}

void DataCollectMode::postPeriodic()
{
}
