/**
 * Meet Programming Language Values.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Copyright (c) 2019 Turaiiao
 * Email: 1171840237@qq.com
 * Github: https://github.com/turaiiao
 */
#ifndef MEET_VALUE_H
#define MEET_VALUE_H

#include <iostream>
#include <map>
#include <sstream>
#include <vector>

#include "../Token.hpp"

#include "../statements/FunctionStatement.hpp"

class Value {
    public:
        explicit Value(int value);
        explicit Value(float value);
        explicit Value(std::string value);
        explicit Value(bool value);
        explicit Value(std::vector<Value> value);
        explicit Value(FunctionStatement* value);

        Value(); // Null value.

        Value operator + (const Value& a);
        Value operator - (const Value& b);
        Value operator * (const Value& b);
        Value operator / (const Value& b);
        Value operator % (const Value& b);
        Value operator > (const Value& b);
        Value operator < (const Value& b);
        Value operator >= (const Value& b);
        Value operator <= (const Value& b);
        Value operator != (const Value& b);
        Value operator == (const Value& b);
        Value operator || (const Value& b);
        Value operator && (const Value& b);

        bool valueNumber = false;
        bool valueFloat = false;
        bool valueString = false;
        bool valueBool = false;
        bool valueNull = false;
        bool valueList = false;
        bool valueFun = false;

        int numberValue = 0;
        float floatValue = 0;
        bool boolValue = false;
        std::string stringValue = std::string();

        std::string fixedListValue;
        std::vector<Value> listValue = std::vector<Value>();

        FunctionStatement* funValue = nullptr;

        bool varAny = false;
        bool varNumber = false;
        bool varFloat = false;
        bool varString = false;
        bool varBoolean = false;
        bool varNull = false;
        bool varList = false;

        void printValue();
        void printLineValue();

        std::string toString();
};

Value backValueWithToken(Token token);
Value backValueWithNullTyped(std::string literal);

#endif