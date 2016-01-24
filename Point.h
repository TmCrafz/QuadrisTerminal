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
	
	// The getters are const, because we dont change any member data
	int getX() const;
	int getY() const;

	void setX(int x);
	void setY(int y);

	void rotateAround(int targetPX, int targetPY, float angleDegree);
	void rotateAround(Point target, float  angleDegree);

};

#endif // !POINT_H
