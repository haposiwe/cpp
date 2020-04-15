#include <cstdlib>
#include <iostream>
#include <stdexcept>

namespace haposik {

////////////////////////////////////////////////////////////////////////////////

struct complex {
  double re;
  double im;

  explicit complex(double re) : re(re), im(0) {}
  complex(double re, double im) : re(re), im(im) {}

  friend bool operator==(const complex& lhs, const complex& rhs);
  friend bool operator!=(const complex& lhs, const complex& rhs);

  friend complex operator+(const complex& lhs, const complex& rhs);
  friend complex operator-(const complex& lhs, const complex& rhs);
  friend complex operator*(const complex& lhs, const complex& rhs);
  friend complex operator/(const complex& lhs, const complex& rhs);
};

////////////////////////////////////////////////////////////////////////////////

bool operator==(const complex &lhs, const complex& rhs) {
    return lhs.re == rhs.re && lhs.im == rhs.im;
}

bool operator!=(const complex &lhs, const complex &rhs) {
    return !(lhs == rhs);
}

complex operator+(const complex &lhs, const complex &rhs) {
    return {lhs.re + rhs.re, lhs.im + rhs.im};
}

complex operator-(const complex &lhs, const complex &rhs) {
    return {lhs.re - rhs.re, lhs.im - rhs.im};
}

complex operator*(const complex &lhs, const complex &rhs) {
    return {
        lhs.re * rhs.re - lhs.im * rhs.im,
        lhs.re * rhs.im + lhs.im * rhs.re
    };
}

complex operator/(const complex &lhs, const complex &rhs) {
    if (rhs.re == 0 && rhs.im == 0) {
        throw std::runtime_error("Division by zero");
    }

    const double denominator = rhs.re  * rhs.re + rhs.im * rhs.im;

    return {
        (lhs.re * rhs.re + lhs.im * rhs.im) / denominator,
        (lhs.im * rhs.re - lhs.re * rhs.im) / denominator
    };
}

////////////////////////////////////////////////////////////////////////////////

#define assert(x) if (!(x)) {                                                  \
    fprintf(stderr, "Assertion failed: %s, function %s, file %s, line %d.\n",  \
        #x, __PRETTY_FUNCTION__, __FILE__, __LINE__                            \
    );                                                                         \
    abort();                                                                   \
}

////////////////////////////////////////////////////////////////////////////////

void test_complex_addition() {
    complex a{1.2, 3.4};
    complex b{4.5, 6.7};

    complex actual = a + b;
    complex expected = {5.7, 10.1};

    assert(actual == expected);
};

void test_complex_substitution() {
    complex a{1.2, 3.4};
    complex b{4.5, -6.7};

    complex actual = a - b;
    complex expected = {-3.3, 10.1};

    assert(actual == expected);
};

void test_complex_multiplication() {
    complex a{2, 3};
    complex b{4, 7};

    complex actual = a * b;
    complex expected = {-13, 26};

    assert(actual == expected);
};

void test_complex_multiplication_by_double() {
    complex a{2, 3};

    complex actual = a * complex{4};
    complex expected = {8, 12};

    assert(actual == expected);
};

void test_complex_division() {
    complex a{-13, 26};
    complex b{4, 7};

    complex actual = a / b;
    complex expected = {2, 3};

    assert(actual == expected);
};

void test_complex_division_by_zero() {
    complex a{1, 2};
    complex b{0, 0};

    try {
        a / b;
    } catch (const std::runtime_error& e) {
        return;  // Fine
    } catch (...) {
        // pass
    }

    // Expected to throw runtime error
    assert(false);
};

void run_all_tests() {
    test_complex_addition();
    test_complex_substitution();
    test_complex_multiplication();
    test_complex_multiplication_by_double();
    test_complex_division();
    test_complex_division_by_zero();
}

}   // namespace haposik

////////////////////////////////////////////////////////////////////////////////

int main() {
    using namespace haposik;

    try {
        run_all_tests();
    } catch (...) {
        std::cerr << "Tests failed!" << std::endl;
        return 1;
    }

    std::cerr << "Tests passed!" << std::endl;
    return 0;
}
