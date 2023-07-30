//
// Created by terez on 27/05/2021.
//

#ifndef SEMESTRAL_CDATASQL_H
#define SEMESTRAL_CDATASQL_H
#include "CData.h"
#include <postgresql/libpq-fe.h>

/*!
 * Subclass of CData. Loads data postgresSQL database.
 */
class CDataSQL : public CData{
public:
    /*!
    * Constructor with name of the database
    * @param load
    */
    CDataSQL(const std::string& load, const std:: string & pass);
    /*!
    * Destructor closes connection
    */
    virtual ~CDataSQL();
    /*!
    * Overrides tryLoading method, tries connecting to database
    * @return bool if connection was successful, false if interrupted
    */
    bool tryLoading() override;
    /*!
    * Overrides loadTables method, uses SQL queries to get tables stored in database.
    */
    void LoadTables() override; // loads data from requested location
    /*!
   * Overrides saveOne method, uses SQL queries to get rows.
   * @param fileName - name of new table
   * @param tmpTable - shared pointer to that table
   */
    void SaveOne(const std::string & fileName, std::shared_ptr<CTable> & tmpTable) override; // saves header of table
private:
    PGconn *conn; /*!< Connection pointer */
    PGresult *res; /*!< SQL query pointer */
    std:: string password; /*!<password to database>*/
};

#endif //SEMESTRAL_CDATASQL_H
