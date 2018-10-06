#include "event.hpp"

TempoEvent::TempoEvent(intmax_t t)
{
	tempo_ = t;
}
intmax_t TempoEvent::getTempo() const
{
	return tempo_;
}

EndTrackEvent::EndTrackEvent()
{

}

NoteEvent::NoteEvent(bool on, int8_t notenum, int8_t notevelocity)
{
	on_ = on;
	notenum_ = notenum;
	notevelocity_ = notevelocity;
}
bool NoteEvent::getNoteOn()
{
	return on_;
}
int8_t NoteEvent::getNoteNumber() const
{
	return notenum_;
}
int8_t NoteEvent::getNoteVelocity() const
{
	return notevelocity_;
}

MIDIEvent::MIDIEvent(TempoEvent e, intmax_t ticktime)
{
	eventType = Tempo;
	event.TempoEvent_ = e;
	ticktime_ = ticktime;
}
MIDIEvent::MIDIEvent(EndTrackEvent e, intmax_t ticktime)
{
	eventType = End;
	event.EndTrackEvent_ = e;
	ticktime_ = ticktime;
}
MIDIEvent::MIDIEvent(NoteEvent e, intmax_t ticktime)
{
	eventType = Note;
	event.NoteEvent_ = e;
	ticktime_ = ticktime;
}
bool MIDIEvent::isTempoEvent() const
{
	if (eventType == Tempo)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool MIDIEvent::isEndTrackEvent() const
{
	if (eventType == End)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool MIDIEvent::isNoteEvent() const
{
	if (eventType == Note)
	{
		return true;
	}
	else
	{
		return false;
	}
}
intmax_t MIDIEvent::getTickTime() const
{
	return ticktime_;
}
TempoEvent MIDIEvent::asTempoEvent() const
{
	return event.TempoEvent_;
}
NoteEvent MIDIEvent::asNoteEvent() const
{
	return event.NoteEvent_;
}