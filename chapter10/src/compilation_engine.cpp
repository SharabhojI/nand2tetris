#include "compilation_engine.h"
#include <iostream>

CompilationEngine::CompilationEngine(std::string input_file, std::string output_file) : 
    tokenizer(input_file), indentLevel(0) {
    this->output_file.open(output_file);
    if (!this->output_file.is_open()) {
        throw std::runtime_error("Unable to open file: " + output_file);
    }
}

void CompilationEngine::writeIndentation() {
    for (int i = 0; i < indentLevel; i++) {
        output_file << "  ";
    }
}

void CompilationEngine::writeXMLTag(const std::string& tag, bool isClosing) {
    writeIndentation();
    output_file << (isClosing ? "</" : "<") << tag << ">" << std::endl;
}

void CompilationEngine::writeToken() {
    writeIndentation();
    switch (tokenizer.tokenType()) {
        case JackTokenizer::KEYWORD:
            output_file << "<keyword> " << tokenizer.keyWord() << " </keyword>" << std::endl;
            break;
        case JackTokenizer::SYMBOL:
            output_file << "<symbol> ";
            // Handle special XML symbols
            char sym = tokenizer.symbol();
            if (sym == '<') output_file << "&lt;";
            else if (sym == '>') output_file << "&gt;";
            else if (sym == '"') output_file << "&quot;";
            else if (sym == '&') output_file << "&amp;";
            else output_file << sym;
            output_file << " </symbol>" << std::endl;
            break;
        case JackTokenizer::IDENTIFIER:
            output_file << "<identifier> " << tokenizer.identifier() << " </identifier>" << std::endl;
            break;
        case JackTokenizer::INT_CONST:
            output_file << "<integerConstant> " << tokenizer.intVal() << " </integerConstant>" << std::endl;
            break;
        case JackTokenizer::STRING_CONST:
            output_file << "<stringConstant> " << tokenizer.stringVal() << " </stringConstant>" << std::endl;
            break;
    }
}

void CompilationEngine::advance() {
    if (tokenizer.hasMoreTokens()) {
        tokenizer.advance();
    }
}

bool CompilationEngine::isOperator(char symbol) {
    return (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || 
            symbol == '&' || symbol == '|' || symbol == '<' || symbol == '>' || symbol == '=');
}

void CompilationEngine::compileClass() {
    advance(); // Get first token
    writeXMLTag("class", false);
    indentLevel++;

    // class name
    if (tokenizer.tokenType() != JackTokenizer::KEYWORD || tokenizer.keyWord() != JackTokenizer::CLASS) {
        throw std::runtime_error("Expected 'class'");
    }
    writeToken();
    advance();

    // class name identifier
    if (tokenizer.tokenType() != JackTokenizer::IDENTIFIER) {
        throw std::runtime_error("Expected class name");
    }
    writeToken();
    advance();

    // {
    if (tokenizer.tokenType() != JackTokenizer::SYMBOL || tokenizer.symbol() != '{') {
        throw std::runtime_error("Expected '{'");
    }
    writeToken();
    advance();

    // class vars
    while (tokenizer.tokenType() == JackTokenizer::KEYWORD && 
           (tokenizer.keyWord() == JackTokenizer::STATIC || 
            tokenizer.keyWord() == JackTokenizer::FIELD)) {
        compileClassVarDec();
    }

    // subroutines
    while (tokenizer.tokenType() == JackTokenizer::KEYWORD && 
           (tokenizer.keyWord() == JackTokenizer::CONSTRUCTOR || 
            tokenizer.keyWord() == JackTokenizer::FUNCTION || 
            tokenizer.keyWord() == JackTokenizer::METHOD)) {
        compileSubroutine();
    }

    // }
    if (tokenizer.tokenType() != JackTokenizer::SYMBOL || tokenizer.symbol() != '}') {
        throw std::runtime_error("Expected '}'");
    }
    writeToken();

    indentLevel--;
    writeXMLTag("class", true);
}

