#pragma execution_character_set("utf-8")
#include "Public_Header.h"
#include "Hypersen_Client.h"
#include "Jaka_Client.h"
#include "Meijidenki_Client.h"

/*************************************************************************************************************************************************
**Function:ȫ�ֱ�������
*************************************************************************************************************************************************/
QJsonObject c_Variable::g_Communicate_DB;
QJsonObject c_Variable::g_Robot_Teach_Widget_DB;
/*************************************************************************************************************************************************
**Function:ͨѶ������Ϣ
*************************************************************************************************************************************************/
QString c_Variable::TCP_Status(int State)
{
	switch (State)
	{
	case 0:
		return " ���ӱ��Եȷ��ܾ�����ʱ��";
	case 1:
		return " Զ�������ر������ӡ���ע�⣬�ͻ����׽��֣������׽��֣����ڷ���Զ�̹ر�֪ͨ��ر�";
	case 2:
		return " �Ҳ���������ַ";
	case 3:
		return " �׽��ֲ���ʧ�ܣ���ΪӦ�ó���ȱ�������Ȩ��";
	case 4:
		return " ����ϵͳ��Դ���㣨���磬�׽��ֹ��ࣩ";
	case 5:
		return " �׽��ֲ�����ʱ";
	case 6:
		return " ���ݱ����ڲ���ϵͳ�����ƣ��ɵ���8192�ֽڣ�";
	case 7:
		return " ���緢���������磬������������Σ�";
	case 8:
		return " ΪQAbstractSocket:��bind����ָ���ĵ�ַ����ʹ���У���������Ϊ��ռ";
	case 9:
		return " ΪQAbstractSocket:��bind����ָ���ĵ�ַ����������";
	case 10:
		return " ���ز���ϵͳ��֧��������׽��ֲ��������磬ȱ��IPv6֧�֣�";
	case 11:
		return " ����QAbstractSocketEngineʹ�ã��ϴγ��ԵĲ�����δ��ɣ����ں�̨���У�";
	case 12:
		return "�׽�������ʹ�ô���������Ҫ�����֤";
	case 13:
		return "SSL/TLS����ʧ�ܣ���������ѹرգ�����QSslSocket��ʹ�ã�";
	case 14:
		return "�޷���ϵ�������������Ϊ��÷����������ӱ��ܾ�";
	case 15:
		return "��������������������رգ��������նԵȷ���������֮ǰ��";
	case 16:
		return "���������������ӳ�ʱ�����ߴ���������������֤�׶�ֹͣ��Ӧ��";
	case 17:
		return "�Ҳ���ʹ��setProxy�������õĴ����ַ����Ӧ�ó������";
	case 18:
		return "����������������Э��ʧ�ܣ���Ϊ�޷�������Դ������������Ӧ";
	case 19:
		return "���׽��ִ��ڲ������״̬ʱ��������һ������";
	case 20:
		return "����ʹ�õ�SSL�ⱨ����һ���ڲ���������������ڿ�İ�װ��������ô�����ɵ�";
	case 21:
		return "�ṩ����Ч���ݣ�֤�顢��Կ������ȣ�����ʹ�õ���SSL���г��ִ���";
	case 22:
		return "������ʱ�������磬���������������׽���Ϊ��������";
	case 23:
		return "�׽���δ����";
	case 24:
		return "�׽�������ִ������������";
	case 25:
		return "�׽����ѿ�ʼ��������";
	case 26:
		return "������һ������";
	case 27:
		return "�׽��ְ󶨵�һ����ַ�Ͷ˿�";
	case 28:
		return "�׽��ּ����رգ����ݿ������ڵȴ�д�룩";
	case 29:
		return "�׽��ּ���״̬�������ڲ�ʹ�ã�";
	case -1:
		return "������һ���޷�ʶ��Ĵ���";
	default:
		return "��״̬";
	}
}
QString c_Variable::Modbus_Status(int State)
{
	switch (State)
	{
	case 0:
		return "������";
	case 1:
		return "��ȡ�����ڼ䷢������";
	case 2:
		return "д������ڼ䷢������";
	case 3:
		return ":���Դ򿪺��ʱ����";
	case 4:
		return ":�����������ò���ʱ����";
	case 5:
		return ":I/O�ڼ䷢����ʱ��I/O����δ�ڸ�����ʱ�䷶Χ�����";
	case 6:
		return "����Modbus�ض�Э�����";
	case 7:
		return "�����豸�Ͽ����ӣ��ظ�����ֹ";
	case 8:
		return "����δ֪����";
	case 9:
		return "�豸�ѶϿ�����";
	case 10:
		return "���������豸";
	case 11:
		return "�豸���ڹر�";
	default:
		return "��״̬";
	}
}
/*************************************************************************************************************************************************
**Function:��������ʱ
*************************************************************************************************************************************************/
bool c_Variable::msleep(const int mSec)
{
	QEventLoop *loop = new QEventLoop;
	QTimer::singleShot(mSec, loop, &QEventLoop::quit);
	loop->exec();
	return true;
}
/*************************************************************************************************************************************************
**Function:���캯��
*************************************************************************************************************************************************/
c_Variable::c_Variable(QObject *parent) : QObject(parent)
{
	/*************************************************************************************************************************************************
	**Function:��ȡͨѶ����
	*************************************************************************************************************************************************/
	Communicate_DB.setFileName(QDir::currentPath() + "/System_DB/Communicate_DB.json");
	Communicate_DB.open(QFile::ReadOnly | QIODevice::Text);
	QByteArray Data = Communicate_DB.readAll();
	Communicate_DB.close();
	QJsonDocument DB_Doc(QJsonDocument::fromJson(Data));
	g_Communicate_DB = DB_Doc.object();
}
/*************************************************************************************************************************************************
**Function:��������
*************************************************************************************************************************************************/
c_Variable::~c_Variable()
{
	/*************************************************************************************************************************************************
	**Function:�޸�ͨѶ���������ļ�
	*************************************************************************************************************************************************/
	Communicate_DB.open(QFile::WriteOnly | QIODevice::Text);
	QJsonDocument DB_Doc;
	DB_Doc.setObject(g_Communicate_DB);
	Communicate_DB.write(DB_Doc.toJson());
	Communicate_DB.close();
}

