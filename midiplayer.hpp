#ifndef MIDIPLAYER_HPP
#define MIDIPLAYER_HPP

#include "midi.hpp"
#include "instrument.hpp"
#include "shared_double_buffer.hpp"
#include "message_queue.hpp"

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QGroupBox>
#include <QDir>
#include <QMessageBox>
#include <QAudioOutput>
#include <QIODevice>
#include <vector>
#include <cmath>
#include <thread>

class MIDIPlayer :public QWidget
{
	Q_OBJECT
public:
	MIDIPlayer(QWidget * parent = nullptr);
	~MIDIPlayer();
	void setMIDIBox();
	void setAudioBox();
	void audioSetup();
	void synthesize();

private slots:
	void browseMIDI();
	void playAudio();
	void pauseAudio();
	void stopAudio();
	void muteAudio();
	void setVolume();
	void handleState();
	void parseTrack();
	void playBuffer();

private:
	QLineEdit *inPath;
	QPushButton *browseButton;
	QPushButton *play;
	QPushButton *stop;
	QPushButton *pause;
	QSlider *volume;
	QPushButton *mute;
	QGroupBox *midiGroupBox;
	QGroupBox *audioGroupBox;
	QAudioOutput *audio;
	QIODevice *device;
	QAudioFormat format;

	TrackListType T;
	Track track;
	DefaultInstrument *I;
	SharedDoubleBuffer *doubleBuffer;
	message_queue *messages;
	std::thread t1;

	bool parsed ;
	bool stopped;
	bool wait;
	bool full;
	double sample;
	double s_rate;
	std::size_t buffer_size;
	std::vector<char> audio_buffer;
};
#endif
