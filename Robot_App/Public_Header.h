#pragma once
/*************************************************************************************************************************************************
**系统三层结构：
                                           |->信号槽（signal/slot）               
          |->用户界面层（user interface）->|
          |                                |->界面（ui）
          |
		  |		                         |->发送数据（send）
软件架构->|->业务逻辑层(business logic)->|->接收数据（receive）
		  |		                         |->处理数据（process）
		  |
		  |                                                   |->本地（local）->打开（open）、关闭(close)、写(write)、读（read）
          |                                 |->设备（device）-|
		  |                                 |                 |->远程（remote）->通讯（socket）
          |                                 |
		  |->数据访问层(data access layer)->|->数据库（datebase）->增（add）、删（delete）、改（modify）、查（select）
		                                    |
                                            |->进程接口（ipc）->接口（api）->服务器（server）

**设备组成
->上位机：工控机（研华）
->下位机：PLC（西门子1200）
          采集机（研华）
		  机械臂控制器（Jaka minicab）
		  线阵雷达（Meijidenki）
		  面阵雷达（Hypersen）

**待添加功能：
->写指令缓存区
/*************************************************************************************************************************************************
**Function:线阵雷达IO映射
*************************************************************************************************************************************************/
#define IO_OUTNUM 3
#define IO_INNUM 2
/*************************************************************************************************************************************************
**Function:机械臂巡检工位映射
*************************************************************************************************************************************************/

/*************************************************************************************************************************************************
**Function:移动底盘寄存器地址映射
*************************************************************************************************************************************************/
//RGV手动正向行走
#define MANUALFORWARDTRAVEL 0
//RGV手动反向行走
#define MANUALREVERSETRAVEL 1
//第n次断续反向运行
#define THENTHINTERMITTENTREVERSEOPERATION 2
//RGV手动停止
#define MANUALSTOP 3
//连续正向行走
#define CONTINUOUSFORWARDWALKING 4
//第一次断续反向运行
#define FIRSTINTERMITTENTREVERSEOPERATION 5
//位置清零
#define POSITIONRESET 6
//左升降复位
#define LEFTLIFTINGRESET 7
//手动左上升
#define MANUALLEFTRISE 8
//手动左下降
#define MANUALLEFTDESCENT 9
//右升降复位
#define RIGHTLIFTINGRESET 10
//手动右上升
#define MANUALRIGHTRISE 11
//手动右下降
#define MANUALRIGHTDESCENT 12
//左开门
#define LEFTDOOROPENING 13
//中开门
#define MIDDLEDOOROPENING 14
//右开门
#define RIGHTDOOROPENING 15
//左关门
#define LEFTDOORCLOSING 16
//中关门
#define MIDDLEDOORCLOSING 17
//右关门
#define RIGHTDOORCLOSING 18
//左升降台上升高度
#define LEFTLIFTINGHEIGHT 19
//右升降台上升高度
#define RIGHTLIFTINGHEIGHT 20
//拖车轴1
#define TRAILERAXIS1 21
//拖车轴2
#define TRAILERAXIS2 22
//动车轴1
#define MOTORAXIS1 23
//动车轴2
#define MOTORAXIS2 24

//RGV参数设置
//RGV运动速度
#define MOVEMENTSPEED 1
//RGV断续运行速度
#define MANUALREVERSESPEED 2
//RGV蠕动速度
#define FIRSTCREEPSPEED 3
//RGV第二次蠕动速度
#define SECONDCREEPSPEED 4
//RGV加速度
#define ACCELERATIONSPEED 5
//RGV减速度
#define DECELERATIONLSPEED 6
//左升降台参数设置
//原点速度(复位)
#define LEFTLIFTINGORIGINSPEED 7
//爬行速度
#define LEFTLIFTINGCREEPSPEED 8
//手动速度
#define LEFTLIFTINGMANUALSPEED 9
//升降速度
#define LEFTLIFTINGAUTOMATICSPEED 10
//右升降台参数设置
//原点速度(复位)
#define RIGHTLIFTINGORIGINSPEED 11
//爬行速度
#define RIGHTLIFTINGCREEPSPEED 12
//手动速度
#define RIGHTLIFTINGMANUALSPEED 13
//升降速度
#define RIGHTLIFTINGAUTOMATICSPEED 14
//移动门参数设置
//左门速度
#define LEFTDOORSPEED 15
//中门速度
#define MIDDLEDOORSPEED 16
//右门速度
#define RIGHTDOORSPEED 17
//运行参数设置
//车底检测距离
#define BOTTOMDETECTIONDISTANCE 18
//车底检测距离延时
#define BOTTOMDETECTIONDELAY 19
//拖车轮对距离
#define TRAILERWHEELSETDISTANCE 20
//拖车轮对误差
#define TRAILERWHEELSETERROR 21
//拖车轮轴距离
#define TRAILERAXLEDISTANCE 22
//拖车轮轴误差
#define TRAILERAXLEERROR 23
//动车轮对距离
#define MOTORWHEELSETDISTANCE 24
//动车轮对误差
#define MOTORWHEELWHEELSETERROR 25
//动车轮轴距离
#define MOTORWHEELAXLEDISTANCE 26
//动车轮轴误差
#define MOTORWHEELAXLEERROR 27

