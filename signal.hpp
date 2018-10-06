#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include <cstdint>
#include <vector>
using namespace std;

// A Signal holds equally spaceed samples of type double. 
class Signal
{
public:
	//Construct a Signal given a sampling rate is samples-per-second (Hz). The default rate is 44.1 kHz.
	Signal(unsigned int sampleRate = 44100);

	unsigned int getSampleRate();		 // return the sampling rate in Hz.

	void normalize() {}				 // Normalize the Signal to fit into a 16 bit integer when quantized.

	void push_back(double value);		 // Add a sample to the signal. \param value the double sample value to add.

	size_t size();					 // Return the number of samples in the signal.

	double operator[](size_t index);	 // Return the sample at given index. param index the index of the sample to return.

private:
	unsigned int sample_rate;
	vector <double> samples;
};
#endif