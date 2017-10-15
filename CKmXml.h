/***********************************************************
 * 2016-01-8 14:20:02
 *
 * author:魏永倬
 * tel:15626234799
 * e-mail:jobshionway@qq.com
 *
 * xml文件格式
 * <?xml version="1.0" encoding="utf-8"?>
 * <kmData>
 * <size>
 *    <row m = "2"></row>
 *     <column n = "1"></column>
 * </size>
 * <roleName>
    <column number = "0" value = "temperature"></column>
 * </roleName>
 * <vectorL>
 *     <column number = "0" value = "1"></column>
 * </vectorL>
 * <vectorBA>
 *     <column number = "0" value = "1"></column>
 *     <column number = "1" value = "2"></column>
 * </vectorBA>
 * <matrixQ>
 *     <row number="0">
 *         <column number = "0" value = "0.1"></column>
 *         <column number = "1" value = "0.2"></column>
 *     </row>
 * </matrixQ>
 * </kmData>
*************************************************************/
#ifndef CKMXML_H
#define CKMXML_H
#include "CKm.h"
#include <QXmlStreamReader>

class CKmXml : public CKm
{
public:
    CKmXml(const int m, const int n);
    ~CKmXml();
public:
    QXmlStreamReader *m_pReader;

public:
    void readFile(const QString &fileName);

private:

    bool readXmlFile(const QString &fileName);

    void readKmData();

    void readSize();
    void readRoleName();
    void readVectorL();
    void readVectorLa();
    void readMatrixQ();

    void readM();
    void readN();
    void readRoleNameColumn();
    void readVectorLColumn();
    void readVectorLaColumn();
    void readMatrixQRow();
    void readMatrixQColumn(const int rowNumber);
};

#endif // CKMXML_H
