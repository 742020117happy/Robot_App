﻿#pragma execution_character_set("utf-8")
#include "Jaka_120_Remote.h"
/*************************************************************************************************************************************************
**Function:    构造函数
**Others:      构造函数初始化在主线程实例化中完成，故在子线程中运行时，成员函数的初始化不能在构造函数中完成
*************************************************************************************************************************************************/
c_Jaka_120_Remote::c_Jaka_120_Remote(c_Jaka_Remote *parent) : c_Jaka_Remote(parent)
{
	
}
/*************************************************************************************************************************************************
**Function:    析构函数
*************************************************************************************************************************************************/
c_Jaka_120_Remote::~c_Jaka_120_Remote()
{
}
/*************************************************************************************************************************************************
**Function:    操作接口
*************************************************************************************************************************************************/
void c_Jaka_120_Remote::Connect()
{
	QString ip = c_Variable::g_Communicate_DB.value("Jaka_120_Ip").toString();
	int port = c_Variable::g_Communicate_DB.value("Jaka_Remote_Port").toInt();
	emit Connect_Device(ip, port);
}