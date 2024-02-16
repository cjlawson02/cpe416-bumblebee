#include "neural_network.h"

NeuralNetwork::NeuralNetwork(const size_t numInputs, const std::vector<size_t> topology)
    : m_topology(topology)
{
    for (size_t i = 0; i < topology.size(); i++)
    {
        std::vector<Neuron *> layer;
        size_t numNeurons = topology[i];
        for (size_t j = 0; j < numNeurons; j++)
        {
            Neuron *neuron;
            if (i == 0)
            {
                // Input layer
                neuron = new Neuron(getRandWeights(numInputs), 0.0);
            }
            else
            {
                neuron = new Neuron(getRandWeights(topology[i - 1]), 0.0);
            }
            layer.push_back(neuron);
        }
        neuronLayers.push_back(layer);
    }
}

NeuralNetwork::~NeuralNetwork()
{
}

std::vector<float> NeuralNetwork::calculate(const std::vector<float> inputs)
{
    // If the number of inputs doesn't match the number of inputs for the network, return an empty vector
    if (inputs.size() != m_topology[0])
    {
        return std::vector<float>();
    }

    // Calculate on the first layer, then pass those results to the next layer, and so on
    std::vector<float> in = inputs;
    for (size_t i = 0; i < m_topology.size(); i++)
    {
        std::vector<float> results;
        for (size_t j = 0; j < neuronLayers[i].size(); j++)
        {
            results.push_back(neuronLayers[i][j]->calculate(in));
        }
        in = results;
    }

    return in;
}

std::vector<float> NeuralNetwork::getRandWeights(const size_t numWeights)
{
    std::vector<float> weights;
    for (size_t i = 0; i < numWeights; i++)
    {
        weights.push_back(rand() % 100 / 100.0f);
    }
    return weights;
}