/*************************************************************************************************************************************************
**Function:ָ�������״�Ļص�������ȫ��ָ��
*************************************************************************************************************************************************/
c_Hypersen_CallBack *c_Hypersen_CallBack::g_Hypersen_CallBack = new c_Hypersen_CallBack;
/*************************************************************************************************************************************************
**Function:���캯��
*************************************************************************************************************************************************/
c_Hypersen_CallBack::c_Hypersen_CallBack(QObject * parent) : QObject(parent)
{
}
/*************************************************************************************************************************************************
**Function:����ָ��
*************************************************************************************************************************************************/
c_Hypersen_CallBack::~c_Hypersen_CallBack()
{
	g_Hypersen_CallBack = NULL;
	delete g_Hypersen_CallBack;
}
/*************************************************************************************************************************************************
**Function:״̬�ص�
*************************************************************************************************************************************************/
void c_Hypersen_CallBack::Hypersen_DebugFunc(char *str, void *contex)
{
	emit g_Hypersen_CallBack->State_Changed(QString(str));
}
/*************************************************************************************************************************************************
**Function:�¼��ص�
*************************************************************************************************************************************************/
void c_Hypersen_CallBack::Hypersen_OutputEventFunc(uint8_t out_id, uint8_t event, void *contex)
{
	//������¼������Ի�ȡÿ��ROI�������ѧͳ����Ϣ
	if (event == EVENT_ROISIMPLEDISTANCERECVD)
	{
		//��ȡָ��ROI�������Ϣǰ����Ҫͨ��ROI�����ӿڣ���ȡ��ǰ�����ROI��Ϣ�����м���ROI��ROI��ID�ȣ�
		emit  g_Hypersen_CallBack->ReadReady(out_id);
	}
	else if (event == EVENT_DEVDISCONNECT) {
		//�Ͽ����ӣ�������Դ
		HPS3D_DisConnect(out_id);
	}
}

