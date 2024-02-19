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

//Overwrites values of passed in neueral network to current neural network of same topology
void NeuralNetwork::copy_in_nn(NeuralNetwork *nn)
{
    for (size_t i = 0; i < m_topology.size(); i++)
    {
        size_t numNeurons = m_topology[i];
        for (size_t j = 0; j < numNeurons; j++)
        {
            // If we are on the first layer, the number of inputs is the number of inputs to the network
            neuronLayers[i][j]->setBias(nn->neuronLayers[i][j]->getBias());
            neuronLayers[i][j]->setWeights(nn->neuronLayers[i][j]->getWeights());
        }
    }
}

NeuralNetwork::~NeuralNetwork()
{
    //clear out the neurons
    
    // for (size_t i = 0; i < m_topology.size(); i++)
    // {
    //     std::vector<Neuron *> layer;
    //     size_t numNeurons = m_topology[i];
    //     for (size_t j = 0; j < numNeurons; j++)
    //     {
    //         //delete layer[i];
    //         layer.pop_back(); //idk why pop back works and delete does not yet
    //     }
    //     neuronLayers.pop_back();
    // } 
}

std::vector<float> NeuralNetwork::calculate(const std::vector<float> inputs)
{
    // If the number of inputs doesn't match the number of inputs for the network, return an empty vector
    if (inputs.size() != m_num_inputs) // TODO: double check
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

void NeuralNetwork::train(TrainingData data_pt, NeuralNetwork *temp_network, float alpha)
{
    // Back propagation
    // outer for loop will go through all the points

    // First work on the output layer
    // must scale analog inputs to a value between 0 and 1
  
    std::vector<float> inputs = {analog_to_percent(data_pt.left_ir_reading), analog_to_percent(data_pt.right_ir_reading)};
    std::vector<float> outputs = calculate(inputs); //neural netowrk outputs
    
    // does in[left] correspond to output[left]?
    // the new network we will calculate.'
    // make the new network we will write update values too
    //NeuralNetwork new_network(m_num_inputs, m_topology);

    float etotal_wgt_pd;
    float etotal_outneuronop_pd, outneuronop_ONnet_pd, oNnet_wgt_pd;
    float etotal_hiddennueronop_pd, hiddennueronop_HNnet_pd, hNnet_wgt_pd;
    // float eoutneuron_HNop;
    float mapped_target;
    float speed_to_map;
    float new_weight, new_bias;
    std::vector<float> etotalONX_ONXnet_pd;

    // Train the output layer
    for (size_t i = 0; i < m_topology.back(); i++)
    {
        speed_to_map = (i == 0) ? data_pt.speeds.left_speed : data_pt.speeds.right_speed;
        mapped_target = Util::map(speed_to_map, -100.0, 100.0, 0.0, 1.0);
        etotal_outneuronop_pd = outputs[i] - mapped_target;
        outneuronop_ONnet_pd = outputs[i] * (1 - outputs[i]);
        etotalONX_ONXnet_pd.push_back(etotal_outneuronop_pd * outneuronop_ONnet_pd);

        // work on the weights first
        if (m_topology.size() > 1)
        {
            // go through all the weights (number of weights is number of neurons in previous layer)
            for (size_t j = 0; j < m_topology[m_topology.size() - 2]; j++)
            {
                // look at the previous layer neuron inpu corresponding to weight j
                oNnet_wgt_pd = neuronLayers[m_topology.size() - 2][j]->calculate(inputs);

                etotal_wgt_pd = etotal_outneuronop_pd * outneuronop_ONnet_pd * oNnet_wgt_pd;

                new_weight = neuronLayers[m_topology.size() - 1][i]->getWeight(j) - alpha * etotal_wgt_pd;
                // look at the current neuron
                temp_network->neuronLayers[m_topology.size() - 1][i]->setWeight(j, new_weight);
                //new_network.neuronLayers[m_topology.size() - 1][i]->setWeight(j, new_weight);
                // new_network.neuronLayers[m_topology.size() - 1][j] =
            }
        }

        etotal_wgt_pd = etotal_outneuronop_pd * outneuronop_ONnet_pd * -1.0;
        new_bias = neuronLayers[m_topology.size() - 1][i]->getBias() - alpha * etotal_wgt_pd;
        temp_network->neuronLayers[m_topology.size() - 1][i]->setBias(new_bias);
        //new_network.neuronLayers[m_topology.size() - 1][i]->setBias(new_bias);
        // neuronLayers[neuronLayers.size()-1][i]
        
    }

    // NO OTHER INTERMEDIATE HIDDEN LAYERS ASSUMED

    float out_hidden_neuron;

    // input layer (hidden layer 0). For each neuron in the hidden layer
    for (size_t i = 0; i < m_topology.front(); i++)
    {
        // work on the weights first
        if (m_topology.size() > 1)
        {
            out_hidden_neuron = neuronLayers[0][i]->calculate(inputs);
            hiddennueronop_HNnet_pd = (out_hidden_neuron) * (1 - out_hidden_neuron);

            etotal_hiddennueronop_pd = 0.0;
            // go through all the output neurons connected to this neuron

            // computer stuff based on connections to output layer
            for (size_t j = 0; j < m_topology[m_topology.size() - 1]; j++)
            {
                etotal_hiddennueronop_pd += (etotalONX_ONXnet_pd[j] * (neuronLayers[m_topology.size() - 1][j]->getWeight(i)));
            }

            // then compute stuff based on the inputs recieved (the third term we need) and update the two associatd weights
            for (size_t j = 0; j < m_num_inputs; j++)
            {
                hNnet_wgt_pd = inputs[j];
                etotal_wgt_pd = etotal_hiddennueronop_pd * hiddennueronop_HNnet_pd * hNnet_wgt_pd;
                new_weight = neuronLayers[0][i]->getWeight(j) - alpha * etotal_wgt_pd;
                temp_network->neuronLayers[0][i]->setWeight(j, new_weight);
                //new_network.neuronLayers[0][i]->setWeight(j, new_weight);
            }
            etotal_wgt_pd = etotal_hiddennueronop_pd * hiddennueronop_HNnet_pd * -1.0;
            new_bias = neuronLayers[0][i]->getBias() - alpha * etotal_wgt_pd;
            //new_network.neuronLayers[0][i]->setBias(new_bias);
            temp_network->neuronLayers[0][i]->setBias(new_bias);
        }
    }

   // etotalONX_ONXnet_pd.pop_back();
    //etotalONX_ONXnet_pd.pop_back();
 
    //clear_screen();
    // final step: copy the new network over the current one.
   // std::copy(neuronLayers.begin(), neuronLayers.end(), std::back_inserter(temp_network->neuronLayers));
    copy_in_nn(temp_network);
    
   
    // lcd_cursor(0, 1);
    // print_num((u16)data_pt.left_ir_reading);
    // clear_screen();
    //delete new_network;
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
