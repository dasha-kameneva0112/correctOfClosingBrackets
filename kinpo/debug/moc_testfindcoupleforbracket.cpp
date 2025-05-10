/****************************************************************************
** Meta object code from reading C++ file 'testfindcoupleforbracket.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../testfindcoupleforbracket.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'testfindcoupleforbracket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASStestfindcoupleforbracketENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASStestfindcoupleforbracketENDCLASS = QtMocHelpers::stringData(
    "testfindcoupleforbracket",
    "roundBracket",
    "",
    "squareBracket",
    "curlyBracket",
    "multipleBracketsOfTheSameType",
    "thereIsNoCouple",
    "theStackIsEmpty"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASStestfindcoupleforbracketENDCLASS_t {
    uint offsetsAndSizes[16];
    char stringdata0[25];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[14];
    char stringdata4[13];
    char stringdata5[30];
    char stringdata6[16];
    char stringdata7[16];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASStestfindcoupleforbracketENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASStestfindcoupleforbracketENDCLASS_t qt_meta_stringdata_CLASStestfindcoupleforbracketENDCLASS = {
    {
        QT_MOC_LITERAL(0, 24),  // "testfindcoupleforbracket"
        QT_MOC_LITERAL(25, 12),  // "roundBracket"
        QT_MOC_LITERAL(38, 0),  // ""
        QT_MOC_LITERAL(39, 13),  // "squareBracket"
        QT_MOC_LITERAL(53, 12),  // "curlyBracket"
        QT_MOC_LITERAL(66, 29),  // "multipleBracketsOfTheSameType"
        QT_MOC_LITERAL(96, 15),  // "thereIsNoCouple"
        QT_MOC_LITERAL(112, 15)   // "theStackIsEmpty"
    },
    "testfindcoupleforbracket",
    "roundBracket",
    "",
    "squareBracket",
    "curlyBracket",
    "multipleBracketsOfTheSameType",
    "thereIsNoCouple",
    "theStackIsEmpty"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASStestfindcoupleforbracketENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x08,    1 /* Private */,
       3,    0,   51,    2, 0x08,    2 /* Private */,
       4,    0,   52,    2, 0x08,    3 /* Private */,
       5,    0,   53,    2, 0x08,    4 /* Private */,
       6,    0,   54,    2, 0x08,    5 /* Private */,
       7,    0,   55,    2, 0x08,    6 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject testfindcoupleforbracket::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASStestfindcoupleforbracketENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASStestfindcoupleforbracketENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASStestfindcoupleforbracketENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<testfindcoupleforbracket, std::true_type>,
        // method 'roundBracket'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'squareBracket'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'curlyBracket'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'multipleBracketsOfTheSameType'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'thereIsNoCouple'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'theStackIsEmpty'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void testfindcoupleforbracket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<testfindcoupleforbracket *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->roundBracket(); break;
        case 1: _t->squareBracket(); break;
        case 2: _t->curlyBracket(); break;
        case 3: _t->multipleBracketsOfTheSameType(); break;
        case 4: _t->thereIsNoCouple(); break;
        case 5: _t->theStackIsEmpty(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *testfindcoupleforbracket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *testfindcoupleforbracket::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASStestfindcoupleforbracketENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int testfindcoupleforbracket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
