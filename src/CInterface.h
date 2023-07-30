//
// Created by terez on 27/05/2021.
//

#ifndef SEMESTRAL_CINTERFACE_H
#define SEMESTRAL_CINTERFACE_H
#include <string>
#include <memory>
#include "CData.h"

class CInterface {
public:
    /*!
     * Shows name of query and initial instructions
     */
    void welcome() const;
    /*!
     * Navigates user through the application
     */
    void printHelp() const;
    /*!
     * Prints menu according to possible operations
     * @param lines - to be printed
     */
    void printMenu(const std::vector < std::string > & lines) const;
    /*!
     * Shows allowed syntax of queries
     */
    void possibleQueries() const;
    /*!
     * Renders lines that are to be printed to console window
     * @param text - to be written
     * @param delimiter
     * @param end
     */
     void renderText(const std::string & text,int delimiter,int end) const;
    /*!
     * Loads data from user's location choice
     */
    bool loadData();
    /*!
     * Processes query from user, saves result if wanted, exports or prints to the console window...
     * @return returns true if query was processed successfully
     */
    bool processQuery(std::string & line);
    /*!
     * Gets query from user
     */
    void getQuery();
    /*!
     * Translates to corresponding SQL query
     */
    void translate(const std::string & sql) const;
    /*!
     * Method handles quit request
     * @return returns true if users wants to quit app, false otherwise
     */
    bool quit() const;
    /*!
     * Writes line of text to console window
     * @param text - to be written
     */
    void write(const std::string & text) const;
    /*!
     * Shows user's tables
     */
    void showTables() const;
private:
    std::unique_ptr < CData > data; /// stores data from location into tables
    const int WIDTH = 160; /// width of lines being printed to console
    const std::string WRONG_INPUT = "Wrong input!"; /// shows warning
    const std::string EOF_ = "EOF!"; /// shows eof message
};

#endif //SEMESTRAL_CINTERFACE_H