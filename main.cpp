

//                                            ********* Writer: Matt Hamilton      *********
 //                                             ******** Class: CS 136             ******** 
 //                                              ******* Professor: Brian Dauzat   *******
 //                                                *****         Quiz #3           *****
 //                                                 **** ========================= ****
 //                                                   **  *** *** *** *** *** *** **

//Modify the attached file to detect and display multiple candidates with the same number of votes: 
//multiple winners, multiple candidates with the second highest number of votes, multiple candidates 
//with the third highest number of votes, and so on.




#include <array>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <map>



using namespace std;

const string filename = "votes.txt";
const int maxCandidates = 8;

struct Candidate
{
    string name = "";
    size_t votes = 0;
    double percent = 0.0;
	
	string rank;//to store the rank in elections
	vector <string> place {"First", "Second", "Third", "Fourth", "Fifth", "Sixth"};

};







int main()
{
    ifstream inps(filename);
    assert(inps);
    array <Candidate, maxCandidates> candidates;
    size_t nCandidates = 0;
	
    while (inps.good() && nCandidates < maxCandidates) //validate input
    {
        string name;
        inps >> name;//store each name
        size_t votes;
        inps >> votes;//store number of votes 
        candidates[nCandidates].name = name; ///pass names to the array at a specific index
        candidates[nCandidates].votes = votes;//pass number of votes to the array at a specific index (candidate)
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
                candidates[idx].percent = 100.0 * candidates[idx].votes / static_cast<double>(totalvotes);//set percentage for each candidate 
        }
		
			// -------------------- Check if there is more than one winner ----------------------|
		
		unsigned int max_votes = candidates[maxidx].votes; // stores the max number of votes received during elections
		vector <int> winners_index;//a vector that stores the index of every winner, whether there is only one or more than one winner.
		
		
		for(size_t idx{0}; idx < nCandidates; idx++){//loop through the entire struct 
			if(max_votes == candidates[idx].votes){// find other candidates who have the same amount of votes as the winner
			  winners_index.push_back(idx); // store the index of a winner to the vector of winners
			  
			}
		}
		
		
		//*********************** Quiz 3 ********************||
	  
			//Step 1 
		//let's create a vector that would hold candidates' ranks (in words), 
		//since the max number of participants is 8, we gonna have a maximum of 8 ranks
		vector <string> ranks_vec {"First", "Second", "Third", "Fourth", "Fifth", "Sixth","Seventh","Eighth"};
		
			//Step 2
		//let's create a map that would hold the candidate's name and a number of votes. 
		//in this case data type map is really useful since it automatically sorts number values from lowest to greatest
		//names of the candidates don't really matter, because all we need is the number of votes. The program is not gonna use the names from map rank
		map <int, string> rank; 
		
		
		//Step 3
		//then set names and number of votes to the map for each candidate. 
		for(size_t idx{0}; idx < nCandidates; idx++){
			rank.insert(pair<int, string>(candidates[idx].votes, candidates[idx].name));
		};
		
		//Step 4
		//Now we have the number of votes stored to the map (without the repetition)
		
		int num_of_ranks = rank.size();//this variable basically represents the number of ranks, because it stores the number of votes that are unique
		int rank_idx{num_of_ranks-1}; //since the first value in the rank map represents the lowest number of votes, we give it the lowest rank based on the number of participants
		
		//now we loop through the map 
		for(const auto &elem : rank){
			
			//and give a rank to each candidate
		for (size_t idx {0}; idx < nCandidates; idx++){
			
               if(candidates[idx].votes ==  elem.first){
			   candidates[idx].rank = ranks_vec[rank_idx]; 
			   }
				}
				rank_idx--; 
		};
				
		

		//-------------output the deta -------------|
	cout << "\t**************************************************************************\n";
        cout << fixed << setprecision(2);
        cout << left << setw(namefieldwith) << "Candidate" << ' ' << right << setw(votesfieldwidth) << "Votes Received" << ' ' 
		<< right << setw(percentfieldwidth) << setfill(' ') << "% of Total Votes " << endl << endl;
        for (size_t idx = 0; idx < nCandidates; ++idx)
            cout << left << setw(namefieldwith) << candidates[idx].name << ' ' << right << setw(votesfieldwidth) << candidates[idx].votes << ' ' << right << setw(percentfieldwidth) << setfill(' ') << candidates[idx].percent << endl;
        size_t totalvotesfieldwidth = namefieldwidth + votesfieldwidth + 1;
		cout << "---------------------------------------------------------------------------\n";
        cout << "Total:" << setw(totalvotesfieldwidth) <<  totalvotes  << endl << endl;
		 
		   cout << "Candiate Place in The Elctions : \n"  << endl;
		   cout << "-------------------------------\n";
      for(size_t idx{0}; idx < nCandidates; idx++){//loop through all the winners in this elections
		  cout << left << setw(namefieldwith) << candidates[idx].name << right << setw(votesfieldwidth) << " - " << candidates[idx].rank + " Place"
		  << " ( " << candidates[idx].votes << " vts) " << endl;
	  }
		cout << "\n\n\t********************The End of The Elections*********************\n";

    }
	
	
	system("pause");
    return 0;
}
