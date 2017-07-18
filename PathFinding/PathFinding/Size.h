#pragma once
/*
 * Size class
 * 2009-11-05 KimSungcheol
 *
 * This class represents the specific position in 2D space.
 */
template<typename T>
class Size
{
private:
	T	w, h;
public:
	Size(void);
	Size(T w, T h);
	Size(const Size<T>& pt);
	~Size(void);
	T getW(void) const;
	T getH(void) const;
	void setW(T w);
	void setH(T h);
	void setWH(T w, T h);
};
typedef Size<int> IntSize;
/*---------------------------------------------------------------*/
#include <cstring>
template<class T>
Size<T>::Size(void)
{
	memset((void *)&w, 0, sizeof(T));
	memset((void *)&h, 0, sizeof(T));
}
template<class T>
Size<T>::~Size(void)
{
}

template<class T>
Size<T>::Size(T w, T h) : w(w), h(h)
{
}
template<class T>
Size<T>::Size(const Size<T>& size)
{
	w = size.w;
	h = size.h;
}
template<class T>
T Size<T>::getW(void) const
{
	return w;
}
template<class T>
T Size<T>::getH(void) const
{
	return h;
}

template<class T>
void Size<T>::setW(T w)
{
	this->w = w;
}
template<class T>
void Size<T>::setH(T h)
{
	this->h = h;
}
template<class T>
void Size<T>::setWH(T w, T h)
{
	this->w = w;
	this->h = h;
}
