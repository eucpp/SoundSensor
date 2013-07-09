#include "alglibCorrelator.h"

alglib::real_1d_array AlglibCorrelator::correlation(Signal signal, Signal pattern) const
{
    if (pattern.size() > signal.size())
        throw SignalsSizeExc();

    time_t time1 = time(NULL);
    alglib::real_1d_array signalArray;
    signalArray.setcontent(signal.size(), signal.toDoubleArray());
    time_t time2 = time(NULL);
    alglib::real_1d_array patternArray;
    patternArray.setcontent(pattern.size(), pattern.toDoubleArray());
    alglib::real_1d_array corrArray;
    time_t time3 = time(NULL);
    alglib::corrr1d(signalArray, signal.size(), patternArray, pattern.size(), corrArray);
    time_t time4 = time(NULL);

    std::cout << "Init signal time: " << difftime(time2, time1) << std::endl;
    std::cout << "Init pattern time: " << difftime(time3, time2) << std::endl;
    std::cout << "Algorhytm time: " << difftime(time4, time3) << std::endl;

    return corrArray;
}
