#include "neurone.hpp"
#include "constantes.hpp"
#include <cmath>
#include <iostream>

Neurone::Neurone()
:potential(0.0), nb_spikes(0.0), time(0)
{}

double Neurone::getPotential() const
{
	return potential;
}

unsigned int Neurone::getNbSpikes() const
{
	return nb_spikes;
}

void Neurone::setPotential(double p) 
{
	potential = p;
}

int Neurone::getLastSpikeTime() const
{
	return times_spikes[times_spikes.size()-1];
}

bool Neurone::isRefractory()
{
	if(times_spikes.size() == 0)
		return false;
	if(time - getLastSpikeTime() < refractory_time)
		return true;
	return false;
}

void Neurone::addSpikeTime(int simtime)
{
	times_spikes.push_back(simtime);
}

void Neurone::update(double I_ext)
{
	if(potential >= Vth)
	{
		addSpikeTime(time);
	}
	
	if(isRefractory())
		setPotential(0.0);
	else
		potential = exp(-h/tau)*potential + I_ext*membrane_resistance*(1-exp(-h/tau));
	
	time = time+dt;
}

void Neurone::affiche()
{
	std::cout << "Neurone informations " << std::endl;
	std::cout << "Membrane resistance = " << membrane_resistance << std::endl;
	std::cout << "Times of spike " << std::endl;
	if( times_spikes.empty())
		std::cout << " no spike " << std::endl;
	else
	{
		for(size_t i(0); i<times_spikes.size(); i++)
		{
			std::cout << times_spikes[i]*h << ", ";
		}
	}
}