void CompilationEngine::compileClassVarDec() {
    writeXMLTag("classVarDec", false);
    indentLevel++;

    // static/field
    writeToken();
    advance();

    // type
    if ((tokenizer.tokenType() != JackTokenizer::KEYWORD || 
         (tokenizer.keyWord() != JackTokenizer::INT && 
          tokenizer.keyWord() != JackTokenizer::CHAR && 
          tokenizer.keyWord() != JackTokenizer::BOOLEAN)) && 
        tokenizer.tokenType() != JackTokenizer::IDENTIFIER) {
        throw std::runtime_error("Expected type");
    }
    writeToken();
    advance();

    // varName
    if (tokenizer.tokenType() != JackTokenizer::IDENTIFIER) {
        throw std::runtime_error("Expected variable name");
    }
    writeToken();
    advance();

    // (',' varName)*
    while (tokenizer.tokenType() == JackTokenizer::SYMBOL && tokenizer.symbol() == ',') {
        writeToken(); // write ','
        advance();

        if (tokenizer.tokenType() != JackTokenizer::IDENTIFIER) {
            throw std::runtime_error("Expected variable name");
        }
        writeToken();
        advance();
    }

    // ;
    if (tokenizer.tokenType() != JackTokenizer::SYMBOL || tokenizer.symbol() != ';') {
        throw std::runtime_error("Expected ';'");
    }
    writeToken();
    advance();

    indentLevel--;
    writeXMLTag("classVarDec", true);
}

void CompilationEngine::compileSubroutine() {
    writeXMLTag("subroutineDec", false);
    indentLevel++;

    // constructor/function/method
    writeToken();
    advance();

    // return type
    if ((tokenizer.tokenType() != JackTokenizer::KEYWORD || 
         (tokenizer.keyWord() != JackTokenizer::VOID && 
          tokenizer.keyWord() != JackTokenizer::INT && 
          tokenizer.keyWord() != JackTokenizer::CHAR && 
          tokenizer.keyWord() != JackTokenizer::BOOLEAN)) && 
        tokenizer.tokenType() != JackTokenizer::IDENTIFIER) {
        throw std::runtime_error("Expected return type");
    }
    writeToken();
    advance();

    // subroutineName
    if (tokenizer.tokenType() != JackTokenizer::IDENTIFIER) {
        throw std::runtime_error("Expected subroutine name");
    }
    writeToken();
    advance();

    // (
    if (tokenizer.tokenType() != JackTokenizer::SYMBOL || tokenizer.symbol() != '(') {
        throw std::runtime_error("Expected '('");
    }
    writeToken();
    advance();

    compileParameterList();

    // )
    if (tokenizer.tokenType() != JackTokenizer::SYMBOL || tokenizer.symbol() != ')') {
        throw std::runtime_error("Expected ')'");
    }
    writeToken();
    advance();

    compileSubroutineBody();

    indentLevel--;
    writeXMLTag("subroutineDec", true);
}

void CompilationEngine::compileParameterList() {
    writeXMLTag("parameterList", false);
    indentLevel++;

    if (tokenizer.tokenType() != JackTokenizer::SYMBOL || tokenizer.symbol() != ')') {
        // type
        if ((tokenizer.tokenType() != JackTokenizer::KEYWORD || 
             (tokenizer.keyWord() != JackTokenizer::INT && 
              tokenizer.keyWord() != JackTokenizer::CHAR && 
              tokenizer.keyWord() != JackTokenizer::BOOLEAN)) && 
            tokenizer.tokenType() != JackTokenizer::IDENTIFIER) {
            throw std::runtime_error("Expected type");
        }
        writeToken();
        advance();

        // varName
        if (tokenizer.tokenType() != JackTokenizer::IDENTIFIER) {
            throw std::runtime_error("Expected variable name");
        }
        writeToken();
        advance();

        // (',' type varName)*
        while (tokenizer.tokenType() == JackTokenizer::SYMBOL && tokenizer.symbol() == ',') {
            writeToken(); // write ','
            advance();

            // type
            if ((tokenizer.tokenType() != JackTokenizer::KEYWORD || 
                 (tokenizer.keyWord() != JackTokenizer::INT && 
                  tokenizer.keyWord() != JackTokenizer::CHAR && 
                  tokenizer.keyWord() != JackTokenizer::BOOLEAN)) && 
                tokenizer.tokenType() != JackTokenizer::IDENTIFIER) {
                throw std::runtime_error("Expected type");
            }
            writeToken();
            advance();

            // varName
            if (tokenizer.tokenType() != JackTokenizer::IDENTIFIER) {
                throw std::runtime_error("Expected variable name");
            }
            writeToken();
            advance();
        }
    }

    indentLevel--;
    writeXMLTag("parameterList", true);
}

