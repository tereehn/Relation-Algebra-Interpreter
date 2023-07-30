//
// Created by terez on 27/05/2021.
//

#include "CDataSQL.h"

CDataSQL::CDataSQL(const std::string & load, const std:: string & pass) : CData(load),password(pass) {}

CDataSQL::~CDataSQL() {
    PQfinish(conn); /// close connection to database server
}

bool CDataSQL::tryLoading() {
    std::string data = "dbname=" + src + " host=localhost user=postgres password="+password; /// login information
    conn = PQconnectdb(data.c_str());
    if (PQstatus(conn) == CONNECTION_BAD) {
        return false;
    }
    return true;
}

void CDataSQL::LoadTables() {
    std::vector < std::string > tableNames;
    res = PQexec(conn, "SELECT table_name FROM information_schema.tables "
                       "WHERE table_schema = 'public'");
    int rows = PQntuples(res); /// finds number of tables in database

    for (int i = 0; i < rows; i++) {
        std::string tmp = PQgetvalue(res, i, 0); /// store name of tables to tmp vector
        tableNames.push_back(tmp);
    }
    PQclear(res); /// clear SQL query

    for (unsigned int i = 0; i < tableNames.size(); i++) {
        std::shared_ptr < CTable > tmpTable = std::make_shared < CTable > (tableNames[i]);
        SaveOne(tableNames[i], tmpTable);
        savedData.insert(std::make_pair(tableNames[i], tmpTable));
    }
    if (savedData.empty()) {
        throw ErrorLoadingDataException("No data found!");
    }
}

void CDataSQL::SaveOne(const std::string & fileName, std::shared_ptr < CTable > & tmpTable) {

    std::string query = "SELECT * FROM " + fileName; /// SQL query to get all data from table
    res = PQexec(conn, query.c_str());
    int ncols = PQnfields(res);

    for (int i = 0; i < ncols; i++) {
        std::string tmp = PQfname(res, i);
        tmpTable -> getHeader().push_back(tmp);
    }

    int rec_count = PQntuples(res); /// get rows from table and store them to table
    for (int i = 0; i < rec_count; i++) {
        std::shared_ptr < CRow > newRow = std::make_shared < CRow > ();
        tmpTable -> pushData(newRow);
        for (int j = 0; j < (int) tmpTable -> getHeader().size(); j++) {
            std::string tmpLine = PQgetvalue(res, i, j), word;
            newRow -> pushData(tmpLine);
        }
    }
    PQclear(res); /// clear SQL query
}