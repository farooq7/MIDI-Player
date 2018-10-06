#include "midiplayer.hpp"
#include "instrument.hpp"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLayout>
#include <QGridLayout> 
#include <QFileDialog>
#include <QButtonGroup>
#include <QDebug>

MIDIPlayer::MIDIPlayer(QWidget * parent)
{
	parsed = false;
	stopped = false;
	wait = true;
	full = false;
	sample = 0.0;
	s_rate  = 0.0;

	doubleBuffer = new SharedDoubleBuffer(1024);
	messages = new message_queue;
	t1 = std::thread(&MIDIPlayer::synthesize, this);

	audioSetup();
	setMIDIBox();
	setAudioBox();

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(midiGroupBox);
	mainLayout->addWidget(audioGroupBox);
	setLayout(mainLayout);
	
	connect(audio, SIGNAL(notify()), this, SLOT(playBuffer()));
	connect(audio, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleState()));
	connect(browseButton, &QAbstractButton::clicked, this, &MIDIPlayer::browseMIDI);
	connect(inPath, SIGNAL(returnPressed()), this, SLOT(parseTrack()));
	connect(play, &QAbstractButton::clicked, this, &MIDIPlayer::playAudio);
	connect(pause, &QAbstractButton::clicked, this, &MIDIPlayer::pauseAudio);
	connect(stop, &QAbstractButton::clicked, this, &MIDIPlayer::stopAudio);
	connect(mute, &QAbstractButton::clicked, this, &MIDIPlayer::muteAudio);
	connect(volume, &QAbstractSlider::valueChanged, this, &MIDIPlayer::setVolume);
}

MIDIPlayer::~MIDIPlayer( )
{
	messages->addMessage("destroy");
	stopped = true;
	t1.join();
}

void MIDIPlayer::setAudioBox()
{
	audioGroupBox = new QGroupBox(tr("Audio Controls"));
	audioGroupBox->setObjectName("audioBox");
	play = new QPushButton(tr("Play"));
	play->setObjectName("play");
	pause = new QPushButton(tr("Pause"));
	pause->setObjectName("pause");
	stop = new QPushButton(tr("Stop"));
	stop->setObjectName("stop");
	QLabel *volumeLabel = new QLabel(tr("Volume:"));
	volume = new QSlider(Qt::Horizontal);
	volume->setObjectName("volume");
	volume->setRange(0, 100);
	volume->setSliderPosition(50);
	mute = new QPushButton(tr("Mute"));
	mute->setObjectName("mute");
	
	QHBoxLayout *horizontal1 = new QHBoxLayout;
	horizontal1->addWidget(play);
	horizontal1->addWidget(pause);
	horizontal1->addWidget(stop);
	QHBoxLayout *horizontal2 = new QHBoxLayout;
	horizontal2->addWidget(volumeLabel);
	horizontal2->addWidget(volume);
	horizontal2->addWidget(mute);
	QVBoxLayout *vertical = new QVBoxLayout;
	vertical->addLayout(horizontal1);
	vertical->addLayout(horizontal2);
	audioGroupBox->setLayout(vertical);
}

void MIDIPlayer::setMIDIBox()
{
	midiGroupBox = new QGroupBox(tr("MIDI Input"));
	midiGroupBox->setObjectName("midiBox");
	inPath = new QLineEdit;
	inPath->setObjectName("inputpath");
	browseButton = new QPushButton(tr("Browse..."));
	browseButton->setObjectName("browse1");

	QHBoxLayout *layout1 = new QHBoxLayout;
	layout1->addWidget(inPath);
	layout1->addWidget(browseButton);
	midiGroupBox->setLayout(layout1);
}

void MIDIPlayer::audioSetup()
{
	QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
	auto rates = info.supportedSampleRates();

	int sampleRate = rates.at(0);
	for (int i = 1; i < rates.size(); ++i) {
		if (rates.at(i) < sampleRate)
			sampleRate = rates.at(i);
	}
	messages->addMessage("sample rate " + std::to_string(sampleRate));

	format.setSampleRate(sampleRate);
	format.setChannelCount(1);
	format.setSampleSize(16);
	format.setCodec("audio/pcm");
	format.setByteOrder(QAudioFormat::LittleEndian);
	format.setSampleType(QAudioFormat::SignedInt);

	if (!info.isFormatSupported(format)) {
		qWarning()
			<< "Raw audio format not supported by backend, cannot play audio.";
	}
	else
	{
		audio = new QAudioOutput(format);
		audio->setVolume(0.5);
		audio->setNotifyInterval(25);
		buffer_size = audio->bufferSize();
		buffer_size = buffer_size > 0 ? buffer_size : 1024;
	}
}

