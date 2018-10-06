/****************************************************************************
** Meta object code from reading C++ file 'midiplayer.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../midiplayer.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'midiplayer.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MIDIPlayer_t {
    QByteArrayData data[11];
    char stringdata0[108];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MIDIPlayer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MIDIPlayer_t qt_meta_stringdata_MIDIPlayer = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MIDIPlayer"
QT_MOC_LITERAL(1, 11, 10), // "browseMIDI"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 9), // "playAudio"
QT_MOC_LITERAL(4, 33, 10), // "pauseAudio"
QT_MOC_LITERAL(5, 44, 9), // "stopAudio"
QT_MOC_LITERAL(6, 54, 9), // "muteAudio"
QT_MOC_LITERAL(7, 64, 9), // "setVolume"
QT_MOC_LITERAL(8, 74, 11), // "handleState"
QT_MOC_LITERAL(9, 86, 10), // "parseTrack"
QT_MOC_LITERAL(10, 97, 10) // "playBuffer"

    },
    "MIDIPlayer\0browseMIDI\0\0playAudio\0"
    "pauseAudio\0stopAudio\0muteAudio\0setVolume\0"
    "handleState\0parseTrack\0playBuffer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MIDIPlayer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    0,   61,    2, 0x08 /* Private */,
       5,    0,   62,    2, 0x08 /* Private */,
       6,    0,   63,    2, 0x08 /* Private */,
       7,    0,   64,    2, 0x08 /* Private */,
       8,    0,   65,    2, 0x08 /* Private */,
       9,    0,   66,    2, 0x08 /* Private */,
      10,    0,   67,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MIDIPlayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MIDIPlayer *_t = static_cast<MIDIPlayer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->browseMIDI(); break;
        case 1: _t->playAudio(); break;
        case 2: _t->pauseAudio(); break;
        case 3: _t->stopAudio(); break;
        case 4: _t->muteAudio(); break;
        case 5: _t->setVolume(); break;
        case 6: _t->handleState(); break;
        case 7: _t->parseTrack(); break;
        case 8: _t->playBuffer(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MIDIPlayer::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MIDIPlayer.data,
      qt_meta_data_MIDIPlayer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MIDIPlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MIDIPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MIDIPlayer.stringdata0))
        return static_cast<void*>(const_cast< MIDIPlayer*>(this));
    return QWidget::qt_metacast(_clname);
}

int MIDIPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
