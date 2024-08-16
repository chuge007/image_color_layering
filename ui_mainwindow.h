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
    QLabel *lbOriginalImageDisplay_cORr;
    QLabel *lbOriginalImageDisplay_mORg;
    QLabel *lbOriginalImageDisplay_yORb;
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
    QGroupBox *groupBox;
    QSpinBox *sBimageHeight;
    QLabel *label_8;
    QLabel *label_9;
    QDoubleSpinBox *dsbLineDistance;
    QCheckBox *cBblackLayering;
    QComboBox *cmbColorLayerdType;
    QLabel *label_10;
    QLabel *label;
    QLabel *label_2;
    QComboBox *cmbDrawLnType;
    QLabel *label_11;
    QSpinBox *sbGrayLevel;
    QLabel *label_14;
    QRadioButton *rBisWithMatrix;
    QCheckBox *cBSelectCorR;
    QCheckBox *cBSelectMorG;
    QCheckBox *cBSelectYorB;
    QCheckBox *cBSelectK;
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
        MainWindow->resize(807, 782);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        lbOriginalImageDisplay = new QLabel(centralWidget);
        lbOriginalImageDisplay->setObjectName(QString::fromUtf8("lbOriginalImageDisplay"));
        lbOriginalImageDisplay->setGeometry(QRect(24, 132, 284, 284));
        lbOriginalImageDisplay->setStyleSheet(QString::fromUtf8("background-color:rgb(74, 74, 74)"));
        lbOriginalImageDisplay_cORr = new QLabel(centralWidget);
        lbOriginalImageDisplay_cORr->setObjectName(QString::fromUtf8("lbOriginalImageDisplay_cORr"));
        lbOriginalImageDisplay_cORr->setGeometry(QRect(365, 132, 138, 138));
        lbOriginalImageDisplay_cORr->setStyleSheet(QString::fromUtf8("background-color:rgb(74, 74, 74)"));
        lbOriginalImageDisplay_cORr->setMargin(0);
        lbOriginalImageDisplay_mORg = new QLabel(centralWidget);
        lbOriginalImageDisplay_mORg->setObjectName(QString::fromUtf8("lbOriginalImageDisplay_mORg"));
        lbOriginalImageDisplay_mORg->setGeometry(QRect(570, 132, 141, 141));
        lbOriginalImageDisplay_mORg->setStyleSheet(QString::fromUtf8("background-color:rgb(74, 74, 74)"));
        lbOriginalImageDisplay_yORb = new QLabel(centralWidget);
        lbOriginalImageDisplay_yORb->setObjectName(QString::fromUtf8("lbOriginalImageDisplay_yORb"));
        lbOriginalImageDisplay_yORb->setGeometry(QRect(365, 318, 138, 138));
        lbOriginalImageDisplay_yORb->setStyleSheet(QString::fromUtf8("background-color:rgb(74, 74, 74)"));
        lbOriginalImageDisplay_k = new QLabel(centralWidget);
        lbOriginalImageDisplay_k->setObjectName(QString::fromUtf8("lbOriginalImageDisplay_k"));
        lbOriginalImageDisplay_k->setGeometry(QRect(570, 318, 138, 138));
        lbOriginalImageDisplay_k->setStyleSheet(QString::fromUtf8("background-color:rgb(74, 74, 74)"));
        lbColor1 = new QLabel(centralWidget);
        lbColor1->setObjectName(QString::fromUtf8("lbColor1"));
        lbColor1->setGeometry(QRect(370, 280, 81, 16));
        lbColor2 = new QLabel(centralWidget);
        lbColor2->setObjectName(QString::fromUtf8("lbColor2"));
        lbColor2->setGeometry(QRect(570, 280, 81, 16));
        lbColor3 = new QLabel(centralWidget);
        lbColor3->setObjectName(QString::fromUtf8("lbColor3"));
        lbColor3->setGeometry(QRect(370, 470, 81, 16));
        lbColor4 = new QLabel(centralWidget);
        lbColor4->setObjectName(QString::fromUtf8("lbColor4"));
        lbColor4->setGeometry(QRect(570, 470, 81, 16));
        pBstartLayering = new QPushButton(centralWidget);
        pBstartLayering->setObjectName(QString::fromUtf8("pBstartLayering"));
        pBstartLayering->setGeometry(QRect(180, 590, 128, 32));
        pBloadImage = new QPushButton(centralWidget);
        pBloadImage->setObjectName(QString::fromUtf8("pBloadImage"));
        pBloadImage->setGeometry(QRect(24, 132, 284, 284));
        pBloadImage->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"border: 1px solid black;"));
        dSBcAdjustmentCoefficient = new QDoubleSpinBox(centralWidget);
        dSBcAdjustmentCoefficient->setObjectName(QString::fromUtf8("dSBcAdjustmentCoefficient"));
        dSBcAdjustmentCoefficient->setGeometry(QRect(400, 280, 62, 22));
        dSBcAdjustmentCoefficient->setMaximum(3.000000000000000);
        dSBcAdjustmentCoefficient->setSingleStep(0.010000000000000);
        dSBmAdjustmentCoefficient = new QDoubleSpinBox(centralWidget);
        dSBmAdjustmentCoefficient->setObjectName(QString::fromUtf8("dSBmAdjustmentCoefficient"));
        dSBmAdjustmentCoefficient->setGeometry(QRect(600, 280, 62, 22));
        dSBmAdjustmentCoefficient->setMaximum(3.000000000000000);
        dSBmAdjustmentCoefficient->setSingleStep(0.010000000000000);
        dSByAdjustmentCoefficient = new QDoubleSpinBox(centralWidget);
        dSByAdjustmentCoefficient->setObjectName(QString::fromUtf8("dSByAdjustmentCoefficient"));
        dSByAdjustmentCoefficient->setGeometry(QRect(400, 470, 62, 22));
        dSByAdjustmentCoefficient->setMaximum(3.000000000000000);
        dSByAdjustmentCoefficient->setSingleStep(0.010000000000000);
        dSBkAdjustmentCoefficient = new QDoubleSpinBox(centralWidget);
        dSBkAdjustmentCoefficient->setObjectName(QString::fromUtf8("dSBkAdjustmentCoefficient"));
        dSBkAdjustmentCoefficient->setGeometry(QRect(590, 470, 62, 22));
        dSBkAdjustmentCoefficient->setMaximum(3.000000000000000);
        dSBkAdjustmentCoefficient->setSingleStep(0.010000000000000);
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
        cbStartInScheme->setGeometry(QRect(700, 24, 107, 16));
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
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 490, 701, 81));
        sBimageHeight = new QSpinBox(groupBox);
        sBimageHeight->setObjectName(QString::fromUtf8("sBimageHeight"));
        sBimageHeight->setGeometry(QRect(90, 20, 61, 22));
        sBimageHeight->setMaximum(1000000000);
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 20, 54, 21));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 50, 91, 21));
        dsbLineDistance = new QDoubleSpinBox(groupBox);
        dsbLineDistance->setObjectName(QString::fromUtf8("dsbLineDistance"));
        dsbLineDistance->setGeometry(QRect(90, 50, 62, 22));
        dsbLineDistance->setDecimals(3);
        dsbLineDistance->setMinimum(0.000000000000000);
        dsbLineDistance->setMaximum(1000000000000000019884624838656.000000000000000);
        dsbLineDistance->setSingleStep(0.001000000000000);
        dsbLineDistance->setValue(0.100000000000000);
        cBblackLayering = new QCheckBox(groupBox);
        cBblackLayering->setObjectName(QString::fromUtf8("cBblackLayering"));
        cBblackLayering->setGeometry(QRect(370, 50, 81, 21));
        cmbColorLayerdType = new QComboBox(groupBox);
        cmbColorLayerdType->addItem(QString());
        cmbColorLayerdType->addItem(QString());
        cmbColorLayerdType->setObjectName(QString::fromUtf8("cmbColorLayerdType"));
        cmbColorLayerdType->setGeometry(QRect(270, 20, 71, 21));
        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(200, 20, 54, 21));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(160, 20, 31, 21));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(160, 50, 31, 21));
        cmbDrawLnType = new QComboBox(groupBox);
        cmbDrawLnType->addItem(QString());
        cmbDrawLnType->addItem(QString());
        cmbDrawLnType->setObjectName(QString::fromUtf8("cmbDrawLnType"));
        cmbDrawLnType->setGeometry(QRect(270, 50, 71, 21));
        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(200, 50, 54, 21));
        sbGrayLevel = new QSpinBox(groupBox);
        sbGrayLevel->setObjectName(QString::fromUtf8("sbGrayLevel"));
        sbGrayLevel->setGeometry(QRect(430, 20, 61, 22));
        sbGrayLevel->setMinimum(0);
        sbGrayLevel->setMaximum(256);
        sbGrayLevel->setValue(0);
        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(370, 20, 54, 21));
        rBisWithMatrix = new QRadioButton(groupBox);
        rBisWithMatrix->setObjectName(QString::fromUtf8("rBisWithMatrix"));
        rBisWithMatrix->setGeometry(QRect(580, 50, 89, 21));
        rBisWithMatrix->setChecked(true);
        cBSelectCorR = new QCheckBox(centralWidget);
        cBSelectCorR->setObjectName(QString::fromUtf8("cBSelectCorR"));
        cBSelectCorR->setGeometry(QRect(480, 140, 71, 16));
        cBSelectMorG = new QCheckBox(centralWidget);
        cBSelectMorG->setObjectName(QString::fromUtf8("cBSelectMorG"));
        cBSelectMorG->setGeometry(QRect(680, 140, 71, 16));
        cBSelectYorB = new QCheckBox(centralWidget);
        cBSelectYorB->setObjectName(QString::fromUtf8("cBSelectYorB"));
        cBSelectYorB->setGeometry(QRect(480, 330, 71, 16));
        cBSelectK = new QCheckBox(centralWidget);
        cBSelectK->setObjectName(QString::fromUtf8("cBSelectK"));
        cBSelectK->setGeometry(QRect(680, 330, 71, 16));
        hSColorSaturation = new QSlider(centralWidget);
        hSColorSaturation->setObjectName(QString::fromUtf8("hSColorSaturation"));
        hSColorSaturation->setGeometry(QRect(70, 430, 191, 31));
        hSColorSaturation->setMaximum(100);
        hSColorSaturation->setSingleStep(0);
        hSColorSaturation->setValue(0);
        hSColorSaturation->setOrientation(Qt::Horizontal);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 440, 54, 12));
        lbColorSaturationDisplay = new QLabel(centralWidget);
        lbColorSaturationDisplay->setObjectName(QString::fromUtf8("lbColorSaturationDisplay"));
        lbColorSaturationDisplay->setGeometry(QRect(270, 430, 54, 31));
        cbGridType = new QComboBox(centralWidget);
        cbGridType->addItem(QString());
        cbGridType->addItem(QString());
        cbGridType->setObjectName(QString::fromUtf8("cbGridType"));
        cbGridType->setGeometry(QRect(60, 590, 71, 31));
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(20, 590, 54, 21));
        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(20, 100, 31, 16));
        lbImageName = new QLabel(centralWidget);
        lbImageName->setObjectName(QString::fromUtf8("lbImageName"));
        lbImageName->setGeometry(QRect(60, 100, 551, 16));
        pBdisplayImage1 = new QPushButton(centralWidget);
        pBdisplayImage1->setObjectName(QString::fromUtf8("pBdisplayImage1"));
        pBdisplayImage1->setGeometry(QRect(365, 250, 138, 21));
        pBdisplayImage1->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"border: 1px solid black;"));
        pBdisplayImage2 = new QPushButton(centralWidget);
        pBdisplayImage2->setObjectName(QString::fromUtf8("pBdisplayImage2"));
        pBdisplayImage2->setGeometry(QRect(570, 250, 141, 21));
        pBdisplayImage2->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"border: 1px solid black;"));
        pBdisplayImage3 = new QPushButton(centralWidget);
        pBdisplayImage3->setObjectName(QString::fromUtf8("pBdisplayImage3"));
        pBdisplayImage3->setGeometry(QRect(365, 440, 138, 16));
        pBdisplayImage3->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"border: 1px solid black;"));
        pBdisplayImage4 = new QPushButton(centralWidget);
        pBdisplayImage4->setObjectName(QString::fromUtf8("pBdisplayImage4"));
        pBdisplayImage4->setGeometry(QRect(570, 440, 138, 16));
        pBdisplayImage4->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"border: 1px solid black;"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 807, 23));
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
        lbOriginalImageDisplay_cORr->setText(QString());
        lbOriginalImageDisplay_mORg->setText(QString());
        lbOriginalImageDisplay_yORb->setText(QString());
        lbOriginalImageDisplay_k->setText(QString());
        lbColor1->setText(QApplication::translate("MainWindow", "C(R)", nullptr));
        lbColor2->setText(QApplication::translate("MainWindow", "M(G)", nullptr));
        lbColor3->setText(QApplication::translate("MainWindow", "Y(B)", nullptr));
        lbColor4->setText(QApplication::translate("MainWindow", "K", nullptr));
        pBstartLayering->setText(QApplication::translate("MainWindow", "\347\224\237\346\210\220", nullptr));
        pBloadImage->setText(QString());
        pBsaveScheme->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
        label_23->setText(QApplication::translate("MainWindow", "\346\226\271\346\241\210", nullptr));
        pbNewScheme->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272", nullptr));
        cbStartInScheme->setText(QApplication::translate("MainWindow", "\345\220\257\345\212\250\346\227\266\346\211\223\345\274\200\346\226\271\346\241\210", nullptr));
        pbOpenScheme->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200", nullptr));
        pBsaveSchemeAs->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\344\270\272", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "\351\200\232\347\224\250\350\256\276\347\275\256", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "\345\233\276\347\211\207\351\253\230\345\272\246\357\274\232", nullptr));
        label_9->setText(QApplication::translate("MainWindow", "\347\272\277\351\227\264\350\267\235\357\274\232", nullptr));
        cBblackLayering->setText(QApplication::translate("MainWindow", "\351\273\221\350\211\262\345\210\206\345\261\202\346\254\241", nullptr));
        cmbColorLayerdType->setItemText(0, QApplication::translate("MainWindow", "CMYK", nullptr));
        cmbColorLayerdType->setItemText(1, QApplication::translate("MainWindow", "RGB", nullptr));

        label_10->setText(QApplication::translate("MainWindow", "\345\210\206\345\261\202\347\261\273\345\236\213\357\274\232", nullptr));
        label->setText(QApplication::translate("MainWindow", "mm", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "mm", nullptr));
        cmbDrawLnType->setItemText(0, QApplication::translate("MainWindow", "\346\250\252\347\272\277", nullptr));
        cmbDrawLnType->setItemText(1, QApplication::translate("MainWindow", "\347\253\226\347\272\277", nullptr));

        label_11->setText(QApplication::translate("MainWindow", "\347\233\264\347\272\277\347\261\273\345\236\213\357\274\232", nullptr));
        label_14->setText(QApplication::translate("MainWindow", "\347\201\260\345\272\246\345\261\202\347\272\247\357\274\232", nullptr));
        rBisWithMatrix->setText(QApplication::translate("MainWindow", "\351\253\230\346\225\260\346\215\256\346\250\241\345\274\217", nullptr));
        cBSelectCorR->setText(QString());
        cBSelectMorG->setText(QString());
        cBSelectYorB->setText(QString());
        cBSelectK->setText(QString());
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
