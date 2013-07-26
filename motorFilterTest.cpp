#include "motorFilterTest.h"
#include "signal/fourierTransform/hannWindow.h"

using namespace std;

void motorFilterTest()
{
    const int frameSize = 1024;

    WavFile noiseFile("../motor_noise.wav");
    noiseFile.open(WavFile::ReadOnly);

    if (noiseFile.size() < frameSize)
    {
        cout << "Too small file!" << endl;
        return;
    }

    Signal noise = noiseFile.read(frameSize);
    FFTRealWrap fft(frameSize);
    QScopedPointer<WindowFunction> hannWin(new HannWindow(noise.size()));
    Spectrum noiseSpectr = fft.fourierTransform(noise, hannWin.data());


    /*
    ofstream out("motor_noise_spectrum_hann_window.txt");

    out << "frequency, amplitude, phase \n";
    for (int i = 0; i < spectrum.size(); i++)
    {
        out << round(spectrum[i].getFrequency()) << ", " << round(100 * spectrum[i].amplitude())
            << ", " << round(spectrum[i].phase()) << " \n";
        std::cout << fixed << spectrum[i].amplitude() << endl;
    }
    */

    WavFile signalFile("../motor_noise_2.wav");
    signalFile.open(WavFile::ReadOnly);

    Signal signal = signalFile.readAll();
    int samples = signal.size();
    int pos = 0;
    const double K = 0.9;
    while (samples > frameSize)
    {
        Signal frame = signal.subSignal(pos, frameSize);
        Spectrum frameSpectr = fft.fourierTransform(frame, hannWin.data());

        for (int i = 0; i < frameSpectr.size(); i++)
        {
            frameSpectr[i].setRe(qMax((frameSpectr[i].getRe() - K * noiseSpectr[i].getRe()), (double)0));
            frameSpectr[i].setIm(qMax((frameSpectr[i].getIm() - K * noiseSpectr[i].getIm()), (double)0));
        }

        Signal clearFrame = fft.inverseFourierTransform(frameSpectr);

        for (int i = 0; i < clearFrame.size(); i++)
        {
            signal[pos + i] = clearFrame[i].toPcm16();
        }

        samples -= frameSize;
        pos += frameSize;
    }

    WavFile outFile("signal_without_noise.wav");
    outFile.open(WavFile::WriteOnly, signal.getFormat());

    outFile.write(signal);

    cout << "time: " << signal.time(signal.size()) << std::endl;
    cout << "signal file sample rate = " << signalFile.getHeader().sampleRate() << "; out file sample rate = "
            << outFile.getHeader().sampleRate() << endl;
    cout << "signal file size = " << signalFile.size() << "; out file size = " << outFile.size() << endl;

    noiseFile.close();
    signalFile.close();
    outFile.close();

    //out.close();
}
