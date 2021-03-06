/**
 * Meet Programming Language Expression.
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
#ifndef MEET_GET_EXPRESSION_H
#define MEET_GET_EXPRESSION_H

#include "../interpreter/Expression.hpp"
#include "../Token.hpp"

class GetExpression: public Expression {
    public:
        Token name;

        Expression* expression;

        std::string type;

        GetExpression(Token name, Expression* expression, std::string type): name(std::move(name)),
            expression(std::move(expression)), type(std::move(type)) {}

        ~GetExpression() {
            delete &name;
            delete expression;
        }

        std::string defintion() {
            return EXPRESSION_GET;
        }

        std::string toString() {
            return "[ GetExpression: name = " + name.literal + ", expression = " + 
                expression->toString() + ", type = " + type + " ]";
        }
};

#endif