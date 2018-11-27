#ifndef JLRXMLPARSER_H
#define JLRXMLPARSER_H

#include <QFile>
#include <QXmlStreamReader>
#include "mainwindow.h"
#include "romdatatypes.h"
#include "errorcodes.h"

class JlrXmlParser
{
public:
    JlrXmlParser();
    bool read(QIODevice *device);
    void readXML(void);

    /* Functions related to 'Information' tag */
    void processXmlInformation(void);
    void processVipConstantEnums(void);
    ERROR_CODES_T updateVipConstEnumTable(QXmlStreamReader& xml);
    void UpdateVariantInfo(QString const& variantData);
    void UpdateXmlVersion(const QString &xmlVersion);

    static inline QString versionAttribute() { return QStringLiteral("version"); }

private:
   QXmlStreamReader jlrXml;
   QFile *jlrFile;
   ROM_DATA_INFO romDataInfo;
   QList<ROM_DATA_VIP_CONST_ENUMS> romDataConstVipEnum;
};


#endif // JLRXMLPARSER_H
