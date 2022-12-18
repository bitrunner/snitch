#if defined(SNATCH_TEST_WITH_SNATCH)
// The library being tested is also the library used for testing...
#    if defined(SNATCH_TEST_HEADER_ONLY)
#        include "snatch/snatch_all.hpp"
#    else
#        include "snatch/snatch.hpp"
#    endif

#else

// The library being tested.
#    if defined(SNATCH_TEST_HEADER_ONLY)
#        include "snatch/snatch_all.hpp"
#    else
#        include "snatch/snatch.hpp"
#    endif
// The library used for testing.
#    include "doctest/doctest.h"
// Adjust doctest macros to match the snatch API
#    define SECTION(name) DOCTEST_SUBCASE(name)
#    undef TEST_CASE
#    define TEST_CASE(name, ...) DOCTEST_TEST_CASE(name " " __VA_ARGS__)
#    define TEMPLATE_TEST_CASE(name, tags, ...)                                                    \
        DOCTEST_TEST_CASE_TEMPLATE(tags " " name, TestType, __VA_ARGS__)
#    define SKIP(message) return

#    include <ostream>

namespace doctest::detail {
template<typename T>
concept function = std::is_function_v<T>;

template<function T>
struct filldata<T*> {
    static void fill(std::ostream* stream, T* in) {
        filldata<const void*>::fill(stream, in != nullptr ? "funcptr" : "nullptr");
    }
};
} // namespace doctest::detail
#endif

#if defined(__clang__)
#    define SNATCH_WARNING_DISABLE_UNREACHABLE
#    define SNATCH_WARNING_DISABLE_INT_BOOLEAN
#elif defined(__GNUC__)
#    define SNATCH_WARNING_DISABLE_UNREACHABLE
#    define SNATCH_WARNING_DISABLE_INT_BOOLEAN                                                     \
        _Pragma("GCC diagnostic ignored \"-Wint-in-bool-context\"")
#elif defined(_MSC_VER)
#    define SNATCH_WARNING_DISABLE_UNREACHABLE _Pragma("warning(disable: 4702)")
#    define SNATCH_WARNING_DISABLE_INT_BOOLEAN
#else
#    define SNATCH_WARNING_DISABLE_UNREACHABLE
#    define SNATCH_WARNING_DISABLE_INT_BOOLEAN
#endif
