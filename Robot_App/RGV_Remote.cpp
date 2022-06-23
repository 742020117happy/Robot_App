#pragma execution_character_set("utf-8")
#include "RGV_Remote.h"
#include "RGV_Client.h"

c_RGV_Remote::c_RGV_Remote(QObject *parent) : QObject(parent)
{

}
c_RGV_Remote::~c_RGV_Remote()
{
   //线程中断
	m_RGV_Remote_Thread->requestInterruption();
	//线程退出
	m_RGV_Remote_Thread->quit();
	//线程等待
	m_RGV_Remote_Thread->wait();
	//删除对象
	delete m_RGV_Remote;
}

void c_RGV_Remote::Init()
{
	//实例化
	m_RGV_Remote = new c_RGV_Client;
	m_RGV_Remote_Thread = new QThread;
	m_RGV_Remote->moveToThread(m_RGV_Remote_Thread);
	for (int i = 0; i <= 1000; i++)
	{
		QString addr = QString::number(i);
		m_Coils.insert(addr, 0000);
	}
	for (int i = 0; i <= 1000; i++)
	{
		QString addr = QString::number(i);
		m_HoldingRegisters.insert(addr, 0000);
	}
	//初始化数据交换层
	QObject::connect(m_RGV_Remote_Thread, &QThread::started, m_RGV_Remote, &c_RGV_Client::Init);
	//连接设备
	QObject::connect(this, &c_RGV_Remote::Connect_Device, m_RGV_Remote, &c_RGV_Client::Connect_Device);
	QObject::connect(this, &c_RGV_Remote::Disconnect_Device, m_RGV_Remote, &c_RGV_Client::Disconnect_Device);
	//读数据
	QObject::connect(this, &c_RGV_Remote::Read_DiscreteInputs, m_RGV_Remote, &c_RGV_Client::Read_DiscreteInputs);
	QObject::connect(this, &c_RGV_Remote::Read_InputRegisters, m_RGV_Remote, &c_RGV_Client::Read_InputRegisters);
	//写数据
	QObject::connect(this, &c_RGV_Remote::Write_Coils, m_RGV_Remote, &c_RGV_Client::Write_Coils);
	QObject::connect(this, &c_RGV_Remote::Write_HoldingRegisters, m_RGV_Remote, &c_RGV_Client::Write_HoldingRegisters);
	//设备状态改变
	QObject::connect(m_RGV_Remote, &c_RGV_Client::Connect_Done, this, &c_RGV_Remote::Set_Working);
	QObject::connect(m_RGV_Remote, &c_RGV_Client::Disconnect_Done, this, &c_RGV_Remote::Set_Default);
	//键盘按键改变
	QObject::connect(this, &c_RGV_Remote::Set_Working, this, [=] {emit setEnabled(true); });
	QObject::connect(this, &c_RGV_Remote::Set_Default, this, [=] {emit setEnabled(false); });
	//读到消息
	QObject::connect(m_RGV_Remote, &c_RGV_Client::Write_Coils_Done, this, &c_RGV_Remote::Write_Coils_Done);
	QObject::connect(m_RGV_Remote, &c_RGV_Client::Read_DiscreteInputs_Done, this, &c_RGV_Remote::Read_DiscreteInputs_Done);
	QObject::connect(m_RGV_Remote, &c_RGV_Client::Read_InputRegisters_Done, this, &c_RGV_Remote::Read_InputRegisters_Done);
	QObject::connect(m_RGV_Remote, &c_RGV_Client::Write_HoldingRegisters_Done, this, &c_RGV_Remote::Write_HoldingRegisters_Done);
	//向状态服务写入状态
	QObject::connect(m_RGV_Remote, &c_RGV_Client::Connect_Done, this, &c_RGV_Remote::Connect_Done);
	QObject::connect(m_RGV_Remote, &c_RGV_Client::Disconnect_Done, this, &c_RGV_Remote::Disconnect_Done);
	//提示信息
	QObject::connect(m_RGV_Remote, &c_RGV_Client::Status, this, [=](int state) {emit Status(c_Variable::Modbus_Status(state)); });
	//启动线程
	m_RGV_Remote_Thread->start();
	emit setEnabled(false);
}

