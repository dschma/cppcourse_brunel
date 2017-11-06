#include "neurone.hpp"
#include "constantes.hpp"
#include <cmath>
#include <iostream>
#include <cassert>
#include <random>

Neurone::Neurone(double J_)
:potential(0.0), 
nb_spikes(0.0), 
I_ext(0.0),
my_time(0), 
spike_buffer({0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}),
J(J_)
{}

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

double Neurone::get_J() const
{
	return J;
}

std::vector<int> Neurone::getSpikes() const
{
	return times_spikes;
}

double Neurone::get_spike_buffer(int time) const
{
	return spike_buffer[time%(D+1)];
}

void Neurone::setPotential(double new_potential) 
{
	potential = new_potential;
}

void Neurone::set_ext_I(const double& new_I)
{
	I_ext = new_I;
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

void Neurone::addSpikeTime(int time)
{
	times_spikes.push_back(time);
}

bool Neurone::update(const int& poisson)
{
	bool spike(false);
	double S(spike_buffer[my_time%(D+1)]);
	
	if(potential >= Vth)
	{
		addSpikeTime(my_time);
		nb_spikes++;
		spike = true;
		setPotential(0.0);
	}
	else if(isRefractory())
	{
		setPotential(0.0);
	}
	else
	{
		double newPotential(c1*potential + I_ext*c2 + S + Je*poisson);
		potential = newPotential;
	}

	spike_buffer[my_time%(D+1)] = 0.0;
	my_time += dt;
	return spike;
}

void Neurone::receive_spike(unsigned int time_arrival, double psp)
{
	size_t idx(time_arrival%(D+1));
	assert(idx < spike_buffer.size());
	spike_buffer[idx]+= psp;
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


