#include "state_handler_training.h"
#include <time.h>
#include <util/delay.h>

TrainingMode::TrainingMode(NeuralNetwork *nn,NeuralNetwork *temp_nn, std::vector<struct TrainingData> *data_pts, float alpha)
 : m_neural(nn), m_temp_neural(temp_nn), m_data(data_pts), m_alpha(alpha)
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
    
    lcd_cursor(0, 1);
    print_string("Pts: ");
    lcd_cursor(5, 1);
    print_num((u16)m_data->size());

    _delay_ms(2000);

    // clear_screen();


    // print_string("Training");

    //  for (size_t j = 0; j < m_data->size(); j++)
    // {  
    //     lcd_cursor(0, 1);
    //     print_num((u16)(*m_data)[j].speeds.left_speed);
    //     lcd_cursor(4, 1);
    //     print_num((u16) (*m_data)[j].speeds.right_speed);
    //     _delay_ms(1000);
    // }

    clear_screen();
    print_string("Training");

    for (size_t i = 0; i < 150; i++)
    {
        for (size_t j = 0; j < m_data->size()-1; j++)
        {
           m_neural->train((*m_data)[j],m_temp_neural,m_alpha);
        }
        clear_screen();
        print_string("Training");
        lcd_cursor(0, 1);
        print_num((u16)i);
        _delay_ms(10);
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
