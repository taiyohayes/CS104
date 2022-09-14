#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cctype>
#include "md_parser.h"
#include "util.h"

using namespace std;

typedef enum { NORMALTEXT, LINKTEXT, ISLINK, LINKURL } PARSE_STATE_T;

// To be completed
void MDParser::parse(std::istream& istr, std::set<std::string>& allSearchableTerms, std::set<std::string>& allOutgoingLinks)
{

    // Remove any contents of the sets before starting to parse.
    allSearchableTerms.clear();
    allOutgoingLinks.clear();

    // Complete your code below
    string term = "";
    string link = "";

    char x = istr.get();
    //bool isLink = false;
    PARSE_STATE_T state = NORMALTEXT;

    while(!istr.fail()){
        if (state == NORMALTEXT){
            if (!isalnum(x)){
                if (term != ""){
                    term = conv_to_lower(term);
                    allSearchableTerms.insert(term);
                    term = "";
                }
                if (x == ']'){
                    x = istr.get();
                    if (!isalnum(x)){
                        if (x == '('){
                            state = LINKURL;
                        }
                    }
                    else{
                        term += x;
                    }
                }
            }
            else{
                term += x;
            }
        }
        else{
            if (x == ')'){
                if (link != ""){
                    link = conv_to_lower(link);
                    allOutgoingLinks.insert(link);
                    link = "";
                }
                state = NORMALTEXT;
            }
            else{
                link += x;
            }
        }
        x = istr.get();
    }
    if(term != ""){
        term = conv_to_lower(term);
        allSearchableTerms.insert(term);
    }
}

// To be completed
std::string MDParser::display_text(std::istream& istr)
{
    std::string text = "";

    char x = istr.get();
    PARSE_STATE_T state = NORMALTEXT;
    while (!istr.fail()){
        if (state == NORMALTEXT){
            if (x == ']'){
                text += x;
                x = istr.get();
                if (x == '('){
                    state = LINKURL;
                }
                else{
                    text += x;
                }
            }
            else{
                text += x;
            }
        }
        else{
            if (x == ')'){
                state = NORMALTEXT;
            }
        }
        x = istr.get();
    }
    return text;
}


