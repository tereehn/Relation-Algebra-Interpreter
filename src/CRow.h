//
// Created by terez on 27/05/2021.
//

#ifndef SEMESTRAL_CROW_H
#define SEMESTRAL_CROW_H
#include <string>
#include <vector>

class CRow {
public:
    /*!
     * Default constructor
     */
    CRow() {}
    /*!
     * Constructor that takes vector filled with data
     * @param oneRow - vector of items to be stored
     */
    CRow(std::vector < std::string > & oneRow);
    /*!
     * Default destructor
     */
    ~CRow(void);
    /*!
     * Pushes item into the vector of values
     * @param data - item to be stored
     */
    void pushData(const std::string & data);
    /*!
     * Appends data from another row
     * @param newValues - appends data to current row
     */
    void appendData(const std::vector < std::string > & newValues);
    /*!
     * Number of data in a row
     * @return int count
     */
    unsigned int dataCount(void) const;
    const std::vector < std::string > getValues() const;
    /*!
    * Overloaded [] operator, access item at index
    * @return string - item from column
    */
    const std::string operator[](unsigned int index) const;
    /*!
     * Compare two rows
     * @param another - row to compare with
     * @return bool true if rows are the same, false otherwise.
     */
    bool operator == (const CRow & another) const;
private:
    std::vector < std::string > values;
};

#endif //SEMESTRAL_CROW_H