//连接接口
void c_RGV_Remote::Connect()
{
	QString ip = c_Variable::g_Communicate_DB.value("RGV_Ip").toString();
	int port = c_Variable::g_Communicate_DB.value("RGV_Port").toInt();
	emit Connect_Device(ip, port);
}

void c_RGV_Remote::Forward_continuous_operation()
{

}
void c_RGV_Remote::The_nth_reverse_intermittent_operation()
{

}
void c_RGV_Remote::First_reverse_intermittent_operation()
{

}
void c_RGV_Remote::Stop_motion()
{

}
void c_RGV_Remote::Get_Right_Rise()
{

}
void c_RGV_Remote::Get_Left_Rise()
{

}
void c_RGV_Remote::Forward_motion()
{

}
void c_RGV_Remote::Reverse_motion()
{

}
void c_RGV_Remote::Left_Lifting_reset()
{

}
void c_RGV_Remote::Right_Lifting_reset()
{

}
void c_RGV_Remote::Left_Manual_rise()
{

}
void c_RGV_Remote::Right_Manual_rise()
{

}
void c_RGV_Remote::Left_Manual_descent()
{

}
void c_RGV_Remote::Right_Manual_descent()
{

}
void c_RGV_Remote::Clean_position()
{

}
void c_RGV_Remote::Left_door()
{

}
void c_RGV_Remote::Right_door()
{

}
void c_RGV_Remote::Middle_door()
{

}
void c_RGV_Remote::Middle_door_closing()
{

}
void c_RGV_Remote::Left_door_closing()
{

}
void c_RGV_Remote::Right_door_closing()
{

}
void c_RGV_Remote::Movement_speed()
{

}
void c_RGV_Remote::Intermittent_running_speed()
{

}
void c_RGV_Remote::First_creep_speed()
{

}
void c_RGV_Remote::Second_creep_speed()
{

}
void c_RGV_Remote::Acceleration()
{

}
void c_RGV_Remote::Deceleration()
{

}
void c_RGV_Remote::Left_reset_speed()
{

}
void c_RGV_Remote::Left_creep_speed()
{

}
void c_RGV_Remote::Left_manual_speed()
{

}
void c_RGV_Remote::Left_lifting_speed()
{

}
void c_RGV_Remote::Left_door_speed()
{

}
void c_RGV_Remote::Middle_door_speed()
{

}
void c_RGV_Remote::Right_door_speed()
{

}
void c_RGV_Remote::Right_reset_speed()
{

}
void c_RGV_Remote::Right_creep_speed()
{

}
void c_RGV_Remote::Right_manual_speed()
{

}
void c_RGV_Remote::Right_lifting_speed()
{

}
void c_RGV_Remote::Underbody_detection_distance()
{

}
void c_RGV_Remote::Underbody_detection_distance_delay()
{

}
void c_RGV_Remote::Trailer_wheel_distance()
{

}
void c_RGV_Remote::Trailer_wheel_error()
{

}
void c_RGV_Remote::Trailer_axle_distance()
{

}
void c_RGV_Remote::Trailer_axle_error()
{

}
void c_RGV_Remote::Motor_wheel_distance()
{

}
void c_RGV_Remote::Motor_wheel_distance_error()
{

}
void c_RGV_Remote::Motor_axle_distance()
{

}
void c_RGV_Remote::Motor_axle_error()
{

}
/*************************************************************************************************************************************************
**置位复位赋值
************************************************************************************************************************************************/
void c_RGV_Remote::Set_Coils(int addr)
{
	m_Coils.insert(QString::number(addr), 1);
	m_Write_Coils = true;
}
void c_RGV_Remote::Reset_Coils(int addr)
{
	m_Coils.insert(QString::number(addr), 0);
	m_Write_Coils = true;
}
void c_RGV_Remote::Set_HoldingRegisters(int addr, int value)
{
	m_HoldingRegisters.insert(QString::number(addr), value);
	m_Write_HoldingRegisters = true;
}
/*************************************************************************************************************************************************
**断开连接
************************************************************************************************************************************************/
void c_RGV_Remote::Disconnect_Done()
{
	m_RGV_Remote_State.insert("Connected", true);
	emit Write_RGV_Remote_State(m_RGV_Remote_State);
}
/*************************************************************************************************************************************************
**轮询操作
************************************************************************************************************************************************/
//完成连接
void c_RGV_Remote::Connect_Done()
{
	m_RGV_Remote_State.insert("Connected", true);
	emit Write_RGV_Remote_State(m_RGV_Remote_State);
	//读离散输入
	int Read_DiscreteInputs_Addr = c_Variable::g_Communicate_DB.value("Read_DiscreteInputs_Addr").toInt();
	int Read_DiscreteInputs_Size = c_Variable::g_Communicate_DB.value("Read_DiscreteInputs_Size").toInt();
	emit Read_DiscreteInputs(Read_DiscreteInputs_Addr, Read_DiscreteInputs_Size);	
}

