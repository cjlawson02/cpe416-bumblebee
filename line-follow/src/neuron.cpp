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
    return inner_product(inputs.begin(), inputs.end(), m_weights.begin(), 0) - m_bias;
}

float Neuron::activation(float net)
{
    return 1 / (1 + exp(-net));
}
