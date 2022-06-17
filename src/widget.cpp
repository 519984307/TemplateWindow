//
// Created by 12038 on 2022/6/15.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Widget.h" resolved

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
        : QWidget(parent)
        , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //取消菜单栏
    this->setWindowFlags(Qt::FramelessWindowHint);

    //阴影边框效果
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(10);
    shadow->setColor(Qt::black);
    shadow->setOffset(0);

    ui->shadowWidget->setGraphicsEffect(shadow);

    //父窗口透明
    this->setAttribute(Qt::WA_TranslucentBackground);

    //最大化最小化关闭功能实现
    connect(ui->btnMax, SIGNAL(clicked()), this, SLOT(btnMaxClickedSlot()));
    connect(ui->btnMin, SIGNAL(clicked()), this, SLOT(btnMinClickedSlot()));
    connect(ui->btnClose, SIGNAL(clicked()), this, SLOT(btnCloseClickedSlot()));

    ui->btnMin->setStyleSheet("border-image: url(../resources/min.png)");
    ui->btnMax->setStyleSheet("border-image: url(../resources/fullscreen3.png)");
    ui->btnClose->setStyleSheet("border-image: url(../resources/close.png)");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
//    QWidget::mousePressEvent(event);
    QPoint mouseStartPoint = event->globalPos();
    QPoint windowLeftTopPoint = this->geometry().topLeft();
    this->mousePosInWindow = mouseStartPoint - windowLeftTopPoint;
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
//    QWidget::mouseMoveEvent(event);
    if(this->mousePosInWindow == QPoint()) return;
    QPoint mousePoint = event->globalPos();
    QPoint windowLeftTopPoint = mousePoint - this->mousePosInWindow;
    this->move(windowLeftTopPoint);
}

void Widget::mouseReleaseEvent(QMouseEvent *)
{
    this->mousePosInWindow = QPoint();
}

void Widget::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton button;
    button=QMessageBox::question(this,tr("退出程序"),QString(tr("确认退出程序?")),QMessageBox::Yes|QMessageBox::No);
    if(button==QMessageBox::No)
    {
        event->ignore(); // 忽略退出信号，程序继续进行
    }
    else if(button==QMessageBox::Yes)
    {
        event->accept(); // 接受退出信号，程序退出
    }
}

void Widget::btnMaxClickedSlot()
{
    ui->btnMax->setStyleSheet("border-image: url(../resources/fullscreen4.png)");
    if(this->isMaximized()){
        ui->layoutMain->setMargin(9);
        ui->btnMax->setStyleSheet("border-image: url(../resources/fullscreen3.png)");
        this->showNormal();
    }
    else{
        ui->layoutMain->setMargin(0);
        ui->btnMax->setStyleSheet("border-image: url(../resources/fullscreen4.png)");
        this->showMaximized();
    }
}

void Widget::btnMinClickedSlot()
{
    this->showMinimized();
}

void Widget::btnCloseClickedSlot()
{
    this->close();
}

