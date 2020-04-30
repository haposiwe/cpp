#include <algorithm>
#include <exception>
#include <iostream>

namespace haposik {

////////////////////////////////////////////////////////////////////////////////

template <size_t N>
struct vector {
  constexpr int32_t& operator[](size_t idx);
  constexpr const int32_t& operator[](size_t idx) const;

  constexpr int32_t& at(size_t idx);
  constexpr const int32_t& at(size_t idx) const;

  int32_t _data[N];
};

////////////////////////////////////////////////////////////////////////////////

template <size_t N>
constexpr bool operator==(const vector<N>& lhs, const vector<N>& rhs) {
    for (size_t i = 0; i < N; i++) {
        if (lhs[i] != rhs[i]) {
            return false;
        }
    }
    return true;
}

template <size_t N>
constexpr bool operator!=(const vector<N>& lhs, const vector<N>& rhs) {
    return !(lhs == rhs);
}

template <size_t N>
constexpr vector<N> operator+(const vector<N>& lhs, const vector<N>& rhs) {
    vector<N> result{};
    for (size_t i = 0; i < N; i++) {
        result[i] = lhs[i] + rhs[i];
    }
    return result;
}

template <size_t N>
constexpr vector<N> operator-(const vector<N>& lhs, const vector<N>& rhs) {
    vector<N> result{};
    for (size_t i = 0; i < N; i++) {
        result[i] = lhs[i] - rhs[i];
    }
    return result;
}

template <size_t N>
constexpr vector<N> operator^(const vector<N>& lhs, const vector<N>& rhs) {
    vector<N> result{};
    for (size_t i = 0; i < N; i++) {
        result[i] = lhs[i] * rhs[i];
    }
    return result;
}

template<size_t N>
constexpr int32_t& vector<N>::operator[](size_t idx) {
    return _data[idx];
}

template<size_t N>
constexpr const int32_t& vector<N>::operator[](size_t idx) const {
    return _data[idx];
}

template<size_t N>
constexpr int32_t& vector<N>::at(size_t idx) {
    if (idx >= N) {
        throw std::out_of_range("vector::at(): idx >= N");
    }
    return _data[idx];
}

template<size_t N>
constexpr const int32_t &vector<N>::at(size_t idx) const {
    if (idx >= N) {
        throw std::out_of_range("vector::at(): idx >= N");
    }
    return _data[idx];
}

////////////////////////////////////////////////////////////////////////////////

void test_vector_addition() {
    constexpr const vector<3> a = {1, 2, 3};
    constexpr const vector<3> b = {4, 5, 6};

    constexpr const vector<3> actual = a + b;
    constexpr const vector<3> expected = {5, 7, 9};

    static_assert(actual == expected, "actual sum != expected");
}

void test_vector_substitution() {
    constexpr const vector<3> a = {4, 5, 6};
    constexpr const vector<3> b = {1, 1, 4};

    constexpr const vector<3> actual = a - b;
    constexpr const vector<3> expected = {3, 4, 2};

    static_assert(actual == expected, "actual sub != expected");
}

void test_vector_scalar_multiplication() {
    constexpr const vector<3> a = {4, 5, 6};
    constexpr const vector<3> b = {2, -3, 1};

    constexpr const vector<3> actual = a ^ b;
    constexpr const vector<3> expected = {8, -15, 6};

    static_assert(actual == expected, "actual mul != expected");
}

}   // namespace haposik

////////////////////////////////////////////////////////////////////////////////

int main() {
    using namespace haposik;

    test_vector_addition();
    test_vector_substitution();
    test_vector_scalar_multiplication();
}
