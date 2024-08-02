// Scheme.h
#ifndef SCHEME_H
#define SCHEME_H

#include <QString>
#include <QJsonObject>

class Scheme {
public:
    Scheme();
    void setSchemePath(const QString &path);
    QString getSchemePath() const;

    void saveCurrentScheme(const QString &filePath, const QString &imagePath, double colorSaturation, bool blackLayer, double pixelGridHeight);
    void loadScheme(const QString &filePath, QString &imagePath, double &colorSaturation, bool &blackLayer, double &pixelGridHeight);

    void resetScheme();  // 新建方案方法

public:
    QString schemePath;
    QString imagePath;


private:
    double colorSaturation;
    bool blackLayer;
    double pixelGridHeight;
};

#endif // SCHEME_H
