#ifndef CLIENTCONFIG_HPP
#define CLIENTCONFIG_HPP
#include <QString>
#include <QStandardPaths>
class ClientConfig
{
public:
    static ClientConfig& getInstance()
    {
        static ClientConfig s_instance;
        return s_instance;
    }

    void setDownloadPath(QString downloadPath)
    {
        m_download_path = downloadPath;
    }


    const QString& getDownloadPath() const
    {
        return m_download_path;
    }
private:
    ClientConfig()
    {
        // 设置系统默认的下载目录为云盘文件的下载目录
        m_download_path = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
    }

    ClientConfig(const ClientConfig&) = delete;
private:
    QString m_download_path;
};

#endif // CLIENTCONFIG_HPP
