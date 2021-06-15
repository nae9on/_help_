#include <boost/geometry.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>

template<typename T>
std::pair<T, T> CalculateMBR(const std::vector<T> Points);

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

    std::cout << min_x << ", " << min_y << ", " << max_x << ", " << max_y << std::endl;

    return std::make_pair(T(min_x, min_y), T(max_x, max_y));
}
template std::pair<CPoint, CPoint> CalculateMBR(const std::vector<CPoint> Points);
template std::pair<C2DPoint, C2DPoint> CalculateMBR(const std::vector<C2DPoint> Points);

/*
   A
  / \
 /   \
D     B
 \   /
  \ /
   C

A------D
|      |
|      |
|      |
|      |
|      |
B------C

A------D
 |      |
  |      |
   |      |
    |      |
     |      |
      B------C

*/

TEST(TestDiameterWidthOfConvexPolygons)
{
    using TPoint = C2DPoint;

    std::vector<TPoint> Vertices;

    // Polygon 1
    Vertices.push_back(TPoint(std::int32_t(30), std::int32_t(10))); // A
    Vertices.push_back(TPoint(std::int32_t(50), std::int32_t(30))); // B
    Vertices.push_back(TPoint(std::int32_t(30), std::int32_t(50))); // C
    Vertices.push_back(TPoint(std::int32_t(10), std::int32_t(30))); // D
    std::pair<TPoint, TPoint> BBox = CalculateMBR(Vertices);
    CHECK_EQUAL(10.0f, BBox.first.GetX());
    CHECK_EQUAL(10.0f, BBox.first.GetY());
    CHECK_EQUAL(50.0f, BBox.second.GetX());
    CHECK_EQUAL(50.0f, BBox.second.GetY());

    // Polygon 2
    Vertices.clear();
    Vertices.push_back(TPoint(std::int32_t(10), std::int32_t(10))); // A
    Vertices.push_back(TPoint(std::int32_t(10), std::int32_t(50))); // B
    Vertices.push_back(TPoint(std::int32_t(50), std::int32_t(50))); // C
    Vertices.push_back(TPoint(std::int32_t(50), std::int32_t(10))); // D
    BBox = CalculateMBR(Vertices);
    CHECK_EQUAL(10.0f, BBox.first.GetX());
    CHECK_EQUAL(10.0f, BBox.first.GetY());
    CHECK_EQUAL(50.0f, BBox.second.GetX());
    CHECK_EQUAL(50.0f, BBox.second.GetY());

    // Polygon 3
    Vertices.clear();
    Vertices.push_back(TPoint(std::int32_t(10), std::int32_t(10))); // A
    Vertices.push_back(TPoint(std::int32_t(20), std::int32_t(50))); // B
    Vertices.push_back(TPoint(std::int32_t(30), std::int32_t(50))); // C
    Vertices.push_back(TPoint(std::int32_t(20), std::int32_t(10))); // D
    BBox = CalculateMBR(Vertices);
    CHECK_EQUAL(10.0f, BBox.first.GetX());
    CHECK_EQUAL(10.0f, BBox.first.GetY());
    CHECK_EQUAL(30.0f, BBox.second.GetX());
    CHECK_EQUAL(50.0f, BBox.second.GetY());

    // Polygon 4
    Vertices.clear();
    Vertices.push_back(TPoint(std::int32_t(7), std::int32_t(3))); // A
    Vertices.push_back(TPoint(std::int32_t(7), std::int32_t(4))); // B
    Vertices.push_back(TPoint(std::int32_t(9), std::int32_t(2))); // C
    Vertices.push_back(TPoint(std::int32_t(8), std::int32_t(2))); // D
    BBox = CalculateMBR(Vertices);
    CHECK_EQUAL(7.0f, BBox.first.GetX());
    CHECK_EQUAL(2.0f, BBox.first.GetY());
    CHECK_EQUAL(9.0f, BBox.second.GetX());
    CHECK_EQUAL(4.0f, BBox.second.GetY());
}
