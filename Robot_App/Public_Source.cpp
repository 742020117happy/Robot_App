#pragma execution_character_set("utf-8")
#include "Public_Header.h"
#include "Hypersen_Client.h"
#include "Jaka_Client.h"
#include "Meijidenki_Client.h"

/*************************************************************************************************************************************************
**Function:全局变量声明
*************************************************************************************************************************************************/
QJsonObject c_Variable::g_Communicate_DB;
QJsonObject c_Variable::g_Robot_Teach_Widget_DB;
/*************************************************************************************************************************************************
**Function:通讯错误信息
*************************************************************************************************************************************************/
QString c_Variable::TCP_Status(int State)
{
	switch (State)
	{
	case 0:
		return " 连接被对等方拒绝（或超时）";
	case 1:
		return " 远程主机关闭了连接。请注意，客户端套接字（即此套接字）将在发送远程关闭通知后关闭";
	case 2:
		return " 找不到主机地址";
	case 3:
		return " 套接字操作失败，因为应用程序缺少所需的权限";
	case 4:
		return " 本地系统资源不足（例如，套接字过多）";
	case 5:
		return " 套接字操作超时";
	case 6:
		return " 数据报大于操作系统的限制（可低至8192字节）";
	case 7:
		return " 网络发生错误（例如，网络电缆意外插拔）";
	case 8:
		return " 为QAbstractSocket:：bind（）指定的地址已在使用中，并被设置为独占";
	case 9:
		return " 为QAbstractSocket:：bind（）指定的地址不属于主机";
	case 10:
		return " 本地操作系统不支持请求的套接字操作（例如，缺少IPv6支持）";
	case 11:
		return " 仅由QAbstractSocketEngine使用，上次尝试的操作尚未完成（仍在后台进行）";
	case 12:
		return "套接字正在使用代理，代理需要身份验证";
	case 13:
		return "SSL/TLS握手失败，因此连接已关闭（仅在QSslSocket中使用）";
	case 14:
		return "无法联系代理服务器，因为与该服务器的连接被拒绝";
	case 15:
		return "与代理服务器的连接意外关闭（在与最终对等方建立连接之前）";
	case 16:
		return "与代理服务器的连接超时，或者代理服务器在身份验证阶段停止响应。";
	case 17:
		return "找不到使用setProxy（）设置的代理地址（或应用程序代理）";
	case 18:
		return "与代理服务器的连接协商失败，因为无法理解来自代理服务器的响应";
	case 19:
		return "当套接字处于不允许的状态时，尝试了一个操作";
	case 20:
		return "正在使用的SSL库报告了一个内部错误。这可能是由于库的安装错误或配置错误造成的";
	case 21:
		return "提供了无效数据（证书、密钥、密码等），其使用导致SSL库中出现错误";
	case 22:
		return "发生临时错误（例如，操作将被阻塞，套接字为非阻塞）";
	case 23:
		return "套接字未连接";
	case 24:
		return "套接字正在执行主机名查找";
	case 25:
		return "套接字已开始建立连接";
	case 26:
		return "建立了一个连接";
	case 27:
		return "套接字绑定到一个地址和端口";
	case 28:
		return "套接字即将关闭（数据可能仍在等待写入）";
	case 29:
		return "套接字监听状态（仅供内部使用）";
	case -1:
		return "发生了一个无法识别的错误";
	default:
		return "无状态";
	}
}
QString c_Variable::Modbus_Status(int State)
{
	switch (State)
	{
	case 0:
		return "已连接";
	case 1:
		return "读取操作期间发生错误";
	case 2:
		return "写入操作期间发生错误";
	case 3:
		return ":尝试打开后端时出错";
	case 4:
		return ":尝试设置配置参数时出错";
	case 5:
		return ":I/O期间发生超时。I/O操作未在给定的时间范围内完成";
	case 6:
		return "发生Modbus特定协议错误";
	case 7:
		return "由于设备断开连接，回复被中止";
	case 8:
		return "发生未知错误";
	case 9:
		return "设备已断开连接";
	case 10:
		return "正在连接设备";
	case 11:
		return "设备正在关闭";
	default:
		return "无状态";
	}
}
/*************************************************************************************************************************************************
**Function:非阻塞延时
*************************************************************************************************************************************************/
bool c_Variable::msleep(const int mSec)
{
	QEventLoop *loop = new QEventLoop;
	QTimer::singleShot(mSec, loop, &QEventLoop::quit);
	loop->exec();
	return true;
}
/*************************************************************************************************************************************************
**Function:构造函数
*************************************************************************************************************************************************/
c_Variable::c_Variable(QObject *parent) : QObject(parent)
{
	/*************************************************************************************************************************************************
	**Function:读取通讯参数
	*************************************************************************************************************************************************/
	Communicate_DB.setFileName(QDir::currentPath() + "/System_DB/Communicate_DB.json");
	Communicate_DB.open(QFile::ReadOnly | QIODevice::Text);
	QByteArray Data = Communicate_DB.readAll();
	Communicate_DB.close();
	QJsonDocument DB_Doc(QJsonDocument::fromJson(Data));
	g_Communicate_DB = DB_Doc.object();
}
/*************************************************************************************************************************************************
**Function:析构函数
*************************************************************************************************************************************************/
c_Variable::~c_Variable()
{
	/*************************************************************************************************************************************************
	**Function:修改通讯参数本地文件
	*************************************************************************************************************************************************/
	Communicate_DB.open(QFile::WriteOnly | QIODevice::Text);
	QJsonDocument DB_Doc;
	DB_Doc.setObject(g_Communicate_DB);
	Communicate_DB.write(DB_Doc.toJson());
	Communicate_DB.close();
}

