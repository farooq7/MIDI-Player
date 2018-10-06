#ifndef EVENT_HPP
#define EVENT_HPP

#include <cstdint>

// A TempoEvent. This event indicates that a change in the tempo should occur on the next MIDI tick.
class TempoEvent
{
public:
	TempoEvent(intmax_t t = 500000);		// Construct a TempoEvent. The default tempo is 120 bpm
	intmax_t getTempo() const;			// Get the tempo in micro-sec per beat.
private:
	intmax_t tempo_;
};

// An EndTrackEvent. This event indicates that the track has ended and the synthesizer should halt sampling the instrument.
class EndTrackEvent
{
public:
	EndTrackEvent();
};

// A NoteEvent. This event indicates that a note should be activated or deactivated.
class NoteEvent
{
public:
	NoteEvent() = delete;				// You cannot default construct a Note Event. 

										// Construct a note event. 
										// param on true if the note should be turned on, false if it should be turned off.
										// param notenum the MIDI note number (0-127) to be modified.
										// param notevelocity the velocity of the note change.
	NoteEvent(bool on, int8_t notenum, int8_t notevelocity);

	bool getNoteOn();					// Get note change type. true if ON, false if OFF. 
	int8_t getNoteNumber() const;		// Get MIDI note number to change. Takes on values in [0,127]
	int8_t getNoteVelocity() const;	// Get the velocity of the note change. 

private:
	bool on_;
	int8_t notenum_;
	int8_t notevelocity_;
};

// A MIDI Event holds one of a TempoEvent, EndTrackEvent, or NoteEvent and an associated MIDI tick time in units of ticks-per-beat.
class MIDIEvent
{
public:
	MIDIEvent(TempoEvent e, intmax_t ticktime);		 // Construct a MIDI event holding a TempoEvent at ticktime.
	MIDIEvent(EndTrackEvent e, intmax_t ticktime);	 // Construct a MIDI event holding an EndTrackEvent at ticktime.
	MIDIEvent(NoteEvent e, intmax_t ticktime);		 // Construct a MIDI event holding a NoteEvent at ticktime.

	bool isTempoEvent() const;					     // True if event is a TempoEvent, else false.
	bool isEndTrackEvent() const;					     // True if event is an EndTrackEvent, else false.
	bool isNoteEvent() const;							 // True if event is a NoteEvent, else false.

	intmax_t getTickTime() const;						 // Get the MIDI tick time of this event (ticks per beat)

	TempoEvent asTempoEvent() const;					// Cast the MIDI event as a TempoEvent. Only valid if isTempoEvent() returns true. 
	NoteEvent asNoteEvent() const;					// Cast the MIDI event as a NoteEvent. Only valid if isNoteEvent() returns true.

private:
	intmax_t ticktime_;
	enum EventType { Tempo, Note, End } eventType;
	union Events
	{
		TempoEvent TempoEvent_;
		EndTrackEvent EndTrackEvent_;
		NoteEvent NoteEvent_;
		Events() { EndTrackEvent(); };
		~Events() {};
	} event;
};
#endif