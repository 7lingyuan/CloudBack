#include "util.h"


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

QSvgWidget* Util::getSvgByFile(const QString& fileName)
{
    QFileInfo fileInfo(fileName);
    QString suffix = fileInfo.suffix().toLower();
    QSvgWidget* svgWidget = new QSvgWidget;

    // 创建一个后缀名到资源路径的映射
    static QMap<QString, QString> suffixSvgMap =
    {
        {"pdf", "://resource/Icon/fileico/pdf.svg"},
        {"txt", "://resource/Icon/fileico/txt.svg"},
        {"doc", "://resource/Icon/fileico/doc.svg"},
        {"docx", "://resource/Icon/fileico/docx.svg"},
        {"ppt", "://resource/Icon/fileico/ppt.svg"},
        {"pptx", "://resource/Icon/fileico/pptx.svg"},
        {"svg", "://resource/Icon/fileico/svg.svg"},
        {"jpg", "://resource/Icon/fileico/jpg.svg"},
        {"jpeg", "://resource/Icon/fileico/jpg.svg"},
        {"png", "://resource/Icon/fileico/png.svg"},
        {"gif", "://resource/Icon/fileico/gif.svg"},
        {"zip", "://resource/Icon/fileico/zip.svg"},
        {"html", "://resource/Icon/fileico/html.svg"},
        {"mp4", "://resource/Icon/fileico/mp4.svg"},
        {"exel", "://resource/Icon/fileico/exel.svg"},
        {"exe", "://resource/Icon/fileico/exe.svg"},
        {"dll", "://resource/Icon/fileico/dll.svg"},
        {"css", "://resource/Icon/fileico/css.svg"},
        {"js", "://resource/Icon/fileico/js.svg"},
        {"7z", "://resource/Icon/fileico/7z.svg"},
        {"ai", "://resource/Icon/fileico/ai.svg"},
        {"mp3", "://resource/Icon/fileico/mp3.svg"}
    };

    // 检查后缀名是否存在映射中
    if(suffixSvgMap.contains(suffix))
    {
        svgWidget->load(suffixSvgMap[suffix]);
    }
    else
    {
        // 默认图标
        svgWidget->load(QString("://resource/Icon/fileico/file_icon.svg"));
    }

    return svgWidget;
}
