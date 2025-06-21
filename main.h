/*!
 \mainpage Программа для проверки правильного закрытия всех скобок
 *
 * \section  Введение
 * Данная программа предназначена для анализа исходного кода на C++ и проверки на корректность использования:
 * - Круглых скобок: `()`
 * - Квадратных скобок: `[]`
 * - Фигурных скобок: `{}`
 *
 *
 * Для запуска программы:
 * 1. Программу необходимо сначала скомпилировать
 *
 * 2. Далее открыть папку debug, расположенную в данной директории
 *
 * 3. Далее в папке открыть cmd
 *
 * Пример запуска программы из командной строки:
 * BracketChecker.exe input.txt output.txt
 *
 * Получение результата от программы:
 * Для проверки правильного закрытия всех скобок необходимо проверить код из input.txt. Если в input.txt будут ошибки входных данных, они отобразятся на консоли, иначе программа запишет результат проверки в файл output.txt, расположенный в той же папке.
 *
 *
* \file main.h - заголовочный файл, содержащий описание функций программы
* \file main.cpp - файл содержит реальзацию функций программы
*/


#ifndef MAIN_H
#define MAIN_H

#include <QCoreApplication>
#include "bracket.h"
#include "mistake.h"
#include "errorininputdata.h"
#include "testfindcoupleforbracket.h"
#include "testupdateconteinerofbrackets.h"
#include "testskipstringconstant.h"
#include "testskipcharconstant.h"
#include "testfindallincorrectusesofbrackets.h"
#include "testfindnextbracket.h"
#include "testskipmultilinecomment.h"
#include "testskiponelinecomment.h"
#include "testconstructorbracket.h"

#include <QSet>
#include <QStack>
#include <qDebug>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QtTest/QtTest>
#include <QTest>


/*!
 * \brief readCppFile - функция
 * \param[in] filePath – путь к входному файлу с исходным кодом на С++
 * \param[in,out] code – массив строк для исходного кода (будет заполнен данными из входного файла)
 * \param[in,out] error – контейнер для найденных ошибок с входными данными
 * \return 0 – функция завершилась успешно
 */
int readCppFile (const QString& filePath, QStringList& code, errorininputdata& error);

/*!
 * \brief findAllIncorrectUsesOfBrackets - функция для выявления в исходном коде всех ошибок некорректного использования скобок или ошибки, связанные с входными данными.
 * \param[in] code – исходный код для проверки
 * \param[in,out] mistakes - пустой контейнер для найденных ошибок (изменяется в процессе)
 * \param[in,out] error - объект для найденной ошибки с входными данными
 * \return countOfMistakes – количество найденных ошибок некорректного использования скобок
 */
int findAllIncorrectUsesOfBrackets (const QStringList& code, QSet<mistake>& mistakes, errorininputdata& error);

/*!
 * \brief findNextBracket - функция для нахождения следующей скобки в зависимости от стартовых позиций (строки и позиции в коде)
 * \param[in] code - исходный код
 * \param[in,out] startLine - стартовая текущая строка для поиска скобок(изменяется в процессе)
 * \param[in,out] startPosition – стартовая текущая позиция в строке для поиска (изменяется в процессе)
 * \param[in,out] error - объект для найденной ошибки с входными данными
 * \return int 1 – скобка найдена; 0 – скобка не найдена; -1 – найдена ошибка с входными данными
 */
int findNextBracket (const QStringList& code, int& startLine, int& startPosition, errorininputdata& error);

/*!
 * \brief skipOneLineComment - функция для пропуска однострочного комментария
 * \param[in] code - исходный код
 * \param[in,out] currentLine - текущая строка (изменяется в процессе)
 * \param[in,out] currentPosition - текущая позиция (изменяется в процессе)
 */
void skipOneLineComment (const QStringList& code, int& currentLine, int& currentPosition);

/*!
 * \brief skipMultilineComment - функция для пропуска многострочного комментария
 * \param[in] code - исходный код
 * \param[in,out] currentLine - текущая строка (изменяется в процессе)
 * \param[in,out] currentPosition - текущая позиция (изменяется в процессе)
 * \return true - конец комментария найден; false - конец комментария не найден
 */
bool skipMultilineComment (const QStringList& code, int& currentLine, int& currentPosition);

/*!
 * \brief skipCharConstant - функция для пропуска символьной константы
 * \param[in] code - исходный код
 * \param[in,out] currentLine - текущая строка (изменяется в процессе)
 * \param[in,out] currentPosition - текущая позиция (изменяется в процессе)
 * \return true - конец символьной константы найден; false - конец символьной константы не найден
 */
bool skipCharConstant (const QStringList& code, int& currentLine, int& currentPosition);

/*!
 * \brief skipStringConstant - функция для пропуска строковой константы
 * \param[in] code - исходный код
 * \param[in,out] currentLine - текущая строка (изменяется в процессе)
 * \param[in,out] currentPosition - текущая позиция (изменяется в процессе)
 * \return true - конец строковой константы найден; false - конец строковой константы не найден
 */
bool skipStringConstant (const QStringList& code, int& currentLine, int& currentPosition);

/*!
 * \brief findCoupleForBracket - функция для поиска парной открывающей скобки для данной
 * \param[in] newBracket – найденная скобка
 * \param[in] brackets – контейнер с найденными скобками
 * \return indexOfBracket – индекс найденной парной открывающей скобки; -1 – пара не найдена
 */
int findCoupleForBracket(const bracket& newBracket, const QStack<bracket>& brackets);

/*!
 * \brief updateContainerOfBrackets - функция для обновления стека с найденными скобками и выявления ошибок использования скобок
 * \param[in] newBracket - найденная скобка
 * \param[in,out] brackets – контейнер с найденными скобками (изменяется в процессе)
 * \param[in,out] mistakes – контейнер для ошибок некорректного использования скобок (изменяется в процессе)
 * \return countOfMistakes – количество выявленных ошибок при добавлении
 */
int updateContainerOfBrackets (bracket& newBracket, QStack <bracket>& brackets, QSet<mistake>& mistakes);

/*!
 * \brief generateOutputTxtFile
 * \param[in] filePath – путь к выходному файлу
 * \param[in] code - исходный код
 * \param[in] mistakes – контейнер с найденными ошибками некорректного использования скобок
 * \param[in,out] errors – контейнер для ошибок с входными данными (изменяется в процессе)
 * \return 0 – функция завершилась успешно
 */
int generateOutputTxtFile (const QString& filePath, const QStringList& code, QSet<mistake>& mistakes, errorininputdata& error);



#endif // MAIN_H
