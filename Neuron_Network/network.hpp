#ifndef NETWORK_H
#define NETWORK_H

#include "neurone.hpp"
#include <vector>
#include <string>


///< Class of network of neurons
/*!
 * This class contains a certain number of neurons connected to each other according to the Brunel's paper
 * The class initialize all neurons it will have, create its connections and simulates the interactions 
 */
class Network 
{

public:
////////////////////////////Constructor////////////////////////////
/**
 * Constructor: initialize the network vector and the connections vector
 * @param nb_exc_neurons : number of excitatory neurons on the network
 * @param nb_inh_neurons : number of inhibitory neurons on the network
 * @param g : g = |Ji/Je| value
 * @param eta : eta = nu_ext/nu_thr
 */
Network(int nb_exc_neurons, int nb_inh_neurons, double g = 5, double eta = 2);

////////////////////////Simulation fonctions////////////////////////
/**
 * Simulate a network , updates all the neurons on the network from a t_start to a t_stop and makes a file with the time of spike of the neurons on the network
 * @param neuro_spikes : the name of the file it will fill with the simulation time and the neuron that spiked
 */
void simulation(const std::string& neuro_spikes);

/**
 * Pass spike to neurons that receives a connection from neuron_i
 * @param simtime : the actual simulation step time
 * @param neuron_i : the index of the neuron that has spiked
 */
void pass_spike(const int& simtime, int neuron_i);

/**
 * Returns the 2D vector of connections: function used in testing 
 * @return {vector<vector<int>>}
 */
std::vector<std::vector<int>> getConnections() const;

/**
 * Returns the vector of Neurons : function used in testing
 * @return {vector<Neurones>}	
 */
std::vector<Neurone> getNetwork() const;


		
////////////////////////////Destructor////////////////////////////	
~Network();

private:

std::vector<Neurone> network;				//Neurons on a network
std::vector<std::vector<int>> connections;	//Connections between neurons: matrice of int
unsigned int nb_exc_neurons;				//nombre neurones excitatoires
unsigned int nb_inh_neurons;				//nombre neurones inhibitoires
double g;									//constante g = Ji/Je
double eta;									//eta = nu_ext/nu_thr
double nu_ext;								//rate of spikes coming from outside the network, for each neuron


////////////////////////////Network initialize functions////////////////////
/**
 * Create nb_exc_neurons excitatory neurons in Network constructor
 */
void create_excitatory_neurons();

/**
 * Create nb_inh_neurons inhibitory neurons in Network constructor
 */
void create_inhibitory_neurons();

/**
 * Create connections in a uniform distribution between the neurons. This distribution is stocked in 2D vector connections 
 * The connections vector stores the target neurons of each neuron on the network. 
 * All neurons receive a number of 10% of the total network size of connections. 
 */
void create_connections();

};


#endif
