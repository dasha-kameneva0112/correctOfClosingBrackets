#include <QCoreApplication>
#include "bracket.h"
#include "mistake.h"
#include "errorininputdata.h"
#include <QSet>
#include <QStack>
#include <qDebug>

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

typedef enum {
    Round,
    Square,
    Curly
}BracketType;
enum BracketSide{
    Opening,
    Closing
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
    //QCoreApplication a(argc, argv);
    //return a.exec();



    //Считать из параметров командной строки путь к входному файлу
    //Считать из параметров командной строки путь к выходному файлу

    //Создать пустой контейнер для ошибок, связанных с входными данными
    QSet<errorininputdata> errors;

    //Считать данные из входного файла (readCppFile)
    //Если ошибок во входных данных нет, то…
    if(errors.isEmpty())
    {
        //Создать пустой контейнер для найденных ошибок, связанных с неправильным использованием скобок
        QSet<mistake> mistakes;
        int countOfMistakes;

        //Проверить корректность использования всех скобок в исходном коде(с помощью функции findAllIncorrectUsesOfBrackets)
        countOfMistakes = findAllIncorrectUsesOfBrackets();

    }

    if(errors.isEmpty())
    {
        //Сформировать выходной файл, содержащий все найденные ошибки (generateOutputTxtFile)

    }

    //Если QSet не пустой, то…
    if(!(errors.isEmpty()))
    {
        //Вывести найденные ошибки с входными данными из контейнера

    }

    //Вернуть успешность завершения функции
    return 0;
}
/*
int readCppFile (const QString& filePath, QStringList& code, QSet <errorininputdata>& errors)
{
    //Открыть указанный входной файл
    //Если не удалось успешно открыть входной файл, то...
    if()
    {
        //Создать новый объект ошибки (с помощью конструктора класса ErrorInInputData), передав тип ошибки – NoAccessToInputFile, и добавить его в контейнер с ошибками
    }
    else
    {
        //Считать содержимое исходного кода из входного файла в массив строк (code)
        //Если количество строк превышает допустимое или входной файл пуст, то...
        {
        // Создать новый объект ошибки (с помощью конструктора класса ErrorInInputData), передав тип ошибки – ExceedingMaxLengthInputFile или EmptyInputFile, и добавить его в контейнер с ошибками (errors)

        }
    }
    //Вернуть успешность завершения функции
    return 0;
}

int findAllIncorrectUsesOfBrackets (const QStringList& code, QSet<mistake>& mistakes, QSet <errorininputdata>& errors)
{
    //Создать пустой контейнер для найденных скобок
    QStack <bracket> brackets;
    //Создать старт
    int startLine=0, startPosition=0;
    int countOfMistakes=0, bracketIsFound=0;

    //Пока не конец кода или пока не найдена ошибка кода...
    while((startLine!=code.size() && startPosition!=...) && (errors.isEmpty()) )
    {
        //Найти скобку любого типа (круглая, квадратная, фигурная) в коде, начиная с startLine и startPosition
        bracketIsFound=findNextBracket();
        //Если скобка найдена, то...
        if(bracketIsFound==1)
        {
            //Создать объект новой скобки
            bracket newBracket(&code, &startLine, &startPosition);
            //Изменить содержимое контейнера с учетом новой скобки (с помощью updateContainerOfBrackets)

        }
        //Изменить стартовые данные (startPosition+1 / startLine+1, startPosition=0)
    }
    //Если ошибка кода не найдена и контейнер для скобок не пустой, то…
    if((errors.isEmpty()) && !(brackets.isEmpty()))
    {
        //Для каждого объекта Bracket в стеке - создать новый объект ошибки
        //(конструктор класса Mistake, передав тип ошибки – UnclosedBracket) и
        //    добавить ее в контейнер с ошибками (mistakes)
    }
    //Вернуть количество ошибок в контейнер с ошибками mistakes
    return countOfMistakes;
}

int findNextBracket (const QStringList& code, int& startLine, int& startPosition, QSet <errorininputdata>& errors)
{
    int bracketIsFound=0;
    //Идти по строке, начиная с startPosition и startLine, пока не нашли скобку или пока
    //не нашли ошибку ErrorInInputData в коде или пока не конец кода…
    for(startPosition; bracketIsFound!=1 || errors.isEmpty() || (startLine!=code.size() && startPosition!=...); startPosition++)
    {
        //Если встретили однострочный комментарий («//»), то пропустить его (skipOneLineComment)
        //Если встретили многострочный комментарий («/*»), то пропустить его (skipMultilineComment)
        //Если встретили символьную константу («`»), пропустить ее (skipCharConstant)
        //Если встретили строковую константу («"»), пропустить ее (skipStringConstant)

        //Если встретили скобку любого типа, то...
        if()
        {
            //Изменить признак нахождения скобки
            bracketIsFound = 1;
        }

        //Если пропуск константы/многострочного комментария не прошел успешно, то…
        if()
        {
            //Найдена ошибка ErrorInInputData в коде
            bracketIsFound = -1;
            //Создать новый объект ошибки, передав тип ошибки –
            //UnclosedMultilineComment / UnclosedCharConst / UnclosedStringConst,
            //    и добавить его в контейнер errors
        }
        //Если строка закончилась, то…
        if()
        {
            // startLine+1, startPosition=0
        }
    }

    //Вернуть результат функции
    return bracketIsFound;
}
*/