void CompilationEngine::compileSubroutineBody() {
    writeXMLTag("subroutineBody", false);
    indentLevel++;

    // {
    if (tokenizer.tokenType() != JackTokenizer::SYMBOL || tokenizer.symbol() != '{') {
        throw std::runtime_error("Expected '{'");
    }
    writeToken();
    advance();

    // varDec*
    while (tokenizer.tokenType() == JackTokenizer::KEYWORD && tokenizer.keyWord() == JackTokenizer::VAR) {
        compileVarDec();
    }

    compileStatements();

    // }
    if (tokenizer.tokenType() != JackTokenizer::SYMBOL || tokenizer.symbol() != '}') {
        throw std::runtime_error("Expected '}'");
    }
    writeToken();
    advance();

    indentLevel--;
    writeXMLTag("subroutineBody", true);
}

void CompilationEngine::compileVarDec() {
    writeXMLTag("varDec", false);
    indentLevel++;

    // var
    writeToken();
    advance();

    // type
    if ((tokenizer.tokenType() != JackTokenizer::KEYWORD || 
         (tokenizer.keyWord() != JackTokenizer::INT && 
          tokenizer.keyWord() != JackTokenizer::CHAR && 
          tokenizer.keyWord() != JackTokenizer::BOOLEAN)) && 
        tokenizer.tokenType() != JackTokenizer::IDENTIFIER) {
        throw std::runtime_error("Expected type");
    }
    writeToken();
    advance();

    // varName
    if (tokenizer.tokenType() != JackTokenizer::IDENTIFIER) {
        throw std::runtime_error("Expected variable name");
    }
    writeToken();
    advance();

    // (',' varName)*
    while (tokenizer.tokenType() == JackTokenizer::SYMBOL && tokenizer.symbol() == ',') {
        writeToken();
        advance();

        if (tokenizer.tokenType() != JackTokenizer::IDENTIFIER) {
            throw std::runtime_error("Expected variable name");
        }
        writeToken();
        advance();
    }

    // ;
    if (tokenizer.tokenType() != JackTokenizer::SYMBOL || tokenizer.symbol() != ';') {
        throw std::runtime_error("Expected ';'");
    }
    writeToken();
    advance();

    indentLevel--;
    writeXMLTag("varDec", true);
}

void CompilationEngine::compileStatements() {
    writeXMLTag("statements", false);
    indentLevel++;

    while (tokenizer.tokenType() == JackTokenizer::KEYWORD) {
        switch (tokenizer.keyWord()) {
            case JackTokenizer::LET:
                compileLet();
                break;
            case JackTokenizer::IF:
                compileIf();
                break;
            case JackTokenizer::WHILE:
                compileWhile();
                break;
            case JackTokenizer::DO:
                compileDo();
                break;
            case JackTokenizer::RETURN:
                compileReturn();
                break;
            default:
                throw std::runtime_error("Expected statement");
        }
    }

    indentLevel--;
    writeXMLTag("statements", true);
}

void CompilationEngine::compileLet() {
    writeXMLTag("letStatement", false);
    indentLevel++;

    // let
    writeToken();
    advance();

    // varName
    if (tokenizer.tokenType() != JackTokenizer::IDENTIFIER) {
        throw std::runtime_error("Expected variable name");
    }
    writeToken();
    advance();

    // ('[' expression ']')?
    if (tokenizer.tokenType() == JackTokenizer::SYMBOL && tokenizer.symbol() == '[') {
        writeToken();
        advance();

        compileExpression();

        if (tokenizer.tokenType() != JackTokenizer::SYMBOL || tokenizer.symbol() != ']') {
            throw std::runtime_error("Expected ']'");
        }
        writeToken();
        advance();
    }

    // =
    if (tokenizer.tokenType() != JackTokenizer::SYMBOL || tokenizer.symbol() != '=') {
        throw std::runtime_error("Expected '='");
    }
    writeToken();
    advance();

    compileExpression();

    // ;
    if (tokenizer.tokenType() != JackTokenizer::SYMBOL || tokenizer.symbol() != ';') {
        throw std::runtime_error("Expected ';'");
    }
    writeToken();
    advance();

    indentLevel--;
    writeXMLTag("letStatement", true);
}

