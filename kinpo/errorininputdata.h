#ifndef ERRORININPUTDATA_H
#define ERRORININPUTDATA_H


class errorininputdata
{
public:
    errorininputdata();


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

    ErrorsInInputDataType type;
    int numberOfLine;
    int positionOfError;

    errorininputdata(ErrorsInInputDataType type, int indexOfLineWithError, int position);

};

#endif // ERRORININPUTDATA_H