/*************************************************************************************************************************************************
**Function:ָ�������״�Ļص�������ȫ��ָ��
*************************************************************************************************************************************************/
c_Meijidenki_CallBack *c_Meijidenki_CallBack::g_Meijidenki_CallBack = new c_Meijidenki_CallBack;
/*************************************************************************************************************************************************
**Function:���캯��
*************************************************************************************************************************************************/
c_Meijidenki_CallBack::c_Meijidenki_CallBack(QObject * parent) : QObject(parent)
{
	g_Meijidenki_CallBack = this;
}
/*************************************************************************************************************************************************
**Function:����ָ��
*************************************************************************************************************************************************/
c_Meijidenki_CallBack::~c_Meijidenki_CallBack()
{
	g_Meijidenki_CallBack = NULL;
	delete g_Meijidenki_CallBack;
}
/*************************************************************************************************************************************************
**Function:״̬�ص�
*************************************************************************************************************************************************/
void CALLBACK c_Meijidenki_CallBack::EqCommStateCallBack(int _cid, unsigned int _state_code, char* _ip, int _port, int _paddr)
{
	emit g_Meijidenki_CallBack->State_Changed(_cid, _state_code);
}
/*************************************************************************************************************************************************
**Function:���ݻص�
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
**Function:��Ϣ����
*************************************************************************************************************************************************/
QVariant c_Meijidenki_CallBack::Meijidenki_DB()
{
	QVariant varData_DB;
	varData_DB.setValue(m_Meijidenki_DB);
	return varData_DB;
}

