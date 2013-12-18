# в этом файле собраны общие платформозависимые настройки сборки проекта.
# его можно подключать во всех подпроектах.

# сборка проекта для тестирования на обычной машине - desktop, сборка для трика - trik
CONFIG += trik

# подключаем pocketsphinx

#  -L/usr/local/lib
#LIBS += -lpthread -lm

# специфичные настройки для сборки под трик/десктоп
trik {
    message("Building for Trik")

    QT += multimedia

#    BUILD_FOLDER = ../../trik-build-arm

    DEFINES += TRIK
}
desktop {
    message("Building for desktop")

    CONFIG += mobility
    MOBILITY += multimedia
    INCLUDEPATH += /usr/include/QtMultimediaKit
    INCLUDEPATH += /usr/include/QtMobility

    BUILD_FOLDER = ../../debug

    DEFINES += DESKTOP
}
