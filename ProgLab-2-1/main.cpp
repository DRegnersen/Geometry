#include <iostream>
#include <vector>
#include <cmath>

namespace geom {
    using namespace std;

    class Point {
    private:
        double x;
        double y;
    public:
        // constructor
        Point(const double &_x_, const double &_y_) {
            x = _x_;
            y = _y_;
        }

        Point() {
            x = 0;
            y = 0;
        }

        // copy constructor
        Point(const Point &_point_) : x(_point_.x), y(_point_.y) {}

        // assignment operator
        Point &operator=(const Point &_point_) {
            if (this == &_point_) {
                return *this;
            }
            x = _point_.x;
            y = _point_.y;

            return *this;
        }

        // equality operator
        friend bool operator==(const Point &A, const Point &B) {
            return (A.x == B.x) && (A.y == B.y);
        }

        // inequality operator
        friend bool operator!=(const Point &A, const Point &B) {
            return (A.x != B.x) || (A.y != B.y);
        }

        // summation operator
        friend Point operator+(const Point &A, const Point &B) {
            Point _result_;
            _result_.x = A.x + B.x;
            _result_.y = A.y + B.y;
            return _result_;
        }

        // subtraction operator
        friend Point operator-(const Point &A, const Point &B) {
            Point _result_;
            _result_.x = A.x - B.x;
            _result_.y = A.y - B.y;
            return _result_;
        }

        //multiplication operator (pseudo scalar multiplication)
        friend double operator*(const Point &A, const Point &B) {
            return A.x * B.y - B.x * A.y;
        }

        //output operator
        friend ostream &operator<<(ostream &out, const Point &_point_) {
            out << "(" << _point_.x << ", " << _point_.y << ")";
            return out;
        }

        // ===== FUNCTIONS =====

        double scalar(const Point &_other_) {
            return this->x * _other_.x + this->y * _other_.y;
        }

        double getX() const {
            return x;
        }

        double getY() const {
            return y;
        }

        void setX(const double &_x_) {
            x = _x_;
        }

        void setY(const double &_y_) {
            y = _y_;
        }
    };

    class DirectSegment {
    private:
        Point begin;
        Point end;
    public:
        // constructor
        DirectSegment(const Point &_begin_, const Point &_end_) {
            begin = _begin_;
            end = _end_;
        }

        // copy constructor
        DirectSegment(const DirectSegment &_segment_) : begin(_segment_.begin), end(_segment_.end) {};

        // assignment operator
        DirectSegment &operator=(const DirectSegment &_segment_) {
            if (this == &_segment_) {
                return *this;
            }
            begin = _segment_.begin;
            end = _segment_.end;

            return *this;
        }

        //multiplication operator (pseudo scalar multiplication)
        friend double operator*(DirectSegment A, DirectSegment B) {
            return A.toVector().getX() * B.toVector().getY() -
                   B.toVector().getX() * A.toVector().getY();
        }

        // output operator
        friend ostream &operator<<(ostream &out, const DirectSegment &_segment_) {
            out << _segment_.begin << " -> " << _segment_.end;
            return out;
        }

        // ===== FUNCTIONS =====
        double length() {
            return sqrt(pow(end.getX() - begin.getX(), 2) + pow(end.getY() - begin.getY(), 2));
        }

        double scalar(DirectSegment _other_) {
            return this->toVector().getX() * _other_.toVector().getX() +
                   this->toVector().getY() * _other_.toVector().getY();
        }

        Point toVector() {
            return end - begin;
        }

        DirectSegment &reverse() {
            swap(begin, end);
            return *this;
        }

        bool intersects(DirectSegment _other_) {
            double min_this, max_this;
            double min_other, max_other;

            min_this = min(this->begin.getX(), this->end.getX());
            max_this = max(this->begin.getX(), this->end.getX());

            min_other = min(_other_.begin.getX(), _other_.end.getX());
            max_other = max(_other_.begin.getX(), _other_.end.getX());

            if (max_this < min_other || max_other < min_this) {
                return false;
            }

            min_this = min(this->begin.getY(), this->end.getY());
            max_this = max(this->begin.getY(), this->end.getY());

            min_other = min(_other_.begin.getY(), _other_.end.getY());
            max_other = max(_other_.begin.getY(), _other_.end.getY());

            if (max_this < min_other || max_other < min_this) {
                return false;
            }

            if (((this->begin - _other_.begin) * this->toVector()) * ((this->begin - _other_.end) * this->toVector()) >
                0) {
                return false;
            }

            if (((_other_.begin - this->begin) * _other_.toVector()) *
                ((_other_.begin - this->end) * _other_.toVector()) > 0) {
                return false;
            }

            return true;
        }
    };