/*************************************************************************************************************************************************
**Function:���캯��(����ָ��)
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
**Function:����
*************************************************************************************************************************************************/
c_Jaka_Remote::~c_Jaka_Remote()
{
	//�߳��ж�
	m_Jaka_Remote_Thread->requestInterruption();
	//�߳��˳�
	m_Jaka_Remote_Thread->quit();
	//�̵߳ȴ�
	m_Jaka_Remote_Thread->wait();
	//ɾ������
	delete m_Jaka_Remote;
}
/*************************************************************************************************************************************************
**Function:��ʼ���ӿ�
*************************************************************************************************************************************************/
void c_Jaka_Remote::Init()
{
	//ʵ����
	m_Jaka_Remote = new c_Jaka_Client;
	m_Jaka_Remote_Thread = new QThread;
	m_Jaka_Remote->moveToThread(m_Jaka_Remote_Thread);
	//��ʼ�����ݽ�����
	QObject::connect(m_Jaka_Remote_Thread, &QThread::started, m_Jaka_Remote, &c_Jaka_Client::Init);
	//�����豸
	QObject::connect(this, &c_Jaka_Remote::Connect_Device, m_Jaka_Remote, &c_Jaka_Client::Connect_Device);
	QObject::connect(this, &c_Jaka_Remote::Disconnect_Device, m_Jaka_Remote, &c_Jaka_Client::Disconnect_Device);
	//�豸״̬�ı�
	QObject::connect(m_Jaka_Remote, &c_Jaka_Client::Connect_Done, this, &c_Jaka_Remote::Set_Working);
	QObject::connect(m_Jaka_Remote, &c_Jaka_Client::Disconnect_Done, this, &c_Jaka_Remote::Set_Default);
	//���̰����ı�
	QObject::connect(this, &c_Jaka_Remote::Set_Working, this, [=] {emit setEnabled(true); });
	QObject::connect(this, &c_Jaka_Remote::Set_Default, this, [=] {emit setEnabled(false); });
	//��״̬����д��״̬
	QObject::connect(m_Jaka_Remote, &c_Jaka_Client::Connect_Done, this, &c_Jaka_Remote::Connect_Done);
	QObject::connect(m_Jaka_Remote, &c_Jaka_Client::Disconnect_Done, this, &c_Jaka_Remote::Disconnect_Done);
	//дָ����У��
	QObject::connect(this, &c_Jaka_Remote::Write_Json, m_Jaka_Remote, &c_Jaka_Client::Write_Json);
	QObject::connect(m_Jaka_Remote, &c_Jaka_Client::Read_Json_Done, this, &c_Jaka_Remote::Read_Json_Done);
	//��ʾ��Ϣ
	QObject::connect(m_Jaka_Remote, &c_Jaka_Client::Status, this, [=](int value) {emit Status(c_Variable::TCP_Status(value)); });
	//�����߳�
	m_Jaka_Remote_Thread->start();
	emit setEnabled(false);
}
/*************************************************************************************************************************************************
**Function:�麯��
*************************************************************************************************************************************************/
void c_Jaka_Remote::Connect()
{
}
/*************************************************************************************************************************************************
**Function:���๫��ң�ط����ӿ�
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
	//��������˶�
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
	//��������˶�
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
	//��������˶�
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
	//��������˶�
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
	//��������˶�
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
	//��������˶�
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
	//��������˶�
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
	//��������˶�
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
	//��������˶�
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
	//��������˶�
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
	//��������˶�
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
	//��������˶�
	emit Write(joint_move(joint, 10, 1));
}
/*************************************************************************************************************************************************
**Function:����˽�е�д���ݷ���
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
	emit Status(cmdName + "ָ��У�����");
	m_Writing = false;
}
/*************************************************************************************************************************************************
**Function:����˽�е�д����У��
** errorCode               errorMsg                           Description
**    0                   ������ϢΪ��                       ָ��ִ�гɹ�
**    1           Exception:function call failed             �������쳣
**    2                 ���ؾ���Ĵ�����Ϣ                     ������Ϣ
*************************************************************************************************************************************************/
void c_Jaka_Remote::Read_Json_Done(QJsonObject json)
{
	QString cmdName = json.value("cmdName").toString();
	QString errorCode = json.value("errorCode").toString();
	QString errorMsg = json.value("errorMsg").toString();
	emit Status(cmdName + "ָ��У�鿪ʼ");
	if (errorCode == "0") {
		emit Status(cmdName + "ָ��ִ�гɹ�");
		emit Write_Json_Done();
	}
	if (errorCode == "1") {
		emit Status(cmdName + "����ʧ�ܣ��������쳣,��Ͽ��豸��������");
		emit Write_Json_Error();
		emit setEnabled(false);
	}
	if (errorCode == "2") {
		emit Status(cmdName + "����ʧ�ܣ�������Ϣ��" + errorMsg + ",��Ͽ��豸��������");
		emit Write_Json_Error();
		emit setEnabled(false);
	}
}
/*************************************************************************************************************************************************
**Function:����˽������״̬д��
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
**Function:����˽��д����ת��ָ��
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
**Function:���캯��(״̬����)
*************************************************************************************************************************************************/
c_Jaka_Monitor::c_Jaka_Monitor(QObject *parent) : QObject(parent)
{

}
/*************************************************************************************************************************************************
**Function:����
*************************************************************************************************************************************************/
c_Jaka_Monitor::~c_Jaka_Monitor()
{
	//�߳��ж�
	m_Jaka_Monitor_Thread->requestInterruption();
	//�߳��˳�
	m_Jaka_Monitor_Thread->quit();
	//�̵߳ȴ�
	m_Jaka_Monitor_Thread->wait();
	//ɾ������
	delete m_Jaka_Monitor;
}
/*************************************************************************************************************************************************
**Function:��ʼ���ӿ�
*************************************************************************************************************************************************/
void c_Jaka_Monitor::Init()
{
	//ʵ����
	m_Jaka_Monitor = new c_Jaka_Client;
	m_Jaka_Monitor_Thread = new QThread;
	m_Jaka_Monitor->moveToThread(m_Jaka_Monitor_Thread);
	//��ʼ�����ݽ�����
	QObject::connect(m_Jaka_Monitor_Thread, &QThread::started, m_Jaka_Monitor, &c_Jaka_Client::Init);
	//�����豸
	QObject::connect(this, &c_Jaka_Monitor::Connect_Device, m_Jaka_Monitor, &c_Jaka_Client::Connect_Device);
	QObject::connect(this, &c_Jaka_Monitor::Disconnect_Device, m_Jaka_Monitor, &c_Jaka_Client::Disconnect_Device);
	//�豸״̬�ı�
	QObject::connect(m_Jaka_Monitor, &c_Jaka_Client::Connect_Done, this, &c_Jaka_Monitor::Set_Working);
	QObject::connect(m_Jaka_Monitor, &c_Jaka_Client::Disconnect_Done, this, &c_Jaka_Monitor::Set_Default);
	//���̰����ı�
	QObject::connect(this, &c_Jaka_Monitor::Set_Working, this, [=] {emit setEnabled(true); });
	QObject::connect(this, &c_Jaka_Monitor::Set_Default, this, [=] {emit setEnabled(false); });
	//��״̬����д��״̬
	QObject::connect(m_Jaka_Monitor, &c_Jaka_Client::Connect_Done, this, &c_Jaka_Monitor::Connect_Done);
	QObject::connect(m_Jaka_Monitor, &c_Jaka_Client::Disconnect_Done, this, &c_Jaka_Monitor::Disconnect_Done);
	//дָ����У��
	QObject::connect(m_Jaka_Monitor, &c_Jaka_Client::Read_Json_Done, this, &c_Jaka_Monitor::Read_Json_Done);
	//��ʾ��Ϣ
	QObject::connect(m_Jaka_Monitor, &c_Jaka_Client::Status, this, [=](int value) {emit Status(c_Variable::TCP_Status(value)); });
	//�����߳�
	m_Jaka_Monitor_Thread->start();
	emit setEnabled(false);
}
/*************************************************************************************************************************************************
**Function:�麯��
*************************************************************************************************************************************************/
void c_Jaka_Monitor::Connect()
{
}
/*************************************************************************************************************************************************
**Function:����˽�еĶ�״̬��������״̬����ȡ�����г�Ա����
*************************************************************************************************************************************************/
void c_Jaka_Monitor::Read_Json_Done(QJsonObject json)
{
	m_Jaka_Monitor_State.insert("DB", json);
	emit Write_Jaka_Monitor_State(m_Jaka_Monitor_State);
	//�����˹ؽڽǶ�
	joint_actual_position = json.value("joint_actual_position").toArray();
	//������ tcp ��λ��
	actual_position = json.value("actual_position").toArray();
	//1 ����������µ� 2 ����������ϵ� 3 �����������ʹ�� 4 �����������ʹ��
	task_state = json.value("task_state").toInt();
	//�����˱����õ� home ��λ
	homed = json.value("homed").toArray();
	//�����˵�����ģʽ 1 �����ֶ�ģʽ 2 �����Զ�ģʽ 3 ���� MDI(������)ģʽ 4 ������קģʽ
	task_mode = json.value("task_mode").toInt();
	//��������״̬ 0 ������� 1 �������ڼ��� 2 ������ͣ 3 ������������
	interp_state = json.value("interp_state").toInt();
	//�����˵�ǰʹ�õĹ��� ID
	current_tool_id = json.value("current_tool_id").toInt();
	//ֵΪ 1 ʱ��������������ڼ�ͣ״̬
	protective_stop = json.value("protective_stop").toInt();
	//ֵΪ 1 ʱ��������������ڹؽ�����λ
	on_soft_limit = json.value("on_soft_limit").toInt();
	//ֵΪ 1 ʱ��������������ڴ���ͣ״̬
	emergency_stop = json.value("emergency_stop").toInt();
	//ֵΪ 1 ʱ��������˽ӽ���ק�ļ���λ��
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
**Function:��ع��ܽӿ�
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
**Function:����˽������״̬д��
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
**Function:����˽�йؽڽǱȽ�
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
	bool arraysEqual = qFuzzyCompare(a[0], b[0]) && qFuzzyCompare(a[1], b[1]) && qFuzzyCompare(a[2], b[2]) && qFuzzyCompare(a[3], b[3]) && qFuzzyCompare(a[4], b[4]) && qFuzzyCompare(a[5], b[5]); // ��־����
	return arraysEqual;
}

