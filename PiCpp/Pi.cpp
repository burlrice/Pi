#include "Pi.h"

#include <string>
#include <msclr/marshal_cppstd.h>

using namespace Demo;

// https://www.facebook.com/photo/?fbid=2743885709090652&set=gm.4784083801612572

System::String^ Pi::Generate(unsigned int digits)
{
    int a = 10000, b, c = 8400, d, e, f[8401], g;
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

    return msclr::interop::marshal_as<System::String^>("3." + s.substr(0, digits));
}
