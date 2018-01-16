QT       += widgets

TARGET = TranslateExternal
TEMPLATE = app

TRANSLATIONS = \
    translations/myapp_de.ts \
    translations/myapp_es.ts \
    translations/myapp_pl.ts \
    translations/myapp_ru.ts

SOURCES += \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    MainWindow.h \
    translations/data.tri

RESOURCES += \
    resources.qrc
