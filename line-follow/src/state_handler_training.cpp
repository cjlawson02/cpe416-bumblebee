#include "state_handler_training.h"

TrainingMode::TrainingMode(NeuralNetwork *nn, std::vector<struct TrainingData> data, float alpha)
    : m_neural(nn), m_data(data), m_alpha(alpha)
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

    for (size_t i = 0; i < m_data.size(); i++)
    {
        m_neural->train(m_data[i], m_alpha);
    }
}

void TrainingMode::periodic()
{
}

void TrainingMode::postPeriodic()
{
}
