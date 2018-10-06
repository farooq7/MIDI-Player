#include "signal.hpp"

Signal::Signal(unsigned int sampleRate)
{
	sample_rate = sampleRate;
}

unsigned int Signal::getSampleRate()
{
	return sample_rate;
}

void Signal::push_back(double value)
{
	samples.push_back(value);
}

size_t Signal::size()
{
	return samples.size();
}

double Signal::operator[](size_t index)
{
	return samples[index];
}
