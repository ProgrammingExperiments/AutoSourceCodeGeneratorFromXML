#ifndef JLRXMLPARSER_H
#define JLRXMLPARSER_H

#include <QFile>
#include <QXmlStreamReader>
#include "mainwindow.h"

class JlrXmlParser
{
public:
    JlrXmlParser(QStatusBar* status);
    bool read(QIODevice *device);
    void readXML(void);

    /* Functions related to 'Information' tag */
    void processXmlInformation(void);
    void UpdateVariantInfo(QString const& variantData);


    static inline QString versionAttribute() { return QStringLiteral("version"); }

private:
   QXmlStreamReader jlrXml;
   QFile *jlrFile;
   QStringList variantList;
   QStatusBar* statusBar;
};


#endif // JLRXMLPARSER_H
