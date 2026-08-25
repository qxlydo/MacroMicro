/****************************************************************************
** Meta object code from reading C++ file 'MegaByteFinder.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../MegaByteFinder.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MegaByteFinder.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.2. It"
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
struct qt_meta_tag_ZN8MMEngineE_t {};
} // unnamed namespace

template <> constexpr inline auto MMEngine::qt_create_metaobjectdata<qt_meta_tag_ZN8MMEngineE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MMEngine",
        "disksListChanged",
        "",
        "filesListChanged",
        "currentPathChanged",
        "statusChanged",
        "scanStarted",
        "scanFinished",
        "error",
        "msg",
        "fileFound",
        "path",
        "size",
        "scanDirectory",
        "QUrl",
        "dirUrl",
        "refreshDisks",
        "addFile",
        "name",
        "clearFiles",
        "showNotification",
        "title",
        "message",
        "disksList",
        "QVariantList",
        "filesList",
        "currentPath",
        "status"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'disksListChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'filesListChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'currentPathChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'statusChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'scanStarted'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'scanFinished'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'error'
        QtMocHelpers::SignalData<void(const QString &)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 9 },
        }}),
        // Signal 'fileFound'
        QtMocHelpers::SignalData<void(const QString &, qint64)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 11 }, { QMetaType::LongLong, 12 },
        }}),
        // Method 'scanDirectory'
        QtMocHelpers::MethodData<void(const QUrl &)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 14, 15 },
        }}),
        // Method 'refreshDisks'
        QtMocHelpers::MethodData<void()>(16, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'addFile'
        QtMocHelpers::MethodData<void(const QString &, qint64)>(17, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 18 }, { QMetaType::LongLong, 12 },
        }}),
        // Method 'clearFiles'
        QtMocHelpers::MethodData<void()>(19, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'showNotification'
        QtMocHelpers::MethodData<void(const QString &, const QString &)>(20, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 21 }, { QMetaType::QString, 22 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'disksList'
        QtMocHelpers::PropertyData<QVariantList>(23, 0x80000000 | 24, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'filesList'
        QtMocHelpers::PropertyData<QVariantList>(25, 0x80000000 | 24, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 1),
        // property 'currentPath'
        QtMocHelpers::PropertyData<QString>(26, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 2),
        // property 'status'
        QtMocHelpers::PropertyData<QString>(27, QMetaType::QString, QMC::DefaultPropertyFlags, 3),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MMEngine, qt_meta_tag_ZN8MMEngineE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MMEngine::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8MMEngineE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8MMEngineE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN8MMEngineE_t>.metaTypes,
    nullptr
} };

void MMEngine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MMEngine *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->disksListChanged(); break;
        case 1: _t->filesListChanged(); break;
        case 2: _t->currentPathChanged(); break;
        case 3: _t->statusChanged(); break;
        case 4: _t->scanStarted(); break;
        case 5: _t->scanFinished(); break;
        case 6: _t->error((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->fileFound((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<qint64>>(_a[2]))); break;
        case 8: _t->scanDirectory((*reinterpret_cast<std::add_pointer_t<QUrl>>(_a[1]))); break;
        case 9: _t->refreshDisks(); break;
        case 10: _t->addFile((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<qint64>>(_a[2]))); break;
        case 11: _t->clearFiles(); break;
        case 12: _t->showNotification((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (MMEngine::*)()>(_a, &MMEngine::disksListChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (MMEngine::*)()>(_a, &MMEngine::filesListChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (MMEngine::*)()>(_a, &MMEngine::currentPathChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (MMEngine::*)()>(_a, &MMEngine::statusChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (MMEngine::*)()>(_a, &MMEngine::scanStarted, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (MMEngine::*)()>(_a, &MMEngine::scanFinished, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (MMEngine::*)(const QString & )>(_a, &MMEngine::error, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (MMEngine::*)(const QString & , qint64 )>(_a, &MMEngine::fileFound, 7))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QVariantList*>(_v) = _t->disksList(); break;
        case 1: *reinterpret_cast<QVariantList*>(_v) = _t->filesList(); break;
        case 2: *reinterpret_cast<QString*>(_v) = _t->currentPath(); break;
        case 3: *reinterpret_cast<QString*>(_v) = _t->status(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 2: _t->setCurrentPath(*reinterpret_cast<QString*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *MMEngine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MMEngine::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8MMEngineE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MMEngine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void MMEngine::disksListChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MMEngine::filesListChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MMEngine::currentPathChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MMEngine::statusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MMEngine::scanStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void MMEngine::scanFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void MMEngine::error(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1);
}

// SIGNAL 7
void MMEngine::fileFound(const QString & _t1, qint64 _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1, _t2);
}
QT_WARNING_POP
