#pragma once

#include <stddef.h>
#include <math.h>
#include <vector>

/**
 * @brief Neuron class represents a single neuron in a neural network.
 *
 * The Neuron class is responsible for storing the weights and bias of a neuron.
 * It is used in the implementation of a neural network for line following.
 */
class Neuron
{
public:
    /**
     * @brief Neuron constructor.
     *
     * @param weights The weights for the neuron.
     * @param bias The bias value for the neuron.
     */
    Neuron(std::vector<float> weights, float bias);

    /**
     * @brief Neuron destructor.
     */
    ~Neuron();

    /**
     * @brief Calculates the output of the neuron given the inputs.
     *
     * @param inputs The inputs to the neuron.
     * @return The output of the neuron.
     */
    float calculate(std::vector<float> inputs);

    /**
     * @brief Sets the weights of the neuron.
     *
     * @param weights The new weights for the neuron.
     */
    void setWeights(std::vector<float> weights);

private:
    std::vector<float> m_weights; // The weights of the neuron
    float m_bias;                 // The bias value of the neuron

    /**
     * @brief Calculates the net input of the neuron.
     *
     * @param x1 The first input.
     * @param x2 The second input.
     * @param x3 The third input.
     * @return The net input of the neuron.
     */
    float calculateNet(std::vector<float> inputs);

    /**
     * @brief Applies the activation function to the net input.
     *
     * @param net The net input.
     * @return The output of the neuron.
     */
    float activation(float net);
};
