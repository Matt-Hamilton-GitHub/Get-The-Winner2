#include <array>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const string filename = "votes.txt";
const int maxCandidates = 8;
struct Candidate
{
    string name = "";
    size_t votes = 0;
    double percent = 0.0;
};
int main()
{
    ifstream inps(filename);
    assert(inps);
    array<Candidate, maxCandidates> candidates;
    size_t nCandidates = 0;
    while (inps.good() && nCandidates < maxCandidates)
    {
        string name;
        inps >> name;
        size_t votes;
        inps >> votes;
        candidates[nCandidates].name = name;
        candidates[nCandidates].votes = votes;
        nCandidates++;
    }
    if (nCandidates > 0)
    {
        size_t namefieldwidth = 12;
        size_t maxvotes = 0;
        size_t maxidx = 0;
        size_t totalvotes = 0;
        for (size_t idx = 0; idx < nCandidates; idx++)
        {
            totalvotes += candidates[idx].votes;
            if (candidates[idx].votes > maxvotes)
            {
                maxvotes = candidates[idx].votes;
                maxidx = idx;
            }
        }
        size_t namefieldwith = 16;
        size_t votesfieldwidth = 16;
        size_t percentfieldwidth = 16;
        if (totalvotes > 0)
        {
            for (size_t idx = 0; idx < nCandidates; idx++)
                candidates[idx].percent = 100.0 * candidates[idx].votes / static_cast<double>(totalvotes);
        }
        cout << fixed << setprecision(2);
        cout << left << setw(namefieldwidth) << "Candidate" << ' ' << right << setw(votesfieldwidth) << "Votes Received" << ' ' << right << setw(percentfieldwidth) << setfill(' ') << "% of Total Votes " << endl << endl;
        for (size_t idx = 0; idx < nCandidates; ++idx)
            cout << left << setw(namefieldwidth) << candidates[idx].name << ' ' << right << setw(votesfieldwidth) << candidates[idx].votes << ' ' << right << setw(percentfieldwidth) << setfill(' ') << candidates[idx].percent << endl;
        size_t totalvotesfieldwidth = namefieldwidth + votesfieldwidth + 1;
        cout << setw(totalvotesfieldwidth) << totalvotes << endl << endl;

        cout << "The winner of the Election is " << candidates[maxidx].name << endl;
    }
    return 0;
}
