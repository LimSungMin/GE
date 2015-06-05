#include "stdafx.h"
#include "GLine.h"


GLine::GLine() : GObject(0, 0), m_endX(0), m_endY(0)	
{	
}


GLine::~GLine()
{
}

void GLine::draw(CDC* dc){
	CPen pen(this->getPattern(), this->getThick(), this->getColor());
	dc->SelectObject(&pen);
	// �� �׸���� ���⼭����
	dc->MoveTo(getStartX(), getStartY());
	dc->LineTo(GetEnd());
}

void GLine::SetEnd(POINT point){
	m_endX = point.x;
	m_endY = point.y;	
}
POINT GLine::GetEnd(){
	POINT value;
	value.x = m_endX;
	value.y = m_endY;
	return value;
}