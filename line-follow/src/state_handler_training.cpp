#include "state_handler_training.h"

TrainingMode::TrainingMode(NeuralNetwork *nn, NeuralNetwork *temp_nn, std::vector<struct TrainingData> *data_pts, float alpha)
    : m_neural(nn), m_temp_neural(temp_nn), m_data(data_pts), m_alpha(alpha), m_startTime(0), m_epoch(0), m_j(0)
{
    m_stateName = TRAINING_MODE;
}

TrainingMode::~TrainingMode()
{
}

void TrainingMode::printTrainingScreen()
{
    clear_screen();
    print_string("Training");

    lcd_cursor(0, 1);
    print_string("Ep: ");
    lcd_cursor(5, 1);
    print_num((u16)CalibrationData::EPOCHS);
}

void TrainingMode::init()
{
    m_epoch = 0;
    m_j = 0;
    CalibrationData::EPOCHS = 150;
    printTrainingScreen();

    m_startTime = millis();
}

void TrainingMode::periodic()
{
    if (m_editMode)
    {
        lcd_cursor(0, 1);
        print_num((u16)CalibrationData::EPOCHS);
        m_startTime = millis();
        return;
    }

    // Show the training screen for 2 seconds
    if (millis() - m_startTime < 2000)
    {
        return;
    }

    // Train the neural network
    if (m_epoch < CalibrationData::EPOCHS)
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

            lcd_cursor(0, 1);
            print_string("    ");
            lcd_cursor(0, 1);
            print_num((u16)m_epoch);
        }
    }
    else
    {
        lcd_cursor(0, 1);
        print_string("Done    ");
    }
}

void TrainingMode::postPeriodic()
{
}

bool TrainingMode::btnPressed()
{
    // Don't allow mode switching while training
    if (m_editMode)
    {
        // Add 15 to the epoch, and if it's over 450, reset it to 150
        CalibrationData::EPOCHS += 50;
        if (CalibrationData::EPOCHS > 800)
        {
            lcd_cursor(0, 1);
            print_string("   ");
            CalibrationData::EPOCHS = 150;
        }

        return false;
    }
    else
    {
        return true;
    }
}

void TrainingMode::btnHeld()
{
    // Toggle edit mode
    if (m_editMode)
    {
        printTrainingScreen();
        m_editMode = false;
    }
    else
    {
        clear_screen();
        print_string("Epochs");
        // If we are starting to edit, reset the epoch to 150
        CalibrationData::EPOCHS = 150;
        m_editMode = true;
    }
}
