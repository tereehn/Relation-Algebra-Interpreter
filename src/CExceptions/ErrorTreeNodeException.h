//
// Created by terez on 31/05/2021.
//

#ifndef SEMESTRAL_ERRORTREENODEEXCEPTION_H
#define SEMESTRAL_ERRORTREENODEEXCEPTION_H

/*!  Shows the error message and explanation, when tree cannot be built successfully. */
class ErrorTreeNodeException: public std::exception {
private:
    std::string message; /// problem with construction
public:
    explicit ErrorTreeNodeException(std::string mess) : message(move(mess)) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};


#endif //SEMESTRAL_ERRORTREENODEEXCEPTION_H
