#pragma execution_character_set("utf-8")
#include "Meijidenki_Client.h"
/*************************************************************************************************************************************************
**Function:    构造函数
**Description: 初始化成员变量
**Input:       无输入
**Output:      无输出
**Return:      无返回
**Others:      构造函数初始化在主线程实例化中完成，故在子线程中运行时，成员函数的初始化不能在构造函数中完成
*************************************************************************************************************************************************/
c_Meijidenki_Client::c_Meijidenki_Client(QObject *parent) : QObject(parent)
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
c_Meijidenki_Client::~c_Meijidenki_Client()
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
void c_Meijidenki_Client::Init()
{
	//如果，客户端，状态改变，执行，本线程，状态改变函数
	QObject::connect(c_Meijidenki_CallBack::g_Meijidenki_CallBack, &c_Meijidenki_CallBack::State_Changed, this, &c_Meijidenki_Client::State_Changed);
	//开启监听模式{机器人，有可读取通道，对象，读取信号}
	QObject::connect(c_Meijidenki_CallBack::g_Meijidenki_CallBack, &c_Meijidenki_CallBack::ReadReady, this, &c_Meijidenki_Client::Read_Json);
}
/*************************************************************************************************************************************************
**Function:    Connect_Device(QString ip, int port)
**Description: 连接tcpsocket服务器
**Input:       -> ip
               -> port
**Output:      ->connectDone    连接成功
               ->disconnectDone 断开成功
**Return:      无返回
**Others:      分二个步骤
*************************************************************************************************************************************************/
void c_Meijidenki_Client::Connect_Device(int id, QString ip, int port)
{
	//第一步，//获取SDK版本
	int m_device_id = id;
	int sdk_version = GetEquipmentCommVersion();
	emit Status(QString::number(sdk_version));
	//第二步，通讯库初始化
	if (EquipmentCommInit(NULL, c_Meijidenki_CallBack::EqCommDataCallBack, c_Meijidenki_CallBack::EqCommStateCallBack)) {
		emit Status("注册回调函数.................成功");
	}
	else {
		emit Status("注册回调函数.................失败");
	}
	if (!OpenEquipmentComm(id, ip.toLatin1().data(), port)) {
		emit Connect_Error();
		emit Status("连接设备.................失败");
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
void c_Meijidenki_Client::Disconnect_Device()
{
	if (!CloseEquipmentComm(m_device_id)) {
		emit Disconnect_Error();
		emit Status("断开设备连接:..........失败!");
		return;
	}
}
/*************************************************************************************************************************************************
**Function:    Read_Json()
**Description: 读消息
**Input:
**Output:      status、readError、readDone
**Return:      无返回
**Others:
*************************************************************************************************************************************************/
void c_Meijidenki_Client::Read_Json(QVariant db)
{
	s_Meijidenki_DB Meijidenki_DB = db.value<s_Meijidenki_DB>();
	if (Meijidenki_DB.cid != m_device_id) {
		return;
	}
	switch (Meijidenki_DB.lim->nCode)
	{
	case LIM_CODE_LDBCONFIG:
		m_Value.insert("LIM_CODE_LDBCONFIG", Meijidenki_LDBCONFIG_Decoding(Meijidenki_DB.lim));
		break;
	case LIM_CODE_LMD:
		m_Value.insert("LIM_CODE_LMD", Meijidenki_LMD_Decoding(Meijidenki_DB.lim));
		break;
	case LIM_CODE_LMD_RSSI:
		m_Value.insert("LIM_CODE_LMD_RSSI", Meijidenki_LMD_RSSI_Decoding(Meijidenki_DB.lim));
		break;
	case LIM_CODE_FMSIG:
		m_Value.insert("LIM_CODE_FMSIG", Meijidenki_FMSIG_Decoding(Meijidenki_DB.lim));
		break;
	case LIM_CODE_IOSTATUS:
		m_Value.insert("LIM_CODE_IOSTATUS", Meijidenki_IOSTATUS_Decoding(Meijidenki_DB.lim));
		break;
	case LIM_CODE_ALARM:
		emit Status(Meijidenki_ALARM_Decoding(Meijidenki_DB.lim));
		break;
	case LIM_CODE_DISALARM:
		emit Status(Meijidenki_DISALARM_Decoding(Meijidenki_DB.lim));
		break;
	default:
		emit Read_Json_Error();
		return;
	}
	emit Read_Json_Done(m_Value);
}
/*************************************************************************************************************************************************
**Function:    Write(quint32 code)
**Description: 写消息
**Input:       QJsonObject value -> {"cmdName":"cmd","parameter1":"parameter1","parameter2":"parameter2",...}
**Output:      status、writeError、writeDone
**Return:      无返回
**Others:      无
*************************************************************************************************************************************************/
void c_Meijidenki_Client::Write(quint32 code)
{
	LIM_HEAD* lim = NULL;
	//编辑报文
	LIM_Pack(lim, m_device_id, code, NULL); 
	//发送报文
	if(SendLIM(m_device_id, lim, lim->nLIMLen)) {
		emit Write_Done();
	} 
	else {
		emit Write_Error();
	}
}
/*************************************************************************************************************************************************
**Function:    State_Changed()
**Description: 连接状态改变
**Input:       无输入
**Output:      connectDone、disconnectDone、status
**Return:      无返回
**Others:     
*************************************************************************************************************************************************/
void c_Meijidenki_Client::State_Changed(qint32 _cid, quint32 _state_code)
{
	if (_cid == m_device_id && _state_code == EQCOMM_STATE_OK) {
		Write(LIM_CODE_GET_LDBCONFIG);
		emit Connect_Done();
		emit Status("连接设备.................成功");
	}
	if (_cid == m_device_id && _state_code == EQCOMM_STATE_ERR)
	{
		emit Connect_Error();
		emit Status("连接设备.................失败");
	}
	if (_cid == m_device_id && _state_code == EQCOMM_STATE_LOST) {
		emit  Disconnect_Done();
		emit Status("断开设备连接:..........成功!");
	}
}
/*************************************************************************************************************************************************
**Function:   Decoding(LIM_HEAD *lim)
**Description: 解析消息
**Input:       LIM_HEAD *lim 
**Output:      QJsonObject
**Return:      无返回
**Others:      无
*************************************************************************************************************************************************/
// LIM_CODE_LDBCONFIG LIM包解码
QJsonObject c_Meijidenki_Client::Meijidenki_LDBCONFIG_Decoding(LIM_HEAD *lim)
{
	QJsonObject object;
	ULDINI_Type *ldtype = (ULDINI_Type*)LIM_ExData(lim);
	object.insert("Type", QString(ldtype->szType));
	object.insert("Manufacturer", QString(ldtype->szManufacturer));
	object.insert("ReleaseDate", QString(ldtype->szReleaseDate));
	object.insert("SerialNo", QString(ldtype->szSerialNo));
	object.insert("szMAC", QString(ldtype->szMAC));
	object.insert("szIP", QString(ldtype->szIP));
	object.insert("szMask", QString(ldtype->szMask));
	object.insert("szGate", QString(ldtype->szGate));
	object.insert("szDNS", QString(ldtype->szDNS));
	object.insert("MR", ldtype->nMR);
	object.insert("ESAR", ldtype->nESAR);
	object.insert("ESA0", ldtype->nESA[0]);
	object.insert("ESA1", ldtype->nESA[1]);
	object.insert("SAR", ldtype->nSAR);
	object.insert("SA0", ldtype->nSA[0]);
	object.insert("SA1", ldtype->nSA[1]);
	object.insert("SAV", ldtype->nSAV);
	object.insert("SAP", ldtype->nSAP / 1000.);
	object.insert("PF", ldtype->nPF);
	return object;
}
// LIM_CODE_LMD LIM包解码
QJsonObject c_Meijidenki_Client::Meijidenki_LMD_Decoding(LIM_HEAD*lim)
{
	QJsonObject object;
	LMD_INFO* lmd_info = LMD_Info(lim);  // 获取LMD_INFO指针
	LMD_D_Type* lmd = LMD_D(lim);        // 获取LMD数据指针										
	object.insert("nRange", lmd_info->nRange / 100.);
	object.insert("nBAngle", lmd_info->nBAngle / 1000.);
	object.insert("nEAngle", lmd_info->nEAngle / 1000.);
	object.insert("nAnglePrecision", lmd_info->nAnglePrecision / 1000.);
	object.insert("nRPM", lmd_info->nRPM / 1.);
	object.insert("nMDataNum", lmd_info->nMDataNum / 1.);
	QJsonArray distance;
	for (int i = 0; i < lmd_info->nMDataNum; i++)
	{
		distance.append(lmd[i]);
	}
	object.insert("LMD_D", distance);
	return object;
}
// LIM_CODE_LMD_RSSI LIM包解码
QJsonObject c_Meijidenki_Client::Meijidenki_LMD_RSSI_Decoding(LIM_HEAD*lim)
{
	QJsonObject object;
	LMD_INFO* lmd_info = LMD_Info(lim);  //获取LMD_INFO指针
	LMD_D_Type* lmd = LMD_D(lim);        //获取LMD数据指针
	LMD_D_RSSI_Type *lmdrssi = LMD_D_RSSI(lim);//获取RSSI数据指针
	//打印LMD_INFO
	object.insert("nRange", lmd_info->nRange / 100.);
	object.insert("nBAngle", lmd_info->nBAngle / 1000.);
	object.insert("nEAngle", lmd_info->nEAngle / 1000.);
	object.insert("nAnglePrecision", lmd_info->nAnglePrecision / 1000.);
	object.insert("nRPM", lmd_info->nRPM / 1.);
	object.insert("nMDataNum", lmd_info->nMDataNum / 1.);
	return object;
}
// LIM_CODE_FMSIG LIM包解码
QJsonObject c_Meijidenki_Client::Meijidenki_FMSIG_Decoding(LIM_HEAD*lim)
{
	QJsonObject object;
	int fieldIdx;
	int alm;
	int attentionW, attentionA;
	int alertW, alertA;
	int alarmW, alarmA;

	fieldIdx = lim->Data[0];
	alm = lim->Data[1];

	alarmA = (alm & 0x01);
	alarmW = (alm & 0x02) >> 1;
	alertA = (alm & 0x04) >> 2;
	alertW = (alm & 0x08) >> 3;
	attentionA = (alm & 0x10) >> 4;
	attentionW = (alm & 0x20) >> 5;

	object.insert("fieldIdx", fieldIdx);
	object.insert("alarmA", alarmA);
	object.insert("alertA", alertA);
	object.insert("attentionA", attentionA);
	object.insert("alarmW", alarmW);
	object.insert("alertW", alertW);
	object.insert("attentionW", attentionW);
	return object;
}
// LIM_CODE_IOSTATUS LIM包解码
QJsonObject c_Meijidenki_Client::Meijidenki_IOSTATUS_Decoding(LIM_HEAD*lim)
{
	QJsonObject object;
	int iosts = lim->Data[0];

	QJsonArray IO_OutSts;
	QJsonArray IO_InSts;

	for (int i = 0; i < IO_OUTNUM; i++)
	{
		int arry = ((iosts & (1 << i)) >> i);
		IO_OutSts.append(arry);
	}
		
	for (int i = IO_OUTNUM; i < IO_OUTNUM + IO_INNUM; i++)
	{
		int arry = ((iosts & (1 << i)) >> i);
		IO_InSts.append(arry);
	}
	
	object.insert("IO_OutSts", IO_OutSts);
	object.insert("IO_InSts", IO_InSts);

	return object;
}
// LIM_CODE_ALARM LIM包解码
QString c_Meijidenki_Client::Meijidenki_ALARM_Decoding(LIM_HEAD*lim)
{
	QString str;
	switch (lim->Data[0]) {
	case LIM_DATA_ALARMCODE_INTERNAL:
		str = "内部错误";
		break;
	case LIM_DATA_ALARMCODE_Occluded:
		str = "设备出光面被遮挡或者透过罩太脏";
		break;
	case LIM_DATA_ALARMCODE_High_Temperature:
		str = "高温报警";
		break;
	case LIM_DATA_ALARMCODE_Low_Temperature:
		str = "低温报警";
		break;
	default:
		str = "未知错误";
		break;
	}
	return str;
}
// LIM_CODE_DISALARM LIM包解码
QString c_Meijidenki_Client::Meijidenki_DISALARM_Decoding(LIM_HEAD*lim)
{
	QString str;
	switch (lim->Data[0]) {
	case LIM_DATA_ALARMCODE_INTERNAL:
		str = "内部错误解除";
		break;
	case LIM_DATA_ALARMCODE_Occluded:
		str = "设备出光面被遮挡或者透过罩太脏解除";
		break;
	case LIM_DATA_ALARMCODE_High_Temperature:
		str = "高温报警解除";
		break;
	case LIM_DATA_ALARMCODE_Low_Temperature:
		str = "低温报警解除";
		break;
	default:
		str = "未知错误解除";
		break;
	}
	return str;
}



