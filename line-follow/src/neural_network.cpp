#include "neural_network.h"

NeuralNetwork::NeuralNetwork(std::vector<size_t> topology)
    : m_topology(topology)
{

    for (size_t i = 0; i < m_topology.size(); i++)
    {
        size_t numNeurons = m_topology[i];
        for (size_t j = 0; j < numNeurons; j++)
        {
            Neuron *neuron = new Neuron(getRandWeights(3), 0.0);
            neuronLayers[j].push_back(neuron);
        }
    }
}

NeuralNetwork::~NeuralNetwork()
{
}

float NeuralNetwork::calculate(std::vector<float> inputs)
{
    return 0.0f;
}

std::vector<float> NeuralNetwork::getRandWeights(size_t numWeights)
{
    std::vector<float> weights;
    for (size_t i = 0; i < numWeights; i++)
    {
        weights.push_back(rand() % 100 / 100.0f);
    }
    return weights;
}
