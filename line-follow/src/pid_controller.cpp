#include "pid_controller.h"

PID::PID(double Kp, double Ki, double Kd)
{
    m_Kp = Kp;
    m_Ki = Ki;
    m_Kd = Kd;

    m_target = 0;
    m_min = -1;
    m_max = 1;

    m_timeLastUpdateSec = 0.0;
    m_prevPos = NAN;
    m_prevErr = NAN;
    m_integral = 0;
}

void PID::setGains(double Kp, double Ki, double Kd)
{
    m_Kp = Kp;
    m_Ki = Ki;
    m_Kd = Kd;
}

void PID::setTarget(double target)
{
    m_target = target;
}

double PID::getTarget()
{
    return m_target;
}

void PID::reset(double currPosition)
{
    m_integral = 0.0;
    m_prevPos = currPosition;
    m_timeLastUpdateSec = 0.0;
}

void PID::setBounds(double min, double max)
{
    m_min = min;
    m_max = max;
}

double PID::calcOutput(double actual)
{
    return calcOutput(actual, millis());
}

double PID::calcOutput(double actual, u16 time)
{
    double error = m_target - actual;
    double derivative = 0;
    double output;

    /**
     * m_timeLastUpdate will be zero if this is the first call ever or first
     * call since a reset. In this case there aren't enough samples to
     * integrate or differentiate.
     */
    if (m_timeLastUpdateSec != 0.0)
    {
        double deltaTimeSec = secs() - m_timeLastUpdateSec;

        m_integral += error * deltaTimeSec;

        if (m_prevPos != NAN)
        {
            derivative = (actual - m_prevPos) / deltaTimeSec;
        }
    }
    m_timeLastUpdateSec = secs();
    m_prevPos = actual;

    output = m_Kp * error + m_Ki * m_integral +
             m_Kd * derivative;

    output = Util::bound(output, m_min, m_max);

    return output;
}

double PID::calcOutputWithError(double error)
{
    return calcOutputWithError(error, millis());
}

double PID::calcOutputWithError(double error, u16 time)
{
    double derivative = 0;
    double output;

    /**
     * m_timeLastUpdate will be zero if this is the first call ever or first
     * call since a reset. In this case there aren't enough samples to
     * integrate or differentiate.
     */
    if (m_timeLastUpdateSec != 0.0)
    {
        double deltaTimeSec = secs() - m_timeLastUpdateSec;

        m_integral += error * deltaTimeSec;

        if (m_prevPos != NAN)
        {
            derivative = (error - m_prevErr) / deltaTimeSec;
        }
    }
    m_timeLastUpdateSec = secs();
    m_prevErr = error;

    output = m_Kp * error + m_Ki * m_integral +
             m_Kd * derivative;

    output = Util::bound(output, m_min, m_max);

    return output;
}
