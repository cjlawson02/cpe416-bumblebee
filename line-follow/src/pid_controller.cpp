#include "pid_controller.h"

PID::PID(float Kp, float Ki, float Kd)
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

void PID::setGains(float Kp, float Ki, float Kd)
{
    m_Kp = Kp;
    m_Ki = Ki;
    m_Kd = Kd;
}

void PID::setTarget(float target)
{
    m_target = target;
}

float PID::getTarget()
{
    return m_target;
}

void PID::reset(float currPosition)
{
    m_integral = 0.0;
    m_prevPos = currPosition;
    m_timeLastUpdateSec = 0.0;
}

void PID::setBounds(float min, float max)
{
    m_min = min;
    m_max = max;
}

float PID::calcOutput(float actual)
{
    float error = m_target - actual;
    float derivative = 0;
    float output;

    /**
     * m_timeLastUpdate will be zero if this is the first call ever or first
     * call since a reset. In this case there aren't enough samples to
     * integrate or differentiate.
     */
    if (m_timeLastUpdateSec != 0.0)
    {
        float deltaTimeSec = secs() - m_timeLastUpdateSec;

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

float PID::calcOutputWithError(float error)
{
    float derivative = 0;
    float output;

    /**
     * m_timeLastUpdate will be zero if this is the first call ever or first
     * call since a reset. In this case there aren't enough samples to
     * integrate or differentiate.
     */
    if (m_timeLastUpdateSec != 0.0)
    {
        float deltaTimeSec = secs() - m_timeLastUpdateSec;

        m_integral += error * deltaTimeSec;

        if (m_prevPos != NAN && m_prevErr != NAN && deltaTimeSec != 0.0)
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
