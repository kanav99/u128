#include <cstdint>
#include <iostream>
#include <utility>
#include <Eigen/Dense>

struct u128
{
    uint64_t low;
    uint64_t high;

    u128(uint64_t low, uint64_t high) : low(low), high(high) {}
    u128(uint64_t low) : low(low), high(0) {}
    u128(const u128& other) : low(other.low), high(other.high) {}
    u128() : low(0), high(0) {}
    u128(std::pair<uint64_t, uint64_t> p) : low(p.first), high(p.second) {}

    u128 operator+(const u128& other) const
    {
        uint64_t low = this->low + other.low;
        uint64_t high = this->high + other.high + (low >= (-this->low));
        return u128(low, high);
    }

    u128 operator*(const u128& other) const
    {
        uint64_t l1 = this->low;
        uint64_t h1 = this->high;
        uint64_t l2 = other.low;
        uint64_t h2 = other.high;

        __uint128_t ll = l1;
        ll *= l2;

        uint64_t low = (uint64_t )ll;
        uint64_t high = ((uint64_t *)(&ll))[1]; //(uint64_t )(ll >> 64);
        high += l1 * h2 + l2 * h1;
        return u128(low, high);
    }
};

namespace Eigen {
 
template<> struct NumTraits<u128> : GenericNumTraits<u128>
{
  typedef u128 Real;
//   typedef u128 NonInteger;
//   typedef u128 Nested;
 
  enum {
    IsComplex = 0,
    IsInteger = 1,
    IsSigned = 0,
    RequireInitialization = 0,
    ReadCost = 1,
    AddCost = 3,
    MulCost = 3
  };
};
 
}

std::ostream& operator<<(std::ostream& os, const u128& u128)
{
    os << "(" << u128.high << ", " << u128.low << ")";
    return os;
}

int main()
{
    rand();
    u128 a(rand(), rand());
    u128 b(rand(), rand());
    u128 c = a * b;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;

    Eigen::Matrix<u128, 2, 2> m1, m2, m3;
    m1 << a, b, c, a;
    m2 << b, c, a, b;
    m3 = m1 * m2;
    std::cout << m3(0, 0) << std::endl;
    return 0;
}
