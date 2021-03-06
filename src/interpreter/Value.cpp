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
#include "Value.hpp"

Value::Value(int value) {
    this->valueNumber = true;
    this->numberValue = std::move(value);
}

Value::Value(float value) {
    this->valueFloat = true;
    this->floatValue = std::move(value);
}

Value::Value(std::string value) {
    this->valueString = true;
    this->stringValue = std::move(value);
}

Value::Value(bool value) {
    this->valueBool = true;
    this->boolValue = value;
}

Value::Value(std::vector<Value> value) {
    this->valueList = true;
    this->listValue = std::move(value);
}

Value::Value(FunctionStatement* value) {
    this->valueFun = true;
    this->funValue = std::move(value);
}

Value::Value() {
    this->valueNull = true;
}

void Value::printValue() {
    if (this->valueNumber) {
        std::cout << this->numberValue;

        return;
    }


    if (this->valueFloat) {
        std::cout << this->floatValue;

        return;
    }

    if (this->valueString) {
        std::cout << this->stringValue;

        return;
    }

    if (this->valueBool) {
        this->boolValue ? std::cout << "true" << std::endl : std::cout << "false";

        return;
    }

    if (this->valueNull)
        std::cout << "null";

    if (this->valueList) {
        std::cout << "[ ";

        for (std::vector<Value>::iterator a = listValue.begin(); a != listValue.end(); a ++) {
            if ((a + 1) == listValue.end())
                std::cout << a->toString();
            else
                std::cout << a->toString() << ", ";
        }

        std::cout << " ]" << std::endl;
    }

    if (this->valueFun)
        std::cout << "FunctionStatement";
}

void Value::printLineValue() {
    if (this->valueNumber) {
        std::cout << this->numberValue << std::endl;

        return;
    }

    if (this->valueFloat) {
        std::cout << this->floatValue << std::endl;

        return;
    }

    if (this->valueString) {
        std::cout << this->stringValue << std::endl;

        return;
    }

    if (this->valueBool) {
        this->boolValue ? std::cout << "true" << std::endl : std::cout << "false" << std::endl;

        return;
    }

    if (this->valueNull)
        std::cout << "null" << std::endl;

    if (this->valueList) {
        std::cout << "[ ";

        for (std::vector<Value>::iterator a = listValue.begin(); a != listValue.end(); a ++) {
            if ((a + 1) == listValue.end())
                std::cout << a->toString();
            else
                std::cout << a->toString() << ", ";
        }

        std::cout << " ]" << std::endl;
    }

    if (this->valueFun)
        std::cout << "FunctionStatement" << std::endl;
}

std::string Value::toString() {
    if (this->valueNumber) return std::to_string(this->numberValue);
    if (this->valueFloat)  return std::to_string(this->floatValue);
    if (this->valueString) return this->stringValue;
    if (this->valueBool)   return (this->boolValue) ? "true" : "false";
    if (this->valueNull)   return "null";
    if (this->valueFun)    return "FunctionStatement";

    if (this->valueList) {
        std::stringstream data;

        data << "[ ";

        for (std::vector<Value>::iterator a = this->listValue.begin(); a != this->listValue.end(); a ++) {
            if ((a + 1) == this->listValue.end())
                data << a->toString();
            else
                data << a->toString() << ", ";
        }

        data << " ]";

        return data.str();
    }

    throw std::runtime_error("interpret error: cannot to string.");
}

Value backValueWithToken(Token token) {
    if (token.type == TOKEN_VALUE_INT)    return Value(std::stoi(token.literal));
    if (token.type == TOKEN_VALUE_FLOAT)  return Value(std::stof(token.literal));
    if (token.type == TOKEN_VALUE_STRING) return Value(token.literal);
    if (token.type == TOKEN_TRUE)         return Value(true);
    if (token.type == TOKEN_FALSE)        return Value(false);
    if (token.type == TOKEN_NULL)         return Value();

    throw std::runtime_error("type error: unknow literal token decode to value '" + token.literal + "'.");
}

Value backValueWithNullTyped(std::string literal) {
    if (literal == TOKEN_NULL || literal == TOKEN_ANY) return Value();
    if (literal == TOKEN_INT)                          return Value(0);
    if (literal == TOKEN_FLOAT)                        return Value((float) 0);
    if (literal == TOKEN_BOOLEAN)                      return Value(false);
    if (literal == TOKEN_STRING)                       return Value(std::string(""));

    if (literal == TOKEN_LIST) {
        std::vector<Value> a = std::vector<Value>();

        return Value(a);
    }

    throw std::runtime_error("type error: unknown literal with Post-initialized variable.");
}

