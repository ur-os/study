#ifndef UTILS_H
#define UTILS_H

#include <QCoreApplication>
#include <QtCore>
#include <QObject>
#include <QIODevice>
#include <QProcess>
#include <QDebug>
#include <QDataStream>
#include <QVector>
#include <QMap>
#include <QList>

typedef struct qube{
    QByteArray scope;
    QByteArray type;
    QByteArray addr;
    QByteArray content;
    QByteArray name;
    int coord[3] = {-1, -1, -1};
    int pointTo[3] = {-1, -1, -1};
} Qube;

class GdbInterface : public QObject {
     Q_OBJECT

    QByteArray mainClipboard;
public:
    QProcess gdb;
    QString gdbProgram;
    QStringList gdbArguments;
    qint64 pid;

    QByteArray command;
    QByteArray magicBox(QByteArray clipboard);

    int identification(QByteArray commandResult, int varIndex);
    int countVars(QByteArray commandResult);
    int countFrames();


    void magicParser(QByteArray commandResult);
    void findAndPushName(QByteArray list);
    void getCurrentScope();



    QVector<QVector<QVector<Qube>>> magicEssence;
    QByteArray currentScope;
    QMap<QByteArray, Qube> addressingTable;
    QVector<QVector<Qube>> empty2;  //  for size + 1, ".push_back(empty);"
    QVector<Qube> empty1;
    Qube empty0;

    void magicFirst();
    void magicSecond(QByteArray infoLocal);
    void parserQube(QByteArray lineWithName, int currRow);
    void parserMass(QByteArray name, int currRow);
    void parserStruct(QByteArray name, int currRow);

    void parserInfolocal();
    void parserUsualQube(QByteArray name);
    void parserStaticArray(QByteArray name);
    void parserDynamicArray(QByteArray name);
    void parserStruct(QByteArray name);
    QMap<QByteArray, int> sizesDynamicArrays;
    void sizeOfarraysControl(QByteArray step);
    QByteArray history;

    QByteArray getNameVar(QByteArray commandResult, int  tildaIndex);
    QByteArray getTypeVar(QByteArray name);
    QByteArray getAddrVar(QByteArray name);
    QByteArray getContentVar(QByteArray name);
    QByteArray getContentArray(QByteArray name);
    QByteArray getFrameName(QByteArray lvl);

    QByteArray readFromTo(QByteArray stroke, int beg, int end);
    QByteArray readNSymbols(QByteArray stroke, int beg, int symbols);
public slots:
    void onGDBConnected();
    void gdbReadyRead();
    int trigger();
signals:
    void parsed(QVector <QVector <QVector <Qube>>> vector);  //  to makeMeEntity() thread
public:
    GdbInterface();
    GdbInterface(QString pathToTestingProgramm);
};

#endif // UTILS_H
