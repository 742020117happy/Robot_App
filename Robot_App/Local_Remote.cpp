#pragma execution_character_set("utf-8")
#include "Local_Remote.h"
#include "Robot_Server.h"

/*************************************************************************************************************************************************
**Function:    构造函数
**Others:      构造函数初始化在主线程实例化中完成，故在子线程中运行时，成员函数的初始化不能在构造函数中完成
*************************************************************************************************************************************************/
c_Local_Remote::c_Local_Remote(QObject *parent) : QObject(parent)
{

}
/*************************************************************************************************************************************************
**Function:    析构函数
*************************************************************************************************************************************************/
c_Local_Remote::~c_Local_Remote()
{
	//线程中断
	m_Local_Remote_Thread->requestInterruption();
	//线程退出
	m_Local_Remote_Thread->quit();
	//线程等待
	m_Local_Remote_Thread->wait();
	//删除对象
	delete m_Local_Remote;
}
/*************************************************************************************************************************************************
**Function:初始化接口
*************************************************************************************************************************************************/
void c_Local_Remote::Init()
{
	//实例化
	QEventLoop Init_Loop;
	m_Local_Remote = new c_Robot_Server;
	m_Local_Remote_Thread = new QThread;
	m_Local_Remote->moveToThread(m_Local_Remote_Thread);
	//等待初始化完成
	QObject::connect(m_Local_Remote, &c_Robot_Server::Init_Done, &Init_Loop, &QEventLoop::quit);
	//初始化数据交换层
	QObject::connect(m_Local_Remote_Thread, &QThread::started, m_Local_Remote, &c_Robot_Server::Init);
	//连接设备
	QObject::connect(this, &c_Local_Remote::Connect_Device, m_Local_Remote, &c_Robot_Server::Connect_Device);
	QObject::connect(this, &c_Local_Remote::Disconnect_Device, m_Local_Remote, &c_Robot_Server::Disconnect_Device);
	//读写
	QObject::connect(this, &c_Local_Remote::Write_Json, m_Local_Remote, &c_Robot_Server::Write_Json);
	QObject::connect(m_Local_Remote, &c_Robot_Server::Read_Json_Done, this, &c_Local_Remote::Remote_Cmd);
	//设备状态改变
	QObject::connect(m_Local_Remote, &c_Robot_Server::Connect_Done, this, &c_Local_Remote::Set_Working);
	QObject::connect(m_Local_Remote, &c_Robot_Server::Disconnect_Done, this, &c_Local_Remote::Set_Default);
	//键盘按键改变
	QObject::connect(this, &c_Local_Remote::Set_Working, this, [=] {emit setEnabled(true); });
	QObject::connect(this, &c_Local_Remote::Set_Default, this, [=] {emit setEnabled(false); });
	//向状态服务写入状态
	QObject::connect(m_Local_Remote, &c_Robot_Server::Connect_Done, this, &c_Local_Remote::Connect_Done);
	QObject::connect(m_Local_Remote, &c_Robot_Server::Disconnect_Done, this, &c_Local_Remote::Disconnect_Done);
	//提示信息
	QObject::connect(m_Local_Remote, &c_Robot_Server::Status, this, [=](int value) {emit Status(c_Variable::TCP_Status(value)); });
	//启动线程
	m_Local_Remote_Thread->start();
	emit setEnabled(false);
	//保持监视状态
	QString ip = c_Variable::g_Communicate_DB.value("Local_Ip").toString();
	int port = c_Variable::g_Communicate_DB.value("Local_Remote_Port").toInt();
	emit Connect_Device(ip, port);
}
/*************************************************************************************************************************************************
**Function:私有接口
*************************************************************************************************************************************************/
void c_Local_Remote::Connect_Done()
{
	m_Local_Remote_State.insert("Connected", true);
	emit Write_Local_Remote_State(m_Local_Remote_State);
}
void c_Local_Remote::Disconnect_Done()
{
	m_Local_Remote_State.insert("Connected", false);
	emit Write_Local_Remote_State(m_Local_Remote_State);
}
