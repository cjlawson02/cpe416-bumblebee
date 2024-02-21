// Name:  Lorenzo Pedroza and Chris Lawson
// Lab 3
// Description: Robot class to run the robot.

#include "robot.h"

Robot::Robot() : m_dataPts(std::vector<struct TrainingData>()),
                 m_drivetrain(new Drivetrain(SERVO0_PIN, SERVO1_PIN)),
                 m_button(new ButtonDebouncer(10)),
                 m_pidController(new PID(27.2, 0.0, 0.0)),
                 m_neuralNetwork(new NeuralNetwork(NEURAL_INPUTS, NEURAL_TOPOLOGY)),
                 m_temp_neuralNetwork(new NeuralNetwork(NEURAL_INPUTS, NEURAL_TOPOLOGY)),
                 m_tuningMode(new TuningMode()),
                 m_pidMode(new PIDMode(m_drivetrain, m_pidController)),
                 m_dataCollectMode(new DataCollectMode(m_drivetrain, m_pidController, &m_dataPts)),
                 m_dataWaitMode(new DataWaitMode(m_drivetrain, m_pidController)),
                 m_trainingMode(new TrainingMode(m_neuralNetwork, m_temp_neuralNetwork, &m_dataPts, NEURAL_ALPHA)),
                 m_neuralMode(new NeuralMode(m_drivetrain, m_neuralNetwork)),
                 m_stateManager(new StateManager()),
                 m_buttonPressed(false),
                 m_longPressTriggered(false),
                 m_buttonPressTime(0)
{
    m_pidController->setBounds(-100, 100);
}

Robot::~Robot()
{
    delete m_drivetrain;
    delete m_button;
    delete m_pidController;
    delete m_neuralNetwork;
    delete m_tuningMode;
    delete m_pidMode;
    delete m_dataCollectMode;
    delete m_dataWaitMode;
    delete m_trainingMode;
    delete m_neuralMode;
    delete m_stateManager;
}

void Robot::setup()
{
    init_millis(F_CPU);
    init();
    clear_screen();
    m_drivetrain->setup();
    m_stateManager->switchState(m_tuningMode);
}

void Robot::run()
{
    while (1)
    {
        periodic();
    }
}

void Robot::periodic()
{
    bool buttonState = m_button->get();
    unsigned long currentTime = millis();

    if (buttonState && !m_buttonPressed)
    {
        // Button is pressed down
        m_buttonPressed = true;
        m_buttonPressTime = currentTime; // Record the time when the button is first pressed
        m_longPressTriggered = false;    // Reset the long press flag
    }
    else if (!buttonState && m_buttonPressed)
    {
        // Button is released
        if (!m_longPressTriggered && currentTime - m_buttonPressTime < BTN_HOLD_TIME)
        {
            // Button was pressed for less than 2 seconds and when_btn_held wasn't called
            when_btn_pressed();
        }
        m_buttonPressed = false;
    }
    else if (buttonState && m_buttonPressed && !m_longPressTriggered && currentTime - m_buttonPressTime >= BTN_HOLD_TIME)
    {
        // Button is held for 2 seconds or more and when_btn_held hasn't been called yet
        when_btn_held();
        m_longPressTriggered = true; // Prevent when_btn_held from being called repeatedly
    }

    m_stateManager->update();
}

void Robot::when_btn_pressed()
{
    bool shouldChange = m_stateManager->btnPressedSignal();

    if (shouldChange)
    {
        m_stateManager->post();

        switch (m_stateManager->getCurrentState())
        {
        case TUNING_MODE:
            m_stateManager->switchState(m_pidMode);
            break;
        case PID_MODE:
            m_stateManager->switchState(m_dataCollectMode);
            break;
        case DATA_COLLECT_MODE:
            m_stateManager->switchState(m_dataWaitMode);
            break;
        case DATA_WAIT_MODE:
            m_stateManager->switchState(m_trainingMode, true);
            break;
        case TRAINING_MODE:
            m_stateManager->switchState(m_neuralMode, true);
            break;
        case NEURAL_NETWORK_MODE:
            m_stateManager->switchState(m_trainingMode, true);
            break;
        default:
            break;
        }
    }
}

void Robot::when_btn_held()
{
    m_stateManager->btnHeldSignal();
}
