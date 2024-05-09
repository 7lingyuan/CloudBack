#include "util.h"

Util::Util() {}


/**
 * @brief 二进制数据单位转化
 * @param bytes 以字节单位的数据
 * @return 转化后的数据大小
 */
QString Util::convertBytes(qint64 bytes)
{
    const auto kb = 1024.0;
    const auto mb = kb * kb;
    const auto gb = mb * kb;
    const auto tb = gb * kb;

    QString unit;
    double result;

    if (bytes >= tb)
    {
        unit = "TB";
        result = bytes / tb;
    }
    else if (bytes >= gb)
    {
        unit = "GB";
        result = bytes / gb;
    }
    else if (bytes >= mb)
    {
        unit = "MB";
        result = bytes / mb;
    }
    else if(bytes >= kb)
    {
        unit = "KB";
        result = bytes / kb;
    }
    else
    {
        unit = "Bytes";
        result = static_cast<double>(bytes);
    }

    return QString::number(result, 'f', 1) + " " + unit;
}

bool Util::checkNetworkState()
{
    QTcpSocket socket;
    socket.connectToHost("www.baidu.com", 80);
    // 设置超时时间为3秒
    if (socket.waitForConnected(3000))
    {
        socket.abort();
        return true;
    }
    else
    {
        return false;
    }
}
