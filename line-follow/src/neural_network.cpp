#include "neural_network.h"

NeuralNetwork::NeuralNetwork(const size_t numInputs, const std::vector<size_t> topology)
    : m_topology(topology), m_num_inputs(numInputs)
{
    for (size_t i = 0; i < topology.size(); i++)
    {
        std::vector<Neuron *> layer;
        size_t numNeurons = topology[i];
        for (size_t j = 0; j < numNeurons; j++)
        {
            // If we are on the first layer, the number of inputs is the number of inputs to the network
            std::vector<float> randWeights = i == 0 ? getRandWeights(numInputs) : getRandWeights(topology[i - 1]);
            float randBias = Util::getRandVal();

            layer.push_back(new Neuron(randWeights, randBias));
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
    if (inputs.size() != m_topology[0]) // TODO: double check
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

void NeuralNetwork::recalc_weights(size_t layer, NeuralNetwork old_net)
{
}

void NeuralNetwork::train(std::vector<struct TrainingData> data_pts)
{
    // Back propagation
    // outer for loop will go through all the points

    // First work on the output layer
    TrainingData data_pt = data_pts[0];
    // must scale analog inputs to a value between 0 and 1
    std::vector<float> inputs = {analog_to_percent(data_pt.left_ir_reading), analog_to_percent(data_pt.right_ir_reading)};
    std::vector<float> outputs = calculate(inputs);

    for (size_t i = 0; i < outputs.size(); i++)
    {
    }

    // does in[left] correspond to output[left]?
    // the new network we will calculate.'
    // make the new network we will write update values too
    NeuralNetwork new_network(m_num_inputs, m_topology);

    for (size_t i = 0; i < m_topology.back(); i++)
    {
        // work on the weights first
        if (m_topology.size() > 1)
        {
            for (size_t j = 0; j < m_topology[m_topology.size() - 2]; j++)
            {
                float total_out_pd;
                if (i == 0)
                {
                    total_out_pd = outputs[i] - data_pt.speeds.left_speed;
                }
                new_network.neuronLayers[m_topology.size() - 1][j] =
            }
        }

        // neuronLayers[neuronLayers.size()-1][i]
    }

    //     //Then work on the hidden layer(s)
    //     for (size_t i = m_topology.size()-2; i >=0; i--)
    //     {

    //         std::vector<float> results;
    //         for (size_t j = 0; j < neuronLayers[i].size(); j++)
    //         {
    //             results.push_back(neuronLayers[i][j].calculate(in));
    //         }
    //         in = results;
    //     }

    //    //Now we can set the weights
    //    for (size_t i = 0; i < neuronLayers[m_topology.size()-1].size(); i++)
    //    {
    //      weights.pop_back() neuronLayers[m_topology.size()-1][i].setWeights();
    //    }
}

std::vector<float> NeuralNetwork::getRandWeights(const size_t numWeights)
{
    std::vector<float> weights;
    for (size_t i = 0; i < numWeights; i++)
    {
        weights.push_back(Util::getRandVal());
    }
    return weights;
}
