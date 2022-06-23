/*************************************************************************************************************************************************
**Copyright(C), 2020-2025, bjtds.
**Version:2.0
**Author: dz
**Date:2021.2.1
**Description:
**Others:                            "System_Time"                                 "State_DB"
							  ____________________________                      ____________________
			 QTimer::timeout->|REQ          |        DONE|->Write_System_Time->|REQ       |     DONE|->System_Scan
			    current_time->|DATA         |            |                 DB->|DATA      |         |
							  ----------------------------             device->|Thread    |         |
							                                                    --------------------
*************************************************************************************************************************************************/
#pragma once
#include "Public_Header.h"

QT_BEGIN_NAMESPACE
class QTimer;
QT_END_NAMESPACE

class c_System_Time : public QObject
{
	Q_OBJECT
public:
	explicit c_System_Time(QObject *parent = nullptr);
	~c_System_Time();

	public slots:
	void Init();

signals:
	void Write_System_Time(QString time);

private:
	QTimer *m_System_Time;

	private slots:
	void System_Time();
};

/*************************************************************************************************************************************************
**Function:扫面系统状态参数
*************************************************************************************************************************************************/
class c_State_DB : public QObject
{
	Q_OBJECT
public:
	explicit c_State_DB(QObject *parent = nullptr);
	~c_State_DB();

	//线程操作接口
	public slots:
	void Init();
	void Write_System_Time(QString time);
	void Write_RGV_State(QJsonObject db);
	void Write_Jaka_120_Remote_State(QJsonObject db);
	void Write_Jaka_121_Remote_State(QJsonObject db);
	void Write_Jaka_120_Monitor_State(QJsonObject db);
	void Write_Jaka_121_Monitor_State(QJsonObject db);
	void Write_Hypersen_30_State(QJsonObject db);
	void Write_Hypersen_31_State(QJsonObject db);
	void Write_Meijidenki_20_State(QJsonObject db);
	void Write_Meijidenki_21_State(QJsonObject db);
	void Write_Fast_Scan_State(QJsonObject db);
	void Write_Prec_Scan_120_State(QJsonObject db);
	void Write_Prec_Scan_121_State(QJsonObject db);
	void Write_Local_Remote_State(QJsonObject db);
	void Write_Local_Monitor_State(QJsonObject db);

signals:
	void System_Scan(QJsonObject db);

private:
	QJsonObject m_State_DB;
};