#ifndef FOURIERTRANSFORM_H
#define FOURIERTRANSFORM_H

#include "define.h"


/**
  * Абстрактный класс, предоставляет интерфейс для алгоритмов преобразования Фурье.
  */
class FourierTransform
{
public:
    class SizeExc {};

    enum WindowFunction
    {
        Rectangle,
        HannWindow
    };

    virtual ~FourierTransform()
    {}
    /**
      * Прямое преобразование Фурье.
      *
      * @param inBuff входной буфер, содержащий комплексный сигнал для преобразования
      *     (должен быть размера 2 * size * sampleSize байт).
      * @param outBuff буфер, в который помещается результат (массив из size комплексных чисел,
      *     действительная часть числа i хранится в элементе с индесом [2 * i], мнимая в [2 * i + 1]),
      *     должен быть размера 2 * size * sampleSize байт.
      * @param size размер сигнала в сэмплах (должен быть степенью двойки).
      * @param sampleSize размер сэмпла в байтах.
      * @param window оконная функция, применяемая к сигналу.
      */
    virtual void fourierTransform(char* inBuff, char* outBuff, int size, int sampleSize,
                                  WindowFunction window = Rectangle) = 0;
    /**
      * Обратное преобразование Фурье.
      *
      * @param inBuff входной буфер, содержащий комплесный спектр для преобразования
      *     (должен быть размера 2 * size * sampleSize байт).
      * @param outBuff буфер, в который помещается результат (массив из size комплексных чисел,
      *     действительная часть числа i хранится в элементе с индесом [2 * i], мнимая в [2 * i + 1]).
      * @param size размер спектра (должен быть степенью двойки).
      * @param sampleSize размер сэмпла в байтах.
      */
    virtual void inverseFourierTransform(char* inBuff, char* outBuff, int size, int sampleSize) = 0;
};

#endif // FOURIERTRANSFORM_H