/*************************************************************************************************************************************************
**Function:指向面阵雷达的回调函数的全局指针
*************************************************************************************************************************************************/
c_Hypersen_CallBack *c_Hypersen_CallBack::g_Hypersen_CallBack = new c_Hypersen_CallBack;
/*************************************************************************************************************************************************
**Function:构造函数
*************************************************************************************************************************************************/
c_Hypersen_CallBack::c_Hypersen_CallBack(QObject * parent) : QObject(parent)
{
}
/*************************************************************************************************************************************************
**Function:析构指针
*************************************************************************************************************************************************/
c_Hypersen_CallBack::~c_Hypersen_CallBack()
{
	g_Hypersen_CallBack = NULL;
	delete g_Hypersen_CallBack;
}
/*************************************************************************************************************************************************
**Function:状态回调
*************************************************************************************************************************************************/
void c_Hypersen_CallBack::Hypersen_DebugFunc(char *str, void *contex)
{
	emit g_Hypersen_CallBack->State_Changed(QString(str));
}
/*************************************************************************************************************************************************
**Function:事件回调
*************************************************************************************************************************************************/
void c_Hypersen_CallBack::Hypersen_OutputEventFunc(uint8_t out_id, uint8_t event, void *contex)
{
	//简单深度事件，可以获取每个ROI的深度数学统计信息
	if (event == EVENT_ROISIMPLEDISTANCERECVD)
	{
		//获取指定ROI的深度信息前，需要通过ROI参数接口，获取当前输出的ROI信息，（有几个ROI，ROI的ID等）
		emit  g_Hypersen_CallBack->ReadReady(out_id);
	}
	else if (event == EVENT_DEVDISCONNECT) {
		//断开连接，回收资源
		HPS3D_DisConnect(out_id);
	}
}

/*************************************************************************************************************************************************
**Function:指向线阵雷达的回调函数的全局指针
*************************************************************************************************************************************************/
c_Meijidenki_CallBack *c_Meijidenki_CallBack::g_Meijidenki_CallBack = new c_Meijidenki_CallBack;
/*************************************************************************************************************************************************
**Function:构造函数
*************************************************************************************************************************************************/
c_Meijidenki_CallBack::c_Meijidenki_CallBack(QObject * parent) : QObject(parent)
{
	g_Meijidenki_CallBack = this;
}
/*************************************************************************************************************************************************
**Function:析构指针
*************************************************************************************************************************************************/
c_Meijidenki_CallBack::~c_Meijidenki_CallBack()
{
	g_Meijidenki_CallBack = NULL;
	delete g_Meijidenki_CallBack;
}
/*************************************************************************************************************************************************
**Function:状态回调
*************************************************************************************************************************************************/
void CALLBACK c_Meijidenki_CallBack::EqCommStateCallBack(int _cid, unsigned int _state_code, char* _ip, int _port, int _paddr)
{
	emit g_Meijidenki_CallBack->State_Changed(_cid, _state_code);
}
/*************************************************************************************************************************************************
**Function:数据回调
*************************************************************************************************************************************************/
void CALLBACK c_Meijidenki_CallBack::EqCommDataCallBack(int _cid, unsigned int _lim_code, void* _lim, int _lim_len, int _paddr)
{
	g_Meijidenki_CallBack->m_Meijidenki_DB.cid = _cid;
	g_Meijidenki_CallBack->m_Meijidenki_DB.lim = (LIM_HEAD*)_lim;
	unsigned int checksum = LIM_CheckSum(g_Meijidenki_CallBack->m_Meijidenki_DB.lim);
	if (checksum != g_Meijidenki_CallBack->m_Meijidenki_DB.lim->CheckSum) {
		return;
	}
	emit g_Meijidenki_CallBack->ReadReady(g_Meijidenki_CallBack->Meijidenki_DB());
}
/*************************************************************************************************************************************************
**Function:消息容器
*************************************************************************************************************************************************/
QVariant c_Meijidenki_CallBack::Meijidenki_DB()
{
	QVariant varData_DB;
	varData_DB.setValue(m_Meijidenki_DB);
	return varData_DB;
}

