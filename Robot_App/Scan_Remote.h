#pragma once
#include "Public_Header.h"
#include "Scan_Client.h"

class c_Scan_Client;

class c_Scan_Remote : public QObject
{
	Q_OBJECT
public:
	explicit c_Scan_Remote(QObject *parent = nullptr);
	~c_Scan_Remote();
	QThread *m_Scan_Remote_Thread;
	c_Scan_Client *m_Scan_Remote;

	public slots:
	//外部操作接口
	void Init();
	void Connect();
	void Prec_Scan_120_Start();
	void Prec_Scan_120_Collection();
	void Prec_Scan_120_Stop();
	void Prec_Scan_121_Start();
	void Prec_Scan_121_Collection();
	void Prec_Scan_121_Stop();
	void Fast_Scan_Start();
	void Fast_Scan_Collection();
	void Fast_Scan_Stop();

signals:
	void Connect_Device(QString ip, int port);//连接到服务器
	void Disconnect_Device();//断开连接
	void Write_Scan_Remote_State(QJsonObject db);//写状态
	void Set_Working();//工作状态
	void Set_Default();//非工作状态
	void setEnabled(bool ready);//写消息状态
	void Write_String(QString ip, int port, QString value);
	void Status(QString status);//监视器状态

private:
	QJsonObject m_Scan_Remote_State;

	private slots:
	void Connect_Done();
	void Disconnect_Done();
	void Read_String_Done(QString json);
};

