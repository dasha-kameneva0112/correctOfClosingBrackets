#include <QCoreApplication>
#include "main.h"

int main(int argc, char *argv[])
{
    system("chcp 1251>nul");
    QString first_arg = argv[1];
    // Если первый аргумент является флагом тестирования
    if (first_arg == "-test")
    {
        QTest::qExec(new testfindcoupleforbracket);
        QTest::qExec(new testupdateconteinerofbrackets);
        QTest::qExec(new testskipstringconstant);
        QTest::qExec(new testskipcharconstant);
        QTest::qExec(new testskipmultilinecomment);
        QTest::qExec(new testskiponelinecomment);
        QTest::qExec(new testfindnextbracket);
        QTest::qExec(new testfindallincorrectusesofbrackets);
        QTest::qExec(new testconstructorbracket);
        // Завершить работу програмы
        return 0;
    }

    /* qDebug() << "Starting program with arguments:";
    for (int i = 0; i < argc; ++i) {
        qDebug() << "argv[" << i << "] =" << argv[i];
    } */

    QCoreApplication a(argc, argv);

    //Считать из параметров командной строки путь к входному и выходному файлу
    QString inputFilePath = argv[1];
    QString outputFilePath = argv[2];

    // пустой объект для ошибки с входными данными
    errorininputdata error;
    QSet<mistake> mistakes;
    QStringList code;
    int countOfMistakes;

    //Считать данные из входного файла
    int resultOfFunction;
    resultOfFunction = readCppFile(inputFilePath, code, error);

    //Если ошибок во входных данных нет, то проверить корректность использования всех скобок в исходном коде
    if(resultOfFunction)
        countOfMistakes = findAllIncorrectUsesOfBrackets(code, mistakes, error);

    if(error.getType() == NoError) // не было error
        resultOfFunction = generateOutputTxtFile(outputFilePath, code, mistakes, error); //Сформировать выходной файл

    if(error.getType() != NoError)
    {
        //Вывести найденную ошибку с входными данными
        ErrorsInInputDataType type = error.getType();
        int line, pos;
        switch(type)
        {
        case NoAccessToInputFile:
            qInfo() << "Неверно указан файл с входными данными. Возможно, файл не существует." << '\n';
            break;
        case NoAccessToOutputFile:
            qInfo() << "Неверно указан файл для выходных данных. Возможно, указанного расположения не существует или нет прав на запись." << '\n';
            break;
        case EmptyInputFile:
            qInfo() << "Неверно указан файл с входными данными. Данный файл пуст. " << '\n';
            break;
        case UnclosedMultilineComment:
            line = error.getLine();
            pos = error.getPosition();
            qInfo() << "Во входном файле содержится код, в котором присутствует незакрытый многострочный комментарий:";
            qInfo().noquote() << line << ": " << code[line];
            qInfo().noquote() << QString(QString::number(line).length()+pos+3, ' ') << '^';
            break;
        case UnclosedStringConst:
            line = error.getLine();
            pos = error.getPosition();
            qInfo() << "Во входном файле содержится код, в котором присутствует не заканчивающаяся строковая константа:";
            qInfo().noquote() << line << ": " << code[line];
            qInfo().noquote() << QString(QString::number(line).length()+pos+3, ' ') << '^';
            break;
        case UnclosedCharConst:
            line = error.getLine();
            pos = error.getPosition();
            qInfo() << "Во входном файле содержится код, в котором присутствует не заканчивающаяся символьная константа: ";
            qInfo().noquote() << line << ": " << code[line];
            qInfo().noquote() << QString(QString::number(line).length()+pos+3, ' ') << '^';
            break;
        case IncorrectFileExtension:
            qInfo() << "Неверно указан файл для выходных данных. Расширение файла некорректно. " << '\n';
            break;
        case ExceedingMaxLengthInputFile:
            qInfo() << "Программа принимает на вход код длиной больше, чем максимально допустимая." << '\n';
        }
    }

    //Вернуть успешность завершения функции
    return 0;
}

