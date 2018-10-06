#include <QTest>
#include <QPushButton>
#include <QSlider>
#include <QLineEdit>

#include "midiplayer.hpp"
#include "test_config.hpp"

class TestMIDIPlayer : public QObject {
  Q_OBJECT

private slots:

  void initTestCase();
  void testMIDIBox();
  void testAudioControls();
  void testDoubleBuffer();
  void testMessageQueue();
  void testMute();
  void testAudioButtons();
  // TODO: add your tests
  
private:

  MIDIPlayer widget;
};

void TestMIDIPlayer::initTestCase()
{
  {
    auto w = widget.findChild<QLineEdit *>("inputpath");
    QVERIFY2(w, "Could not find a QLineEdit widget");
  }

  {
    auto w = widget.findChild<QPushButton *>("play");
    QVERIFY2(w, "Could not find play button");
  }

  {
    auto w = widget.findChild<QPushButton *>("pause");
    QVERIFY2(w, "Could not find pause button");
  }
  
  {
    auto w = widget.findChild<QPushButton *>("stop");
    QVERIFY2(w, "Could not find stop button");
  }

  {
    auto w = widget.findChild<QSlider *>("volume");
    QVERIFY2(w, "Could not find volume slider");
  }
  
  {
    auto w = widget.findChild<QPushButton *>("mute");
    QVERIFY2(w, "Could not find mute button");
  }
}

void TestMIDIPlayer::testMIDIBox() 
{
	auto mb = widget.findChild<QGroupBox *>("midiBox");
	QVERIFY2(mb, "Could not find MIDI box");

	auto in = widget.findChild<QLineEdit *>("inputpath");
	QVERIFY(in->text().isEmpty());

	auto b1 = widget.findChild<QPushButton *>("browse1");
	QVERIFY2(b1, "Could not find MIDI browse button");
}

void TestMIDIPlayer::testAudioControls() 
{
	auto ab = widget.findChild<QGroupBox *>("audioBox");
	QVERIFY2(ab, "Could not find Audio Control box");

	auto p = widget.findChild<QPushButton *>("play");
	QVERIFY(p->isEnabled());

	auto pa = widget.findChild<QPushButton *>("pause");
	QVERIFY(pa->isEnabled());

	auto s = widget.findChild<QPushButton *>("stop");
	QVERIFY(s->isEnabled());

	auto m = widget.findChild<QPushButton *>("mute");
	QVERIFY(m->isEnabled());

	auto v = widget.findChild<QSlider *>("volume");
	QVERIFY(v->sliderPosition() == 50);
}

void TestMIDIPlayer::testMute()
{
	auto m = widget.findChild<QPushButton *>("mute");
	auto v = widget.findChild<QSlider *>("volume");

	m->click();
	QVERIFY(v->sliderPosition() == 0);
}

void TestMIDIPlayer::testDoubleBuffer()
{
	SharedDoubleBuffer SDB(5);

	QVERIFY(SDB.bufferSize() == 5);
	
	for (int i = 0; i < 5; i++)
	{
		SDB.write(i * 5);
	}

	QVERIFY(SDB.writeBufferSize() == 5);

	SDB.read();
	QVERIFY(SDB.writeBufferSize() == 0);

	SDB.read();
	double s = SDB.read();

	QVERIFY(s == 10);
}

void TestMIDIPlayer::testMessageQueue()
{
	message_queue MQ;
	MQ.addMessage("message");
	string m = MQ.removeMessage();
	QVERIFY(m == "message");
}

void TestMIDIPlayer::testAudioButtons()
{
	std::string fname = TEST_FILE_DIR + "/test1.mid";
	QString filename = QString::fromStdString(fname);

	auto i = widget.findChild<QLineEdit *>("inputpath");
	auto b = widget.findChild<QPushButton *>("browse1");
	auto p = widget.findChild<QPushButton *>("play");
	auto pa = widget.findChild<QPushButton *>("pause");
	auto s = widget.findChild<QPushButton *>("stop");

	p->click();
	QVERIFY(p->isEnabled() == true);
	pa->click();
	QVERIFY(pa->isEnabled() == true);
	s->click();
	QVERIFY(s->isEnabled() == true);

	i->setText(filename);
	i->returnPressed();

	p->click();
	QVERIFY(p->isEnabled() == false);
	QVERIFY(i->isEnabled() == false);
	QVERIFY(b->isEnabled() == false);
	QVERIFY(pa->isEnabled() == true);
	QVERIFY(s->isEnabled() == true);

	pa->click();
	QVERIFY(p->isEnabled() == true);
	QVERIFY(i->isEnabled() == false);
	QVERIFY(b->isEnabled() == false);
	QVERIFY(pa->isEnabled() == false);
	QVERIFY(s->isEnabled() == true);

	s->click();
	QVERIFY(p->isEnabled() == true);
	QVERIFY(i->isEnabled() == true);
	QVERIFY(b->isEnabled() == true);
	QVERIFY(pa->isEnabled() == false);
	QVERIFY(s->isEnabled() == false);
}

QTEST_MAIN(TestMIDIPlayer)
#include "test_midiplayer.moc"

