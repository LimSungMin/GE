#pragma once
#include "GObject.h"
class GLine	: public GObject
{
public:
	GLine();
	~GLine();
	void SetEnd(POINT point);
	POINT GetEnd();

	// �ٸ� �ֵ� ��
	void draw(CDC* dc, int mode);

	//void move(int x1, int y1, int x2, int y2);
private:
	int m_endX;
	int m_endY;
	int m_mode;	
};

