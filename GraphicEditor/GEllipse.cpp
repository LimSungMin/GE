#include "stdafx.h"
#include "GEllipse.h"


GEllipse::GEllipse() : GObject(0, 0), m_endX(0), m_endY(0)
{
}


GEllipse::~GEllipse()
{
}

void GEllipse::draw(CDC* dc)
{
	CPen pen(this->getPattern(), this->getThick(), this->getLineColor());
	dc->SelectObject(&pen);
	// �� �׸���� ���⼭����
	dc->MoveTo(getStartX(), getStartY());
	dc->Ellipse(this->getStartX(), this->getStartY(), GetEnd().x, GetEnd().y);
}

POINT GEllipse::GetEnd(){
	POINT value;
	value.x = m_endX;
	value.y = m_endY;
	return value;
}

void GEllipse::SetEnd(POINT point){
	m_endX = point.x;
	m_endY = point.y;
}