/*************************************************************************************************************************************************
**Function:构造函数(控制指令)
*************************************************************************************************************************************************/
c_Jaka_Remote::c_Jaka_Remote(QObject *parent) : QObject(parent)
{
	power_on.insert("cmdName", "power_on");
	power_off.insert("cmdName", "power_off");
	enable_robot.insert("cmdName", "enable_robot");
	disable_robot.insert("cmdName", "disable_robot");
	stop_program.insert("cmdName", "stop_program");

}
/*************************************************************************************************************************************************
**Function:析构
*************************************************************************************************************************************************/
c_Jaka_Remote::~c_Jaka_Remote()
{
	//线程中断
	m_Jaka_Remote_Thread->requestInterruption();
	//线程退出
	m_Jaka_Remote_Thread->quit();
	//线程等待
	m_Jaka_Remote_Thread->wait();
	//删除对象
	delete m_Jaka_Remote;
}
/*************************************************************************************************************************************************
**Function:初始化接口
*************************************************************************************************************************************************/
void c_Jaka_Remote::Init()
{
	//实例化
	m_Jaka_Remote = new c_Jaka_Client;
	m_Jaka_Remote_Thread = new QThread;
	m_Jaka_Remote->moveToThread(m_Jaka_Remote_Thread);
	//初始化数据交换层
	QObject::connect(m_Jaka_Remote_Thread, &QThread::started, m_Jaka_Remote, &c_Jaka_Client::Init);
	//连接设备
	QObject::connect(this, &c_Jaka_Remote::Connect_Device, m_Jaka_Remote, &c_Jaka_Client::Connect_Device);
	QObject::connect(this, &c_Jaka_Remote::Disconnect_Device, m_Jaka_Remote, &c_Jaka_Client::Disconnect_Device);
	//设备状态改变
	QObject::connect(m_Jaka_Remote, &c_Jaka_Client::Connect_Done, this, &c_Jaka_Remote::Set_Working);
	QObject::connect(m_Jaka_Remote, &c_Jaka_Client::Disconnect_Done, this, &c_Jaka_Remote::Set_Default);
	//键盘按键改变
	QObject::connect(this, &c_Jaka_Remote::Set_Working, this, [=] {emit setEnabled(true); });
	QObject::connect(this, &c_Jaka_Remote::Set_Default, this, [=] {emit setEnabled(false); });
	//向状态服务写入状态
	QObject::connect(m_Jaka_Remote, &c_Jaka_Client::Connect_Done, this, &c_Jaka_Remote::Connect_Done);
	QObject::connect(m_Jaka_Remote, &c_Jaka_Client::Disconnect_Done, this, &c_Jaka_Remote::Disconnect_Done);
	//写指令与校验
	QObject::connect(this, &c_Jaka_Remote::Write_Json, m_Jaka_Remote, &c_Jaka_Client::Write_Json);
	QObject::connect(m_Jaka_Remote, &c_Jaka_Client::Read_Json_Done, this, &c_Jaka_Remote::Read_Json_Done);
	//提示信息
	QObject::connect(m_Jaka_Remote, &c_Jaka_Client::Status, this, [=](int value) {emit Status(c_Variable::TCP_Status(value)); });
	//启动线程
	m_Jaka_Remote_Thread->start();
	emit setEnabled(false);
}
/*************************************************************************************************************************************************
**Function:虚函数
*************************************************************************************************************************************************/
void c_Jaka_Remote::Connect()
{
}
/*************************************************************************************************************************************************
**Function:子类公有遥控方法接口
*************************************************************************************************************************************************/
void c_Jaka_Remote::Jaka_power_on()
{
	Write(power_on);
}
void c_Jaka_Remote::Jaka_power_off()
{
	Write(power_off);
}
void c_Jaka_Remote::Jaka_enable_robot()
{
	Write(enable_robot);
}
void c_Jaka_Remote::Jaka_disable_robot()
{
	Write(disable_robot);
}
void c_Jaka_Remote::Jaka_stop_program()
{
	Write(stop_program);
}
void c_Jaka_Remote::Jaka_reset_program()
{
	QJsonArray joint;
	joint.append(-90);
	joint.append(150);
	joint.append(-150);
	joint.append(90);
	joint.append(0);
	joint.append(0);
	Write(joint_move(joint, 10, 0));
}
void c_Jaka_Remote::Jaka_joint_1_1()
{

	QJsonArray joint;
	joint.append(5);
	joint.append(0);
	joint.append(0);
	joint.append(0);
	joint.append(0);
	joint.append(0);
	//相对坐标运动
	emit Write(joint_move(joint, 10, 1));
}
void c_Jaka_Remote::Jaka_joint_2_1()
{
	QJsonArray joint;
	joint.append(0);
	joint.append(5);
	joint.append(0);
	joint.append(0);
	joint.append(0);
	joint.append(0);
	//相对坐标运动
	emit Write(joint_move(joint, 10, 1));
}
void c_Jaka_Remote::Jaka_joint_3_1()
{
	QJsonArray joint;
	joint.append(0);
	joint.append(0);
	joint.append(5);
	joint.append(0);
	joint.append(0);
	joint.append(0);
	//相对坐标运动
	emit Write(joint_move(joint, 10, 1));
}
void c_Jaka_Remote::Jaka_joint_4_1()
{
	QJsonArray joint;
	joint.append(0);
	joint.append(0);
	joint.append(0);
	joint.append(5);
	joint.append(0);
	joint.append(0);
	//相对坐标运动
	emit Write(joint_move(joint, 10, 1));
}
void c_Jaka_Remote::Jaka_joint_5_1()
{
	QJsonArray joint;
	joint.append(0);
	joint.append(0);
	joint.append(0);
	joint.append(0);
	joint.append(5);
	joint.append(0);
	//相对坐标运动
	emit Write(joint_move(joint, 10, 1));
}
void c_Jaka_Remote::Jaka_joint_6_1()
{
	QJsonArray joint;
	joint.append(0);
	joint.append(0);
	joint.append(0);
	joint.append(0);
	joint.append(0);
	joint.append(5);
	//相对坐标运动
	emit Write(joint_move(joint, 10, 1));
}
void c_Jaka_Remote::Jaka_joint_1_2()
{
	QJsonArray joint;
	joint.append(-5);
	joint.append(0);
	joint.append(0);
	joint.append(0);
	joint.append(0);
	joint.append(0);
	//相对坐标运动
	emit Write(joint_move(joint, 10, 1));
}
void c_Jaka_Remote::Jaka_joint_2_2()
{
	QJsonArray joint;
	joint.append(0);
	joint.append(-5);
	joint.append(0);
	joint.append(0);
	joint.append(0);
	joint.append(0);
	//相对坐标运动
	emit Write(joint_move(joint, 10, 1));
}
void c_Jaka_Remote::Jaka_joint_3_2()
{
	QJsonArray joint;
	joint.append(0);
	joint.append(0);
	joint.append(-5);
	joint.append(0);
	joint.append(0);
	joint.append(0);
	//相对坐标运动
	emit Write(joint_move(joint, 10, 1));
}
void c_Jaka_Remote::Jaka_joint_4_2()
{
	QJsonArray joint;
	joint.append(0);
	joint.append(0);
	joint.append(0);
	joint.append(-5);
	joint.append(0);
	joint.append(0);
	//相对坐标运动
	emit Write(joint_move(joint, 10, 1));
}
void c_Jaka_Remote::Jaka_joint_5_2()
{
	QJsonArray joint;
	joint.append(0);
	joint.append(0);
	joint.append(0);
	joint.append(0);
	joint.append(-5);
	joint.append(0);
	//相对坐标运动
	emit Write(joint_move(joint, 10, 1));
}
void c_Jaka_Remote::Jaka_joint_6_2()
{
	QJsonArray joint;
	joint.append(0);
	joint.append(0);
	joint.append(0);
	joint.append(0);
	joint.append(0);
	joint.append(-5);
	//相对坐标运动
	emit Write(joint_move(joint, 10, 1));
}
/*************************************************************************************************************************************************
**Function:父类私有的写数据方法
*************************************************************************************************************************************************/
void c_Jaka_Remote::Write(QJsonObject json)
{
	if (m_Writing){
		return;
	}
	m_Writing = true;
	QEventLoop *Write_Loop = new QEventLoop;
	QObject::connect(this, &c_Jaka_Remote::Write_Json_Done, Write_Loop, &QEventLoop::quit);
	QObject::connect(this, &c_Jaka_Remote::Set_Default, Write_Loop, &QEventLoop::quit);
	QString cmdName = json.value("cmdName").toString();
	emit Write_Json(json);
	Write_Loop->exec();
	emit Status(cmdName + "指令校验完成");
	m_Writing = false;
}
/*************************************************************************************************************************************************
**Function:父类私有的写反馈校验
** errorCode               errorMsg                           Description
**    0                   返回消息为空                       指令执行成功
**    1           Exception:function call failed             程序发生异常
**    2                 返回具体的错误消息                     错误信息
*************************************************************************************************************************************************/
void c_Jaka_Remote::Read_Json_Done(QJsonObject json)
{
	QString cmdName = json.value("cmdName").toString();
	QString errorCode = json.value("errorCode").toString();
	QString errorMsg = json.value("errorMsg").toString();
	emit Status(cmdName + "指令校验开始");
	if (errorCode == "0") {
		emit Status(cmdName + "指令执行成功");
		emit Write_Json_Done();
	}
	if (errorCode == "1") {
		emit Status(cmdName + "发送失败，程序发生异常,请断开设备重新连接");
		emit Write_Json_Error();
		emit setEnabled(false);
	}
	if (errorCode == "2") {
		emit Status(cmdName + "发送失败，错误信息：" + errorMsg + ",请断开设备重新连接");
		emit Write_Json_Error();
		emit setEnabled(false);
	}
}
/*************************************************************************************************************************************************
**Function:父类私有连接状态写入
*************************************************************************************************************************************************/
void c_Jaka_Remote::Connect_Done()
{
	m_Jaka_Remote_State.insert("Connected", true);
	emit Write_Jaka_Remote_State(m_Jaka_Remote_State);
}
void c_Jaka_Remote::Disconnect_Done()
{
	m_Jaka_Remote_State.insert("Connected", false);
	emit Write_Jaka_Remote_State(m_Jaka_Remote_State);
}
/*************************************************************************************************************************************************
**Function:父类私有写入旋转角指令
*************************************************************************************************************************************************/
QJsonObject c_Jaka_Remote::joint_move(QJsonArray joint, double spped, int relflag)
{
	QJsonObject object;
	object.insert("cmdName", "joint_move");
	object.insert("jointPosition", QJsonValue(joint));
	object.insert("10", spped);
	object.insert("relFlag", relflag);
	return object;
}

