#include "widget.h"
#include "ui_page.h"


Widget::Widget(QWidget* parent)
    : SidebarWindow(parent)
{
    this->setWindowTitle("简易云盘");
    this->setupSidebar(this->sidebar());
    this->setupStackedWidget(this->stackedWidget());

    // 设置窗口最小高度为侧边栏所有控件的累计高度,确保窗口缩放时侧边栏中的控件不会重叠
    this->setMinimumHeight(this->sidebar()->childrenCumulativeHeight());

    this->resize(780, 580);

    connect(this->btn_expand, &SidebarOptionsButton::clicked, this->sidebar(), &Sidebar::autoExpand);
    connect(this->btn_page_1, &SidebarOptionsButton::selectedIndex, this->stackedWidget(), &QStackedWidget::setCurrentIndex);
    connect(this->btn_page_2, &SidebarOptionsButton::selectedIndex, this->stackedWidget(), &QStackedWidget::setCurrentIndex);
    connect(this->btn_page_3, &SidebarOptionsButton::selectedIndex, this->stackedWidget(), &QStackedWidget::setCurrentIndex);
    connect(this->btn_set, &SidebarOptionsButton::selectedIndex, this->stackedWidget(), &QStackedWidget::setCurrentIndex);
    connect(this, &SidebarWindow::clicked, this->sidebar(), &Sidebar::shrink);
}

Widget::~Widget()
{
    delete this->page_ui;
}

void Widget::setupSidebar(Sidebar* parent)
{
    btn_page_1 = new SidebarOptionsButton(parent, 0);
    btn_page_2 = new SidebarOptionsButton(parent, 1);
    btn_page_3 = new SidebarOptionsButton(parent, 2);
    verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);
    btn_set = new SidebarOptionsButton(parent, 3);
    btn_expand = new SidebarOptionsButton(parent);

    // 设置颜色
    // 1. 设置选中时颜色
    btn_page_1->setClickedColor(QColor(212, 226, 255));
    btn_page_2->setClickedColor(QColor(212, 226, 255));
    btn_page_3->setClickedColor(QColor(212, 226, 255));
    btn_set->setClickedColor(QColor(212, 226, 255));
    btn_expand->setClickedColor(QColor(212, 226, 255));

    // 2.设置选中时鼠标进入颜色
    btn_page_1->setClickedEnterColor(QColor(212, 226, 255));
    btn_page_2->setClickedEnterColor(QColor(212, 226, 255));
    btn_page_3->setClickedEnterColor(QColor(212, 226, 255));
    btn_set->setClickedEnterColor(QColor(212, 226, 255));
    btn_expand->setClickedEnterColor(QColor(212, 226, 255));

    // 3.设置未选中时鼠标进入颜色
    btn_page_1->setDisClickedEnterColor(QColor(236, 236, 238));
    btn_page_2->setDisClickedEnterColor(QColor(236, 236, 238));
    btn_page_3->setDisClickedEnterColor(QColor(236, 236, 238));
    btn_set->setDisClickedEnterColor(QColor(236, 236, 238));
    btn_expand->setDisClickedEnterColor(QColor(236, 236, 238));


    // 设置选中提示线颜色
    btn_page_1->setPromptLineColor(QColor(255, 50, 114));
    btn_page_2->setPromptLineColor(QColor(0, 174, 236));
    btn_page_3->setPromptLineColor(QColor(255, 198, 46));
    btn_set->setPromptLineColor(QColor(113, 124, 134));

    // 设置按钮图标
    btn_page_1->setIcon(QPixmap(":/resource/Icon/file.png"));
    btn_page_2->setIcon(QPixmap(":/resource/Icon/translation list.png"));
    // btn_page_3->setIcon(QPixmap(":/button_icon/collect.svg"));
    btn_set->setIcon(QPixmap(":/resource/Icon/settings.png"));
    btn_expand->setIcon(QPixmap(":/resource/Icon/extend.png"));

    // 设置右侧文本
    btn_page_1->setText("文件列表");
    btn_page_2->setText("文件传输");
    btn_page_3->setText("待定");
    btn_set->setText("设置");

    // 添加到sidebar中（Sidebar默认的垂直布局,注意添加顺序:从上到下）
    parent->addWidget(btn_page_1);
    parent->addWidget(btn_page_2);
    parent->addWidget(btn_page_3);
    parent->addItem(verticalSpacer);
    parent->addWidget(btn_set);
    parent->addWidget(btn_expand);



    // 设置展开时的宽度大小
    parent->setIncreasedWidth(90);

    btn_page_1->setChecked(true);               // 默认第一个按钮被选中
    btn_expand->setFixedSize(40, 36);           // 展开按钮固定大小
    btn_expand->setDrawPromptLineEnable(false); // 展开按钮不绘制选中提示线条
    btn_expand->setCheckable(false);            // 展开按钮不可选中(可点击但不可选中)
}

void Widget::setupStackedWidget(QStackedWidget* parent)
{
    this->page_ui = new Ui_page;

    page_file = new FileWindow(this);
    page_2 = new QWidget(parent);
    page_3 = new QWidget(parent);
    page_set = new QWidget(parent);

    // 设置ui布局

    page_ui->setupUi(page_2);
    page_ui->setupUi(page_3);
    page_ui->setupUi(page_set);

    // 向多页窗口添加页面
    parent->addWidget(page_file);
    parent->addWidget(page_2);
    parent->addWidget(page_3);
    parent->addWidget(page_set);

    // 设置展示页面中label的内容(展示页面只有一个label,特殊处理🤔)
    page_2->findChildren<QLabel*>().at(0)->setText("文件传输");
    page_3->findChildren<QLabel*>().at(0)->setText("要不要😍收藏一下❓");
    page_set->findChildren<QLabel*>().at(0)->setText("设置~~");

    parent->setCurrentIndex(0);                                   // 默认显示第一页
    parent->setStyleSheet("background-color: rgb(249,249,249);"); // 简单设置一下背景色
}
