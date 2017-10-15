/************************************************************
 * 2016-01-10 14:22:20
 *
 * author:魏永倬
 * tel:15626234799
 * e-mail:jobshionway@qq.com
 *
 * <?xml version="1.0" encoding="utf-8"?>
 * <data>
 * <map>
 *     <filename filename ="field.jpg"></filename>
 *     <size width="1600" height="800"></size>
 * </map>
 * <agent>
 *     <count count ="3"></count>
 *     <number number="1" x="50" y="60" size ="30"></number>
 *     <number number="2" x="200" y="300" size ="30"></number>
 *     <number number="3" x="500" y="500" size ="30"></number>
 * </agent>
 * </data>
****************************************************************/
#ifndef CSCENEXML_H
#define CSCENEXML_H
#include <QXmlStreamReader>
#include <vector>
using namespace std;

class CAgentLocation
{
public:
    int m_number;
    int m_x;
    int m_y;
    int m_size;
public:
    CAgentLocation(int number, int x, int y, int size)
        : m_number(number), m_x(x), m_y(y), m_size(size){}
};

class CSceneXml
{
public:
    CSceneXml();
    ~CSceneXml();

private:
    QXmlStreamReader *m_pReader;

public:
    QString m_strFileName;
    int m_uMapWidth;
    int m_uMapHeight;
    int m_uAgentCount;
    vector<CAgentLocation> m_vLocation;

private:
    bool readXmlFile(const QString &fileName);  //读取xml文件转为成agent信息保存在内存上
    void readData();
    void readMap();
    void readAgent();
    void readFileName();
    void readMapSize();
    void readAgentCount();
    void readAgentNumber();

public:
    void readFile(const QString &fileName); //读取文件获取文件夹路径以获取图片路径
};

#endif // CSCENEXML_H
