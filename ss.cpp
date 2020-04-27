#include "ss.h"

using namespace std;

void Parser::analyze ()
{
    gl();
    P();
    cout << endl << "Syntax is OK!!!" << endl;
}
 
void Parser::P ()
{
    // cout << "P\n";
    if (c_type == LEX_PROGRAM)
        gl();
    else
        throw curr_lex;
    if (c_type == LEX_LCBR)
        gl();
    else
        throw curr_lex;
    D1();

    S1();

    if (c_type == LEX_RCBR)
    {
        gl();
    }
    else
        throw curr_lex;


    if (c_type != LEX_FIN)
        throw curr_lex;
}
 
void Parser::D1 ()
{
    // cout << "D1\n";
    while (c_type == LEX_INT || c_type == LEX_STRING || c_type == LEX_BOOLEAN)
    {   
        D();
        if (c_type == LEX_SEMICOLON) 
        {   
            gl();
        }
        else
            throw curr_lex;
    }
}

void Parser::D ()
{
    // cout << "D\n";
    if (c_type == LEX_INT)
    {
        //some semantic moves
    } else if (c_type == LEX_STRING)
    {
        //some semantic moves
    } else if (c_type == LEX_BOOLEAN)
    {
        //some semantic moves
    }
    gl();
    I1();
    while (c_type == LEX_COMMA)
    {
        gl();
        I1();
    }
}

void Parser::I1 ()
{
    // cout << "I1\n";
    if (c_type == LEX_ID)
    {
        gl(); 
    } else 
    {
        throw curr_lex;
    } 

    if (c_type == LEX_EQ) {
        gl();
        CONST_();
    }
}

void Parser::CONST_ ()
{
    // cout << "CONST\n";
    if (c_type == LEX_PLUS || c_type == LEX_MINUS)
    {
        //some semantics
        gl();
        if (c_type == LEX_NUM)
        {
            gl();
        } else
        {
            throw curr_lex;
        } 
    } else if (c_type == LEX_STR)
    {
        //some semantic
        gl();
    } else  if (c_type == LEX_TRUE || c_type == LEX_FALSE)
    {
        //some semantic
        gl();
    } else
    {
        throw curr_lex;
    }
}

void Parser::S1 ()
{
    // cout << "S1\n";
    while (c_type == LEX_IF || c_type == LEX_WHILE || c_type == LEX_READ || \
        c_type == LEX_WRITE || c_type == LEX_LCBR ||  c_type == LEX_ID)
    {
        S();
    } 
}

void Parser::S ()
{
    // cout << "S\n";
    if (c_type == LEX_IF)
    {
        gl();
        if ( c_type == LEX_LPAREN )
        {
            gl();
        }
        else
            throw curr_lex;
        E();
        if ( c_type == LEX_RPAREN )
        {
            gl();
        }
        else
            throw curr_lex;
        S();
        if ( c_type == LEX_ELSE )
        {
            gl();
        }
        else
            throw curr_lex;
        S();
    }//end_if
    else if (c_type == LEX_WHILE)
    {
        gl();
        if ( c_type == LEX_LPAREN )
        {
            gl();
        }
        else
            throw curr_lex;
        E();
        if ( c_type == LEX_RPAREN )
        {
            gl();
        }
        else
            throw curr_lex;
        S();
    }//end_while
    else if (c_type == LEX_READ)
    {
        gl();
        if ( c_type == LEX_LPAREN )
        {
            gl();
        }
        else
            throw curr_lex;
        if ( c_type == LEX_ID )
        {
            gl();
        }
        else
            throw curr_lex;
        if ( c_type == LEX_RPAREN )
        {
            gl();
        }
        else
            throw curr_lex;
        if ( c_type == LEX_SEMICOLON )
        {
            gl();
        }
        else
            throw curr_lex;
    }//end read
    else if (c_type == LEX_WRITE)
    {
        gl();
        if ( c_type == LEX_LPAREN )
        {
            gl();
        }
        else
            throw curr_lex;
        E();
        while (c_type == LEX_COMMA) 
        {
            gl();
            E();
        }
        if ( c_type == LEX_RPAREN )
        {
            gl();
        }
        else
            throw curr_lex;
        if ( c_type == LEX_SEMICOLON )
        {
            gl();
        }
        else
            throw curr_lex;
    }//end write
    else if ( c_type == LEX_ID )
    {
        gl();
        if ( c_type == LEX_EQ )
        {
            gl();
        }
        else
            throw curr_lex;
        E();
        if ( c_type == LEX_SEMICOLON )
        {
            gl();
        }
        else
            throw curr_lex;
    }//assign-end
    else if (c_type == LEX_LCBR) 
    {
        S1();
        if ( c_type == LEX_RCBR )
        {
            gl();
        }
        else
            throw curr_lex;

    } //составной оператор end
    else
        throw curr_lex;

}
void Parser::E () 
{
    // cout << "E\n";
    E1();
    if ( c_type == LEX_EQEQ || c_type == LEX_LSS || c_type == LEX_GTR ||
       c_type == LEX_LEQ || c_type == LEX_GEQ || c_type == LEX_NEQ )
    {
        gl(); 
        E1(); 
    }
}
 
void Parser::E1 ()
{
    // cout << "E1\n";
    T();
    while ( c_type == LEX_PLUS || c_type == LEX_MINUS || c_type == LEX_OR)
    {
        gl();
        T();
    }
}
 
void Parser::T ()
{
    // cout << "T\n";
    F();
    while ( c_type == LEX_TIMES || c_type == LEX_SLASH || c_type == LEX_AND || c_type == LEX_PERCENT)
    {
        gl();
        F();
    }
}
 
void Parser::F () 
{
    // cout << "F\n";
    if ( c_type == LEX_ID ) 
    {
        gl();
    }
    else if ( c_type == LEX_NUM ) 
    {
        gl();
    }
    else if ( c_type == LEX_TRUE ) 
    {
        gl();
    }
    else if ( c_type == LEX_FALSE)
    {
        gl();
    }
    else if (c_type == LEX_NOT) 
    {
        gl(); 
        F(); 
    }
    else if ( c_type == LEX_LPAREN ) 
    {
        gl(); 
        E();
    if ( c_type == LEX_RPAREN)
        gl();
    else 
        throw curr_lex;
    }
    else 
        throw curr_lex;
}
 
