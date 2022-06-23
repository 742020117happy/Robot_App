#pragma execution_character_set("utf-8") 
#include "Public_Header.h"
#include "Robot_Logon_Widget.h"
#include "Robot_App_Widget.h"

int main(int argc, char *argv[])
{
	//初始化App
	QApplication Application(argc, argv);
	//系统文件夹完整性自检
	bool exist;
	QDir System_Dir;
	exist = System_Dir.exists(QDir::currentPath() + "/System_DB");
	if (!exist){
		System_Dir.mkdir(QDir::currentPath() + "/System_DB");
	}
	exist = System_Dir.exists(QDir::currentPath() + "/Robot_Teach");
	if (!exist){
		System_Dir.mkdir(QDir::currentPath() + "/Robot_Teach");
	}
	exist = System_Dir.exists(QDir::currentPath() + "/Robot_App");
	if (!exist) {
		System_Dir.mkdir(QDir::currentPath() + "/Robot_App");
	}
	//创建窗体
	c_Robot_App_Widget Robot_App_Widget;
	c_Robot_Logon_Widget Robot_Logon_Widget;
	QObject::connect(&Robot_Logon_Widget, &c_Robot_Logon_Widget::Show_Robot_App, &Robot_App_Widget, &c_Robot_App_Widget::showMaximized);
	Robot_Logon_Widget.show();
	//等待App退出
	return Application.exec();
}
