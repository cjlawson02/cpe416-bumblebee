#include "state_handler_pid.h"

PIDMode::PIDMode(Drivetrain *drivetrain, PID *pidController) : m_drivetrain(drivetrain), m_pidController(pidController)
{
    m_stateName = PID_MODE;
}

PIDMode::~PIDMode()
{
}

void PIDMode::init()
{
    clear_screen();
    print_string("PID");
}

void PIDMode::periodic()
{
    int dir = m_lastWorkingDir;
    // If off track, sweep left and right
    if (off_track())
    {
        // If we just entered off track mode, set the initial time
        if (!m_offTrackMode)
        {
            m_offTrackInitTime = millis();
            m_offTrackMode = true;
        }

        // Turn in place
        m_drivetrain->set_speed_turn(0, dir * 50);

        // If we've been off track for too long, reverse direction
        if (millis() - m_offTrackInitTime > m_offTrackWaitTime)
        {
            dir *= -1;
            m_offTrackInitTime = millis();
            m_offTrackWaitTime *= 2;
        }
    }
    // If we're on track, follow the line
    else
    {
        // If we just got back on track, reset the wait time and turn off off track mode
        if (m_offTrackMode)
        {
            m_offTrackWaitTime = 100;
            m_offTrackMode = false;

            // Save the last working direction that got us back on track
            // This is an educated guess for the next time we go off track
            m_lastWorkingDir = dir;
        }

        // Set the speed and turn based on the PID controller
        struct MotorCommand speeds;
        speeds = m_drivetrain->compute_proportional(m_pidController, 15, get_left_IR_raw(), get_right_IR_raw());
        m_drivetrain->set_speed(speeds);
    }
}

void PIDMode::postPeriodic()
{
}

bool PIDMode::btnPressed()
{
    return true;
}

void PIDMode::btnHeld()
{
}