void skipOneLineComment (const QStringList& code, int& currentLine, int& currentPosition)
{
    /*
     currentLine++;
    currentPosition=0;
    QString line = code[currentLine];
    int lastchar=line.size()-1;

    while (line[lastchar]=='\\' && currentLine<code.size())
    {
        currentLine++;
        currentPosition=0;
        line = code[currentLine];
        lastchar=line.size()-1;
    }
    */

    QString line = code[currentLine];
    if(currentLine!=code.size()-1)
    {
        if(line[line.size()-1]=='\\')
        {
            //Делать…
            do
            {
                currentLine++;
                currentPosition=0;
                line = code[currentLine];
            } while (line[line.size()-1]=='\\' && currentLine<code.size());
            //Пока последний символ строки `\` или пока не конец кода
        }
        currentLine++;
        currentPosition=0;
        line = code[currentLine];
    }
    else
        currentPosition=line.size();

}




bool skipMultilineComment (const QStringList& code, int& currentLine, int& currentPosition)
{
    bool resultOfSkipping=0; // 1 - успешно
    QString line = code[currentLine];
    currentPosition++; // начинаем после *

    //Идти по строке, пока не нашли конец комментария или пока не конец кода...
    for(currentPosition; resultOfSkipping!=1 && currentPosition<line.size(); currentPosition++)
    {
        //Если встретили «*/», то…
        if(line[currentPosition]=='/' && currentPosition != 0)
            if(line[currentPosition-1]=='*')
                resultOfSkipping=1; //Нашли конец

        //Если конец строки и строка не последняя, то...
        if(currentPosition == line.size()-1)
        {
            if(currentLine != code.size()-1)
            {
                currentPosition=-1;
                currentLine++;
                line = code[currentLine];
            }
        }
    }

    //Вернуть результат проверки (нашли конец комментария или нет)
    return resultOfSkipping;
}

bool skipCharConstant (const QStringList& code, int& currentLine, int& currentPosition)
{
    bool resultOfSkipping=0; // 1 - успешно
    QString line = code[currentLine];
    bool slashesFlag = 0;
    currentPosition++; // начинаем после открывающей кавычки

    //Идти по строке, пока не нашли конец константы или пока не конец строки...
    for(currentPosition; resultOfSkipping!=1 && currentPosition<line.size(); currentPosition++)
    {
        //Если встретили `\`, то...
        if(line[currentPosition]=='\\')
        {
            if(slashesFlag==0)
                slashesFlag = 1;
            else
                slashesFlag = 0;
        }

        //Если встретили ` ‘ `, то...
        if(line[currentPosition]=='\'')
        {
            //Если слэш не был найден, то...
            if(slashesFlag==0)
                resultOfSkipping=1; //Нашли конец константы
            //Иначе oбнулить флаг нахождения слэша
            else
                slashesFlag=0;
        }
    }

    //Вернуть результат функции (успешность нахождения конца константы)
    return resultOfSkipping;
}

bool skipStringConstant (const QStringList& code, int& currentLine, int& currentPosition)
{
    bool resultOfSkipping=0; // 1 - успешно
    QString line = code[currentLine];
    int slashesCount=0;
    currentPosition++; // начинаем после открывающей кавычки

    // Идти посимвольно по строке, пока не нашли конец константы или пока не конец строки...
    for(currentPosition; resultOfSkipping!=1 && currentPosition<line.size(); currentPosition++)
    {
        //Если встретили не `\` и не ` " `, то...
        if(line[currentPosition]!='\\' && line[currentPosition]!='"')
            slashesCount=0; //Обнулить количество слэшей

        //Если встретили `\`, то…
        if(line[currentPosition]=='\\')
            slashesCount++; //Увеличить количество слэшей на 1
        //Если встретили ` " ` и количество слэшей не равно 0, то…
        if(line[currentPosition]=='"')
        {
            //Если количество слэшев четное, то…
            if(slashesCount%2==0)
                resultOfSkipping = 1; //Константа пропущена
            //Иначе константа не пропущена
        }
        //Если дошли до последнего символа строки, то…
        if(currentPosition == line.size()-1)
        {
            //Если количество слэшей нечетное…
            if(slashesCount%2!=0)
            { //Перейти на начало следующей строки
                if(currentLine!=code.size()-1)
                {
                    currentPosition=0;
                    currentLine++;
                    line = code[currentLine];
                }
                else
                    resultOfSkipping=1;
            }
        }
    }
    //Вернуть результат пропуска константы (нашли конец или нет)
    return resultOfSkipping;

    // **если конец не нашли, то currentPosition на 1 больше последнего индекса, а если нашли - на ;
}

