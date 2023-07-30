//
// Created by terez on 31/05/2021.
//

#ifndef SEMESTRAL_ERRORLOADINGDATA_H
#define SEMESTRAL_ERRORLOADINGDATA_H

/*!  Class that throws error when loading runs into problem. Prints message explaining error. */
class ErrorLoadingDataException: public std::exception {
private: std::string message;
public: explicit ErrorLoadingDataException(std::string mess): message(move(mess)) {}
    const char * what() const noexcept override {
        return message.c_str();
    }
};


#endif //SEMESTRAL_ERRORLOADINGDATA_H