Value Value::operator + (const Value& a) {
    if (this->valueNumber) {
        if (a.valueNumber) return Value(this->numberValue + a.numberValue);
        if (a.valueFloat)  return Value(this->numberValue + a.floatValue);
    }

    if (this->valueFloat) {
        if (a.valueNumber) return Value(this->floatValue + a.numberValue);
        if (a.valueFloat)  return Value(this->floatValue + a.floatValue);
    }

    if (this->valueString && a.valueString)
        return Value(this->stringValue + a.stringValue);

    throw std::runtime_error("type error: Operands '+' must be two numbers and floats or two strings.");
}

Value Value::operator - (const Value& a) {
    if (this->valueNumber) {
        if (a.valueNumber) return Value(this->numberValue - a.numberValue);
        if (a.valueFloat)  return Value(this->numberValue - a.floatValue);
    }

    if (this->valueFloat) {
        if (a.valueNumber) return Value(this->floatValue - a.numberValue);
        if (a.valueFloat)  return Value(this->floatValue - a.floatValue);
    }

    throw std::runtime_error("type error: Operands '-' must be two numbers or two floats.");
}

Value Value::operator * (const Value& a) {
    if (this->valueNumber) {
        if (a.valueNumber) return Value(this->numberValue * a.numberValue);
        if (a.valueFloat)  return Value(this->numberValue * a.floatValue);
    }

    if (this->valueFloat) {
        if (a.valueNumber) return Value(this->floatValue * a.numberValue);
        if (a.valueFloat)  return Value(this->floatValue * a.floatValue);
    }

    throw std::runtime_error("type error: Operands '*' must be two numbers or two floats.");
}

Value Value::operator / (const Value& a) {
    if (this->valueNumber) {
        if (a.valueNumber) return Value(this->numberValue / a.numberValue);
        if (a.valueFloat)  return Value(this->numberValue / a.floatValue);
    }

    if (this->valueFloat) {
        if (a.valueNumber) return Value(this->floatValue / a.numberValue);
        if (a.valueFloat)  return Value(this->floatValue / a.floatValue);
    }

    throw std::runtime_error("type error: Operands '/' must be two numbers or two floats.");
}

Value Value::operator % (const Value& a) {
    if (this->valueNumber && a.valueNumber) {
        int x = this->numberValue;
        int y = a.numberValue;

        float z = x % y;

        return Value(z);
    }

    throw std::runtime_error("type error: Operands '%' must be two numbers.");
}

Value Value::operator > (const Value& a) {
    if (this->valueNumber) {
        if (a.valueNumber) return Value(this->numberValue > a.numberValue);
        if (a.valueFloat)  return Value(this->numberValue > a.floatValue);
    }

    if (this->valueFloat) {
        if (a.valueNumber) return Value(this->floatValue > a.numberValue);
        if (a.valueFloat)  return Value(this->floatValue > a.floatValue);
    }

    throw std::runtime_error("type error: Operands '>' must be two numbers or two floats.");
}

Value Value::operator < (const Value& a) {
    if (this->valueNumber) {
        if (a.valueNumber) return Value(this->numberValue < a.numberValue);
        if (a.valueFloat)  return Value(this->numberValue < a.floatValue);
    }

    if (this->valueFloat) {
        if (a.valueNumber) return Value(this->floatValue < a.numberValue);
        if (a.valueFloat)  return Value(this->floatValue < a.floatValue);
    }

    throw std::runtime_error("type error: Operands '<' must be two numbers or two floats.");
}

Value Value::operator >= (const Value& a) {
    if (this->valueNumber) {
        if (a.valueNumber) return Value(this->numberValue >= a.numberValue);
        if (a.valueFloat)  return Value(this->numberValue >= a.floatValue);
    }

    if (this->valueFloat) {
        if (a.valueNumber) return Value(this->floatValue >= a.numberValue);
        if (a.valueFloat)  return Value(this->floatValue >= a.floatValue);
    }

    throw std::runtime_error("type error: Operands '>=' must be two numbers or two floats.");
}

Value Value::operator <= (const Value& a) {
    if (this->valueNumber) {
        if (a.valueNumber) return Value(this->numberValue <= a.numberValue);
        if (a.valueFloat)  return Value(this->numberValue <= a.floatValue);
    }

    if (this->valueFloat) {
        if (a.valueNumber) return Value(this->floatValue <= a.numberValue);
        if (a.valueFloat)  return Value(this->floatValue <= a.floatValue);
    }

    throw std::runtime_error("type error: Operands '<=' must be two numbers or two floats.");
}

