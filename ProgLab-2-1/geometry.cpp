#include "geometry.h"
#include <cmath>

// assignment operator
Point &Point::operator=(const Point &point) {
    _x_ = point._x_;
    _y_ = point._y_;

    return *this;
}

// equality operator
bool operator==(const Point &A, const Point &B) {
    return (A._x_ == B._x_) && (A._y_ == B._y_);
}

// inequality operator
bool operator!=(const Point &A, const Point &B) {
    return (A._x_ != B._x_) || (A._y_ != B._y_);
}

// summation operator
Point operator+(const Point &A, const Point &B) {
    return Point(A._x_ + B._x_, A._y_ + B._y_);
}

// subtraction operator
Point operator-(const Point &A, const Point &B) {
    return Point(A._x_ - B._x_, A._y_ - B._y_);
}

//multiplication operator (pseudo scalar multiplication)
double operator*(const Point &A, const Point &B) {
    return A._x_ * B._y_ - B._x_ * A._y_;
}

//output operator
ostream &operator<<(ostream &out, const Point &point) {
    out << "(" << point._x_ << ", " << point._y_ << ")";
    return out;
}

// ===== FUNCTIONS =====
double Point::scalar(const Point &other) const {
    return this->_x_ * other._x_ + this->_y_ * other._y_;
}

double Point::getX() const {
    return _x_;
}

double Point::getY() const {
    return _y_;
}

void Point::setX(const double &x) {
    _x_ = x;
}

void Point::setY(const double &y) {
    _y_ = y;
}

// assignment operator
DirectSegment &DirectSegment::operator=(const DirectSegment &segment) {
    _begin_ = segment._begin_;
    _end_ = segment._end_;

    return *this;
}

//multiplication operator (pseudo scalar multiplication)
double operator*(DirectSegment A, DirectSegment B) {
    return A.toVector().getX() * B.toVector().getY() -
           B.toVector().getX() * A.toVector().getY();
}

// output operator
ostream &operator<<(ostream &out, const DirectSegment &segment) {
    out << "[" << segment._begin_ << ", " << segment._end_ << "]";
    return out;
}

// ===== FUNCTIONS =====
double DirectSegment::length() {
    return sqrt(pow(_end_.getX() - _begin_.getX(), 2) + pow(_end_.getY() - _begin_.getY(), 2));
}

double DirectSegment::scalar(DirectSegment other) {
    return this->toVector().getX() * other.toVector().getX() +
           this->toVector().getY() * other.toVector().getY();
}

Point DirectSegment::toVector() {
    return _end_ - _begin_;
}

DirectSegment &DirectSegment::reverse() {
    swap(_begin_, _end_);
    return *this;
}

bool DirectSegment::intersects(DirectSegment other) {
    double min_this, max_this;
    double min_other, max_other;

    min_this = min(this->_begin_.getX(), this->_end_.getX());
    max_this = max(this->_begin_.getX(), this->_end_.getX());

    min_other = min(other._begin_.getX(), other._end_.getX());
    max_other = max(other._begin_.getX(), other._end_.getX());

    if (max_this < min_other || max_other < min_this) {
        return false;
    }

    min_this = min(this->_begin_.getY(), this->_end_.getY());
    max_this = max(this->_begin_.getY(), this->_end_.getY());

    min_other = min(other._begin_.getY(), other._end_.getY());
    max_other = max(other._begin_.getY(), other._end_.getY());

    if (max_this < min_other || max_other < min_this) {
        return false;
    }

    if (((this->_begin_ - other._begin_) * this->toVector()) *
        ((this->_begin_ - other._end_) * this->toVector()) > 0) {
        return false;
    }

    if (((other._begin_ - this->_begin_) * other.toVector()) *
        ((other._begin_ - this->_end_) * other.toVector()) > 0) {
        return false;
    }

    return true;
}

Polyline::Polyline(initializer_list<Point> vertexes) {
    _vertexes_.clear();
    for (const Point &point: vertexes) {
        _vertexes_.push_back(point);
    }
}

//copy constructor
Polyline::Polyline(const Polyline &line) {
    _vertexes_.clear();
    _vertexes_ = line._vertexes_;
}

// assignment operator
Polyline &Polyline::operator=(const Polyline &line) {
    _vertexes_.clear();
    _vertexes_ = line._vertexes_;

    return *this;
}

