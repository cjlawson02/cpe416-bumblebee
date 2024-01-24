#include <Bumblebee.h>
#include <math.h>
#include "util.h"
#include "timer.h"

#pragma once

class PID
{
public:
    PID(double Kp = 0.0, double Ki = 0.0, double Kd = 0.0);

    void setGains(double Kp = 0.0, double Ki = 0.0, double Kd = 0.0);
    void setTarget(double target);
    double getTarget();
    void reset(double currPosition = NAN);
    void setBounds(double min, double max);

    // These calculate output based on the target and actual
    double calcOutput(double actual);
    double calcOutput(double actual, u16 timeMs);

    // These calculate output based on error
    double calcOutputWithError(double error);
    double calcOutputWithError(double error, u16 timeMs);

private:
    double m_Kp;
    double m_Ki;
    double m_Kd;

    double m_target;
    double m_min;
    double m_max;

    double m_timeLastUpdateSec;
    double m_prevPos;
    double m_prevErr;
    double m_integral;

    double m_lastOutput;
};
