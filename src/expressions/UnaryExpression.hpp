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
#ifndef MEET_UNARY_EXPRESSION_H
#define MEET_UNARY_EXPRESSION_H

#include "../Expression.hpp"

class UnaryExpression: public Expression {
    private:
        Token token;

        Expression* expression;
    public:
        UnaryExpression(Token token, Expression* expression): token(std::move(token)), 
            expression(std::move(expression)) {}

        ~UnaryExpression() {
            delete &token;
            delete expression;
        }

        std::string classType() {
            return UNARY_EXPRESSION;
        }

        std::string toString() {
            return "[ UnaryExpression: token = " + token.getTokenLiteral() + ", expr = " + 
                expression->toString() + " ]";
        }
};

#endif