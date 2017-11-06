#include <iostream>
#include "neurone.hpp"
#include "googletest/include/gtest/gtest.h"

TEST(neuronTest, membrane_potential)
{
	Neurone neurone;
	neurone.set_ext_I(1.01);
	neurone.update(1);
	EXPECT_EQ(1.01*20.0*(1-std::exp(-0.1/20.0)), neurone.getPotential());
}

TEST(neuronTest, FirstSpike)
{
	Neurone neurone;
	neurone.set_ext_I(1.01);
	neurone.update(940);
	EXPECT_EQ(924, neurone.getLastSpikeTime());
	EXPECT_EQ(0.0, neurone.getPotential());
	
}

TEST(neuronTest, Spikes)
{
	Neurone neurone;
	neurone.set_ext_I(1.01);
	neurone.update(4000);
	EXPECT_EQ(4, neurone.getNbSpikes());
	
}

TEST(TwoNeurons, NoReceivedSpike)
{
	Neurone n1;
	Neurone n2;
	n1.set_ext_I(1.01);
	//n2 has I_ext = 0.0 par defaut
	EXPECT_EQ(0.0, n2.get_I_ext());
	n1.addConnection(&n2);
	int delay = 15;
	bool spike(false);
	for(int i(0); i<924+delay; ++i)
	{
		spike = n1.update(1);
		if(spike)
			n1.pass_spike(i);
		n2.update(1);
	}
	//there was an spike from n1 but n2 has not yet received, so the membrane potential of n2 is still 0.0
	EXPECT_EQ(0.0, n2.getPotential());
	
	
}

TEST(TwoNeurons, Receive_1_Spike)
{
	Neurone n1;
	Neurone n2;
	n1.set_ext_I(1.01);
	//n2 has I_ext = 0.0 par defaut
	EXPECT_EQ(0.0, n2.get_I_ext());
	n1.addConnection(&n2);
	int delay = 15;
	bool spike(false);
	for(int i(0); i<924+delay+1; ++i)
	{
		spike = n1.update(1);
		if(spike)
			n1.pass_spike(i);
		n2.update(1);
	}
	//the spike was received, n2 has potential greater than 0
	EXPECT_GT(n2.getPotential(), 0.0);
	
	
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
