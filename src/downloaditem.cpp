#include "downloaditem.h"
#include "ClientConfig.hpp"

DownloadItem::DownloadItem(QWidget* parent)
    : QWidget{parent}
    , m_fileSvg(new QSvgWidget(":/resource/Icon/fileico/file_icon.svg", this))
    , m_btn_folder(new QPushButton(this))
{
    // 设置水平布局
    QHBoxLayout* layout = new QHBoxLayout(this);
    // 设置控件之间的距离
    layout->setSpacing(20);

    // 设置文件图标
    m_fileSvg->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_fileSvg->setFixedSize(45, 45);
    m_fileSvg->show();

    // 设置进度条
    m_progressBar.setMinimum(0);
    m_progressBar.setMaximum(100);
    m_progressBar.setValue(0);
    m_progressBar.setFixedWidth(200);


    // 设置按钮图标
    m_btn_folder->setIcon(QIcon(":/resource/Icon/folder.svg"));
    m_btn_folder->setIconSize(QSize(18, 18));

    // 设置按钮样式
    m_btn_folder->setStyleSheet("QPushButton{ border: 0px; border-radius: 5px; padding: 5px; }"
                                "QPushButton:hover{background-color: rgb(229,229,229);}"
                                "QPushButton:pressed{background-color: rgb(234,234,234);}");


    // 添加控件
    layout->addWidget(m_fileSvg);
    layout->addWidget(&m_fileName);
    // 加一个弹簧进行分割
    layout->addStretch();
    // 怎么设置进度条的水平长度固定
    layout->addWidget(&m_progressBar);
    layout->addWidget(m_btn_folder);
}

DownloadItem::DownloadItem(QString fileName, QWidget* parent)
    : DownloadItem(parent)
{
    setFileName(fileName);
    m_downloadPath = ClientConfig::getInstance().getDownloadPath();
}

void DownloadItem::setFileSvg(QSvgWidget* svgWidget)
{
    QHBoxLayout* layout = qobject_cast<QHBoxLayout*>(this->layout());
    if (layout)
    {
        // 先把旧的控件取出来
        layout->takeAt(0);
        delete m_fileSvg;

        // 设置新的控件
        m_fileSvg = svgWidget;
        m_fileSvg->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        m_fileSvg->setFixedSize(45, 45);

        // 在指定位置添加新的控件
        layout->insertWidget(0, m_fileSvg);

        // Show new image
        m_fileSvg->show();
    }
    else
    {
        qDebug() << "获取布局失败";
    }
}

void DownloadItem::setFileName(const QString& fileName)
{

    QFont font;
    font.setPixelSize(16);
    m_fileName.setFont(font);

    // 当文件名过长时进行省略
    QFontMetrics metrics(m_fileName.font());
    QString elidedText = metrics.elidedText(fileName, Qt::ElideRight, m_fileName.width() * 2  / 3);

    m_fileName.setText(elidedText);
}

const QString DownloadItem::getFileName() const
{
    return m_fileName.text();
}

const QString& DownloadItem::getDownlaodPath() const
{
    return m_downloadPath;
}

void DownloadItem::setProgressBarValue(int value)
{
    m_progressBar.setValue(value);
}





