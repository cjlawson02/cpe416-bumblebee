#pragma once

#include <Bumblebee.h>
#include "state_handler.h"

class TuningMode : public IRobotState
{
public:
    TuningMode();
    ~TuningMode();

    void init() override;
    void periodic() override;
    void postPeriodic() override;

    enum CalibrationState
    {
        CALIBRATE_LEFT_WHITE,
        CALIBRATE_LEFT_BLACK,
        CALIBRATE_RIGHT_WHITE,
        CALIBRATE_RIGHT_BLACK,
        CONFIRM_CALIBRATION
    };

private:
};
