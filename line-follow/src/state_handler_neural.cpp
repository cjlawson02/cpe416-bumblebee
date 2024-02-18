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
    speeds = m_drivetrain->compute_neural_network(m_neuralNetwork, {get_left_IR_percent(), get_right_IR_percent()});
    m_drivetrain->set_speed(speeds);
}

void NeuralMode::postPeriodic()
{
}
