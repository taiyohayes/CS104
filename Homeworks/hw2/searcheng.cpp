#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include "searcheng.h"

using namespace std;

// Helper function that will extract the extension of a filename
std::string extract_extension(const std::string& filename);

std::string extract_extension(const std::string& filename)
{
    size_t idx = filename.rfind(".");
    if (idx == std::string::npos) {
        return std::string();
    }
    return filename.substr(idx + 1);
}


// To be updated as needed 
SearchEng::SearchEng()
{
    parsers_.clear();
    termpages.clear();
    pages.clear();

}

// To be completed
SearchEng::~SearchEng()
{
    for (map<string, WebPage*>::iterator it = pages.begin(); it != pages.end(); it++)
    {
        delete it->second;
    }
    for (map<string, PageParser*>::iterator it = parsers_.begin(); it != parsers_.end(); it++)
    {
        delete it->second;
    }
}

// Complete
void SearchEng::register_parser(const std::string& extension, PageParser* parser)
{
    if (parsers_.find(extension) != parsers_.end())
    {
        throw std::invalid_argument("parser for provided extension already exists");
    }
    parsers_.insert(make_pair(extension, parser));
}

// Complete
void SearchEng::read_pages_from_index(const std::string& index_file)
{
    ifstream ifile(index_file.c_str());
    if(ifile.fail()) {
        cerr << "Unable to open index file: " << index_file << endl;
    }

    // Parse all the files
    string filename;
    while(ifile >> filename) {
#ifdef DEBUG
        cout << "Reading " << filename << endl;
#endif
        read_page(filename);
    }
    ifile.close();
}

// To be completed
void SearchEng::read_page(const string& filename)
{

    string ext = extract_extension(filename);
    if (parsers_.find(ext) == parsers_.end())
    {
        throw std::logic_error("no parser registered for provided extension");
    }
    ifstream ifile(filename.c_str());
    if (ifile.fail())
    {
        throw std::invalid_argument("file does not exist");
    }
    PageParser* p = parsers_[ext];
    StringSet allSearchTerms;
    StringSet allOutgoingLinks;
    p->parse(ifile, allSearchTerms, allOutgoingLinks);
    if (pages.find(filename) == pages.end())
    {
        WebPage* wPage = new WebPage;
        wPage->filename(filename);
        wPage->all_terms(allSearchTerms);
        pages.insert(make_pair( filename, wPage) );
        for (StringSet::iterator it = allSearchTerms.begin(); it != allSearchTerms.end(); ++it)
        {
            if (termpages.find(*it) == termpages.end())
            {
                WebPageSet searchset;
                termpages.insert(make_pair( *it, searchset ));
            }
            termpages[*it].insert(wPage);
        }
        for (StringSet::iterator it = allOutgoingLinks.begin(); it != allOutgoingLinks.end(); ++it)
        {
            if (pages.find(*it) == pages.end())
            {
                WebPage* wPage2 = new WebPage;
                pages.insert(make_pair(*it, wPage2));
                wPage2->filename(*it);
                wPage2->add_incoming_link(wPage);
                wPage->add_outgoing_link(wPage2);
                
            }
            else
            {
                pages.find(*it)->second->add_incoming_link(wPage);
                wPage->add_outgoing_link(pages.find(*it)->second);
            }
        }
    }
    else
    {
        WebPage* wPage = pages.find(filename)->second;
        for (StringSet::iterator it = allOutgoingLinks.begin(); it != allOutgoingLinks.end(); ++it)
        {
            if (pages.find(*it) == pages.end())
            {
                WebPage* wPage2 = new WebPage;
                pages.insert(make_pair(*it, wPage2));
                wPage2->filename(*it);
                wPage2->add_incoming_link(wPage);
                wPage->add_outgoing_link(wPage2);
                
            }
            else
            {
                pages.find(*it)->second->add_incoming_link(wPage);
                wPage->add_outgoing_link(pages.find(*it)->second);
            }
        }
    }
}

// To be completed
WebPage* SearchEng::retrieve_page(const std::string& page_name) const
{
    map<string, WebPage*> :: const_iterator it = pages.find(page_name);
    if (it == pages.end())
    {
        return NULL;
    }
    return it->second; 
}

// To be completed
void SearchEng::display_page(std::ostream& ostr, const std::string& page_name) const
{
    WebPage* page = retrieve_page(page_name);
    string file = page->filename();
    string ext = extract_extension(file); 
    map<string, PageParser*> :: const_iterator it = parsers_.find(ext);
    if (it == parsers_.end())
    {
        throw std::logic_error("no parser registered for provided extension");
    }
    PageParser* p = it->second;
    ifstream ifile(file.c_str());
    string display = p->display_text(ifile);
    ostr << display;
}

// To be completed
WebPageSet SearchEng::search(const std::vector<std::string>& terms, WebPageSetCombiner* combiner) const
{
    WebPageSet combo;
    WebPageSet combo2;
    combo.clear();
    combo2.clear();
    if (terms.size() == 0)
    {
        //delete combiner;
        return combo;
    }
    else
    {
        for (vector<string> :: const_iterator vit = terms.begin(); vit != terms.end(); ++vit)
        {
            map<string, WebPageSet> :: const_iterator it1 = termpages.find(*vit);
            if (vit == terms.begin())
            {
                if (it1 != termpages.end())
                {
                    combo = it1 -> second;
                }
                if (terms.size() == 1)
                {
                    return combo;
                }

            }
            else
            {
                if (it1 != termpages.end())
                {
                    combo2 = it1 -> second;
                    combo = combiner->combine(combo, it1 -> second);
                }
            }
        }
        //delete combiner;
        return combo;
    }
}

// Add private helper function implementations here

