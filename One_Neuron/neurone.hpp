#ifndef NEURONE_H
#define NEURONE_H
#include <vector> 

///////////////////////////////Constantes///////////////////////////////
constexpr double tau(20.0);
constexpr int refractory_time(2);
constexpr double membrane_resistance(tau);

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
			
///////////////////////////////Setters///////////////////////////////
/**
 * Change le potentiel de la membrane
 * @param : double : the new value of the membrane potential
 */
void setPotential(double);

/////////////////////////////////////////////////////////////
/**
 * Update the state of the neuron of one simulation step, with the external courrent that was passed
 * @param : double - the external current
 */
void update(double I_ext);
	
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

private:
		
	double potential;				//membrane potential
	unsigned int nb_spikes;			//number of spikes it made
	std::vector<int> times_spikes;	//time of the spikes it made
	double time;					//neuron specific clock
	
};

#endif
