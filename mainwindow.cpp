#include <QDebug>

#include <QFile>
#include <QTextCodec>
#include <QDataStream>
#include <QByteArray>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QFile colorBookFile("D:/Qt/Projects/untitled/TOYO 94 COLOR FINDER.acb");
    if(!colorBookFile.open(QIODevice::ReadOnly))
    {
       qDebug()<<"Fuck! can't open!";
    }
    QDataStream colorStream(&colorBookFile);
    char header[4];
    colorStream.readRawData(header, 4);
    qDebug()<<"Header Check(Should be 8BCB):"<<header;
    qint16 bookVersion, bookIdentifier;
    colorStream>>bookVersion>>bookIdentifier;
    qDebug()<<"Book version"<<bookVersion<<bookIdentifier;
    qint32 titleLength;
    colorStream>>titleLength;
    qDebug()<<"Title Length"<<titleLength;
    QString titleString;
    while(titleLength--)
    {
        qint16 currentUTF16Data;
        colorStream>>currentUTF16Data;
        QChar currentChar(currentUTF16Data);
        titleString+=currentChar;
    }
    qDebug()<<"Book Title:"<<titleString;

    colorStream>>titleLength; //Now It's prefix;
    qDebug()<<"Prefix Length"<<titleLength;
    titleString.clear();
    while(titleLength--)
    {
        qint16 currentUTF16Data;
        colorStream>>currentUTF16Data;
        QChar currentChar(currentUTF16Data);
        titleString+=currentChar;
    }
    qDebug()<<"Book Prefix:"<<titleString;

    colorStream>>titleLength; //Now It's suffix;
    qDebug()<<"Suffix Length"<<titleLength;
    titleString.clear();
    while(titleLength--)
    {
        qint16 currentUTF16Data;
        colorStream>>currentUTF16Data;
        QChar currentChar(currentUTF16Data);
        titleString+=currentChar;
    }
    qDebug()<<"Book Suffix:"<<titleString;

    colorStream>>titleLength; //Now It's discribe;
    qDebug()<<"Describe Length"<<titleLength;
    titleString.clear();
    while(titleLength--)
    {
        qint16 currentUTF16Data;
        colorStream>>currentUTF16Data;
        QChar currentChar(currentUTF16Data);
        titleString+=currentChar;
    }
    qDebug()<<"Book Describe:"<<titleString;

    qint16 colorNumber;
    colorStream>>colorNumber;
    qDebug()<<"Color Number"<<colorNumber;

    qint16 pageSize;
    colorStream>>pageSize;
    qDebug()<<"Page Size"<<pageSize;

    qint16 pageOffset;
    colorStream>>pageOffset;
    qDebug()<<"Page Offset"<<pageOffset;

    qint16 colorModel;
    colorStream>>colorModel;
    qDebug()<<"Color Model"<<colorModel;

    qint32 colorNameLength;
    int i;
    for(i=0; i<colorNumber; i++)
    {
        colorStream>>colorNameLength;
        QString colorName;
        while(colorNameLength--)
        {
            qint16 currentUTF16Data;
            colorStream>>currentUTF16Data;
            QChar currentChar(currentUTF16Data);
            colorName+=currentChar;
        }
        qint8 code[6];
        colorStream>>code[0]>>code[1]
                >>code[2]>>code[3]
                >>code[4]>>code[5];
        //Components, here is Lab system.
        qint8 dataL, dataA, dataB;
        colorStream>>dataL>>dataA>>dataB;
        qreal l; qint8 a,b;
        l=(qreal)dataL/2.55+0.5;
        a=dataA-128;
        b=dataB-128;
        qDebug()<<colorName<<l<<a<<b;
    }
}
