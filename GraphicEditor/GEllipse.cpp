#include "stdafx.h"
#include "GEllipse.h"


GEllipse::GEllipse() : GObject(0, 0), m_endX(0), m_endY(0)
{
	this->setPattern(PS_DOT);
}


GEllipse::~GEllipse()
{
	// �̰��� ������ heap �Ҵ� ������ ���.. �������� ��
//	delete[] m_selectedRect;
}

void GEllipse::draw(CDC* dc)
{
	CPen pen(this->getPattern(), this->getThick(), this->getLineColor());
	dc->SelectObject(&pen);
	dc->SelectStockObject(NULL_BRUSH);
	// �� �׸���� ���⼭����
	dc->MoveTo(getStartX(), getStartY());
	dc->Ellipse(this->getStartX(), this->getStartY(), GetEnd().x, GetEnd().y);
	if (this->getSelected() == TRUE){
		CBrush brush(RGB(255, 255, 255));
		dc->SelectObject(&brush);
		m_selectedRect[0] = new CRect(this->getStartX() - 5, this->getStartY() - 5, this->getStartX() + 5, this->getStartY() + 5);
		m_selectedRect[1] = new CRect(this->getEndX() - 5, this->getStartY() - 5, this->getEndX() + 5, this->getStartY() + 5);
		m_selectedRect[2] = new CRect(this->getStartX() - 5, this->getEndY() - 5, this->getStartX() + 5, this->getEndY() + 5);
		m_selectedRect[3] = new CRect(this->getEndX() - 5, this->getEndY() - 5, this->getEndX() + 5, this->getEndY() + 5); // �޸� ������ ���� ����. �����ٶ�!
		dc->Rectangle(m_selectedRect[0]);
		dc->Rectangle(m_selectedRect[1]);
		dc->Rectangle(m_selectedRect[2]);
		dc->Rectangle(m_selectedRect[3]);
	}
}

int GEllipse::getEndX(){ return m_endX; }
int GEllipse::getEndY(){ return m_endY; }

void GEllipse::setEndX(int x){ m_endX = x; }
void GEllipse::setEndY(int y){ m_endY = y; }

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

BOOL GEllipse::isInBound(CPoint point){
	if (this->getStartX() <= point.x && point.x <= this->getEndX() || this->getEndX() <= point.x && point.x <= this->getStartX()){
		if (this->getStartY() <= point.y && point.y <= this->getEndY() || this->getEndY() <= point.y && point.y <= this->getStartY()){
			return TRUE;
		}
	}
	return FALSE;
}

int GEllipse::isInSizeBound(CPoint point){
	for (int i = 0; i < 4; i++){
		if (this->m_selectedRect[i]->left <= point.x && point.x <= this->m_selectedRect[i]->right || this->m_selectedRect[i]->right <= point.x && point.x <= this->m_selectedRect[i]->left){
			if (this->m_selectedRect[i]->top <= point.y && point.y <= this->m_selectedRect[i]->bottom || this->m_selectedRect[i]->bottom <= point.y && point.y <= this->m_selectedRect[i]->top){
				MessageBeep(NULL);
				return i;
			}
		}
	}

	return -1;
}

void GEllipse::move(int x1, int y1, int x2, int y2){
	this->setStartX(x1);
	this->setStartY(y1);
	this->setEndX(x2);
	this->setEndY(y2);
}

void GEllipse::setSelected(BOOL selected){
	m_isSelected = selected;

}