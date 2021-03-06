#pragma execution_character_set("utf-8")
#include "Hypersen_Client.h"

/*************************************************************************************************************************************************
**Function:    构造函数
**Description: 初始化成员变量
**Input:       无输入
**Output:      无输出
**Return:      无返回
**Others:      构造函数初始化在主线程实例化中完成，故在子线程中运行时，成员函数的初始化不能在构造函数中完成
*************************************************************************************************************************************************/
c_Hypersen_Client::c_Hypersen_Client(QObject *parent) : QObject(parent)
{

}
/*************************************************************************************************************************************************
**Function:    析构函数
**Description: 析构成员变量
**Input:       无输入
**Output:      无输出
**Return:      无返回
**Others:      析构成员变量后，再次操作时需要重新实例化
*************************************************************************************************************************************************/
c_Hypersen_Client::~c_Hypersen_Client()
{
	
}
/*************************************************************************************************************************************************
**Function:    初始化函数
**Description: 线程的构造函数
**Input:       无输入
**Output:      无输出
**Return:      无返回
**Others:
*************************************************************************************************************************************************/
void c_Hypersen_Client::Init()
{
	//如果，客户端，状态改变，执行，本线程，状态改变函数
	QObject::connect(c_Hypersen_CallBack::g_Hypersen_CallBack, &c_Hypersen_CallBack::State_Changed, this, &c_Hypersen_Client::State_Changed);
	//开启监听模式{机器人，有可读取通道，对象，读取信号}
	QObject::connect(c_Hypersen_CallBack::g_Hypersen_CallBack, &c_Hypersen_CallBack::ReadReady, this, &c_Hypersen_Client::Read_Json);
}
/*************************************************************************************************************************************************
**Function:    Connect_Device(QString ip, int port)
**Description: 连接tcpsocket服务器
**Input:       -> ip
               -> port
**Output:      ->connectDone    连接成功
               ->disconnectDone 断开成功

**Return:      无返回
**Others:      分六个步骤
*************************************************************************************************************************************************/
void c_Hypersen_Client::Connect_Device(QString ip, int port)
{
	uint8_t ret = 0;
	//第一步，设置Debug信息回调函数，用于打印错误信息
	//调试时使用，不需要可以不注册（可选）
	ret = HPS3D_SetDebugCallBack(c_Hypersen_CallBack::Hypersen_DebugFunc, NULL);
	if (ret != RET_OK){
		emit Status("DEBUG信息回调函数注册:..........失败");
		emit  Connect_Error();
		return;
	}
	else{
		emit Status("DEBUG信息回调函数注册:..........成功!");
	}
	//第二步，连接设备（必要），以下为设备的默认IP和端口号
	ret = HPS3D_ConnectByEthernet(ip.toLatin1().data(), port, &m_device_id);
	if (ret != RET_OK){
		emit Status("设备连接:..........失败!");
		emit  Connect_Error();
		return;
	}
	else{
		emit Status("设备连接:..........成功!");
	}
	//第三步，注册输出事件回调函数（必要）
	ret = HPS3D_SetOutputCallBack(c_Hypersen_CallBack::Hypersen_OutputEventFunc, m_device_id, NULL);
	if (ret != RET_OK){
		emit Status("输出事件回调函数注册:..........失败!");
		emit  Connect_Error();
		return;
	}
	else{
		emit Status("输出事件回调函数注册:..........成功!");
	}
	//第四步，关闭开门狗使能（可选）
	//调试时使用，调试完成后需要及时开启
	ret = HPS3D_SetWatchDogEnable(m_device_id, false);
	if (ret != RET_OK){
		emit Status("看门狗关闭:..........失败!");
		emit  Connect_Error();
		return;
	}
	else{
		emit Status("看门狗关闭:..........成功!");
	}
	//第五步,获取设备信息
	//查询设备信息
	ret = HPS3D_GetSDKVersion(m_sdk_version);
	if (ret != RET_OK) {
		emit Status("SDK版本信息获取:..........失败!");
		emit  Connect_Error();
		return;
	}
	else {
		emit Status(QString("SDK版本:20%1-%2-%3 V%4.%5.%6").arg(m_sdk_version[0]).arg(m_sdk_version[1]).arg(m_sdk_version[2]).arg(m_sdk_version[3]).arg(m_sdk_version[4]).arg(m_sdk_version[5]));
	}
	//获取设备版本前，需要确保设备已经正常连接
	ret = HPS3D_GetDeviceVersion(m_device_id, m_device_version);
	if (ret != RET_OK) {
		emit Status("设备版本信息获取:..........失败!");
		emit  Connect_Error();
		return;
	}
	else {
		emit Status(QString("设备版本:20%1-%2-%3 V%4.%5.%6").arg(m_device_version[0]).arg(m_device_version[1]).arg(m_device_version[2]).arg(m_device_version[3]).arg(m_device_version[4]).arg(m_device_version[5]));
	}
	//获取设备序列号前，需要确保设备已经正常连接
	ret = HPS3D_GetDeviceSN(m_device_id, m_SN);
	if (ret != RET_OK) {
		emit Status("设备序列号获取:..........失败!");
		emit  Connect_Error();
		return;
	}
	else {
		emit Status(QString("设备序列号:%1").arg(m_SN));
	}
	//第六步，设置设备输出类型（必要）
	ret = HPS3D_SetOutputDataType(m_device_id, OUTPUT_DISTANCE_SIMPLE);
	if (ret != RET_OK) {
		emit Status("设置ROI简单深度事件:..........失败!");
		emit  Connect_Error();
		return;
	}
	else {
		emit Status("设置ROI简单深度事件:..........成功!");
	}
	//如果没有开启ROI需要开启（ROI配置需要使用客户端）SDK仅提供ROI使能开关
	//以下开启ROI 0,注意如果没有使用客户端绘制ROI区域，设置ROi使能将无效
    ret = HPS3D_SetROIEnable(m_device_id, 1, true);
	if (ret != RET_OK) {
		emit Status("设置ROI简单深度事件:..........失败!");
		emit  Connect_Error();
		return;
	}
	else {
		emit Status("设置ROI简单深度事件:..........成功!");
	}
	if (ret == RET_OK){
		emit Connect_Done();
	}
}
/*************************************************************************************************************************************************
**Function:    Disconnect_Device()
**Description: 断开tcpsocket服务器
**Input:       无输入
**Output:      status
**Return:      无返回
**Others:      如果未连接，则会直接返回
*************************************************************************************************************************************************/
void c_Hypersen_Client::Disconnect_Device()
{
	uint8_t ret = 0;
	ret = HPS3D_DisConnect(m_device_id);
	if (ret != RET_OK) {
		emit Status("断开设备连接:..........失败!");
		emit  Disconnect_Error();
		return;
	}
	else {
		emit Status("断开设备连接:..........成功!");
		emit  Disconnect_Done();
	}
}
/*************************************************************************************************************************************************
**Function:    Read()
**Description: 读消息
**Input:      
**Output:      status、readError、readDone
**Return:      无返回
**Others:
*************************************************************************************************************************************************/
void c_Hypersen_Client::Read_Json(quint8 id)
{
	if (id != m_device_id){
		return;
	}
	uint8_t ret = 0;
	ret = HPS3D_GetOutRoiParam_CB(id, &m_group_id, &m_roi_number, m_roi_id);
	QJsonObject object;
	object.insert("roi_number", m_roi_number);
	//获取ROI数学统计信息
	for (int i = 0; i < m_roi_number; i++) {
		QJsonArray arry;
		ret = HPS3D_GetOutRoiAverageDistance_CB(id, m_roi_id[i], &m_roi_aver_distance);
		arry.append(m_roi_aver_distance);
		ret = HPS3D_GetOutRoiMaxDistance_CB(id, m_roi_id[i], &m_roi_max_distance);
		arry.append(m_roi_max_distance);
		ret = HPS3D_GetOutRoiMinDistance_CB(id, m_roi_id[i], &m_roi_min_distance);
		arry.append(m_roi_min_distance);
		ret = HPS3D_GetOutRoiAllAverAmplitude_CB(id, m_roi_id[i], &m_roi_all_aver_amp);
		arry.append(m_roi_all_aver_amp);
		ret = HPS3D_GetOutRoiValidAverAmplitude_CB(id, m_roi_id[i], &m_roi_valid_aver_amp);
		arry.append(m_roi_valid_aver_amp);
		object.insert(QString::number(i), arry);
	}
	if (ret == RET_OK){
		emit Read_Json_Done(object);
	}
	else{
		emit Read_Json_Error();
	}
}
/*************************************************************************************************************************************************
**Function:    Write(quint8 value)
**Description: 写消息
**Input:       QJsonObject value -> {"cmdName":"cmd","parameter1":"parameter1","parameter2":"parameter2",...}
**Output:      status、writeError、writeDone
**Return:      无返回
**Others:      无
*************************************************************************************************************************************************/
void c_Hypersen_Client::Write(quint8 value)
{
	uint8_t ret = 0;
	ret = HPS3D_SetRunMode(m_device_id, value);
	if(ret != RET_OK){
		emit Write_Error();
	}
	else {
		emit Write_Done();
	}
}
/*************************************************************************************************************************************************
**Function:    State_Changed(QString str)
**Description: 状态改变信号
**Input:
**Output:      
**Return:      
**Others:   有待开发
*************************************************************************************************************************************************/
void c_Hypersen_Client::State_Changed(QString str)
{
}