Polyline &Polyline::operator=(initializer_list<Point> vertexes) {
    _vertexes_.clear();

    for (const Point &point: vertexes) {
        _vertexes_.push_back(point);
    }

    return *this;
}

// indexing operator
Point &Polyline::operator[](const long long &idx) {
    if (idx >= 0 && idx < _vertexes_.size()) {
        return _vertexes_[idx];
    } else {
        cout << "<Polyline> Index is out of range" << endl;
        return _vertexes_[0];
    }
}

//output operator
ostream &operator<<(ostream &out, Polyline &line) {
    out << "[";
    for (int i = 0; i < line.size(); i++) {
        if (i != 0) {
            out << ", ";
        }
        out << line[i];
    }
    out << "]";
    return out;
}

// ===== FUNCTIONS =====

long long Polyline::size() {
    return _vertexes_.size();
}

void Polyline::clear() {
    _vertexes_.clear();
}

void Polyline::elongate(const Point &vertex) {
    _vertexes_.push_back(vertex);
}

double Polyline::length() {
    double _length_ = 0;
    for (int i = 0; i < _vertexes_.size() - 1; i++) {
        _length_ += sqrt(pow(_vertexes_[i + 1].getX() - _vertexes_[i].getX(), 2)
                         + pow(_vertexes_[i + 1].getY() - _vertexes_[i].getY(), 2));
    }
    return _length_;
}


// assignment operator
ClosedPolyline &ClosedPolyline::operator=(const ClosedPolyline &closed_line) {
    Polyline::operator=(closed_line);
    return *this;
}

ClosedPolyline &ClosedPolyline::operator=(const Polyline &line) {
    Polyline::operator=(line);
    return *this;
}

ClosedPolyline &ClosedPolyline::operator=(initializer_list<Point> vertexes) {
    Polyline::operator=(vertexes);
    return *this;
}

// indexing operator
Point &ClosedPolyline::operator[](const long long &idx) {
    if (idx < 0) {
        return Polyline::operator[](((idx % Polyline::size()) + Polyline::size()) % Polyline::size());
    } else {
        return Polyline::operator[](idx % Polyline::size());
    }
}

//output operator
ostream &operator<<(ostream &out, ClosedPolyline &closed_line) {
    out << "[";
    for (int i = 0; i < closed_line.size(); i++) {
        if (i != 0) {
            out << ", ";
        }
        out << closed_line[i];
    }

    out << " >>]";
    return out;
}

// ===== FUNCTIONS =====

long long ClosedPolyline::size() {
    return Polyline::size();
}

double ClosedPolyline::perimeter() {
    double _perimeter_ = Polyline::length();
    _perimeter_ += sqrt(
            pow(operator[](0).getX() - operator[](size() - 1).getX(), 2) +
            pow(operator[](0).getY() - operator[](size() - 1).getY(), 2));
    return _perimeter_;
}


bool Polygon::isAdequate(const Point &new_vertex) {
    for (int i = 1; i < size() - 1; i++) {
        if (DirectSegment(operator[](size() - 1), new_vertex).intersects(
                DirectSegment(operator[](i - 1), operator[](i)))) {
            return false;
        }
    }
    return true;
}

bool Polygon::isClosed() {
    if (size() <= 2) {
        return false;
    }
    for (int i = 2; i < size() - 1; i++) {
        if (DirectSegment(operator[](size() - 1), operator[](0)).intersects(
                DirectSegment(operator[](i - 1), operator[](i)))) {
            return false;
        }
    }
    return true;
}

double Polygon::det(const Point &A, const Point &B) {
    return A.getX() * B.getY() - B.getX() * A.getY();
}


Polygon::Polygon(initializer_list<Point> vertexes) : ClosedPolyline(vertexes), _type_("...") {
    clear();
    for (const Point &point: vertexes) {
        if (isAdequate(point)) {
            ClosedPolyline::elongate(point);
        } else {
            clear();
            cout << "<Polygon> The points do not form a polygon" << endl;
            return;
        }
    }
    if (!isClosed()) {
        clear();
        cout << "<Polygon> The points do not form a polygon" << endl;
    }
}

// assignment operator
Polygon &Polygon::operator=(const Polygon &polygon) {
    ClosedPolyline::operator=(polygon);
    return *this;
};

