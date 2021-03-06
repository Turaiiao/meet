/**
 * Meet Programming Language Statement.
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
#ifndef MEET_STATEMENT_H
#define MEET_STATEMENT_H

#include <iostream>

#define STATEMENT_EXPRESSION "STATEMENT_EXPRESSION"
#define STATEMENT_VAR        "STATEMENT_VAR"
#define STATEMENT_PRINTLN    "STATEMENT_PRINTLN"
#define STATEMENT_BLOCK      "STATEMENT_BLOCK"
#define STATEMENT_FOR        "STATEMENT_FOR"
#define STATEMENT_BREAK      "STATEMENT_BREAK"
#define STATEMENT_CONTINUE   "STATEMENT_CONTINUE"
#define STATEMENT_IF         "STATEMENT_IF"
#define STATEMENT_WHILE      "STATEMENT_WHILE"
#define STATEMENT_FUN        "STATEMENT_FUN"
#define STATEMENT_RETURN     "STATEMENT_RETURN"

class Statement {
    public:
        virtual ~Statement() = default;
        
        virtual std::string defintion() = 0;

        virtual std::string toString() = 0;
};

#endif