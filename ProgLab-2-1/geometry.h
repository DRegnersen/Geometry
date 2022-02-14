#ifndef PROGLAB_2_1_GEOMETRY_H
#define PROGLAB_2_1_GEOMETRY_H

#include <iostream>
#include <vector>

using namespace std;

class Point {
private:
    double _x_;
    double _y_;
public:
    // constructor
    explicit Point(const double &x = 0, const double &y = 0) : _x_(x), _y_(y) {}

    // copy constructor
    Point(const Point &point) : _x_(point._x_), _y_(point._y_) {}

    // assignment operator
    Point &operator=(const Point &point);

    // equality operator
    friend bool operator==(const Point &A, const Point &B);

    // inequality operator
    friend bool operator!=(const Point &A, const Point &B);

    // summation operator
    friend Point operator+(const Point &A, const Point &B);

    // subtraction operator
    friend Point operator-(const Point &A, const Point &B);

    //multiplication operator (pseudo scalar multiplication)
    friend double operator*(const Point &A, const Point &B);

    //output operator
    friend ostream &operator<<(ostream &out, const Point &point);

    // ===== FUNCTIONS =====
    double scalar(const Point &other) const;

    double getX() const;

    double getY() const;

    //void abobus();

    void setX(const double &x);

    void setY(const double &y);
};

class DirectSegment {
private:
    Point _begin_;
    Point _end_;
public:
    // constructor
    DirectSegment(const Point &begin, const Point &end) : _begin_(begin), _end_(end) {}

    // copy constructor
    DirectSegment(const DirectSegment &segment) : _begin_(segment._begin_), _end_(segment._end_) {}

    // assignment operator
    DirectSegment &operator=(const DirectSegment &segment);

    //multiplication operator (pseudo scalar multiplication)
    friend double operator*(DirectSegment A, DirectSegment B);

    // output operator
    friend ostream &operator<<(ostream &out, const DirectSegment &segment);

    // ===== FUNCTIONS =====
    double length();

    double scalar(DirectSegment other);

    Point toVector();

    DirectSegment &reverse();

    bool intersects(DirectSegment other);
};

class Polyline {
private:
    vector<Point> _vertexes_;
public:
    //constructor
    Polyline() = default;

    Polyline(initializer_list<Point> vertexes);

    //copy constructor
    Polyline(const Polyline &line);

    // assignment operator
    virtual Polyline &operator=(const Polyline &line);

    virtual Polyline &operator=(initializer_list<Point> vertexes);

    // indexing operator
    virtual Point &operator[](const long long &idx);

    //output operator
    friend ostream &operator<<(ostream &out, Polyline &line);

    // ===== FUNCTIONS =====

    virtual long long size();

    void clear();

    virtual void elongate(const Point &vertex);

    virtual double length();
};

class ClosedPolyline : protected Polyline {
public:
    //constructor
    ClosedPolyline() : Polyline() {}

    ClosedPolyline(const Polyline &_line_) : Polyline(_line_) {}

    ClosedPolyline(initializer_list<Point> vertexes) : Polyline(vertexes) {}

    //copy constructor
    ClosedPolyline(const ClosedPolyline &closed_line) : Polyline(closed_line) {}

    // assignment operator
    ClosedPolyline &operator=(const ClosedPolyline &closed_line);

    ClosedPolyline &operator=(const Polyline &line) override;

    ClosedPolyline &operator=(initializer_list<Point> vertexes) override;

    // indexing operator
    Point &operator[](const long long &idx) override;

    //output operator
    friend ostream &operator<<(ostream &out, ClosedPolyline &closed_line);

    // ===== FUNCTIONS =====

    long long size() override;

    virtual double perimeter();
};

class Polygon : protected ClosedPolyline {
private:
    string _type_;

    bool isAdequate(const Point &new_vertex);

    bool isClosed();

    static double det(const Point &A, const Point &B);

public:
    //constructor
    Polygon() : ClosedPolyline() {}

    Polygon(initializer_list<Point> vertexes);

    //copy constructor
    Polygon(const Polygon &polygon) : ClosedPolyline(polygon) {}

    // assignment operator
    Polygon &operator=(const Polygon &polygon);

    // equality operator
    friend bool operator==(Polygon &A, Polygon &B);

    // inequality operator
    friend bool operator!=(Polygon &A, Polygon &B);

    // less operator
    friend bool operator<(Polygon &A, Polygon &B);

    // greater operator
    friend bool operator>(Polygon &A, Polygon &B);

    // output operator
    friend ostream &operator<<(ostream &out, Polygon &polygon);

    // ===== FUNCTIONS =====

    long long degree();

    double perimeter() override;

    double area();

protected:
    void setType(const string &type_name);

    void add(const Point &point);
};

class Triangle : public Polygon {
public:
    Triangle();

    Triangle(initializer_list<Point> vertexes);
};

class Trapezoid : public Polygon {
public:
    Trapezoid();

    Trapezoid(initializer_list<Point> vertexes);
};

class RegularPolygon : public Polygon {
public:
    // constructor
    RegularPolygon();

    RegularPolygon(initializer_list<Point> vertexes);

    RegularPolygon(int n, double side_len, const Point &center);

    // copy constructor
    explicit RegularPolygon(const Polygon &polygon) : Polygon(polygon) {};

    // assignment operator
    RegularPolygon &operator=(const RegularPolygon &polygon);
};


#endif //PROGLAB_2_1_GEOMETRY_H
