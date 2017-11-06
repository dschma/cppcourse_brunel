#ifndef NEURONE_H
#define NEURONE_H

#include <vector> 
#include <cmath>
#include "constantes.hpp"

///< Class of neurons objects
/*!
 * This class creates a single neuron and its attributs
 * A neuron can be excitatory of inhibitory according to the value of J it receives
 */
class Neurone  
{
public:
///////////////////////////////Constructor///////////////////////////////
/**
 * Constructor: initialize a neuron
 * @param J_ : the post synaptic potential the neuron gives
 */
Neurone(double J_);
		
///////////////////////////////Getters///////////////////////////////
/**
 * Return membrane potential 
 * @return : potential value
 */
double getPotential() const;

/**
 * Return the number of spikes the neuron made
 * @return : number spikes the neuron did during all simulation
 */
unsigned int getNbSpikes() const;

/**
 * Return the time of the last spike that was made
 * @return : the spike time in time step of simulation
 */
int getLastSpikeTime() const;
			
/**
 * Return the external current received by the neuron
 * @return : external current I_ext
 */
int get_I_ext() const;

/**
 * Return the value of J, the post synaptic potential that is passed when the neuron spikes
 * @return : J value of the neuron
 */
double get_J() const;
		
////////////////////////////////Setters///////////////////////////////
/**
 * Change le potential of the membrane
 * @param new_potential : the new value of the membrane potential
 */
void setPotential(double new_potential);

/**
 * Change the external current for a neuron
 * @param new_I : the new current value
 */
 void set_ext_I(const double& new_I);
/////////////////////////////////////////////////////////////
/**
 * Update the state of the neuron of one simulation step
 * @param poisson - the poisson distribution value that comes from the outside neurons
 */
bool update(const int& poisson);

	
/**
 * To know if the neuron is refractory or not, that is, if it spiked in 2 simulation time step
 * @return boolean : whether the neuron is refractory of not
 */		
bool isRefractory();
		
/**
 * Add a new time of spike to the vector times_spike
 * @param time : the simulation time step of neuron at the moment it spiked
 */
void addSpikeTime(int time);
		
/**
 * Affiche des informations sur le neurone: the membrane resistance and the times it spiked (in ms)
 */
void affiche();
		
/**
 * Update the value of the spike received on the spike buffer
 * @param time_arrival : the time of arrival of the spike
 * @param j : the value of the intensity of the spike the neuron receives
 */
void receive_spike(unsigned int time_arrival, double j);

/**
 * Returns the time_of_spikes vector
 * @return vector<int> : contains all the simulation time step when the neuron spiked
 */
std::vector<int> getSpikes() const;

/**
 * Returns the value of the spike buffer at a time 'time'
 * @param time : time of which we want to know the value of the buffer
 * @return : the value of the spike buffer
 */
double get_spike_buffer(int time) const;

private:
	
	double potential;							//!membrane potential
	unsigned int nb_spikes;						//!number of spikes it made
	double I_ext;								//!External current
	std::vector<int> times_spikes;				//!time of the spikes it made
	int my_time;								//!neuron specific clock in simulation steps
	std::vector<double> spike_buffer;			//!Receives a spike
	double J;									//!Spike reponse amplitude: may be Je or Ji
};

#endif
