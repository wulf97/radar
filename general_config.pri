unix {
    CONFIG(debug, debug|release) {
        LIBS += -L$${_PRO_FILE_PWD_}/../../debug/
        DESTDIR = $${_PRO_FILE_PWD_}/../../debug/
    } else {
        LIBS += -L$${_PRO_FILE_PWD_}/../../release/
        DESTDIR = $${_PRO_FILE_PWD_}/../../release/
    }

    RCC_DIR     = $${_PRO_FILE_PWD_}/../../build/rcc
    MOC_DIR     = $${_PRO_FILE_PWD_}/../../build/moc
    OBJECTS_DIR = $${_PRO_FILE_PWD_}/../../build/obj
    UI_DIR      = $${_PRO_FILE_PWD_}/../../build/ui
}
