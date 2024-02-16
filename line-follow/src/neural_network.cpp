#include "neural_network.h"

NeuralNetwork::NeuralNetwork(const std::vector<size_t> topology)
    : m_topology(topology)
{
    for (size_t i = 0; i < m_topology.size(); i++)
    {
        std::vector<Neuron *> layer;
        size_t numNeurons = m_topology[i];
        for (size_t j = 0; j < numNeurons; j++)
        {
            // TODO: fix num weights
            Neuron *neuron = new Neuron(getRandWeights(3), 0.0);
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
