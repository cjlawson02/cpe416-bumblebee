#include "state_handler_data_wait.h"

DataWaitMode::DataWaitMode(Drivetrain *drivetrain, PID *pidController)
    : m_drivetrain(drivetrain), m_pidController(pidController), m_lastDataTime(0)
{
    m_stateName = DATA_WAIT_MODE;
}

DataWaitMode::~DataWaitMode()
{
}

void DataWaitMode::init()
{
    m_drivetrain->stop();
    clear_screen();
    print_string("Data");
}

void DataWaitMode::periodic()
{
    struct MotorCommand speeds;
    speeds = m_drivetrain->compute_proportional(m_pidController, 15, get_left_IR_raw(), get_right_IR_raw());
    lcd_cursor(0, 1);
    print_num((u16)speeds.left_speed);
}

void DataWaitMode::postPeriodic()
{
}
