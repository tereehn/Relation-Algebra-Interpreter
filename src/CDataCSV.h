//
// Created by terez on 27/05/2021.
//

#ifndef SEMESTRAL_DATACSV_H
#define SEMESTRAL_DATACSV_H
#include "CData.h"

/*!
 * Subclass of CData. Loads data from directory which contains csv files.*/
class CDataCSV: public CData {
public:
    /*!
     * Constructor with name of the directory
     * @param load
     */
    CDataCSV(const std::string & load);
    /*!
     * Overrides tryLoading method, checks directory, permission...etc
     * @return bool if directory opening was successfull, false if otherwise
     */
    bool tryLoading() override;
    /*!
     * Overrides loadTables method, uses CSVState class to check for quotes.
     */
    void LoadTables() override;
    /*!
     * Overrides saveOne method, split item by delimiter.
     * @param fileName - name of new table
     * @param tmpTable - shared pointer to that table
     */
    void SaveOne(const std::string & fileName, std::shared_ptr < CTable > & tmpTable) override;
private:
    /*!
     * Enum class which specifies type of char that is being processed.
     */
    enum class CSVState {
        UnquotedField,
        QuotedField,
        QuotedQuote
    };
    /// files from directory, from which data are loaded
    std::vector < std::pair < std::string, std::string >> filesToOpen;
};

#endif //SEMESTRAL_DATACSV_H