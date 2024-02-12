#pragma once

#include <Bumblebee.h>
#include <vector>
#include <cstdlib>
#include "neuron.h"

class NeuralNetwork
{
public:
    /**
     * @brief NeuralNetwork class represents a simple neural network for line following.
     *
     * The NeuralNetwork class is responsible for storing the weights and biases of the neurons.
     * It is used in the implementation of a neural network for line following.
     */
    NeuralNetwork(std::vector<size_t> topology);
    ~NeuralNetwork();

    /**
     * @brief Calculates the output of the neural network given the inputs.
     *
     * @param x1 The first input.
     * @param x2 The second input.
     * @param x3 The third input.
     * @return The output of the neural network.
     */
    float calculate(std::vector<float> inputs);

private:
    std::vector<size_t> m_topology;
    std::vector<std::vector<Neuron *>> neuronLayers;

    std::vector<float> getRandWeights(size_t numWeights);
};
