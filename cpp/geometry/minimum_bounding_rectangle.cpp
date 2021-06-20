#include <boost/geometry.hpp>

#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>

#include <vector>
#include <iostream>

class C2DPoint
{
public:
    C2DPoint() = default;
    C2DPoint(double x_, double y_) { x = x_; y = y_;}
    double GetX() const { return x; }
    double GetY() const { return y; }
private:
    double x, y;
};

template<typename T>
std::pair<T, T> CalculateMBR(const std::vector<T> Points)
{
    namespace bg = boost::geometry;
    using point2d = bg::model::point<double, 2, bg::cs::cartesian>;

    boost::geometry::model::polygon<point2d> polygon;

    for(const T& Point : Points)
    {
        bg::append(polygon.outer(), point2d(Point.GetX(), Point.GetY()));
    }

    boost::geometry::model::box<point2d> box;
    boost::geometry::envelope(polygon, box);

    double min_x = bg::get<bg::min_corner, 0>(box);
    double min_y = bg::get<bg::min_corner, 1>(box);
    double max_x = box.max_corner().get<0>();
    double max_y = box.max_corner().get<1>();

    std::cout << "MBR bottom left and top right corners" << std::endl;
    std::cout << min_x << ", " << min_y << ", " << max_x << ", " << max_y << std::endl;

    return std::make_pair(T(min_x, min_y), T(max_x, max_y));
}
template std::pair<C2DPoint, C2DPoint> CalculateMBR(const std::vector<C2DPoint> Points);

int MBR()
{
    std::vector<C2DPoint> Triangle{C2DPoint(-0.5, 0.0), C2DPoint(0.5, 0.0), C2DPoint(0.0, 1.0)};
    auto MBR = CalculateMBR<C2DPoint>(Triangle);
    return 0;
}
