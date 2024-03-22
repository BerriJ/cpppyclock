#ifndef cppytimer
#define cppytimer

#ifdef _OPENMP
#include <omp.h>
#endif

#include <pybind11/pybind11.h>
#include <cpptimer.h>
#include <string>
#include <vector>

// This class inherits its main functionality from CppClock
// It justs extends it with a get_times() method to returning the results as
// a convenient table.
class Timer : public CppTimer
{

public:
    bool autoreturn = true;

    // This ensures that there are no implicit conversions in the constructors
    // That means, the types must exactly match the constructor signature
    // template <typename T>
    // Timer(T &&) = delete;

    Timer() : CppTimer() {} // Will use "times", true
    Timer(const char *name) : CppTimer(name) {}
    Timer(bool verbose) : CppTimer(verbose) {}
    Timer(std::string name, bool verbose) : CppTimer(name, verbose) {}

    // Pass data to R / Python
    std::vector<std::tuple<std::string,
                           double,
                           double,
                           unsigned long int>>
    stop()
    {

        aggregate();

        std::vector<std::tuple<std::string,
                               double,
                               double,
                               unsigned long int>>
            table;

        for (auto const &ent1 : data)
        {

            unsigned long int count = std::get<2>(ent1.second);
            double mean = std::get<0>(ent1.second);
            double variance = std::get<1>(ent1.second) / count;

            table.push_back(std::make_tuple(ent1.first,
                                            std::round(mean) * 1e-3,
                                            std::round(
                                                std::sqrt(
                                                    variance * 1e-6) *
                                                1e+3) *
                                                1e-3,
                                            count));
        }

        return table;
    }
};

#endif