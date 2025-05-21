#ifndef MAIN_H
#define MAIN_H

#include <QCoreApplication>
#include "bracket.h"
#include "mistake.h"
#include "errorininputdata.h"
#include <QSet>
#include <QStack>
#include <qDebug>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QtTest/QtTest>

int readCppFile (const QString& filePath, QStringList& code, errorininputdata& error);
int findAllIncorrectUsesOfBrackets (const QStringList& code, QSet<mistake>& mistakes, errorininputdata& error);
int findNextBracket (const QStringList& code, int& startLine, int& startPosition, errorininputdata& error);
void skipOneLineComment (const QStringList& code, int& currentLine, int& currentPosition);
bool skipMultilineComment (const QStringList& code, int& currentLine, int& currentPosition);
bool skipCharConstant (const QStringList& code, int& currentLine, int& currentPosition);
bool skipStringConstant (const QStringList& code, int& currentLine, int& currentPosition);
int updateContainerOfBrackets (bracket& newBracket, QStack <bracket>& brackets, QSet<mistake>& mistakes);
int findCoupleForBracket(const bracket& newBracket, const QStack<bracket>& brackets);
int generateOutputTxtFile (const QString& filePath, const QStringList& code, QSet<mistake>& mistakes, errorininputdata& errors);


#endif // MAIN_H
