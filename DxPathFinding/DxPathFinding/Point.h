#pragma once
/*
 * class Point<T>
 * ±è¼ºÃ¶
 *
 * 2Â÷¿ø °ø°£ÀÇ ÁÂÇ¥¸¦ ³ªÅ¸³½´Ù.
 */
template<typename T>
class Point
{
private:
	T	x, y;
public:
	Point(void);
	Point(T x, T y);
	Point(const Point<T>& pt);
	~Point(void);
	T getX(void) const;
	T getY(void) const;
	void setX(T x);
	void setY(T y);
	void setXY(T x, T y);
	Point<T> operator+(const Point<T>& pt2);
	Point<T> operator-(const Point<T>& pt2);
	bool operator==(const Point<T>& pt2);
	bool operator!=(const Point<T>& pt2);
};
typedef Point<int> IntPoint;
/*---------------------------------------------------------------*/
#include <cstring>
template<class T>
Point<T>::Point(void)
{
	memset((void *)&x, 0, sizeof(T));
	memset((void *)&y, 0, sizeof(T));
}
template<class T>
Point<T>::~Point(void)
{
}

template<class T>
Point<T>::Point(T x, T y) : x(x), y(y)
{
}
template<class T>
Point<T>::Point(const Point<T>& pt)
{
	x = pt.x;
	y = pt.y;
}
template<class T>
T Point<T>::getX(void) const
{
	return x;
}
template<class T>
T Point<T>::getY(void) const
{
	return y;
}
template<class T>
void Point<T>::setX(T x)
{
	this->x = x;
}
template<class T>
void Point<T>::setY(T y)
{
	this->y = y;
}
template<class T>
void Point<T>::setXY(T x, T y)
{
	this->x = x;
	this->y = y;
}
template<class T>
Point<T> Point<T>::operator+(const Point<T>& pt2)
{
	return Point<T>(this->x+pt2.x, this->y+pt2.y);
}
template<class T>
Point<T> Point<T>::operator-(const Point<T>& pt2)
{
	return Point<T>(this->x-pt2.x, this->y-pt2.y);
}
template<class T>
bool Point<T>::operator==(const Point<T>& pt2)
{
	return (x == pt2.x) && (y == pt2.y);
}

template<class T>
bool Point<T>::operator!=(const Point<T>& pt2)
{
	return !(*this == pt2);
}