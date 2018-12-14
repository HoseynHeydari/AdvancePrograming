#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
using namespace std;

class IllegalArgumentException{};

class Shape{
public:
    Shape(int init_x, int init_y) : x(init_x), y(init_y) {}
    int get_x() const { return x; }
    int get_y() const { return y; }
    void move(int dx, int dy);

    virtual void scale(int s) = 0;
    virtual void print() = 0;
    virtual double area() = 0;
protected:
    int x;
    int y;
};

void Shape::move(int dx,int dy)
{
    x += dx;
    y += dy;
}

class Rect:public Shape{
public:
    Rect(int init_x, int init_y, int w, int h);
    virtual void scale(int s);
    virtual void print();
    virtual double area();
private:
    int width;
    int height;
};

Rect::Rect(int init_x, int init_y, int w, int h)
    : Shape(init_x, init_y)
{
    if (w <= 0 || h <= 0)
        throw IllegalArgumentException();
    width = w;
    height = h;
}

void Rect::scale(int s)
{
    width *= s;
    height *= s;
}

void Rect::print()
{
    cout << "Rect: " << x << ',' << y << ',' << width << ',' << height << endl;
}

double Rect::area()
{
    return width * height;
}

class Circle:public Shape{
public:
    Circle(int init_x, int init_y, int r);
    virtual void scale(int s);
    virtual void print();
    virtual double area();
private:
    int radius;
};

Circle::Circle(int init_x, int init_y,int r)
    : Shape(init_x, init_y)
{
    if (r <= 0)
        throw IllegalArgumentException();
    radius = r;
}

void Circle::scale(int s)
{
    radius *= s;
}

void Circle::print()
{
    cout << "Circle: " << x << ',' << y << ',' << radius << endl;
}

double Circle::area()
{
    return radius * radius * M_PI;
}

class Equilateral:public Shape{
public:
    Equilateral(int init_x, int init_y, int e);
    virtual void scale(int s);
    virtual void print();
    virtual double area();
private:
    int edge;
};

Equilateral::Equilateral(int init_x, int init_y, int e)
    : Shape(init_x, init_y)
{
    if (e <= 0)
        throw IllegalArgumentException();
    edge = e;
}

void Equilateral::scale(int s)
{
    edge *= s;
}

void Equilateral::print()
{
    cout << "Equilateral" << x << ',' << y << ',' << edge << endl;
}

double Equilateral::area()
{
    return sqrt(3) * 0.25 * edge * edge;
}

class Segment:public Shape{
public:
    Segment(int init_x, int init_y, int delta_x, int delta_y);
    virtual void scale(int s);
    virtual void print();
    virtual double area();
private:
    int delta_x;
    int delta_y;
};

Segment::Segment(int init_x, int init_y, int dx, int dy)
    : Shape(init_x, init_y)
{
    if (delta_x == 0 || delta_y == 0)
        throw IllegalArgumentException();
    delta_x = dx;
    delta_y = dy;
}

void Segment::scale(int s)
{
    delta_x *= s;
    delta_y *= s;
}

void Segment::print()
{
    cout << "" << x << ',' << y << ',' << delta_x << ',' << delta_y << endl;
}

double Segment::area()
{
    throw "Segment has no area!";
}
int main()
{
    vector<Shape*> shapes;

    while (true) {
        cout << "r.    New Rectangle\n";
        cout << "c.    New Circle\n";
        cout << "t.    New Equilateral triangle\n";
        cout << "s.    New Segment\n";
        cout << "p.    Display Shapes\n";
        cout << "m.    Move All\n";
        cout << "s.    Scale All\n";
        cout << "a-i.  Display i_th shape area\n";
        cout << "q.    Exit\n";
        char ch;
        cin >> ch;
        if (ch == 'r') {
            int x, y, w, h  ;
            cout << "enter x, y, width, and height: ";
            cin >> x >> y >> w >> h;
            Rect *rect = new Rect(x, y, w, h);
            shapes.push_back(rect);
        } else if (ch == 'c') {
            int x, y, r;
            cout << "enter x, y, and radius: ";
            cin >> x >> y >> r;
            Circle *circ = new Circle(x, y, r);
            shapes.push_back(circ);
        }  else if (ch == 't') {
            int x, y, e;
            cout << "enter x, y, and edge: ";
            cin >> x >> y >> e;
            Equilateral *triangle = new Equilateral(x, y, e);
            shapes.push_back(triangle);
        } else if (ch == 's') {
            int x, y, dx, dy;
            cout << "enter x, y, delta_x, and delta_y: ";
            cin >> x >> y >> dx >> dy;
            Segment *sgmnt = new Segment(x, y, dx, dy);
            shapes.push_back(sgmnt);
        } else if (ch == 'p') {
            for (int i = 0; i < shapes.size(); i++) {
                cout << '[' << i << ']' << " :";
                shapes[i]->print();
            }
            cout<< endl;
        } else if (ch == 'm') {
            int dx, dy;
            cout << "enter dx, dy: ";
            cin >> dx >> dy;
            for (int i = 0; i < shapes.size(); i++)
                shapes[i]->move(dx, dy);
        } else if (ch == 's') {
            int s;
            cout << "enter s: ";
            cin >> s;
            for (int i = 0; i < shapes.size(); i++)
                shapes[i]->scale(s);
        } else if (ch == 'q') {
            for (int i = 0; i < shapes.size(); i++)
                delete shapes[i];
            break;
        }
    } // while (true)
}
