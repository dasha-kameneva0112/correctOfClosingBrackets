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

enum BracketType{
    Round,
    Square,
    Curly
};
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

void skipOneLineComment (const QStringList& code, int& currentLine, int& currentPosition)
{
    //Делать…
    do
    {
        //Перейти на следующую строку (startLine+1, startPosition=0)
    } while ();
    //Пока последний символ строки `\` или пока не конец кода
}

bool skipMultilineComment (const QStringList& code, int& currentLine, int& currentPosition)
{
    int resultOfSkipping=1;
    //Идти посимвольно по строке currentLine, начиная с currentPosition, пока не нашли
    // конец комментария или пока не конец кода...
    for(currentPosition; )
    {
        //Если встретили «*/», то…
        if()
            resultOfSkipping=0; //Нашли конец многострочного комментария
        //Если конец строки и строка не последняя, то...
        if()
        {
            //currentLine+1, currentPosition=0
        }
    }

    //Вернуть результат проверки (нашли конец комментария или нет)
    return resultOfSkipping;
}

bool skipCharConstant (const QStringList& code, int& currentLine, int& currentPosition)
{
    int resultOfSkipping=1;
    //Идти посимвольно по строке currentLine, начиная с currentPosition, пока не нашли
    //конец константы или пока не конец строки...
    for()
    {
        //Если встретили `\`, то...
            //Изменить флаг нахождения слэша
        //Если встретили ` ‘ `, то...
            //Если слэш не был найден (флаг=0), то...
                //Нашли конец константы
            //Иначе...
                //Обнулить флаг нахождения слэша
    }

    //Вернуть результат функции (успешность нахождения конца константы)
    return resultOfSkipping;
}

bool skipStringConstant (const QStringList& code, int& currentLine, int& currentPosition)
{
    int resultOfSkipping=1;
    // Идти посимвольно по строке currentLine, начиная с currentPosition, пока не нашли конец константы или пока не конец строки...
    for()
    {
        //Если встретили не `\` и не ` " `, то...
            //Обнулить количество слэшей
        //Если встретили `\`, то…
            //Увеличить количество слэшей на 1
        //Если встретили ` " ` и количество слэшей не равно 0, то…
            //Если количество слэшев четное, то…
                //Константа пропущена
                resultOfSkipping=0;
            //Иначе…
                //Константа не пропущена
                resultOfSkipping=1;

        //Если дошли до последнего символа строки, то…
            //Если количество слэшей нечетное…
                //Перейти на начало следующей строки (currentPosition=0, currentLine+1)
            //Иначе…
                //Константа не пропущена
                resultOfSkipping=1;
    }

    //Вернуть результат пропуска константы (нашли конец или нет)
    return resultOfSkipping;
}

int updateContainerOfBrackets (bracket& newBracket, QStack <bracket>& brackets, QSet<mistake>& mistakes)
{
    int countOfMistakes=0;
    //Если найденная скобка – открывающая, то…
    if(newBracket.side==Opening)
    {
        //Добавить объект скобки в контейнер со скобками (brackets)
    }
    if(newBracket.side==Closing)
    {
        //Найти в стеке парную открывающую скобку для текущей (findCoupleForBracket)
        //Если пара найдена, то...
        if()
        {
            //Проверить порядок найденной скобки и последней из стека (порядок
            //верный, если последняя – того же типа, открывающая)
            //Если порядок неверный, то...
                //Изменить поле правильности порядка у последней в стеке (correctOfOrder = false)
            //Если у парной открывающей скобки из стека порядок неверный, то...
                //Создать новый объект ошибки (с помощью конструктора
                // класса Mistake, передав тип ошибки – IncorrectOrderOfBrackets)
                // и добавить ее в контейнер с ошибками (mistakes)
            //Удалить из контейнера со всеми скобками (brackets) найденную парную скобку для текущей
        }
        else
        {
            //Создать новый объект ошибки (с помощью конструктора класса
            // Mistake, передав тип ошибки – ExcessiveClosingBracket) и добавить
            // его в контейнер с ошибками (mistakes)
        }
    }

    //Вернуть количество выявленных ошибок (countOfMistakes)
    return countOfMistakes=0;
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
