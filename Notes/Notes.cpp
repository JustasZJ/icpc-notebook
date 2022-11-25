/*
---
Pick's theorem:
If a polygon has all integer coordinates then the area A is
A = i + b / 2 - 1
where i is the number of integer points interior to the polygon
b is the number of integer points on the boundary
---
Shoelace formula:
1/2 * (x1*y2 - x2*y1 + x2*y3 - x3*y2 + ... + xn*y1 - x1*yn)
---
Euler's formula:
For a connected planar graph with v vertices, e edges and f faces (including outer)
v - e + f = 2
*/
// Mo's sorting order
bool cmp(Query A, Query B)
{
  if (A.l / S != B.l / S) return A.l / S < B.l / S;
  return A.r > B.r
}