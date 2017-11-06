#include "neurone.hpp"
#include <iostream> 
#include "constantes.hpp"
#include <fstream>
#include <cassert>


int main()
{
	std::vector<Neurone*> neurones;
		Neurone n1;
		Neurone n2;
	neurones.push_back(&n1);
	neurones.push_back(&n2);
	
	n1.addConnection(&n2);
	n1.set_ext_I(0.0);
	n2.set_ext_I(0.0);
	int a(0);
	int b(5000);
	int simtime(t_start);
	
	while(simtime < t_stop)
	{	
		if(simtime >= a and simtime <= b and a<b)
		{
			n1.set_ext_I(1.01);
		}
		else
			n1.set_ext_I(0.0);
		for(auto& neuron : neurones)
		{
			bool spike(false);
			spike = neuron->update(1);
			if(spike)
			{
				neuron->pass_spike(simtime);
			}
		}
		
		
		simtime += dt;

	};
	
	n1.affiche();
	return 0;
}
