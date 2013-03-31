#include "correlator.h"

Correlator::Correlator()
{}

void Correlator::calcCorrelation(QByteArray signalBytes, QByteArray patternBytes)
{
    int signalSize = signalBytes.size();
    int patternSize = patternBytes.size();
    alglib::real_1d_array signal;
    signal.setcontent(signalSize, byteArrayToDouble(signalBytes));
    alglib::real_1d_array pattern;
    pattern.setcontent(patternSize, byteArrayToDouble(patternBytes));
    alglib::real_1d_array corrArray;
    alglib::corrr1d(signal, signalSize, pattern, patternSize, corrArray);
    emit correlationCalculated(corrArray.getcontent(), signalSize);
}
