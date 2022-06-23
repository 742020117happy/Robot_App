#pragma execution_character_set("utf-8")
#include "System_Time.h"
/*************************************************************************************************************************************************
**Function:默认构造函数
*************************************************************************************************************************************************/
c_System_Time::c_System_Time(QObject *parent) : QObject(parent){}
/*************************************************************************************************************************************************
**Function:析构操作对象
*************************************************************************************************************************************************/
c_System_Time::~c_System_Time()
{
    m_System_Time->stop();
    m_System_Time->deleteLater();
}
/*************************************************************************************************************************************************
**Function:线程初始化
*************************************************************************************************************************************************/
void c_System_Time::Init()
{
    m_System_Time = new QTimer;
	QObject::connect(m_System_Time, &QTimer::timeout, this, &c_System_Time::System_Time);
    m_System_Time->start(100);
}
/*************************************************************************************************************************************************
**Function:线程执行函数
*************************************************************************************************************************************************/
void c_System_Time::System_Time()
{
    QDateTime Date_Time = QDateTime::currentDateTime();
    QString Current_Date_Time = Date_Time.toString("yyyy-MM-dd-hh-mm-ss");
    emit Write_System_Time(Current_Date_Time);
}

/*************************************************************************************************************************************************
**Function:构造函数
*************************************************************************************************************************************************/
c_State_DB::c_State_DB(QObject *parent) : QObject(parent)
{
}
/*************************************************************************************************************************************************
**Function:析构函数
*************************************************************************************************************************************************/
c_State_DB::~c_State_DB()
{
}
/*************************************************************************************************************************************************
**Function:初始化函数
*************************************************************************************************************************************************/
void c_State_DB::Init()
{
	m_State_DB.insert("System_Time", NULL);
	m_State_DB.insert("RGV_State", NULL);
	m_State_DB.insert("Jaka_120_Remote_State", NULL);
	m_State_DB.insert("Jaka_121_Remote_State", NULL);
	m_State_DB.insert("Jaka_120_Monitor_State", NULL);
	m_State_DB.insert("Jaka_121_Monitor_State", NULL);
	m_State_DB.insert("Hypersen_30_State", NULL);
	m_State_DB.insert("Hypersen_31_State", NULL);
	m_State_DB.insert("Meijidenki_20_State", NULL);
	m_State_DB.insert("Meijidenki_21_State", NULL);
	m_State_DB.insert("Fast_Scan_State", NULL);
	m_State_DB.insert("Prec_Scan_120_State", NULL);
	m_State_DB.insert("Prec_Scan_121_State", NULL);
	m_State_DB.insert("Local_Remote_State", NULL);
	m_State_DB.insert("Local_Monitor_State", NULL);
}
/*************************************************************************************************************************************************
**Function:线程操作变量接口
*************************************************************************************************************************************************/
void c_State_DB::Write_System_Time(QString time)
{
	m_State_DB.insert("System_Time", time);
	emit System_Scan(m_State_DB);
}
void c_State_DB::Write_RGV_State(QJsonObject db)
{
	m_State_DB.insert("RGV_State", db);
}
void c_State_DB::Write_Jaka_120_Remote_State(QJsonObject db)
{
	m_State_DB.insert("Jaka_120_Remote_State", db);
}
void c_State_DB::Write_Jaka_121_Remote_State(QJsonObject db)
{
	m_State_DB.insert("Jaka_121_Remote_State", db);
}
void c_State_DB::Write_Jaka_120_Monitor_State(QJsonObject db)
{
	m_State_DB.insert("Jaka_120_Monitor_State", db);
}
void c_State_DB::Write_Jaka_121_Monitor_State(QJsonObject db)
{
	m_State_DB.insert("Jaka_121_Monitor_State", db);
}
void c_State_DB::Write_Hypersen_30_State(QJsonObject db)
{
	m_State_DB.insert("Hypersen_30_State", db);
}
void c_State_DB::Write_Hypersen_31_State(QJsonObject db)
{
	m_State_DB.insert("Hypersen_31_State", db);
}
void c_State_DB::Write_Meijidenki_20_State(QJsonObject db)
{
	m_State_DB.insert("Meijidenki_20_State", db);
}
void c_State_DB::Write_Meijidenki_21_State(QJsonObject db)
{
	m_State_DB.insert("Meijidenki_21_State", db);
}
void c_State_DB::Write_Fast_Scan_State(QJsonObject db)
{
	m_State_DB.insert("Fast_Scan_State", db);
}
void c_State_DB::Write_Prec_Scan_120_State(QJsonObject db)
{
	m_State_DB.insert("Prec_Scan_120_State", db);
}
void c_State_DB::Write_Prec_Scan_121_State(QJsonObject db)
{
	m_State_DB.insert("Prec_Scan_121_State", db);
}
void c_State_DB::Write_Local_Remote_State(QJsonObject db)
{
	m_State_DB.insert("Local_Remote_State", db);
}
void c_State_DB::Write_Local_Monitor_State(QJsonObject db)
{
	m_State_DB.insert("Local_Monitor_State", db);
}
