#include "downloadwindow.h"
#include "util.h"
#include "downloaditem.h"

DownloadWindow::DownloadWindow(QWidget* parent)
    : QWidget(parent)
    , m_recordWidget( new QWidget(this))
    , m_listWidget(new QListWidget(m_recordWidget))
{
    // 设置顶层布局
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(6, 6, 6, 6);
    layout->setSpacing(6);

    // 设置内部布局
    QHBoxLayout* layoutWidget = new QHBoxLayout(m_recordWidget);
    layoutWidget->addWidget(m_listWidget);
    m_recordWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(m_recordWidget);

    // 设置对象名
    this->m_recordWidget->setObjectName("downloadWindow");
    m_listWidget->setObjectName("downloadListWidget");

    // 设置样式
    this->setStyleSheet("QWidget#downloadWindow {border-radius: 15px;background-color: white;}"
                        "QListWidget#downloadListWidget {border: none; }"
                        "QListWidget#downloadListWidget::item { border-bottom: 1px solid rgb(245,245,245); }"
                        "QListWidget#downloadListWidget::item:hover {background-color: rgb(229,243,255);}"
                        "QListWidget#downloadListWidget::item:selected { background-color: rgb(204,232,255); border: none; }");
}

DownloadWindow::~DownloadWindow()
{
    delete m_listWidget;
}

void DownloadWindow::addDownloadItem(const QString& fileName)
{
    QListWidgetItem* listWidgetItem = new QListWidgetItem(m_listWidget);
    listWidgetItem->setSizeHint(QSize(100, 60));

    // 这里必须指定父对象，否则svgWidget会独立一个窗口进行显示
    DownloadItem* downloadItem = new DownloadItem(fileName, m_listWidget);

    // 根据文件名确定文件的图标
    QSvgWidget* svgWidget = Util::getSvgByFile(fileName);

    // 给文件列表子项设置svg图片
    downloadItem->setFileSvg(svgWidget);

    m_listWidget->setItemWidget(listWidgetItem, downloadItem);

    // 设置点击文件路径按钮,打开文件管理器
    QPushButton* btn_folder = downloadItem->findChild<QPushButton*>(QString(), Qt::FindChildOption::FindDirectChildrenOnly);
    connect(btn_folder, &QPushButton::clicked, this, [downloadItem]()
    {
        QString download_path = downloadItem->getDownlaodPath();
        QDesktopServices::openUrl(QUrl::fromLocalFile(download_path));
    });
}

void DownloadWindow::updateProgress(const QString& fileName, qint64 bytesReceived, qint64 bytesTotal)
{
    int count = m_listWidget->count();
    for(int i = 0; i < count; ++i)
    {
        QListWidgetItem* listWidgetItem = m_listWidget->item(i);
        QWidget* widget = m_listWidget->itemWidget(listWidgetItem);
        DownloadItem* downloadItem = qobject_cast<DownloadItem*>(widget);
        // 能够正确的进行转型且名称匹配
        if(downloadItem && downloadItem->getFileName() == fileName)
        {
            downloadItem->setProgressBarValue(100 * bytesReceived / bytesTotal);
            break;
        }
    }
}

