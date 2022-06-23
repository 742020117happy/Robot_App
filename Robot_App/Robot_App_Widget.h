#pragma once
#include "Public_Header.h"
#include "Ui_Robot_App_Widget.h"

QT_BEGIN_NAMESPACE
class QThread;
class c_Variable;
class c_State_DB;
class c_System_Time;
class c_Local_Remote;
class c_Local_Monitor;
class c_RGV_Remote;
class c_Scan_Remote;
class c_Jaka_120_Remote;
class c_Jaka_121_Remote;
class c_Jaka_120_Monitor;
class c_Jaka_121_Monitor;
class c_Hypersen_30_Remote;
class c_Hypersen_31_Remote;
class c_Meijidenki_20_Remote;
class c_Meijidenki_21_Remote;
class Ui_Robot_App_Widget;
QT_END_NAMESPACE

class c_Robot_App_Widget : public QMainWindow {
	Q_OBJECT

public:
	c_Robot_App_Widget(QWidget * parent = nullptr);
	~c_Robot_App_Widget();

private:
	Ui_Robot_App_Widget *ui;
	QThread *m_System_Time_Thread;
	c_System_Time *m_System_Time;
	QThread *m_State_DB_Thread;
	c_State_DB *m_State_DB;
	c_Variable *m_Variable;
	QThread *m_RGV_Remote_Thread;
	c_RGV_Remote *m_RGV_Remote;
	QThread *m_Jaka_120_Remote_Thread;
	c_Jaka_120_Remote *m_Jaka_120_Remote;
	QThread *m_Jaka_121_Remote_Thread;
	c_Jaka_121_Remote *m_Jaka_121_Remote;
	QThread *m_Jaka_120_Monitor_Thread;
	c_Jaka_120_Monitor *m_Jaka_120_Monitor;
	QThread *m_Jaka_121_Monitor_Thread;
	c_Jaka_121_Monitor *m_Jaka_121_Monitor;
	QThread *m_Hypersen_30_Remote_Thread;
	c_Hypersen_30_Remote *m_Hypersen_30_Remote;
	QThread *m_Hypersen_31_Remote_Thread;
	c_Hypersen_31_Remote *m_Hypersen_31_Remote;
	QThread *m_Meijidenki_20_Remote_Thread;
	c_Meijidenki_20_Remote *m_Meijidenki_20_Remote;
	QThread *m_Meijidenki_21_Remote_Thread;
	c_Meijidenki_21_Remote *m_Meijidenki_21_Remote;
	QThread *m_Scan_Remote_Thread;
	c_Scan_Remote *m_Scan_Remote;
	QThread *m_Local_Remote_Thread;
	c_Local_Remote *m_Local_Remote;
	QThread *m_Local_Monitor_Thread;
	c_Local_Monitor *m_Local_Monitor;

	QString m_Current_Time;
	QJsonObject m_RGV_State;
	QJsonObject m_Jaka_120_Remote_State;
	QJsonObject m_Jaka_121_Remote_State;
	QJsonObject m_Jaka_120_Monitor_State;
	QJsonObject m_Jaka_121_Monitor_State;
	QJsonObject m_Hypersen_30_State;
	QJsonObject m_Hypersen_31_State;
	QJsonObject m_Meijidenki_20_State;
	QJsonObject m_Meijidenki_21_State;
	QJsonObject m_Fast_Scan_State;
	QJsonObject m_Prec_Scan_120_State;
	QJsonObject m_Prec_Scan_121_State;
	QJsonObject m_Local_Remote_State;
	QJsonObject m_Local_Monitor_State;

	QString m_Cmd_Name;
	QString m_Begin_Time;
	QString m_Work_Num;
	QString m_Car_Type;
	QString m_Car_Num;

	QJsonObject m_DiscreteInputs;
	QJsonObject m_InputRegisters;

	int m_Jaka_120_Lift_Position;
	int m_Jaka_121_Lift_Position;

	QJsonObject m_json;
	QJsonArray m_joint_actual_position;
	QJsonArray m_actual_position;
	int m_task_state;
	QJsonArray m_homed;
	int m_task_mode;
	int m_interp_state;
	int m_current_tool_id;
	int m_protective_stop;
	int m_on_soft_limit;
	int m_emergency_stop;
	QJsonArray m_drag_near_limit;
	QJsonObject  m_value;
	int m_nMR;// 量程
	int m_nESAR;// 设备角度范围
	int m_nESA0;// 设备角度起始角
	int m_nESA1;// 设备角度终止角
	int m_nSAR;// 有效角度范围
	int m_nSA0;// 有效角度起始角
	int m_nSA1;// 有效角度终止角
	int m_nSAV;// 扫描角速度（度/秒）
	double m_nSAP;// 扫描角度分辨率
	int m_nPF;// 测量频率(HZ)
	double m_nRange;// 设备量程.单位:cm
	double m_nBAngle;// 测量数据起始角度，可能为负值.单位:度
	double m_nEAngle;// 测量数据结束角度，可能为负值.单位:度
	double m_nAnglePrecision;// 角度精度.单位：1/1000 度
	double m_nRPM;// 扫描频率.单位：RPM (转/分钟)
	double m_nMDataNum;//测量数据的个数，根据nBAngle、nEAngle和nAnglePrecision计算
	QJsonArray m_distance;//测量距离数据.单位cm
	double m_idistance;//模长
	double m_iAngle;//角度
	QJsonArray m_Array;
	int m_roi_aver_distance;
	int m_roi_max_distance;
	int m_roi_min_distance;
	int m_roi_valid_aver_amp;
	int m_roi_all_aver_amp;

	private slots:
	void System_Scan(QJsonObject db);

	QString JsonArray_To_String(const QJsonArray &data);

	QJsonObject Read_Robot_Teach(QString Robot_File_Name);
	void Write_Robot_Teach(QString Robot_File_Name, QJsonObject Program_Date);

	void on_Build_New_Date_clicked();
	void on_Teach_Complete_clicked();

	void on_Load_Robot_Teaching_clicked();
	void on_Delete_Task_clicked();

	void on_Load_Car_Number_clicked();

	void on_Current_Point_120_clicked();
	void on_Load_Point_120_clicked();
	void on_Delete_Point_120_clicked();

	void on_Current_Point_121_clicked();
	void on_Delete_Point_121_clicked();
	void on_Load_Point_121_clicked();
	
};
