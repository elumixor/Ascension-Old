//
// Created by Vladyslav Yazykov on 17/12/2018.
//

#ifndef ASCENSION_POW_H
#define ASCENSION_POW_H

namespace math {
    template<int power>
    struct TSign {
        enum {
            value = power % 2 == 0 ? 1 : -1
        };
    };

    template<typename T>
    constexpr int sign(T value) {
        return value % 2 == 0 ? 1 : -1;
    }

    template<typename T>
    constexpr T pow(T num, int _pow) {
        return (_pow >= sizeof(int) * 8) ? 0 :
               _pow == 0 ? 1 : num * pow(num, _pow - 1);
    }


    template<int N>
    struct TFactorial {
        enum {
            value = N * TFactorial<N - 1>::value
        };
    };

    template<>
    struct TFactorial<0> {
        enum {
            value = 1
        };
    };

    template<typename T>
    constexpr int factorial(T v) {
        return v <= 0 ? 1 : v * factorial(v - 1);
    }

    template<int N, int K>
    struct TRangeProduct {
        enum {
            value = N * TRangeProduct<N + 1, K>::value
        };
    };

    template<int K>
    struct TRangeProduct<K, K> {
        enum {
            value = K
        };
    };
    template<int K>
    struct TRangeProduct<K + 1, K> {
        enum {
            value = 1
        };
    };

    template<typename T>
    constexpr int range_product(T from, T to) {
        return from > to ? 1 : from == to ? from : from * range_product(from + 1, to);
    }

    template<typename T>
    constexpr T min(T a, T b) {
        return a > b ? b : a;
    }
    template<typename T>
    constexpr T max(T a, T b) {
        return a < b ? b : a;
    }


}

#endif //ASCENSION_POW_H
