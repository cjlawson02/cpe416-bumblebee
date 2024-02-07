#include "neuron.h"

Neuron::Neuron(float w1, float w2, float w3, float bias)
    : w1(w1), w2(w2), w3(w3), bias(bias)
{
}

Neuron::~Neuron()
{
}

float Neuron::calculate(float x1, float x2, float x3)
{
    float net = calculateNet(x1, x2, x3);
    return activation(net);
}

float Neuron::calculateNet(float x1, float x2, float x3)
{
    return w1 * x1 + w2 * x2 + w3 * x3 + bias;
}

float Neuron::activation(float net)
{
    return 1 / (1 + exp(-net));
}
