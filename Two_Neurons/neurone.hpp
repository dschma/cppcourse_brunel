#ifndef NEURONE_H
#define NEURONE_H

#include <vector> 
#include <cmath>
#include "constantes.hpp"

constexpr double tau(20.0);									//Membrane time constant
constexpr int refractory_time(20);							//Refractory time of neuron: 2ms
constexpr double membrane_resistance(tau);					//Membrane resistance of neuron
constexpr double c1(exp(-h/tau));							//constante used on the membrane potential update
constexpr double c2(membrane_resistance*(1-exp(-h/tau)));	//constante used on the membrane potential update
constexpr double J(0.1);									//Spike reponse amplitude

class Neurone
{
	
public:
///////////////////////////////Constructor///////////////////////////////
Neurone();
		
///////////////////////////////Getters///////////////////////////////
/**
 * Return membrane potential 
 * @return double
 */
double getPotential() const;

/**
 * Return the number of spikes the neuron made
 * @return int
 */
unsigned int getNbSpikes() const;

/**
 * Return the time of the last spike that was made
 * @return int : the spike time in time step of simulation
 */
int getLastSpikeTime() const;
			
/**
 * Return the external current received by the neuron
 * @return int
 */
int get_I_ext() const;
		
////////////////////////////////Setters///////////////////////////////
/**
 * Change le potentiel de la membrane
 * @param : double : the new value of the membrane potential
 */
void setPotential(double);

/**
 * Change the external current for a neuron
 * @param double : the new current value
 */
 void set_ext_I(const double&);
/////////////////////////////////////////////////////////////
/**
 * Update the state of the neuron of one simulation step
 * @param : double simulation steps it should update
 */
bool update(int);
	
/**
 * To know if the neuron is refractory or not, that is, if it spiked in 2 simulation time step
 * @return boolean
 */		
bool isRefractory();
		
/**
 * Add a new time of spike to the vector times_spike
 * @param int : the simulation time step of the spike
 */
void addSpikeTime(int);
		
/**
 * Affiche des informations sur le neurone: the membrane resistance and the times it spiked (in ms)
 */
void affiche();
		
/**
 * Update the value of the spike received on the spike buffer
 * @param unsigned int : the time of arrival of the spike
 * @param double : the value of the intensity of the spike
 */
void receive_spike(unsigned int time_arrival, double j);

/**
 * Passes the spike to the neurons which are connected to this
 * @param int : time when this spiked
 */
void pass_spike(int& t);

/**
 * Add a connection, that is, a pointer to a Neuron in target_neurons
 * @param Neurone* : the neuron to which this is connected
 */
void addConnection(Neurone* n);

bool hasConnection(Neurone* n)
{
	if(target_neurons[0] == n)
		return true;
	return false;
}

	
////////////////////////////////Destructor///////////////////////////////	
~Neurone();
	
private:
	
	double potential;						//membrane potential
	unsigned int nb_spikes;					//number of spikes it made
	double I_ext;							//External current
	std::vector<int> times_spikes;			//time of the spikes it made
	int my_time;							//neuron specific clock in simulation steps
	std::vector<double> spike_buffer; 		//Receives a spike
	std::vector<Neurone*> target_neurons;	//Neurons it is connected to
	
};

#endif
