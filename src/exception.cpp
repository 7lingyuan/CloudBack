#include "exception.h"

Exception::Exception(int error, QString errorMessage)
    : m_error(error)
    , m_errorMessage(errorMessage)
{}

int Exception::getError() const
{
    return m_error;
}

const QString &Exception::getErrorMessage() const
{
    return m_errorMessage;
}


