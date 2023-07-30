//
// Created by terez on 27/05/2021.
//

#include "CInterface.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include "CDataCSV.h"
#include "CDataSQL.h"
#include "CQueryHandler.h"

void CInterface::welcome() const {

    std::string welcome = "RELATION ALGEBRA INTERPRETER";
    std::string load    = "LOAD DATA AND START QUERYING                         >> load        ";
    std::string quit    = "QUIT APPLICATION                                     >> quit       ";
    std::vector < std::string > tmp = {
            welcome,
            load,
            quit
    };
    printMenu(tmp);

}

void CInterface::printMenu(const std::vector < std::string > & lines) const {
    for (auto it = lines.begin(); it != lines.end(); ++it) {
        if (it == lines.begin()) {
            renderText( * it, '-', '+');
        } else {
            renderText( * it, ' ', '+');
        }
    }
    renderText("", '-', '+'); /// print end line
}

void CInterface::printHelp() const {
    std::string option;
    std::string help     = " HELPER ";
    std::string queries  = "SEE POSSIBLE QUERIES                                     >> help         ";
    std::string quit     = "QUIT APPLICATION                                         >> quit         ";
    std::string myTables = "SHOW MY TABLES                                           >> tables       ";
    std::vector < std::string > tmp = {
            help,
            queries,
            quit,
            myTables
    };
    printMenu(tmp);

}

void CInterface::renderText(const std::string & text,int delimiter,int end) const {
    int half = (WIDTH - text.length()) / 2;
    std::cout <<  std::string(1, end) + std::string(half, delimiter) + text+
    std::string(WIDTH - text.length() - half, delimiter) +
    std::string(1, end) << std::endl;
}

void CInterface::write(const std::string & text) const {
    renderText(text, '_', '+');
}

void CInterface::possibleQueries() const {
    std::string title       = "SYNTAX";
    std::string projection  = "PROJECTION                                  >> {QUERY...} [col1,col2...coln-1,coln]                                           ";
    std::string rename      = "RENAME                                      >> {QUERY...} [col1->NEWNAME1,col2->NEWNAME2...coln-1->NEWNAMEn-1,coln->NEWNAMEn] ";
    std::string naturalJoin = "NATURAL JOIN                                >> { TABLE1 * TABLE2 * ...TABLEn}                                                 ";
    std::string joinOn      = "JOIN ON                                     >> { TABLE1 [TABLE1.col1=TABLE2.col2] TABLE2 }                                    ";
    std::string selection   = "SELECTION                                   >> { TABLE(col op value) }                                                        ";
    std::string unionOp     = "UNION                                       >> { RELATION1 U RELATION2 U ...RELATIONn}                                        ";
    std::string intersect   = "INTERSECT                                   >> { RELATION1 I RELATION2 I ...RELATIONn}                                        ";
    std::string diff        = "DIFFERENCE                                  >> { RELATION1 \\ RELATION2 \\ ...RELATION}                                         ";
    std::string cartesian   = "CARTESIAN PRODUCT                           >> { RELATION1 X RELATION2 X ...RELATIONn}                                        ";

    std::vector < std::string > tmp = {
            title,
            projection,
            rename,
            naturalJoin,
            joinOn,
            selection,
            unionOp,
            intersect,
            diff,
            cartesian
    };
    printMenu(tmp);
}

bool CInterface::loadData() {

    welcome();
    std::string option, loadFrom;

    while (!std::cin.eof()) {
        if (!(getline(std::cin >> std::ws, option))) {
            return false;
        }
        if (option == "load") {
            write(" Load CSV files or connect to PostgreSQL database ");
            break;
        } else if (option == "quit") {
            if (quit()) {
                return false;
            }
        } else {
            std::cout << WRONG_INPUT << std::endl;
        }
    }

    while (!std::cin.eof()) {
        if (!(getline(std::cin >> std::ws, loadFrom))) {
            return false;
        } else if (loadFrom == "sql") {
            write(" WRITE NAME OF DATABASE AND PASSWORD ");
            std::string databaseName, password;
            if (!(std::cin >> databaseName >> password)) {
                std::cout << EOF_ << std::endl;
            }
            data = (std::make_unique < CDataSQL > (databaseName, password));
            break;

        } else if (loadFrom == "csv") {
            write(" WRITE NAME OF DIRECTORY ");
            std::string CSV;
            if (!(std::cin >> CSV)) {
                std::cout << EOF_ << std::endl;
            }
            data = (std::make_unique < CDataCSV > (CSV));
            break;

        } else {
            std::cout << "Choose between csv and sql!" << std::endl;
        }
    }

    if (!data -> tryLoading()) {
        std::cout << "No data retrieved!" << std::endl;
    } else {
        try {
            data -> LoadTables(); /*!< Data can be loaded, store them into tables*/
        } catch (ErrorLoadingDataException
                 const & ex) {
            std::cout << ex.what() << std::endl;
            return true;
        }
        getQuery(); /*!< Start querying */
    }
    return true;
}

void CInterface::getQuery() {
    std::string writeQuery = " WRITE QUERY ";
    write(writeQuery);

    std::cin.ignore();
    std::string line = "";

    while (!std::cin.eof()) {
        printHelp();
        if (!(getline(std::cin, line))) {
            std::cout << EOF_ << std::endl;
            break;
        }
        if (line == "quit") {
            if (quit()) {
                break;
            }
        } else if (line == "help") {
            possibleQueries();
        } else if (line == "tables") {
            showTables();
        } else {
            if (!processQuery(line)) {
                std::cout << WRONG_INPUT << std::endl;
            }
        }
    }

}

