#ifndef DCGP_GYM_H
#define DCGP_GYM_H

#include <boost/math/constants/constants.hpp>
#include <cmath>
#include <random>
#include <vector>

#include <dcgp/nist_data.hpp>

namespace dcgp
{
namespace gym
{
namespace detail
{
inline constexpr auto pi = boost::math::constants::pi<double>();
inline constexpr auto e = boost::math::constants::e<double>();

typedef std::function<double(const std::vector<double> &x)> multivar_func;

// Standard Problems
inline const multivar_func koza_quintic
    = [](const std::vector<double> &x) { return std::pow(x[0], 5) - 2 * std::pow(x[0], 3) + x[0]; };

// From:
// Izzo, D., Biscani, F., & Mereta, A. (2017, April).
// Differentiable genetic programming.
// In European Conference on Genetic Programming (pp. 35-51). Springer.
inline const multivar_func P1
    = [](const std::vector<double> &x) { return std::pow(x[0], 5) - pi * std::pow(x[0], 3) + x[0]; };
inline const multivar_func P2
    = [](const std::vector<double> &x) { return std::pow(x[0], 5) - pi * std::pow(x[0], 3) + 2. * pi / x[0]; };
inline const multivar_func P3
    = [](const std::vector<double> &x) { return (e * std::pow(x[0], 5) + std::pow(x[0], 3)) / (x[0] + 1.); };
inline const multivar_func P4 = [](const std::vector<double> &x) { return sin(pi * x[0]) + 1. / x[0]; };
inline const multivar_func P5
    = [](const std::vector<double> &x) { return e * std::pow(x[0], 5) - pi * std::pow(x[0], 3) + x[0]; };
inline const multivar_func P6 = [](const std::vector<double> &x) { return (e * x[0] * x[0] - 1) / (pi * (x[0] + 2)); };
inline const multivar_func P7 = [](const std::vector<double> &x) { return std::cos(pi * x[0]) + std::sin(e * x[0]); };

// From:
// Vladislavleva, Ekaterina J., Guido F. Smits, and Dick Den Hertog.
// "Order of nonlinearity as a complexity measure for models generated by symbolic regression via pareto genetic
// programming." IEEE Transactions on Evolutionary Computation 13.2 (2008): 333-349.
inline const multivar_func kotanchek = [](const std::vector<double> &x) {
    return std::exp(-(x[0] - 1.) * (x[0] - 1.)) / (1.2 + (x[1] - 2.5) * (x[1] - 2.5));
};
inline const multivar_func salutowicz = [](const std::vector<double> &x) {
    return std::exp(-x[0]) * x[0] * x[0] * x[0] * std::cos(x[0]) * std::sin(x[0])
           * (std::cos(x[0]) * std::sin(x[0]) * std::sin(x[0]) - 1.);
};
inline const multivar_func salutowicz2d = [](const std::vector<double> &x) { return salutowicz(x) * (x[1] - 5.); };
inline const multivar_func uball5d = [](const std::vector<double> &x) {
    return 10.
           / (5.
              + std::pow((x[0] - 3.), 2) * std::pow((x[1] - 3.), 2) * std::pow((x[2] - 3.), 2)
                    * std::pow((x[3] - 3.), 2) * std::pow((x[4] - 3.), 2));
};
inline const multivar_func ratpol3d
    = [](const std::vector<double> &x) { return 30. * (x[0] - 1.) * (x[2] - 1.) / (x[1] * x[1] * (x[0] - 10.)); };
inline const multivar_func sinecosine
    = [](const std::vector<double> &x) { return 6. * std::cos(x[0] * std::sin(x[1])); };
inline const multivar_func ripple
    = [](const std::vector<double> &x) { return (x[0] - 3.) * (x[1] - 3.) + 2 * std::sin((x[0] - 4.) * (x[1] - 4.)); };
inline const multivar_func ratpol2d = [](const std::vector<double> &x) {
    return (std::pow(x[0] - 3., 4) + std::pow(x[1] - 3., 3) - (x[1] - 3.)) / (std::pow(x[1] - 2, 4.) + 10.);
};

// Generates data to test symbolic regression on 1D input-output cases.
inline void generate_1Ddata(std::vector<std::vector<double>> &points, std::vector<std::vector<double>> &labels,
                            multivar_func f, double lb = -1, double ub = 1, unsigned N = 10)
{
    points.clear();
    labels.clear();
    for (unsigned i = 0u; i < N; ++i) {
        double x = lb + (i * (ub - lb)) / (N - 1);
        points.push_back({x});
        labels.push_back({f({x})});
    }
}
} // namespace detail
inline void generate_koza_quintic(std::vector<std::vector<double>> &points, std::vector<std::vector<double>> &labels)
{
    gym::detail::generate_1Ddata(points, labels, detail::koza_quintic, -3., 3., 10);
}
inline void generate_P1(std::vector<std::vector<double>> &points, std::vector<std::vector<double>> &labels)
{
    gym::detail::generate_1Ddata(points, labels, detail::P1, 1., 3., 10);
}
inline void generate_P2(std::vector<std::vector<double>> &points, std::vector<std::vector<double>> &labels)
{
    gym::detail::generate_1Ddata(points, labels, detail::P2, 0.1, 5., 10);
}
inline void generate_P3(std::vector<std::vector<double>> &points, std::vector<std::vector<double>> &labels)
{
    gym::detail::generate_1Ddata(points, labels, detail::P3, -0.9, 1, 10);
}
inline void generate_P4(std::vector<std::vector<double>> &points, std::vector<std::vector<double>> &labels)
{
    gym::detail::generate_1Ddata(points, labels, detail::P4, -1, 1, 10);
}
inline void generate_P5(std::vector<std::vector<double>> &points, std::vector<std::vector<double>> &labels)
{
    gym::detail::generate_1Ddata(points, labels, detail::P5, 1., 3., 10);
}
inline void generate_P6(std::vector<std::vector<double>> &points, std::vector<std::vector<double>> &labels)
{
    gym::detail::generate_1Ddata(points, labels, detail::P6, -2.1, 1., 10);
}
inline void generate_P7(std::vector<std::vector<double>> &points, std::vector<std::vector<double>> &labels)
{
    gym::detail::generate_1Ddata(points, labels, detail::P7, -1, 1, 10);
}
inline void generate_kotanchek(std::vector<std::vector<double>> &points, std::vector<std::vector<double>> &labels)
{
    points.clear();
    labels.clear();
    std::mt19937 mt(32);
    std::uniform_real_distribution<double> dist(0.3, 4);
    for (unsigned i = 0; i < 100u; ++i) {
        std::vector<double> point = {dist(mt), dist(mt)};
        points.push_back(point);
        labels.push_back({detail::kotanchek(point)});
    }
}
inline void generate_salutowicz(std::vector<std::vector<double>> &points, std::vector<std::vector<double>> &labels)
{
    gym::detail::generate_1Ddata(points, labels, detail::salutowicz, 0.05, 10., 100);
}
inline void generate_salutowicz2d(std::vector<std::vector<double>> &points, std::vector<std::vector<double>> &labels)
{
    points.clear();
    labels.clear();
    std::mt19937 mt(32);
    std::uniform_real_distribution<double> dist(0.05, 10);
    for (unsigned i = 0; i < 601u; ++i) {
        std::vector<double> point = {dist(mt), dist(mt)};
        points.push_back(point);
        labels.push_back({detail::salutowicz2d(point)});
    }
}
inline void generate_uball5d(std::vector<std::vector<double>> &points, std::vector<std::vector<double>> &labels)
{
    points.clear();
    labels.clear();
    std::mt19937 mt(32);
    std::uniform_real_distribution<double> dist(0.05, 6.05);
    for (unsigned i = 0; i < 1024u; ++i) {
        std::vector<double> point = {dist(mt), dist(mt), dist(mt), dist(mt), dist(mt)};
        points.push_back(point);
        labels.push_back({detail::uball5d(point)});
    }
}
inline void generate_ratpol3d(std::vector<std::vector<double>> &points, std::vector<std::vector<double>> &labels)
{
    points.clear();
    labels.clear();
    std::mt19937 mt(32);
    std::uniform_real_distribution<double> dist(0.05, 2);
    std::uniform_real_distribution<double> dist1(1, 2);
    for (unsigned i = 0; i < 300u; ++i) {
        std::vector<double> point = {dist(mt), dist1(mt), dist(mt)};
        points.push_back(point);
        labels.push_back({detail::ratpol3d(point)});
    }
}
inline void generate_sinecosine(std::vector<std::vector<double>> &points, std::vector<std::vector<double>> &labels)
{
    points.clear();
    labels.clear();
    std::mt19937 mt(32);
    std::uniform_real_distribution<double> dist(0.1, 5.9);
    for (unsigned i = 0; i < 30u; ++i) {
        std::vector<double> point = {dist(mt), dist(mt)};
        points.push_back(point);
        labels.push_back({detail::sinecosine(point)});
    }
}
inline void generate_ripple(std::vector<std::vector<double>> &points, std::vector<std::vector<double>> &labels)
{
    points.clear();
    labels.clear();
    std::mt19937 mt(32);
    std::uniform_real_distribution<double> dist(0.05, 6.05);
    for (unsigned i = 0; i < 300u; ++i) {
        std::vector<double> point = {dist(mt), dist(mt)};
        points.push_back(point);
        labels.push_back({detail::ripple(point)});
    }
}
inline void generate_ratpol2d(std::vector<std::vector<double>> &points, std::vector<std::vector<double>> &labels)
{
    points.clear();
    labels.clear();
    std::mt19937 mt(32);
    std::uniform_real_distribution<double> dist(0.05, 6.05);
    for (unsigned i = 0; i < 50u; ++i) {
        std::vector<double> point = {dist(mt), dist(mt)};
        points.push_back(point);
        labels.push_back({detail::ratpol2d(point)});
    }
}

inline void generate_chwirut1(std::vector<std::vector<double>> &points, std::vector<std::vector<double>> &labels)
{
    points.clear();
    labels.clear();
    points = chwirut1_points;
    labels = chwirut1_labels;
}

inline void generate_chwirut2(std::vector<std::vector<double>> &points, std::vector<std::vector<double>> &labels)
{
    points.clear();
    labels.clear();
    points = chwirut2_points;
    labels = chwirut2_labels;
}

inline void generate_daniel_wood(std::vector<std::vector<double>> &points, std::vector<std::vector<double>> &labels)
{
    points.clear();
    labels.clear();
    points = daniel_wood_points;
    labels = daniel_wood_labels;
}

inline void generate_gauss1(std::vector<std::vector<double>> &points, std::vector<std::vector<double>> &labels)
{
    points.clear();
    labels.clear();
    points = gauss1_points;
    labels = gauss1_labels;
}

inline void generate_kirby2(std::vector<std::vector<double>> &points, std::vector<std::vector<double>> &labels)
{
    points.clear();
    labels.clear();
    points = kirby2_points;
    labels = kirby2_labels;
}

inline void generate_lanczos2(std::vector<std::vector<double>> &points, std::vector<std::vector<double>> &labels)
{
    points.clear();
    labels.clear();
    points = lanczos2_points;
    labels = lanczos2_labels;
}

inline void generate_misra1b(std::vector<std::vector<double>> &points, std::vector<std::vector<double>> &labels)
{
    points.clear();
    labels.clear();
    points = misra1b_points;
    labels = misra1b_labels;
}
} // namespace gym
} // namespace dcgp

#endif