//RGV状态
//主动力通信状态
#define ACTIVEPOWERCOMMUNICATIONSTATUS 28
//主动力电流反馈
#define ACTIVEFORCECURRENTFEEDBACK 29
//主动力故障信号
#define MAINPOWERFAILURESIGNAL 30
//主动力状态信号
#define ACTIVEPOWERSTATUSSIGNAL 31
//主动力电压
#define MAINFORCEVOLTAGE 32
//主动力温度
#define MAINFORCETEMPERATURE 33
//中轮对距离1
#define MIDDLEWHEELSETDISTANCE1 34
//中轮轴距离
#define MIDDLEAXLEDISTANCE 35
//中轮对距离2
#define MIDDLEWHEELSETDISTANCE2 36
//车底板距离
#define FLOORDISTANCE 37
//当前速度
#define CURRENTSPEED 38
//主动位置反馈
#define ACTIVEPOSITIONFEEDBACK 39
//右轮对距离
#define RIGHTWHEELSETDISTANCE 40
//左轴对距离
#define LEFTAXISDISTANCE 41
//左升降位置
#define LEFTLIFTINGPOSITION 42
//右升降位置
#define RIGHTLIFTINGPOSITION 43
//左门1通信状态
#define LEFTDOORCOMMUNICATIONSTATUS1 44
//左门2通信状态
#define LEFTDOORCOMMUNICATIONSTATUS2 45
//左门1启动停止信号
#define LEFTDOORSTARTSTOPSIGNAL1 46
//左门2启动停止信号
#define LEFTDOORSTARTSTOPSIGNAL2 47
//中门1状态
#define MIDDLEDOORSTATUS1 48
//中门2状态
#define MIDDLEDOORSTATUS2 49
//中门1停止启动
#define MIDDLEDOORSTOPSTART1 50
//中门2停止启动
#define MIDDLEDOORSTOPSTART2 51
//右门1状态
#define RIGHTDOORSTATUS1 52
//右门2状态
#define RIGHTDOORSTATUS2 53
//右门1启动停止
#define RIGHTDOORSTARTSTOP1 54
//右门2启动停止
#define RIGHTDOORSTARTSTOP2 55
//电池电压
#define BATTERYVOLTAGE 56
//电量%
#define ELECTRICQUANTITY 57
//电池剩于容量MA*H
#define BATTERYREMAININGCAPACITY 58
//RGV手动正向行走
#define MANUALFORWARDTRAVELSTATE 59
//RGV手动反向行走
#define MANUALREVERSETRAVELSTATE 60
/*************************************************************************************************************************************************
**Function:包含目录
*************************************************************************************************************************************************/
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QTimer>
#include <QDateTime>
#include <QObject>
#include <QThread>
#include <QMutex>
#include <QMutexLocker>
#include <QWidget>
#include <QKeyEvent>
#include <QMessageBox>
#include <QVector>
#include <QVariant>
#include <QByteArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QHostAddress>
#include <QApplication>
#include <QMainWindow>
#include <QstackedWidget>
#include <QEventLoop>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QAbstractSocket>
#include <QModbusTcpClient>
#include <QModbusDataUnit>
#include <Qpainter>
#include <Qbrush>
#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include "Custom_Plot.h"
#include "HPS3D_IF.h"
#include "HPS3D_DEFINE.h"
#include "EquipmentComm.h"
#include "lim.h"
/*************************************************************************************************************************************************
**Function:前置声明
*************************************************************************************************************************************************/
class c_Hypersen_Client;
class c_Jaka_Client;
class c_Meijidenki_Client;
class c_RGV_Client;
class c_Robot_Server;
/*************************************************************************************************************************************************
**Function:注册结构体
*************************************************************************************************************************************************/
struct s_Meijidenki_DB {
	int cid = 0;
	LIM_HEAD *lim = NULL;
};
Q_DECLARE_METATYPE(s_Meijidenki_DB);

