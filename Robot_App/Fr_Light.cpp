#pragma execution_character_set("utf-8")
#include "Fr_Light.h"

c_Fr_Light::c_Fr_Light(QWidget * parent) :QWidget(parent)
{
	m_State = Default;
	m_Working_Color = QColor("green");
	m_Default_Color = QColor("red");
	m_Error_Color = QColor("yellow");
	update();
}

c_Fr_Light::~c_Fr_Light() {
	
}

void c_Fr_Light::Set_Working()
{
	m_State = Working;
	update();
}
void c_Fr_Light::Set_Default()
{
	m_State = Default;
	update();
}
void c_Fr_Light::Set_Error()
{
	m_State = Error;
	update();
}

void c_Fr_Light::paintEvent(QPaintEvent*) {
	int side = qMin(width(), height());
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.translate(width() / 2, height() / 2);
	painter.scale(side / 100.0, side / 100.0);
	QColor color;
	switch (m_State) {
	case Default:
		color = m_Default_Color;
		break;
	case Working:
		color = m_Working_Color;
		break;
	case Error:
		color = m_Error_Color;
		break;
	default:
		color = m_Default_Color;
		break;
	}
	QRadialGradient radial(0, 0, 50, 0, 0);    //设置圆的原点和焦点在中心,半径50
	radial.setSpread(QGradient::PadSpread);
	radial.setColorAt(1, color);
	painter.setPen(Qt::transparent);
	painter.setBrush(radial);
	painter.drawEllipse(-50, -50, 100, 100);
}