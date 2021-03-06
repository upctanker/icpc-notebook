// Convex Hull Trick

// In case of floating point parameters swap long long with long double
typedef long long type;
struct line { type b, m; }

// Order by increasing m if b is equal, otherwise by decreasing b
// If you need the minimum convex hull use { -b, -m }
// [](line s, line t){ return s.b == t.b ? s.m < t.m : s.b > t.b }

// nh: number of lines on convex hull
// pos: position for linear time search
// hull: lines in the convex hull
int nh, pos;
line hull[N];

bool check(line s, line t, line u) {
  return (s.b - t.b)*(u.m - s.m) < (s.b - u.b)*(t.m - s.m);
}

// Add new line to convex hull, if possible
// Must receive lines in the correct order, otherwise it won't work
void update(line s) {
  // 1. if first lines have the same b, get the one with bigger m
  // 2. if line is parallel to the one at the top, ignore
  // 3. pop lines that are worse
  // 3.1 if you can do a linear time search, use 
  // 4. add new line

  if (nh == 1 and hull[nh-1].b == s.b) nh--;
  if (nh > 0  and hull[nh-1].m >= s.m) return;
  while (nh >= 2 and !check(hull[nh-2], hull[nh-1], l)) nh--, pos = min(pos, nh);
  hull[nh++] = l;
}

type eval(int id, type x) { return hull[id].b + hull[id].m * x; }

/*
// Linear search query - O(n) for all queries
// Only possible if the queries always move to the right
type query(type x) {
  while (pos+1 < nh and eval(pos, x) > eval(pos+1, x)) pos++;
  return eval(pos, x);
}
*/

// Ternary search query - O(logn) for each query
type query(type x) {
  int lo = 0, hi = nh-1;
  while (lo < hi) {
    int mid = (lo+hi)/2;
    if (eval(mid, x) < eval(mid+1, x)) hi = mid;
    else lo = mid+1;
  }
  return eval(lo, x);
}

// better use geometry line_intersect (this assumes s and t are not parallel)
ld intersect_x(line s, line t) { return (t.b - s.b)/(ld)(s.m - t.m); }
ld intersect_y(line s, line t) { return s.b + s.m * intersect_x(s, t); }
