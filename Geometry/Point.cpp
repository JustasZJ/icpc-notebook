const ld eps = 1e-9;
int sgn(ld a) {
    return (a > 0) - (a < 0);
}
struct point {
    // Use ll everywhere instead of ld if coordinates are always integers
    ld x, y;
    point(ld a = 0, ld b = 0) {
        x = a, y = b;
    }
    bool operator==(const point& o) const {
        return x == o.x && y == o.y;
    }
    point operator+(const point &b) const {
        return point(x + b.x, y + b.y);
    }
    point operator-(const point &b) const {
        return point(x - b.x, y - b.y);
    }
    point operator*(const ld &a) const {
        return point(x * a, y * a);
    }
    point operator/(const ld &a) const {
        return point(x / a, y / a);
    }
    ld vlensq() {
        return x * x + y * y;
    }
    ld vlen() {
        return sqrtl(vlensq()); 
    }
    point perp() const { 
        return point(-y, x); 
    }
    // normalize vector
    point toUnit() {
        return *this / vlen();
    }
};
ld dot(point a, point b) {
    return a.x * b.x + a.y * b.y;
}
ld cross(point a, point b) {
    return a.x * b.y - a.y * b.x;
}
point proj(point v, point u) {
    // projection of v onto u
    return u * (dot(v, u) / dot(u, u));
}
// check if line segments AB and CD intersect
bool isect(point a, point b, point c, point d) {
    int A = sgn(cross(c - a, d - a));
    int B = sgn(cross(c - b, d - b));
    if (A * B != 0 && A == B) {
        return false;
    }
    int C = sgn(cross(a - c, b - c));
    int D = sgn(cross(a - d, b - d));
    if (C * D != 0 && C == D) {
        return false;
    }
    return true;
}
// intersection point of line segments AB and CD 
point inter(point a, point b, point c, point d) {
    point ab = b - a;
    point cd = d - c;
    ld top = cross(a, ab) - cross(c, ab);
    ld bot = cross(cd, ab);
    // if(cd.x * top % bot != 0) // FLOATING POINT - CHANGE TO DOUBLE IF NECESSARY
    // 	return point(mod, mod);
    // if(cd.y * top % bot != 0) // FLOATING POINT - CHANGE TO DOUBLE IF NECESSARY
    // 	return point(mod, mod);
    ld X = c.x + cd.x * top / bot;
    ld Y = c.y + cd.y * top / bot;
    // or alternatively (works with doubles) 
    // return c + cd * (top / bot)
    return point(X, Y);
}
// checks if circles with centers a, b and radiuses r1, r2 intersect
// intersection points are written to parameter out
bool circleInter(point a, point b,double r1,double r2,pair<point, point>* out) {
    if (a == b) { assert(r1 != r2); return false; }
    point vec = b - a;
    double d2 = vec.vlensq(), sum = r1+r2, dif = r1-r2,
           p = (d2 + r1*r1 - r2*r2)/(d2*2), h2 = r1*r1 - p*p*d2;
    if (sum*sum < d2 || dif*dif > d2) return false;
    point mid = a + vec*p, per = vec.perp() * sqrt(fmax(0, h2) / d2);
    *out = {mid + per, mid - per};
    return true;
}
// point in polygon
bool insidePoly(point p, vector<point>poly) {
    point mx = {-1e9, -1e9};
    for (point pp : poly) {
        if (pp.x > mx.x) {
            mx = pp;
        }
    }
    mx.x++;
    int cnt = 0;
    for (int i = 0; i < poly.size(); i++) {
        point a = poly[i];
        point b = poly[(i + 1) % poly.size()];
        if (isect(p, mx, a, b)) {
            cnt++;
        }
    }
    return cnt == 1;
}
// get unit vector that is orthogonal to given vector
point getUnitOrthog(point vec) {
    if (abs(vec.x) < eps || abs(vec.y) < eps) {
        swap(vec.x, vec.y);
        return vec.toUnit();
    }
    point orthog(1, 0);
    orthog.y = -orthog.x * vec.x / vec.y;
    return orthog.toUnit();
}
// circle with center c, radius r and line through points a and b
vector<point> circleLine(point c, double r, point a, point b) {
	point ab = b - a, p = a + ab * dot(c - a, ab) / ab.vlensq();
	double s = cross(b - a, c - a), h2 = r*r - s*s / ab.vlensq();
	if (h2 < 0) return {};
	if (h2 == 0) return {p};
	point h = ab.toUnit() * sqrt(h2);
	return {p - h, p + h};
}