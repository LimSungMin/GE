#pragma once
#include "GObject.h"
class GPolyline :
	public GObject
{
public:
	GPolyline();
	virtual ~GPolyline();
	virtual void draw(CDC* dc);
	void setEndX(int x);
	void setEndY(int y);
	
	int getStartX();
	int getStartY();
	
	int getEndX();
	int getEndY();
	void move(int x1, int y1, int x2, int y2);
	
	void polypointset(POINT point);
	void deletepolypointset(int);
	//vector <POINT> pointofpoly;

	int findhighest();
	int findlowest();
	int findleftest();
	int findrightest(); // �� ���⺰ �ְ����� ã�� �ܰ����� ������ ��´� 

	BOOL isInBound(CPoint point);
	void setSElected(BOOL selected);
	//int isInSizeBound(CPoint point);

	void xmover(int);
	void ymover(int);

private:
	int m_endX;
	int m_endY;
	int m_mode; 
	CArray<POINT, POINT&> m_polypoints;
	CRect* m_selectedRect[5]; // 4������ �ֺ� 4���� ��, �׸��� 5�� �ѷ��� ǥ���ϴ� �簢���̴�
};