//  需要写线圈时：读离散输入完成->写线圈
//不需要写线圈时：读离散输入完成->//读保持寄存器
void c_RGV_Remote::Read_DiscreteInputs_Done(QJsonObject value)
{
	m_RGV_Remote_DB.insert("DiscreteInputs", value);
	//此处插入要执行的操作

	//此处插入要执行的操作
	if (m_Write_Coils) {
		//写线圈
		int Write_Coils_Addr = c_Variable::g_Communicate_DB.value("Write_Coils_Addr").toInt();
		int Write_Coils_Size = c_Variable::g_Communicate_DB.value("Write_Coils_Size").toInt();
		emit Write_Coils(Write_Coils_Addr, m_Coils, Write_Coils_Size);
		m_Write_Coils = false;
	}
	if(!m_Write_Coils){
		//读保持寄存器
		int Read_InputRegisters_Addr = c_Variable::g_Communicate_DB.value("Read_InputRegisters_Addr").toInt();
		int Read_InputRegisters_Size = c_Variable::g_Communicate_DB.value("Read_InputRegisters_Size").toInt();
		emit Read_InputRegisters(Read_InputRegisters_Addr, Read_InputRegisters_Size);
	}
}

//写线圈完成->读输入寄存器
void c_RGV_Remote::Write_Coils_Done()
{	
	//读保持寄存器
	int Read_InputRegisters_Addr = c_Variable::g_Communicate_DB.value("Read_InputRegisters_Addr").toInt();
	int Read_InputRegisters_Size = c_Variable::g_Communicate_DB.value("Read_InputRegisters_Size").toInt();
	emit Read_InputRegisters(Read_InputRegisters_Addr, Read_InputRegisters_Size);
}

//读输入寄存器完成—>写保持寄存器
void c_RGV_Remote::Read_InputRegisters_Done(QJsonObject value)
{
	m_RGV_Remote_DB.insert("InputRegisters", value);
	m_RGV_Remote_State.insert("DB", m_RGV_Remote_DB);
	emit Write_RGV_Remote_State(m_RGV_Remote_State);
	//此处插入要执行的操作


	//此处插入要执行的操作
	if (m_Write_HoldingRegisters) {
		//写输入寄存器
		int Write_HoldingRegisters_Addr = c_Variable::g_Communicate_DB.value("Write_HoldingRegisters_Addr").toInt();
		int Write_HoldingRegisters_Size = c_Variable::g_Communicate_DB.value("Write_HoldingRegisters_Size").toInt();
		emit Write_HoldingRegisters(Write_HoldingRegisters_Addr, m_HoldingRegisters, Write_HoldingRegisters_Size);
		m_Write_HoldingRegisters = false;
	}
	if (!m_Write_HoldingRegisters) {
		//读离散输入
		int Read_DiscreteInputs_Addr = c_Variable::g_Communicate_DB.value("Read_DiscreteInputs_Addr").toInt();
		int Read_DiscreteInputs_Size = c_Variable::g_Communicate_DB.value("Read_DiscreteInputs_Size").toInt();
		emit Read_DiscreteInputs(Read_DiscreteInputs_Addr, Read_DiscreteInputs_Size);
	}
}

//写保持寄存器完成->读离散输入寄存器
void c_RGV_Remote::Write_HoldingRegisters_Done()
{
    //完成一次轮询
	//读离散输入
	int Read_DiscreteInputs_Addr = c_Variable::g_Communicate_DB.value("Read_DiscreteInputs_Addr").toInt();
	int Read_DiscreteInputs_Size = c_Variable::g_Communicate_DB.value("Read_DiscreteInputs_Size").toInt();
	emit Read_DiscreteInputs(Read_DiscreteInputs_Addr, Read_DiscreteInputs_Size);
}