    class Polyline {
    private:
        vector<Point> vertexes;
    public:
        //constructor
        Polyline() {}

        Polyline(initializer_list<Point> _vertexes_) {
            vertexes.clear();
            for (const Point &_point_: _vertexes_) {
                vertexes.push_back(_point_);
            }
        }

        //copy constructor
        Polyline(const Polyline &_line_) {
            vertexes.clear();
            vertexes = _line_.vertexes;
        };

        // assignment operator
        virtual Polyline &operator=(const Polyline &_line_) {
            if (this == &_line_) {
                return *this;
            }
            vertexes.clear();
            vertexes = _line_.vertexes;

            return *this;
        }

        virtual Polyline &operator=(initializer_list<Point> _vertexes_) {
            vertexes.clear();

            for (const Point &_point_: _vertexes_) {
                vertexes.push_back(_point_);
            }

            return *this;
        }

        // indexing operator
        virtual Point &operator[](const long long &_idx_) {
            if (_idx_ >= 0 && _idx_ < vertexes.size()) {
                return vertexes[_idx_];
            } else {
                cout << "<Polyline> Index is out of range" << endl;
                return vertexes[0];
            }
        }

        //output operator
        friend ostream &operator<<(ostream &out, Polyline &_line_) {
            out << "[";
            for (int i = 0; i < _line_.size(); i++) {
                if (i != 0) {
                    out << ", ";
                }
                out << _line_[i];
            }
            out << "]";
            return out;
        }

        // ===== FUNCTIONS =====

        virtual long long size() {
            return vertexes.size();
        }

        void clear() {
            vertexes.clear();
        }

        virtual void elongate(const Point &_vertex_) {
            vertexes.push_back(_vertex_);
        }

        virtual double length() {
            double _length_ = 0;
            for (int i = 0; i < vertexes.size() - 1; i++) {
                _length_ += sqrt(pow(vertexes[i + 1].getX() - vertexes[i].getX(), 2)
                                 + pow(vertexes[i + 1].getY() - vertexes[i].getY(), 2));
            }
            return _length_;
        }
    };

    class ClosedPolyline : protected Polyline {
    public:
        //constructor
        ClosedPolyline() : Polyline() {}

        ClosedPolyline(const Polyline &_line_) : Polyline(_line_) {}

        ClosedPolyline(initializer_list<Point> _vertexes_) : Polyline(_vertexes_) {}

        //copy constructor
        ClosedPolyline(const ClosedPolyline &_closed_line_) : Polyline(_closed_line_) {}

        // assignment operator
        ClosedPolyline &operator=(const ClosedPolyline &_closed_line_) {
            Polyline::operator=(_closed_line_);
            return *this;
        }

        ClosedPolyline &operator=(const Polyline &_line_) override {
            Polyline::operator=(_line_);
            return *this;
        }

        ClosedPolyline &operator=(initializer_list<Point> _vertexes_) override {
            Polyline::operator=(_vertexes_);
            return *this;
        }

        // indexing operator
        Point &operator[](const long long &_idx_) override {
            if (_idx_ < 0) {
                return Polyline::operator[](((_idx_ % Polyline::size()) + Polyline::size()) % Polyline::size());
            } else {
                return Polyline::operator[](_idx_ % Polyline::size());
            }
        }

        //output operator
        friend ostream &operator<<(ostream &out, ClosedPolyline &_closed_line_) {
            out << "[";
            for (int i = 0; i < _closed_line_.size(); i++) {
                if (i != 0) {
                    out << ", ";
                }
                out << _closed_line_[i];
            }

            out << " >>]";
            return out;
        }

        // ===== FUNCTIONS =====

        long long size() override {
            return Polyline::size();
        }

        virtual double perimeter() {
            double _perimeter_ = Polyline::length();
            _perimeter_ += sqrt(
                    pow(operator[](0).getX() - operator[](size() - 1).getX(), 2) +
                    pow(operator[](0).getY() - operator[](size() - 1).getY(), 2));
            return _perimeter_;
        }
    };

    class Polygon : protected ClosedPolyline {
    private:
        string type;

        bool isAdequate(const Point &_new_vertex_) {
            for (int i = 1; i < size() - 1; i++) {
                if (DirectSegment(operator[](size() - 1), _new_vertex_).intersects(
                        DirectSegment(operator[](i - 1), operator[](i)))) {
                    return false;
                }
            }
            return true;
        }

