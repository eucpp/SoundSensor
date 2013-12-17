#ifndef TRIKOGNITIONCE_H
#define TRIKOGNITIONCE_H

#include <ti/sdo/ce/audio1/audenc1.h>


#include "codecEngine.h"

class TrikognitionCE : public CodecEngine
{
	Q_OBJECT
public:
	TrikognitionCE(QObject *parent = 0);

	AUDENC1_Handle createAUDENC1() const;
signals:

public slots:

};

#endif // TRIKOGNITIONCE_H
