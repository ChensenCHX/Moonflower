struct point
{
    double x,y;
    point() {}
    point(double x, double y):x(x), y(y) {}
    point operator+(const point &a) const
    {
        return point(x+a.x,y+a.y);
    }
    point operator-(const point &a) const
    {
        return point(x-a.x,y-a.y);
    }
    point operator*(const double &a) const
    {
        return point(x*a,y*a);
    }
    double operator*(const point &a) const  //叉乘
    {
        return x*a.y-a.x*y;
    }
    double operator^(const point &a) const  //点乘
    {
        return x*a.x+y*a.y;
    }
    point operator/(const double &a) const
    {
        return point(x/a,y/a);
    }
    bool operator==(const point &a) const
    {
        return !sign(x-a.x)&&!sign(y-a.y);
    }
    bool operator<(const point &a) const
    {
        return fabs(x-a.x)<=eps?y<a.y:x<a.x;
    }
};
struct line  //x为起点，y为方向
{
    point x,y;
    line(point a=point(),point b=point())
    {
        x=a,y=b;
    }
};
struct segm
{
    point x,y;
    segm(point a=point(),point b=point())
    {
        x=a,y=b;
    }
};
const int max_pol=1010;
struct poly
{
    int idx;
    point num[max_pol];
    poly(int x=0)
    {
        idx=x;
    }
};