#include "state_handler_training.h"
#include <time.h>
#include <util/delay.h>

TrainingMode::TrainingMode(NeuralNetwork *nn, NeuralNetwork *temp_nn, std::vector<struct TrainingData> *data_pts, float alpha)
    : m_neural(nn), m_temp_neural(temp_nn), m_data(data_pts), m_alpha(alpha), m_startTime(0), m_epoch(0), m_j(0)
{
    m_stateName = TRAINING_MODE;
}

TrainingMode::~TrainingMode()
{
}

void TrainingMode::init()
{
    // Print out the training screen
    clear_screen();
    print_string("Training");

    lcd_cursor(0, 1);
    print_string("Pts: ");
    lcd_cursor(5, 1);
    print_num((u16)m_data->size());

    m_startTime = millis();
}

void TrainingMode::periodic()
{
    // Show the training screen for 2 seconds
    if (millis() - m_startTime < 2000)
    {
        return;
    }

    // Train the neural network
    if (m_epoch < 150)
    {
        m_neural->train((*m_data)[m_j], m_temp_neural, m_alpha);

        // Move to the next data point
        if (m_j < m_data->size() - 1)
        {
            m_j++;
        }

        // Move to the next epoch
        else
        {
            m_j = 0;
            m_epoch++;

            clear_screen();
            print_string("Training");
            lcd_cursor(0, 1);
            print_num((u16)m_epoch);
            _delay_ms(10);
        }
    }
}

void TrainingMode::postPeriodic()
{
    // Training is done
    clear_screen();
    print_string("Training");
    lcd_cursor(0, 1);
    print_string("Done");
}