void CompilationEngine::compileIf() {
    writeXMLTag("ifStatement", false);
    indentLevel++;

    // if
    writeToken();
    advance();

    // (
    if (tokenizer.tokenType() != JackTokenizer::SYMBOL || tokenizer.symbol() != '(') {
        throw std::runtime_error("Expected '('");
    }
    writeToken();
    advance();

    compileExpression();

    // )
    if (tokenizer.tokenType() != JackTokenizer::SYMBOL || tokenizer.symbol() != ')') {
        throw std::runtime_error("Expected ')'");
    }
    writeToken();
    advance();

    // {
    if (tokenizer.tokenType() != JackTokenizer::SYMBOL || tokenizer.symbol() != '{') {
        throw std::runtime_error("Expected '{'");
    }
    writeToken();
    advance();

    compileStatements();

    // }
    if (tokenizer.tokenType() != JackTokenizer::SYMBOL || tokenizer.symbol() != '}') {
        throw std::runtime_error("Expected '}'");
    }
    writeToken();
    advance();

    // (else { statements })?
    if (tokenizer.tokenType() == JackTokenizer::KEYWORD && tokenizer.keyWord() == JackTokenizer::ELSE) {
        writeToken();
        advance();

        if (tokenizer.tokenType() != JackTokenizer::SYMBOL || tokenizer.symbol() != '{') {
            throw std::runtime_error("Expected '{'");
        }
        writeToken();
        advance();

        compileStatements();

        if (tokenizer.tokenType() != JackTokenizer::SYMBOL || tokenizer.symbol() != '}') {
            throw std::runtime_error("Expected '}'");
        }
        writeToken();
        advance();
    }

    indentLevel--;
    writeXMLTag("ifStatement", true);
}

void CompilationEngine::compileWhile() {
    writeXMLTag("whileStatement", false);
    indentLevel++;

    // while
    writeToken();
    advance();

    // (
    if (tokenizer.tokenType() != JackTokenizer::SYMBOL || tokenizer.symbol() != '(') {
        throw std::runtime_error("Expected '('");
    }
    writeToken();
    advance();

    compileExpression();

    // )
    if (tokenizer.tokenType() != JackTokenizer::SYMBOL || tokenizer.symbol() != ')') {
        throw std::runtime_error("Expected ')'");
    }
    writeToken();
    advance();

    // {
    if (tokenizer.tokenType() != JackTokenizer::SYMBOL || tokenizer.symbol() != '{') {
        throw std::runtime_error("Expected '{'");
    }
    writeToken();
    advance();

    compileStatements();

    // }
    if (tokenizer.tokenType() != JackTokenizer::SYMBOL || tokenizer.symbol() != '}') {
        throw std::runtime_error("Expected '}'");
    }
    writeToken();
    advance();

    indentLevel--;
    writeXMLTag("whileStatement", true);
}

void CompilationEngine::compileDo() {
    writeXMLTag("doStatement", false);
    indentLevel++;

    // do
    writeToken();
    advance();

    // subroutineCall
    if (tokenizer.tokenType() != JackTokenizer::IDENTIFIER) {
        throw std::runtime_error("Expected subroutine name");
    }
    writeToken();
    advance();

    if (tokenizer.tokenType() == JackTokenizer::SYMBOL && tokenizer.symbol() == '.') {
        writeToken();
        advance();

        if (tokenizer.tokenType() != JackTokenizer::IDENTIFIER) {
            throw std::runtime_error("Expected subroutine name");
        }
        writeToken();
        advance();
    }

    // (
    if (tokenizer.tokenType() != JackTokenizer::SYMBOL || tokenizer.symbol() != '(') {
        throw std::runtime_error("Expected '('");
    }
    writeToken();
    advance();

    compileExpressionList();

    // )
    if (tokenizer.tokenType() != JackTokenizer::SYMBOL || tokenizer.symbol() != ')') {
        throw std::runtime_error("Expected ')'");
    }
    writeToken();
    advance();

    // ;
    if (tokenizer.tokenType() != JackTokenizer::SYMBOL || tokenizer.symbol() != ';') {
        throw std::runtime_error("Expected ';'");
    }
    writeToken();
    advance();

    indentLevel--;
    writeXMLTag("doStatement", true);
}

void CompilationEngine::compileReturn() {
    writeXMLTag("returnStatement", false);
    indentLevel++;

    // return
    writeToken();
    advance();

    // expression?
    if (tokenizer.tokenType() != JackTokenizer::SYMBOL || tokenizer.symbol() != ';') {
        compileExpression();
    }

    // ;
    if (tokenizer.tokenType() != JackTokenizer::SYMBOL || tokenizer.symbol() != ';') {
        throw std::runtime_error("Expected ';'");
    }
    writeToken();
    advance();

    indentLevel--;
    writeXMLTag("returnStatement", true);
}

