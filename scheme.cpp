// Scheme.cpp
#include "Scheme.h"
#include <QFile>
#include <QJsonDocument>
#include <QDebug>
Scheme::Scheme(){}

void Scheme::setSchemePath(const QString &path) {
    schemePath = path;
}

QString Scheme::getSchemePath() const {
    return schemePath;
}

void Scheme::saveCurrentScheme(const QString &filePath, const QString &imagePath,int grayLevel,int halftoneGridType,int DrawLnType,QString colorlayereType,
                               double dsbLineDistance, double imageHeight,bool blackLayer, double  dataDenstyScaling,int BlackRange,QVector <double> colorSaturationLIst ,QVector <bool> colorlayerLIst,QVector<QVector<int>> ColorCorrection) {
    QJsonObject scheme;
    scheme["imagePath"] = imagePath;
    scheme["blackLayer"] = blackLayer;
    scheme["dsbLineDistance"] = dsbLineDistance;
    scheme["halftoneGridType"] = halftoneGridType;
    scheme["gridImageSort"] = DrawLnType;
    scheme["colorlayereType"] = colorlayereType;
    scheme["imageHeight"] = imageHeight;
    scheme["grayLevel"] = grayLevel;
    scheme["dataDenstyScaling"] = dataDenstyScaling;
    scheme["BlackRange"] = BlackRange;
    for(int i=0;i<5;i++){
        scheme[QString("colorSaturationLIst%1").arg(i)] = colorSaturationLIst[i];
    }


    for(int i=0;i<4;i++){
        scheme[QString("colorlayerLIst%1").arg(i)] = colorlayerLIst[i];
    }


    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            scheme[QString("ColorCorrection%1%2").arg(i).arg(j)] = ColorCorrection[i][j];
        }
    }

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(scheme).toJson());
        file.close();
    }
}

void Scheme::loadScheme(const QString &filePath, QString &imagePath,int &grayLevel ,int &halftoneGridType,int &DrawLnType,QString &colorlayereType,
                        double &dsbLineDistance, double &imageHeight,bool &blackLayer, double &dataDenstyScaling,int &BlackRange,QVector <double> &colorSaturationLIst ,QVector <bool> &colorlayerLIst,QVector<QVector<int>> &ColorCorrection) {
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        QJsonObject scheme = QJsonDocument::fromJson(file.readAll()).object();
        file.close();

        imagePath = QString(scheme["imagePath"].toString());
        grayLevel=scheme["grayLevel"].toInt();
        halftoneGridType=scheme["halftoneGridType"].toInt();
        DrawLnType=scheme["gridImageSort"].toInt();
        colorlayereType=scheme["colorlayereType"].toString();


        imageHeight = scheme["imageHeight"].toDouble();
        dsbLineDistance = scheme["dsbLineDistance"].toDouble();
        blackLayer = scheme["blackLayer"].toBool();
        dataDenstyScaling = scheme["dataDenstyScaling"].toDouble();
        BlackRange = scheme["BlackRange"].toInt();
        ColorCorrection={{100,0,0},{0,100,0},{0,0,100}};
        for (int i=0;i<5;i++) {
            colorSaturationLIst.append(scheme[QString("colorSaturationLIst%1").arg(i)].toDouble());

        }

        for(int i=0;i<4;i++){
            colorlayerLIst.append( scheme[QString("colorlayerLIst%1").arg(i)].toBool());

        }

        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                ColorCorrection[i][j] = scheme[QString("ColorCorrection%1%2").arg(i).arg(j)].toInt();
            }
        }

    }
}

void Scheme::resetScheme() {
    schemePath = "";
    imagePath = "";

}
