#include "midiplayer.hpp"
#include <QApplication> 

int main(int argc, char * argv[])
{
	QApplication app(argc, argv);
	MIDIPlayer widget;
	
	widget.show();
	return app.exec();
}