int readCppFile (const QString& filePath, QStringList& code, errorininputdata& error)
{
    bool errorFound = 0; //0 - нет; 1 - найдена
    bool resultOfFunction = 1;
    QFileInfo fileInf(filePath);
    if(fileInf.suffix() != "cpp" && fileInf.suffix() != "h" && fileInf.suffix() != "txt") //если расширение неправильное
    {
        errorFound = 1;
        error.setType(IncorrectFileExtension);
    }

    if(errorFound==0)
    {
        //Открыть указанный входной файл
        QFile file(filePath);

        //Если не удалось успешно открыть входной файл, то...
        if(!file.open(QIODevice::ReadOnly))
        {
            errorFound = 1;
            error.setType(NoAccessToInputFile);
        }
        else
        {
            //Считать содержимое исходного кода из входного файла в массив строк (code)
            QTextStream inp(&file);
            while(!inp.atEnd())
                code << inp.readLine();

            //Если количество строк превышает допустимое или входной файл пуст, то...
            if(code.size()>10000)
            {
                errorFound = 1;
                error.setType(ExceedingMaxLengthInputFile);
            }
            if(code.isEmpty())
            {
                errorFound = 1;
                error.setType(EmptyInputFile);
            }
        }
    }

    if(errorFound==1)
        resultOfFunction=0;

    //Вернуть успешность завершения функции
    return resultOfFunction; //1 - успешно
}

int findAllIncorrectUsesOfBrackets (const QStringList& code, QSet<mistake>& mistakes, errorininputdata& error)
{
    QStack<bracket> brackets; // стек для найденных скобок
    QStack<bracket>::const_iterator it;
    int startLine = 0, startPosition = 0; // старт
    int countOfMistakes = 0;
    int resultOfFound = 0; //1 - нашли; 0 - не нашли; -1 - ошибка кода
    QString line = code[startLine];

    //Пока не конец кода или пока не найдена error...
    while(startPosition < line.size() && resultOfFound!=-1)
    {
        //Найти скобку любого типа в коде, начиная с startLine и startPosition
        resultOfFound=findNextBracket(code, startLine, startPosition, error);
        line = code[startLine];

        //Если скобка найдена
        if(resultOfFound == 1)
        {
            //Создать объект новой скобки и изменить содержимое стека
            bracket newBracket(code, startLine, startPosition);
            countOfMistakes += updateContainerOfBrackets(newBracket, brackets, mistakes);
        }

        //Изменить стартовые данные
        if(startPosition == line.size()-1)
        {
            if(startLine != code.size()-1)
            {
                startLine++;
                startPosition=0;
                line = code[startLine];
            } else startPosition++;
        } else startPosition++;
    }

    //Если error не найдена и стек не пустой, то…
    if(resultOfFound!=-1 && !(brackets.isEmpty()))
    {
        //Для каждой ошибки в стеке - создать новый объект(UnclosedBracket) и добавить в mistakes
        for(it = brackets.constBegin(); it!=brackets.constEnd(); ++it)
        {
            mistakes.insert(mistake(*it, UnclosedBracket));
            countOfMistakes++;
        }
    }

    if(resultOfFound == -1)
        countOfMistakes=0;

    //Вернуть количество ошибок в контейнер с ошибками mistakes
    return countOfMistakes;
}

int findNextBracket (const QStringList& code, int& startLine, int& startPosition, errorininputdata& error)
{
    int bracketIsFound=0; //1 - нашли; 0 - не нашли; -1 - ошибка кода
    QString line = code[startLine];
    int resultOfSkipping=-1;

    //Идти по строке, пока не нашли скобку или ErrorInInputData или пока не конец кода…
    for(startPosition; bracketIsFound==0 && startPosition < line.size(); startPosition++)
    {
        //Если встретили одно- или многострочный коммент
        if(line[startPosition]=='/' && startPosition!=line.size()-1)
        {
            if(line[startPosition+1]=='/')
            {
                startPosition++;
                skipOneLineComment(code, startLine, startPosition);
                line = code[startLine];
            }
            if(line[startPosition+1]=='*')
            {
                startPosition++;
                resultOfSkipping = skipMultilineComment(code, startLine, startPosition);
                line = code[startLine];
                if(resultOfSkipping==0)
                {
                    bracketIsFound = -1;
                    error.updateError(UnclosedMultilineComment, startLine, startPosition);
                }
            }
        }

        //Если встретили символьную константу («`»), пропустить ее (skipCharConstant)
        if(line[startPosition]=='\'' && bracketIsFound != -1)
        {
            resultOfSkipping = skipCharConstant(code, startLine, startPosition);
            line = code[startLine];
            if(resultOfSkipping==0)
            {
                bracketIsFound = -1;
                error.updateError(UnclosedCharConst, startLine, startPosition);
            }
        }

        //Если встретили строковую константу («"»), пропустить ее (skipStringConstant)
        if(line[startPosition]=='\"' && bracketIsFound != -1)
        {
            resultOfSkipping = skipStringConstant(code, startLine, startPosition);
            line = code[startLine];
            if(resultOfSkipping==0)
            {
                bracketIsFound = -1;
                error.updateError(UnclosedStringConst, startLine, startPosition);
            }
        }

        //Если встретили скобку любого типа, то...
        if(bracketIsFound != -1 && (line[startPosition]=='(' || line[startPosition]==')' || line[startPosition]=='[' || line[startPosition]==']' || line[startPosition]=='{' || line[startPosition]=='}'))
        {
            startPosition--; //(смещается)
            bracketIsFound = 1;
        }

        //Если строка закончилась, то…
        if(startPosition == line.size()-1)
        {
            if(startLine != code.size()-1)
            {
                startPosition=-1;
                startLine++;
                line = code[startLine];
            }
        }
    }
    if(bracketIsFound!=1)
        startPosition--; //смещается

    //Вернуть результат функции
    return bracketIsFound;
}