// equality operator
bool operator==(Polygon &A, Polygon &B) {
    return A.area() == B.area();
}

// inequality operator
bool operator!=(Polygon &A, Polygon &B) {
    return A.area() != B.area();
}

// less operator
bool operator<(Polygon &A, Polygon &B) {
    return A.area() < B.area();
}

// greater operator
bool operator>(Polygon &A, Polygon &B) {
    return A.area() > B.area();
}

// output operator
ostream &operator<<(ostream &out, Polygon &polygon) {
    out << "[" << polygon._type_ << "][";
    for (int i = 0; i < polygon.size(); i++) {
        if (i != 0) {
            out << ", ";
        }
        out << polygon[i];
    }

    out << "]";
    return out;
}

// ===== FUNCTIONS =====

long long Polygon::degree() {
    return ClosedPolyline::size();
}

double Polygon::perimeter() {
    return ClosedPolyline::perimeter();
}

double Polygon::area() {
    double _area_ = 0;
    for (int i = 0; i < size() - 1; i++) {
        _area_ += det(operator[](i), operator[](i + 1));
    }

    return abs(_area_) / 2;
}

void Polygon::setType(const string &type_name) {
    _type_ = type_name;
}

void Polygon::add(const Point &point) {
    elongate(point);
}


Triangle::Triangle() : Polygon() {
    setType("tri");
}

Triangle::Triangle(initializer_list<Point> vertexes) : Polygon(vertexes) {
    setType("tri");
    if (vertexes.size() != 3) {
        clear();
        cout << "<Triangle> The number of vertexes is not equal to 3" << endl;
    }
}


Trapezoid::Trapezoid() : Polygon() {
    setType("tpz");
}

Trapezoid::Trapezoid(initializer_list<Point> vertexes) : Polygon(vertexes) {
    setType("tpz");
    if (vertexes.size() != 4) {
        clear();
        cout << "<Trapezoid> The number of vertexes is not equal to 4" << endl;
    } else {
        vector<Point> _vertexes_;
        bool first_pair, second_pair;

        for (const Point &point: vertexes) {
            _vertexes_.push_back(point);
        }
        first_pair = DirectSegment(_vertexes_[0], _vertexes_[1]) *
                     DirectSegment(_vertexes_[2], _vertexes_[3]) == 0;

        second_pair = DirectSegment(_vertexes_[1], _vertexes_[2]) *
                      DirectSegment(_vertexes_[3], _vertexes_[0]) == 0;

        if (first_pair == second_pair) {
            clear();
            cout << "<Trapezoid> The points do not form a trapezoid" << endl;
        }
    }
}

// constructor
RegularPolygon::RegularPolygon() : Polygon() {
    setType("reg");
}

RegularPolygon::RegularPolygon(initializer_list<Point> vertexes) : Polygon(vertexes) {
    setType("reg");
    vector<Point> _vertexes_;
    double prev;

    for (const Point &point: vertexes) {
        _vertexes_.push_back(point);
    }

    for (int i = 1; i < _vertexes_.size(); i++) {
        if (i == 1) {
            prev = DirectSegment(_vertexes_[i - 1], _vertexes_[i]).length();
        } else {
            if (DirectSegment(_vertexes_[i - 1], _vertexes_[i]).length() != prev) {
                clear();
                cout << "<RegularPolygon> The points do not form a regular polygon" << endl;
                return;
            }
        }

    }
}

RegularPolygon::RegularPolygon(int n, double side_len, const Point &center) : Polygon() {
    setType("reg");
    if (n <= 2) {
        cout << "<RegularPolygon> The points do not form a polygon" << endl;
        return;
    }

    double x = side_len / 2;
    double y = side_len * tan(((n - 2) * M_PI) / (2 * n)) / 2;

    add(Point(x + center.getX(), y + center.getY()));

    double cs, sn;
    double new_x, new_y;
    for (int i = 0; i < n - 1; i++) {
        cs = cos(2 * M_PI / n);
        sn = sin(2 * M_PI / n);

        new_x = x * cs - y * sn;
        new_y = x * sn + y * cs;

        add(Point(new_x + center.getX(), new_y + center.getY()));

        x = new_x;
        y = new_y;
    }
}

// assignment operator
RegularPolygon &RegularPolygon::operator=(const RegularPolygon &polygon) {
    Polygon::operator=(polygon);
    return *this;
}


