
Matrix2D::Matrix2D(
	float r0c0, float r0c1,
	float r1c0, float r1c1) :
	r0c0(r0c0), r0c1(r0c1),
	r1c0(r1c0), r1c1(r1c1)
{
}
Vector2D operator*(const Matrix2D& left, const Vector2D& right)
{
	return Vector2D();
}