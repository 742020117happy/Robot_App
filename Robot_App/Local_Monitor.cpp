#pragma execution_character_set("utf-8")
#include "Local_Monitor.h"
#include "Robot_Server.h"
 
/*************************************************************************************************************************************************
**Function:    构造函数
**Others:      构造函数初始化在主线程实例化中完成，故在子线程中运行时，成员函数的初始化不能在构造函数中完成
*************************************************************************************************************************************************/
c_Local_Monitor::c_Local_Monitor(QObject *parent) : QObject(parent)
{

}
/*************************************************************************************************************************************************
**Function:    析构函数
*************************************************************************************************************************************************/
c_Local_Monitor::~c_Local_Monitor()
{
	//线程中断
	m_Local_Monitor_Thread->requestInterruption();
	//线程退出
	m_Local_Monitor_Thread->quit();
	//线程等待
	m_Local_Monitor_Thread->wait();
	//删除对象
	delete m_Local_Monitor;
}
/*************************************************************************************************************************************************
**Function:初始化接口
*************************************************************************************************************************************************/
void c_Local_Monitor::Init()
{
	//实例化
	QEventLoop Init_Loop;
	m_Local_Monitor = new c_Robot_Server;
	m_Local_Monitor_Thread = new QThread;
	m_Local_Monitor->moveToThread(m_Local_Monitor_Thread);
	//等待初始化完成
	QObject::connect(m_Local_Monitor, &c_Robot_Server::Init_Done, &Init_Loop, &QEventLoop::quit);
	//初始化数据交换层
	QObject::connect(m_Local_Monitor_Thread, &QThread::started, m_Local_Monitor, &c_Robot_Server::Init);
	//连接设备
	QObject::connect(this, &c_Local_Monitor::Connect_Device, m_Local_Monitor, &c_Robot_Server::Connect_Device);
	QObject::connect(this, &c_Local_Monitor::Disconnect_Device, m_Local_Monitor, &c_Robot_Server::Disconnect_Device);
	//读写
	QObject::connect(this, &c_Local_Monitor::Write_Json, m_Local_Monitor, &c_Robot_Server::Write_Json);
	QObject::connect(m_Local_Monitor, &c_Robot_Server::Read_Json_Done, this, &c_Local_Monitor::Read_Json_Done);
	//设备状态改变
	QObject::connect(m_Local_Monitor, &c_Robot_Server::Connect_Done, this, &c_Local_Monitor::Set_Working);
	QObject::connect(m_Local_Monitor, &c_Robot_Server::Disconnect_Done, this, &c_Local_Monitor::Set_Default);
	//键盘按键改变
	QObject::connect(this, &c_Local_Monitor::Set_Working, this, [=] {emit setEnabled(true); });
	QObject::connect(this, &c_Local_Monitor::Set_Default, this, [=] {emit setEnabled(false); });
	//向状态服务写入状态
	QObject::connect(m_Local_Monitor, &c_Robot_Server::Connect_Done, this, &c_Local_Monitor::Connect_Done);
	QObject::connect(m_Local_Monitor, &c_Robot_Server::Disconnect_Done, this, &c_Local_Monitor::Disconnect_Done);
	//提示信息
	QObject::connect(m_Local_Monitor, &c_Robot_Server::Status, this, [=](int value) {emit Status(c_Variable::TCP_Status(value)); });
	//启动线程
	m_Local_Monitor_Thread->start();
	emit setEnabled(false);
	Init_Loop.exec();
	//保持监视状态
	QString ip = c_Variable::g_Communicate_DB.value("Local_Ip").toString();
	int port = c_Variable::g_Communicate_DB.value("Local_Monitor_Port").toInt();
	emit Connect_Device(ip, port);
}
/*************************************************************************************************************************************************
**Function: 公有接口
*************************************************************************************************************************************************/
void c_Local_Monitor::System_Scan(QJsonObject db)
{
	m_State_DB = db;
}
/*************************************************************************************************************************************************
**Function:私有接口
*************************************************************************************************************************************************/
void c_Local_Monitor::Connect_Done()
{
	m_Local_Monitor_State.insert("Connected", true);
	emit Write_Local_Monitor_State(m_Local_Monitor_State);
}
void c_Local_Monitor::Disconnect_Done()
{
	m_Local_Monitor_State.insert("Connected", false);
	emit Write_Local_Monitor_State(m_Local_Monitor_State);
}
//收到Ai服务器读请求，发送系统状态，解决粘包问题
void c_Local_Monitor::Read_Json_Done(QJsonObject json)
{
	m_Read_Ready = json.value("Read_Ready").toBool();
	if (m_Read_Ready){
		emit Write_Json(m_State_DB);
	}
}