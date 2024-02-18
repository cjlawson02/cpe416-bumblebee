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
}

void TuningMode::postPeriodic()
{
}
