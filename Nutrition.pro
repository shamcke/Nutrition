QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++2a

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialog.cc \
    editDialog.cc \
    ingredient.cc \
    main.cc \
    mainwindow.cc \
    mapOfIngredients.cc \
    measuredIngredient.cc \
    newIngredientDialog.cc \
    recipeList.cc

HEADERS += \
    dialog.h \
    editDialog.h \
    ingredient.h \
    mainwindow.h \
    mapOfIngredients.h \
    measuredIngredient.h \
    newIngredientDialog.h \
    recipeList.h

FORMS += \
    dialog.ui \
    editDialog.ui \
    mainwindow.ui \
    newIngredientDialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
