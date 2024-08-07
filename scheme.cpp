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
                               double pixelGridHeight, double imageHeight,bool blackLayer,QVector <double> colorSaturationLIst ,QVector <bool> colorlayerLIst) {
    QJsonObject scheme;
    scheme["imagePath"] = imagePath;
    scheme["blackLayer"] = blackLayer;
    scheme["pixelGridHeight"] = pixelGridHeight;
    scheme["halftoneGridType"] = halftoneGridType;
    scheme["gridImageSort"] = DrawLnType;
    scheme["colorlayereType"] = colorlayereType;
    scheme["imageHeight"] = imageHeight;
    scheme["grayLevel"] = grayLevel;

    for(int i=0;i<5;i++){
        scheme[QString("colorSaturationLIst%1").arg(i)] = colorSaturationLIst[i];
    }


    for(int i=0;i<4;i++){
        scheme[QString("colorlayerLIst%1").arg(i)] = colorlayerLIst[i];
    }

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(scheme).toJson());
        file.close();
    }
}

void Scheme::loadScheme(const QString &filePath, QString &imagePath,int &grayLevel ,int &halftoneGridType,int &DrawLnType,QString &colorlayereType,
                        double &pixelGridHeight, double &imageHeight,bool &blackLayer,QVector <double> &colorSaturationLIst ,QVector <bool> &colorlayerLIst) {
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
        pixelGridHeight = scheme["pixelGridHeight"].toDouble();
        blackLayer = scheme["blackLayer"].toBool();

        for (int i=0;i<5;i++) {
            colorSaturationLIst.append(scheme[QString("colorSaturationLIst%1").arg(i)].toDouble());

        }

        for(int i=0;i<4;i++){
            colorlayerLIst.append( scheme[QString("colorlayerLIst%1").arg(i)].toBool());
            qDebug()<<"colorlayerLIst"<<colorlayerLIst;
        }
    }
}

void Scheme::resetScheme() {
    schemePath = "";
    imagePath = "";

}
