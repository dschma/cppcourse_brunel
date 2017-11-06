#include <iostream>
#include "neurone.hpp"
#include "googletest/include/gtest/gtest.h"
#include "network.hpp"
#include <cmath>

TEST(NeuronsOfNetwork, g_and_J_inputs)
{
	double epsilon(0.00001);
	Network network(1,1,3,2);
		double j_ext((network.getNetwork())[0].get_J());
		double j_inh((network.getNetwork())[1].get_J());
		ASSERT_TRUE(j_ext - 0.1 <= epsilon );
		ASSERT_TRUE(j_inh-(-0.3) <= epsilon);
		
	Network network2(1,1,6,4);
		double j_ext2((network2.getNetwork())[0].get_J());
		double j_inh2((network2.getNetwork())[1].get_J());
		ASSERT_TRUE(j_ext2  - 0.1 <= epsilon);
		ASSERT_TRUE(j_inh2 -(-0.6) <= epsilon);
		
	Network network3(1,1,5,2);
		double j_ext3((network3.getNetwork())[0].get_J());
		double j_inh3((network3.getNetwork())[1].get_J());
		ASSERT_TRUE(j_ext3 - 0.1 <= epsilon);
		ASSERT_TRUE(j_inh3- (-0.5) <= epsilon);
		
	Network network4(1,1,4.5,0.9);
		double j_ext4((network4.getNetwork())[0].get_J());
		double j_inh4((network4.getNetwork())[1].get_J());
		ASSERT_TRUE(j_ext4 - 0.1 <= epsilon);
		ASSERT_TRUE(j_inh4 -(-0.45) <= epsilon);
	
}

TEST( NeuronsAtNetwork, nb_received_connections)
{
	Network network(10000, 2500);
	std::vector<std::vector<int>> connections(network.getConnections());
	ASSERT_TRUE(connections.size() == 12500);
	
	//we want to know if the one neuron, e.g. neuron 3, receives Ce = 100 and Ci=25 connections
	int nb_exc(0);
	int nb_inh(0);
	unsigned int counter(0);
	for(auto& neuron : connections)
	{
		for(auto& target : neuron)
		{
			if(target == 3)
			{
				if(counter <=9999)
					++nb_exc;
				else if(counter > 9999 and counter <12500)
					++nb_inh;
			}	
		}
		++counter;
	}
	
	EXPECT_EQ(1000, nb_exc);
	EXPECT_EQ(250, nb_inh);
}

TEST(OneNeuron, potential)
{
	Neurone neuron1(Je);
	for(int i(0); i< 150; ++i)
	{	
		neuron1.update(2); 
	}
	
	//we have more or less 0.2mV of spike from the poisson distribution ( 2 spikes reveived per step time)
	//with 150 step times we would have, at least 1 spike, it could be more but probably not
	EXPECT_EQ(neuron1.getNbSpikes(), 1);
}

TEST(TwoNeurons, receive_spike_delay)
{
	Neurone neuron1(Je);
	Neurone neuron2(-5*Je);
	bool spike(false);
	double psp(0.0);
	for(int i(0); i< 150; ++i)
	{	
		spike = neuron1.update(2); 
		if(spike)
		{
			neuron2.receive_spike(i+D, neuron1.get_J());
			psp = neuron2.get_spike_buffer(i+D);
			break;
		}
	}
	ASSERT_TRUE(spike);
	EXPECT_EQ(psp, 0.1);
	EXPECT_EQ(neuron1.getNbSpikes(), 1);
}

TEST(OneNeuron, potential_after_receive_spike)
{
	Neurone n1(Je);
	n1.receive_spike(0, 0.1);
	bool spike(false);
	
	for(int i(0); i<10000 ; i++)
	{
		spike = n1.update(0);
		if(spike)
			break;
	}
	
	ASSERT_TRUE(n1.getPotential() < 0.00001);
	ASSERT_FALSE(spike);
}


int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

