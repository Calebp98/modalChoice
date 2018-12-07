/* Demo_01_Agent.cpp */


#include <iostream>

#include "Demo_01_Agent.h"
#include "Fuzzy.h" //no longer use


//constructors
RepastHPCDemoAgent::RepastHPCDemoAgent(repast::AgentId id): id_(id), c(100), total(200){ }

RepastHPCDemoAgent::RepastHPCDemoAgent(repast::AgentId id, int age, char mode, int income, int travelDistance): id_(id), c(100), total(200), mode(mode), age(age), income(income), travelDistance(travelDistance){ } //added to set mode

RepastHPCDemoAgent::RepastHPCDemoAgent(repast::AgentId id, double newC, double newTotal): id_(id), c(newC), total(newTotal){ }

RepastHPCDemoAgent::~RepastHPCDemoAgent(){ } //destructor


void RepastHPCDemoAgent::set(int currentRank, double newC, double newTotal){ //set RepastHPCDemoAgent variables
    id_.currentRank(currentRank); //sets the current rank for the agent
    c     = newC; //set c attribute to newC parameter
    total = newTotal; //set total attribute to newTotal
}

bool RepastHPCDemoAgent::cooperate(){
	return repast::Random::instance()->nextDouble() < c/total; //if the random number is less than c/total cooperate
}

void RepastHPCDemoAgent::play(repast::SharedContext<RepastHPCDemoAgent>* context){ //play prisoners dilemma game
    // Fuzzy* fuzzyEngine = new Fuzzy();
    //
    // fuzzyEngine->search();

    std::set<RepastHPCDemoAgent*> agentsToPlay; //pointers to playing agents

    agentsToPlay.insert(this); // Prohibit playing against self

    context->selectAgents(3, agentsToPlay, true); //Gets a set of pointers to 3 randomly selected agents

    double cPayoff     = 0; //cooperation pay off
    double totalPayoff = 0; //total pay off
    std::set<RepastHPCDemoAgent*>::iterator agentToPlay = agentsToPlay.begin();
    while(agentToPlay != agentsToPlay.end()){
        bool iCooperated = cooperate();                          // Do I cooperate?
        double payoff = (iCooperated ?
						 ((*agentToPlay)->cooperate() ?  7 : 1) :     // If I cooperated, did my opponent?
						 ((*agentToPlay)->cooperate() ? 10 : 3));     // If I didn't cooperate, did my opponent?
        if(iCooperated) cPayoff += payoff;
        totalPayoff             += payoff;

        agentToPlay++;
    }
    c      += cPayoff;
    total  += totalPayoff;

}

bool RepastHPCDemoAgent::decideToSearch(){
  std::cout<<"Agent Decided Whether it is Worth Searching..." << std::endl;
  std::cout<<"Agent Decided to Search" << std::endl;
  return true;  //for now agent always decides to search

}

void RepastHPCDemoAgent::search(){
  std::cout << "Agent Searching ..."<<std::endl;
  std::cout << "Agent Completed Search"<<std::endl;
}

void RepastHPCDemoAgent::decide(){
  std::cout << "Agent Deciding ..."<<std::endl;
  //paramters are arbitrary for now, will be modified later



  std::cout << "Agent Completed Decision"<<std::endl;
}
