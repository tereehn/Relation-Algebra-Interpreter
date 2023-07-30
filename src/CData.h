//
// Created by terez on 27/05/2021.
//

#ifndef SEMESTRAL_CDATA_H
#define SEMESTRAL_CDATA_H
#include "CTable.h"
#include "CExceptions/ErrorLoadingData.h"
#include <map>

/*!
 * This class is parent class of CSVData and SQLData. Loads data from user's requested location and stores them in form of tables..
 */
class CData {
public:
    const static char delimiter = ',';
    /*!
     * Constructor with name of data location
     * @param load - name of location
     */
    CData(const std::string & load): src(load) {}
    /*!
     * Copy constructor deleted, only one source of data is present
     */
    CData(const CData & src) = delete;
    /*!
     * Assigment constructor deleted
     */
    virtual CData & operator = (const CData & src) = delete;
    /*!
     * Default destructor
     */
    virtual~CData() =default;
    /*!
     * Check if it is possible to get data
     * @return bool - true if data can be loaded, false otherwise
     */
    virtual bool tryLoading() = 0;
    /*!
     * Loads data from the source
     */
    virtual void LoadTables() = 0;
    /*!
     * Saves one table each time
     * @param fileName - name of new table
     * @param tmpTable - shared pointer to that table
     */
    virtual void SaveOne(const std::string & fileName, std::shared_ptr < CTable > & tmpTable) = 0;
    /*!
     * Adds new table
     * @param newTable - new table to be added
     */
    virtual void appendData(const std::string & tableName, std::shared_ptr < CTable > newTable);
    /*!
     * Removes table
     * @param tableName- table to be removed
     */
    virtual void removeData(const std::string & tableName);
    /*!
     * Data Getter
     * @return std::map<std::string,std::shared_ptr<CTable>> & data which program operates on
     */
    virtual const std::map < std::string, std::shared_ptr < CTable >> & getData() const;
    /*!
     * Exports result to csv file
     * @param filename - requested name of new file
     * @param tableToExport
     */
    virtual void writeToCsv(const std::string & filename, std::shared_ptr < CTable > tableToExport) const;
protected:
    std::string src;
    std::map < std::string, std::shared_ptr < CTable >> savedData; /*!< Name of the table and its data */
};

#endif //SEMESTRAL_CDATA_H