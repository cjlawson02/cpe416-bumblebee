#include "neuron.h"

Neuron::Neuron(std::vector<float> weights, float bias) : m_weights(weights), m_bias(bias)
{
}

Neuron::~Neuron()
{
}

float Neuron::calculate(std::vector<float> inputs)
{
    float net = calculateNet(inputs);
    return activation(net);
}

float Neuron::calculateNet(std::vector<float> inputs)
{
    return 0.0f;
}

float Neuron::activation(float net)
{
    return 1 / (1 + exp(-net));
}
