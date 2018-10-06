#include "track.hpp"
#include <string>
using namespace std;

Track::Track(intmax_t ticks_per_beat)
{
	tpb = ticks_per_beat;
}

intmax_t Track::getTicksPerBeat() const
{
	return tpb;
}

Track::ConstIteratorType Track::begin() const
{
	return midiEvents.begin();
}

Track::ConstIteratorType Track::end() const
{
	return midiEvents.end();
}

void Track::addTempoEvent(intmax_t tempo, intmax_t tick_time)
{
	TempoEvent Tempo(tempo);
	MIDIEvent midi(Tempo, tick_time);
	midiEvents.push_back(midi);
}

void Track::addNoteEvent(uint8_t code, uint8_t data1, uint8_t data2, intmax_t tick_time)
{
	bool temp;
	if (code == 8)
	{
		temp = false;
	}
	else if (code == 9)
	{
		temp = true;
	}
	else
	{
		temp = false;
	}
	NoteEvent Note(temp, data1, data2);
	MIDIEvent midi(Note, tick_time);
	midiEvents.push_back(midi);
}

void Track::addEndEvent(intmax_t tick_time)
{
	EndTrackEvent End;
	MIDIEvent midi(End, tick_time);
	midiEvents.push_back(midi);
}