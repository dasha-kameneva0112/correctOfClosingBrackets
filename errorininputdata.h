#ifndef ERRORININPUTDATA_H
#define ERRORININPUTDATA_H

enum ErrorsInInputDataType {
    NoError,
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
    void setType(ErrorsInInputDataType new_type);
    void setLine(int line);
    void setPos(int pos);

    bool operator==(const errorininputdata& other) const
    {
        return (type == other.type && numberOfLine == other.numberOfLine &&
                positionOfError == other.positionOfError);
    }

private:
    ErrorsInInputDataType type=NoError;
    int numberOfLine=-1;
    int positionOfError=-1;
};

#endif // ERRORININPUTDATA_H
