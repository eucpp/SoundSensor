#include "alglibCorrelator.h"

alglib::real_1d_array AlglibCorrelator::correlation(Signal signal, Signal pattern) const
{
    //if (pattern.size() > signal.size())
    //    throw SignalsSizeExc();

    clock_t time1 = clock();
    alglib::real_1d_array signalArray;
    signalArray.setcontent(signal.size(), signal.toDoubleArray());
    clock_t time2 = clock();
    alglib::real_1d_array patternArray;
    patternArray.setcontent(pattern.size(), pattern.toDoubleArray());
    alglib::real_1d_array corrArray;
    clock_t time3 = clock();
    alglib::corrr1d(signalArray, signal.size(), patternArray, pattern.size(), corrArray);
    clock_t time4 = clock();

    //std::cout << "Init signal time: " << (time2 - time1) / (CLOCKS_PER_SEC / 1000) << std::endl;
    //std::cout << "Init pattern time: " << (time3 - time2) / (CLOCKS_PER_SEC / 1000) << std::endl;
    //std::cout << "Total init time: " << (time3 - time1) / (CLOCKS_PER_SEC / 1000) << std::endl;
    //std::cout << "Algorhytm time: " << (time4 - time3) / (CLOCKS_PER_SEC / 1000) << std::endl;

    return corrArray;
}
