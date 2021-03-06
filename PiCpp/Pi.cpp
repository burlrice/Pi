#include "Pi.h"

#include <string>
#include <msclr/marshal_cppstd.h>

using namespace Demo;
using namespace msclr::interop;
using namespace System;

String^ Pi::Generate(unsigned int digits)
{
    int a = 10000, b = 0, c = 8400, d = 0, e = 0, f[8401], g;
    std::string s;

    for (; b - c && b < std::size(f); )
    {
        f[b++] = a / 5;
    }

    for (; d = 0, (g = c * 2); c -= 14, s += std::to_string(e + d / a), e = d % a)
    {
        if (s.length() >= digits)
        {
            break;
        }

        for (b = c; d += f[b] * a, f[b] = d % --g, d /= g--, --b; d *= b)
        {
        }
    }

    return marshal_as<String^>("3." + s.substr(0, digits));
}
