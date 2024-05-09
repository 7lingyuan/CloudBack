#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <QString>

class Exception
{
public:
    Exception(int error, QString errorMessage);

    int getError() const;

    const QString& getErrorMessage() const;

protected:
    int m_error;
    QString m_errorMessage;
};

#endif // EXCEPTION_H