Value Value::operator != (const Value& a) {
    if (this->valueNull) {
        if (a.valueNull)   return Value(false);
        if (a.valueNumber) return Value(a.numberValue != 0);
        if (a.valueFloat)  return Value(a.floatValue != 0);
        if (a.valueString) return Value(a.stringValue != "");
        if (a.valueBool)   return Value(true);
    }

    if (this->valueNumber) {
        if (a.valueNull)   return Value(a.numberValue != 0);
        if (a.valueNumber) return Value(this->numberValue != a.numberValue);
        if (a.valueFloat)  return Value(this->numberValue != a.floatValue);

        if (a.valueBool) {
            if (a.boolValue)
                return Value(this->numberValue <= 1);
            else
                return Value(this->numberValue >= 0);
        }

        if (a.valueString)
            throw std::runtime_error("type error: cannot comparison number with string.");
    }

    if (this->valueString) {
        if (a.valueNull)   return Value(this->stringValue != "");
        if (a.valueString) return Value(this->stringValue != a.stringValue);

        throw std::runtime_error("type error: string cannot comparison not null and string.");
    }

    if (this->valueFloat) {
        if (a.valueFloat) return Value(this->floatValue != a.floatValue);

        throw std::runtime_error("type error: cannot use '!=' operator without two float.");
    }

    if (this->valueBool) {
        if (a.valueBool) return Value(this->boolValue != a.boolValue);

        if (a.valueNumber) {
            if (this->boolValue)
                return Value(a.numberValue >= 1);
            else
                return Value(a.numberValue <= 0);
        }

        if (a.valueFloat) {
            if (this->boolValue)
                return Value(a.floatValue >= 1);
            else
                return Value(a.floatValue <= 0);
        }

        throw std::runtime_error("type error: bool cannot comparison not bool and number or float.");
    }

    return Value();
}

Value Value::operator == (const Value& a) {
    if (this->valueNull) {
        if (a.valueNull)   return Value(true);
        if (a.valueNumber) return Value(a.numberValue == 0);
        if (a.valueFloat)  return Value(a.floatValue == 0);
        if (a.valueString) return Value(a.stringValue == "");
        if (a.valueBool)   return Value(false);
    }

    if (this->valueNumber) {
        if (a.valueNull)   return Value(a.numberValue == 0);
        if (a.valueNumber) return Value(a.numberValue == this->numberValue);
        if (a.valueFloat)  return Value(a.numberValue == this->floatValue);

        if (a.valueBool) {
            if (a.boolValue)
                return Value(this->numberValue >= 1);
            else
                return Value(this->numberValue <= 0);
        }

        if (a.valueString)
            throw std::runtime_error("type error: cannot comparison number with string.");
    }

    if (this->valueFloat) {
        if (a.valueFloat)  return Value(this->floatValue == a.floatValue);
        if (a.valueNumber) return Value((int) this->floatValue == a.numberValue);

        throw std::runtime_error("type error: cannot use '==' operator without two float.");
    }

    if (this->valueString) {
        if (a.valueNull)   return Value(this->stringValue == "");
        if (a.valueString) return Value(this->stringValue == a.stringValue);

        throw std::runtime_error("type error: string cannot comparison not null and string.");
    }

    if (this->valueBool) {
        if (a.valueBool) return Value(this->boolValue == a.boolValue);

        if (a.valueNumber) {
            if (this->boolValue)
                return Value(a.numberValue >= 1);
            else
                return Value(a.numberValue <= 0);
        }

        if (a.valueFloat) {
            if (this->boolValue)
                return Value(a.floatValue >= 1);
            else
                return Value(a.floatValue <= 0);
        }

        throw std::runtime_error("type error: bool cannot comparison not bool and number or floats.");
    }

    return Value();
}

Value Value::operator || (const Value& b) {
    if (this->valueNumber) return Value(this->numberValue >= 1);
    if (this->valueFloat)  return Value(this->floatValue >= 1);
    if (this->valueBool)   return Value(this->boolValue);
    if (this->valueNull)   return Value(false);

    throw std::runtime_error("interpret error: cannot execute logical expression unknown value.");
}

Value Value::operator && (const Value& b) {
    if (this->valueNumber) {
        if (b.valueNumber) return Value(this->numberValue >= 1 && b.numberValue >= 1);
        if (b.valueFloat)  return Value(this->numberValue >= 1 && b.floatValue >= 1);
        if (b.valueBool)   return Value(this->numberValue >= 1 && b.boolValue);
        if (b.valueNull)   return Value(false);

        throw std::runtime_error("interpret error: cannot execute logical expression unknown value.");
    }

    if (this->valueBool) {
        if (b.valueNumber) return Value(this->boolValue && b.numberValue >= 1);
        if (b.valueFloat)  return Value(this->boolValue && b.floatValue >= 1);
        if (b.valueBool)   return Value(this->boolValue && b.boolValue);
        if (b.valueNull)   return Value(this->boolValue == false);

        throw std::runtime_error("interpret error: cannot execute logical expression unknown value.");
    }

    if (this->valueNull) {
        if (b.valueNumber) return Value(b.numberValue <= 0);
        if (b.valueFloat)  return Value(b.floatValue == 0);
        if (b.valueBool)   return Value(b.boolValue == false);
        if (b.valueNull)   return Value(true);

        throw std::runtime_error("interpret error: cannot execute logical expression unknown value.");
    }

    return Value();
}