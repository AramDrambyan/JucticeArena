#pragma once

struct Point
{
	int x, y;

	Point(int x = 0, int y = 0)
	{
		this->x = x;
		this->y = y;
	}
};
struct Rect
{
	// upper-left corner of Rectangle
	Point p;
	int h, w;

	// coords start from the uppper-left corner of the field

	Rect(Point p = Point(),int w = 0, int h = 0)
	{
		this->p = p;
		this->h = h;
		this->w = w;
	}

	bool contains_point(const Point& p) const
	{
		return p.x >= this->p.x && 
			p.x <= this->p.x + w &&
			p.y >= this->p.y &&
			p.y <= this->p.y + h;
	}

	bool intersects_rect(const Rect& r) const
	{
		Point a[] = {r.p, Point(r.p.x + r.w, r.p.y), Point(r.p.x, r.p.y + r.h), Point(r.p.x + r.w, r.p.y + r.h)};
		for(int i = 0; i < 4; ++i)
		{
			if(this->contains_point(a[i]))
				return true;
		}
		return false;
	}

	bool contains_rect(const Rect& r) const		// check if rectangle contains another one 
	{
		Point a[] = {r.p, Point(r.p.x + r.w, r.p.y), Point(r.p.x, r.p.y + r.h), Point(r.p.x + r.w, r.p.y + r.h)};
		for(int i = 0; i < 4; ++i)
		{
			if(!(this->contains_point(a[i])))
				return false;
		}
		return true;
	}

	bool intersect_direction(const Rect& r,Direction dir) const     //  checks direction of intersect
	{
		if (contains_point(Point(r.p.x + r.w, r.p.y + r.h)))
		{
			return dir == LEFT || dir == UP;
		}

		if (contains_point(Point(r.p.x, r.p.y)))
		{
			return dir == RIGHT || dir == DOWN;
		}

		if (contains_point(Point(r.p.x + r.w, r.p.y)))
		{
			return dir == LEFT || dir == DOWN;
		}

		if (contains_point(Point(r.p.x, r.p.y + r.h)))
		{
			return dir == RIGHT || dir == UP;
		}
		return false;
	}
};