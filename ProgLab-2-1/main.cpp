#include <iostream>
#include <vector>
#include <cmath>

namespace geom {
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
        Point &operator=(const Point &point) {
            _x_ = point._x_;
            _y_ = point._y_;

            return *this;
        }

        // equality operator
        friend bool operator==(const Point &A, const Point &B) {
            return (A._x_ == B._x_) && (A._y_ == B._y_);
        }

        // inequality operator
        friend bool operator!=(const Point &A, const Point &B) {
            return (A._x_ != B._x_) || (A._y_ != B._y_);
        }

        // summation operator
        friend Point operator+(const Point &A, const Point &B) {
            return Point(A._x_ + B._x_, A._y_ + B._y_);
        }

        // subtraction operator
        friend Point operator-(const Point &A, const Point &B) {
            return Point(A._x_ - B._x_, A._y_ - B._y_);
        }

        //multiplication operator (pseudo scalar multiplication)
        friend double operator*(const Point &A, const Point &B) {
            return A._x_ * B._y_ - B._x_ * A._y_;
        }

        //output operator
        friend ostream &operator<<(ostream &out, const Point &point) {
            out << "(" << point._x_ << ", " << point._y_ << ")";
            return out;
        }

        // ===== FUNCTIONS =====

        double scalar(const Point &_other_) const {
            return this->_x_ * _other_._x_ + this->_y_ * _other_._y_;
        }

        double getX() const {
            return _x_;
        }

        double getY() const {
            return _y_;
        }

        void setX(const double &x) {
            _x_ = x;
        }

        void setY(const double &y) {
            _y_ = y;
        }
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
        DirectSegment &operator=(const DirectSegment &segment) {
            _begin_ = segment._begin_;
            _end_ = segment._end_;

            return *this;
        }

        //multiplication operator (pseudo scalar multiplication)
        friend double operator*(DirectSegment A, DirectSegment B) {
            return A.toVector().getX() * B.toVector().getY() -
                   B.toVector().getX() * A.toVector().getY();
        }

        // output operator
        friend ostream &operator<<(ostream &out, const DirectSegment &segment) {
            out << "[" << segment._begin_ << ", " << segment._end_ << "]";
            return out;
        }

        // ===== FUNCTIONS =====
        double length() {
            return sqrt(pow(_end_.getX() - _begin_.getX(), 2) + pow(_end_.getY() - _begin_.getY(), 2));
        }

        double scalar(DirectSegment other) {
            return this->toVector().getX() * other.toVector().getX() +
                   this->toVector().getY() * other.toVector().getY();
        }

        Point toVector() {
            return _end_ - _begin_;
        }

        DirectSegment &reverse() {
            swap(_begin_, _end_);
            return *this;
        }

        bool intersects(DirectSegment other) {
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
    };

    class Polyline {
    private:
        vector<Point> _vertexes_;
    public:
        //constructor
        Polyline() = default;

        Polyline(initializer_list<Point> vertexes) {
            _vertexes_.clear();
            for (const Point &point: vertexes) {
                _vertexes_.push_back(point);
            }
        }

        //copy constructor
        Polyline(const Polyline &line) {
            _vertexes_.clear();
            _vertexes_ = line._vertexes_;
        };

        // assignment operator
        virtual Polyline &operator=(const Polyline &line) {
            _vertexes_.clear();
            _vertexes_ = line._vertexes_;

            return *this;
        }

        virtual Polyline &operator=(initializer_list<Point> vertexes) {
            _vertexes_.clear();

            for (const Point &point: vertexes) {
                _vertexes_.push_back(point);
            }

            return *this;
        }

        // indexing operator
        virtual Point &operator[](const long long &idx) {
            if (idx >= 0 && idx < _vertexes_.size()) {
                return _vertexes_[idx];
            } else {
                cout << "<Polyline> Index is out of range" << endl;
                return _vertexes_[0];
            }
        }

        //output operator
        friend ostream &operator<<(ostream &out, Polyline &line) {
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

        virtual long long size() {
            return _vertexes_.size();
        }

        void clear() {
            _vertexes_.clear();
        }

        virtual void elongate(const Point &vertex) {
            _vertexes_.push_back(vertex);
        }

        virtual double length() {
            double _length_ = 0;
            for (int i = 0; i < _vertexes_.size() - 1; i++) {
                _length_ += sqrt(pow(_vertexes_[i + 1].getX() - _vertexes_[i].getX(), 2)
                                 + pow(_vertexes_[i + 1].getY() - _vertexes_[i].getY(), 2));
            }
            return _length_;
        }
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
        ClosedPolyline &operator=(const ClosedPolyline &closed_line) {
            Polyline::operator=(closed_line);
            return *this;
        }

        ClosedPolyline &operator=(const Polyline &line) override {
            Polyline::operator=(line);
            return *this;
        }

        ClosedPolyline &operator=(initializer_list<Point> vertexes) override {
            Polyline::operator=(vertexes);
            return *this;
        }

        // indexing operator
        Point &operator[](const long long &idx) override {
            if (idx < 0) {
                return Polyline::operator[](((idx % Polyline::size()) + Polyline::size()) % Polyline::size());
            } else {
                return Polyline::operator[](idx % Polyline::size());
            }
        }

        //output operator
        friend ostream &operator<<(ostream &out, ClosedPolyline &closed_line) {
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
        string _type_;

        bool isAdequate(const Point &new_vertex) {
            for (int i = 1; i < size() - 1; i++) {
                if (DirectSegment(operator[](size() - 1), new_vertex).intersects(
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

        Polygon(initializer_list<Point> vertexes) : ClosedPolyline(vertexes), _type_("...") {
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

        //copy constructor
        Polygon(const Polygon &polygon) : ClosedPolyline(polygon) {};

        // assignment operator
        Polygon &operator=(const Polygon &polygon) {
            ClosedPolyline::operator=(polygon);
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
        friend ostream &operator<<(ostream &out, Polygon &polygon) {
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
        void setType(const string &type_name) {
            _type_ = type_name;
        }

        void add(const Point &point) {
            elongate(point);
        }
    };

    class Triangle : public Polygon {
    public:
        Triangle() : Polygon() {
            setType("tri");
        }

        Triangle(initializer_list<Point> vertexes) : Polygon(vertexes) {
            setType("tri");
            if (vertexes.size() != 3) {
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

        Trapezoid(initializer_list<Point> vertexes) : Polygon(vertexes) {
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
    };

    class RegularPolygon : public Polygon {
    public:
        // constructor
        RegularPolygon() : Polygon() {
            setType("reg");
        }

        RegularPolygon(initializer_list<Point> vertexes) : Polygon(vertexes) {
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

        RegularPolygon(int n, double side_len, const Point &center) : Polygon() {
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
        explicit RegularPolygon(const Polygon &polygon) : Polygon(polygon) {};

        // assignment operator
        RegularPolygon &operator=(const RegularPolygon &polygon) {
            Polygon::operator=(polygon);
            return *this;
        };
    };
}

int main() {
    using namespace geom;
    RegularPolygon some_regular(4, 2, Point(0, 0));
    cout << some_regular << endl;


    return 0;
}
