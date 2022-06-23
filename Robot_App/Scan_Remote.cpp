#pragma execution_character_set("utf-8")
#include "Scan_Remote.h"
 
/*************************************************************************************************************************************************
**Function:构造函数(状态监视)
*************************************************************************************************************************************************/
c_Scan_Remote::c_Scan_Remote(QObject *parent) : QObject(parent)
{

}
/*************************************************************************************************************************************************
**Function:析构
*************************************************************************************************************************************************/
c_Scan_Remote::~c_Scan_Remote()
{
	//线程中断
	m_Scan_Remote_Thread->requestInterruption();
	//线程退出
	m_Scan_Remote_Thread->quit();
	//线程等待
	m_Scan_Remote_Thread->wait();
	//删除对象
	delete m_Scan_Remote;
}
/*************************************************************************************************************************************************
**Function:初始化接口
*************************************************************************************************************************************************/
void c_Scan_Remote::Init()
{
	//实例化
	m_Scan_Remote = new c_Scan_Client;
	m_Scan_Remote_Thread = new QThread;
	m_Scan_Remote->moveToThread(m_Scan_Remote_Thread);
	//初始化数据交换层
	QObject::connect(m_Scan_Remote_Thread, &QThread::started, m_Scan_Remote, &c_Scan_Client::Init);
	//连接设备
	QObject::connect(this, &c_Scan_Remote::Connect_Device, m_Scan_Remote, &c_Scan_Client::Connect_Device);
	QObject::connect(this, &c_Scan_Remote::Disconnect_Device, m_Scan_Remote, &c_Scan_Client::Disconnect_Device);
	//写数据
	QObject::connect(this, &c_Scan_Remote::Write_String, m_Scan_Remote, &c_Scan_Client::Write_String);
	//设备状态改变
	QObject::connect(m_Scan_Remote, &c_Scan_Client::Connect_Done, this, &c_Scan_Remote::Set_Working);
	QObject::connect(m_Scan_Remote, &c_Scan_Client::Disconnect_Done, this, &c_Scan_Remote::Set_Default);
	//键盘按键改变
	QObject::connect(this, &c_Scan_Remote::Set_Working, this, [=] {emit setEnabled(true); });
	QObject::connect(this, &c_Scan_Remote::Set_Default, this, [=] {emit setEnabled(false); });
	//读到消息
	QObject::connect(m_Scan_Remote, &c_Scan_Client::Read_String_Done, this, &c_Scan_Remote::Read_String_Done);
	//向状态服务写入状态
	QObject::connect(m_Scan_Remote, &c_Scan_Client::Connect_Done, this, &c_Scan_Remote::Connect_Done);
	QObject::connect(m_Scan_Remote, &c_Scan_Client::Disconnect_Done, this, &c_Scan_Remote::Disconnect_Done);
	//提示信息
	QObject::connect(m_Scan_Remote, &c_Scan_Client::Status, this, [=](int state) {emit Status(c_Variable::TCP_Status(state)); });
	//启动线程
	m_Scan_Remote_Thread->start();
	emit setEnabled(false);
}
/*************************************************************************************************************************************************
**Function:操作接口
*************************************************************************************************************************************************/
void c_Scan_Remote::Connect()
{
	QString ip = c_Variable::g_Communicate_DB.value("Local_Ip").toString();
	int port = c_Variable::g_Communicate_DB.value("Local_Port").toInt();
	emit Connect_Device(ip, port);
}
void c_Scan_Remote::Prec_Scan_120_Start()
{
	QString ip = c_Variable::g_Communicate_DB.value("Remote_Ip").toString();
	int port = c_Variable::g_Communicate_DB.value("Prec_Scan_120_Port").toInt();
	emit Write_String(ip, port, "");
}
void c_Scan_Remote::Prec_Scan_120_Collection()
{
	QString ip = c_Variable::g_Communicate_DB.value("Remote_Ip").toString();
	int port = c_Variable::g_Communicate_DB.value("Prec_Scan_120_Port").toInt();
	emit Write_String(ip, port, "");
}
void c_Scan_Remote::Prec_Scan_120_Stop()
{
	QString ip = c_Variable::g_Communicate_DB.value("Remote_Ip").toString();
	int port = c_Variable::g_Communicate_DB.value("Prec_Scan_120_Port").toInt();
	emit Write_String(ip, port, "");
}
void c_Scan_Remote::Prec_Scan_121_Start()
{
	QString ip = c_Variable::g_Communicate_DB.value("Remote_Ip").toString();
	int port = c_Variable::g_Communicate_DB.value("Prec_Scan_121_Port").toInt();
	emit Write_String(ip, port, "");
}
void c_Scan_Remote::Prec_Scan_121_Collection()
{
	QString ip = c_Variable::g_Communicate_DB.value("Remote_Ip").toString();
	int port = c_Variable::g_Communicate_DB.value("Prec_Scan_121_Port").toInt();
	emit Write_String(ip, port, "");
}
void c_Scan_Remote::Prec_Scan_121_Stop()
{
	QString ip = c_Variable::g_Communicate_DB.value("Remote_Ip").toString();
	int port = c_Variable::g_Communicate_DB.value("Prec_Scan_121_Port").toInt();
	emit Write_String(ip, port, "");
}
void c_Scan_Remote::Fast_Scan_Start()
{
	QString ip = c_Variable::g_Communicate_DB.value("Remote_Ip").toString();
	int port = c_Variable::g_Communicate_DB.value("Fast_Scan_Port").toInt();
	emit Write_String(ip, port, "");
}
void c_Scan_Remote::Fast_Scan_Collection()
{
	QString ip = c_Variable::g_Communicate_DB.value("Remote_Ip").toString();
	int port = c_Variable::g_Communicate_DB.value("Fast_Scan_Port").toInt();
	emit Write_String(ip, port, "");
}
void c_Scan_Remote::Fast_Scan_Stop()
{
	QString ip = c_Variable::g_Communicate_DB.value("Remote_Ip").toString();
	int port = c_Variable::g_Communicate_DB.value("Fast_Scan_Port").toInt();
	emit Write_String(ip, port, "");
}

/*************************************************************************************************************************************************
**Function:私有的读状态函数，将状态量提取到公有成员变量
*************************************************************************************************************************************************/
void c_Scan_Remote::Read_String_Done(QString json)
{
	m_Scan_Remote_State.insert("DB", json);
	emit Write_Scan_Remote_State(m_Scan_Remote_State);
}
/*************************************************************************************************************************************************
**Function:私有连接状态写入
*************************************************************************************************************************************************/
void c_Scan_Remote::Connect_Done()
{
	m_Scan_Remote_State.insert("Connected", true);
	emit Write_Scan_Remote_State(m_Scan_Remote_State);
}
void c_Scan_Remote::Disconnect_Done()
{
	m_Scan_Remote_State.insert("Connected", false);
	emit Write_Scan_Remote_State(m_Scan_Remote_State);
}