void skipOneLineComment (const QStringList& code, int& currentLine, int& currentPosition)
{
    QString line = code[currentLine];
    currentPosition++;
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
    int startOfCommentLine=currentLine;
    int startOfCommentPosition=currentPosition; //буферы для ошибки
    QString line = code[currentLine];
    bool end_of_code=false;

    //Идти по строке, пока не нашли конец комментария или пока не конец кода...
    do
    {
        //Если встретили «*/», то…
        if(line[currentPosition]=='*' && currentPosition+1 != line.size())
            if(line[currentPosition+1]=='/')
                resultOfSkipping=1; //Нашли конец

        //Если конец строки и строка не последняя, то...
        if(currentPosition == line.size()-1 && resultOfSkipping==0)
        {
            if(currentLine != code.size()-1)
            {
                currentPosition=0;
                currentLine++;
                line = code[currentLine];
            }
        } else
            // к следующему символу
            currentPosition++;
        if(currentLine>=code.size()-1 && currentPosition>=line.size()-1)
            end_of_code=true;

    } while (resultOfSkipping!=1 && end_of_code!=true);

    if(resultOfSkipping==0)
    {
        currentLine=startOfCommentLine;
        currentPosition=startOfCommentPosition;
    }

    //Вернуть результат проверки (нашли конец комментария или нет)
    return resultOfSkipping;
}

bool skipCharConstant (const QStringList& code, int& currentLine, int& currentPosition)
{
    bool resultOfSkipping=0; // 1 - успешно
    int startOfCommentLine=currentLine;
    int startOfCommentPosition=currentPosition; //буферы для ошибки
    QString line = code[currentLine];
    bool slashesFlag = 0;

    //Идти посимвольно по строке, пока не нашли конец константы или пока не конец строки...
    while(resultOfSkipping!=1 && currentPosition < line.size()-1)
    {
        // начинаем в первый раз после открывающей кавычки
        currentPosition++;

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
                //Нашли конец константы
                resultOfSkipping=1;
            else
                //Иначе oбнулить флаг нахождения слэша
                slashesFlag=0;
        }
    }
    if(resultOfSkipping==0)
    {
        currentLine=startOfCommentLine;
        currentPosition=startOfCommentPosition;
    }

    //Вернуть результат функции (успешность нахождения конца константы)
    return resultOfSkipping;
}

