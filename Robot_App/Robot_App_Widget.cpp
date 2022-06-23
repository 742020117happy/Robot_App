#pragma execution_character_set("utf-8")
#include "Robot_App_Widget.h"
#include "System_Time.h"
#include "Fr_Light.h"
#include "RGV_Remote.h"
#include "Jaka_120_Remote.h"
#include "Jaka_121_Remote.h"
#include "Jaka_120_Monitor.h"
#include "Jaka_121_Monitor.h"
#include "Hypersen_30_Remote.h"
#include "Hypersen_31_Remote.h"
#include "Meijidenki_20_Remote.h"
#include "Meijidenki_21_Remote.h"
#include "Local_Remote.h"
#include "Local_Monitor.h"
#include "Scan_Remote.h"
c_Robot_App_Widget::c_Robot_App_Widget(QWidget * parent) : QMainWindow(parent) {
	/*************************************************************************************************************************************************
	**Function:建立UI界面
	*************************************************************************************************************************************************/
	ui = new Ui_Robot_App_Widget;
	ui->setupUi(this);
	/*************************************************************************************************************************************************
	**Function:实例化区
	*************************************************************************************************************************************************/
	QEventLoop Init_Loop;
	m_System_Time_Thread = new QThread;
	m_System_Time = new c_System_Time;
	m_State_DB_Thread = new QThread;
	m_State_DB = new c_State_DB;
	m_Variable = new c_Variable;
	m_RGV_Remote_Thread = new QThread;
	m_RGV_Remote = new c_RGV_Remote;
	m_Jaka_120_Remote_Thread = new QThread;
	m_Jaka_120_Remote = new c_Jaka_120_Remote;
	m_Jaka_121_Remote_Thread = new QThread;
	m_Jaka_121_Remote = new c_Jaka_121_Remote;
	m_Jaka_120_Monitor_Thread = new QThread;
	m_Jaka_120_Monitor = new c_Jaka_120_Monitor;
	m_Jaka_121_Monitor_Thread = new QThread;
	m_Jaka_121_Monitor = new c_Jaka_121_Monitor;
	m_Hypersen_30_Remote_Thread = new QThread;
	m_Hypersen_30_Remote = new c_Hypersen_30_Remote;
	m_Hypersen_31_Remote_Thread = new QThread;
	m_Hypersen_31_Remote = new c_Hypersen_31_Remote;
	m_Meijidenki_20_Remote_Thread = new QThread;
	m_Meijidenki_20_Remote = new c_Meijidenki_20_Remote;
	m_Meijidenki_21_Remote_Thread = new QThread;
	m_Meijidenki_21_Remote = new c_Meijidenki_21_Remote;
	m_Scan_Remote_Thread = new QThread;
	m_Scan_Remote = new c_Scan_Remote;
	m_Local_Remote_Thread = new QThread;
	m_Local_Remote = new c_Local_Remote;
	m_Local_Monitor_Thread = new QThread;
	m_Local_Monitor = new c_Local_Monitor;
	/*************************************************************************************************************************************************
	**Function:线程绑定区
	*************************************************************************************************************************************************/
	m_System_Time->moveToThread(m_System_Time_Thread);
	QObject::connect(m_System_Time_Thread, &QThread::started, m_System_Time, &c_System_Time::Init);

	m_State_DB->moveToThread(m_State_DB_Thread);
	QObject::connect(m_State_DB_Thread, &QThread::started, m_State_DB, &c_State_DB::Init);

	m_RGV_Remote->moveToThread(m_RGV_Remote_Thread);
	QObject::connect(m_RGV_Remote_Thread, &QThread::started, m_RGV_Remote, &c_RGV_Remote::Init);

	m_Jaka_120_Remote->moveToThread(m_Jaka_120_Remote_Thread);
	QObject::connect(m_Jaka_120_Remote_Thread, &QThread::started, m_Jaka_120_Remote, &c_Jaka_120_Remote::Init);

	m_Jaka_121_Remote->moveToThread(m_Jaka_121_Remote_Thread);
	QObject::connect(m_Jaka_121_Remote_Thread, &QThread::started, m_Jaka_121_Remote, &c_Jaka_121_Remote::Init);

	m_Jaka_120_Monitor->moveToThread(m_Jaka_120_Monitor_Thread);
	QObject::connect(m_Jaka_120_Monitor_Thread, &QThread::started, m_Jaka_120_Monitor, &c_Jaka_120_Monitor::Init);

	m_Jaka_121_Monitor->moveToThread(m_Jaka_121_Monitor_Thread);
	QObject::connect(m_Jaka_121_Monitor_Thread, &QThread::started, m_Jaka_121_Monitor, &c_Jaka_121_Remote::Init);

	m_Hypersen_30_Remote->moveToThread(m_Hypersen_30_Remote_Thread);
	QObject::connect(m_Hypersen_30_Remote_Thread, &QThread::started, m_Hypersen_30_Remote, &c_Hypersen_30_Remote::Init);

	m_Hypersen_31_Remote->moveToThread(m_Hypersen_31_Remote_Thread);
	QObject::connect(m_Hypersen_31_Remote_Thread, &QThread::started, m_Hypersen_31_Remote, &c_Hypersen_31_Remote::Init);

	m_Meijidenki_20_Remote->moveToThread(m_Meijidenki_20_Remote_Thread);
	QObject::connect(m_Meijidenki_20_Remote_Thread, &QThread::started, m_Meijidenki_20_Remote, &c_Meijidenki_20_Remote::Init);

	m_Meijidenki_21_Remote->moveToThread(m_Meijidenki_21_Remote_Thread);
	QObject::connect(m_Meijidenki_21_Remote_Thread, &QThread::started, m_Meijidenki_21_Remote, &c_Meijidenki_21_Remote::Init);

	m_Scan_Remote->moveToThread(m_Scan_Remote_Thread);
	QObject::connect(m_Scan_Remote_Thread, &QThread::started, m_Scan_Remote, &c_Scan_Remote::Init);

	m_Local_Remote->moveToThread(m_Local_Remote_Thread);
	QObject::connect(m_Local_Remote_Thread, &QThread::started, m_Local_Remote, &c_Local_Remote::Init);

	m_Local_Monitor->moveToThread(m_Local_Monitor_Thread);
	QObject::connect(m_Local_Monitor_Thread, &QThread::started, m_Local_Monitor, &c_Local_Monitor::Init);
	/*************************************************************************************************************************************************
	**Function:系统时间传递（全局变量只在主线程中读写）
	*************************************************************************************************************************************************/
	QObject::connect(m_System_Time, &c_System_Time::Write_System_Time, m_State_DB, &c_State_DB::Write_System_Time);
	QObject::connect(m_State_DB, &c_State_DB::System_Scan, this, &c_Robot_App_Widget::System_Scan);
	QObject::connect(m_State_DB, &c_State_DB::System_Scan, m_Local_Monitor, &c_Local_Monitor::System_Scan);
	/*************************************************************************************************************************************************
	**Function:系统状态
	*************************************************************************************************************************************************/
	QObject::connect(m_RGV_Remote, &c_RGV_Remote::Set_Working, ui->RGV_Working_State, &c_Fr_Light::Set_Working);
	QObject::connect(m_RGV_Remote, &c_RGV_Remote::Set_Default, ui->RGV_Working_State, &c_Fr_Light::Set_Default);
	QObject::connect(m_RGV_Remote, &c_RGV_Remote::Status, this, [=](QString value) {ui->Worry_List->addItem(m_Current_Time + "RGV遥控：" + value); });

	QObject::connect(m_Jaka_120_Remote, &c_Jaka_120_Remote::Set_Working, ui->Jaka_120_Remote_Working_State, &c_Fr_Light::Set_Working);
	QObject::connect(m_Jaka_120_Remote, &c_Jaka_120_Remote::Set_Default, ui->Jaka_120_Remote_Working_State, &c_Fr_Light::Set_Default);
	QObject::connect(m_Jaka_120_Remote, &c_Jaka_120_Remote::Write_Json_Error, ui->Jaka_120_Remote_Working_State, &c_Fr_Light::Set_Error);
	QObject::connect(m_Jaka_120_Remote, &c_Jaka_120_Remote::Status, this, [=](QString value) {ui->Worry_List->addItem(m_Current_Time + "机械臂120遥控：" + value); });

	QObject::connect(m_Jaka_121_Remote, &c_Jaka_121_Remote::Set_Working, ui->Jaka_121_Remote_Working_State, &c_Fr_Light::Set_Working);
	QObject::connect(m_Jaka_121_Remote, &c_Jaka_121_Remote::Set_Default, ui->Jaka_121_Remote_Working_State, &c_Fr_Light::Set_Default);
	QObject::connect(m_Jaka_121_Remote, &c_Jaka_121_Remote::Write_Json_Error, ui->Jaka_121_Remote_Working_State, &c_Fr_Light::Set_Error);
	QObject::connect(m_Jaka_121_Remote, &c_Jaka_121_Remote::Status, this, [=](QString value) {ui->Worry_List->addItem(m_Current_Time + "机械臂121遥控：" + value); });

	QObject::connect(m_Jaka_120_Monitor, &c_Jaka_120_Monitor::Set_Working, ui->Jaka_120_Monitor_Working_State, &c_Fr_Light::Set_Working);
	QObject::connect(m_Jaka_120_Monitor, &c_Jaka_120_Monitor::Set_Default, ui->Jaka_120_Monitor_Working_State, &c_Fr_Light::Set_Default);
	QObject::connect(m_Jaka_120_Monitor, &c_Jaka_120_Monitor::Status, this, [=](QString value) {ui->Worry_List->addItem(m_Current_Time + "机械臂120监视：" + value); });

	QObject::connect(m_Jaka_121_Monitor, &c_Jaka_121_Monitor::Set_Working, ui->Jaka_121_Remote_Working_State, &c_Fr_Light::Set_Working);
	QObject::connect(m_Jaka_121_Monitor, &c_Jaka_121_Monitor::Set_Default, ui->Jaka_121_Remote_Working_State, &c_Fr_Light::Set_Default);
	QObject::connect(m_Jaka_121_Monitor, &c_Jaka_121_Monitor::Status, this, [=](QString value) {ui->Worry_List->addItem(m_Current_Time + "机械臂121监视：" + value); });

	QObject::connect(m_Hypersen_30_Remote, &c_Hypersen_30_Remote::Set_Working, ui->Hypersen_30_Working_State, &c_Fr_Light::Set_Working);
	QObject::connect(m_Hypersen_30_Remote, &c_Hypersen_30_Remote::Set_Default, ui->Hypersen_30_Working_State, &c_Fr_Light::Set_Default);
	QObject::connect(m_Hypersen_30_Remote, &c_Hypersen_30_Remote::Status, this, [=](QString value) {ui->Worry_List->addItem(m_Current_Time + "面阵激光雷达30：" + value); });

	QObject::connect(m_Hypersen_31_Remote, &c_Hypersen_31_Remote::Set_Working, ui->Hypersen_31_Working_State, &c_Fr_Light::Set_Working);
	QObject::connect(m_Hypersen_31_Remote, &c_Hypersen_31_Remote::Set_Default, ui->Hypersen_31_Working_State, &c_Fr_Light::Set_Default);
	QObject::connect(m_Hypersen_31_Remote, &c_Hypersen_31_Remote::Status, this, [=](QString value) {ui->Worry_List->addItem(m_Current_Time + "面阵激光雷达31：" + value); });

	QObject::connect(m_Meijidenki_20_Remote, &c_Meijidenki_20_Remote::Set_Working, ui->Meijidenki_20_Working_State, &c_Fr_Light::Set_Working);
	QObject::connect(m_Meijidenki_20_Remote, &c_Meijidenki_20_Remote::Set_Default, ui->Meijidenki_20_Working_State, &c_Fr_Light::Set_Default);
	QObject::connect(m_Meijidenki_20_Remote, &c_Meijidenki_20_Remote::Status, this, [=](QString value) {ui->Worry_List->addItem(m_Current_Time + "线阵激光雷达20：" + value); });

	QObject::connect(m_Meijidenki_21_Remote, &c_Meijidenki_21_Remote::Set_Working, ui->Meijidenki_21_Working_State, &c_Fr_Light::Set_Working);
	QObject::connect(m_Meijidenki_21_Remote, &c_Meijidenki_21_Remote::Set_Default, ui->Meijidenki_21_Working_State, &c_Fr_Light::Set_Default);
	QObject::connect(m_Meijidenki_21_Remote, &c_Meijidenki_21_Remote::Status, this, [=](QString value) {ui->Worry_List->addItem(m_Current_Time + "线阵激光雷达21：" + value); });

	QObject::connect(m_Scan_Remote, &c_Scan_Remote::Set_Working, ui->Scan_Working_State, &c_Fr_Light::Set_Working);
	QObject::connect(m_Scan_Remote, &c_Scan_Remote::Set_Default, ui->Scan_Working_State, &c_Fr_Light::Set_Default);
	QObject::connect(m_Scan_Remote, &c_Scan_Remote::Status, this, [=](QString value) {ui->Worry_List->addItem(m_Current_Time + "采集机：" + value); });

	QObject::connect(m_Local_Remote, &c_Local_Remote::Set_Working, ui->Local_Remote_Working_State, &c_Fr_Light::Set_Working);
	QObject::connect(m_Local_Remote, &c_Local_Remote::Set_Default, ui->Local_Remote_Working_State, &c_Fr_Light::Set_Default);
	QObject::connect(m_Local_Remote, &c_Local_Remote::Status, this, [=](QString value) {ui->Worry_List->addItem(m_Current_Time + "本地控制服务：" + value); });

	QObject::connect(m_Local_Monitor, &c_Local_Monitor::Set_Working, ui->Local_Monitor_Working_State, &c_Fr_Light::Set_Working);
	QObject::connect(m_Local_Monitor, &c_Local_Monitor::Set_Default, ui->Local_Monitor_Working_State, &c_Fr_Light::Set_Default);
	QObject::connect(m_Local_Monitor, &c_Local_Monitor::Status, this, [=](QString value) {ui->Worry_List->addItem(m_Current_Time + "本地监视服务：" + value); });
	/*************************************************************************************************************************************************
	**Function:RGV遥控器
	*************************************************************************************************************************************************/
	QObject::connect(ui->RGV_Connect, &QPushButton::clicked, m_RGV_Remote, &c_RGV_Remote::Connect);
	QObject::connect(ui->RGV_Disconnect, &QPushButton::clicked, m_RGV_Remote, &c_RGV_Remote::Disconnect_Device);
	QObject::connect(m_RGV_Remote, &c_RGV_Remote::Write_RGV_Remote_State, m_State_DB, &c_State_DB::Write_RGV_State);
	/*************************************************************************************************************************************************
	**Function:机械臂120遥控
	*************************************************************************************************************************************************/
	QObject::connect(ui->Jaka_120_Remote_Connect, &QPushButton::clicked, m_Jaka_120_Remote, &c_Jaka_120_Remote::Connect);
	QObject::connect(ui->Jaka_120_Remote_Disconnect, &QPushButton::clicked, m_Jaka_120_Remote, &c_Jaka_120_Remote::Disconnect_Device);

	QObject::connect(m_Jaka_120_Remote, &c_Jaka_120_Remote::Write_Jaka_Remote_State, m_State_DB, &c_State_DB::Write_Jaka_120_Remote_State);

	QObject::connect(ui->Jaka_120_power_on, &QPushButton::clicked, m_Jaka_120_Remote, &c_Jaka_120_Remote::Jaka_power_on);
	QObject::connect(ui->Jaka_120_power_off, &QPushButton::clicked, m_Jaka_120_Remote, &c_Jaka_120_Remote::Jaka_power_off);
	QObject::connect(ui->Jaka_120_enable, &QPushButton::clicked, m_Jaka_120_Remote, &c_Jaka_120_Remote::Jaka_enable_robot);
	QObject::connect(ui->Jaka_120_disable, &QPushButton::clicked, m_Jaka_120_Remote, &c_Jaka_120_Remote::Jaka_disable_robot);
	QObject::connect(ui->Jaka_120_stop, &QPushButton::clicked, m_Jaka_120_Remote, &c_Jaka_120_Remote::Jaka_stop_program);
	QObject::connect(ui->Jaka_120_reset, &QPushButton::clicked, m_Jaka_120_Remote, &c_Jaka_120_Remote::Jaka_reset_program);

	QObject::connect(ui->Jaka_120_joint_1_1, &QPushButton::clicked, m_Jaka_120_Remote, &c_Jaka_120_Remote::Jaka_joint_1_1);
	QObject::connect(ui->Jaka_120_joint_2_1, &QPushButton::clicked, m_Jaka_120_Remote, &c_Jaka_120_Remote::Jaka_joint_2_1);
	QObject::connect(ui->Jaka_120_joint_3_1, &QPushButton::clicked, m_Jaka_120_Remote, &c_Jaka_120_Remote::Jaka_joint_3_1);
	QObject::connect(ui->Jaka_120_joint_4_1, &QPushButton::clicked, m_Jaka_120_Remote, &c_Jaka_120_Remote::Jaka_joint_4_1);
	QObject::connect(ui->Jaka_120_joint_5_1, &QPushButton::clicked, m_Jaka_120_Remote, &c_Jaka_120_Remote::Jaka_joint_5_1);
	QObject::connect(ui->Jaka_120_joint_6_1, &QPushButton::clicked, m_Jaka_120_Remote, &c_Jaka_120_Remote::Jaka_joint_6_1);
	QObject::connect(ui->Jaka_120_joint_1_2, &QPushButton::clicked, m_Jaka_120_Remote, &c_Jaka_120_Remote::Jaka_joint_1_2);
	QObject::connect(ui->Jaka_120_joint_2_2, &QPushButton::clicked, m_Jaka_120_Remote, &c_Jaka_120_Remote::Jaka_joint_2_2);
	QObject::connect(ui->Jaka_120_joint_3_2, &QPushButton::clicked, m_Jaka_120_Remote, &c_Jaka_120_Remote::Jaka_joint_3_2);
	QObject::connect(ui->Jaka_120_joint_4_2, &QPushButton::clicked, m_Jaka_120_Remote, &c_Jaka_120_Remote::Jaka_joint_4_2);
	QObject::connect(ui->Jaka_120_joint_5_2, &QPushButton::clicked, m_Jaka_120_Remote, &c_Jaka_120_Remote::Jaka_joint_5_2);
	QObject::connect(ui->Jaka_120_joint_6_2, &QPushButton::clicked, m_Jaka_120_Remote, &c_Jaka_120_Remote::Jaka_joint_6_2);

	QObject::connect(m_Jaka_120_Remote, &c_Jaka_121_Remote::setEnabled, ui->Jaka_120_power_on, &QPushButton::setEnabled);
	QObject::connect(m_Jaka_120_Remote, &c_Jaka_121_Remote::setEnabled, ui->Jaka_120_power_off, &QPushButton::setEnabled);
	QObject::connect(m_Jaka_120_Remote, &c_Jaka_121_Remote::setEnabled, ui->Jaka_120_enable, &QPushButton::setEnabled);
	QObject::connect(m_Jaka_120_Remote, &c_Jaka_121_Remote::setEnabled, ui->Jaka_120_disable, &QPushButton::setEnabled);
	QObject::connect(m_Jaka_120_Remote, &c_Jaka_121_Remote::setEnabled, ui->Jaka_120_stop, &QPushButton::setEnabled);
	QObject::connect(m_Jaka_120_Remote, &c_Jaka_121_Remote::setEnabled, ui->Jaka_120_reset, &QPushButton::setEnabled);

	QObject::connect(m_Jaka_120_Remote, &c_Jaka_121_Remote::setEnabled, ui->Jaka_120_joint_1_1, &QPushButton::setEnabled);
	QObject::connect(m_Jaka_120_Remote, &c_Jaka_121_Remote::setEnabled, ui->Jaka_120_joint_2_1, &QPushButton::setEnabled);
	QObject::connect(m_Jaka_120_Remote, &c_Jaka_121_Remote::setEnabled, ui->Jaka_120_joint_3_1, &QPushButton::setEnabled);
	QObject::connect(m_Jaka_120_Remote, &c_Jaka_121_Remote::setEnabled, ui->Jaka_120_joint_4_1, &QPushButton::setEnabled);
	QObject::connect(m_Jaka_120_Remote, &c_Jaka_121_Remote::setEnabled, ui->Jaka_120_joint_5_1, &QPushButton::setEnabled);
	QObject::connect(m_Jaka_120_Remote, &c_Jaka_121_Remote::setEnabled, ui->Jaka_120_joint_6_1, &QPushButton::setEnabled);
	QObject::connect(m_Jaka_120_Remote, &c_Jaka_121_Remote::setEnabled, ui->Jaka_120_joint_1_2, &QPushButton::setEnabled);
	QObject::connect(m_Jaka_120_Remote, &c_Jaka_121_Remote::setEnabled, ui->Jaka_120_joint_2_2, &QPushButton::setEnabled);
	QObject::connect(m_Jaka_120_Remote, &c_Jaka_121_Remote::setEnabled, ui->Jaka_120_joint_3_2, &QPushButton::setEnabled);
	QObject::connect(m_Jaka_120_Remote, &c_Jaka_121_Remote::setEnabled, ui->Jaka_120_joint_4_2, &QPushButton::setEnabled);
	QObject::connect(m_Jaka_120_Remote, &c_Jaka_121_Remote::setEnabled, ui->Jaka_120_joint_5_2, &QPushButton::setEnabled);
	QObject::connect(m_Jaka_120_Remote, &c_Jaka_121_Remote::setEnabled, ui->Jaka_120_joint_6_2, &QPushButton::setEnabled);
	/*************************************************************************************************************************************************
	**Function:机械臂121遥控
	*************************************************************************************************************************************************/
	QObject::connect(ui->Jaka_121_Remote_Connect, &QPushButton::clicked, m_Jaka_121_Remote, &c_Jaka_121_Remote::Connect);
	QObject::connect(ui->Jaka_121_Remote_Disconnect, &QPushButton::clicked, m_Jaka_121_Remote, &c_Jaka_121_Remote::Disconnect_Device);

	QObject::connect(m_Jaka_121_Remote, &c_Jaka_121_Remote::Write_Jaka_Remote_State, m_State_DB, &c_State_DB::Write_Jaka_121_Remote_State);

	QObject::connect(ui->Jaka_121_power_on, &QPushButton::clicked, m_Jaka_121_Remote, &c_Jaka_121_Remote::Jaka_power_on);
	QObject::connect(ui->Jaka_121_power_off, &QPushButton::clicked, m_Jaka_121_Remote, &c_Jaka_121_Remote::Jaka_power_off);
	QObject::connect(ui->Jaka_121_enable, &QPushButton::clicked, m_Jaka_121_Remote, &c_Jaka_121_Remote::Jaka_enable_robot);
	QObject::connect(ui->Jaka_121_disable, &QPushButton::clicked, m_Jaka_121_Remote, &c_Jaka_121_Remote::Jaka_disable_robot);
	QObject::connect(ui->Jaka_121_stop, &QPushButton::clicked, m_Jaka_121_Remote, &c_Jaka_121_Remote::Jaka_stop_program);
	QObject::connect(ui->Jaka_121_reset, &QPushButton::clicked, m_Jaka_121_Remote, &c_Jaka_121_Remote::Jaka_reset_program);

	QObject::connect(ui->Jaka_121_joint_1_1, &QPushButton::clicked, m_Jaka_121_Remote, &c_Jaka_121_Remote::Jaka_joint_1_1);
	QObject::connect(ui->Jaka_121_joint_2_1, &QPushButton::clicked, m_Jaka_121_Remote, &c_Jaka_121_Remote::Jaka_joint_2_1);
	QObject::connect(ui->Jaka_121_joint_3_1, &QPushButton::clicked, m_Jaka_121_Remote, &c_Jaka_121_Remote::Jaka_joint_3_1);
	QObject::connect(ui->Jaka_121_joint_4_1, &QPushButton::clicked, m_Jaka_121_Remote, &c_Jaka_121_Remote::Jaka_joint_4_1);
	QObject::connect(ui->Jaka_121_joint_5_1, &QPushButton::clicked, m_Jaka_121_Remote, &c_Jaka_121_Remote::Jaka_joint_5_1);
	QObject::connect(ui->Jaka_121_joint_6_1, &QPushButton::clicked, m_Jaka_121_Remote, &c_Jaka_121_Remote::Jaka_joint_6_1);
	QObject::connect(ui->Jaka_121_joint_1_2, &QPushButton::clicked, m_Jaka_121_Remote, &c_Jaka_121_Remote::Jaka_joint_1_2);
	QObject::connect(ui->Jaka_121_joint_2_2, &QPushButton::clicked, m_Jaka_121_Remote, &c_Jaka_121_Remote::Jaka_joint_2_2);
	QObject::connect(ui->Jaka_121_joint_3_2, &QPushButton::clicked, m_Jaka_121_Remote, &c_Jaka_121_Remote::Jaka_joint_3_2);
	QObject::connect(ui->Jaka_121_joint_4_2, &QPushButton::clicked, m_Jaka_121_Remote, &c_Jaka_121_Remote::Jaka_joint_4_2);
	QObject::connect(ui->Jaka_121_joint_5_2, &QPushButton::clicked, m_Jaka_121_Remote, &c_Jaka_121_Remote::Jaka_joint_5_2);
	QObject::connect(ui->Jaka_121_joint_6_2, &QPushButton::clicked, m_Jaka_121_Remote, &c_Jaka_121_Remote::Jaka_joint_6_2);

	QObject::connect(m_Jaka_121_Remote, &c_Jaka_121_Remote::setEnabled, ui->Jaka_121_power_on, &QPushButton::setEnabled);
	QObject::connect(m_Jaka_121_Remote, &c_Jaka_121_Remote::setEnabled, ui->Jaka_121_power_off, &QPushButton::setEnabled);
	QObject::connect(m_Jaka_121_Remote, &c_Jaka_121_Remote::setEnabled, ui->Jaka_121_enable, &QPushButton::setEnabled);
	QObject::connect(m_Jaka_121_Remote, &c_Jaka_121_Remote::setEnabled, ui->Jaka_121_disable, &QPushButton::setEnabled);
	QObject::connect(m_Jaka_121_Remote, &c_Jaka_121_Remote::setEnabled, ui->Jaka_121_stop, &QPushButton::setEnabled);
	QObject::connect(m_Jaka_121_Remote, &c_Jaka_121_Remote::setEnabled, ui->Jaka_121_reset, &QPushButton::setEnabled);

	QObject::connect(m_Jaka_121_Remote, &c_Jaka_121_Remote::setEnabled, ui->Jaka_121_joint_1_1, &QPushButton::setEnabled);
	QObject::connect(m_Jaka_121_Remote, &c_Jaka_121_Remote::setEnabled, ui->Jaka_121_joint_2_1, &QPushButton::setEnabled);
	QObject::connect(m_Jaka_121_Remote, &c_Jaka_121_Remote::setEnabled, ui->Jaka_121_joint_3_1, &QPushButton::setEnabled);
	QObject::connect(m_Jaka_121_Remote, &c_Jaka_121_Remote::setEnabled, ui->Jaka_121_joint_4_1, &QPushButton::setEnabled);
	QObject::connect(m_Jaka_121_Remote, &c_Jaka_121_Remote::setEnabled, ui->Jaka_121_joint_5_1, &QPushButton::setEnabled);
	QObject::connect(m_Jaka_121_Remote, &c_Jaka_121_Remote::setEnabled, ui->Jaka_121_joint_6_1, &QPushButton::setEnabled);
	QObject::connect(m_Jaka_121_Remote, &c_Jaka_121_Remote::setEnabled, ui->Jaka_121_joint_1_2, &QPushButton::setEnabled);
	QObject::connect(m_Jaka_121_Remote, &c_Jaka_121_Remote::setEnabled, ui->Jaka_121_joint_2_2, &QPushButton::setEnabled);
	QObject::connect(m_Jaka_121_Remote, &c_Jaka_121_Remote::setEnabled, ui->Jaka_121_joint_3_2, &QPushButton::setEnabled);
	QObject::connect(m_Jaka_121_Remote, &c_Jaka_121_Remote::setEnabled, ui->Jaka_121_joint_4_2, &QPushButton::setEnabled);
	QObject::connect(m_Jaka_121_Remote, &c_Jaka_121_Remote::setEnabled, ui->Jaka_121_joint_5_2, &QPushButton::setEnabled);
	QObject::connect(m_Jaka_121_Remote, &c_Jaka_121_Remote::setEnabled, ui->Jaka_121_joint_6_2, &QPushButton::setEnabled);
	/*************************************************************************************************************************************************
	**Function:面阵激光雷达30遥控
	*************************************************************************************************************************************************/
	QObject::connect(ui->Hypersen_30_Connect, &QPushButton::clicked, m_Hypersen_30_Remote, &c_Hypersen_30_Remote::Connect);
	QObject::connect(ui->Hypersen_30_Disconnect, &QPushButton::clicked, m_Hypersen_30_Remote, &c_Hypersen_30_Remote::Disconnect_Device);
	QObject::connect(m_Hypersen_30_Remote, &c_Hypersen_30_Remote::Write_Hypersen_Remote_State, m_State_DB, &c_State_DB::Write_Hypersen_30_State);

	QObject::connect(ui->RUN_SINGLE_SHOT_30, &QPushButton::clicked, m_Hypersen_30_Remote, &c_Hypersen_30_Remote::Run_Single_Shot);
	QObject::connect(ui->RUN_CONTINUOUS_30, &QPushButton::clicked, m_Hypersen_30_Remote, &c_Hypersen_30_Remote::Run_Continuous);
	QObject::connect(ui->RUN_IDLE_30, &QPushButton::clicked, m_Hypersen_30_Remote, &c_Hypersen_30_Remote::Run_Idle);

	QObject::connect(m_Hypersen_30_Remote, &c_Hypersen_30_Remote::setEnabled, ui->RUN_SINGLE_SHOT_30, &QPushButton::setEnabled);
	QObject::connect(m_Hypersen_30_Remote, &c_Hypersen_30_Remote::setEnabled, ui->RUN_CONTINUOUS_30, &QPushButton::setEnabled);
	QObject::connect(m_Hypersen_30_Remote, &c_Hypersen_30_Remote::setEnabled, ui->RUN_IDLE_30, &QPushButton::setEnabled);
	/*************************************************************************************************************************************************
	**Function:面阵激光雷达31遥控
	*************************************************************************************************************************************************/
	QObject::connect(ui->Hypersen_31_Connect, &QPushButton::clicked, m_Hypersen_31_Remote, &c_Hypersen_31_Remote::Connect);
	QObject::connect(ui->Hypersen_31_Disconnect, &QPushButton::clicked, m_Hypersen_31_Remote, &c_Hypersen_31_Remote::Disconnect_Device);
	QObject::connect(m_Hypersen_31_Remote, &c_Hypersen_31_Remote::Write_Hypersen_Remote_State, m_State_DB, &c_State_DB::Write_Hypersen_31_State);

	QObject::connect(ui->RUN_SINGLE_SHOT_31, &QPushButton::clicked, m_Hypersen_31_Remote, &c_Hypersen_31_Remote::Run_Single_Shot);
	QObject::connect(ui->RUN_CONTINUOUS_31, &QPushButton::clicked, m_Hypersen_31_Remote, &c_Hypersen_31_Remote::Run_Continuous);
	QObject::connect(ui->RUN_IDLE_31, &QPushButton::clicked, m_Hypersen_31_Remote, &c_Hypersen_31_Remote::Run_Idle);

	QObject::connect(m_Hypersen_31_Remote, &c_Hypersen_31_Remote::setEnabled, ui->RUN_SINGLE_SHOT_31, &QPushButton::setEnabled);
	QObject::connect(m_Hypersen_31_Remote, &c_Hypersen_31_Remote::setEnabled, ui->RUN_CONTINUOUS_31, &QPushButton::setEnabled);
	QObject::connect(m_Hypersen_31_Remote, &c_Hypersen_31_Remote::setEnabled, ui->RUN_IDLE_31, &QPushButton::setEnabled);
	/*************************************************************************************************************************************************
	**Function:线阵激光雷达20遥控
	*************************************************************************************************************************************************/
	QObject::connect(ui->Meijidenki_20_Connect, &QPushButton::clicked, m_Meijidenki_20_Remote, &c_Meijidenki_20_Remote::Connect);
	QObject::connect(ui->Meijidenki_20_Disconnect, &QPushButton::clicked, m_Meijidenki_20_Remote, &c_Meijidenki_20_Remote::Disconnect_Device);
	QObject::connect(m_Meijidenki_20_Remote, &c_Meijidenki_20_Remote::Write_Meijidenki_Remote_State, m_State_DB, &c_State_DB::Write_Meijidenki_20_State);

	QObject::connect(ui->Meijidenki_20_START_LMD, &QPushButton::clicked, m_Meijidenki_20_Remote, &c_Meijidenki_20_Remote::START_LMD);
	QObject::connect(ui->Meijidenki_20_STOP_LMD, &QPushButton::clicked, m_Meijidenki_20_Remote, &c_Meijidenki_20_Remote::STOP_LMD);

	QObject::connect(m_Meijidenki_20_Remote, &c_Meijidenki_20_Remote::setEnabled, ui->Meijidenki_20_START_LMD, &QPushButton::setEnabled);
	QObject::connect(m_Meijidenki_20_Remote, &c_Meijidenki_20_Remote::setEnabled, ui->Meijidenki_20_STOP_LMD, &QPushButton::setEnabled);
	/*************************************************************************************************************************************************
	**Function:线阵激光雷达21遥控
	*************************************************************************************************************************************************/
	QObject::connect(ui->Meijidenki_21_Connect, &QPushButton::clicked, m_Meijidenki_21_Remote, &c_Meijidenki_21_Remote::Connect);
	QObject::connect(ui->Meijidenki_21_Disconnect, &QPushButton::clicked, m_Meijidenki_21_Remote, &c_Meijidenki_21_Remote::Disconnect_Device);
	QObject::connect(m_Meijidenki_21_Remote, &c_Meijidenki_21_Remote::Write_Meijidenki_Remote_State, m_State_DB, &c_State_DB::Write_Meijidenki_21_State);

	QObject::connect(ui->Meijidenki_21_START_LMD, &QPushButton::clicked, m_Meijidenki_20_Remote, &c_Meijidenki_20_Remote::START_LMD);
	QObject::connect(ui->Meijidenki_21_STOP_LMD, &QPushButton::clicked, m_Meijidenki_20_Remote, &c_Meijidenki_20_Remote::STOP_LMD);

	QObject::connect(m_Meijidenki_21_Remote, &c_Meijidenki_21_Remote::setEnabled, ui->Meijidenki_21_START_LMD, &QPushButton::setEnabled);
	QObject::connect(m_Meijidenki_21_Remote, &c_Meijidenki_21_Remote::setEnabled, ui->Meijidenki_21_STOP_LMD, &QPushButton::setEnabled);
	/*************************************************************************************************************************************************
	**Function:采集机遥控
	*************************************************************************************************************************************************/
	QObject::connect(ui->Scan_Connect, &QPushButton::clicked, m_Scan_Remote, &c_Scan_Remote::Connect);
	QObject::connect(ui->Scan_Disconnect, &QPushButton::clicked, m_Scan_Remote, &c_Scan_Remote::Disconnect_Device);
	/*************************************************************************************************************************************************
	**Function:本地控制服务
	*************************************************************************************************************************************************/
	QObject::connect(ui->Local_Remote_Disconnect, &QPushButton::clicked, m_Local_Remote, &c_Local_Remote::Disconnect_Device);
	QObject::connect(m_Local_Remote, &c_Local_Remote::Remote_Cmd, this, [=](QJsonObject object) {
		m_Cmd_Name = object.value("Cmd_Name").toString();
		//{"Cmd_Name":"Work_Start","Begin_Time":"20211-11-06-09-40","Car_Type":"CRH2A","Car_Num":"2411"}
		if (m_Cmd_Name == "Work_Start") {
			m_Begin_Time = object.value("Begin_Time").toString();
			ui->Begin_Time->setText(m_Begin_Time);
			m_Car_Type = object.value("Car_Type").toString();
			ui->Car_Type->setText(m_Car_Type);
			m_Car_Num = object.value("Car_Num").toString();
			ui->Car_Num->setText(m_Car_Num);
			ui->Work_Num->setText(m_Begin_Time + "-" + m_Car_Type + m_Car_Num);
			ui->Work_Start->clicked();
		}
	});

	/*************************************************************************************************************************************************
	**Function:本地监视服务
	*************************************************************************************************************************************************/
	QObject::connect(ui->Local_Monitor_Disconnect, &QPushButton::clicked, m_Local_Monitor, &c_Local_Monitor::Disconnect_Device);
	/*************************************************************************************************************************************************
	**Function:线程启动区
	*************************************************************************************************************************************************/
	m_Local_Remote_Thread->start();
	m_Local_Monitor_Thread->start();
	m_RGV_Remote_Thread->start();
	m_Jaka_120_Monitor_Thread->start();
	m_Jaka_121_Monitor_Thread->start();
	m_Jaka_120_Remote_Thread->start();
	m_Jaka_121_Remote_Thread->start();
	m_Hypersen_30_Remote_Thread->start();
	m_Hypersen_31_Remote_Thread->start();
	m_Meijidenki_20_Remote_Thread->start();
	m_Meijidenki_21_Remote_Thread->start();
	m_Scan_Remote_Thread->start();
	m_State_DB_Thread->start();
	m_System_Time_Thread->start();
	/*************************************************************************************************************************************************
	**Function:等待所有线程正常运行
	*************************************************************************************************************************************************/
	QObject::connect(m_System_Time, &c_System_Time::Write_System_Time, &Init_Loop, &QEventLoop::quit);
	Init_Loop.exec();
	/*************************************************************************************************************************************************
	**Function:切换页面
	*************************************************************************************************************************************************/
	ui->stackedWidget->setCurrentWidget(ui->Work_Widget);
	QObject::connect(ui->Show_Work_Widget, &QPushButton::clicked, this, [=]() {ui->stackedWidget->setCurrentWidget(ui->Work_Widget); });
	QObject::connect(ui->Show_Setting_Widget, &QPushButton::clicked, this, [=]() {ui->stackedWidget->setCurrentWidget(ui->Setting_Widget); });
	QObject::connect(ui->Show_RGV_Remote_Widget, &QPushButton::clicked, this, [=]() {ui->stackedWidget->setCurrentWidget(ui->RGV_Remote_Widget); });
	QObject::connect(ui->Show_RGV_Monitor_Widget, &QPushButton::clicked, this, [=]() {ui->stackedWidget->setCurrentWidget(ui->RGV_Monitor_Widget); });
	QObject::connect(ui->Show_Jaka_120_Widget, &QPushButton::clicked, this, [=]() {ui->stackedWidget->setCurrentWidget(ui->Jaka_120_Widget); });
	QObject::connect(ui->Show_Jaka_121_Widget, &QPushButton::clicked, this, [=]() {ui->stackedWidget->setCurrentWidget(ui->Jaka_121_Widget); });
	QObject::connect(ui->Show_Scan_Widget, &QPushButton::clicked, this, [=]() {ui->stackedWidget->setCurrentWidget(ui->Scan_Widget); });
	QObject::connect(ui->Show_Hypersen_Widget, &QPushButton::clicked, this, [=]() {ui->stackedWidget->setCurrentWidget(ui->Hypersen_Widget); });
	QObject::connect(ui->Show_Meijidenki_Widget, &QPushButton::clicked, this, [=]() {ui->stackedWidget->setCurrentWidget(ui->Meijidenki_Widget); });
	QObject::connect(ui->Show_Robot_Teach_Widget, &QPushButton::clicked, this, [=]() {ui->stackedWidget->setCurrentWidget(ui->Robot_Teach_Widget); });
	/*************************************************************************************************************************************************
	**Function:初始任务信息讯参数
	*************************************************************************************************************************************************/
	ui->Begin_Time->setText(m_Current_Time);
	/*************************************************************************************************************************************************
	**Function:初始化通讯参数
	*************************************************************************************************************************************************/
	ui->Local_Ip->setText(c_Variable::g_Communicate_DB.value("Local_Ip").toString());
	ui->Local_Port->setText(QString::number(c_Variable::g_Communicate_DB.value("Local_Port").toInt()));
	ui->Collector_Ip->setText(c_Variable::g_Communicate_DB.value("Collector_Ip").toString());
	ui->Prec_Scan_120_Port->setText(QString::number(c_Variable::g_Communicate_DB.value("Prec_Scan_120_Port").toInt()));
	ui->Prec_Scan_121_Port->setText(QString::number(c_Variable::g_Communicate_DB.value("Prec_Scan_121_Port").toInt()));
	ui->Fast_Scan_Port->setText(QString::number(c_Variable::g_Communicate_DB.value("Fast_Scan_Port").toInt()));
	ui->Jaka_120_Ip->setText(c_Variable::g_Communicate_DB.value("Jaka_120_Ip").toString());
	ui->Jaka_121_Ip->setText(c_Variable::g_Communicate_DB.value("Jaka_121_Ip").toString());
	ui->Jaka_Remote_Port->setText(QString::number(c_Variable::g_Communicate_DB.value("Jaka_Remote_Port").toInt()));
	ui->Jaka_Monitor_Port->setText(QString::number(c_Variable::g_Communicate_DB.value("Jaka_Monitor_Port").toInt()));
	ui->RGV_Ip->setText(c_Variable::g_Communicate_DB.value("RGV_Ip").toString());
	ui->RGV_Port->setText(QString::number(c_Variable::g_Communicate_DB.value("RGV_Port").toInt()));
	ui->Hypersen_30_Ip->setText(c_Variable::g_Communicate_DB.value("Hypersen_30_Ip").toString());
	ui->Hypersen_30_Id->setText(QString::number(c_Variable::g_Communicate_DB.value("Hypersen_30_Id").toInt()));
	ui->Hypersen_30_Port->setText(QString::number(c_Variable::g_Communicate_DB.value("Hypersen_30_Port").toInt()));
	ui->Hypersen_31_Ip->setText(c_Variable::g_Communicate_DB.value("Hypersen_31_Ip").toString());
	ui->Hypersen_31_Id->setText(QString::number(c_Variable::g_Communicate_DB.value("Hypersen_31_Id").toInt()));
	ui->Hypersen_31_Port->setText(QString::number(c_Variable::g_Communicate_DB.value("Hypersen_31_Port").toInt()));
	ui->Meijidenki_20_Ip->setText(c_Variable::g_Communicate_DB.value("Meijidenki_20_Ip").toString());
	ui->Meijidenki_20_Id->setText(QString::number(c_Variable::g_Communicate_DB.value("Meijidenki_20_Id").toInt()));
	ui->Meijidenki_20_Port->setText(QString::number(c_Variable::g_Communicate_DB.value("Meijidenki_20_Port").toInt()));
	ui->Meijidenki_21_Ip->setText(c_Variable::g_Communicate_DB.value("Meijidenki_21_Ip").toString());
	ui->Meijidenki_21_Id->setText(QString::number(c_Variable::g_Communicate_DB.value("Meijidenki_21_Id").toInt()));
	ui->Meijidenki_21_Port->setText(QString::number(c_Variable::g_Communicate_DB.value("Meijidenki_21_Port").toInt()));
	ui->Web_Server_Ip->setText(c_Variable::g_Communicate_DB.value("Web_Server_Ip").toString());
	ui->Ai_Server_Ip->setText(c_Variable::g_Communicate_DB.value("Ai_Server_Ip").toString());
	ui->Local_Monitor_Port->setText(QString::number(c_Variable::g_Communicate_DB.value("Local_Monitor_Port").toInt()));
	ui->Local_Remote_Port->setText(QString::number(c_Variable::g_Communicate_DB.value("Local_Remote_Port").toInt()));

	ui->Write_Coils_Size->setValue(c_Variable::g_Communicate_DB.value("Write_Coils_Size").toInt());
	ui->Read_DiscreteInputs_Size->setValue(c_Variable::g_Communicate_DB.value("Read_DiscreteInputs_Size").toInt());
	ui->Read_InputRegisters_Size->setValue(c_Variable::g_Communicate_DB.value("Read_InputRegisters_Size").toInt());
	ui->Write_HoldingRegisters_Size->setValue(c_Variable::g_Communicate_DB.value("Write_HoldingRegisters_Size").toInt());

	ui->Write_Coils_Addr->setValue(c_Variable::g_Communicate_DB.value("Write_Coils_Addr").toInt());
	ui->Read_DiscreteInputs_Addr->setValue(c_Variable::g_Communicate_DB.value("Read_DiscreteInputs_Addr").toInt());
	ui->Read_DiscreteInputs_Addr->setValue(c_Variable::g_Communicate_DB.value("Read_DiscreteInputs_Addr").toInt());
	ui->Write_HoldingRegisters_Addr->setValue(c_Variable::g_Communicate_DB.value("Write_HoldingRegisters_Addr").toInt());

	ui->Right_Rise_number->setText(QString::number(c_Variable::g_Communicate_DB.value("Right_Rise_number").toInt()));
	ui->Left_Rise_number->setText(QString::number(c_Variable::g_Communicate_DB.value("Left_Rise_number").toInt()));
	ui->Movement_speed_2->setText(QString::number(c_Variable::g_Communicate_DB.value("Movement_speed_2").toInt()));
	ui->Intermittent_running_speed_2->setText(QString::number(c_Variable::g_Communicate_DB.value("Intermittent_running_speed_2").toInt()));
	ui->First_creep_speed_2->setText(QString::number(c_Variable::g_Communicate_DB.value("First_creep_speed_2").toInt()));
	ui->Second_creep_speed_2->setText(QString::number(c_Variable::g_Communicate_DB.value("Second_creep_speed_2").toInt()));
	ui->Acceleration_2->setText(QString::number(c_Variable::g_Communicate_DB.value("Acceleration_2").toInt()));
	ui->Deceleration_2->setText(QString::number(c_Variable::g_Communicate_DB.value("Deceleration_2").toInt()));
	ui->Left_reset_speed_2->setText(QString::number(c_Variable::g_Communicate_DB.value("Left_reset_speed_2").toInt()));
	ui->Left_creep_speed_2->setText(QString::number(c_Variable::g_Communicate_DB.value("Left_creep_speed_2").toInt()));
	ui->Left_manual_speed_2->setText(QString::number(c_Variable::g_Communicate_DB.value("Left_manual_speed_2").toInt()));
	ui->Left_lifting_speed_2->setText(QString::number(c_Variable::g_Communicate_DB.value("Left_lifting_speed_2").toInt()));
	ui->Left_door_speed_2->setText(QString::number(c_Variable::g_Communicate_DB.value("Left_door_speed_2").toInt()));
	ui->Middle_door_speed_2->setText(QString::number(c_Variable::g_Communicate_DB.value("Middle_door_speed_2").toInt()));
	ui->Right_door_speed_2->setText(QString::number(c_Variable::g_Communicate_DB.value("Right_door_speed_2").toInt()));
	ui->Right_reset_speed_2->setText(QString::number(c_Variable::g_Communicate_DB.value("Right_reset_speed_2").toInt()));
	ui->Right_creep_speed_2->setText(QString::number(c_Variable::g_Communicate_DB.value("Right_creep_speed_2").toInt()));
	ui->Right_manual_speed_2->setText(QString::number(c_Variable::g_Communicate_DB.value("Right_manual_speed_2").toInt()));
	ui->Right_lifting_speed_2->setText(QString::number(c_Variable::g_Communicate_DB.value("Right_lifting_speed_2").toInt()));
	ui->Underbody_detection_distance_2->setText(QString::number(c_Variable::g_Communicate_DB.value("Underbody_detection_distance_2").toInt()));
	ui->Underbody_detection_distance_delay_2->setText(QString::number(c_Variable::g_Communicate_DB.value("Underbody_detection_distance_delay_2").toInt()));
	ui->Trailer_wheel_distance_2->setText(QString::number(c_Variable::g_Communicate_DB.value("Trailer_wheel_distance_2").toInt()));
	ui->Trailer_wheel_error_2->setText(QString::number(c_Variable::g_Communicate_DB.value("Trailer_wheel_error_2").toInt()));
	ui->Trailer_axle_distance_2->setText(QString::number(c_Variable::g_Communicate_DB.value("Trailer_axle_distance_2").toInt()));
	ui->Trailer_axle_error_2->setText(QString::number(c_Variable::g_Communicate_DB.value("Trailer_axle_error_2").toInt()));
	ui->Motor_wheel_distance_2->setText(QString::number(c_Variable::g_Communicate_DB.value("Motor_wheel_distance_2").toInt()));
	ui->Motor_wheel_distance_error_2->setText(QString::number(c_Variable::g_Communicate_DB.value("Motor_wheel_distance_error_2").toInt()));
	ui->Motor_axle_distance_2->setText(QString::number(c_Variable::g_Communicate_DB.value("Motor_axle_distance_2").toInt()));
	ui->Motor_axle_error_2->setText(QString::number(c_Variable::g_Communicate_DB.value("Motor_axle_error_2").toInt()));
	/*************************************************************************************************************************************************
	**Function:绑定通讯参数
	*************************************************************************************************************************************************/
	QObject::connect(ui->Local_Ip, &QLineEdit::textChanged, this, [=](QString ip) {c_Variable::g_Communicate_DB.insert("Local_Ip", ip); });
	QObject::connect(ui->Local_Port, &QLineEdit::textChanged, this, [=](QString port) {c_Variable::g_Communicate_DB.insert("Local_Port", port.toInt()); });
	QObject::connect(ui->Collector_Ip, &QLineEdit::textChanged, this, [=](QString ip) {c_Variable::g_Communicate_DB.insert("Collector_Ip", ip); });
	QObject::connect(ui->Prec_Scan_120_Port, &QLineEdit::textChanged, this, [=](QString port) {c_Variable::g_Communicate_DB.insert("Prec_Scan_120_Port", port.toInt()); });
	QObject::connect(ui->Prec_Scan_121_Port, &QLineEdit::textChanged, this, [=](QString port) {c_Variable::g_Communicate_DB.insert("Prec_Scan_121_Port", port.toInt()); });
	QObject::connect(ui->Fast_Scan_Port, &QLineEdit::textChanged, this, [=](QString port) {c_Variable::g_Communicate_DB.insert("Fast_Scan_Port", port.toInt()); });
	QObject::connect(ui->Jaka_120_Ip, &QLineEdit::textChanged, this, [=](QString ip) {c_Variable::g_Communicate_DB.insert("Jaka_120_Ip", ip); });
	QObject::connect(ui->Jaka_121_Ip, &QLineEdit::textChanged, this, [=](QString ip) {c_Variable::g_Communicate_DB.insert("Jaka_121_Ip", ip); });
	QObject::connect(ui->Jaka_Remote_Port, &QLineEdit::textChanged, this, [=](QString port) {c_Variable::g_Communicate_DB.insert("Jaka_Remote_Port", port.toInt()); });
	QObject::connect(ui->Jaka_Monitor_Port, &QLineEdit::textChanged, this, [=](QString port) {c_Variable::g_Communicate_DB.insert("Jaka_Monitor_Port", port.toInt()); });
	QObject::connect(ui->RGV_Ip, &QLineEdit::textChanged, this, [=](QString ip) {c_Variable::g_Communicate_DB.insert("RGV_Ip", ip); });
	QObject::connect(ui->RGV_Port, &QLineEdit::textChanged, this, [=](QString port) {c_Variable::g_Communicate_DB.insert("RGV_Port", port.toInt()); });
	QObject::connect(ui->Hypersen_30_Ip, &QLineEdit::textChanged, this, [=](QString ip) {c_Variable::g_Communicate_DB.insert("Hypersen_30_Ip", ip); });
	QObject::connect(ui->Hypersen_30_Id, &QLineEdit::textChanged, this, [=](QString id) {c_Variable::g_Communicate_DB.insert("Hypersen_30_Id", id.toInt()); });
	QObject::connect(ui->Hypersen_30_Port, &QLineEdit::textChanged, this, [=](QString port) {c_Variable::g_Communicate_DB.insert("Hypersen_30_Port", port.toInt()); });
	QObject::connect(ui->Hypersen_31_Ip, &QLineEdit::textChanged, this, [=](QString ip) {c_Variable::g_Communicate_DB.insert("Hypersen_31_Ip", ip); });
	QObject::connect(ui->Hypersen_31_Id, &QLineEdit::textChanged, this, [=](QString id) {c_Variable::g_Communicate_DB.insert("Hypersen_31_Id", id.toInt()); });
	QObject::connect(ui->Hypersen_31_Port, &QLineEdit::textChanged, this, [=](QString port) {c_Variable::g_Communicate_DB.insert("Hypersen_31_Port", port.toInt()); });
	QObject::connect(ui->Meijidenki_20_Ip, &QLineEdit::textChanged, this, [=](QString ip) {c_Variable::g_Communicate_DB.insert("Meijidenki_20_Ip", ip); });
	QObject::connect(ui->Meijidenki_20_Id, &QLineEdit::textChanged, this, [=](QString id) {c_Variable::g_Communicate_DB.insert("Meijidenki_20_Id", id.toInt()); });
	QObject::connect(ui->Meijidenki_20_Port, &QLineEdit::textChanged, this, [=](QString port) {c_Variable::g_Communicate_DB.insert("Meijidenki_20_Port", port.toInt()); });
	QObject::connect(ui->Meijidenki_21_Ip, &QLineEdit::textChanged, this, [=](QString ip) {c_Variable::g_Communicate_DB.insert("Meijidenki_21_Ip", ip); });
	QObject::connect(ui->Meijidenki_21_Id, &QLineEdit::textChanged, this, [=](QString id) {c_Variable::g_Communicate_DB.insert("Meijidenki_21_Id", id.toInt()); });
	QObject::connect(ui->Meijidenki_21_Port, &QLineEdit::textChanged, this, [=](QString port) {c_Variable::g_Communicate_DB.insert("Meijidenki_21_Port", port.toInt()); });
	QObject::connect(ui->Web_Server_Ip, &QLineEdit::textChanged, this, [=](QString ip) {c_Variable::g_Communicate_DB.insert("Web_Server_Ip", ip); });
	QObject::connect(ui->Ai_Server_Ip, &QLineEdit::textChanged, this, [=](QString ip) {c_Variable::g_Communicate_DB.insert("Ai_Server_Ip", ip); });
	QObject::connect(ui->Local_Monitor_Port, &QLineEdit::textChanged, this, [=](QString port) {c_Variable::g_Communicate_DB.insert("Local_Monitor_Port", port.toInt()); });
	QObject::connect(ui->Local_Remote_Port, &QLineEdit::textChanged, this, [=](QString port) {c_Variable::g_Communicate_DB.insert("Local_Remote_Port", port.toInt()); });

	QObject::connect(ui->Right_Rise_number, &QLineEdit::textChanged, this, [=](QString num) {c_Variable::g_Communicate_DB.insert("Right_Rise_number", num.toInt()); });
	QObject::connect(ui->Left_Rise_number, &QLineEdit::textChanged, this, [=](QString num) {c_Variable::g_Communicate_DB.insert("Left_Rise_number", num.toInt()); });
	QObject::connect(ui->Movement_speed_2, &QLineEdit::textChanged, this, [=](QString num) {c_Variable::g_Communicate_DB.insert("Movement_speed_2", num.toInt()); });
	QObject::connect(ui->Intermittent_running_speed_2, &QLineEdit::textChanged, this, [=](QString num) {c_Variable::g_Communicate_DB.insert("Intermittent_running_speed_2", num.toInt()); });
	QObject::connect(ui->First_creep_speed_2, &QLineEdit::textChanged, this, [=](QString num) {c_Variable::g_Communicate_DB.insert("First_creep_speed_2", num.toInt()); });
	QObject::connect(ui->Second_creep_speed_2, &QLineEdit::textChanged, this, [=](QString num) {c_Variable::g_Communicate_DB.insert("Second_creep_speed_2", num.toInt()); });
	QObject::connect(ui->Acceleration_2, &QLineEdit::textChanged, this, [=](QString num) {c_Variable::g_Communicate_DB.insert("Acceleration_2", num.toInt()); });
	QObject::connect(ui->Deceleration_2, &QLineEdit::textChanged, this, [=](QString num) {c_Variable::g_Communicate_DB.insert("Deceleration_2", num.toInt()); });
	QObject::connect(ui->Left_reset_speed_2, &QLineEdit::textChanged, this, [=](QString num) {c_Variable::g_Communicate_DB.insert("Left_reset_speed_2", num.toInt()); });
	QObject::connect(ui->Left_creep_speed_2, &QLineEdit::textChanged, this, [=](QString num) {c_Variable::g_Communicate_DB.insert("Left_creep_speed_2", num.toInt()); });
	QObject::connect(ui->Left_manual_speed_2, &QLineEdit::textChanged, this, [=](QString num) {c_Variable::g_Communicate_DB.insert("Left_manual_speed_2", num.toInt()); });
	QObject::connect(ui->Left_lifting_speed_2, &QLineEdit::textChanged, this, [=](QString num) {c_Variable::g_Communicate_DB.insert("Left_lifting_speed_2", num.toInt()); });
	QObject::connect(ui->Left_door_speed_2, &QLineEdit::textChanged, this, [=](QString num) {c_Variable::g_Communicate_DB.insert("Left_door_speed_2", num.toInt()); });
	QObject::connect(ui->Middle_door_speed_2, &QLineEdit::textChanged, this, [=](QString num) {c_Variable::g_Communicate_DB.insert("Middle_door_speed_2", num.toInt()); });
	QObject::connect(ui->Right_door_speed_2, &QLineEdit::textChanged, this, [=](QString num) {c_Variable::g_Communicate_DB.insert("Right_door_speed_2", num.toInt()); });
	QObject::connect(ui->Right_reset_speed_2, &QLineEdit::textChanged, this, [=](QString num) {c_Variable::g_Communicate_DB.insert("Right_reset_speed_2", num.toInt()); });
	QObject::connect(ui->Right_creep_speed_2, &QLineEdit::textChanged, this, [=](QString num) {c_Variable::g_Communicate_DB.insert("Right_creep_speed_2", num.toInt()); });
	QObject::connect(ui->Right_manual_speed_2, &QLineEdit::textChanged, this, [=](QString num) {c_Variable::g_Communicate_DB.insert("Right_manual_speed_2", num.toInt()); });
	QObject::connect(ui->Right_lifting_speed_2, &QLineEdit::textChanged, this, [=](QString num) {c_Variable::g_Communicate_DB.insert("Right_lifting_speed_2", num.toInt()); });
	QObject::connect(ui->Underbody_detection_distance_2, &QLineEdit::textChanged, this, [=](QString num) {c_Variable::g_Communicate_DB.insert("Underbody_detection_distance_2", num.toInt()); });
	QObject::connect(ui->Underbody_detection_distance_delay_2, &QLineEdit::textChanged, this, [=](QString num) {c_Variable::g_Communicate_DB.insert("Underbody_detection_distance_delay_2", num.toInt()); });
	QObject::connect(ui->Trailer_wheel_distance_2, &QLineEdit::textChanged, this, [=](QString num) {c_Variable::g_Communicate_DB.insert("Trailer_wheel_distance_2", num.toInt()); });
	QObject::connect(ui->Trailer_wheel_error_2, &QLineEdit::textChanged, this, [=](QString num) {c_Variable::g_Communicate_DB.insert("Trailer_wheel_error_2", num.toInt()); });
	QObject::connect(ui->Trailer_axle_distance_2, &QLineEdit::textChanged, this, [=](QString num) {c_Variable::g_Communicate_DB.insert("Trailer_axle_distance_2", num.toInt()); });
	QObject::connect(ui->Trailer_axle_error_2, &QLineEdit::textChanged, this, [=](QString num) {c_Variable::g_Communicate_DB.insert("Trailer_axle_error_2", num.toInt()); });
	QObject::connect(ui->Motor_wheel_distance_2, &QLineEdit::textChanged, this, [=](QString num) {c_Variable::g_Communicate_DB.insert("Motor_wheel_distance_2", num.toInt()); });
	QObject::connect(ui->Motor_wheel_distance_error_2, &QLineEdit::textChanged, this, [=](QString num) {c_Variable::g_Communicate_DB.insert("Motor_wheel_distance_error_2", num.toInt()); });
	QObject::connect(ui->Motor_axle_distance_2, &QLineEdit::textChanged, this, [=](QString num) {c_Variable::g_Communicate_DB.insert("Motor_axle_distance_2", num.toInt()); });
	QObject::connect(ui->Motor_axle_error_2, &QLineEdit::textChanged, this, [=](QString num) {c_Variable::g_Communicate_DB.insert("Motor_axle_error_2", num.toInt()); });

	QObject::connect(ui->Write_Coils_Size, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int Write_Coils_Size) {c_Variable::g_Communicate_DB.insert("Write_Coils_Size", Write_Coils_Size); });
	QObject::connect(ui->Read_DiscreteInputs_Size, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int Read_DiscreteInputs_Size) {c_Variable::g_Communicate_DB.insert("Read_DiscreteInputs_Size", Read_DiscreteInputs_Size); });
	QObject::connect(ui->Read_InputRegisters_Size, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int Read_InputRegisters_Size) {c_Variable::g_Communicate_DB.insert("Read_InputRegisters_Size", Read_InputRegisters_Size); });
	QObject::connect(ui->Write_HoldingRegisters_Size, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int Write_HoldingRegisters_Size) {c_Variable::g_Communicate_DB.insert("Write_HoldingRegisters_Size", Write_HoldingRegisters_Size); });

	QObject::connect(ui->Write_Coils_Addr, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int Write_Coils_Addr) {c_Variable::g_Communicate_DB.insert("Write_Coils_Addr", Write_Coils_Addr); });
	QObject::connect(ui->Read_DiscreteInputs_Addr, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int Read_DiscreteInputs_Addr) {c_Variable::g_Communicate_DB.insert("Read_DiscreteInputs_Addr", Read_DiscreteInputs_Addr); });
	QObject::connect(ui->Read_InputRegisters_Addr, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int Read_InputRegisters_Addr) {c_Variable::g_Communicate_DB.insert("Read_InputRegisters_Addr", Read_InputRegisters_Addr); });
	QObject::connect(ui->Write_HoldingRegisters_Addr, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int Write_HoldingRegisters_Addr) {c_Variable::g_Communicate_DB.insert("Write_HoldingRegisters_Addr", Write_HoldingRegisters_Addr); });
	/*************************************************************************************************************************************************
	**Function:更新程序列表
	*************************************************************************************************************************************************/
	ui->Teach_Complete->clicked();
}
/*************************************************************************************************************************************************
**Function:析构函数
*************************************************************************************************************************************************/
c_Robot_App_Widget::~c_Robot_App_Widget() {
	//处理系统参数
	delete m_Variable;
	//线程中断
	m_System_Time_Thread->requestInterruption();
	m_State_DB_Thread->requestInterruption();
	m_Local_Remote_Thread->requestInterruption();
	m_Local_Monitor_Thread->requestInterruption();
	m_Scan_Remote_Thread->requestInterruption();
	m_RGV_Remote_Thread->requestInterruption();
	m_Jaka_120_Monitor_Thread->requestInterruption();
	m_Jaka_121_Monitor_Thread->requestInterruption();
	m_Jaka_120_Remote_Thread->requestInterruption();
	m_Jaka_121_Remote_Thread->requestInterruption();
	m_Hypersen_30_Remote_Thread->requestInterruption();
	m_Hypersen_31_Remote_Thread->requestInterruption();
	m_Meijidenki_20_Remote_Thread->requestInterruption();
	m_Meijidenki_21_Remote_Thread->requestInterruption();
	//线程退出
	m_System_Time_Thread->quit();
	m_State_DB_Thread->quit();
	m_Local_Remote_Thread->quit();
	m_Local_Monitor_Thread->quit();
	m_RGV_Remote_Thread->quit();
	m_Scan_Remote_Thread->quit();
	m_Jaka_120_Monitor_Thread->quit();
	m_Jaka_121_Monitor_Thread->quit();
	m_Jaka_120_Remote_Thread->quit();
	m_Jaka_121_Remote_Thread->quit();
	m_Hypersen_30_Remote_Thread->quit();
	m_Hypersen_31_Remote_Thread->quit();
	m_Meijidenki_20_Remote_Thread->quit();
	m_Meijidenki_21_Remote_Thread->quit();
	//线程等待
	m_System_Time_Thread->wait();
	m_State_DB_Thread->wait();
	m_Local_Remote_Thread->wait();
	m_Local_Monitor_Thread->wait();
	m_Scan_Remote_Thread->wait();
	m_RGV_Remote_Thread->wait();
	m_Jaka_120_Monitor_Thread->wait();
	m_Jaka_121_Monitor_Thread->wait();
	m_Jaka_120_Remote_Thread->wait();
	m_Jaka_121_Remote_Thread->wait();
	m_Hypersen_30_Remote_Thread->wait();
	m_Hypersen_31_Remote_Thread->wait();
	m_Meijidenki_20_Remote_Thread->wait();
	m_Meijidenki_21_Remote_Thread->wait();
	//删除对象
	delete m_System_Time;
	delete m_State_DB;
	delete m_Local_Remote;
	delete m_Local_Monitor;
	delete m_RGV_Remote;
	delete m_Scan_Remote;
	delete m_Jaka_120_Monitor;
	delete m_Jaka_121_Monitor;
	delete m_Jaka_120_Remote;
	delete m_Jaka_121_Remote;
	delete m_Hypersen_30_Remote;
	delete m_Hypersen_31_Remote;
	delete m_Meijidenki_20_Remote;
	delete m_Meijidenki_21_Remote;
	//删除界面
	delete ui;
}
/*************************************************************************************************************************************************
**Function:系统状态扫描
*************************************************************************************************************************************************/
void c_Robot_App_Widget::System_Scan(QJsonObject db)
{
	//获取时间
	m_Current_Time = db.value("System_Time").toString();
	//获取状态信息
	m_RGV_State = db.value("RGV_State").toObject();//更新
	m_Jaka_120_Remote_State = db.value("Jaka_120_Remote_State").toObject();//更新
	m_Jaka_121_Remote_State = db.value("Jaka_121_Remote_State").toObject();//更新
	m_Jaka_120_Monitor_State = db.value("Jaka_120_Monitor_State").toObject();//更新
	m_Jaka_121_Monitor_State = db.value("Jaka_121_Monitor_State").toObject();//更新
	m_Hypersen_30_State = db.value("Hypersen_30_State").toObject();//更新
	m_Hypersen_31_State = db.value("Hypersen_31_State").toObject();//更新
	m_Meijidenki_20_State = db.value("Meijidenki_20_State").toObject();//更新
	m_Meijidenki_21_State = db.value("Meijidenki_21_State").toObject();//更新
	m_Fast_Scan_State = db.value("Fast_Scan_State").toObject();//更新
	m_Prec_Scan_120_State = db.value("Prec_Scan_120_State").toObject();//更新
	m_Prec_Scan_121_State = db.value("Prec_Scan_121_State").toObject();//更新
	m_Local_Remote_State = db.value("Local_Remote_State").toObject();//更新
	m_Local_Monitor_State = db.value("Local_Monitor_State").toObject();//更新
	ui->Status_Bar->showMessage("系统时间：" + m_Current_Time);//更新系统时间
	/*************************************************************************************************************************************************
	**Function:更新RGV状态显示
	*************************************************************************************************************************************************/
	if (m_RGV_State.value("Connected").toBool())
	{
		m_json = m_RGV_State.value("DB").toObject();
		m_DiscreteInputs = m_json.value("DiscreteInputs").toObject();
		m_InputRegisters = m_json.value("InputRegisters").toObject();
		qDebug() << m_InputRegisters;
		//主动力通信状态
		if (m_InputRegisters.value(QString::number(ACTIVEPOWERCOMMUNICATIONSTATUS)).toInt() == 0) {
			ui->RGV_State_1->setText("正常");
		}
		if (m_InputRegisters.value(QString::number(ACTIVEPOWERCOMMUNICATIONSTATUS)).toInt() != 0) {
			ui->RGV_State_1->setText("异常");
		}
		//主动力电流反馈
		ui->RGV_State_3->setText(QString::number(m_InputRegisters.value(QString::number(ACTIVEFORCECURRENTFEEDBACK)).toDouble() / 10) + "A");
		//主动力故障信号
		if (m_InputRegisters.value(QString::number(MAINPOWERFAILURESIGNAL)).toInt() == 0) {
			ui->RGV_State_4->setText("正常");
		}
		if (m_InputRegisters.value(QString::number(MAINPOWERFAILURESIGNAL)).toInt() != 0) {
			ui->RGV_State_4->setText("异常");
		}
		//主动力状态信号
		if (m_InputRegisters.value(QString::number(ACTIVEPOWERSTATUSSIGNAL)).toInt() == 0) {
			ui->RGV_State_5->setText("正常");
		}
		if (m_InputRegisters.value(QString::number(ACTIVEPOWERSTATUSSIGNAL)).toInt() != 0) {
			ui->RGV_State_5->setText("异常");
		}
		//主动力电压
		ui->RGV_State_6->setText(QString::number(m_InputRegisters.value(QString::number(MAINFORCEVOLTAGE)).toInt()) + "V");
		//主动力温度
		ui->RGV_State_7->setText(QString::number(m_InputRegisters.value(QString::number(MAINFORCETEMPERATURE)).toInt()) + "°C");
		//中轮对距离1
		ui->RGV_State_8->setText(QString::number(m_InputRegisters.value(QString::number(MIDDLEWHEELSETDISTANCE1)).toDouble()));
		//中轮对距离2
		ui->RGV_State_10->setText(QString::number(m_InputRegisters.value(QString::number(MIDDLEWHEELSETDISTANCE2)).toDouble()));
		//车底板距离
		ui->RGV_State_11->setText(QString::number(m_InputRegisters.value(QString::number(FLOORDISTANCE)).toDouble()));
		//
	}
	/*************************************************************************************************************************************************
	**Function:更新机械臂120状态显示
	*************************************************************************************************************************************************/
	if (m_Jaka_120_Monitor_State.value("Connected").toBool())
	{
		m_json = m_Jaka_120_Monitor_State.value("DB").toObject();
		//机器人关节角度
		m_joint_actual_position = m_json.value("joint_actual_position").toArray();
		ui->Jaka_120_joint_1->setText(QString::number(m_joint_actual_position.at(0).toDouble()));
		ui->Jaka_120_joint_2->setText(QString::number(m_joint_actual_position.at(1).toDouble()));
		ui->Jaka_120_joint_3->setText(QString::number(m_joint_actual_position.at(2).toDouble()));
		ui->Jaka_120_joint_4->setText(QString::number(m_joint_actual_position.at(3).toDouble()));
		ui->Jaka_120_joint_5->setText(QString::number(m_joint_actual_position.at(4).toDouble()));
		ui->Jaka_120_joint_6->setText(QString::number(m_joint_actual_position.at(5).toDouble()));
		//机器人 tcp 的位姿
		m_actual_position = m_json.value("actual_position").toArray();
		ui->Jaka_120_TCP_x->setText(QString::number(m_actual_position.at(0).toDouble()));
		ui->Jaka_120_TCP_y->setText(QString::number(m_actual_position.at(1).toDouble()));
		ui->Jaka_120_TCP_z->setText(QString::number(m_actual_position.at(2).toDouble()));
		ui->Jaka_120_TCP_a->setText(QString::number(m_actual_position.at(3).toDouble()));
		ui->Jaka_120_TCP_b->setText(QString::number(m_actual_position.at(4).toDouble()));
		ui->Jaka_120_TCP_c->setText(QString::number(m_actual_position.at(5).toDouble()));
		//1 代表机器人下电 2 代表机器人上电 3 代表机器人下使能 4 代表机器人上使能
		m_task_state = m_json.value("task_state").toInt();
		switch (m_task_state)
		{
		case 1:
			ui->Jaka_120_task_state->setText("下电");
			break;
		case 2:
			ui->Jaka_120_task_state->setText("上电");
			break;
		case 3:
			ui->Jaka_120_task_state->setText("下使能");
			break;
		case 4:
			ui->Jaka_120_task_state->setText("上使能");
			break;
		default:
			ui->Jaka_120_task_state->setText("未连接");
			break;
		}
		//机器人被设置的 home 点位
		m_homed = m_json.value("homed").toArray();
		ui->Jaka_120_home_x->setText(QString::number(m_homed.at(0).toDouble()));
		ui->Jaka_120_home_y->setText(QString::number(m_homed.at(1).toDouble()));
		ui->Jaka_120_home_z->setText(QString::number(m_homed.at(2).toDouble()));
		ui->Jaka_120_home_a->setText(QString::number(m_homed.at(3).toDouble()));
		ui->Jaka_120_home_b->setText(QString::number(m_homed.at(4).toDouble()));
		ui->Jaka_120_home_c->setText(QString::number(m_homed.at(5).toDouble()));
		//机器人的任务模式 1 代表手动模式 2 代表自动模式 3 代表 MDI(面板操作)模式 4 代表拖拽模式
		m_task_mode = m_json.value("task_mode").toInt();
		switch (m_task_mode)
		{
		case 1:
			ui->Jaka_120_task_mode->setText("手动");
			break;
		case 2:
			ui->Jaka_120_task_mode->setText("自动");
			break;
		case 3:
			ui->Jaka_120_task_mode->setText("面板操作");
			break;
		case 4:
			ui->Jaka_120_task_mode->setText("拖拽");
			break;
		default:
			ui->Jaka_120_task_mode->setText("未连接");
			break;
		}
		//程序运行状态 0 代表空闲 1 代表正在加载 2 代表暂停 3 代表正在运行
		m_interp_state = m_json.value("interp_state").toInt();
		switch (m_interp_state)
		{
		case 0:
			ui->Jaka_120_interp_state->setText("空闲");
			break;
		case 1:
			ui->Jaka_120_interp_state->setText("正在加载");
			break;
		case 2:
			ui->Jaka_120_interp_state->setText("暂停");
			break;
		case 3:
			ui->Jaka_120_interp_state->setText("正在运行");
			break;
		default:
			ui->Jaka_120_interp_state->setText("未连接");
			break;
		}
		//机器人当前使用的工具 ID
		m_current_tool_id = m_json.value("current_tool_id").toInt();
		ui->Jaka_120_current_tool_id->setText(QString::number(m_current_tool_id));
		//值为 1 时代表机器人正处于急停状态
		m_protective_stop = m_json.value("protective_stop").toInt();
		ui->Jaka_120_protective_stop->setText(QString::number(m_protective_stop));
		//值为 1 时代表机器人正处于关节软限位
		m_on_soft_limit = m_json.value("on_soft_limit").toInt();
		ui->Jaka_120_on_soft_limit->setText(QString::number(m_on_soft_limit));
		//值为 1 时代表机器人正处于代表急停状态
		m_emergency_stop = m_json.value("emergency_stop").toInt();
		ui->Jaka_120_emergency_stop->setText(QString::number(m_emergency_stop));
		//值为 1 时代表机器人接近拖拽的极限位置
		m_drag_near_limit = m_json.value("drag_near_limit").toArray();
		ui->Jaka_120_drag_near_limit_1->setText(QString::number(m_drag_near_limit.at(0).toDouble()));
		ui->Jaka_120_drag_near_limit_2->setText(QString::number(m_drag_near_limit.at(1).toDouble()));
		ui->Jaka_120_drag_near_limit_3->setText(QString::number(m_drag_near_limit.at(2).toDouble()));
		ui->Jaka_120_drag_near_limit_4->setText(QString::number(m_drag_near_limit.at(3).toDouble()));
		ui->Jaka_120_drag_near_limit_5->setText(QString::number(m_drag_near_limit.at(4).toDouble()));
		ui->Jaka_120_drag_near_limit_6->setText(QString::number(m_drag_near_limit.at(5).toDouble()));
	}
	/*************************************************************************************************************************************************
	**Function:更新机械臂121状态显示
	*************************************************************************************************************************************************/
	if (m_Jaka_121_Monitor_State.value("Connected").toBool())
	{
		m_json = m_Jaka_121_Monitor_State.value("DB").toObject();
		//机器人关节角度
		m_joint_actual_position = m_json.value("joint_actual_position").toArray();
		ui->Jaka_121_joint_1->setText(QString::number(m_joint_actual_position.at(0).toDouble()));
		ui->Jaka_121_joint_2->setText(QString::number(m_joint_actual_position.at(1).toDouble()));
		ui->Jaka_121_joint_3->setText(QString::number(m_joint_actual_position.at(2).toDouble()));
		ui->Jaka_121_joint_4->setText(QString::number(m_joint_actual_position.at(3).toDouble()));
		ui->Jaka_121_joint_5->setText(QString::number(m_joint_actual_position.at(4).toDouble()));
		ui->Jaka_121_joint_6->setText(QString::number(m_joint_actual_position.at(5).toDouble()));
		//机器人 tcp 的位姿
		m_actual_position = m_json.value("actual_position").toArray();
		ui->Jaka_121_TCP_x->setText(QString::number(m_actual_position.at(0).toDouble()));
		ui->Jaka_121_TCP_y->setText(QString::number(m_actual_position.at(1).toDouble()));
		ui->Jaka_121_TCP_z->setText(QString::number(m_actual_position.at(2).toDouble()));
		ui->Jaka_121_TCP_a->setText(QString::number(m_actual_position.at(3).toDouble()));
		ui->Jaka_121_TCP_b->setText(QString::number(m_actual_position.at(4).toDouble()));
		ui->Jaka_121_TCP_c->setText(QString::number(m_actual_position.at(5).toDouble()));
		//1 代表机器人下电 2 代表机器人上电 3 代表机器人下使能 4 代表机器人上使能
		m_task_state = m_json.value("task_state").toInt();
		switch (m_task_state)
		{
		case 1:
			ui->Jaka_121_task_state->setText("下电");
			break;
		case 2:
			ui->Jaka_121_task_state->setText("上电");
			break;
		case 3:
			ui->Jaka_121_task_state->setText("下使能");
			break;
		case 4:
			ui->Jaka_121_task_state->setText("上使能");
			break;
		default:
			ui->Jaka_121_task_state->setText("未连接");
			break;
		}
		//机器人被设置的 home 点位
		m_homed = m_json.value("homed").toArray();
		ui->Jaka_121_home_x->setText(QString::number(m_homed.at(0).toDouble()));
		ui->Jaka_121_home_y->setText(QString::number(m_homed.at(1).toDouble()));
		ui->Jaka_121_home_z->setText(QString::number(m_homed.at(2).toDouble()));
		ui->Jaka_121_home_a->setText(QString::number(m_homed.at(3).toDouble()));
		ui->Jaka_121_home_b->setText(QString::number(m_homed.at(4).toDouble()));
		ui->Jaka_121_home_c->setText(QString::number(m_homed.at(5).toDouble()));
		//机器人的任务模式 1 代表手动模式 2 代表自动模式 3 代表 MDI(面板操作)模式 4 代表拖拽模式
		m_task_mode = m_json.value("task_mode").toInt();
		switch (m_task_mode)
		{
		case 1:
			ui->Jaka_121_task_mode->setText("手动");
			break;
		case 2:
			ui->Jaka_121_task_mode->setText("自动");
			break;
		case 3:
			ui->Jaka_121_task_mode->setText("面板操作");
			break;
		case 4:
			ui->Jaka_121_task_mode->setText("拖拽");
			break;
		default:
			ui->Jaka_121_task_mode->setText("未连接");
			break;
		}
		//程序运行状态 0 代表空闲 1 代表正在加载 2 代表暂停 3 代表正在运行
		m_interp_state = m_json.value("interp_state").toInt();
		switch (m_interp_state)
		{
		case 0:
			ui->Jaka_121_interp_state->setText("空闲");
			break;
		case 1:
			ui->Jaka_121_interp_state->setText("正在加载");
			break;
		case 2:
			ui->Jaka_121_interp_state->setText("暂停");
			break;
		case 3:
			ui->Jaka_121_interp_state->setText("正在运行");
			break;
		default:
			ui->Jaka_121_interp_state->setText("未连接");
			break;
		}
		//机器人当前使用的工具 ID
		m_current_tool_id = m_json.value("m_current_tool_id").toInt();
		ui->Jaka_121_current_tool_id->setText(QString::number(m_current_tool_id));
		//值为 1 时代表机器人正处于急停状态
		m_protective_stop = m_json.value("protective_stop").toInt();
		ui->Jaka_121_protective_stop->setText(QString::number(m_protective_stop));
		//值为 1 时代表机器人正处于关节软限位
		m_on_soft_limit = m_json.value("on_soft_limit").toInt();
		ui->Jaka_121_on_soft_limit->setText(QString::number(m_on_soft_limit));
		//值为 1 时代表机器人正处于代表急停状态
		m_emergency_stop = m_json.value("emergency_stop").toInt();
		ui->Jaka_121_emergency_stop->setText(QString::number(m_emergency_stop));
		//值为 1 时代表机器人接近拖拽的极限位置
		m_drag_near_limit = m_json.value("drag_near_limit").toArray();
		ui->Jaka_121_drag_near_limit_1->setText(QString::number(m_drag_near_limit.at(0).toDouble()));
		ui->Jaka_121_drag_near_limit_2->setText(QString::number(m_drag_near_limit.at(1).toDouble()));
		ui->Jaka_121_drag_near_limit_3->setText(QString::number(m_drag_near_limit.at(2).toDouble()));
		ui->Jaka_121_drag_near_limit_4->setText(QString::number(m_drag_near_limit.at(3).toDouble()));
		ui->Jaka_121_drag_near_limit_5->setText(QString::number(m_drag_near_limit.at(4).toDouble()));
		ui->Jaka_121_drag_near_limit_6->setText(QString::number(m_drag_near_limit.at(5).toDouble()));
	}
	/*************************************************************************************************************************************************
	**Function:更新线阵雷达状态显示
	*************************************************************************************************************************************************/
	if (m_Meijidenki_20_State.value("Connected").toBool())
	{
		m_json = m_Meijidenki_20_State.value("DB").toObject();
		m_value = m_json.value("LIM_CODE_LDBCONFIG").toObject();

		m_nMR = m_value.value("nMR").toInt();// 量程
		m_nESAR = m_value.value("nESAR").toInt();// 设备角度范围
		m_nESA0 = m_value.value("nESA0").toInt();// 设备角度起始角
		m_nESA1 = m_value.value("nESA1").toInt();// 设备角度终止角
		m_nSAR = m_value.value("nSAR").toInt();// 有效角度范围
		m_nSA0 = m_value.value("nSA0").toInt();// 有效角度起始角
		m_nSA1 = m_value.value("nSA1").toInt();// 有效角度终止角
		m_nSAV = m_value.value("nSAV").toInt();// 扫描角速度（度/秒）
		m_nSAP = m_value.value("nSAP").toDouble();// 扫描角度分辨率
		m_nPF = m_value.value("nPF").toInt();// 测量频率(HZ)

		ui->ESAR_20->setText(QString::number(m_nESAR));//设备角度范围
		ui->MR_20->setText(QString::number(m_nESAR));//量程
		ui->ESA_20->setText(QString("(%1，%2)").arg(m_nESA0).arg(m_nESA1));//设备角度起始终止角
		ui->SAV_20->setText(QString::number(m_nSAV));//扫描角速度
		ui->SAR_20->setText(QString::number(m_nSAR));//有效角度范围
		ui->PF_20->setText(QString::number(m_nPF));//测量频率(HZ)
		ui->SA_20->setText(QString("(%1，%2)").arg(m_nSA0).arg(m_nSA1));//有效角度起始终止角
		ui->SAP_20->setText(QString::number(m_nSAP));//扫描角度分辨率

		m_value = m_json.value("LIM_CODE_LMD").toObject();
		m_nRange = m_value.value("nRange").toDouble();// 设备量程.单位:cm
		m_nBAngle = m_value.value("nBAngle").toDouble();// 测量数据起始角度，可能为负值.单位:度
		m_nEAngle = m_value.value("nEAngle").toDouble();// 测量数据结束角度，可能为负值.单位:度
		m_nAnglePrecision = m_value.value("nAnglePrecision").toDouble();// 角度精度.单位：1/1000 度
		m_nRPM = m_value.value("nRPM").toDouble();// 扫描频率.单位：RPM (转/分钟)
		m_nMDataNum = m_value.value("nMDataNum").toDouble();//测量数据的个数，根据nBAngle、nEAngle和nAnglePrecision计算
		ui->nMDataNum_20->setText(QString::number(m_nMDataNum));
		m_distance = m_value.value("LMD_D").toArray();//测量距离数据.单位cm
		int i = ui->MDataNum_20->value();//当前点
		m_idistance = m_distance.at(i).toDouble();//模长
		m_iAngle = m_nBAngle + i * m_nAnglePrecision;//角度
		ui->LMD_20->setText(QString(" %1 °: %2 cm").arg(m_iAngle).arg(m_idistance));//极坐标
	}

	if (m_Meijidenki_21_State.value("Connected").toBool())
	{
		m_json = m_Meijidenki_21_State.value("DB").toObject();
		m_value = m_json.value("LIM_CODE_LDBCONFIG").toObject();

		m_nMR = m_value.value("nMR").toInt();// 量程
		m_nESAR = m_value.value("nESAR").toInt();// 设备角度范围
		m_nESA0 = m_value.value("nESA0").toInt();// 设备角度起始角
		m_nESA1 = m_value.value("nESA1").toInt();// 设备角度终止角
		m_nSAR = m_value.value("nSAR").toInt();// 有效角度范围
		m_nSA0 = m_value.value("nSA0").toInt();// 有效角度起始角
		m_nSA1 = m_value.value("nSA1").toInt();// 有效角度终止角
		m_nSAV = m_value.value("nSAV").toInt();// 扫描角速度（度/秒）
		m_nSAP = m_value.value("nSAP").toDouble();// 扫描角度分辨率
		m_nPF = m_value.value("nPF").toInt();// 测量频率(HZ)

		ui->ESAR_21->setText(QString::number(m_nESAR));//设备角度范围
		ui->MR_21->setText(QString::number(m_nESAR));//量程
		ui->ESA_21->setText(QString("(%1，%2)").arg(m_nESA0).arg(m_nESA1));//设备角度起始终止角
		ui->SAV_21->setText(QString::number(m_nSAV));//扫描角速度
		ui->SAR_21->setText(QString::number(m_nSAR));//有效角度范围
		ui->PF_21->setText(QString::number(m_nPF));//测量频率(HZ)
		ui->SA_21->setText(QString("(%1，%2)").arg(m_nSA0).arg(m_nSA1));//有效角度起始终止角
		ui->SAP_21->setText(QString::number(m_nSAP));//扫描角度分辨率

		m_value = m_json.value("LIM_CODE_LMD").toObject();
		m_nRange = m_value.value("nRange").toDouble();// 设备量程.单位:cm
		m_nBAngle = m_value.value("nBAngle").toDouble();// 测量数据起始角度，可能为负值.单位:1/1000度
		m_nEAngle = m_value.value("nEAngle").toDouble();// 测量数据结束角度，可能为负值.单位:1/1000度
		m_nAnglePrecision = m_value.value("nAnglePrecision").toDouble();// 角度精度.单位：1/1000 度
		m_nRPM = m_value.value("nRPM").toDouble();// 扫描频率.单位：RPM (转/分钟)
		m_nMDataNum = m_value.value("nMDataNum").toDouble();//测量数据的个数，根据nBAngle、nEAngle和nAnglePrecision计算
		ui->nMDataNum_21->setText(QString::number(m_nMDataNum));
		m_distance = m_value.value("LMD_D").toArray();//测量距离数据.单位cm
		int i = ui->MDataNum_21->value();//当前点
		m_idistance = m_distance.at(i).toDouble();//模长
		m_iAngle = m_nBAngle + i * m_nAnglePrecision;//角度
		ui->LMD_21->setText(QString(" %1 °: %2 cm").arg(m_iAngle).arg(m_idistance));//极坐标
	}
	/*************************************************************************************************************************************************
	**Function:更新面阵雷达状态显示
	*************************************************************************************************************************************************/
	if (m_Hypersen_30_State.value("Connected").toBool())
	{
		m_json = m_Hypersen_30_State.value("DB").toObject();
		m_Array = m_json.value("0").toArray();

		m_roi_aver_distance = m_Array.at(0).toInt();
		ui->roi_aver_distance_30_0->setText(QString::number(m_roi_aver_distance));//ROI_0平均距离
		m_roi_max_distance = m_Array.at(1).toInt();
		ui->roi_max_distance_30_0->setText(QString::number(m_roi_max_distance));//ROI_0最大距离
		m_roi_min_distance = m_Array.at(2).toInt();
		ui->roi_min_distance_30_0->setText(QString::number(m_roi_min_distance));//ROI_0最小距离
		m_roi_valid_aver_amp = m_Array.at(3).toInt();
		ui->roi_valid_aver_amp_30_0->setText(QString::number(m_roi_valid_aver_amp));//ROI_0有效幅值
		m_roi_all_aver_amp = m_Array.at(4).toInt();
		ui->roi_all_aver_amp_30_0->setText(QString::number(m_roi_all_aver_amp));//ROI_0平均幅值

		m_Array = m_json.value("1").toArray();

		m_roi_aver_distance = m_Array.at(0).toInt();
		ui->roi_aver_distance_30_1->setText(QString::number(m_roi_aver_distance));//ROI_1平均距离
		m_roi_max_distance = m_Array.at(1).toInt();
		ui->roi_max_distance_30_1->setText(QString::number(m_roi_max_distance));//ROI_1最大距离
		m_roi_min_distance = m_Array.at(2).toInt();
		ui->roi_min_distance_30_1->setText(QString::number(m_roi_min_distance));//ROI_1最小距离
		m_roi_valid_aver_amp = m_Array.at(3).toInt();
		ui->roi_valid_aver_amp_30_1->setText(QString::number(m_roi_valid_aver_amp));//ROI_1有效幅值
		m_roi_all_aver_amp = m_Array.at(4).toInt();
		ui->roi_all_aver_amp_30_1->setText(QString::number(m_roi_all_aver_amp));//ROI_1平均幅值
	}

	if (m_Hypersen_31_State.value("Connected").toBool())
	{
		m_json = m_Hypersen_31_State.value("DB").toObject();
		m_Array = m_json.value("0").toArray();

		m_roi_aver_distance = m_Array.at(0).toInt();
		ui->roi_aver_distance_31_0->setText(QString::number(m_roi_aver_distance));//ROI_0平均距离
		m_roi_max_distance = m_Array.at(1).toInt();
		ui->roi_max_distance_31_0->setText(QString::number(m_roi_max_distance));//ROI_0最大距离
		m_roi_min_distance = m_Array.at(2).toInt();
		ui->roi_min_distance_31_0->setText(QString::number(m_roi_min_distance));//ROI_0最小距离
		m_roi_valid_aver_amp = m_Array.at(3).toInt();
		ui->roi_valid_aver_amp_31_0->setText(QString::number(m_roi_valid_aver_amp));//ROI_0有效幅值
		m_roi_all_aver_amp = m_Array.at(4).toInt();
		ui->roi_all_aver_amp_31_0->setText(QString::number(m_roi_all_aver_amp));//ROI_0平均幅值

		m_Array = m_json.value("1").toArray();

		m_roi_aver_distance = m_Array.at(0).toInt();
		ui->roi_aver_distance_31_1->setText(QString::number(m_roi_aver_distance));//ROI_1平均距离
		m_roi_max_distance = m_Array.at(1).toInt();
		ui->roi_max_distance_31_1->setText(QString::number(m_roi_max_distance));//ROI_1最大距离
		m_roi_min_distance = m_Array.at(2).toInt();
		ui->roi_min_distance_31_1->setText(QString::number(m_roi_min_distance));//ROI_1最小距离
		m_roi_valid_aver_amp = m_Array.at(3).toInt();
		ui->roi_valid_aver_amp_31_1->setText(QString::number(m_roi_valid_aver_amp));//ROI_1有效幅值
		m_roi_all_aver_amp = m_Array.at(4).toInt();
		ui->roi_all_aver_amp_31_1->setText(QString::number(m_roi_all_aver_amp));//ROI_1平均幅值
	}
}
/*************************************************************************************************************************************************
**Function:新建示教文件
*************************************************************************************************************************************************/
void c_Robot_App_Widget::on_Build_New_Date_clicked()
{
	QString Car_Name = ui->Car_Name->text();
	QString Car_Number = ui->Car_Number->text();
	QString Jaka_File_Name = QString("%1-%2%3").arg(m_Current_Time).arg(Car_Name).arg(Car_Number);
	ui->Robot_File_Name_2->setItemText(0, Jaka_File_Name);
	QFile file(QDir::currentPath() + "/Robot_Teach/" + Jaka_File_Name + ".json");
	//判断文件是否存在
	if (file.exists()) {
		ui->Worry_Message->addItem(m_Current_Time + "：文件已存在，可以编辑修改");
	}
	else {
		//存在打开，不存在创建
		file.open(QIODevice::ReadWrite | QIODevice::Text);
		ui->Worry_Message->addItem(m_Current_Time + "：开始创建记录，请输入车型号，并点击记录");
	}
	file.close();

	QJsonArray Position_Date;
	Position_Date.append("升降台位置");
	Position_Date.append("第一关节角");
	Position_Date.append("第二关节角");
	Position_Date.append("第三关节角");
	Position_Date.append("第四关节角");
	Position_Date.append("第五关节角");
	Position_Date.append("第六关节角");
	Position_Date.append("是否为巡检点");
	Position_Date.append("图片名称信息");

	QJsonArray Jaka_Date;
	Jaka_Date.append(Position_Date);

	QJsonObject Axis_Jaka_Date;
	Axis_Jaka_Date.insert("Jaka_120", Jaka_Date);
	Axis_Jaka_Date.insert("Jaka_121", Jaka_Date);

	QJsonObject Car_Axis_Jaka_Date;
	Car_Axis_Jaka_Date.insert("1", Axis_Jaka_Date);
	Car_Axis_Jaka_Date.insert("2", Axis_Jaka_Date);

	QJsonObject Program_Date;
	Program_Date.insert("A", Car_Axis_Jaka_Date);
	Program_Date.insert("B", Car_Axis_Jaka_Date);

	Program_Date.insert("Program_Name", Jaka_File_Name);

	Write_Robot_Teach(Jaka_File_Name, Program_Date);
	ui->Worry_Message->addItem(m_Current_Time + "-成功创建新数据：" + Jaka_File_Name);
	ui->Load_Robot_Teaching->clicked();
}
/*************************************************************************************************************************************************
**Function:示教完成
*************************************************************************************************************************************************/
void c_Robot_App_Widget::on_Teach_Complete_clicked()
{
	QFile Program_Inf(QDir::currentPath() + "/Jaka_App/Program_Inf.txt");
	Program_Inf.open(QFile::ReadOnly | QIODevice::Text);
	QString Current_File_Name = Program_Inf.readAll();
	Program_Inf.close();
	ui->Robot_File_Name->clear();
	//添加新项
	ui->Robot_File_Name->addItem(Current_File_Name, "文件名");

	ui->Robot_File_Name_2->clear();
	//添加新项
	ui->Robot_File_Name_2->addItem("请创建或选择项目", "文件名");
	//文件存放路径
	QDir folder(QDir::currentPath() + "/Robot_Teach");
	//查看路径中后缀为.json格式的文件
	QStringList files;
	files << QString("*.json");
	folder.setFilter(QDir::Files | QDir::NoSymLinks); //设置类型过滤器，只为文件格式
	folder.setNameFilters(files);  //设置文件名称过滤器，只为filters格式
								   //统计cfg格式的文件个数
	int folder_count = static_cast<int>(folder.count());
	//存储文件名称
	for (int i = 0; i<folder_count; i++)
	{
		QString file = folder[i].split(".", QString::SkipEmptyParts).at(0);
		//添加新项
		ui->Robot_File_Name->addItem("", "文件名");
		//在项中添加文件名
		ui->Robot_File_Name->setItemText(i + 1, file);
		//添加新项
		ui->Robot_File_Name_2->addItem("", "文件名");
		//在项中添加文件名
		ui->Robot_File_Name_2->setItemText(i + 1, file);
	}
	ui->Worry_List->addItem(m_Current_Time + "巡检程序列表已刷新");
}
/*************************************************************************************************************************************************
**Function:读取示教文件
*************************************************************************************************************************************************/
QJsonObject c_Robot_App_Widget::Read_Robot_Teach(QString Jaka_File_Name)
{
	QFile file(QDir::currentPath() + "/Robot_Teach/" + Jaka_File_Name + ".json");
	file.open(QFile::ReadOnly | QIODevice::Text);
	QByteArray allData = file.readAll();
	file.close();

	QJsonDocument Jaka_Doc(QJsonDocument::fromJson(allData));
	QJsonObject Program_Date = Jaka_Doc.object();

	return Program_Date;
}
/*************************************************************************************************************************************************
**Function:写入示教文件
*************************************************************************************************************************************************/
void c_Robot_App_Widget::Write_Robot_Teach(QString Jaka_File_Name, QJsonObject Program_Date)
{
	//写入新的文件
	QFile file_new(QDir::currentPath() + "/Robot_Teach/" + Jaka_File_Name + ".json");
	file_new.open(QFile::WriteOnly | QIODevice::Text);
	QJsonDocument Jaka_doc;
	Jaka_doc.setObject(Program_Date);
	file_new.write(Jaka_doc.toJson());
	file_new.close();
}
/*************************************************************************************************************************************************
**Function:文件载入程序列表：A动车、B拖车；1 轴1、2 轴2
*************************************************************************************************************************************************/
void c_Robot_App_Widget::on_Load_Robot_Teaching_clicked()
{
	ui->Robot_Teaching_List->clear();

	QString Jaka_File_Name = ui->Robot_File_Name_2->currentText();
	QJsonObject Program_Date = Read_Robot_Teach(Jaka_File_Name);

	QString Program_Name = Program_Date.value("Program_Name").toString();

	QJsonArray Car_Number = Program_Date.value("Car_Number").toArray();
	QString Car_Number_Date = JsonArray_To_String(Car_Number);
	ui->Robot_Teaching_List->addItem(m_Current_Time + "-车箱组成：" + Car_Number_Date);

	QJsonObject Motor_Date = Program_Date.value("A").toObject();;
	QJsonObject Trailer_Date = Program_Date.value("B").toObject();

	QJsonObject Motor_Axis_1_Date = Motor_Date.value("1").toObject();
	QJsonObject Motor_Axis_2_Date = Motor_Date.value("2").toObject();
	QJsonObject Trailer_Axis_1_Date = Trailer_Date.value("1").toObject();;
	QJsonObject Trailer_Axis_2_Date = Trailer_Date.value("2").toObject();

	QJsonArray Motor_Axis_1_Jaka_120_Date = Motor_Axis_1_Date.value("Jaka_120").toArray();
	QJsonArray Motor_Axis_2_Jaka_120_Date = Motor_Axis_2_Date.value("Jaka_120").toArray();
	QJsonArray Trailer_Axis_1_Jaka_120_Date = Trailer_Axis_1_Date.value("Jaka_120").toArray();
	QJsonArray Trailer_Axis_2_Jaka_120_Date = Trailer_Axis_2_Date.value("Jaka_120").toArray();
	QJsonArray Motor_Axis_1_Jaka_121_Date = Motor_Axis_1_Date.value("Jaka_121").toArray();
	QJsonArray Motor_Axis_2_Jaka_121_Date = Motor_Axis_2_Date.value("Jaka_121").toArray();
	QJsonArray Trailer_Axis_1_Jaka_121_Date = Trailer_Axis_1_Date.value("Jaka_121").toArray();
	QJsonArray Trailer_Axis_2_Jaka_121_Date = Trailer_Axis_2_Date.value("Jaka_121").toArray();

	ui->Robot_Teaching_List->addItem(m_Current_Time + "-位置信息：动车->轴1->机械臂120：");
	for (int i = 0; i<Motor_Axis_1_Jaka_120_Date.size(); i++)
	{
		QJsonArray Point_Array = Motor_Axis_1_Jaka_120_Date.at(i).toArray();
		QString Point = JsonArray_To_String(Point_Array);
		ui->Robot_Teaching_List->addItem(m_Current_Time + "-机械臂120位置点：" + QString::number(i) + "：" + Point);
	}

	ui->Robot_Teaching_List->addItem(m_Current_Time + "-位置信息：动车->轴2->机械臂120：");
	for (int i = 0; i<Motor_Axis_2_Jaka_120_Date.size(); i++)
	{
		QJsonArray Point_Array = Motor_Axis_2_Jaka_120_Date.at(i).toArray();
		QString Point = JsonArray_To_String(Point_Array);
		ui->Robot_Teaching_List->addItem(m_Current_Time + "-机械臂120位置点：" + QString::number(i) + "：" + Point);
	}
	ui->Robot_Teaching_List->addItem(m_Current_Time + "-位置信息：拖车->轴1->机械臂120：");
	for (int i = 0; i<Trailer_Axis_1_Jaka_120_Date.size(); i++)
	{
		QJsonArray Point_Array = Trailer_Axis_1_Jaka_120_Date.at(i).toArray();
		QString Point = JsonArray_To_String(Point_Array);
		ui->Robot_Teaching_List->addItem(m_Current_Time + "-机械臂120位置点：" + QString::number(i) + "：" + Point);
	}
	ui->Robot_Teaching_List->addItem(m_Current_Time + "-位置信息：拖车->轴2->机械臂120：");
	for (int i = 0; i<Trailer_Axis_2_Jaka_120_Date.size(); i++)
	{
		QJsonArray Point_Array = Trailer_Axis_2_Jaka_120_Date.at(i).toArray();
		QString Point = JsonArray_To_String(Point_Array);
		ui->Robot_Teaching_List->addItem(m_Current_Time + "-机械臂120位置点：" + QString::number(i) + "：" + Point);
	}

	ui->Robot_Teaching_List->addItem(m_Current_Time + "-位置信息：动车->轴1->机械臂121：");
	for (int i = 0; i<Motor_Axis_1_Jaka_121_Date.size(); i++)
	{
		QJsonArray Point_Array = Motor_Axis_1_Jaka_121_Date.at(i).toArray();
		QString Point = JsonArray_To_String(Point_Array);
		ui->Robot_Teaching_List->addItem(m_Current_Time + "-机械臂121位置点：" + QString::number(i) + "：" + Point);
	}
	ui->Robot_Teaching_List->addItem(m_Current_Time + "-位置信息：动车->轴2->机械臂121：");
	for (int i = 0; i<Motor_Axis_2_Jaka_121_Date.size(); i++)
	{
		QJsonArray Point_Array = Motor_Axis_2_Jaka_121_Date.at(i).toArray();
		QString Point = JsonArray_To_String(Point_Array);
		ui->Robot_Teaching_List->addItem(m_Current_Time + "-机械臂121位置点：" + QString::number(i) + "：" + Point);
	}
	ui->Robot_Teaching_List->addItem(m_Current_Time + "-位置信息：拖车->轴1->机械臂121：");
	for (int i = 0; i<Trailer_Axis_1_Jaka_121_Date.size(); i++)
	{
		QJsonArray Point_Array = Trailer_Axis_1_Jaka_121_Date.at(i).toArray();
		QString Point = JsonArray_To_String(Point_Array);
		ui->Robot_Teaching_List->addItem(m_Current_Time + "-机械臂121位置点：" + QString::number(i) + "：" + Point);
	}
	ui->Robot_Teaching_List->addItem(m_Current_Time + "-位置信息：拖车->轴2->机械臂121：");
	for (int i = 0; i<Trailer_Axis_2_Jaka_121_Date.size(); i++)
	{
		QJsonArray Point_Array = Trailer_Axis_2_Jaka_121_Date.at(i).toArray();
		QString Point = JsonArray_To_String(Point_Array);
		ui->Robot_Teaching_List->addItem(m_Current_Time + "-机械臂121位置点：" + QString::number(i) + "：" + Point);
	}
	ui->Worry_Message->addItem(m_Current_Time + "-成功读取：" + Program_Name);
}
/*************************************************************************************************************************************************
**Function:删除记录
*************************************************************************************************************************************************/
void c_Robot_App_Widget::on_Delete_Task_clicked()
{
	QString Jaka_File_Name = ui->Robot_File_Name_2->currentText();
	QFile file(QDir::currentPath() + "/Robot_Teach/" + Jaka_File_Name + ".json");
	file.remove();
	ui->Worry_Message->addItem(m_Current_Time + "-成功删除：" + Jaka_File_Name);
	ui->Robot_Teaching_List->clear();
	ui->Teach_Complete->clicked();
}
/*************************************************************************************************************************************************
**Function:车厢组成数据：A动车、B拖车
*************************************************************************************************************************************************/
void c_Robot_App_Widget::on_Load_Car_Number_clicked()
{
	QString Jaka_File_Name = ui->Robot_File_Name_2->currentText();
	QJsonObject Program_Date = Read_Robot_Teach(Jaka_File_Name);

	int Car_Number_Date = ui->Car_Number_Date->currentText().toInt();

	QJsonArray Car_Number;
	if (Car_Number_Date == 8)
	{
		Car_Number.append(ui->Car_Number_1->currentText());
		Car_Number.append(ui->Car_Number_2->currentText());
		Car_Number.append(ui->Car_Number_3->currentText());
		Car_Number.append(ui->Car_Number_4->currentText());
		Car_Number.append(ui->Car_Number_5->currentText());
		Car_Number.append(ui->Car_Number_6->currentText());
		Car_Number.append(ui->Car_Number_7->currentText());
		Car_Number.append(ui->Car_Number_8->currentText());
	}
	if (Car_Number_Date == 16)
	{
		Car_Number.append(ui->Car_Number_1->currentText());
		Car_Number.append(ui->Car_Number_2->currentText());
		Car_Number.append(ui->Car_Number_3->currentText());
		Car_Number.append(ui->Car_Number_4->currentText());
		Car_Number.append(ui->Car_Number_5->currentText());
		Car_Number.append(ui->Car_Number_6->currentText());
		Car_Number.append(ui->Car_Number_7->currentText());
		Car_Number.append(ui->Car_Number_8->currentText());
		Car_Number.append(ui->Car_Number_9->currentText());
		Car_Number.append(ui->Car_Number_10->currentText());
		Car_Number.append(ui->Car_Number_11->currentText());
		Car_Number.append(ui->Car_Number_12->currentText());
		Car_Number.append(ui->Car_Number_13->currentText());
		Car_Number.append(ui->Car_Number_14->currentText());
		Car_Number.append(ui->Car_Number_15->currentText());
		Car_Number.append(ui->Car_Number_16->currentText());
	}


	Program_Date.insert("Car_Number", Car_Number);

	Write_Robot_Teach(Jaka_File_Name, Program_Date);

	ui->Worry_Message->addItem(m_Current_Time + "-成功写入车厢组成数据：" + Jaka_File_Name);
	ui->Load_Robot_Teaching->clicked();
}
/*************************************************************************************************************************************************
**Function:机械臂120当前位置
*************************************************************************************************************************************************/
void c_Robot_App_Widget::on_Current_Point_120_clicked()
{
	ui->Jaka_120_Lift->setText(QString::number(m_Jaka_120_Lift_Position));
	ui->Jaka_120_Point_1->setText(QString::number(m_joint_actual_position.at(0).toDouble()));
	ui->Jaka_120_Point_2->setText(QString::number(m_joint_actual_position.at(1).toDouble()));
	ui->Jaka_120_Point_3->setText(QString::number(m_joint_actual_position.at(2).toDouble()));
	ui->Jaka_120_Point_4->setText(QString::number(m_joint_actual_position.at(3).toDouble()));
	ui->Jaka_120_Point_5->setText(QString::number(m_joint_actual_position.at(4).toDouble()));
	ui->Jaka_120_Point_6->setText(QString::number(m_joint_actual_position.at(5).toDouble()));
}
/*************************************************************************************************************************************************
**Function:机械臂121当前位置
*************************************************************************************************************************************************/
void c_Robot_App_Widget::on_Current_Point_121_clicked()
{
	ui->Jaka_121_Lift->setText(QString::number(m_Jaka_121_Lift_Position));
	ui->Jaka_121_Point_1->setText(QString::number(m_joint_actual_position.at(0).toDouble()));
	ui->Jaka_121_Point_2->setText(QString::number(m_joint_actual_position.at(1).toDouble()));
	ui->Jaka_121_Point_3->setText(QString::number(m_joint_actual_position.at(2).toDouble()));
	ui->Jaka_121_Point_4->setText(QString::number(m_joint_actual_position.at(3).toDouble()));
	ui->Jaka_121_Point_5->setText(QString::number(m_joint_actual_position.at(4).toDouble()));
	ui->Jaka_121_Point_6->setText(QString::number(m_joint_actual_position.at(5).toDouble()));
}
/*************************************************************************************************************************************************
**Function:记录机械臂120示教文件
*************************************************************************************************************************************************/
void c_Robot_App_Widget::on_Load_Point_120_clicked()
{
	QString Car_Name = ui->Car_Name->text();
	QString Car_Number = ui->Car_Number->text();

	QString Jaka_File_Name = ui->Robot_File_Name_2->currentText();
	QJsonObject Program_Date = Read_Robot_Teach(Jaka_File_Name);

	QJsonObject Motor_Date = Program_Date.value("A").toObject();;
	QJsonObject Trailer_Date = Program_Date.value("B").toObject();

	QJsonObject Motor_Axis_1_Date = Motor_Date.value("1").toObject();
	QJsonObject Motor_Axis_2_Date = Motor_Date.value("2").toObject();
	QJsonObject Trailer_Axis_1_Date = Trailer_Date.value("1").toObject();;
	QJsonObject Trailer_Axis_2_Date = Trailer_Date.value("2").toObject();

	QJsonArray Motor_Axis_1_Jaka_120_Date = Motor_Axis_1_Date.value("Jaka_120").toArray();
	QJsonArray Motor_Axis_2_Jaka_120_Date = Motor_Axis_2_Date.value("Jaka_120").toArray();
	QJsonArray Trailer_Axis_1_Jaka_120_Date = Trailer_Axis_1_Date.value("Jaka_120").toArray();
	QJsonArray Trailer_Axis_2_Jaka_120_Date = Trailer_Axis_2_Date.value("Jaka_120").toArray();

	QString Camera_Number_120 = ui->Camera_Number_120->text();
	QString Car_Box_Number_120 = ui->Car_Box_Number_120->currentText();
	QString Bogie_Number_120 = ui->Bogie_Number_120->currentText();
	QString Axis_Number_120 = ui->Axis_Number_120->currentText();
	QString Wheel_Number_120 = ui->Wheel_Number_120->currentText();
	QString Primary_Component_120 = ui->Primary_Component_120->currentText();
	QString Secondary_Component_120 = ui->Secondary_Component_120->currentText();

	QString Point_Name_120 = QString("%1-%2-%3-%4-%5-%6-%7-%8").arg(Camera_Number_120).arg(Car_Name+ Car_Number)
		.arg(Car_Box_Number_120).arg(Bogie_Number_120).arg(Axis_Number_120).arg(Wheel_Number_120)
		.arg(Primary_Component_120).arg(Secondary_Component_120);

	QJsonArray Jaka_120_Position_Date;
	Jaka_120_Position_Date.append(ui->Jaka_120_Lift->text().toDouble());
	Jaka_120_Position_Date.append(ui->Jaka_120_Point_1->text().toDouble());
	Jaka_120_Position_Date.append(ui->Jaka_120_Point_2->text().toDouble());
	Jaka_120_Position_Date.append(ui->Jaka_120_Point_3->text().toDouble());
	Jaka_120_Position_Date.append(ui->Jaka_120_Point_4->text().toDouble());
	Jaka_120_Position_Date.append(ui->Jaka_120_Point_5->text().toDouble());
	Jaka_120_Position_Date.append(ui->Jaka_120_Point_6->text().toDouble());
	Jaka_120_Position_Date.append(ui->Camera_120->currentText().toInt());
	Jaka_120_Position_Date.append(Point_Name_120);

	int Work_Point_Number_120 = ui->Work_Point_Number_120->value();

	if (Bogie_Number_120 == "A" && Axis_Number_120 == "1")
	{
		if (Work_Point_Number_120 < Motor_Axis_1_Jaka_120_Date.size()) {
			Motor_Axis_1_Jaka_120_Date.replace(Work_Point_Number_120, Jaka_120_Position_Date);
		}
		else {
			Motor_Axis_1_Jaka_120_Date.append(Jaka_120_Position_Date);
		}
		Motor_Axis_1_Date.insert("Jaka_120", Motor_Axis_1_Jaka_120_Date);
		Motor_Date.insert("1", Motor_Axis_1_Date);
		Program_Date.insert("A", Motor_Date);
	}

	if (Bogie_Number_120 == "A" && Axis_Number_120 == "2")
	{
		if (Work_Point_Number_120 < Motor_Axis_2_Jaka_120_Date.size()) {
			Motor_Axis_2_Jaka_120_Date.replace(Work_Point_Number_120, Jaka_120_Position_Date);
		}
		else {
			Motor_Axis_2_Jaka_120_Date.append(Jaka_120_Position_Date);
		}
		Motor_Axis_2_Date.insert("Jaka_120", Motor_Axis_2_Jaka_120_Date);
		Motor_Date.insert("2", Motor_Axis_2_Date);
		Program_Date.insert("A", Motor_Date);
	}

	if (Bogie_Number_120 == "B" && Axis_Number_120 == "1")
	{
		if (Work_Point_Number_120 < Trailer_Axis_1_Jaka_120_Date.size()) {
			Trailer_Axis_1_Jaka_120_Date.replace(Work_Point_Number_120, Jaka_120_Position_Date);
		}
		else {
			Trailer_Axis_1_Jaka_120_Date.append(Jaka_120_Position_Date);
		}
		Trailer_Axis_1_Date.insert("Jaka_120", Trailer_Axis_1_Jaka_120_Date);
		Trailer_Date.insert("1", Trailer_Axis_1_Date);
		Program_Date.insert("B", Trailer_Date);
	}

	if (Bogie_Number_120 == "B" && Axis_Number_120 == "2")
	{
		if (Work_Point_Number_120 < Trailer_Axis_2_Jaka_120_Date.size()) {
			Trailer_Axis_2_Jaka_120_Date.replace(Work_Point_Number_120, Jaka_120_Position_Date);
		}
		else {
			Trailer_Axis_2_Jaka_120_Date.append(Jaka_120_Position_Date);
		}
		Trailer_Axis_2_Date.insert("Jaka_120", Trailer_Axis_2_Jaka_120_Date);
		Trailer_Date.insert("2", Trailer_Axis_1_Date);
		Program_Date.insert("B", Trailer_Date);
	}

	Write_Robot_Teach(Jaka_File_Name, Program_Date);
	ui->Worry_Message->addItem(m_Current_Time + "-机械臂120：已修改位置点" + QString::number(Work_Point_Number_120));
	ui->Load_Robot_Teaching->clicked();
	ui->Worry_Message->addItem(m_Current_Time + "-注意调整位置点编号");
}
/*************************************************************************************************************************************************
**Function:记录机械臂121示教文件
*************************************************************************************************************************************************/
void c_Robot_App_Widget::on_Load_Point_121_clicked()
{
	QString Car_Name = ui->Car_Name->text();
	QString Car_Number = ui->Car_Number->text();

	QString Jaka_File_Name = ui->Robot_File_Name_2->currentText();
	QJsonObject Program_Date = Read_Robot_Teach(Jaka_File_Name);

	QJsonObject Motor_Date = Program_Date.value("A").toObject();;
	QJsonObject Trailer_Date = Program_Date.value("B").toObject();

	QJsonObject Motor_Axis_1_Date = Motor_Date.value("1").toObject();
	QJsonObject Motor_Axis_2_Date = Motor_Date.value("2").toObject();
	QJsonObject Trailer_Axis_1_Date = Trailer_Date.value("1").toObject();;
	QJsonObject Trailer_Axis_2_Date = Trailer_Date.value("2").toObject();

	QJsonArray Motor_Axis_1_Jaka_121_Date = Motor_Axis_1_Date.value("Jaka_121").toArray();
	QJsonArray Motor_Axis_2_Jaka_121_Date = Motor_Axis_2_Date.value("Jaka_121").toArray();
	QJsonArray Trailer_Axis_1_Jaka_121_Date = Trailer_Axis_1_Date.value("Jaka_121").toArray();
	QJsonArray Trailer_Axis_2_Jaka_121_Date = Trailer_Axis_2_Date.value("Jaka_121").toArray();

	QString Camera_Number_121 = ui->Camera_Number_121->text();
	QString Car_Box_Number_121 = ui->Car_Box_Number_121->currentText();
	QString Bogie_Number_121 = ui->Bogie_Number_121->currentText();
	QString Axis_Number_121 = ui->Axis_Number_121->currentText();
	QString Wheel_Number_121 = ui->Wheel_Number_121->currentText();
	QString Primary_Component_121 = ui->Primary_Component_121->currentText();
	QString Secondary_Component_121 = ui->Secondary_Component_121->currentText();

	QString Point_Name_121 = QString("%1-%2-%3-%4-%5-%6-%7-%8").arg(Camera_Number_121).arg(Car_Name + Car_Number)
		.arg(Car_Box_Number_121).arg(Bogie_Number_121).arg(Axis_Number_121).arg(Wheel_Number_121)
		.arg(Primary_Component_121).arg(Secondary_Component_121);

	QJsonArray Jaka_121_Position_Date;
	Jaka_121_Position_Date.append(ui->Jaka_121_Lift->text().toDouble());
	Jaka_121_Position_Date.append(ui->Jaka_121_Point_1->text().toDouble());
	Jaka_121_Position_Date.append(ui->Jaka_121_Point_2->text().toDouble());
	Jaka_121_Position_Date.append(ui->Jaka_121_Point_3->text().toDouble());
	Jaka_121_Position_Date.append(ui->Jaka_121_Point_4->text().toDouble());
	Jaka_121_Position_Date.append(ui->Jaka_121_Point_5->text().toDouble());
	Jaka_121_Position_Date.append(ui->Jaka_121_Point_6->text().toDouble());
	Jaka_121_Position_Date.append(ui->Camera_121->currentText().toInt());
	Jaka_121_Position_Date.append(Point_Name_121);

	int Work_Point_Number_121 = ui->Work_Point_Number_121->value();

	if (Bogie_Number_121 == "A" && Axis_Number_121 == "1")
	{
		if (Work_Point_Number_121 < Motor_Axis_1_Jaka_121_Date.size()) {
			Motor_Axis_1_Jaka_121_Date.replace(Work_Point_Number_121, Jaka_121_Position_Date);
		}
		else {
			Motor_Axis_1_Jaka_121_Date.append(Jaka_121_Position_Date);
		}
		Motor_Axis_1_Date.insert("Jaka_121", Motor_Axis_1_Jaka_121_Date);
		Motor_Date.insert("1", Motor_Axis_1_Date);
		Program_Date.insert("A", Motor_Date);
	}

	if (Bogie_Number_121 == "A" && Axis_Number_121 == "2")
	{
		if (Work_Point_Number_121 < Motor_Axis_2_Jaka_121_Date.size()) {
			Motor_Axis_2_Jaka_121_Date.replace(Work_Point_Number_121, Jaka_121_Position_Date);
		}
		else {
			Motor_Axis_2_Jaka_121_Date.append(Jaka_121_Position_Date);
		}
		Motor_Axis_2_Date.insert("Jaka_121", Motor_Axis_2_Jaka_121_Date);
		Motor_Date.insert("2", Motor_Axis_2_Date);
		Program_Date.insert("A", Motor_Date);
	}

	if (Bogie_Number_121 == "B" && Axis_Number_121 == "1")
	{
		if (Work_Point_Number_121 < Trailer_Axis_1_Jaka_121_Date.size()) {
			Trailer_Axis_1_Jaka_121_Date.replace(Work_Point_Number_121, Jaka_121_Position_Date);
		}
		else {
			Trailer_Axis_1_Jaka_121_Date.append(Jaka_121_Position_Date);
		}
		Trailer_Axis_1_Date.insert("Jaka_121", Trailer_Axis_1_Jaka_121_Date);
		Trailer_Date.insert("1", Trailer_Axis_1_Date);
		Program_Date.insert("B", Trailer_Date);
	}

	if (Bogie_Number_121 == "B" && Axis_Number_121 == "2")
	{
		if (Work_Point_Number_121 < Trailer_Axis_2_Jaka_121_Date.size()) {
			Trailer_Axis_2_Jaka_121_Date.replace(Work_Point_Number_121, Jaka_121_Position_Date);
		}
		else {
			Trailer_Axis_2_Jaka_121_Date.append(Jaka_121_Position_Date);
		}
		Trailer_Axis_2_Date.insert("Jaka_121", Trailer_Axis_2_Jaka_121_Date);
		Trailer_Date.insert("2", Trailer_Axis_1_Date);
		Program_Date.insert("B", Trailer_Date);
	}

	Write_Robot_Teach(Jaka_File_Name, Program_Date);
	ui->Worry_Message->addItem(m_Current_Time + "-机械臂121：已修改位置点" + QString::number(Work_Point_Number_121));
	ui->Load_Robot_Teaching->clicked();
	ui->Worry_Message->addItem(m_Current_Time + "-注意调整位置点编号");
}
/*************************************************************************************************************************************************
**Function:删除机械臂120示教文件
*************************************************************************************************************************************************/
void c_Robot_App_Widget::on_Delete_Point_120_clicked()
{
	QString Jaka_File_Name = ui->Robot_File_Name_2->currentText();
	QJsonObject Program_Date = Read_Robot_Teach(Jaka_File_Name);

	QJsonObject Motor_Date = Program_Date.value("A").toObject();;
	QJsonObject Trailer_Date = Program_Date.value("B").toObject();

	QJsonObject Motor_Axis_1_Date = Motor_Date.value("1").toObject();
	QJsonObject Motor_Axis_2_Date = Motor_Date.value("2").toObject();
	QJsonObject Trailer_Axis_1_Date = Trailer_Date.value("1").toObject();;
	QJsonObject Trailer_Axis_2_Date = Trailer_Date.value("2").toObject();

	QJsonArray Motor_Axis_1_Jaka_120_Date = Motor_Axis_1_Date.value("Jaka_120").toArray();
	QJsonArray Motor_Axis_2_Jaka_120_Date = Motor_Axis_2_Date.value("Jaka_120").toArray();
	QJsonArray Trailer_Axis_1_Jaka_120_Date = Trailer_Axis_1_Date.value("Jaka_120").toArray();
	QJsonArray Trailer_Axis_2_Jaka_120_Date = Trailer_Axis_2_Date.value("Jaka_120").toArray();

	QString Camera_Number_120 = ui->Camera_Number_120->text();
	QString Car_Box_Number_120 = ui->Car_Box_Number_120->currentText();
	QString Bogie_Number_120 = ui->Bogie_Number_120->currentText();
	QString Axis_Number_120 = ui->Axis_Number_120->currentText();
	QString Wheel_Number_120 = ui->Wheel_Number_120->currentText();
	QString Primary_Component_120 = ui->Primary_Component_120->currentText();
	QString Secondary_Component_120 = ui->Secondary_Component_120->currentText();

	int Work_Point_Number_120 = ui->Work_Point_Number_120->value();

	if (Bogie_Number_120 == "A" && Axis_Number_120 == "1")
	{
		if (Work_Point_Number_120 < Motor_Axis_1_Jaka_120_Date.size()) {
			Motor_Axis_1_Jaka_120_Date.removeAt(Work_Point_Number_120);
		}
		else {
			QMessageBox::information(this, "错误", "位置不存在");
		}
		Motor_Axis_1_Date.insert("Jaka_120", Motor_Axis_1_Jaka_120_Date);
		Motor_Date.insert("1", Motor_Axis_1_Date);
		Program_Date.insert("A", Motor_Date);
	}

	if (Bogie_Number_120 == "A" && Axis_Number_120 == "2")
	{
		if (Work_Point_Number_120 < Motor_Axis_2_Jaka_120_Date.size()) {
			Motor_Axis_2_Jaka_120_Date.removeAt(Work_Point_Number_120);
		}
		else {
			QMessageBox::information(this, "错误", "位置不存在");
		}
		Motor_Axis_2_Date.insert("Jaka_120", Motor_Axis_2_Jaka_120_Date);
		Motor_Date.insert("2", Motor_Axis_2_Date);
		Program_Date.insert("A", Motor_Date);
	}

	if (Bogie_Number_120 == "B" && Axis_Number_120 == "1")
	{
		if (Work_Point_Number_120 < Trailer_Axis_1_Jaka_120_Date.size()) {
			Trailer_Axis_1_Jaka_120_Date.removeAt(Work_Point_Number_120);
		}
		else {
			QMessageBox::information(this, "错误", "位置不存在");
		}
		Trailer_Axis_1_Date.insert("Jaka_120", Trailer_Axis_1_Jaka_120_Date);
		Trailer_Date.insert("1", Trailer_Axis_1_Date);
		Program_Date.insert("B", Trailer_Date);
	}

	if (Bogie_Number_120 == "B" && Axis_Number_120 == "2")
	{
		if (Work_Point_Number_120 < Trailer_Axis_2_Jaka_120_Date.size()) {
			Trailer_Axis_2_Jaka_120_Date.removeAt(Work_Point_Number_120);
		}
		else {
			QMessageBox::information(this, "错误", "位置不存在");
		}
		Trailer_Axis_2_Date.insert("Jaka_120", Trailer_Axis_2_Jaka_120_Date);
		Trailer_Date.insert("2", Trailer_Axis_1_Date);
		Program_Date.insert("B", Trailer_Date);
	}

	Write_Robot_Teach(Jaka_File_Name, Program_Date);
	ui->Worry_Message->addItem(m_Current_Time + "-机械臂120：已删除位置点" + QString::number(Work_Point_Number_120));
	ui->Load_Robot_Teaching->clicked();
	ui->Worry_Message->addItem(m_Current_Time + "-注意调整位置点编号");
}
/*************************************************************************************************************************************************
**Function:删除机械臂121示教文件
*************************************************************************************************************************************************/
void c_Robot_App_Widget::on_Delete_Point_121_clicked()
{
	QString Jaka_File_Name = ui->Robot_File_Name_2->currentText();
	QJsonObject Program_Date = Read_Robot_Teach(Jaka_File_Name);

	QJsonObject Motor_Date = Program_Date.value("A").toObject();;
	QJsonObject Trailer_Date = Program_Date.value("B").toObject();

	QJsonObject Motor_Axis_1_Date = Motor_Date.value("1").toObject();
	QJsonObject Motor_Axis_2_Date = Motor_Date.value("2").toObject();
	QJsonObject Trailer_Axis_1_Date = Trailer_Date.value("1").toObject();;
	QJsonObject Trailer_Axis_2_Date = Trailer_Date.value("2").toObject();

	QJsonArray Motor_Axis_1_Jaka_121_Date = Motor_Axis_1_Date.value("Jaka_121").toArray();
	QJsonArray Motor_Axis_2_Jaka_121_Date = Motor_Axis_2_Date.value("Jaka_121").toArray();
	QJsonArray Trailer_Axis_1_Jaka_121_Date = Trailer_Axis_1_Date.value("Jaka_121").toArray();
	QJsonArray Trailer_Axis_2_Jaka_121_Date = Trailer_Axis_2_Date.value("Jaka_121").toArray();

	QString Camera_Number_121 = ui->Camera_Number_121->text();
	QString Car_Box_Number_121 = ui->Car_Box_Number_121->currentText();
	QString Bogie_Number_121 = ui->Bogie_Number_121->currentText();
	QString Axis_Number_121 = ui->Axis_Number_121->currentText();
	QString Wheel_Number_121 = ui->Wheel_Number_121->currentText();
	QString Primary_Component_121 = ui->Primary_Component_121->currentText();
	QString Secondary_Component_121 = ui->Secondary_Component_121->currentText();

	int Work_Point_Number_121 = ui->Work_Point_Number_121->value();

	if (Bogie_Number_121 == "A" && Axis_Number_121 == "1")
	{
		if (Work_Point_Number_121 < Motor_Axis_1_Jaka_121_Date.size()) {
			Motor_Axis_1_Jaka_121_Date.removeAt(Work_Point_Number_121);
		}
		else {
			QMessageBox::information(this, "错误", "位置不存在");
		}
		Motor_Axis_1_Date.insert("Jaka_121", Motor_Axis_1_Jaka_121_Date);
		Motor_Date.insert("1", Motor_Axis_1_Date);
		Program_Date.insert("A", Motor_Date);
	}

	if (Bogie_Number_121 == "A" && Axis_Number_121 == "2")
	{
		if (Work_Point_Number_121 < Motor_Axis_2_Jaka_121_Date.size()) {
			Motor_Axis_2_Jaka_121_Date.removeAt(Work_Point_Number_121);
		}
		else {
			QMessageBox::information(this, "错误", "位置不存在");
		}
		Motor_Axis_2_Date.insert("Jaka_121", Motor_Axis_2_Jaka_121_Date);
		Motor_Date.insert("2", Motor_Axis_2_Date);
		Program_Date.insert("A", Motor_Date);
	}

	if (Bogie_Number_121 == "B" && Axis_Number_121 == "1")
	{
		if (Work_Point_Number_121 < Trailer_Axis_1_Jaka_121_Date.size()) {
			Trailer_Axis_1_Jaka_121_Date.removeAt(Work_Point_Number_121);
		}
		else {
			QMessageBox::information(this, "错误", "位置不存在");
		}
		Trailer_Axis_1_Date.insert("Jaka_121", Trailer_Axis_1_Jaka_121_Date);
		Trailer_Date.insert("1", Trailer_Axis_1_Date);
		Program_Date.insert("B", Trailer_Date);
	}

	if (Bogie_Number_121 == "B" && Axis_Number_121 == "2")
	{
		if (Work_Point_Number_121 < Trailer_Axis_2_Jaka_121_Date.size()) {
			Trailer_Axis_2_Jaka_121_Date.removeAt(Work_Point_Number_121);
		}
		else {
			QMessageBox::information(this, "错误", "位置不存在");
		}
		Trailer_Axis_2_Date.insert("Jaka_121", Trailer_Axis_2_Jaka_121_Date);
		Trailer_Date.insert("2", Trailer_Axis_1_Date);
		Program_Date.insert("B", Trailer_Date);
	}

	Write_Robot_Teach(Jaka_File_Name, Program_Date);
	ui->Worry_Message->addItem(m_Current_Time + "-机械臂121：已删除位置点" + QString::number(Work_Point_Number_121));
	ui->Load_Robot_Teaching->clicked();
	ui->Worry_Message->addItem(m_Current_Time + "-注意调整位置点编号");
}
/*************************************************************************************************************************************************
**Function:JsonArray转String
*************************************************************************************************************************************************/
QString c_Robot_App_Widget::JsonArray_To_String(const QJsonArray &data)
{
	QJsonDocument doc;
	doc.setArray(data);
	return QString::fromUtf8(doc.toJson(QJsonDocument::Compact).constData());
}