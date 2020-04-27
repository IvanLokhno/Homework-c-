using namespace std;

class Parser 
{
    Lex          curr_lex;
    type_of_lex  c_type;
    int          c_val;
    string       c_string_val;   
    Scanner      scan;
    void         P();
    void         D1();
    void         D();
    void         I1();
    void         CONST_();
    void         S();
    void         S1();
    void         E();
    void         E1();
    void         T();
    void         F();
    void         gl ()
    {
        curr_lex = scan.get_lex();
        c_type = curr_lex.get_type();
        c_val = curr_lex.get_value();
    }
public:
                Parser (const char *program ) : scan (program){}
    void        analyze();
};
