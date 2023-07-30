//
// Created by terez on 27/05/2021.
//

#include "CJoin.h"

CJoin::CJoin(std::shared_ptr < CExpression > left, std::shared_ptr < CExpression > right): CBinaryExpression(left, right) {}

void CJoin::joinTables(std::shared_ptr < CTable > & newTable, std::shared_ptr < CTable > leftTable, std::shared_ptr < CTable > rightTable) const {
    for (unsigned i = 0; i < leftTable -> rowCount(); i++) {
        CRow tmpLeft = ( * (leftTable))[i];
        std::string tmpLeftNum = tmpLeft[leftCol];

        for (unsigned j = 0; j < rightTable -> rowCount(); j++) {
            CRow tmpRight = ( * (rightTable))[j];
            std::string tmpRightNum = tmpRight[rightCol];

            if (tmpRightNum == tmpLeftNum) {
                std::shared_ptr < CRow > newRow = std::make_shared < CRow > (tmpLeft);
                for (unsigned k = 0; k < tmpRight.dataCount(); k++) {
                    if (k == rightCol) continue; /// don't add the same column twice
                    newRow -> pushData(tmpRight[k]);
                }
                newTable -> pushData(newRow);
            }
        }
    }
}