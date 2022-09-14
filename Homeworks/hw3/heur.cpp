#include <cmath>
#include "heur.h"
#include <vector>
#include <set>
using namespace std;

// Complete
size_t BFSHeuristic::compute(const Board& b)
{
    return 0U;
}


// To be completed
size_t DirectHeuristic::compute(const Board& b)
{
    Vehicle a = b.escapeVehicle();
    int escapeRow = a.startr;
    std::set<char> VSet;
    for (int i = a.startc + a.length; i < b.size(); i++)
    {
        char v = b.at(escapeRow, i);
        if (v != '.')
        {
            VSet.insert(v);
        }
    }
    return VSet.size();
    
}

// To be completed
size_t IndirectHeuristic::compute(const Board& b)
{
    Vehicle a = b.escapeVehicle();
    int escapeRow = a.startr;
    std::set<char> VSet;
    for (int i = a.startc + a.length; i < b.size(); i++){
        //char dv = b.at(escapeRow, i);
        if (b.at(escapeRow, i) != '.'){
            VSet.insert(b.at(escapeRow, i));
            std::set<char> aboveSet;
            std::set<char> belowSet;
            bool canFit = false;
            Vehicle directBlock = b.vehicle(b.at(escapeRow, i));
            if (directBlock.length <= escapeRow){
                for (int j = directBlock.startr-1; j >= 0; j--){
                    //char iv = b.at(j, i);
                    if (b.at(j, i) != '.'){
                        aboveSet.insert(b.at(j, i));
                    }
                }
                if (aboveSet.empty()){
                    canFit = true;
                }
            }
            if (directBlock.length <= b.size()-escapeRow-1){
                for (int k = directBlock.startr + directBlock.length; k < b.size(); k++){
                    //char iv = b.at(k, i);
                    if (b.at(k, i) != '.'){
                        belowSet.insert(b.at(k, i));
                    }
                }
                if (belowSet.empty()){
                    canFit = true;
                }
            }
            if (aboveSet.empty() && !(belowSet.empty()) && canFit == false){
                VSet.insert(*(belowSet.begin()));
            }
            else if (!(aboveSet.empty()) && belowSet.empty() && canFit == false){
                VSet.insert(*(aboveSet.begin()));
            }
        }
    }
    return VSet.size();
}

