How to use Boost? Is Boost a header-only library or it needs to be build.

Reference https://www.boost.org/doc/libs/1_74_0/more/getting_started/windows.html#header-only-libraries
Most Boost libraries are header-only: they consist entirely of header files containing templates and inline functions, and require no separately-compiled library binaries or special treatment when linking.

However, some Boost libraries must be built (example Boost.Filesystem, Boost.Chrono etc). When using such libraries, the executable also needs to be linked with the library (example when using Boost.Filesystem application needs to be linked with libboost_filesystem).
