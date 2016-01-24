#ifndef POINT_H
#define POINT_H

class Point
{
private:
	int m_x;
	int m_y;
public:
	Point();
	Point(const int x, const int y);
	
	// The getters are const, because we dont change any member data
	int getX() const;
	int getY() const;

	void setX(const int x);
	void setY(const int y);

	void rotateAround(const int targetPX, const int targetPY, const float angleDegree);
	void rotateAround(const Point target, const float  angleDegree);

};

#endif // !POINT_H
