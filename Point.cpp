struct point
{
    ll x, y;
    point()
    {

    }
    point(ll a, ll b)
    {
        x=a;
        y=b;
    }
    point operator+(const point &o)
    {
        return point(this->x+o.x, this->y+o.y);
    }
    point operator-(const point &o)
    {
        return point(this->x-o.x, this->y-o.y);
    }
};
ll cross(point a, point b)
{
    return a.x*b.y-a.y*b.x;
}
ll dot(point a, point b)
{
    return a.x*b.x+a.y*b.y;
}