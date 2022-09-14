#include "combiners.h"
#include "searcheng.h"
#include "util.h"
#include <set>
#include <iostream>
// Complete the necessary code
using namespace std;

AndWebPageSetCombiner::AndWebPageSetCombiner()
{
}

WebPageSet AndWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB)
{
    WebPageSet comboSet;
    for (set<WebPage*>:: iterator it = setA.begin(); it != setA.end(); ++it)
    {
        if (setB.find(*it) != setB.end())
        {
            comboSet.insert(*it);
        }
    }
    return comboSet;
}
OrWebPageSetCombiner::OrWebPageSetCombiner()
{
}

WebPageSet OrWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB)
{
    WebPageSet comboSet;
    comboSet.clear();
    if (setA.empty())
    {
        comboSet = setB;
    }
    else if (setB.empty())
    {
        comboSet = setA;
    }
    else
    {
        for (set<WebPage*>::iterator it = setA.begin(); it != setA.end(); ++it)
        {
            comboSet.insert(*it);
        }
        for (set<WebPage*>::iterator it = setB.begin(); it != setB.end(); ++it)
        {
            comboSet.insert(*it);
        }
    }
    return comboSet;
}

DiffWebPageSetCombiner::DiffWebPageSetCombiner()
{
}

WebPageSet DiffWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB)
{
    WebPageSet comboSet;
    for (set<WebPage*>:: iterator it = setA.begin(); it != setA.end(); ++it)
    {
        if (setB.find(*it) == setB.end())
        {
            comboSet.insert(*it);
        }
    }
    return comboSet;
}