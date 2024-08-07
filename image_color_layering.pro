#-------------------------------------------------
#
# Project created by QtCreator 2024-07-24T18:09:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = image_color_layering
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    floydsetinTool.cpp \
    improcesstool.cpp \
        main.cpp \
        mainwindow.cpp \
    scheme.cpp


HEADERS += \
    floydsetinTool.h \
    improcesstool.h \
        mainwindow.h \
    scheme.h



FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target




#INCLUDEPATH += "G:/opencv_4.5.4_mingw730/opencv/build_opencv_64/install/include"

## 添加库路径和库文件
#CONFIG(debug, debug|release) {
#    DEFINES += DEBUG_BUILD
#    LIBS += -L"G:/opencv_4.5.4_mingw730/opencv/build_opencv_64/install/x64/mingw/lib" \
#            -llibopencv_calib3d450.dll \
#            -llibopencv_core450.dll \
#            -llibopencv_dnn450.dll\
#            -llibopencv_features2d450.dll \
#            -llibopencv_flann450.dll \
#            -llibopencv_highgui450.dll \
#            -llibopencv_imgcodecs450.dll \
#            -llibopencv_imgproc450.dll \
#            -llibopencv_ml450.dll \
#            -llibopencv_objdetect450.dll \
#            -llibopencv_photo450.dll \
#            -llibopencv_stitching450.dll \
#            -llibopencv_video450.dll \
#            -llibopencv_videoio450.dll
#} else {
#    DEFINES += RELEASE_BUILD
#    LIBS += -L"G:/opencv_4.5.4_mingw730/opencv/build_opencv_64/install/x64/mingw/lib" \
#            -llibopencv_calib3d450.dll\
#            -llibopencv_core450.dll \
#            -llibopencv_dnn450.dll \
#            -llibopencv_features2d450.dll \
#            -llibopencv_flann450.dll \
#            -llibopencv_highgui450.dll \
#            -llibopencv_imgcodecs450.dll \
#            -llibopencv_imgproc450.dll \
#            -llibopencv_ml450.dll \
#            -llibopencv_objdetect450.dll \
#            -llibopencv_photo450.dll \
#            -llibopencv_stitching450.dll \
#            -llibopencv_video450.dll \
#            -llibopencv_videoio450.dll
#}

INCLUDEPATH += "G:/opencv_4.8.1_msvc/opencv/build/include"

#LIBS += -L"G:/opencv_4.8.1_msvc/opencv\build/x64/vc16/lib" -lopencv_world481d
#CONFIG(debug, debug|release) {
#    DEFINES += DEBUG_BUILD
#    LIBS += -L"G:/opencv_4.8.1_msvc/opencv\build/x64/vc16/lib" -lopencv_world481d
#} else {
#    DEFINES += RELEASE_BUILD
#    LIBS += -L"G:/opencv_4.8.1_msvc/opencv\build/x64/vc16/lib" -lopencv_world481
#}

LIBS += -L"G:/opencv_4.8.1_msvc/opencv\build/x64/vc16/lib" -lopencv_world481d


#LIBS += -L"G:\mingw64-potrace\lib"  -llibpotrace

#LIBS += -L"G:/potrace-1.15/src_mini/potrace/bin/Debug"  -llibpotrace

#LIBS += -L"G:/potrace-1.15/src_mini/mingw730"  -llibpotrace.dll

#LIBS += -L"G:/potrace-1.16/potrace-1.16_mingw730/src_mini/lib"  -llibpotrace.dll



DISTFILES += \
    Makefile \
    Makefile.Debug \
    Makefile.Release \
    image_color_layering.pro.user
