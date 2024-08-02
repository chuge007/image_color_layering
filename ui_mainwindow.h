/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *lbOriginalImageDisplay;
    QLabel *lbOriginalImageDisplay_c;
    QLabel *lbOriginalImageDisplay_m;
    QLabel *lbOriginalImageDisplay_y;
    QLabel *lbOriginalImageDisplay_k;
    QLabel *lbColor1;
    QLabel *lbColor2;
    QLabel *lbColor3;
    QLabel *lbColor4;
    QPushButton *pBstartLayering;
    QPushButton *pBloadImage;
    QDoubleSpinBox *dSBcAdjustmentCoefficient;
    QDoubleSpinBox *dSBmAdjustmentCoefficient;
    QDoubleSpinBox *dSByAdjustmentCoefficient;
    QDoubleSpinBox *dSBkAdjustmentCoefficient;
    QPushButton *pBsaveScheme;
    QLabel *label_23;
    QPushButton *pbNewScheme;
    QCheckBox *cbStartInScheme;
    QPushButton *pbOpenScheme;
    QPushButton *pBsaveSchemeAs;
    QLineEdit *leSchemeDameDisplay;
    QPushButton *pBexportVectorDiagram;
    QPushButton *pBexportGrayScaleImage;
    QLabel *lbOriginalImageDisplay_r;
    QLabel *lbOriginalImageDisplay_g;
    QLabel *lbOriginalImageDisplay_b;
    QGroupBox *groupBox;
    QSpinBox *sBimageHeight;
    QLabel *label_8;
    QLabel *label_9;
    QDoubleSpinBox *dSBpixelGridheight;
    QCheckBox *cBblackLayering;
    QComboBox *cmbColorLayerdType;
    QLabel *label_10;
    QGroupBox *groupBox_3;
    QRadioButton *rBrandomSorting;
    QRadioButton *rBsortNeatly;
    QRadioButton *rBaggregateSort;
    QCheckBox *cBSelectC;
    QCheckBox *cBSelectM;
    QCheckBox *cBSelectY;
    QCheckBox *cBSelectK;
    QCheckBox *cBSelectG;
    QCheckBox *cBSelectB;
    QCheckBox *cBSelectR;
    QSlider *hSColorSaturation;
    QLabel *label_5;
    QLabel *lbColorSaturationDisplay;
    QComboBox *cbGridType;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *lbImageName;
    QPushButton *pBdisplayImage1;
    QPushButton *pBdisplayImage2;
    QPushButton *pBdisplayImage3;
    QPushButton *pBdisplayImage4;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1073, 843);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        lbOriginalImageDisplay = new QLabel(centralWidget);
        lbOriginalImageDisplay->setObjectName(QString::fromUtf8("lbOriginalImageDisplay"));
        lbOriginalImageDisplay->setGeometry(QRect(24, 132, 284, 284));
        lbOriginalImageDisplay->setStyleSheet(QString::fromUtf8("background-color:rgb(74, 74, 74)"));
        lbOriginalImageDisplay_c = new QLabel(centralWidget);
        lbOriginalImageDisplay_c->setObjectName(QString::fromUtf8("lbOriginalImageDisplay_c"));
        lbOriginalImageDisplay_c->setGeometry(QRect(325, 132, 138, 138));
        lbOriginalImageDisplay_c->setStyleSheet(QString::fromUtf8("background-color:rgb(74, 74, 74)"));
        lbOriginalImageDisplay_c->setMargin(0);
        lbOriginalImageDisplay_m = new QLabel(centralWidget);
        lbOriginalImageDisplay_m->setObjectName(QString::fromUtf8("lbOriginalImageDisplay_m"));
        lbOriginalImageDisplay_m->setGeometry(QRect(474, 132, 138, 138));
        lbOriginalImageDisplay_m->setStyleSheet(QString::fromUtf8("background-color:rgb(74, 74, 74)"));
        lbOriginalImageDisplay_y = new QLabel(centralWidget);
        lbOriginalImageDisplay_y->setObjectName(QString::fromUtf8("lbOriginalImageDisplay_y"));
        lbOriginalImageDisplay_y->setGeometry(QRect(325, 318, 138, 138));
        lbOriginalImageDisplay_y->setStyleSheet(QString::fromUtf8("background-color:rgb(74, 74, 74)"));
        lbOriginalImageDisplay_k = new QLabel(centralWidget);
        lbOriginalImageDisplay_k->setObjectName(QString::fromUtf8("lbOriginalImageDisplay_k"));
        lbOriginalImageDisplay_k->setGeometry(QRect(474, 318, 138, 138));
        lbOriginalImageDisplay_k->setStyleSheet(QString::fromUtf8("background-color:rgb(74, 74, 74)"));
        lbColor1 = new QLabel(centralWidget);
        lbColor1->setObjectName(QString::fromUtf8("lbColor1"));
        lbColor1->setGeometry(QRect(330, 280, 81, 16));
        lbColor2 = new QLabel(centralWidget);
        lbColor2->setObjectName(QString::fromUtf8("lbColor2"));
        lbColor2->setGeometry(QRect(480, 280, 81, 16));
        lbColor3 = new QLabel(centralWidget);
        lbColor3->setObjectName(QString::fromUtf8("lbColor3"));
        lbColor3->setGeometry(QRect(330, 470, 81, 16));
        lbColor4 = new QLabel(centralWidget);
        lbColor4->setObjectName(QString::fromUtf8("lbColor4"));
        lbColor4->setGeometry(QRect(480, 470, 81, 16));
        pBstartLayering = new QPushButton(centralWidget);
        pBstartLayering->setObjectName(QString::fromUtf8("pBstartLayering"));
        pBstartLayering->setGeometry(QRect(180, 470, 128, 32));
        pBloadImage = new QPushButton(centralWidget);
        pBloadImage->setObjectName(QString::fromUtf8("pBloadImage"));
        pBloadImage->setGeometry(QRect(24, 132, 284, 284));
        pBloadImage->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"border: 1px solid black;"));
        dSBcAdjustmentCoefficient = new QDoubleSpinBox(centralWidget);
        dSBcAdjustmentCoefficient->setObjectName(QString::fromUtf8("dSBcAdjustmentCoefficient"));
        dSBcAdjustmentCoefficient->setGeometry(QRect(350, 280, 62, 22));
        dSBmAdjustmentCoefficient = new QDoubleSpinBox(centralWidget);
        dSBmAdjustmentCoefficient->setObjectName(QString::fromUtf8("dSBmAdjustmentCoefficient"));
        dSBmAdjustmentCoefficient->setGeometry(QRect(500, 280, 62, 22));
        dSByAdjustmentCoefficient = new QDoubleSpinBox(centralWidget);
        dSByAdjustmentCoefficient->setObjectName(QString::fromUtf8("dSByAdjustmentCoefficient"));
        dSByAdjustmentCoefficient->setGeometry(QRect(350, 470, 62, 22));
        dSBkAdjustmentCoefficient = new QDoubleSpinBox(centralWidget);
        dSBkAdjustmentCoefficient->setObjectName(QString::fromUtf8("dSBkAdjustmentCoefficient"));
        dSBkAdjustmentCoefficient->setGeometry(QRect(500, 470, 62, 22));
        pBsaveScheme = new QPushButton(centralWidget);
        pBsaveScheme->setObjectName(QString::fromUtf8("pBsaveScheme"));
        pBsaveScheme->setGeometry(QRect(460, 18, 75, 24));
        pBsaveScheme->setMinimumSize(QSize(44, 24));
        pBsaveScheme->setStyleSheet(QString::fromUtf8(""));
        label_23 = new QLabel(centralWidget);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(28, 18, 28, 26));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        label_23->setFont(font);
        pbNewScheme = new QPushButton(centralWidget);
        pbNewScheme->setObjectName(QString::fromUtf8("pbNewScheme"));
        pbNewScheme->setGeometry(QRect(610, 18, 75, 24));
        pbNewScheme->setMinimumSize(QSize(44, 24));
        pbNewScheme->setStyleSheet(QString::fromUtf8(""));
        cbStartInScheme = new QCheckBox(centralWidget);
        cbStartInScheme->setObjectName(QString::fromUtf8("cbStartInScheme"));
        cbStartInScheme->setGeometry(QRect(801, 24, 107, 16));
        pbOpenScheme = new QPushButton(centralWidget);
        pbOpenScheme->setObjectName(QString::fromUtf8("pbOpenScheme"));
        pbOpenScheme->setGeometry(QRect(385, 18, 75, 24));
        pbOpenScheme->setMinimumSize(QSize(44, 24));
        pbOpenScheme->setStyleSheet(QString::fromUtf8(""));
        pBsaveSchemeAs = new QPushButton(centralWidget);
        pBsaveSchemeAs->setObjectName(QString::fromUtf8("pBsaveSchemeAs"));
        pBsaveSchemeAs->setGeometry(QRect(535, 18, 75, 24));
        pBsaveSchemeAs->setMinimumSize(QSize(56, 24));
        pBsaveSchemeAs->setStyleSheet(QString::fromUtf8(""));
        leSchemeDameDisplay = new QLineEdit(centralWidget);
        leSchemeDameDisplay->setObjectName(QString::fromUtf8("leSchemeDameDisplay"));
        leSchemeDameDisplay->setGeometry(QRect(64, 20, 321, 20));
        pBexportVectorDiagram = new QPushButton(centralWidget);
        pBexportVectorDiagram->setObjectName(QString::fromUtf8("pBexportVectorDiagram"));
        pBexportVectorDiagram->setGeometry(QRect(660, 420, 128, 32));
        pBexportGrayScaleImage = new QPushButton(centralWidget);
        pBexportGrayScaleImage->setObjectName(QString::fromUtf8("pBexportGrayScaleImage"));
        pBexportGrayScaleImage->setGeometry(QRect(860, 420, 128, 32));
        lbOriginalImageDisplay_r = new QLabel(centralWidget);
        lbOriginalImageDisplay_r->setObjectName(QString::fromUtf8("lbOriginalImageDisplay_r"));
        lbOriginalImageDisplay_r->setGeometry(QRect(325, 132, 138, 138));
        lbOriginalImageDisplay_r->setStyleSheet(QString::fromUtf8("background-color:rgb(74, 74, 74)"));
        lbOriginalImageDisplay_r->setMargin(0);
        lbOriginalImageDisplay_g = new QLabel(centralWidget);
        lbOriginalImageDisplay_g->setObjectName(QString::fromUtf8("lbOriginalImageDisplay_g"));
        lbOriginalImageDisplay_g->setGeometry(QRect(475, 132, 138, 138));
        lbOriginalImageDisplay_g->setStyleSheet(QString::fromUtf8("background-color:rgb(74, 74, 74)"));
        lbOriginalImageDisplay_g->setMargin(0);
        lbOriginalImageDisplay_b = new QLabel(centralWidget);
        lbOriginalImageDisplay_b->setObjectName(QString::fromUtf8("lbOriginalImageDisplay_b"));
        lbOriginalImageDisplay_b->setGeometry(QRect(325, 322, 138, 138));
        lbOriginalImageDisplay_b->setStyleSheet(QString::fromUtf8("background-color:rgb(74, 74, 74)"));
        lbOriginalImageDisplay_b->setMargin(0);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(630, 140, 421, 81));
        sBimageHeight = new QSpinBox(groupBox);
        sBimageHeight->setObjectName(QString::fromUtf8("sBimageHeight"));
        sBimageHeight->setGeometry(QRect(90, 20, 61, 22));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 20, 54, 21));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 50, 91, 21));
        dSBpixelGridheight = new QDoubleSpinBox(groupBox);
        dSBpixelGridheight->setObjectName(QString::fromUtf8("dSBpixelGridheight"));
        dSBpixelGridheight->setGeometry(QRect(90, 50, 62, 22));
        dSBpixelGridheight->setMinimum(2.000000000000000);
        dSBpixelGridheight->setValue(2.000000000000000);
        cBblackLayering = new QCheckBox(groupBox);
        cBblackLayering->setObjectName(QString::fromUtf8("cBblackLayering"));
        cBblackLayering->setGeometry(QRect(210, 50, 121, 16));
        cmbColorLayerdType = new QComboBox(groupBox);
        cmbColorLayerdType->addItem(QString());
        cmbColorLayerdType->addItem(QString());
        cmbColorLayerdType->setObjectName(QString::fromUtf8("cmbColorLayerdType"));
        cmbColorLayerdType->setGeometry(QRect(290, 20, 71, 21));
        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(210, 20, 54, 21));
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(630, 260, 421, 71));
        rBrandomSorting = new QRadioButton(groupBox_3);
        rBrandomSorting->setObjectName(QString::fromUtf8("rBrandomSorting"));
        rBrandomSorting->setGeometry(QRect(130, 30, 89, 16));
        rBsortNeatly = new QRadioButton(groupBox_3);
        rBsortNeatly->setObjectName(QString::fromUtf8("rBsortNeatly"));
        rBsortNeatly->setGeometry(QRect(30, 30, 89, 16));
        rBaggregateSort = new QRadioButton(groupBox_3);
        rBaggregateSort->setObjectName(QString::fromUtf8("rBaggregateSort"));
        rBaggregateSort->setGeometry(QRect(230, 30, 89, 16));
        cBSelectC = new QCheckBox(centralWidget);
        cBSelectC->setObjectName(QString::fromUtf8("cBSelectC"));
        cBSelectC->setGeometry(QRect(440, 140, 71, 16));
        cBSelectM = new QCheckBox(centralWidget);
        cBSelectM->setObjectName(QString::fromUtf8("cBSelectM"));
        cBSelectM->setGeometry(QRect(590, 140, 71, 16));
        cBSelectY = new QCheckBox(centralWidget);
        cBSelectY->setObjectName(QString::fromUtf8("cBSelectY"));
        cBSelectY->setGeometry(QRect(440, 330, 71, 16));
        cBSelectK = new QCheckBox(centralWidget);
        cBSelectK->setObjectName(QString::fromUtf8("cBSelectK"));
        cBSelectK->setGeometry(QRect(590, 330, 71, 16));
        cBSelectG = new QCheckBox(centralWidget);
        cBSelectG->setObjectName(QString::fromUtf8("cBSelectG"));
        cBSelectG->setGeometry(QRect(590, 140, 71, 16));
        cBSelectB = new QCheckBox(centralWidget);
        cBSelectB->setObjectName(QString::fromUtf8("cBSelectB"));
        cBSelectB->setGeometry(QRect(440, 330, 71, 16));
        cBSelectR = new QCheckBox(centralWidget);
        cBSelectR->setObjectName(QString::fromUtf8("cBSelectR"));
        cBSelectR->setGeometry(QRect(440, 140, 71, 16));
        hSColorSaturation = new QSlider(centralWidget);
        hSColorSaturation->setObjectName(QString::fromUtf8("hSColorSaturation"));
        hSColorSaturation->setGeometry(QRect(70, 421, 191, 31));
        hSColorSaturation->setMaximum(100);
        hSColorSaturation->setSingleStep(0);
        hSColorSaturation->setValue(10);
        hSColorSaturation->setOrientation(Qt::Horizontal);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 430, 54, 12));
        lbColorSaturationDisplay = new QLabel(centralWidget);
        lbColorSaturationDisplay->setObjectName(QString::fromUtf8("lbColorSaturationDisplay"));
        lbColorSaturationDisplay->setGeometry(QRect(270, 420, 54, 31));
        cbGridType = new QComboBox(centralWidget);
        cbGridType->addItem(QString());
        cbGridType->addItem(QString());
        cbGridType->setObjectName(QString::fromUtf8("cbGridType"));
        cbGridType->setGeometry(QRect(70, 470, 71, 31));
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(20, 472, 54, 21));
        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(20, 100, 31, 16));
        lbImageName = new QLabel(centralWidget);
        lbImageName->setObjectName(QString::fromUtf8("lbImageName"));
        lbImageName->setGeometry(QRect(60, 100, 241, 16));
        pBdisplayImage1 = new QPushButton(centralWidget);
        pBdisplayImage1->setObjectName(QString::fromUtf8("pBdisplayImage1"));
        pBdisplayImage1->setGeometry(QRect(330, 160, 131, 101));
        pBdisplayImage1->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"border: 1px solid black;"));
        pBdisplayImage2 = new QPushButton(centralWidget);
        pBdisplayImage2->setObjectName(QString::fromUtf8("pBdisplayImage2"));
        pBdisplayImage2->setGeometry(QRect(480, 160, 131, 101));
        pBdisplayImage2->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"border: 1px solid black;"));
        pBdisplayImage3 = new QPushButton(centralWidget);
        pBdisplayImage3->setObjectName(QString::fromUtf8("pBdisplayImage3"));
        pBdisplayImage3->setGeometry(QRect(330, 350, 131, 101));
        pBdisplayImage3->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"border: 1px solid black;"));
        pBdisplayImage4 = new QPushButton(centralWidget);
        pBdisplayImage4->setObjectName(QString::fromUtf8("pBdisplayImage4"));
        pBdisplayImage4->setGeometry(QRect(480, 350, 131, 101));
        pBdisplayImage4->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"border: 1px solid black;"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1073, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        lbOriginalImageDisplay->setText(QString());
        lbOriginalImageDisplay_c->setText(QString());
        lbOriginalImageDisplay_m->setText(QString());
        lbOriginalImageDisplay_y->setText(QString());
        lbOriginalImageDisplay_k->setText(QString());
        lbColor1->setText(QApplication::translate("MainWindow", "C", nullptr));
        lbColor2->setText(QApplication::translate("MainWindow", "M", nullptr));
        lbColor3->setText(QApplication::translate("MainWindow", "Y", nullptr));
        lbColor4->setText(QApplication::translate("MainWindow", "K", nullptr));
        pBstartLayering->setText(QApplication::translate("MainWindow", "\347\224\237\346\210\220", nullptr));
        pBloadImage->setText(QString());
        pBsaveScheme->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
        label_23->setText(QApplication::translate("MainWindow", "\346\226\271\346\241\210", nullptr));
        pbNewScheme->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272", nullptr));
        cbStartInScheme->setText(QApplication::translate("MainWindow", "\345\220\257\345\212\250\346\227\266\346\211\223\345\274\200\346\226\271\346\241\210", nullptr));
        pbOpenScheme->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200", nullptr));
        pBsaveSchemeAs->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\344\270\272", nullptr));
        pBexportVectorDiagram->setText(QApplication::translate("MainWindow", "\345\257\274\345\207\272\347\237\242\351\207\217\345\233\276", nullptr));
        pBexportGrayScaleImage->setText(QApplication::translate("MainWindow", "\345\257\274\345\207\272\347\201\260\345\272\246\345\233\276", nullptr));
        lbOriginalImageDisplay_r->setText(QString());
        lbOriginalImageDisplay_g->setText(QString());
        lbOriginalImageDisplay_b->setText(QString());
        groupBox->setTitle(QApplication::translate("MainWindow", "\351\200\232\347\224\250\350\256\276\347\275\256", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "\345\233\276\347\211\207\351\253\230\345\272\246\357\274\232", nullptr));
        label_9->setText(QApplication::translate("MainWindow", "\345\203\217\347\264\240\347\275\221\346\240\274\351\253\230\345\272\246\357\274\232", nullptr));
        cBblackLayering->setText(QApplication::translate("MainWindow", "\351\273\221\350\211\262\345\210\206\345\261\202\346\254\241", nullptr));
        cmbColorLayerdType->setItemText(0, QApplication::translate("MainWindow", "CMYK", nullptr));
        cmbColorLayerdType->setItemText(1, QApplication::translate("MainWindow", "RGB", nullptr));

        label_10->setText(QApplication::translate("MainWindow", "\345\210\206\345\261\202\347\261\273\345\236\213\357\274\232", nullptr));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "\345\257\274\345\207\272\347\201\260\345\272\246\345\233\276\350\256\276\347\275\256", nullptr));
        rBrandomSorting->setText(QApplication::translate("MainWindow", "\351\232\217\346\234\272\346\216\222\345\272\217", nullptr));
        rBsortNeatly->setText(QApplication::translate("MainWindow", "\346\225\264\351\275\220\346\216\222\345\272\217", nullptr));
        rBaggregateSort->setText(QApplication::translate("MainWindow", "\350\201\232\351\233\206\346\216\222\345\272\217", nullptr));
        cBSelectC->setText(QString());
        cBSelectM->setText(QString());
        cBSelectY->setText(QString());
        cBSelectK->setText(QString());
        cBSelectG->setText(QString());
        cBSelectB->setText(QString());
        cBSelectR->setText(QString());
        label_5->setText(QApplication::translate("MainWindow", "\351\245\261\345\222\214\345\272\246\357\274\232", nullptr));
        lbColorSaturationDisplay->setText(QString());
        cbGridType->setItemText(0, QApplication::translate("MainWindow", "\345\234\206\347\202\271", nullptr));
        cbGridType->setItemText(1, QApplication::translate("MainWindow", "\346\226\271\347\202\271", nullptr));

        label_12->setText(QApplication::translate("MainWindow", "\347\275\221\347\202\271\357\274\232", nullptr));
        label_13->setText(QApplication::translate("MainWindow", "\346\226\207\344\273\266\357\274\232", nullptr));
        lbImageName->setText(QString());
        pBdisplayImage1->setText(QString());
        pBdisplayImage2->setText(QString());
        pBdisplayImage3->setText(QString());
        pBdisplayImage4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