/*************************************************************************************************************************************************
**Function:构造函数(状态监视)
*************************************************************************************************************************************************/
c_Jaka_Monitor::c_Jaka_Monitor(QObject *parent) : QObject(parent)
{

}
/*************************************************************************************************************************************************
**Function:析构
*************************************************************************************************************************************************/
c_Jaka_Monitor::~c_Jaka_Monitor()
{
	//线程中断
	m_Jaka_Monitor_Thread->requestInterruption();
	//线程退出
	m_Jaka_Monitor_Thread->quit();
	//线程等待
	m_Jaka_Monitor_Thread->wait();
	//删除对象
	delete m_Jaka_Monitor;
}
/*************************************************************************************************************************************************
**Function:初始化接口
*************************************************************************************************************************************************/
void c_Jaka_Monitor::Init()
{
	//实例化
	m_Jaka_Monitor = new c_Jaka_Client;
	m_Jaka_Monitor_Thread = new QThread;
	m_Jaka_Monitor->moveToThread(m_Jaka_Monitor_Thread);
	//初始化数据交换层
	QObject::connect(m_Jaka_Monitor_Thread, &QThread::started, m_Jaka_Monitor, &c_Jaka_Client::Init);
	//连接设备
	QObject::connect(this, &c_Jaka_Monitor::Connect_Device, m_Jaka_Monitor, &c_Jaka_Client::Connect_Device);
	QObject::connect(this, &c_Jaka_Monitor::Disconnect_Device, m_Jaka_Monitor, &c_Jaka_Client::Disconnect_Device);
	//设备状态改变
	QObject::connect(m_Jaka_Monitor, &c_Jaka_Client::Connect_Done, this, &c_Jaka_Monitor::Set_Working);
	QObject::connect(m_Jaka_Monitor, &c_Jaka_Client::Disconnect_Done, this, &c_Jaka_Monitor::Set_Default);
	//键盘按键改变
	QObject::connect(this, &c_Jaka_Monitor::Set_Working, this, [=] {emit setEnabled(true); });
	QObject::connect(this, &c_Jaka_Monitor::Set_Default, this, [=] {emit setEnabled(false); });
	//向状态服务写入状态
	QObject::connect(m_Jaka_Monitor, &c_Jaka_Client::Connect_Done, this, &c_Jaka_Monitor::Connect_Done);
	QObject::connect(m_Jaka_Monitor, &c_Jaka_Client::Disconnect_Done, this, &c_Jaka_Monitor::Disconnect_Done);
	//写指令与校验
	QObject::connect(m_Jaka_Monitor, &c_Jaka_Client::Read_Json_Done, this, &c_Jaka_Monitor::Read_Json_Done);
	//提示信息
	QObject::connect(m_Jaka_Monitor, &c_Jaka_Client::Status, this, [=](int value) {emit Status(c_Variable::TCP_Status(value)); });
	//启动线程
	m_Jaka_Monitor_Thread->start();
	emit setEnabled(false);
}
/*************************************************************************************************************************************************
**Function:虚函数
*************************************************************************************************************************************************/
void c_Jaka_Monitor::Connect()
{
}
/*************************************************************************************************************************************************
**Function:父类私有的读状态函数，将状态量提取到公有成员变量
*************************************************************************************************************************************************/
void c_Jaka_Monitor::Read_Json_Done(QJsonObject json)
{
	m_Jaka_Monitor_State.insert("DB", json);
	emit Write_Jaka_Monitor_State(m_Jaka_Monitor_State);
	//机器人关节角度
	joint_actual_position = json.value("joint_actual_position").toArray();
	//机器人 tcp 的位姿
	actual_position = json.value("actual_position").toArray();
	//1 代表机器人下电 2 代表机器人上电 3 代表机器人下使能 4 代表机器人上使能
	task_state = json.value("task_state").toInt();
	//机器人被设置的 home 点位
	homed = json.value("homed").toArray();
	//机器人的任务模式 1 代表手动模式 2 代表自动模式 3 代表 MDI(面板操作)模式 4 代表拖拽模式
	task_mode = json.value("task_mode").toInt();
	//程序运行状态 0 代表空闲 1 代表正在加载 2 代表暂停 3 代表正在运行
	interp_state = json.value("interp_state").toInt();
	//机器人当前使用的工具 ID
	current_tool_id = json.value("current_tool_id").toInt();
	//值为 1 时代表机器人正处于急停状态
	protective_stop = json.value("protective_stop").toInt();
	//值为 1 时代表机器人正处于关节软限位
	on_soft_limit = json.value("on_soft_limit").toInt();
	//值为 1 时代表机器人正处于代表急停状态
	emergency_stop = json.value("emergency_stop").toInt();
	//值为 1 时代表机器人接近拖拽的极限位置
	drag_near_limit = json.value("drag_near_limit").toArray();
	if (m_Power_Monitor && task_state == 1) {
		emit Power_Off();
	}
	if (m_Power_Monitor && task_state == 2) {
		emit Power_On();
	}
	if (m_Power_Monitor && task_state == 3) {
		emit Enable_Robot();
	}
	if (m_Power_Monitor && task_state == 4) {
		emit Disable_Robot();
	}
	if (m_Joint_Monitor && Compare_position(joint_aim_position, joint_actual_position)) {
		emit Joint_Moved();
	}
}
/*************************************************************************************************************************************************
**Function:监控功能接口
*************************************************************************************************************************************************/
void c_Jaka_Monitor::Joint_Monitor(QJsonArray joint)
{
	m_Joint_Monitor = true;
	joint_aim_position = joint;
}
void c_Jaka_Monitor::Power_Monitor()
{
	m_Power_Monitor = true;
}
void c_Jaka_Monitor::Enable_Monitor()
{
	m_Able_Monitor = true;
}
/*************************************************************************************************************************************************
**Function:父类私有连接状态写入
*************************************************************************************************************************************************/
void c_Jaka_Monitor::Connect_Done()
{
	m_Jaka_Monitor_State.insert("Connected", true);
	emit Write_Jaka_Monitor_State(m_Jaka_Monitor_State);
}
void c_Jaka_Monitor::Disconnect_Done()
{
	m_Jaka_Monitor_State.insert("Connected", false);
	emit Write_Jaka_Monitor_State(m_Jaka_Monitor_State);
}
/*************************************************************************************************************************************************
**Function:父类私有关节角比较
*************************************************************************************************************************************************/
bool c_Jaka_Monitor::Compare_position(QJsonArray joint1, QJsonArray joint2)
{
	double a[6];
	double b[6];
	for (int i = 0; i < 6; i++)
	{
		a[i] = joint1.at(i).toDouble();
		b[i] = joint2.at(i + 1).toDouble();
	}
	bool arraysEqual = qFuzzyCompare(a[0], b[0]) && qFuzzyCompare(a[1], b[1]) && qFuzzyCompare(a[2], b[2]) && qFuzzyCompare(a[3], b[3]) && qFuzzyCompare(a[4], b[4]) && qFuzzyCompare(a[5], b[5]); // 标志变量
	return arraysEqual;
}

