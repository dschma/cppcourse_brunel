#include "neurone.hpp"
#include "constantes.hpp"
#include <cmath>
#include <iostream>
#include <cassert>

Neurone::Neurone()
:potential(0.0), 
nb_spikes(0.0), 
my_time(0), 
I_ext(0.0),
spike_buffer({0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0})
{}

Neurone::~Neurone()
{
	for( auto& neurone : target_neurons)
	{
		neurone = nullptr;
	}
	target_neurons.clear();
}

double Neurone::getPotential() const
{
	return potential;
}

unsigned int Neurone::getNbSpikes() const
{
	return nb_spikes;
}

int Neurone::get_I_ext() const
{
	return I_ext;
}

void Neurone::setPotential(double p) 
{
	potential = p;
}

void Neurone::set_ext_I(const double& I)
{
	I_ext = I;
}

int Neurone::getLastSpikeTime() const
{
	int spike_size(times_spikes.size());
	if(spike_size >=1)
		return times_spikes[spike_size-1];
	return -1;
}

bool Neurone::isRefractory()
{
	if(times_spikes.empty())
		return false;
	if(my_time - getLastSpikeTime() < refractory_time)
		return true;
	return false;
}

void Neurone::addSpikeTime(int simtime)
{
	times_spikes.push_back(simtime);
}

bool Neurone::update(int nb_steps)
{
	int steps(0);
	bool spike(false);
	while(steps < nb_steps)
	{
		double S(spike_buffer[my_time%(D+1)]);
	
		if(potential>=Vth)
		{
			addSpikeTime(my_time);
			nb_spikes++;
			spike = true;
		}
	
		if(isRefractory())
		{
			setPotential(0.0);
		}
		else
		{
			potential = c1*potential + I_ext*c2 + S;
		}
	
		spike_buffer[my_time%(D+1)] = 0;
		my_time += dt;
		steps +=1;
	}
	return spike;
}

void Neurone::receive_spike(unsigned int time_arrival, double j)
{
	size_t idx(time_arrival%(D+1));
	assert(idx < spike_buffer.size());
	spike_buffer[idx]+=j;
}

void Neurone::addConnection(Neurone* n)
{
	target_neurons.push_back(n);
}

void Neurone::pass_spike(int& t)
{
	for(auto& neuron_connect : target_neurons)
	{
		neuron_connect->receive_spike(t+D, J);
	}
	
}

void Neurone::affiche()
{
	std::cout << "Neurone informations " << std::endl;
	std::cout << "Membrane resistance = " << membrane_resistance << std::endl;
	std::cout << "Times of spike " << std::endl;
	if( times_spikes.empty())
		std::cout << " non spike " << std::endl;
	else
	{
		for(size_t i(0); i<times_spikes.size(); i++)
		{
			std::cout << times_spikes[i] << ", ";
		}
	}
}


