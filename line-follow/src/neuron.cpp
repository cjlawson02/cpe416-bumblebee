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

void Neuron::setWeights(std::vector<float> weights)
{
    m_weights = weights;
}

std::vector<float> Neuron::getWeights()
{
    return m_weights;
}

void Neuron::setWeight(size_t number, float weight)
{
    if (number < m_weights.size())
    {
        m_weights[number] = weight;
    }
}

float Neuron::getWeight(size_t number)
{
    if (number < m_weights.size())
    {
        return m_weights[number];
    }
    return -1.0;
}

float Neuron::getBias()
{
    return m_bias;
}

void Neuron::setBias(float bias)
{
    m_bias = bias;
}