void CompilationEngine::compileExpression() {
    writeXMLTag("expression", false);
    indentLevel++;

    compileTerm();

    while (tokenizer.tokenType() == JackTokenizer::SYMBOL && isOperator(tokenizer.symbol())) {
        writeToken();
        advance();
        compileTerm();
    }

    indentLevel--;
    writeXMLTag("expression", true);
}

void CompilationEngine::compileTerm() {
    writeXMLTag("term", false);
    indentLevel++;

    if (tokenizer.tokenType() == JackTokenizer::INT_CONST) {
        writeToken();
        advance();
    } else if (tokenizer.tokenType() == JackTokenizer::STRING_CONST) {
        writeToken();
        advance();
    } else if (tokenizer.tokenType() == JackTokenizer::KEYWORD) {
        if (tokenizer.keyWord() == JackTokenizer::TRUE ||
            tokenizer.keyWord() == JackTokenizer::FALSE ||
            tokenizer.keyWord() == JackTokenizer::NULL_KEY ||
            tokenizer.keyWord() == JackTokenizer::THIS) {
            writeToken();
            advance();
        } else {
            throw std::runtime_error("Expected keyword constant");
        }
    } else if (tokenizer.tokenType() == JackTokenizer::IDENTIFIER) {
        writeToken();
        advance();
        if (tokenizer.tokenType() == JackTokenizer::SYMBOL && tokenizer.symbol() == '[') {
            writeToken();
            advance();
            compileExpression();
            if (tokenizer.tokenType() != JackTokenizer::SYMBOL || tokenizer.symbol() != ']') {
                throw std::runtime_error("Expected ']'");
            }
            writeToken();
            advance();
        } else if (tokenizer.tokenType() == JackTokenizer::SYMBOL && (tokenizer.symbol() == '(' || tokenizer.symbol() == '.')) {
            if (tokenizer.symbol() == '(') {
                writeToken();
                advance();
                compileExpressionList();
                if (tokenizer.tokenType() != JackTokenizer::SYMBOL || tokenizer.symbol() != ')') {
                    throw std::runtime_error("Expected ')'");
                }
                writeToken();
                advance();
            } else if (tokenizer.symbol() == '.') {
                writeToken();
                advance();
                if (tokenizer.tokenType() != JackTokenizer::IDENTIFIER) {
                    throw std::runtime_error("Expected subroutine name");
                }
                writeToken();
                advance();
                if (tokenizer.tokenType() != JackTokenizer::SYMBOL || tokenizer.symbol() != '(') {
                    throw std::runtime_error("Expected '('");
                }
                writeToken();
                advance();
                compileExpressionList();
                if (tokenizer.tokenType() != JackTokenizer::SYMBOL || tokenizer.symbol() != ')') {
                    throw std::runtime_error("Expected ')'");
                }
                writeToken();
                advance();
            }
        }
    } else if (tokenizer.tokenType() == JackTokenizer::SYMBOL) {
        if (tokenizer.symbol() == '(') {
            writeToken();
            advance();
            compileExpression();
            if (tokenizer.tokenType() != JackTokenizer::SYMBOL || tokenizer.symbol() != ')') {
                throw std::runtime_error("Expected ')'");
            }
            writeToken();
            advance();
        } else if (tokenizer.symbol() == '-' || tokenizer.symbol() == '~') {
            writeToken();
            advance();
            compileTerm();
        } else {
            throw std::runtime_error("Expected term");
        }
    } else {
        throw std::runtime_error("Expected term");
    }

    indentLevel--;
    writeXMLTag("term", true);
}

int CompilationEngine::compileExpressionList() {
    writeXMLTag("expressionList", false);
    indentLevel++;

    int numExpressions = 0;

    if (tokenizer.tokenType() != JackTokenizer::SYMBOL || tokenizer.symbol() != ')') {
        compileExpression();
        numExpressions++;
        while (tokenizer.tokenType() == JackTokenizer::SYMBOL && tokenizer.symbol() == ',') {
            writeToken();
            advance();
            compileExpression();
            numExpressions++;
        }
    }

    indentLevel--;
    writeXMLTag("expressionList", true);

    return numExpressions;
}