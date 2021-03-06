/**
 * Copyright 2014 Andreas Schäfer
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef FLAT_ARRAY_DETAIL_SHORT_VEC_SSE_FLOAT_4_HPP
#define FLAT_ARRAY_DETAIL_SHORT_VEC_SSE_FLOAT_4_HPP

#ifdef __SSE__

#include <emmintrin.h>
#include <libflatarray/detail/sqrt_reference.hpp>

#ifndef __CUDA_ARCH__

namespace LibFlatArray {

template<typename CARGO, int ARITY>
class short_vec;

template<typename CARGO, int ARITY>
class sqrt_reference;

#ifdef __ICC
// disabling this warning as implicit type conversion is exactly our goal here:
#pragma warning push
#pragma warning (disable: 2304)
#endif

template<>
class short_vec<float, 4>
{
public:
    static const int ARITY = 4;

    typedef short_vec_strategy::sse strategy;

    template<typename _CharT, typename _Traits>
    friend std::basic_ostream<_CharT, _Traits>& operator<<(
        std::basic_ostream<_CharT, _Traits>& __os,
        const short_vec<float, 4>& vec);

    inline
    short_vec(const float data = 0) :
        val1(_mm_set1_ps(data))
    {}

    inline
    short_vec(const float *data) :
        val1(_mm_loadu_ps(data +  0))
    {}

    inline
    short_vec(const __m128& val1) :
        val1(val1)
    {}

    inline
    short_vec(const sqrt_reference<float, 4> other);

    inline
    void operator-=(const short_vec<float, 4>& other)
    {
        val1 = _mm_sub_ps(val1, other.val1);
    }

    inline
    short_vec<float, 4> operator-(const short_vec<float, 4>& other) const
    {
        return short_vec<float, 4>(
            _mm_sub_ps(val1, other.val1));
    }

    inline
    void operator+=(const short_vec<float, 4>& other)
    {
        val1 = _mm_add_ps(val1, other.val1);
    }

    inline
    short_vec<float, 4> operator+(const short_vec<float, 4>& other) const
    {
        return short_vec<float, 4>(
            _mm_add_ps(val1, other.val1));
    }

    inline
    void operator*=(const short_vec<float, 4>& other)
    {
        val1 = _mm_mul_ps(val1, other.val1);
    }

    inline
    short_vec<float, 4> operator*(const short_vec<float, 4>& other) const
    {
        return short_vec<float, 4>(
            _mm_mul_ps(val1, other.val1));
    }

    inline
    void operator/=(const short_vec<float, 4>& other)
    {
        val1 = _mm_div_ps(val1, other.val1);
    }

    inline
    void operator/=(const sqrt_reference<float, 4>& other);

    inline
    short_vec<float, 4> operator/(const short_vec<float, 4>& other) const
    {
        return short_vec<float, 4>(
            _mm_div_ps(val1, other.val1));
    }

    inline
    short_vec<float, 4> operator/(const sqrt_reference<float, 4>& other) const;

    inline
    short_vec<float, 4> sqrt() const
    {
        return short_vec<float, 4>(
            _mm_sqrt_ps(val1));
    }

    inline
    void store(float *data) const
    {
        _mm_storeu_ps(data +  0, val1);
    }

private:
    __m128 val1;
};

inline
void operator<<(float *data, const short_vec<float, 4>& vec)
{
    vec.store(data);
}

template<>
class sqrt_reference<float, 4>
{
public:
    template<typename OTHER_CARGO, int OTHER_ARITY>
    friend class short_vec;

    sqrt_reference(const short_vec<float, 4>& vec) :
        vec(vec)
    {}

private:
    short_vec<float, 4> vec;
};

#ifdef __ICC
#pragma warning pop
#endif

inline
short_vec<float, 4>::short_vec(const sqrt_reference<float, 4> other) :
    val1(_mm_sqrt_ps(other.vec.val1))
{}

inline
void short_vec<float, 4>::operator/=(const sqrt_reference<float, 4>& other)
{
    val1 = _mm_mul_ps(val1, _mm_rsqrt_ps(other.vec.val1));
}

inline
short_vec<float, 4> short_vec<float, 4>::operator/(const sqrt_reference<float, 4>& other) const
{
    return short_vec<float, 4>(
        _mm_mul_ps(val1, _mm_rsqrt_ps(other.vec.val1)));
}

inline
sqrt_reference<float, 4> sqrt(const short_vec<float, 4>& vec)
{
    return sqrt_reference<float, 4>(vec);
}

template<typename _CharT, typename _Traits>
std::basic_ostream<_CharT, _Traits>&
operator<<(std::basic_ostream<_CharT, _Traits>& __os,
           const short_vec<float, 4>& vec)
{
    const float *data1 = reinterpret_cast<const float *>(&vec.val1);
    __os << "[" << data1[0] << ", " << data1[1]  << ", " << data1[2]  << ", " << data1[3] << "]";
    return __os;
}

}

#endif
#endif

#endif
