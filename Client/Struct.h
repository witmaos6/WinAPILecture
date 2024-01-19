#pragma once

struct Vec2
{
	float X;
	float Y;

	Vec2()
		: X(0.0f)
		, Y(0.0f)
	{}

	Vec2(float _X, float _Y)
		: X(_X)
		, Y(_Y)
	{}

	Vec2(const POINT& _pt)
		: X((float)_pt.x)
		, Y((float)_pt.y)
	{}

	Vec2 operator - ()
	{
		return Vec2(-X, -Y);
	}

	Vec2& operator = (POINT _pt)
	{
		X = (float)_pt.x;
		Y = (float)_pt.y;
	}

	Vec2 operator + (Vec2 _vOther)
	{
		return Vec2(X + _vOther.X, Y + _vOther.Y);
	}

	void operator += (Vec2 _vOther)
	{
		X += _vOther.X;
		Y += _vOther.Y;
	}

	Vec2 operator - (Vec2 _vOther)
	{
		return Vec2(X - _vOther.X, Y - _vOther.Y);
	}

	void operator -= (Vec2 _vOther)
	{
		X -= _vOther.X;
		Y -= _vOther.Y;
	}

	void operator -= (float _f)
	{
		X -= _f;
		Y -= _f;
	}

	Vec2 operator * (Vec2 _vOther)
	{
		return Vec2(X * _vOther.X, Y * _vOther.Y);
	}

	Vec2 operator * (int _i)
	{
		return Vec2(X * (float)_i, Y * (float)_i);
	}

	Vec2 operator * (float _f)
	{
		return Vec2(X * _f, Y * _f);
	}

	void operator *= (float _f)
	{
		X *= _f;
		Y *= _f;
	}

	Vec2 operator / (Vec2 _vOther)
	{
		assert(!(_vOther.X == 0.0f || _vOther.Y == 0.0f));
		return Vec2(X / _vOther.X, Y / _vOther.Y);
	}

	Vec2 operator / (float _f)
	{
		assert(!(_f == 0.0f));
		return Vec2(X / _f, Y / _f);
	}

public:
	bool IsZero()
	{
		if (X == 0.f && Y == 0.f)
		{
			return true;
		}
		return false;
	}
	Vec2& Normalize()
	{
		float fLength = Length();

		assert(fLength != 0.0f);

		X /= fLength;
		Y /= fLength;

		return *this;
	}

	float Length()
	{
		return sqrt(X * X + Y * Y);
	}
};
