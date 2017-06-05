/****************************************************************************
** Meta object code from reading C++ file 'noteediteur.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../PluriNote/noteediteur.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'noteediteur.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NoteEditeur_t {
    QByteArrayData data[6];
    char stringdata0[60];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NoteEditeur_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NoteEditeur_t qt_meta_stringdata_NoteEditeur = {
    {
QT_MOC_LITERAL(0, 0, 11), // "NoteEditeur"
QT_MOC_LITERAL(1, 12, 17), // "saveModifications"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 9), // "supprimer"
QT_MOC_LITERAL(4, 41, 14), // "afficherBouton"
QT_MOC_LITERAL(5, 56, 3) // "str"

    },
    "NoteEditeur\0saveModifications\0\0supprimer\0"
    "afficherBouton\0str"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NoteEditeur[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    0,   45,    2, 0x0a /* Public */,
       4,    1,   46,    2, 0x08 /* Private */,
       4,    0,   49,    2, 0x28 /* Private | MethodCloned */,
       4,    1,   50,    2, 0x08 /* Private */,
       4,    1,   53,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QDate,    2,

       0        // eod
};

void NoteEditeur::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NoteEditeur *_t = static_cast<NoteEditeur *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->saveModifications(); break;
        case 1: _t->supprimer(); break;
        case 2: _t->afficherBouton((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->afficherBouton(); break;
        case 4: _t->afficherBouton((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->afficherBouton((*reinterpret_cast< QDate(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject NoteEditeur::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_NoteEditeur.data,
      qt_meta_data_NoteEditeur,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *NoteEditeur::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NoteEditeur::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_NoteEditeur.stringdata0))
        return static_cast<void*>(const_cast< NoteEditeur*>(this));
    return QWidget::qt_metacast(_clname);
}

int NoteEditeur::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
struct qt_meta_stringdata_ArticleEditeur_t {
    QByteArrayData data[4];
    char stringdata0[44];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ArticleEditeur_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ArticleEditeur_t qt_meta_stringdata_ArticleEditeur = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ArticleEditeur"
QT_MOC_LITERAL(1, 15, 17), // "saveModifications"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 9) // "supprimer"

    },
    "ArticleEditeur\0saveModifications\0\0"
    "supprimer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ArticleEditeur[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a /* Public */,
       3,    0,   25,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ArticleEditeur::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ArticleEditeur *_t = static_cast<ArticleEditeur *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->saveModifications(); break;
        case 1: _t->supprimer(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ArticleEditeur::staticMetaObject = {
    { &NoteEditeur::staticMetaObject, qt_meta_stringdata_ArticleEditeur.data,
      qt_meta_data_ArticleEditeur,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ArticleEditeur::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ArticleEditeur::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ArticleEditeur.stringdata0))
        return static_cast<void*>(const_cast< ArticleEditeur*>(this));
    return NoteEditeur::qt_metacast(_clname);
}

int ArticleEditeur::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = NoteEditeur::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
struct qt_meta_stringdata_TaskEditeur_t {
    QByteArrayData data[6];
    char stringdata0[75];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TaskEditeur_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TaskEditeur_t qt_meta_stringdata_TaskEditeur = {
    {
QT_MOC_LITERAL(0, 0, 11), // "TaskEditeur"
QT_MOC_LITERAL(1, 12, 17), // "saveModifications"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 9), // "supprimer"
QT_MOC_LITERAL(4, 41, 16), // "afficherPriorite"
QT_MOC_LITERAL(5, 58, 16) // "afficherDeadline"

    },
    "TaskEditeur\0saveModifications\0\0supprimer\0"
    "afficherPriorite\0afficherDeadline"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TaskEditeur[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a /* Public */,
       3,    0,   35,    2, 0x0a /* Public */,
       4,    0,   36,    2, 0x08 /* Private */,
       5,    0,   37,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TaskEditeur::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TaskEditeur *_t = static_cast<TaskEditeur *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->saveModifications(); break;
        case 1: _t->supprimer(); break;
        case 2: _t->afficherPriorite(); break;
        case 3: _t->afficherDeadline(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject TaskEditeur::staticMetaObject = {
    { &NoteEditeur::staticMetaObject, qt_meta_stringdata_TaskEditeur.data,
      qt_meta_data_TaskEditeur,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TaskEditeur::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TaskEditeur::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TaskEditeur.stringdata0))
        return static_cast<void*>(const_cast< TaskEditeur*>(this));
    return NoteEditeur::qt_metacast(_clname);
}

int TaskEditeur::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = NoteEditeur::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
struct qt_meta_stringdata_MultimediaEditeur_t {
    QByteArrayData data[4];
    char stringdata0[47];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MultimediaEditeur_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MultimediaEditeur_t qt_meta_stringdata_MultimediaEditeur = {
    {
QT_MOC_LITERAL(0, 0, 17), // "MultimediaEditeur"
QT_MOC_LITERAL(1, 18, 17), // "saveModifications"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 9) // "supprimer"

    },
    "MultimediaEditeur\0saveModifications\0"
    "\0supprimer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MultimediaEditeur[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a /* Public */,
       3,    0,   25,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MultimediaEditeur::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MultimediaEditeur *_t = static_cast<MultimediaEditeur *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->saveModifications(); break;
        case 1: _t->supprimer(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MultimediaEditeur::staticMetaObject = {
    { &NoteEditeur::staticMetaObject, qt_meta_stringdata_MultimediaEditeur.data,
      qt_meta_data_MultimediaEditeur,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MultimediaEditeur::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MultimediaEditeur::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MultimediaEditeur.stringdata0))
        return static_cast<void*>(const_cast< MultimediaEditeur*>(this));
    return NoteEditeur::qt_metacast(_clname);
}

int MultimediaEditeur::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = NoteEditeur::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
struct qt_meta_stringdata_ImageEditeur_t {
    QByteArrayData data[4];
    char stringdata0[42];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ImageEditeur_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ImageEditeur_t qt_meta_stringdata_ImageEditeur = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ImageEditeur"
QT_MOC_LITERAL(1, 13, 17), // "saveModifications"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 9) // "supprimer"

    },
    "ImageEditeur\0saveModifications\0\0"
    "supprimer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ImageEditeur[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a /* Public */,
       3,    0,   25,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ImageEditeur::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ImageEditeur *_t = static_cast<ImageEditeur *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->saveModifications(); break;
        case 1: _t->supprimer(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ImageEditeur::staticMetaObject = {
    { &MultimediaEditeur::staticMetaObject, qt_meta_stringdata_ImageEditeur.data,
      qt_meta_data_ImageEditeur,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ImageEditeur::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ImageEditeur::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ImageEditeur.stringdata0))
        return static_cast<void*>(const_cast< ImageEditeur*>(this));
    return MultimediaEditeur::qt_metacast(_clname);
}

int ImageEditeur::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MultimediaEditeur::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
struct qt_meta_stringdata_AudioEditeur_t {
    QByteArrayData data[4];
    char stringdata0[42];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AudioEditeur_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AudioEditeur_t qt_meta_stringdata_AudioEditeur = {
    {
QT_MOC_LITERAL(0, 0, 12), // "AudioEditeur"
QT_MOC_LITERAL(1, 13, 17), // "saveModifications"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 9) // "supprimer"

    },
    "AudioEditeur\0saveModifications\0\0"
    "supprimer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AudioEditeur[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a /* Public */,
       3,    0,   25,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AudioEditeur::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AudioEditeur *_t = static_cast<AudioEditeur *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->saveModifications(); break;
        case 1: _t->supprimer(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject AudioEditeur::staticMetaObject = {
    { &MultimediaEditeur::staticMetaObject, qt_meta_stringdata_AudioEditeur.data,
      qt_meta_data_AudioEditeur,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AudioEditeur::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AudioEditeur::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AudioEditeur.stringdata0))
        return static_cast<void*>(const_cast< AudioEditeur*>(this));
    return MultimediaEditeur::qt_metacast(_clname);
}

int AudioEditeur::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MultimediaEditeur::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
struct qt_meta_stringdata_VideoEditeur_t {
    QByteArrayData data[4];
    char stringdata0[42];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VideoEditeur_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VideoEditeur_t qt_meta_stringdata_VideoEditeur = {
    {
QT_MOC_LITERAL(0, 0, 12), // "VideoEditeur"
QT_MOC_LITERAL(1, 13, 17), // "saveModifications"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 9) // "supprimer"

    },
    "VideoEditeur\0saveModifications\0\0"
    "supprimer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VideoEditeur[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a /* Public */,
       3,    0,   25,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void VideoEditeur::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VideoEditeur *_t = static_cast<VideoEditeur *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->saveModifications(); break;
        case 1: _t->supprimer(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject VideoEditeur::staticMetaObject = {
    { &MultimediaEditeur::staticMetaObject, qt_meta_stringdata_VideoEditeur.data,
      qt_meta_data_VideoEditeur,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *VideoEditeur::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VideoEditeur::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_VideoEditeur.stringdata0))
        return static_cast<void*>(const_cast< VideoEditeur*>(this));
    return MultimediaEditeur::qt_metacast(_clname);
}

int VideoEditeur::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MultimediaEditeur::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
