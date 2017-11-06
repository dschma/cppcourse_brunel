#include "network.hpp"
#include <random>
#include <iostream> 
#include <fstream>
#include <cassert>
#include <string>

Network::Network(int number_exc_neurons, int number_inh_neurons, double g_, double eta_)
:nb_exc_neurons(number_exc_neurons), 
nb_inh_neurons(number_inh_neurons), 
g(g_), 
eta(eta_),
nu_ext(eta*nu_thr)
{
	create_excitatory_neurons();
	create_inhibitory_neurons();
	create_connections();
}

void Network::simulation(const std::string& neuro_spikes)
{
	int simtime(t_start);
	
	std::random_device rd;
	std::mt19937 gen(rd());
	std::poisson_distribution<> pd(nu_ext*h);

	std::ofstream spikes_of_neurons;
	spikes_of_neurons.open(neuro_spikes);

	while(simtime < t_stop)
	{
		for(size_t neuron_i(0); neuron_i<network.size(); ++neuron_i)
		{
			bool spike(false);
			spike = network[neuron_i].update(pd(gen));
			if(spike)
			{
				spikes_of_neurons << simtime << "\t" << neuron_i << "\n";
				pass_spike(simtime, neuron_i);
			}
		}
		simtime += dt;
	};
	spikes_of_neurons.close();
}

void Network::pass_spike(const int& simtime, int neuron_i)
{
	double spike_strength = network[neuron_i].get_J();
	for(auto& target_neuron : connections[neuron_i])
	{
		network[target_neuron].receive_spike(simtime+D,spike_strength);	
	}
}

void Network::create_excitatory_neurons()
{
	for(unsigned int i(0); i<nb_exc_neurons; ++i)
	{
		network.push_back(Neurone(Je));
	}
}

void Network::create_inhibitory_neurons()
{
	for(unsigned int i(0); i<nb_inh_neurons; ++i)
	{
		network.push_back(Neurone(-g*Je));
	}
}

void Network::create_connections()
{
	assert(connections.empty());
	
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> exc(0,nb_exc_neurons-1);
	std::uniform_int_distribution<> inh(nb_exc_neurons, nb_exc_neurons+nb_inh_neurons-1);

	unsigned int network_size(network.size());
	connections = std::vector<std::vector<int>>(network_size);

	for(unsigned int i(0); i<network_size; ++i)
	{
		for(unsigned int k(0); k<nb_exc_neurons/10; ++k)
		{
			int source_e = exc(gen);
			connections[source_e].push_back(i);
		}
		for(unsigned int l(0); l<nb_inh_neurons/10; ++l)
		{
			int source_i = inh(gen);
			connections[source_i].push_back(i);
		}
	}
	assert(connections.size() == network.size());
}

std::vector<std::vector<int>> Network::getConnections() const
{
	return connections;
}

std::vector<Neurone> Network::getNetwork() const
{
	return network;
}

Network::~Network()
{
	network.clear();
	connections.clear();
}
