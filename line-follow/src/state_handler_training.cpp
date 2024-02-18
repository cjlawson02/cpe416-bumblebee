#include "state_handler_training.h"

TrainingMode::TrainingMode(Drivetrain *drivetrain, PID *pidController)
    : m_drivetrain(drivetrain), m_pidController(pidController)
{
    m_stateName = TRAINING_MODE;
}

TrainingMode::~TrainingMode()
{
}

void TrainingMode::init()
{
    clear_screen();
    print_string("Training");
}

void TrainingMode::periodic()
{
}

void TrainingMode::postPeriodic()
{
}
