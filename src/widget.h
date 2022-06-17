//
// Created by 12038 on 2022/6/15.
//

#ifndef DUPLICATEFILESCHECK_WIDGET_H
#define DUPLICATEFILESCHECK_WIDGET_H

#include <QMouseEvent>
#include <QWidget>
#include <QPoint>
#include <QGraphicsDropShadowEffect>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void closeEvent(QCloseEvent *event);

private slots:
    void btnMaxClickedSlot();
    void btnMinClickedSlot();
    void btnCloseClickedSlot();

private:
    Ui::Widget *ui;

    QPoint mousePosInWindow = QPoint();
};


#endif //DUPLICATEFILESCHECK_WIDGET_H
