cmake_minimum_required(VERSION 3.17)
project(semestral)

set(CMAKE_CXX_STANDARD 17)

include_directories(ehnovter/src)

add_executable(semestral
        ehnovter/src/CInterface.h
        ehnovter/src/CInterface.cpp
        ehnovter/src/CRow.cpp
        ehnovter/src/CRow.h
        ehnovter/src/CTable.cpp
        ehnovter/src/CTable.h
        ehnovter/src/CData.cpp
        ehnovter/src/CData.h
        ehnovter/src/CDataSQL.cpp
        ehnovter/src/CDataSQL.h
        ehnovter/src/CDataCSV.cpp
        ehnovter/src/CDataCSV.h
        ehnovter/src/main.cpp
        ehnovter/src/CQueryHandler.h
        ehnovter/src/CQueryHandler.cpp
        ehnovter/src/CSyntaxKind.h ehnovter/src/CTokenizer.cpp ehnovter/src/CTokenizer.h ehnovter/src/CSyntaxToken.cpp ehnovter/src/CSyntaxToken.h ehnovter/src/CExpression.cpp ehnovter/src/CExpression.h ehnovter/src/CTableExpression.cpp ehnovter/src/CTableExpression.h ehnovter/src/CProjectExpression.cpp ehnovter/src/CProjectExpression.h ehnovter/src/CBinaryExpression.cpp ehnovter/src/CBinaryExpression.h ehnovter/src/CJoin.cpp ehnovter/src/CJoin.h ehnovter/src/CJoinExpression.cpp ehnovter/src/CJoinExpression.h ehnovter/src/CJoinOnExpression.cpp ehnovter/src/CJoinOnExpression.h ehnovter/src/CSetExpression.cpp ehnovter/src/CSetExpression.h ehnovter/src/CIntersectExpression.cpp ehnovter/src/CIntersectExpression.h ehnovter/src/CUnionExpression.cpp ehnovter/src/CUnionExpression.h ehnovter/src/CDiffExpression.cpp ehnovter/src/CDiffExpression.h ehnovter/src/CCartesianExpression.cpp ehnovter/src/CCartesianExpression.h ehnovter/src/CSelectExpression.cpp ehnovter/src/CSelectExpression.h ehnovter/src/CExceptions/ErrorTreeNodeException.h ehnovter/src/CExceptions/ErrorLoadingData.h)