/*************************************************************************************************************************************************
**Function:���캯��
*************************************************************************************************************************************************/
c_Hypersen_Remote::c_Hypersen_Remote(QObject *parent) : QObject(parent)
{

}
/*************************************************************************************************************************************************
**Function:����
*************************************************************************************************************************************************/
c_Hypersen_Remote::~c_Hypersen_Remote()
{
	//�߳��ж�
	m_Hypersen_Remote_Thread->requestInterruption();
	//�߳��˳�
	m_Hypersen_Remote_Thread->quit();
	//�̵߳ȴ�
	m_Hypersen_Remote_Thread->wait();
	//ɾ������
	delete m_Hypersen_Remote;
}
/*************************************************************************************************************************************************
**Function:��ʼ���ӿ�
*************************************************************************************************************************************************/
void c_Hypersen_Remote::Init()
{
	//ʵ����
	m_Hypersen_Remote = new c_Hypersen_Client;
	m_Hypersen_Remote_Thread = new QThread;
	m_Hypersen_Remote->moveToThread(m_Hypersen_Remote_Thread);
	//��ʼ�����ݽ�����
	QObject::connect(m_Hypersen_Remote_Thread, &QThread::started, m_Hypersen_Remote, &c_Hypersen_Client::Init);
	//�����豸
	QObject::connect(this, &c_Hypersen_Remote::Connect_Device, m_Hypersen_Remote, &c_Hypersen_Client::Connect_Device);
	QObject::connect(this, &c_Hypersen_Remote::Disconnect_Device, m_Hypersen_Remote, &c_Hypersen_Client::Disconnect_Device);
	//д����
	QObject::connect(this, &c_Hypersen_Remote::Write, m_Hypersen_Remote, &c_Hypersen_Client::Write);
	//�豸״̬�ı�
	QObject::connect(m_Hypersen_Remote, &c_Hypersen_Client::Connect_Done, this, &c_Hypersen_Remote::Set_Working);
	QObject::connect(m_Hypersen_Remote, &c_Hypersen_Client::Disconnect_Done, this, &c_Hypersen_Remote::Set_Default);
	//���̰����ı�
	QObject::connect(this, &c_Hypersen_Remote::Set_Working, this, [=] {emit setEnabled(true); });
	QObject::connect(this, &c_Hypersen_Remote::Set_Default, this, [=] {emit setEnabled(false); });
	//������Ϣ
	QObject::connect(m_Hypersen_Remote, &c_Hypersen_Client::Read_Json_Done, this, &c_Hypersen_Remote::Read_Json_Done);
	//��״̬����д��״̬
	QObject::connect(m_Hypersen_Remote, &c_Hypersen_Client::Connect_Done, this, &c_Hypersen_Remote::Connect_Done);
	QObject::connect(m_Hypersen_Remote, &c_Hypersen_Client::Disconnect_Done, this, &c_Hypersen_Remote::Disconnect_Done);
	//��ʾ��Ϣ
	QObject::connect(m_Hypersen_Remote, &c_Hypersen_Client::Status, this, &c_Hypersen_Remote::Status);
	//�����߳�
	m_Hypersen_Remote_Thread->start();
	emit setEnabled(false);
}
/*************************************************************************************************************************************************
**Function:�麯��
*************************************************************************************************************************************************/
void c_Hypersen_Remote::Connect()
{
}
/*************************************************************************************************************************************************
**Function:�����ӿ�
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
**Function:����˽�еĶ�״̬��������״̬����ȡ�����г�Ա����
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
**Function:����˽������״̬д��
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
**Function:���캯��(״̬����)
*************************************************************************************************************************************************/
c_Meijidenki_Remote::c_Meijidenki_Remote(QObject *parent) : QObject(parent)
{

}
/*************************************************************************************************************************************************
**Function:����
*************************************************************************************************************************************************/
c_Meijidenki_Remote::~c_Meijidenki_Remote()
{
	//�߳��ж�
	m_Meijidenki_Remote_Thread->requestInterruption();
	//�߳��˳�
	m_Meijidenki_Remote_Thread->quit();
	//�̵߳ȴ�
	m_Meijidenki_Remote_Thread->wait();
	//ɾ������
	delete m_Meijidenki_Remote;
}
/*************************************************************************************************************************************************
**Function:��ʼ���ӿ�
*************************************************************************************************************************************************/
void c_Meijidenki_Remote::Init()
{
	//ʵ����
	m_Meijidenki_Remote = new c_Meijidenki_Client;
	m_Meijidenki_Remote_Thread = new QThread;
	m_Meijidenki_Remote->moveToThread(m_Meijidenki_Remote_Thread);
	//��ʼ�����ݽ�����
	QObject::connect(m_Meijidenki_Remote_Thread, &QThread::started, m_Meijidenki_Remote, &c_Meijidenki_Client::Init);
	//�����豸
	QObject::connect(this, &c_Meijidenki_Remote::Connect_Device, m_Meijidenki_Remote, &c_Meijidenki_Client::Connect_Device);
	QObject::connect(this, &c_Meijidenki_Remote::Disconnect_Device, m_Meijidenki_Remote, &c_Meijidenki_Client::Disconnect_Device);
	//д����
	QObject::connect(this, &c_Meijidenki_Remote::Write, m_Meijidenki_Remote, &c_Meijidenki_Client::Write);
	//�豸״̬�ı�
	QObject::connect(m_Meijidenki_Remote, &c_Meijidenki_Client::Connect_Done, this, &c_Meijidenki_Remote::Set_Working);
	QObject::connect(m_Meijidenki_Remote, &c_Meijidenki_Client::Disconnect_Done, this, &c_Meijidenki_Remote::Set_Default);
	//���̰����ı�
	QObject::connect(this, &c_Meijidenki_Remote::Set_Working, this, [=] {emit setEnabled(true); });
	QObject::connect(this, &c_Meijidenki_Remote::Set_Default, this, [=] {emit setEnabled(false); });
	//������Ϣ
	QObject::connect(m_Meijidenki_Remote, &c_Meijidenki_Client::Read_Json_Done, this, &c_Meijidenki_Remote::Read_Json_Done);
	//��״̬����д��״̬
	QObject::connect(m_Meijidenki_Remote, &c_Meijidenki_Client::Connect_Done, this, &c_Meijidenki_Remote::Connect_Done);
	QObject::connect(m_Meijidenki_Remote, &c_Meijidenki_Client::Disconnect_Done, this, &c_Meijidenki_Remote::Disconnect_Done);
	//��ʾ��Ϣ
	QObject::connect(m_Meijidenki_Remote, &c_Meijidenki_Client::Status, this, &c_Meijidenki_Remote::Status);
	//�����߳�
	m_Meijidenki_Remote_Thread->start();
	emit setEnabled(false);
}
/*************************************************************************************************************************************************
**Function:�麯��
*************************************************************************************************************************************************/
void c_Meijidenki_Remote::Connect()
{
}
/*************************************************************************************************************************************************
**Function:�����ӿ�
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
**Function:����˽�еĶ�״̬��������״̬����ȡ�����г�Ա����
*************************************************************************************************************************************************/
void c_Meijidenki_Remote::Read_Json_Done(QJsonObject json)
{
	m_Meijidenki_Remote_State.insert("DB", json);
	emit Write_Meijidenki_Remote_State(m_Meijidenki_Remote_State);
}
/*************************************************************************************************************************************************
**Function:����˽������״̬д��
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




