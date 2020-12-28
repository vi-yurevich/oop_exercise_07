#ifndef OOP_EXERSICE_7_FIGURE_H
#define OOP_EXERSICE_7_FIGURE_H

#include <iostream>
#include <vector>
#include <string>

struct Pair {
    double x;
    double y;
    Pair();
    Pair(double a, double b);
    friend std::ostream& operator<<(std::ostream& os, const Pair& p);
};

std::ostream& operator<<(std::ostream& os, const Pair& p);
std::ostream& operator<<(std::ostream& os, const std::vector<Pair>& v);

class TFigure {
    protected:
        std::vector<Pair> points;
        Pair center;
    public:
        TFigure();
        TFigure(double x0, double y0);
        virtual std::string Name() = 0;
        virtual double Area() = 0;
        virtual Pair Center() = 0;
        virtual std::vector<Pair> Coordinate() = 0;
        virtual Pair Side() = 0;
};

class TRhombus : public TFigure {
    private:
        double verticalDiag;
        double horisontalDiag;
    public:
        TRhombus();
        TRhombus(double x0, double y0, double v, double h);
        std::string Name() override;
        double Area() override;
        Pair Center () override;
        std::vector<Pair> Coordinate() override;
        virtual Pair Side() override;
};

class TPentagone : public TFigure {
    private:
        double side;
    public:
        TPentagone();
        TPentagone(double x0, double y0, double s);
        std::string Name() override;
        double Area() override;
        Pair Center() override;
        std::vector<Pair> Coordinate() override;
        virtual Pair Side() override;
};

class THexagone : public TFigure {
    private:
        double side;
    public:
        THexagone();
        THexagone(double x0, double y0, double s);
        std::string Name() override;
        double Area() override;
        Pair Center() override;
        std::vector<Pair> Coordinate() override;
        virtual Pair Side() override;

};

#endif //OOP_EXERSICE_7_FIGURE_H