/*************************************************************************************************************************************************
**Function:构造函数
*************************************************************************************************************************************************/
c_Hypersen_Remote::c_Hypersen_Remote(QObject *parent) : QObject(parent)
{

}
/*************************************************************************************************************************************************
**Function:析构
*************************************************************************************************************************************************/
c_Hypersen_Remote::~c_Hypersen_Remote()
{
	//线程中断
	m_Hypersen_Remote_Thread->requestInterruption();
	//线程退出
	m_Hypersen_Remote_Thread->quit();
	//线程等待
	m_Hypersen_Remote_Thread->wait();
	//删除对象
	delete m_Hypersen_Remote;
}
/*************************************************************************************************************************************************
**Function:初始化接口
*************************************************************************************************************************************************/
void c_Hypersen_Remote::Init()
{
	//实例化
	m_Hypersen_Remote = new c_Hypersen_Client;
	m_Hypersen_Remote_Thread = new QThread;
	m_Hypersen_Remote->moveToThread(m_Hypersen_Remote_Thread);
	//初始化数据交换层
	QObject::connect(m_Hypersen_Remote_Thread, &QThread::started, m_Hypersen_Remote, &c_Hypersen_Client::Init);
	//连接设备
	QObject::connect(this, &c_Hypersen_Remote::Connect_Device, m_Hypersen_Remote, &c_Hypersen_Client::Connect_Device);
	QObject::connect(this, &c_Hypersen_Remote::Disconnect_Device, m_Hypersen_Remote, &c_Hypersen_Client::Disconnect_Device);
	//写数据
	QObject::connect(this, &c_Hypersen_Remote::Write, m_Hypersen_Remote, &c_Hypersen_Client::Write);
	//设备状态改变
	QObject::connect(m_Hypersen_Remote, &c_Hypersen_Client::Connect_Done, this, &c_Hypersen_Remote::Set_Working);
	QObject::connect(m_Hypersen_Remote, &c_Hypersen_Client::Disconnect_Done, this, &c_Hypersen_Remote::Set_Default);
	//键盘按键改变
	QObject::connect(this, &c_Hypersen_Remote::Set_Working, this, [=] {emit setEnabled(true); });
	QObject::connect(this, &c_Hypersen_Remote::Set_Default, this, [=] {emit setEnabled(false); });
	//读到消息
	QObject::connect(m_Hypersen_Remote, &c_Hypersen_Client::Read_Json_Done, this, &c_Hypersen_Remote::Read_Json_Done);
	//向状态服务写入状态
	QObject::connect(m_Hypersen_Remote, &c_Hypersen_Client::Connect_Done, this, &c_Hypersen_Remote::Connect_Done);
	QObject::connect(m_Hypersen_Remote, &c_Hypersen_Client::Disconnect_Done, this, &c_Hypersen_Remote::Disconnect_Done);
	//提示信息
	QObject::connect(m_Hypersen_Remote, &c_Hypersen_Client::Status, this, &c_Hypersen_Remote::Status);
	//启动线程
	m_Hypersen_Remote_Thread->start();
	emit setEnabled(false);
}
/*************************************************************************************************************************************************
**Function:虚函数
*************************************************************************************************************************************************/
void c_Hypersen_Remote::Connect()
{
}
/*************************************************************************************************************************************************
**Function:操作接口
*************************************************************************************************************************************************/
void c_Hypersen_Remote::Run_Single_Shot()
{
	emit Write(RUN_SINGLE_SHOT);
}
void c_Hypersen_Remote::Run_Continuous()
{
	emit Write(RUN_CONTINUOUS);
}
void c_Hypersen_Remote::Run_Idle()
{
	emit Write(RUN_IDLE);
}
/*************************************************************************************************************************************************
**Function:父类私有的读状态函数，将状态量提取到公有成员变量
*************************************************************************************************************************************************/
void c_Hypersen_Remote::Read_Json_Done(QJsonObject json)
{
	m_Hypersen_Remote_State.insert("DB", json);
	emit Write_Hypersen_Remote_State(m_Hypersen_Remote_State);
	m_roi_number = json.value("roi_number").toInt();
	for (int i = 0; i < m_roi_number; i++)
	{
		m_roi_aver_distance = json.value(QString::number(m_roi_number)).toArray().at(0).toInt();
		m_roi_max_distance = json.value(QString::number(m_roi_number)).toArray().at(1).toInt();
		m_roi_min_distance = json.value(QString::number(m_roi_number)).toArray().at(2).toInt();
		m_roi_valid_aver_amp = json.value(QString::number(m_roi_number)).toArray().at(3).toInt();
		m_roi_all_aver_amp = json.value(QString::number(m_roi_number)).toArray().at(4).toInt();
	}
}
/*************************************************************************************************************************************************
**Function:父类私有连接状态写入
*************************************************************************************************************************************************/
void c_Hypersen_Remote::Connect_Done()
{
	m_Hypersen_Remote_State.insert("Connected", true);
	emit Write_Hypersen_Remote_State(m_Hypersen_Remote_State);
}
void c_Hypersen_Remote::Disconnect_Done()
{
	m_Hypersen_Remote_State.insert("Connected", false);
	emit Write_Hypersen_Remote_State(m_Hypersen_Remote_State);
}