void CInterface::showTables() const {
    write("MY TABLES");
    for (auto & it: data -> getData()) {
        std::cout << it.first << std::endl;
    }
    std::string option;
    std::string tableOptions = "TABLE OPTIONS";
    std::string show         = "SHOW ONE?                                         >> name         ";
    std::string deleteTable  = "DELETE TABLE?                                     >> delete       ";
    std::string back         = "GO BACK?                                          >> back         ";

    std::vector < std::string > tmp = {
            tableOptions,
            show,
            deleteTable,
            back
    };

    while (!std::cin.eof()) {
        printMenu(tmp);
        if (!getline(std::cin >> std::ws, option)) {
            std::cout << EOF_ << std::endl;
        } else if (option == "delete") {
            write("WRITE TABLE TO BE DELETED!");
            std::string tableName;
            if (!(std::cin >> tableName)) {
                std::cout << EOF_ << std::endl;
            }
            std::cin.ignore();
            auto it = data->getData().find(tableName); /// check if name is already used
            if (it == data->getData().end()){
                write("TABLE DOES NOT EXIST!");
            }else {
                data -> removeData(tableName);
                write("TABLE DELETED!");
            }
        } else if (option == "back") {
            break;
        } else {
            auto it = data -> getData().find(option);
            if (it != data -> getData().end()) {
                CTable result = * it -> second;
                result.setWidth();
                std::cout << result;
            } else {
                std::cout << WRONG_INPUT << std::endl;
            }

        }
    }
}

bool CInterface::processQuery(std::string & line) {

    CQueryHandler oneQuery(line, data -> getData()); /// check for correct syntax
    if (!oneQuery.checkParenthesis(line) || !oneQuery.startParsing() || !oneQuery.buildTree()) return false;

    std::string option;
    std::string title      = "CORRECT QUERY WRITTEN, WHAT NOW?";
    std::string save       = "SAVE RESULT?                                       >> save         ";
    std::string exportData = "EXPORT RESULT TO CSV FILE?                         >> export       ";
    std::string show       = "SHOW RESULT                                        >> show         ";
    std::string sql        = "SHOW SQL EXPRESSION                                >> sql          ";
    std::string quitt      = "GO BACK?                                           >> back         ";

    std::vector < std::string > tmp = {
            title,
            save,
            exportData,
            show,
            sql,
            quitt
    };

    while (!std::cin.eof()) {
        printMenu(tmp);
        if (!getline(std::cin, option)) {
            std::cout << EOF_ << std::endl;
            return false;
        }
        if (option == "save") {
            write("NAME TABLE!");
            std::string newName;
            while ((std::cin >> newName)) {
                auto it = data->getData().find(newName); /// check if name is already used
                if (it != data->getData().end()){
                    write("NAME ALREADY USED! CHOOSE DIFFERENT:");
                }else {
                    break;
                }
            }
            if (std::cin.eof()) std::cout << EOF_ << std::endl;
            std::cin.ignore();
            data -> appendData(newName, oneQuery.getResult());
            write("TABLE WAS SAVED!");
        } else if (option == "export") {
            write("NAME THE CVS FILE!");
            std::string newName;
            if (!(std::cin >> newName)) {
                std::cout << EOF_ << std::endl;
            }
            std::cin.ignore();
            try {
                data -> writeToCsv(newName, oneQuery.getResult());
            } catch (ErrorLoadingDataException const & ex) {
                std::cout << ex.what() << std::endl;
                return false;
            }
            write("FILE WAS EXPORTED!");
        } else if (option == "show") {
            CTable result = * oneQuery.getResult();
            if (!result.isEmpty()) {
                result.setWidth();
                std::cout << result;
            } else {
                write("NO DATA RETURNED!");
            }
        } else if (option == "sql") {
            std::string result = oneQuery.getSQL();
            translate(result);
        } else if (option == "back") {
            return true;
        } else
            std::cout << WRONG_INPUT << std::endl;
    }

    return true;
}

void CInterface::translate(const std::string & sql) const {
    unsigned int maxSize = 0;
    std::vector < std::string > tmp;
    std::stringstream ss(sql);
    std::string line;
    while (getline(ss, line)) {
        if (line.size() >= maxSize) {
            maxSize = line.size();
        }
        tmp.push_back(line);
    }
    /// print table that contains SQL translation
    std::cout << '+' << std::setfill('-') << std::setw(maxSize * 2 - 2) << '-' << '+' << std::endl;
    for (unsigned int i = 0; i < tmp.size(); i++) {
        std::cout << '|' << std::left << std::setfill(' ') << std::setw(maxSize * 2 - 2) << tmp[i] << '|' << std::endl;
    }
    std::cout << '+' << std::setfill('-') << std::setw(maxSize * 2 - 2) << '-' << '+' << std::endl;
}

bool CInterface::quit() const {

    write("Quit application? yes/no"); /// make sure if user really wants to quit
    std::string option;
    while (!std::cin.eof()) {
        getline(std::cin, option);

        if (option == "yes")
            return true;
        else if (option == "no")
            return false;
        else
            std::cout << WRONG_INPUT << std::endl;
    }
    return false;
}