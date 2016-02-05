#ifndef POINTF_H
#define POINTF_H

class PointF
{
private:
	float m_x;
	float m_y;
public:
	PointF();
	PointF(const float x, const float y);
	
	float getX() const;
	float getY() const;


	void setX(const float x);
	void setY(const float y);
	
	void rotateAround(const float targetPX, const float targetPY, const float angleDegree);
	void rotateAround(const PointF target, const float  angleDegree);


	void operator=(const PointF &right);
	PointF operator+(const PointF &right);
	// Const so we can use it with const Stones
	PointF operator+(const PointF &right) const;
	PointF operator-(const PointF &right);
	PointF operator-(const PointF &right) const;
	PointF& operator+=(const PointF &right);
	PointF& operator-=(const PointF &right);
	bool operator==(const PointF &right);
}


#endif // !POINTF_H
