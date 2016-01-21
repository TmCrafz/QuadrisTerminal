#ifndef POINT_H
#define POINT_H

class Point
{
private:
	int m_x;
	int m_y;
public:
	Point();
	Point(int x, int y);

	int getX();
	int getY();

	void setX(int x);
	void setY(int y);

};

#endif // !POINT_H
