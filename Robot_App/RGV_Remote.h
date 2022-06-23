/*************************************************************************************************************************************************
**Copyright(C), 2020-2025, bjtds.
**Version:2.0
**Author: dz
**Date:2021.2.1
**Description: 轮询模式
**
**读离散输入完成->写线圈
**写线圈完成->读输入寄存器
**读输入寄存器完成—>写保持寄存器
**写保持寄存器完成->读离散输入寄存器
**读离散输入完成->写线圈
**
*************************************************************************************************************************************************/
#pragma once
#include "Public_Header.h"

class c_RGV_Client;

class c_RGV_Remote : public QObject
{
	Q_OBJECT
public:
	explicit c_RGV_Remote(QObject *parent = nullptr);
	~c_RGV_Remote();
	QThread *m_RGV_Remote_Thread;
	c_RGV_Client *m_RGV_Remote;

	public slots:
	void Init();//线程初始化
	void Connect();//连接
	void Forward_continuous_operation();
	void The_nth_reverse_intermittent_operation();
	void First_reverse_intermittent_operation();
	void Stop_motion();
	void Get_Right_Rise();
	void Get_Left_Rise();
	void Forward_motion();
	void Reverse_motion();
	void Left_Lifting_reset();
	void Right_Lifting_reset();
	void Left_Manual_rise();
	void Right_Manual_rise();
	void Left_Manual_descent();
	void Right_Manual_descent();
	void Clean_position();
	void Left_door();
	void Right_door();
	void Middle_door();
	void Middle_door_closing();
	void Left_door_closing();
	void Right_door_closing();
	void Movement_speed();
	void Intermittent_running_speed();
	void First_creep_speed();
	void Second_creep_speed();
	void Acceleration();
	void Deceleration();
	void Left_reset_speed();
	void Left_creep_speed();
	void Left_manual_speed();
	void Left_lifting_speed();
	void Left_door_speed();
	void Middle_door_speed();
	void Right_door_speed();
	void Right_reset_speed();
	void Right_creep_speed();
	void Right_manual_speed();
	void Right_lifting_speed();
	void Underbody_detection_distance();
	void Underbody_detection_distance_delay();
	void Trailer_wheel_distance();
	void Trailer_wheel_error();
	void Trailer_axle_distance();
	void Trailer_axle_error();
	void Motor_wheel_distance();
	void Motor_wheel_distance_error();
	void Motor_axle_distance();
	void Motor_axle_error();

signals:
	void Connect_Device(QString ip, int port);//连接到服务器
	void Disconnect_Device();//断开连接
	void Write_RGV_Remote_State(QJsonObject db);//写状态
	void Set_Working();//工作状态
	void Set_Default();//非工作状态
	void setEnabled(bool ready);//写消息状态
	void Status(QString status);//监视器状态

	void Write_Coils(int addr, QJsonObject value, int size);//读线圈
	void Write_HoldingRegisters(int addr, QJsonObject value, int size);//读输入寄存器

	void Read_DiscreteInputs(int addr, int size); //写离散输入
	void Read_InputRegisters(int addr, int size);//写输入寄存器

private:
	QJsonObject m_RGV_Remote_DB;
	QJsonObject m_RGV_Remote_State;

	bool m_Write_Coils;
	bool m_Write_HoldingRegisters;

	QJsonObject m_Coils;
	QJsonObject m_HoldingRegisters;

	private slots:
	void Connect_Done();
	void Disconnect_Done();

	void Set_Coils(int addr);
	void Reset_Coils(int addr);
	void Set_HoldingRegisters(int addr, int value);

	void Write_Coils_Done();//读线圈
	void Write_HoldingRegisters_Done();//读保持寄存器

	void Read_DiscreteInputs_Done(QJsonObject value);//读离散输入
	void Read_InputRegisters_Done(QJsonObject value);//读输入寄存器
	
};

