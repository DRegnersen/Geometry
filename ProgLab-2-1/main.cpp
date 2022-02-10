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

    class Polyline {
    private:
        vector<Point> vertexes;
    public:
        //constructor
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

        long long size() {
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

    class ClosedPolyline : Polyline {
    private:
        bool isClosed;
    public:
        //constructor
        ClosedPolyline(const Polyline &_line_) : Polyline(_line_) {
            isClosed = false;
        }

        ClosedPolyline(initializer_list<Point> _vertexes_) : Polyline(_vertexes_) {
            isClosed = false;
        }

        //copy constructor
        ClosedPolyline(const ClosedPolyline &_closed_line_) : Polyline(_closed_line_) {
            isClosed = _closed_line_.isClosed;
        };

        // assignment operator
        ClosedPolyline &operator=(const ClosedPolyline &_closed_line_) {
            if (this == &_closed_line_) {
                return *this;
            }

            isClosed = _closed_line_.isClosed;

            return *this;
        }

        ClosedPolyline &operator=(const Polyline &_line_) override {
            Polyline::operator=(_line_);
            isClosed = false;

            return *this;
        }

        ClosedPolyline &operator=(initializer_list<Point> _vertexes_) override {
            Polyline::operator=(_vertexes_);
            isClosed = false;

            return *this;
        }

        // indexing operator
        Point &operator[](const long long &_idx_) override {
            if (isClosed) {
                if (_idx_ < 0) {
                    return Polyline::operator[](((_idx_ % Polyline::size()) + Polyline::size()) % Polyline::size());
                } else {
                    return Polyline::operator[](_idx_ % Polyline::size());
                }
            } else {
                return Polyline::operator[](_idx_);
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

            if (_closed_line_.isClosed) {
                out << " >>";
            }
            out << "]";
            return out;
        }

        // ===== FUNCTIONS =====

        void close() {
            isClosed = true;
        }

        void elongate(const Point &_vertex_) override {
            if (isClosed) {
                cout << "<ClosedPolyline> The line is already closed, so it cannot be elongated" << endl;
            } else {
                Polyline::elongate(_vertex_);
            }
        }

        double perimeter() {
            if (!isClosed) {
                cout << "<ClosedPolyline> The line is not closed yet - perimeter counting is not available" << endl;
                return -1;
            } else {
                double _perimeter_ = Polyline::length();
                _perimeter_ += sqrt(
                        pow(operator[](0).getX() - operator[](size() - 1).getX(), 2) +
                        pow(operator[](0).getY() - operator[](size() - 1).getY(), 2));
                return _perimeter_;
            }
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

        Point toVector() {
            return end - begin;
        }

        friend bool areIntersected(DirectSegment AB, DirectSegment CD) {
            double min_AB, max_AB;
            double min_CD, max_CD;

            min_AB = min(AB.begin.getX(), AB.end.getX());
            max_AB = max(AB.begin.getX(), AB.end.getX());

            min_CD = min(CD.begin.getX(), CD.end.getX());
            max_CD = max(CD.begin.getX(), CD.end.getX());

            if (max_AB < min_CD || max_CD < min_AB) {
                return false;
            }

            min_AB = min(AB.begin.getY(), AB.end.getY());
            max_AB = max(AB.begin.getY(), AB.end.getY());

            min_CD = min(CD.begin.getY(), CD.end.getY());
            max_CD = max(CD.begin.getY(), CD.end.getY());

            if (max_AB < min_CD || max_CD < min_AB) {
                return false;
            }

            if (((AB.begin - CD.begin) * AB.toVector()) * ((AB.begin - CD.end) * AB.toVector()) > 0) {
                return false;
            }

            if (((CD.begin - AB.begin) * CD.toVector()) * ((CD.begin - AB.end) * CD.toVector()) > 0) {
                return false;
            }

            return true;
        }
    };

    class Polygon : ClosedPolyline {
    private:
        vector<Point> vertexes;

        bool isAdequate(Point _new_vertex_) {
            for (int i = 1; i < (int) vertexes.size() - 1; i++) {
                if (areIntersected(DirectSegment(vertexes[vertexes.size() - 1], _new_vertex_),
                                   DirectSegment(vertexes[i - 1], vertexes[i]))) {
                    return false;
                }
            }
            return true;
        }

        bool isClosed() {
            if (vertexes.size() <= 2) {
                return false;
            }
            for (int i = 2; i < (int) vertexes.size() - 1; i++) {
                if (areIntersected(DirectSegment(vertexes.back(), vertexes[0]),
                                   DirectSegment(vertexes[i - 1], vertexes[i]))) {
                    return false;
                }
            }
            return true;
        }

    public:
        //constructor
        Polygon(initializer_list<Point> _vertexes_) : ClosedPolyline(_vertexes_) {
            vertexes.clear();
            for (const Point &_point_: _vertexes_) {
                if (this->isAdequate(_point_)) {
                    vertexes.push_back(_point_);
                } else {
                    vertexes.clear();
                    cout << "<Polygon> The points do not form a polygon" << endl;
                    return;
                }
            }
            if (!isClosed()) {
                vertexes.clear();
                cout << "<Polygon> The points do not form a polygon" << endl;
                return;
            }
            close();
        }

        //copy constructor
        Polygon(const Polygon &_polygon_) : ClosedPolyline(_polygon_) {
            vertexes.clear();
            vertexes = _polygon_.vertexes;
        };

        // assignment operator
        Polygon &operator=(const Polygon &_polygon_)

        :
        ClosedPolyline(_polygon_){
                if (this == &_polygon_) {
                    return *this;
                }

                vertexes = _polygon_.vertexes;

                return *this;
        }

        // ===== FUNCTIONS =====

        double perimeter() {
            double _perimeter_ = Polyline::length();
            _perimeter_ += sqrt(
                    pow(operator[](0).getX() - operator[](size() - 1).getX(), 2) +
                    pow(operator[](0).getY() - operator[](size() - 1).getY(), 2));
            return _perimeter_;
        }
    };
}

int main() {
    using namespace geom;

    Point A(1, 2);
    Point B(7, 9);

    Polyline line({A, B, Point(-8, 7)});
    line = {Point(6, 7), Point(9, 10), Point(-7, 49)};

    Polyline line_2 = {Point(-81, 9), Point(6, 7)};

    cout << line.length() << endl;

    ClosedPolyline cl_line = {A, B};
    ClosedPolyline cl_line_2 = {A, B, Point(3, 4)};

    cl_line = {Point(-1, -1), Point(2, 3)};
    //cl_line.elongate(Point(6, 7));
    cout << cl_line << endl;
    cl_line.close();

    cout << cl_line[-5] << endl;

    cout << cl_line.perimeter() << endl;
    cout << line << endl;

    DirectSegment AB(Point(0, 0), Point(0, 4));
    DirectSegment CD(Point(0, 1), Point(5, 1));

    Polygon new_polygon = {Point(0, 0), Point(2, 2), Point(3, 1), Point(2, 1)};

    if (areIntersected(AB, CD)) {
        cout << "YES!" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}
