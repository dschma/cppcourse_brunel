#include "neurone.hpp"
#include <iostream> 
#include "constantes.hpp"
#include <fstream>


int main()
{
	Neurone n1;
	int a(0);
	int b(10000);
	int simtime(t_start);
	double I_ext(0.0);
	
	std::ofstream the_potentials;
	the_potentials.open("Membrane_potentials.txt");
	the_potentials << "Membrane potentials: " << std::endl;
	
	while(simtime < t_stop)
	{	
		if(simtime>=a and simtime<=b and a<b)
		{
			I_ext = 1.1;
		}
		else
			I_ext = 0.0;
			
		n1.update(I_ext);
		the_potentials << n1.getPotential() << std::endl;
		simtime += dt;

	};
	
	the_potentials.close();
	n1.affiche();
	
	return 0;
}
