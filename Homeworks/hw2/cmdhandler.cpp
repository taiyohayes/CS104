#include "cmdhandler.h"
#include "util.h"
#include <map>
#include <set>
using namespace std;

// Complete
QuitHandler::QuitHandler()
{

}

// Complete
QuitHandler::QuitHandler(Handler* next)
    : Handler(next)
{

}

// Complete
bool QuitHandler::canHandle(const std::string& cmd) const
{
    return cmd == "QUIT";

}

// Complete
Handler::HANDLER_STATUS_T QuitHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    return HANDLER_QUIT;
}

// Complete
PrintHandler::PrintHandler()
{

}

// Complete
PrintHandler::PrintHandler(Handler* next)
    : Handler(next)
{

}

// Complete
bool PrintHandler::canHandle(const std::string& cmd) const
{
    return cmd == "PRINT";

}

// Complete
Handler::HANDLER_STATUS_T PrintHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    string name;

    if (!(instr >> name)) {
        return HANDLER_ERROR;
    }
    try {
        eng->display_page(ostr, name);
    }
    catch (std::exception& e) {
        return HANDLER_ERROR;
    }
}

IncomingHandler::IncomingHandler()
{

}
IncomingHandler::IncomingHandler(Handler* next)
    : Handler(next)
{

}
bool IncomingHandler::canHandle(const std::string& cmd) const
{
    return cmd == "INCOMING";
}
Handler::HANDLER_STATUS_T IncomingHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    string name;
    instr >> name;
    WebPage* page = eng->retrieve_page(name);
    if (page == NULL)
    {
        return HANDLER_ERROR;
    }
    display_hits(page->incoming_links(), ostr);
    return HANDLER_OK;
}

OutgoingHandler::OutgoingHandler()
{

}
OutgoingHandler::OutgoingHandler(Handler* next)
    : Handler(next)
{

}
bool OutgoingHandler::canHandle(const std::string& cmd) const
{
    return cmd == "OUTGOING";
}
Handler::HANDLER_STATUS_T OutgoingHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    string name;
    instr >> name;
    WebPage* page = eng->retrieve_page(name);
    if (page == NULL)
    {
        return HANDLER_ERROR;
    }
    display_hits(page->outgoing_links(), ostr);
    return HANDLER_OK;

}

AndHandler::AndHandler()
{

}
AndHandler::AndHandler(Handler* next)
    : Handler(next)
{

}
bool AndHandler::canHandle(const std::string& cmd) const
{
    return cmd == "AND";
}
Handler::HANDLER_STATUS_T AndHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    string term;
    std::vector<std::string> vec;
    while(instr >> term)
    {
        vec.push_back(term);
    }
    WebPageSetCombiner* andC = new AndWebPageSetCombiner;
    WebPageSet andSet = eng->search(vec, andC);
    display_hits(andSet, ostr);
    delete andC;
    return HANDLER_OK;
}

OrHandler::OrHandler()
{

}

OrHandler::OrHandler(Handler* next)
    : Handler(next)
{


}
bool OrHandler::canHandle(const std::string& cmd) const
{
    return cmd == "OR";
}

Handler::HANDLER_STATUS_T OrHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    string term;
    std::vector<std::string> vec;
    while(instr >> term)
    {
        vec.push_back(term);
    };
    WebPageSetCombiner* orC = new OrWebPageSetCombiner;
    WebPageSet orSet = eng->search(vec, orC);
    display_hits(orSet, ostr);
    delete orC;
    return HANDLER_OK;
}

DiffHandler::DiffHandler()
{

}

DiffHandler::DiffHandler(Handler* next)
    : Handler(next)
{

}

bool DiffHandler::canHandle(const std::string& cmd) const
{
    return cmd == "DIFF";
}

Handler::HANDLER_STATUS_T DiffHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    string term;
    std::vector<std::string> vec;
    while(instr >> term)
    {
        vec.push_back(term);
    };
    WebPageSetCombiner* diffC = new DiffWebPageSetCombiner;
    WebPageSet diffSet = eng->search(vec, diffC);
    display_hits(diffSet, ostr);
    delete diffC;
    return HANDLER_OK;
}
// Add code for other handler class implementations below
