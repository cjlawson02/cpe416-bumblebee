#pragma once

#include <Bumblebee.h>
#include <vector>
#include <cstdlib>
#include <new.h>
#include "neuron.h"
#include "robot.h"

class NeuralNetwork
{
public:
    /**
     * @brief NeuralNetwork class represents a simple neural network for line following.
     *
     * The NeuralNetwork class is responsible for storing the weights and biases of the neurons.
     * It is used in the implementation of a neural network for line following.
     */
    NeuralNetwork(const size_t numInputs, const std::vector<size_t> topology);
    ~NeuralNetwork();

    /**
     * @brief Calculates the output of the neural network given the inputs.
     *
     * @param inputs The inputs to the neural network.
     * @return The output of the neural network.
     */
    std::vector<float> calculate(const std::vector<float> inputs);
    void NeuralNetwork::train(TrainingData data_pt, float alpha);

private:
    void recalc_weights(size_t layer, NeuralNetwork old_net);
    std::vector<size_t> m_topology;
    std::vector<std::vector<Neuron *>> neuronLayers;
    size_t m_num_inputs;

    std::vector<float> getRandWeights(const size_t numWeights);
};
