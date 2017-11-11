#ifndef CONST_H
#define CONST_H

/**
 * Simulations and Neuron constants
 */

//-------------------------------Simultion constantes-------------------------------
constexpr int t_start(0);									//simulation start time
constexpr int t_stop(10000);									//simulation stop time
constexpr int dt(1);										//simulation time step
constexpr double h(0.1);									//time step in miliseconds

//-------------------------------Neurone constantes------------------------------
constexpr int D(15);										//Delay to receive spike: D = 1.5ms = 15 times step
constexpr double tau(20.0);									//Membrane time constant [ms]
constexpr int refractory_time(20);							//Refractory time of neuron: 2ms
constexpr double membrane_resistance(tau);					//Membrane resistance of neuron
constexpr double c1(std::exp(-h/tau));						//constante used on the membrane potential update
constexpr double c2(membrane_resistance*(1-exp(-h/tau)));	//constante used on the membrane potential update
constexpr double Je(0.1);									//Spike reponse amplitude for excitatory neurons [mV]
constexpr double Vth(20.0);									//Threshold potential [mV]
constexpr double nu_thr(10.0);								//rate of spikes per second tu reach threshold
//--------------------------------------------------------------------------------

#endif