        bool isClosed() {
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

        static double det(const Point &A, const Point &B) {
            return A.getX() * B.getY() - B.getX() * A.getY();
        }

    public:
        //constructor
        Polygon() : ClosedPolyline() {}

        Polygon(initializer_list<Point> _vertexes_) : ClosedPolyline(_vertexes_) {
            type = "...";
            clear();
            for (const Point &_point_: _vertexes_) {
                if (isAdequate(_point_)) {
                    ClosedPolyline::elongate(_point_);
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

        //copy constructor
        Polygon(const Polygon &_polygon_) : ClosedPolyline(_polygon_) {};

        // assignment operator
        Polygon &operator=(const Polygon &_polygon_) {
            ClosedPolyline::operator=(_polygon_);
            return *this;
        };

        // equality operator
        friend bool operator==(Polygon &A, Polygon &B) {
            return A.area() == B.area();
        }

        // inequality operator
        friend bool operator!=(Polygon &A, Polygon &B) {
            return A.area() != B.area();
        }

        // less operator
        friend bool operator<(Polygon &A, Polygon &B) {
            return A.area() < B.area();
        }

        // greater operator
        friend bool operator>(Polygon &A, Polygon &B) {
            return A.area() > B.area();
        }

        // output operator
        friend ostream &operator<<(ostream &out, Polygon &_polygon_) {
            out << "[" << _polygon_.type << "][";
            for (int i = 0; i < _polygon_.size(); i++) {
                if (i != 0) {
                    out << ", ";
                }
                out << _polygon_[i];
            }

            out << "]";
            return out;
        }

        // ===== FUNCTIONS =====

        long long degree() {
            return ClosedPolyline::size();
        }

        double perimeter() override {
            return ClosedPolyline::perimeter();
        }

        double area() {
            double _area_ = 0;
            for (int i = 0; i < size() - 1; i++) {
                _area_ += det(operator[](i), operator[](i + 1));
            }

            return abs(_area_) / 2;
        }

    protected:
        void setType(const string &_typename_) {
            type = _typename_;
        }

        void add(Point _point_) {
            elongate(_point_);
        }
    };

    class Triangle : public Polygon {
    public:
        Triangle() : Polygon() {
            setType("tri");
        }

        Triangle(initializer_list<Point> _vertexes_) : Polygon(_vertexes_) {
            setType("tri");
            if (_vertexes_.size() != 3) {
                clear();
                cout << "<Triangle> The number of vertexes is not equal to 3" << endl;
            }
        }
    };

    class Trapezoid : public Polygon {
    public:
        Trapezoid() : Polygon() {
            setType("tpz");
        }

        Trapezoid(initializer_list<Point> _vertexes_) : Polygon(_vertexes_) {
            setType("tpz");
            if (_vertexes_.size() != 4) {
                clear();
                cout << "<Trapezoid> The number of vertexes is not equal to 4" << endl;
            } else {
                vector<Point> vertexes;
                bool first_pair, second_pair;

                for (const Point &_point_: _vertexes_) {
                    vertexes.push_back(_point_);
                }
                first_pair = DirectSegment(vertexes[0], vertexes[1]) *
                             DirectSegment(vertexes[2], vertexes[3]) == 0;

                second_pair = DirectSegment(vertexes[1], vertexes[2]) *
                              DirectSegment(vertexes[3], vertexes[0]) == 0;

                if (first_pair == second_pair) {
                    clear();
                    cout << "<Trapezoid> The points do not form a trapezoid" << endl;
                }
            }
        }
    };

    class RegularPolygon : public Polygon {
    public:
        // constructor
        RegularPolygon() : Polygon() {
            setType("reg");
        }

        RegularPolygon(initializer_list<Point> _vertexes_) : Polygon(_vertexes_) {
            setType("reg");
            vector<Point> vertexes;
            double prev;

            for (const Point &_point_: _vertexes_) {
                vertexes.push_back(_point_);
            }

            for (int i = 1; i < vertexes.size(); i++) {
                if (i == 1) {
                    prev = DirectSegment(vertexes[i - 1], vertexes[i]).length();
                } else {
                    if (DirectSegment(vertexes[i - 1], vertexes[i]).length() != prev) {
                        clear();
                        cout << "<RegularPolygon> The points do not form a regular polygon" << endl;
                        return;
                    }
                }

            }
        }

        RegularPolygon(int n, const Point &center, double side_len) : Polygon() {
            setType("reg");

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

        // copy constructor
        RegularPolygon(const Polygon &_polygon_) : Polygon(_polygon_) {};

        // assignment operator
        RegularPolygon &operator=(const RegularPolygon &_polygon_) {
            Polygon::operator=(_polygon_);
            return *this;
        };
    };
}

int main() {
    using namespace geom;

    return 0;
}
