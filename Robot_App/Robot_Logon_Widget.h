#pragma once
#include "Public_Header.h"
#include "Ui_Robot_Logon_Widget.h"

QT_BEGIN_NAMESPACE
class Ui_Robot_Logon_Widget;
QT_END_NAMESPACE

class c_Robot_Logon_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit c_Robot_Logon_Widget(QWidget *parent = nullptr);
    ~c_Robot_Logon_Widget();

public slots:
    void keyPressEvent(QKeyEvent *event);
    void Logon_Robot_App();

signals:
    void Show_Robot_App();

private:
	Ui_Robot_Logon_Widget *ui;
};

