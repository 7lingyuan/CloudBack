#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <QTcpSocket>
#include <QFileInfo>
#include <QSvgWidget>
#include <QMap>

class Util
{
public:
    // 二进制数据单位转化
    static QString convertBytes(qint64 bytes) ;
    // 检测网络状态
    static bool checkNetworkState() ;
    // 根据文件后缀确定文件svg图片
    static QSvgWidget* getSvgByFile(const QString& fileName);
};

#endif // UTIL_H
