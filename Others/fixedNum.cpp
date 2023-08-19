#include <iostream>
using namespace std;

class Fixed
{

    static const int total_bit_cnt = 64;

    static const int f_bit_cnt = 16;

    static const int i_bit_cnt = total_bit_cnt - f_bit_cnt;

    static const long long f_mask = (long long)(LLONG_MAX >> i_bit_cnt);

    static const long long i_mask = (long long)(-1LL & ~f_mask);

    static const long long f_range = f_mask + 1;

public:
    static const long long min_val = LLONG_MIN >> f_bit_cnt;
    static const long long max_val = LLONG_MAX >> f_bit_cnt;

private:
    long long mRaw;

public:
    Fixed(int intVal)
    {
        mRaw = (long long)intVal << f_bit_cnt;
    }

    Fixed(long long raw)
    {
        mRaw = raw;
    }

    long GetRaw()
    {
        return mRaw;
    }

    inline Fixed operator+(const Fixed &b)
    {
        return Fixed(mRaw + b.mRaw);
    }

    inline Fixed operator-(const Fixed &b)
    {
        return Fixed(mRaw - b.mRaw);
    }

    inline Fixed operator*(const Fixed &b)
    {
        return Fixed((mRaw * b.mRaw + (f_range >> 1)) >> f_bit_cnt);
    }

    inline Fixed operator/(const Fixed &b)
    {
        return Fixed((mRaw << f_bit_cnt) / b.mRaw);
    }

    double CastToDouble()
    {
        return (double)(mRaw >> f_bit_cnt) + (mRaw & f_mask) / (double)f_range;
    }
};

int main()
{
    Fixed a(35532);
    Fixed b(5);
    Fixed c = a / b;
    cout << c.GetRaw() << endl;
    cout << c.CastToDouble() << endl;
    cout << 35532.0 / 5 << endl;
}

