#ifndef FMT_TEST
#define FMT_TEST
#include "fmt/format.h"
#include <fmt/ranges.h>
#include <fmt/chrono.h>
#include <fmt/compile.h>
#include <fmt/ostream.h>
#include <fmt/os.h>


struct point {
    double x, y;
};
template <> struct fmt::formatter<point> {
    // Presentation format: 'f' - fixed, 'e' - exponential.
    char presentation = 'f';
    // Parses format specifications of the form ['f' | 'e'].
    constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
        // [ctx.begin(), ctx.end()) is a character range that contains a part of
        // the format string starting from the format specifications to be parsed,
        // e.g. in
        //
        //   fmt::format("{:f} - point of interest", point{1, 2});
        //
        // the range will contain "f} - point of interest". The formatter should
        // parse specifiers until '}' or the end of the range. In this example
        // the formatter should parse the 'f' specifier and return an iterator
        // pointing to '}'.
        // Please also note that this character range may be empty, in case of
        // the "{}" format string, so therefore you should check ctx.begin()
        // for equality with ctx.end().
        // Parse the presentation format and store it in the formatter:
        auto it = ctx.begin(), end = ctx.end();
        if (it != end && (*it == 'f' || *it == 'e')) presentation = *it++;
        // Check if reached the end of the range:
        if (it != end && *it != '}') throw format_error("invalid format");
        // Return an iterator past the end of the parsed range:
        return it;
    }
    // Formats the point p using the parsed format specification (presentation)
    // stored in this formatter.
    template <typename FormatContext>
    auto format(const point& p, FormatContext& ctx) const -> decltype(ctx.out()) {
        // ctx.out() is an output iterator to write to.
        return presentation == 'f'
                ? fmt::format_to(ctx.out(), "({:.1f}, {:.1f})", p.x, p.y)
                : fmt::format_to(ctx.out(), "({:.1e}, {:.1e})", p.x, p.y);
    }
};



struct date {
  int year, month, day;
  friend std::ostream& operator<<(std::ostream& os, const date& d) {
    return os << d.year << '-' << d.month << '-' << d.day;
  }
};
template <> struct fmt::formatter<date> : ostream_formatter {};


class CFmtTest{
public:
    CFmtTest();
    ~CFmtTest();
public:
    static int test();
private:
};

#endif