/*************************************************************************************************************************************************
**Function:构造函数(状态监视)
*************************************************************************************************************************************************/
c_Meijidenki_Remote::c_Meijidenki_Remote(QObject *parent) : QObject(parent)
{

}
/*************************************************************************************************************************************************
**Function:析构
*************************************************************************************************************************************************/
c_Meijidenki_Remote::~c_Meijidenki_Remote()
{
	//线程中断
	m_Meijidenki_Remote_Thread->requestInterruption();
	//线程退出
	m_Meijidenki_Remote_Thread->quit();
	//线程等待
	m_Meijidenki_Remote_Thread->wait();
	//删除对象
	delete m_Meijidenki_Remote;
}
/*************************************************************************************************************************************************
**Function:初始化接口
*************************************************************************************************************************************************/
void c_Meijidenki_Remote::Init()
{
	//实例化
	m_Meijidenki_Remote = new c_Meijidenki_Client;
	m_Meijidenki_Remote_Thread = new QThread;
	m_Meijidenki_Remote->moveToThread(m_Meijidenki_Remote_Thread);
	//初始化数据交换层
	QObject::connect(m_Meijidenki_Remote_Thread, &QThread::started, m_Meijidenki_Remote, &c_Meijidenki_Client::Init);
	//连接设备
	QObject::connect(this, &c_Meijidenki_Remote::Connect_Device, m_Meijidenki_Remote, &c_Meijidenki_Client::Connect_Device);
	QObject::connect(this, &c_Meijidenki_Remote::Disconnect_Device, m_Meijidenki_Remote, &c_Meijidenki_Client::Disconnect_Device);
	//写数据
	QObject::connect(this, &c_Meijidenki_Remote::Write, m_Meijidenki_Remote, &c_Meijidenki_Client::Write);
	//设备状态改变
	QObject::connect(m_Meijidenki_Remote, &c_Meijidenki_Client::Connect_Done, this, &c_Meijidenki_Remote::Set_Working);
	QObject::connect(m_Meijidenki_Remote, &c_Meijidenki_Client::Disconnect_Done, this, &c_Meijidenki_Remote::Set_Default);
	//键盘按键改变
	QObject::connect(this, &c_Meijidenki_Remote::Set_Working, this, [=] {emit setEnabled(true); });
	QObject::connect(this, &c_Meijidenki_Remote::Set_Default, this, [=] {emit setEnabled(false); });
	//读到消息
	QObject::connect(m_Meijidenki_Remote, &c_Meijidenki_Client::Read_Json_Done, this, &c_Meijidenki_Remote::Read_Json_Done);
	//向状态服务写入状态
	QObject::connect(m_Meijidenki_Remote, &c_Meijidenki_Client::Connect_Done, this, &c_Meijidenki_Remote::Connect_Done);
	QObject::connect(m_Meijidenki_Remote, &c_Meijidenki_Client::Disconnect_Done, this, &c_Meijidenki_Remote::Disconnect_Done);
	//提示信息
	QObject::connect(m_Meijidenki_Remote, &c_Meijidenki_Client::Status, this, &c_Meijidenki_Remote::Status);
	//启动线程
	m_Meijidenki_Remote_Thread->start();
	emit setEnabled(false);
}
/*************************************************************************************************************************************************
**Function:虚函数
*************************************************************************************************************************************************/
void c_Meijidenki_Remote::Connect()
{
}
/*************************************************************************************************************************************************
**Function:操作接口
*************************************************************************************************************************************************/
void c_Meijidenki_Remote::START_LMD()
{
	emit Write(LIM_CODE_START_LMD);
}
void c_Meijidenki_Remote::STOP_LMD()
{
	emit Write(LIM_CODE_STOP_LMD);
}
/*************************************************************************************************************************************************
**Function:父类私有的读状态函数，将状态量提取到公有成员变量
*************************************************************************************************************************************************/
void c_Meijidenki_Remote::Read_Json_Done(QJsonObject json)
{
	m_Meijidenki_Remote_State.insert("DB", json);
	emit Write_Meijidenki_Remote_State(m_Meijidenki_Remote_State);
}
/*************************************************************************************************************************************************
**Function:父类私有连接状态写入
*************************************************************************************************************************************************/
void c_Meijidenki_Remote::Connect_Done()
{
	m_Meijidenki_Remote_State.insert("Connected", true);
	emit Write_Meijidenki_Remote_State(m_Meijidenki_Remote_State);
}
void c_Meijidenki_Remote::Disconnect_Done()
{
	m_Meijidenki_Remote_State.insert("Connected", false);
	emit Write_Meijidenki_Remote_State(m_Meijidenki_Remote_State);
}




