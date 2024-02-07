#include <math.h>

#pragma once

class Neuron
{
public:
    /**
     * @brief Neuron class represents a single neuron in a neural network.
     *
     * The Neuron class is responsible for storing the weights and bias of a neuron.
     * It is used in the implementation of a neural network for line following.
     *
     * @param w1 The weight for the first input.
     * @param w2 The weight for the second input.
     * @param w3 The weight for the third input.
     * @param bias The bias value for the neuron.
     */
    Neuron(float w1, float w2, float w3, float bias);
    ~Neuron();

    /**
     * @brief Calculates the output of the neuron given the inputs.
     *
     * @param x1 The first input.
     * @param x2 The second input.
     * @param x3 The third input.
     * @return The output of the neuron.
     */
    float calculate(float x1, float x2, float x3);

private:
    float w1, w2, w3;
    float bias;

    float calculateNet(float x1, float x2, float x3);
    float activation(float net);
};
