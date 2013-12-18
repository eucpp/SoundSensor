#ifndef VIDTRANSCODE_CV_ARM_CLIENT_INCLUDE_INTERNAL_CODECENGINE_H_
#define VIDTRANSCODE_CV_ARM_CLIENT_INCLUDE_INTERNAL_CODECENGINE_H_

#include <QtGlobal>
#include <QObject>
#include <QString>
#include <QScopedPointer>

#include <libcodecengine-client/codecengine-client.h>
#include <ti/sdo/ce/audio1/audenc1.h>

namespace trik {

class CodecEngine : public QObject
{
	Q_OBJECT
public:
	explicit CodecEngine(QObject* _parent = NULL);
	virtual ~CodecEngine();

	AUDENC1_Handle createAUDENC1() const;
signals:
	void opened();
	void closed();

public slots:
	void setServerName(const QString& _name);
	void setServerPath(const QString& _path);

	bool open();
	bool close();

	void reportLoad();

private:
	class EngineControl;
	static EngineControl s_engineControl;

	class Handle;
	QScopedPointer<Handle> m_handle;

	QString m_serverName;
	QString m_serverPath;
};

}


#endif // !VIDTRANSCODE_CV_ARM_CLIENT_INCLUDE_INTERNAL_CODECENGINE_H_
