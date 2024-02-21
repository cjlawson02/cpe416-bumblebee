#pragma once

#include <Bumblebee.h>
#include "state_handler.h"
#include "light_sensor.h"
#include "calibration_data.h"

class TuningMode : public IRobotState
{
public:
    TuningMode();
    ~TuningMode();

    void init() override;
    void periodic() override;
    void postPeriodic() override;
    bool btnPressed() override;
    void btnHeld() override;

    enum CalibrationState
    {
        CALIBRATE_LEFT_WHITE,
        CALIBRATE_LEFT_BLACK,
        CALIBRATE_RIGHT_WHITE,
        CALIBRATE_RIGHT_BLACK,
        CONFIRM_CALIBRATION
    };

    bool m_editMode = false;
    CalibrationState m_calibrationState = CALIBRATE_LEFT_WHITE;

    int m_leftWhite, m_leftBlack, m_rightWhite, m_rightBlack;

private:
};
