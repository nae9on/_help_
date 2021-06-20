#include <boost/geometry.hpp>

#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>

#include <vector>
#include <iostream>

namespace
{

template<typename T>
T ConvertToBestApproximation(double x, double y)
{
    return T(x, y);
}

}

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


/*
 *  Compute the Minimum Oriented Bounding Box around a point cloud
 *  See section "Arbitrarily oriented minimum bounding box"
 *  https://en.wikipedia.org/wiki/Minimum_bounding_box#Arbitrarily_oriented_minimum_bounding_box
 */
template<typename T>
struct SMinimumOrientedBoundingBox
{
    SMinimumOrientedBoundingBox(std::vector<T> Vertices, double Width, double Length)
        : s_Vertices{Vertices}
        , s_Width{Width}
        , s_Length{Length}
    {}
    std::vector<T> s_Vertices;

    // Note: the width and length of the bounding box are not axis aligned
    // They follow the usual convention of Width <= Length
    double s_Width{};
    double s_Length{};
};

template<typename T>
SMinimumOrientedBoundingBox<T> ComputeMinimumOrientedBoundingBox(const std::vector<T>& Points, bool IsConvex = false)
{
    // Aliases
    namespace bg = boost::geometry;
    using PointType = bg::model::point<double, 2, bg::cs::cartesian>;
    using PolygonType = bg::model::polygon<PointType>;
    using BoxType = bg::model::box<PointType>;

    PolygonType InitialPolygon, ConvexHull, MinimumOrientedBoundingBox;

    // Compute initial polygon
    for(const T& Point : Points)
    {
        // Note: int32 to double conversion when using CPoint
        InitialPolygon.outer().emplace_back(Point.GetX(), Point.GetY());
    }

    if(IsConvex)
    {
        ConvexHull = InitialPolygon;
        bg::correct(ConvexHull);
    }
    else
    {
        // Compute convex hull of the initial point cloud
        bg::convex_hull(InitialPolygon, ConvexHull);
    }

    // Compute minimum bounding rectangle of the convex hull to set the maximum area
    BoxType MBRConvexHull;
    bg::envelope(ConvexHull, MBRConvexHull);

    // Calculate area
    double OptimumArea = bg::area(MBRConvexHull);
    double OptimumAngle{0.0};
    BoxType OptimumMBR;

    // Loop over all the vertices of the convex hull
    for(auto it = boost::begin(bg::exterior_ring(ConvexHull)); it != boost::end(bg::exterior_ring(ConvexHull))-1; ++it)
    {
        // Compute orientation of edge
        double x1 = bg::get<0>(*it);
        double y1 = bg::get<1>(*it);
        double x2 = bg::get<0>(*(it+1));
        double y2 = bg::get<1>(*(it+1));
        double Angle = std::atan2(y2-y1, x2-x1);

        // Rotate the convex hull
        bg::strategy::transform::rotate_transformer<bg::radian, double, 2, 2> RotateCounterClockwise(Angle);
        PolygonType RotatedConvexHull;
        bg::transform(ConvexHull, RotatedConvexHull, RotateCounterClockwise);

        // Compute minimum bounding rectangle of the rotated convex hull
        BoxType MBR;
        bg::envelope(RotatedConvexHull, MBR);

        if(bg::area(MBR)<=OptimumArea)
        {
            OptimumArea = bg::area(MBR);
            OptimumAngle = Angle;
            OptimumMBR = MBR;
        }
    }

    // Compute new polygon from minimum bounding rectangle
    double Min_x = OptimumMBR.min_corner().get<0>();
    double Min_y = OptimumMBR.min_corner().get<1>();
    double Max_x = OptimumMBR.max_corner().get<0>();
    double Max_y = OptimumMBR.max_corner().get<1>();

    PolygonType NewPolygon;
    NewPolygon.outer().emplace_back(Min_x, Min_y);
    NewPolygon.outer().emplace_back(Min_x, Max_y);
    NewPolygon.outer().emplace_back(Max_x, Max_y);
    NewPolygon.outer().emplace_back(Max_x, Min_y);
    bg::correct(NewPolygon);

    // Restore the initial orientation
    bg::strategy::transform::rotate_transformer<bg::radian, double, 2, 2> RotateClockwise(-OptimumAngle);
    bg::transform(NewPolygon, MinimumOrientedBoundingBox, RotateClockwise);

    std::vector<T> Result;
    for(auto it = boost::begin(bg::exterior_ring(MinimumOrientedBoundingBox)); it != boost::end(bg::exterior_ring(MinimumOrientedBoundingBox)); ++it)
    {
        Result.emplace_back(ConvertToBestApproximation<T>(bg::get<0>(*it), bg::get<1>(*it)));
    }

    double Width = bg::distance(MinimumOrientedBoundingBox.outer()[0], MinimumOrientedBoundingBox.outer()[1]);
    double Length = bg::distance(MinimumOrientedBoundingBox.outer()[1], MinimumOrientedBoundingBox.outer()[2]);

    // Set usual convention Width <= Length
    if(Width > Length)
    {
        std::swap(Width, Length);
    }

    return SMinimumOrientedBoundingBox<T>{Result, Width, Length};
}

int MOBR()
{
    std::vector<C2DPoint> Triangle{C2DPoint(-1.0, 1.0), C2DPoint(1.0, -1.0), C2DPoint(1.0, 1.0)};
    auto MOBR = ComputeMinimumOrientedBoundingBox<C2DPoint>(Triangle, false);

    std::cout << "MOBR vertices (closed rectangle) " << std::endl;
    for(const auto& Point : MOBR.s_Vertices)
    {
        std::cout << Point.GetX() << " " << Point.GetY() << std::endl;
    }

    std::cout << "Width " << MOBR.s_Width << std::endl;
    std::cout << "Length " << MOBR.s_Length << std::endl;
    return 0;
}
