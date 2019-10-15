int sgn(ll a)
{
	if(a > 0)
		return 1;
	if(a < 0)
		return -1;
	return 0;
}
struct point
{
	ll x, y;
	point(ll a = 0, ll b = 0)
	{
		x = a, y = b;
	}
	point operator+(const point &b) const
	{
		return point(x + b.x, y + b.y);
	}
	point operator-(const point &b) const
	{
		return point(x - b.x, y - b.y);
	}
	point operator*(const ll &a) const
	{
		return point(x * a, y * a);
	}
	ll vlen() // SQUARE ROOT NOT TAKEN
	{
		return x * x + y * y; 
	}
};
ll dot(point a, point b)
{
	return a.x * b.x + a.y * b.y;
}
ll cross(point a, point b)
{
	return a.x * b.y - a.y * b.x;
}
point proj(point v, point u) // projection of v onto u
{
	return u * (dot(v, u) / dot(u, u));
}
bool isect(point a, point b, point c, point d)
{
	int A = sgn(cross(c - a, d - a));
	int B = sgn(cross(c - b, d - b));
	if(A * B != 0 && A == B)
		return false;
	int C = sgn(cross(a - c, b - c));
	int D = sgn(cross(a - d, b - d));
	if(C * D != 0 && C == D)
		return false;
	return true;
}
point inter(point a, point b, point c, point d)
{
	point ab = b - a;
	point cd = d - c;
	ll top = cross(a, ab) - cross(c, ab);
	ll bot = cross(cd, ab);
	// if(cd.x * top % bot != 0) // FLOATING POINT - CHANGE TO DOUBLE IF NECESSARY
	// 	return point(mod, mod);
	// if(cd.y * top % bot != 0) // FLOATING POINT - CHANGE TO DOUBLE IF NECESSARY
	// 	return point(mod, mod);
	ll X = c.x + cd.x * top / bot;
	ll Y = c.y + cd.y * top / bot;
	// or alternatively (works with doubles) 
	// return c + cd * (top / bot)
	return point(X, Y);
}