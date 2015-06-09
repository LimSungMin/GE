#include "stdafx.h"
#include "GObject.h"


GObject::GObject() : m_startX(0), m_startY(0), m_thick(1), m_groupIndex(-1)
{
}

GObject::GObject(int x, int y) : m_startX(x), m_startY(y), m_thick(1), m_groupIndex(-1)
{
}

GObject::GObject(GObject& ref)
{
	m_startX = ref.getStartX();
	m_startY = ref.getStartY();
	m_linecolor = ref.getLineColor();
	m_thick = ref.getThick();
	m_pattern = ref.getPattern();
	m_fillPattern = ref.getFillPattern();
	m_panecolor = ref.getFillColor();
	m_isSelected = ref.getSelected();
}

void GObject::setStartX(int x){
	m_startX = x;
}

void GObject::setStartY(int y){
	m_startY = y;
}

int GObject::getStartX(){
	return m_startX;
}

int GObject::getStartY(){
	return m_startY;
}

COLORREF GObject::getLineColor(){
	return m_linecolor;
}

void GObject::setLineColor(COLORREF c){
	m_linecolor = c;
}

void GObject::setLineColor(int r, int g, int b){
	m_linecolor = RGB(r, g, b);
}

COLORREF GObject::getFillColor(){
	return m_panecolor;
}

void GObject::setFillColor(COLORREF c){
	m_panecolor = c;
}

void GObject::setFillColor(int r, int g, int b){
	m_panecolor = RGB(r, g, b);
}


void GObject::setPattern(int pattern){
	m_pattern = pattern;
}
void GObject::setFillPattern(int pattern){
	m_fillPattern = pattern;
}

int GObject::getPattern(){
	return m_pattern;
}
int GObject::getFillPattern(){
	return m_fillPattern;
}
int GObject::getThick(){
	return m_thick;
}

void GObject::setThick(int thick){
	m_thick = thick;
}

void GObject::setFont(int font){
	m_font = font;
}

void GObject::setFontColor(COLORREF c)
{
	m_fontcolor = c;
}

void GObject::setFontColor(int r, int g, int b)
{
	m_fontcolor = RGB(r, g, b);
}

COLORREF GObject::getFontColor()
{
	return m_fontcolor;
}

void GObject::polypointmovecheck(int x)
{
	if (x == 0)
		polypointmove = FALSE;
	else if (x == 1)
		polypointmove = TRUE;
}

void GObject::polyundo(){

}

void GObject::pointmover(int x, int y, int index){

	this->m_polypoints[index].x = x;
	this->m_polypoints[index].y = y;

}

void GObject::setFontSort(int fontsort)
{
	m_fontsort = fontsort;
}
int GObject::getFontSort()
{
	return m_fontsort;
}
GObject::~GObject()
{
}
