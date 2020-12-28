#include "Figure.h"
#include <cmath>
#include <vector>
#include <memory>

Pair::Pair() : x(0.0), y(0.0) {}

Pair::Pair(double a, double b) : x(a), y(b) {}

std::ostream& operator<<(std::ostream& os, const Pair& p){
    os << "(" << p.x << " ; " << p.y << ")";
    return(os);
}

std::ostream& operator<<(std::ostream& os, const std::vector<Pair>& v) {
    for(int i = 0; i < v.size(); ++i) {
        os << v[i] << " "; 
    }
    return(os);
}

TFigure::TFigure(double x0, double y0) {
    center.x = x0;
    center.y = y0;
}

TFigure::TFigure() : TFigure (0.0, 0.0) {}

TRhombus::TRhombus(double x0, double y0, double v, double h) {
    center.x = x0;
    center.y = y0;
    verticalDiag = v;
    horisontalDiag = h;
    points.push_back(Pair(x0, y0 + v/2.0));
    points.push_back(Pair(x0 + h/2.0, y0));
    points.push_back(Pair(x0, y0 - v/2.0));
    points.push_back(Pair(x0 - h/2.0, y0));
}

TRhombus::TRhombus() : TFigure() {
    verticalDiag = 0.0;
    horisontalDiag = 0.0;
}

std::string TRhombus::Name() {
    return("Ромб");
}

double TRhombus::Area() {
    return (verticalDiag * horisontalDiag / 2.0);
}

Pair TRhombus::Center() {
    return(center);
}

std::vector<Pair> TRhombus::Coordinate() {
    return(points);
}

Pair TRhombus::Side() {
    return(Pair{verticalDiag, horisontalDiag});
}

TPentagone::TPentagone(double x0, double y0, double s) {
    center.x = x0;
    center.y = y0;
    side = s;
    double r = s * sqrt(2.0) / sqrt(5.0 - sqrt(5.0));
    points.push_back(Pair(x0, y0 + r));
    points.push_back(Pair(x0 + r, y0));
    points.push_back(Pair(x0 + s / 2.0, y0 - r));
    points.push_back(Pair(x0 - s / 2.0, y0 - r));
    points.push_back(Pair(x0 - r, y0));
}

TPentagone::TPentagone() : TFigure() {
    side = 0.0;
}

std::string TPentagone::Name() {
    return("Пятиугольник");
}

double TPentagone::Area() {
    double a = pow(side, 2.0) * sqrt(5.0) * sqrt(5.0 + 2.0 * sqrt(5.0)) / 4.0;
    return(a);
}

Pair TPentagone::Center() {
    return(center);
}

std::vector<Pair> TPentagone::Coordinate() {
    return(points);
}

Pair TPentagone::Side() {
    return(Pair{side, 0.0});
}

THexagone::THexagone(double x0, double y0, double s) {
    center.x = x0;
    center.y = y0;
    side = s;
    points.push_back(Pair(x0 - s / 2.0, y0 + sqrt(3.0) * s / 2.0));
    points.push_back(Pair(x0 + s / 2.0, y0 + sqrt(3.0) * s / 2.0));
    points.push_back(Pair(x0 + s, y0));
    points.push_back(Pair(x0 + s / 2.0, y0 - sqrt(3.0) * s / 2.0));
    points.push_back(Pair(x0 - s / 2.0, y0 - sqrt(3.0) * s / 2.0));
    points.push_back(Pair(x0 - s, y0));

}

THexagone::THexagone() : TFigure() {
    side = 0.0;
}

std::string THexagone::Name() {
    return("Шестиугольник");
}

double THexagone::Area() {
    double a = 3.0 * sqrt(3.0) * pow(side, 2.0) / 2.0;
    return(a);
}

Pair THexagone::Center() {
    return(center);
}

std::vector<Pair> THexagone::Coordinate() {
    return(points);
}

Pair THexagone::Side() {
    return(Pair{side, 0.0});
}