// Scheme.h
#ifndef SCHEME_H
#define SCHEME_H

#include <QString>
#include <QJsonObject>

#include <Qvector>
class Scheme {
public:
    Scheme();
    void setSchemePath(const QString &path);
    QString getSchemePath() const;

    void saveCurrentScheme(const QString &filePath, const QString &imagePath,int grayLevel,int halftoneGridType,int DrawLnType,QString colorlayereType,
                           double dsbLineDistance, double imageHeight,bool blackLayer,QVector <double> colorSaturationLIst,QVector <bool> colorlayerLIst);

    void loadScheme(const QString &filePath, QString &imagePath,int &grayLevel,int &halftoneGridType,int &DrawLnType,QString &colorlayereType,
                    double &dsbLineDistance, double &imageHeight,bool &blackLayer,QVector <double> &colorSaturationLIst,QVector <bool> &colorlayerLIst);

    void resetScheme();  // 新建方案方法

public:
    QString schemePath;
    QString imagePath;



};

#endif // SCHEME_H
