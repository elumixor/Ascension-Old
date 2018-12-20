//
// Created by Vladyslav Yazykov on 17/12/2018.
//

#ifndef ASCENSION_BEZIER_H
#define ASCENSION_BEZIER_H

#include "util/math.h"
#include "initializer_list"
#include "utility"

template<typename Point>
class Bezier final {
public:
    Point *C;
    size_t n;
    Point integrated{};

    Bezier(std::initializer_list<Point> points) noexcept : C{new Point[points.size()]}, n{points.size() - 1} {
        for (size_t j{0}; j <= n; j++) {
            auto f = math::range_product(n - j + 1, n);

            Point sum{};
            for (size_t i{0}; i <= j; i++)
                sum += (float) math::sign(i + j) * *(points.begin() + i) /
                       (float) (math::factorial(i) * math::factorial(j - i));

            C[j] = (float) f * sum;

            integrated += C[j] / (float) (j + 1);
        }
    }

    ~Bezier() { delete[] C; }

    inline const Point &operator[](size_t i) const { return C[i]; }
    Point &&operator()(float t) const {
        Point r{};
        for (size_t j{0}; j <= n; j++)
            r += math::pow(t, (int) j) * C[j];

        return std::move(r);
    }

    Bezier(const Bezier &) = delete;
    Bezier(Bezier &&) = delete;
    Bezier &operator=(const Bezier &) = delete;
    Bezier &operator=(Bezier &&) = delete;
};

#endif //ASCENSION_BEZIER_H
