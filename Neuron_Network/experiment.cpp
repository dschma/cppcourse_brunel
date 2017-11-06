#include "network.hpp"
#include "neurone.hpp"
#include "constantes.hpp"
#include <string>

void experimentA()
{
	double gA(3.0);
	double etaA(2.25);
	std::string spikes_gA("spikes_A.txt");
	Network networkA(10000, 2500, gA, etaA);
	networkA.simulation(spikes_gA);
	
}

void experimentB()
{
	double gB(6.0);
	double etaB(4.0);
	std::string spikes_gB("spikes_B.txt");
	Network networkB(10000, 2500, gB, etaB);
	networkB.simulation(spikes_gB);
}

void experimentC()
{
	double gC(5.0);
	double etaC(2.0);
	std::string spikes_gC("spikes_C.txt");
	Network networkC(10000, 2500, gC, etaC);
	networkC.simulation(spikes_gC);
}

void experimentD()
{
	double gD(4.5);
	double etaD(0.9);
	std::string spikes_gD("spikes_D.txt");
	Network networkD(10000, 2500, gD, etaD);
	networkD.simulation(spikes_gD);
	
}
