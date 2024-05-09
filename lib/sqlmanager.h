#ifndef SQLMANAGER_H
#define SQLMANAGER_H

#include <QStringList>

class SQLManager
{
public:
    SQLManager();
    ~SQLManager();

    // 获取所有文件信息
    QStringList getAllFileInfo();

};

#endif // SQLMANAGER_H
