#ifndef JLRXMLPARSER_H
#define JLRXMLPARSER_H

#include <QFile>
#include <QXmlStreamReader>

class JlrXmlParser
{
public:
    JlrXmlParser(void);
    bool read(QIODevice *device);
    void readXML(void);
    static inline QString versionAttribute() { return QStringLiteral("version"); }

private:
   QXmlStreamReader jlrXml;
   QFile *jlrFile;

};


#endif // JLRXMLPARSER_H
