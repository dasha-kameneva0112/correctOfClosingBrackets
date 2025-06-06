#ifndef ERRORININPUTDATA_H
#define ERRORININPUTDATA_H

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

class errorininputdata
{
public:
    errorininputdata();
    errorininputdata(ErrorsInInputDataType currentType);
    errorininputdata(ErrorsInInputDataType currentType, int indexOfLineWithError, int position);
    void updateError(ErrorsInInputDataType currentType, int indexOfLineWithError, int position);
    void addError(ErrorsInInputDataType currentType);
    ErrorsInInputDataType getType() const;
    int getLine() const;
    int getPosition() const;

private:
    ErrorsInInputDataType type;
    int numberOfLine;
    int positionOfError;
};

#endif // ERRORININPUTDATA_H
