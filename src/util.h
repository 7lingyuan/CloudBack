#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <QTcpSocket>

class Util
{
public:
    Util();
    // 二进制数据单位转化
    static QString convertBytes(qint64 bytes);
    // 检测网络状态
    static bool checkNetworkState();

};

#endif // UTIL_H
