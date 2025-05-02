#include <QCoreApplication>
#include "bracket.h"
#include "mistake.h"
#include "errorininputdata.h"
#include <QSet>
#include <QStack>

enum ErrorsInInputDataType {
    NoAccessToInputFile,
    NoAccessToOutputFile,
    EmptyInputFile,
    UnclosedMultilineComment,
    UnclosedStringConst,
    UnclosedCharConst,
    IncorrectFileExtension,
    ExceedingMaxLengthInputFile
};

int readCppFile (const QString& filePath, QStringList& code, QSet <errorininputdata>& errors);
int findAllIncorrectUsesOfBrackets (const QStringList& code, QSet<mistake>& mistakes, QSet <errorininputdata>& errors);
int findNextBracket (const QStringList& code, int& startLine, int& startPosition, QSet <errorininputdata>& errors);
void skipOneLineComment (const QStringList& code, int& currentLine, int& currentPosition);
bool skipMultilineComment (const QStringList& code, int& currentLine, int& currentPosition);
bool skipCharConstant (const QStringList& code, int& currentLine, int& currentPosition);
bool skipStringConstant (const QStringList& code, int& currentLine, int& currentPosition);
int updateContainerOfBrackets (bracket& newBracket, QStack <bracket>& brackets, QSet<mistake>& mistakes);
int findCoupleForBracket (bracket& newBracket, QStack<bracket>& brackets);
int generateOutputTxtFile (const QString& filePath, int countOfMistakes, QSet<mistake>& mistakes, QSet<errorininputdata>& errors);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    return a.exec();
}


int updateContainerOfBrackets (bracket& newBracket, QStack <bracket>& brackets, QSet<mistake>& mistakes)
{

}

int findCoupleForBracket(bracket& newBracket, QStack<bracket>& brackets)
{
    //Найти в контейнере скобок, начиная с конца, открывающую скобку того же типа, что и текущая скобка
    //Вернуть индекс найденной парной открывающей скобки (или -1 – если нет пары)

    //по контейнеру с помощью STL
    QStack<bracket>::iterator i=brackets.begin();
    int result=0;
    while (i!=brackets.end() || (*i).type!=newBracket.type)
    {
        i++;
        result++;
    }
    if(i==brackets.end())
        result=-1;

    return result;
}
