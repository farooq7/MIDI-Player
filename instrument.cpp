#include "instrument.hpp"
#include <cmath>
DefaultInstrument::DefaultInstrument(const Track & track, double rate)
{
	track_ = track;
	halt = false;
	sampleRate = rate;
}

bool DefaultInstrument::halted()
{
	if (halt == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

double DefaultInstrument::sample(double deltaT_)
{
	for (auto it = track_.begin() + iter; it != track_.end(); it++)
	{
		double time = (it->getTickTime() * tempo) / (1000000.0 * track_.getTicksPerBeat());
		if (time <= deltaT_)
		{
			if (it->isTempoEvent())
			{
				tempo = it->asTempoEvent().getTempo();
				iter++;
			}
			else if (it->isNoteEvent())
			{
				note_.note_num = it->asNoteEvent().getNoteNumber();
				note_.note_velocity = it->asNoteEvent().getNoteVelocity();
				note_.time_start = 0;// deltaT_ - time; 

				if (it->asNoteEvent().getNoteOn())
				{
					notes.push_back(note_);
				}
				iter++;
			}
			else if (it->isEndTrackEvent())
			{
				halt = true;
			}
		}
	}
	if(notes.size() != 0)
	{
		double sum = 0, s = 0;
		for (int n = 0; n < notes.size(); n++)
		{
			if (notes[n].time_start <= 1.0)
			{
				s = 200 * notes[n].note_velocity * getEnvelope(notes[n].time_start) * sin(2.0 * 3.14159265359 * getFrequency(notes[n].note_num) * notes[n].time_start);
				notes[n].time_start = notes[n].time_start + (1.0 / sampleRate);
			}
			else
			{
				notes.erase(notes.begin() + n);
			}
			sum = sum + s;
		}
		return sum;
	}
	else
	{
		return 0;
	}
}

double DefaultInstrument::getFrequency(double notenum)
{
	vector <double> index = { 261.63, 277.18, 293.66, 311.13, 329.63, 349.63, 369.994, 392.0, 415.305, 440.0, 466.164, 493.88 };
	if (notenum == 60) { return 261.63; }
	else if (notenum == 61) { return 277.18; }
	else if (notenum == 62) { return 293.66; }
	else if (notenum == 63) { return 311.13; }
	else if (notenum == 64) { return 329.63; }
	else if (notenum == 65) { return 349.63; }
	else if (notenum == 66) { return 369.994; }
	else if (notenum == 67) { return 392.0; }
	else if (notenum == 68) { return 415.305; }
	else if (notenum == 69) { return 440.0; }
	else if (notenum == 70) { return 466.164; }
	else if (notenum == 71) { return 493.88; }
	else if (notenum >= 0 && notenum <= 11) {
		return index[notenum] / 10;
	}
	else if (notenum >= 12 && notenum <= 23) {
		int num = notenum - 12;
		return index[num] / 8;
	}
	else if (notenum >= 24 && notenum <= 35) {
		int num = notenum - 24;
		return index[num] / 6;
	}
	else if (notenum >= 36 && notenum <= 47) {
		int num = notenum - 36;
		return index[num] / 4;
	}
	else if (notenum >= 48 && notenum <= 59) {
		int num = notenum - 48;
		return index[num] / 2;
	}
	else if (notenum >= 72 && notenum <= 83) {
		int num = notenum - 72;
		return index[num] * 2;
	}
	else if (notenum >= 84 && notenum <= 95) {
		int num = notenum - 84;
		return index[num] * 4;
	}
	else if (notenum >= 96 && notenum <= 107) {
		int num = notenum - 96;
		return index[num] * 6;
	}
	else if (notenum >= 108 && notenum <= 119) {
		int num = notenum - 108;
		return index[num] * 8;
	}
	else if (notenum >= 120 && notenum <= 127) {
		int num = notenum - 120;
		return index[num] * 10;
	}
}

double DefaultInstrument::getEnvelope(double time)
{
	double t1 = 0.25 * envelope_scale_factor;
	double t2 = 0.45 * envelope_scale_factor;
	double t3 = 0.8 * envelope_scale_factor;
	double t4 = 1.0 * envelope_scale_factor;

	if (0 <= time && time <= t1)
	{
		return (1 / t1) * time;
	}
	else if (t1 < time && time <= t2)
	{
		return (1 - (time - t1));
	}
	else if (t2 < time && time <= t3)
	{
		return 0.8;
	}
	else if (t3 < time && time <= t4)
	{
		return (0.8 - ((0.8 / (t4 - t3)) * (time - t3)));
	}
	else
	{
		return 0.0;
	}
}

void DefaultInstrument::reset()
{
	halt = false;
	iter = 0;
	note_.reset();
	notes.clear();
}