void MIDIPlayer::browseMIDI()
{
	QString midiFile = QFileDialog::getOpenFileName(this, tr("Find MIDI File"), QDir::currentPath(), tr("MIDI Files (*.mid)"));
	inPath->setText(midiFile);
	parseTrack();
}

void MIDIPlayer::parseTrack()
{
	if (inPath->text().isEmpty())
	{
		parsed = false;
		QMessageBox msgBox;
		msgBox.setText("Please Provide Input MIDI File");
		msgBox.exec();
	}
	else
	{
		T = readMIDIFromFile(inPath->text().toStdString());
		if (T.size() == 0)
		{
			parsed = false;
			QMessageBox msgBox;
			msgBox.setText("Please Provide Valid Input MIDI File");
			msgBox.exec();
		}
		else
		{
			track = T.front();
			I = new DefaultInstrument(track, s_rate);
			parsed = true;
		}
	}
}

void MIDIPlayer::playAudio()
{
	if (parsed)
	{
		if (audio->state() == QAudio::SuspendedState)
		{
			audio->resume();
		}
		else
		{
			//audio_buffer.clear();
			messages->addMessage("start synthesizer");
			device = audio->start();
			while (doubleBuffer->writeBufferSize() < doubleBuffer->bufferSize()){}
			playBuffer();
		}
	}
}

void MIDIPlayer::pauseAudio()
{
	audio->suspend();
}

void MIDIPlayer::stopAudio()
{
	audio->stop();
	wait = true;
}

void MIDIPlayer::muteAudio()
{
	audio->setVolume(0.0);
	volume->setSliderPosition(0);
}

void MIDIPlayer::setVolume()
{
	double _volume;
	_volume = volume->sliderPosition() / 100.0;
	audio->setVolume(_volume);
}


void MIDIPlayer::handleState()
{
	if (audio->state() == QAudio::ActiveState)
	{
		stop->setEnabled(true);
		pause->setEnabled(true);
		inPath->setEnabled(false);
		browseButton->setEnabled(false);
		play->setEnabled(false);
	}
	else if (audio->state() == QAudio::IdleState)
	{
	}
	else if (audio->state() == QAudio::SuspendedState)
	{
		pause->setEnabled(false);
		stop->setEnabled(true);
		play->setEnabled(true);
		inPath->setEnabled(false);
		browseButton->setEnabled(false);
	}
	else if (audio->state() == QAudio::StoppedState)
	{
		stop->setEnabled(false);
		pause->setEnabled(false);
		inPath->setEnabled(true);
		browseButton->setEnabled(true);
		play->setEnabled(true);
		doubleBuffer->reset();
	}
}

void MIDIPlayer::playBuffer()
{
	if (doubleBuffer->writeBufferSize() == doubleBuffer->bufferSize()) 
	{
		int bytesFree = audio->bytesFree();
		int bytesToWrite = 2 * doubleBuffer->writeBufferSize();
		if (bytesToWrite > bytesFree)
		{
			bytesToWrite = bytesFree;
		}
		int samplesToWrite = bytesToWrite >> 1;
		bytesToWrite = 2 * samplesToWrite;
		audio_buffer.reserve(bytesToWrite);
		
		for (int i = 0; i < samplesToWrite; ++i)
		{
			int16_t temp = static_cast<int16_t>(lround(doubleBuffer->read()));
			char c = (temp & 0x00FF);
			char d = ((temp & 0xFF00) >> 8);
			audio_buffer.push_back(c);
			audio_buffer.push_back(d);
		}

		if (bytesToWrite > 0)
		{
			device->write(audio_buffer.data(), bytesToWrite);
		}
		audio_buffer.clear();
	}
}

void MIDIPlayer::synthesize()
{
	while (!stopped)
	{
		if (wait)
		{
			std::string m = messages->removeMessage();
			if (m == "start synthesizer")
			{
				sample = 0.0;
				I->reset();
				doubleBuffer->reset();
				wait = false;
			}
			if (m == "destroy")
			{
				break;
			}
			if (m.substr(0,11) == "sample rate")
			{
				s_rate = stod(m.substr(12, m.size() - 12));
			}
		}
		else 
		{
			if (doubleBuffer->writeBufferSize() < doubleBuffer->bufferSize())
			{
				doubleBuffer->write(I->sample(sample));
				sample = sample + (1.0 / s_rate);
			}
		}
	}
}