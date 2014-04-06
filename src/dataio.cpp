#include "dataio.h"

DataIO::DataIO()
{
}

DataIO::DataIO(DataIO &p_dioRef)
{
}

DataIO &DataIO::operator=(DataIO &p_dioRef)
{
    return *this;
}

DataIO &DataIO::getInstance()
{
    static DataIO dioInstance;
    return dioInstance;
}

DataIO &DataIO::operator<<(const CellPattern &p_cpPattern)
{
    try{
        std::ofstream ofOut(PATH, std::ios_base::binary);
        std::ifstream ifIn(PATH, std::ios_base::binary);
        ifIn.seekg(0, ifIn.end);
        if( ! ifIn.tellg()){
            ofOut.write(p_cpPattern.getName().c_str(), p_cpPattern.getName().size());
            ofOut.put('\n');
            long lIndexForNextPos = ofOut.tellp();
            ofOut.seekp(INDEX_SIZE, ofOut.cur);
            for(auto aRows : p_cpPattern){
                for(Cell cCell : aRows){
                    ofOut.put(cCell.getState());
                }
            }
            long lNextWritePos = ofOut.tellp();
            ofOut.seekp(lIndexForNextPos, ofOut.beg);
            for(int i = 0; i < INDEX_SIZE; i++){
                ofOut.put(static_cast<char>(lNextWritePos >> i*8));
                }
            ifIn.seekg(0); //DEBUG
            while(!ifIn.eof())std::cout<<ifIn.get()<<std::endl;
        }
        else{


        }

    }
    catch(std::ios_base::failure fail){

    }
    return *this;
}

CellPattern DataIO::getPattern(const char *p_sName)
{
    try{
        /*
    m_fsstream.open(PATH, std::ios_base::in);
    QString sData = "";
    while( ! m_fsstream.eof()) sData += m_fsstream.get();
    QRegExp qrePattern(QString("<p>.*<n>") + QString(p_sName) + QString("<\/n>.*<\/p>"));
    qrePattern.indexIn(sData);
    if(qrePattern.captureCount() != 1) std::cerr << "More than one Pattern with same name!" << std::endl;
    QRegExp qreRows("<r>\\d*<\/r>");
    qreRows.indexIn(qrePattern.cap(1));
    CellArray caResult;

    for(int iCount = 1; iCount < qreRows.captureCount(); iCount++){
        std::vector<Cell> cvResultRows;
        for(const char *cpPointer = qreRows.cap(iCount).toLocal8Bit().constData(); *cpPointer != '<'; cpPointer++){
            Cell cResultCell;
            cResultCell.setState(static_cast<Globals::State>(*cpPointer));
            cvResultRows.push_back(cResultCell);
        }
        caResult.push_back(cvResultRows);
    }
    return CellPattern (caResult, std::string(p_sName));
    }
    catch(std::ios_base::failure fail){
        m_fsstream.close();
        std::cerr<<"Input Exception"<<std::endl;
    */}
    catch(...){

        std::cerr<<"Unexpected exception"<<std::endl;

    }

}

std::vector<CellPattern> DataIO::getAllCellPatterns()
{

}
