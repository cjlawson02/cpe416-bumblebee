#include "state_handler_neural.h"

NeuralMode::NeuralMode(Drivetrain *drivetrain, NeuralNetwork *neuralNetwork)
    : m_drivetrain(drivetrain), m_neuralNetwork(neuralNetwork)
{
    m_stateName = NEURAL_NETWORK_MODE;
}

NeuralMode::~NeuralMode()
{
}

void NeuralMode::init()
{
    clear_screen();
    print_string("Neural");
}

void NeuralMode::periodic()
{
    // TODO: check percent vs raw
    struct MotorCommand speeds;
    speeds = m_drivetrain->compute_neural_network(m_neuralNetwork, {analog_to_percent(get_left_IR_raw()), analog_to_percent(get_right_IR_raw())});
    m_drivetrain->set_speed(speeds);
}

void NeuralMode::postPeriodic()
{
    m_drivetrain->stop();
}

bool NeuralMode::btnPressed()
{
    return true;
}

void NeuralMode::btnHeld()
{
}