/*************************************************************************************************************************************************
**Function:系统全局变量与接口
*************************************************************************************************************************************************/
class c_Variable : public QObject
{
	Q_OBJECT
public:
    explicit c_Variable(QObject *parent = nullptr);
    ~c_Variable();
	static QJsonObject g_Communicate_DB;
	static QJsonObject g_Robot_Teach_Widget_DB;
	static QString TCP_Status(int State);
	static QString Modbus_Status(int State);
	static bool msleep(const int mSec);
private:
	QFile Communicate_DB;
};

/*************************************************************************************************************************************************
**Function:面阵雷达回调函数
*************************************************************************************************************************************************/
class c_Hypersen_CallBack : public QObject
{
	Q_OBJECT

public:
	c_Hypersen_CallBack(QObject * parent = nullptr);
	~c_Hypersen_CallBack();
	//操作对象
	static c_Hypersen_CallBack *g_Hypersen_CallBack;
	//Debug信息回调函数，只需要将str打印即可
	static void Hypersen_DebugFunc(char *str, void *contex);
	//输出事件回调函数，注意请不要在回调函数中进行耗时较长的操作
	static void Hypersen_OutputEventFunc(uint8_t out_id, uint8_t event, void *contex);

signals:
	//读准备完成
	void ReadReady(quint8 out_id);
	//设备状态
	void State_Changed(QString str);
};

/*************************************************************************************************************************************************
**Function:线阵雷达回调函数
*************************************************************************************************************************************************/
class c_Meijidenki_CallBack : public QObject
{
	Q_OBJECT

public:
	c_Meijidenki_CallBack(QObject * parent = nullptr);
	~c_Meijidenki_CallBack();
	//操作对象
	static c_Meijidenki_CallBack *g_Meijidenki_CallBack;
	//Debug信息回调函数，只需要将_state_code传递即可
	static void CALLBACK EqCommStateCallBack(int _cid, unsigned int _state_code, char* _ip, int _port, int _paddr);
	//输出事件回调函数，注意请不要在回调函数中进行耗时较长的操作
	static void CALLBACK EqCommDataCallBack(int _cid, unsigned int _lim_code, void* _lim, int _lim_len, int _paddr);

signals:
	//读准备完成
	void ReadReady(QVariant _db);
	//设备状态
	void State_Changed(qint32 _cid, quint32 _state_code);

private:
	s_Meijidenki_DB m_Meijidenki_DB;

	private slots:
	QVariant Meijidenki_DB();
};

/*************************************************************************************************************************************************
**Function:机械臂遥控父类定义
*************************************************************************************************************************************************/
class c_Jaka_Remote : public QObject
{
	Q_OBJECT
public:
	explicit c_Jaka_Remote(QObject *parent = nullptr);
	~c_Jaka_Remote();

	QThread *m_Jaka_Remote_Thread;
	c_Jaka_Client *m_Jaka_Remote;

	public slots:
	//初始化接口
	void Init();
	//虚函数
	virtual void Connect();
	
	//遥控接口
	void Jaka_power_on();
	void Jaka_power_off();
	void Jaka_enable_robot();
	void Jaka_disable_robot();
	void Jaka_stop_program();
	void Jaka_reset_program();
	void Jaka_joint_1_1();
	void Jaka_joint_2_1();
	void Jaka_joint_3_1();
	void Jaka_joint_4_1();
	void Jaka_joint_5_1();
	void Jaka_joint_6_1();
	void Jaka_joint_1_2();
	void Jaka_joint_2_2();
	void Jaka_joint_3_2();
	void Jaka_joint_4_2();
	void Jaka_joint_5_2();
	void Jaka_joint_6_2();

signals:
	void Connect_Device(QString ip, int port);//连接到服务器
	void Disconnect_Device();//断开连接
	void Write_Jaka_Remote_State(QJsonObject db);//写状态
	void Write_Json(QJsonObject json);//写Json消息
	void Write_Json_Done();//写Json消息完成
	void Write_Json_Error();//写Json消息错误
	void setEnabled(bool ready);//写消息状态
	void Set_Working();//工作状态
	void Set_Default();//非工作状态
	void Status(QString status);//遥控器状态

private:
	bool m_Writing = false;
	QJsonObject m_Jaka_Remote_State;
	QJsonObject power_on;//上电
	QJsonObject power_off;//下电
	QJsonObject enable_robot;//上使能
	QJsonObject disable_robot;//下使能
	QJsonObject joint_move(QJsonArray joint, double speed, int relflag);//关节角运动
	QJsonObject stop_program;//停止程序

	private slots:
	void Connect_Done();
	void Disconnect_Done();
	void Write(QJsonObject json);
	void Read_Json_Done(QJsonObject json);
};

