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

    for (size_t i = 0; i < 500; i++)
    {
        for (size_t j = 0; j < m_data.size(); j++)
        {
            m_neural->train(m_data[j], m_alpha);
        }
    }

    lcd_cursor(0, 1);
    print_string("Done");
}

void TrainingMode::periodic()
{
}

void TrainingMode::postPeriodic()
{
}
