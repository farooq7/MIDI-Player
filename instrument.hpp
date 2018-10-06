#ifndef INSTRUMENT_HPP
#define INSTRUMENT_HPP

#include "event.hpp"
#include "track.hpp"

const double envelope_scale_factor = 0.25;
// The default instrument. A simple fixed length note instrument using a sinusoid weighted by an envelope function.
class DefaultInstrument
{
public:
	DefaultInstrument() = delete;								  // No default constructor. A DefaultInstrument must have an associated track.
	DefaultInstrument(const DefaultInstrument &) = delete;				 // Cannot be copied. 
	DefaultInstrument & operator=(const DefaultInstrument &) = delete;	 // Cannot be assigned.
	DefaultInstrument(const Track &track, double rate);		// Construct a Default Instrument using the specified track. param track the track to read events from. 

												// Returns true of the DefaultInstrument has stopped processing events.
												// This can occu e.g. if all events have been consumed or a EndTrackEvent has been processed.
	bool halted();

	// Return the sample after the (real) time increment. Samples the 
	// instrument based on its state after processing all events prior to this time.
	// \param deltaT the time increment in seconds.
	double sample(double deltaT);
	void reset();

private:
	Track track_;
	double tempo = 500000.0;
	bool halt;
	int iter = 0;
	double sampleRate;

	double getFrequency(double notenum);
	double getEnvelope(double time);

	struct Note
	{
		double note_num = 0.0;
		double note_velocity = 0.0;
		float note_duration = 0.0;
		double time_start = 0.0;

		void reset()
		{
			note_num = 0.0;
			note_velocity = 0.0;
			time_start = 0.0;
			note_duration = 0.0;
		}
	} note_;
	vector <Note> notes;
};
#endif