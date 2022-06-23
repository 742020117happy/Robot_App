#pragma once
#include "Public_Header.h"

QT_BEGIN_NAMESPACE
class c_Robot_Server;
QT_END_NAMESPACE

class c_Local_Remote : public QObject
{
	Q_OBJECT
public:
	explicit c_Local_Remote(QObject *parent = nullptr);
	~c_Local_Remote();
	QThread *m_Local_Remote_Thread;
	c_Robot_Server *m_Local_Remote;

	public slots:
	void Init();

signals:
	void Connect_Device(QString ip, int port);//连接到服务器
	void Disconnect_Device();//断开连接
	void Write_Json(QJsonObject json);
	void Remote_Cmd(QJsonObject json);
	void Write_Local_Remote_State(QJsonObject db);//写状态
	void Set_Working();//工作状态
	void Set_Default();//非工作状态
	void setEnabled(bool ready);//写消息状态
	void Status(QString status);//监视器状态

private:
	QJsonObject m_Local_Remote_State;

	private slots :
	void Connect_Done();
	void Disconnect_Done();
};
