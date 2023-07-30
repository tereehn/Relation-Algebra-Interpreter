//
// Created by terez on 27/05/2021.
//

#ifndef SEMESTRAL_CTABLE_H
#define SEMESTRAL_CTABLE_H
#include "CRow.h"
#include <memory>

class CTable {
public:
    /*!
     * Default constructor
     */
    CTable();
    /*!
     * Constructor with name
     * @param name - table's name
     */
    CTable(const std::string & name);
    /*!
     * Default destructor
     */
    ~CTable();
    /*!
     * Number of data in a table
     * @return int count
     */
    unsigned int rowCount(void) const;
    /*!
     * Const name Getter
     * @return string name
     */
    const std::string getName() const;
    /*!
     * Name Setter
     * @return string name
     */
    void setName(const std::string & newName);
    /*!
     * Table's header Getter
     * @return std::vector<std::string> & header
     */
    std::vector < std::string > & getHeader();
    const std::vector < std::shared_ptr < CRow >> getData() const;
    /*!
     * Checks for duplicates
     * @return bool true is row is already present, false otherwise
     */
    bool isRowThere(const CRow & other) const;
    CRow & operator[](unsigned int row) const;
    friend std::ostream & operator << (std::ostream & os, const CTable & input);
    /*!
     * Pushes new row into the vector of rows
     * @param newRow - row to be added
     */
    void pushData(std::shared_ptr < CRow > newRow);
    /*!
     * Sets width of each column according to the longest item
     */
    void setWidth();
    /*!
     * Check if table is empty
     * @return true if empty
     */
    bool isEmpty() const;
private:
    std::string tableName;
    std::vector < std::string > tableHeader;
    std::vector < std::shared_ptr < CRow >> rows;
    std::vector < size_t > widths; /// contains the size of columns largest attribute

    struct rowType {
        std::string left;
        std::string intersect;
        std::string right;
    };

    struct lines {
        std::string horizontal;
        std::string vertical;
        rowType top;
        rowType middle;
        rowType bottom;
    };

    lines style = {"-", "|", {"+", "+", "+"}, {"+", "+", "+"}, {"+", "+", "+"}};
    const std::string SPACE_CHARACTER = " ";
    unsigned int padding = 2;
    std::string getLine(rowType rowType) const;
    std::string getRows(std::vector < std::shared_ptr < CRow >> rows) const;
    std::string getHeaders(std::vector < std::string > tableHeader) const;
};

std::string operator * (const std::string & other, int repeats);
#endif //SEMESTRAL_CTABLE_H