/*************************************************************************************************************************************************
**Function:机械臂监视父类定义
*************************************************************************************************************************************************/
class c_Jaka_Monitor : public QObject
{
	Q_OBJECT
public:
	explicit c_Jaka_Monitor(QObject *parent = nullptr);
	~c_Jaka_Monitor();

	QThread *m_Jaka_Monitor_Thread;
	c_Jaka_Client *m_Jaka_Monitor;
	//共有状态参数
	QJsonArray joint_actual_position = {};
	QJsonArray actual_position = {};
	QJsonArray homed = {};
	QJsonArray drag_near_limit = {};
	int task_state = 0;
	int task_mode = 0;
	int interp_state = 0;
	int current_tool_id = 0;
	int protective_stop = 0;
	int on_soft_limit = 0;
	int emergency_stop = 0;

	public slots:
	//初始化接口
	void Init();
	//虚函数
	virtual void Connect();
	//进入状态监控，判断是否到达既定关节角位置
	void Joint_Monitor(QJsonArray joint);
	void Power_Monitor();
	void Enable_Monitor();

signals:
	void Connect_Device(QString ip, int port);//连接到服务器
	void Disconnect_Device();//断开连接
	void Write_Jaka_Monitor_State(QJsonObject db);//写状态
	void Set_Working();//工作状态
	void Set_Default();//非工作状态
	void setEnabled(bool ready);//写消息状态
	void Status(QString status);//监视器状态
	void Joint_Moved();//运动完成
	void Power_On();//上电
	void Power_Off();//下电
	void Enable_Robot();//上使能
	void Disable_Robot();//下使能

private:
	QJsonObject m_Jaka_Monitor_State;
	QJsonArray joint_aim_position = {};
	bool m_Joint_Monitor = false;
	bool m_Power_Monitor = false;
	bool m_Able_Monitor = false;

	private slots :
    void Connect_Done();
	void Disconnect_Done();
	void Read_Json_Done(QJsonObject json);
	bool Compare_position(QJsonArray joint1, QJsonArray joint2);
};

/*************************************************************************************************************************************************
**Function:面阵雷达遥控父类定义
*************************************************************************************************************************************************/
class c_Hypersen_Remote : public QObject
{
	Q_OBJECT
public:
	explicit c_Hypersen_Remote(QObject *parent = nullptr);
	~c_Hypersen_Remote();
	QThread *m_Hypersen_Remote_Thread;
	c_Hypersen_Client *m_Hypersen_Remote;

	public slots:
	//初始化接口
	void Init();
	//虚函数
	virtual void Connect();
	void Run_Single_Shot();
	void Run_Continuous();
	void Run_Idle();
	
signals:
	void Connect_Device(QString ip, int port);//连接到服务器
	void Disconnect_Device();//断开连接
	void Write_Hypersen_Remote_State(QJsonObject db);//写状态
	void Set_Working();//工作状态
	void Set_Default();//非工作状态
	void setEnabled(bool ready);//写消息状态
	void Write(quint8 value);
	void Status(QString status);//监视器状态

private:
	QJsonObject m_Hypersen_Remote_State;
	int m_roi_number = 0;
	int m_roi_aver_distance = 0;
	int m_roi_max_distance = 0;
	int m_roi_min_distance = 0;
	int m_roi_valid_aver_amp = 0;
	int m_roi_all_aver_amp = 0;

	private slots:
	void Connect_Done();
	void Disconnect_Done();
	void Read_Json_Done(QJsonObject json);
};

/*************************************************************************************************************************************************
**Function:线阵阵雷达遥控父类定义
*************************************************************************************************************************************************/
class c_Meijidenki_Remote : public QObject
{
	Q_OBJECT
public:
	explicit c_Meijidenki_Remote(QObject *parent = nullptr);
	~c_Meijidenki_Remote();
	QThread *m_Meijidenki_Remote_Thread;
	c_Meijidenki_Client *m_Meijidenki_Remote;

	public slots:
	//初始化接口
	void Init();
	//虚函数
	virtual void Connect();
	//外部操作接口
	void START_LMD();
	void STOP_LMD();

signals:
	void Connect_Device(int id, QString ip, int port);//连接到服务器
	void Disconnect_Device();//断开连接
	void Write_Meijidenki_Remote_State(QJsonObject db);//写状态
	void Set_Working();//工作状态
	void Set_Default();//非工作状态
	void setEnabled(bool ready);//写消息状态
	void Write(quint32 value);
	void Status(QString status);//监视器状态

private:
	QJsonObject m_Meijidenki_Remote_State;

	private slots:
	void Connect_Done();
	void Disconnect_Done();
	void Read_Json_Done(QJsonObject json);
};