bool skipStringConstant (const QStringList& code, int& currentLine, int& currentPosition)
{
    int resultOfSkipping=0; // 1 - успешно
    //буферы для ошибки
    int startOfCommentLine=currentLine;
    int startOfCommentPosition=currentPosition;
    QString line = code[currentLine];
    int slashesCount=0;

    // Идти посимвольно по строке, пока не нашли конец константы или пока не конец строки...
    while(resultOfSkipping!=1 && currentPosition < line.size()-1)
    {
        // начинаем после открывающей кавычки
        currentPosition++;

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
                //Константа пропущена
                resultOfSkipping = 1;
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
    if(resultOfSkipping==0)
    {
        currentLine=startOfCommentLine;
        currentPosition=startOfCommentPosition;
    }
    return resultOfSkipping;
}

int updateContainerOfBrackets (bracket& newBracket, QStack <bracket>& brackets, QSet<mistake>& mistakes)
{
    int countOfMistakes=0;
    int indexOfCouple=0;
    bracket coupleBracket;
    bool order=false;
    bracket lastBracket;
    QStack<bracket>::iterator it=brackets.end();
    int index=0;

    //Если найденная скобка – открывающая, то…
    if(newBracket.getSide() == Opening)
        //Добавить объект в контейнер
        brackets.push(newBracket);

    if(newBracket.getSide() == Closing)
    {
        //Найти в стеке парную открывающую скобку для текущей
        indexOfCouple = findCoupleForBracket(newBracket, brackets);

        //Если пара найдена, то...
        if(indexOfCouple!=-1)
        {
            //Проверить порядок скобки и последней из стека (последняя – того же типа, открывающая)
            lastBracket = brackets.top();
            if(lastBracket.getType()==newBracket.getType() && lastBracket.getSide()==Opening)
                order = true;
            //Если порядок неверный, то...
            if(order == false)
            {
                //Изменить поле correctOfOrder у всех скобок до парной
                index=brackets.size()-1;
                while(index!=indexOfCouple)
                {
                    index--;
                    --it;
                    (*it).setOrder(false);
                }
            }
            --it;
            coupleBracket = *it;

            //Если у парной порядок неверный, то...
            if(coupleBracket.getOrder() == false)
            {
                //Создать новую ошибку (тип – IncorrectOrderOfBrackets)
                mistake newMistake(newBracket, IncorrectOrderOfBrackets);
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
            mistakes.insert(mistake(newBracket, ExcessiveClosingBracket));
            countOfMistakes++;
        }
    }

    //Вернуть количество выявленных ошибок
    return countOfMistakes;
}


int findCoupleForBracket(const bracket& newBracket, const QStack<bracket>& brackets)
{
    BracketType necessaryType = newBracket.getType(); //определили нужный тип
    int index=brackets.size();
    int result=0;

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
            if((*it).getType() == necessaryType)
            {
                if((*it).getSide() == Opening)
                    result=1;
            }
        }

        if(result!=1)
            index=-1;
    }

    //Вернуть индекс найденной парной открывающей скобки (или -1 – если нет пары)
    return index;
}

int generateOutputTxtFile (const QString& filePath, const QStringList& code, QSet<mistake>& mistakes, errorininputdata& error)
{
    bool errorFound = 0; //0 - нет; 1 - найдена
    bool resultOfFunction = 1;
    QFileInfo fileInf(filePath);

    //Если расширение выходного файла неверное (не .txt), то…
    if(fileInf.suffix() != "txt")
    {
        //Создать новый объект ошибки, передав тип ошибки – IncorrectFileExtension
        errorFound = 1;
        error.setType(IncorrectFileExtension);
    }
    else
    {
        //Создать указанный выходной файл
        QFile file(filePath);
        //Если не удалось успешно открыть выходной файл, то...
        if(!file.open(QIODevice::WriteOnly))
        {
            //Создать новый объект ошибки, передав тип ошибки – NoAccessToOutputFile
            errorFound = 1;
            error.setType(NoAccessToOutputFile);
        }
        else
        {
            //поток для записи
            QTextStream out(&file);
            // Установка кодировки
            out.setEncoding(QStringConverter::System);
            int numberOfMistake=1;

            //Если количество выявленных ошибок равно 0, то…
            if(mistakes.isEmpty())
            {
                // все скобки в коде используются корректно
                out << "Корректное использование всех скобок" << '\n';
            }
            else
            {
                // в коде присутствует некорректное использование скобок
                out << "Некорректное использование скобок" << '\n';

                //Добавить все выявленные ошибки из контейнера с ошибками и их описание
                QSet<mistake>::const_iterator iter;
                MistakeWithBracketsType type;
                bracket currentBracket;
                int line, pos;
                for(iter = mistakes.constBegin(); iter!=mistakes.constEnd(); ++iter)
                {
                    type = (*iter).getType();
                    currentBracket = (*iter).getBracket();
                    line = currentBracket.getLine();
                    pos = currentBracket.getPosition();

                    switch (type)
                    {
                    case UnclosedBracket:
                        out << QString::number(numberOfMistake) << ") Найдена незакрытая скобка:" << '\n';
                        break;
                    case ExcessiveClosingBracket:
                        out << QString::number(numberOfMistake) << ") Найдена избыточная закрывающая скобка:" << '\n';
                        break;
                    case IncorrectOrderOfBrackets:
                        out << QString::number(numberOfMistake) << ") Найден неправильный порядок закрытия скобок:" << '\n';
                        break;
                    }
                    out << line << ": " << code[line] << '\n';
                    out << QString(QString::number(line).length()+pos+2, ' ') << '^' << '\n';
                    numberOfMistake++;
                }
            }
        }
    }

    if(errorFound==1)
        resultOfFunction=0;

    //Вернуть успешность завершения функции
    return resultOfFunction; //1 - успешно
}
