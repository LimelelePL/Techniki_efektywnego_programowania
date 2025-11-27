//
// Created by Dominik on 18.11.2025.
//

#include "Result.h"

Result::Result(ErrorCode c, const std::string &msg) {
    code = c;
    message = msg;

}

ErrorCode Result::getCode() const {
    return code;
}
string Result::getMessage() const {
    return message;
}

Result Result::success() {
    return Result(OK, "");
}

