#include "filelistitem.h"

FileListItem::FileListItem(QWidget* parent)
    : QWidget{parent}
    , m_fileSvg(new QSvgWidget(":/resource/Icon/fileico/file_icon.svg", this))
    , m_btn_download(new QPushButton(this))
{
    // 设置文件图标大小
    m_fileSvg->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_fileSvg->setFixedSize(45, 45);
    m_fileSvg->show();

    // 设置按钮图标
    m_btn_download->setIcon(QIcon("://resource/Icon/fileico/download.svg"));
    m_btn_download->setIconSize(QSize(22, 22));

    // 设置按钮样式
    m_btn_download->setStyleSheet("QPushButton{ border: 0px; border-radius: 5px; padding: 5px; }"
                                  "QPushButton:hover{background-color: rgb(229,229,229);}"
                                  "QPushButton:pressed{background-color: rgb(234,234,234);}");

    // 设置文件大小标签的样式
    m_fileSize.setStyleSheet("QLabel { color: #999; }");

    // 设置文件时间上传时间样式
    m_datetime.setStyleSheet("QLabel { color: #999; }");


    // 设置水平布局
    QGridLayout* layout = new QGridLayout(this);
    // 设置控件之间的水平距离
    layout->setHorizontalSpacing(10);

    // 添加控件到布局中
    layout->addWidget(m_fileSvg, 0, 0, 2, 1);
    layout->addWidget(&m_fileName, 0, 1, 1, 1);
    layout->addWidget(&m_fileSize, 1, 1, 1, 1);
    // 加一个空白进行分割
    QSpacerItem* horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    layout->addItem(horizontalSpacer, 0, 2, 2, 1);
    layout->addWidget(&m_datetime, 0, 3, 2, 1);
    layout->addWidget(m_btn_download, 0, 4, 2, 1);
}


FileListItem::FileListItem(const QString fileName, const QString fileSize, const QString dateTime, QWidget* parent)
    : FileListItem(parent)
{
    setFileName(fileName);
    setFileSize(fileSize);
    setDataTime(dateTime);
}



void FileListItem::setFileSvg(QSvgWidget* svgWidget)
{
    delete m_fileSvg;
    m_fileSvg = svgWidget;


    m_fileSvg->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_fileSvg->setFixedSize(45, 45);

    // Get the layout of FileListItem
    QGridLayout* layout = qobject_cast<QGridLayout*>(this->layout());
    if (layout)
    {
        layout->addWidget(m_fileSvg, 0, 0, 2, 1);
    }
    else
    {
        qDebug() << "获取布局失败";
    }

    // Show new image
    m_fileSvg->show();
}

void FileListItem::setFileName(const QString& fileName)
{
    QFont font;
    font.setPixelSize(16);
    m_fileName.setFont(font);

    // 当文件名过长时进行省略
    QFontMetrics metrics(m_fileName.font());
    QString elidedText = metrics.elidedText(fileName, Qt::ElideRight, m_fileName.width() * 2  / 3);

    m_fileName.setText(elidedText);
}

void FileListItem::setFileSize(const QString& fileszie)
{
    m_fileSize.setText(fileszie);
}

void FileListItem::setDataTime(const QString& datatime)
{
    m_datetime.setText(datatime);
}

const QString FileListItem::getFileName() const
{
    return m_fileName.text();
}


FileListItem::~FileListItem()
{}
