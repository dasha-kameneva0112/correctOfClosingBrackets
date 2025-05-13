#include "errorininputdata.h"

errorininputdata::errorininputdata() {}

errorininputdata::errorininputdata(ErrorsInInputDataType currentType)
{
    type = currentType;
}

errorininputdata::errorininputdata(ErrorsInInputDataType currentType, int indexOfLineWithError, int position)
{
    type = currentType;
    numberOfLine = indexOfLineWithError;
    positionOfError = position;
}

void errorininputdata::updateError(ErrorsInInputDataType currentType, int indexOfLineWithError, int position)
{
    type=currentType;
    numberOfLine=indexOfLineWithError;
    positionOfError=position;
}

void errorininputdata::addError(ErrorsInInputDataType currentType)
{    type=currentType; }


ErrorsInInputDataType errorininputdata::getType() const
{    return this->type; }

int errorininputdata::getLine() const
{    return this->numberOfLine; }

int errorininputdata::getPosition() const
{    return this->positionOfError; }
