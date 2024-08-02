// Scheme.cpp
#include "Scheme.h"
#include <QFile>
#include <QJsonDocument>

Scheme::Scheme() : schemePath(""), colorSaturation(1.0), blackLayer(false), pixelGridHeight(1.0) {}

void Scheme::setSchemePath(const QString &path) {
    schemePath = path;
}

QString Scheme::getSchemePath() const {
    return schemePath;
}

void Scheme::saveCurrentScheme(const QString &filePath, const QString &imagePath, double colorSaturation, bool blackLayer, double pixelGridHeight) {
    QJsonObject scheme;
    scheme["imagePath"] = imagePath;
    scheme["colorSaturation"] = colorSaturation;
    scheme["blackLayer"] = blackLayer;
    scheme["pixelGridHeight"] = pixelGridHeight;

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(scheme).toJson());
        file.close();
    }
}

void Scheme::loadScheme(const QString &filePath, QString &imagePath, double &colorSaturation, bool &blackLayer, double &pixelGridHeight) {
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        QJsonObject scheme = QJsonDocument::fromJson(file.readAll()).object();
        file.close();

        imagePath = scheme["imagePath"].toString();
        colorSaturation = scheme["colorSaturation"].toDouble();
        blackLayer = scheme["blackLayer"].toBool();
        pixelGridHeight = scheme["pixelGridHeight"].toDouble();
    }
}

void Scheme::resetScheme() {
    schemePath = "";
    imagePath = "";
    colorSaturation = 1.0;
    blackLayer = false;
    pixelGridHeight = 1.0;
}
