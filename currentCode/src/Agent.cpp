/*Agent.cpp */

#include "Agent.h"

//constructor
Agent::Agent(repast::AgentId id){ }

Agent::~Agent()

//setters
void Agent::set(int currentRank,char newMode ){
    id_.currentRank(currentRank);
    mode     = newMode;
} //not sure of need for rank, clarification needed with notes

//getters
Agent::char getMode(){
    return mode;
}

//Actions
Agent::char switchMode(char newMode){
    mode = newMode;
} //which mode the agents should switch to (can stay the same)

Agent::void decideToSearch(){
    if (gain > cost){
        search();
        cout << "Agent decided to search" << endl;
    }
    else{
        cout << "Agent decided not to search" << endl;
    }
    
} //logic for agent deciding to search for a new mode of transport

Agent::void search{
    /*
     Logic based on fuzzy logic from beijing paper
     */
    cout << "Search function ran" << endl;
    
} //logic for agent deciding which mode of transport to switch to (uses switch mode)