int updateContainerOfBrackets (bracket& newBracket, QStack <bracket>& brackets, QSet<mistake>& mistakes)
{
    int countOfMistakes=0;
    int indexOfCouple=0;
    bracket coupleBracket;
    bool order=1; //0 - верный
    bracket lastBracket;
    QStack<bracket>::iterator it=brackets.end();;
    int index=0;

    //Если найденная скобка – открывающая, то…
    if(newBracket.side == Opening)
        brackets.push(newBracket);    //Добавить объект в контейнер
    if(newBracket.side == Closing)
    {
        //Найти в стеке парную открывающую скобку для текущей
        indexOfCouple = findCoupleForBracket(newBracket, brackets);

        if(indexOfCouple!=-1)   //Если пара найдена, то...
        {
            //Проверить порядок скобки и последней из стека (последняя – того же типа, открывающая)
            lastBracket = brackets.top();
            if(lastBracket.type==newBracket.type && lastBracket.side==Opening)
                order = 0;
            if(order==1) //Если порядок неверный, то...
            {
                //Изменить поле correctOfOrder у всех скобок до парной
                index=brackets.size()-1;
                while(index!=indexOfCouple)
                {
                    index--;
                    --it;
                    (*it).correctOfOrder = false;
                }
            }
            --it;
            coupleBracket = *it;

            if(coupleBracket.correctOfOrder!=true) //Если у парной порядок неверный, то...
            {
                //Создать новую ошибку (тип – IncorrectOrderOfBrackets)
                mistake newMistake(newBracket, mistake::IncorrectOrderOfBrackets);
                //Добавить ее в контейнер с ошибками (mistakes)
                mistakes.insert(newMistake);
                countOfMistakes++;
            }
            //Удалить из brackets найденную парную скобку для текущей
            brackets.removeAt(indexOfCouple);
        }
        else
        {
            // Если пары нет, то создать ошибку (ExcessiveClosingBracket) и добавить в mistakes
            mistakes.insert(mistake(newBracket, mistake::ExcessiveClosingBracket));
            countOfMistakes++;
        }
    }

    //Вернуть количество выявленных ошибок
    return countOfMistakes;
}

int findCoupleForBracket(const bracket& newBracket, const QStack<bracket>& brackets)
{
    bracket::BracketType necessaryType = newBracket.type; //определили нужный тип
    int index=brackets.size();
    int result=0;
    //QList<bracket> bracketList = brackets.toList(); //из стека в лист
    //QList<bracket>::iterator i;
    //for(i=bracketList.end()-1; i!=brackets.begin() || result!=1; --i)

    //Найти в brackets, начиная с конца, открывающую скобку нужного типа
    QStack<bracket>::const_iterator it=brackets.constEnd();
    if (brackets.isEmpty())
        index=-1;
    else
    {
        while(it != brackets.constBegin() && result!=1)
        {
            --it;
            index--;
            if((*it).type == necessaryType)
                if((*it).side == Opening)
                    result=1;
        }
        if(it==brackets.constBegin() && (*it).type!=necessaryType) //проверка первого
            index=-1;
    }

    //Вернуть индекс найденной парной открывающей скобки (или -1 – если нет пары)
    return index;
}

/*
int generateOutputTxtFile (const QString& filePath, int countOfMistakes, QSet<mistake>& mistakes, QSet<errorininputdata>& errors)
{
    //Если расширение выходного файла неверное (не .txt), то…
    if()
    {
        //Создать новый объект ошибки (с помощью конструктора класса
        // ErrorInInputData), передав тип ошибки – IncorrectFileExtension, и добавить
        // его в контейнер с ошибками (errors)
    }
    else
    {
        //Создать указанный выходной файл
        //Если не удалось успешно создать выходной файл, то...
        if()
        {
            //Создать новый объект ошибки, передав тип ошибки –
            // NoAccessToOutputFile, и добавить его в контейнер с ошибками (errors)
        }
        else
        {
            //Если количество выявленных ошибок равно 0, то…
            if(countOfMistakes==0)
            {
                //Добавить в выходной файл информацию, что все скобки в
                // коде используются корректно
            }
            else
            {
                //Добавить в выходной файл информацию, что в коде
                // присутствует некорректное использование скобок
                //Добавить все выявленные ошибки из контейнера с ошибками
                // некорректного использования скобок в выходной файл и их
                //    соответствующее описание
            }
        }
    }

    //Вернуть успешность завершения функции
    return 0;
}
*/
