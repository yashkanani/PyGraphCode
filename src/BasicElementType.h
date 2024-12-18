#ifndef BASICELEMENTTYPE_H
#define BASICELEMENTTYPE_H

enum class BasicElementType {
    UNKNOW,
    WRITE_VARIABLE,
    READ_VARIABLE,
    CONDITIONS,
    OPERATOR,
    CONSTANT_DECIMAL,
    IF_LOOP,
    FOR_LOOP,
    CONSTANT_TEXT,
    USER_DEFINED
};

#endif  // BASICELEMENTTYPE_H