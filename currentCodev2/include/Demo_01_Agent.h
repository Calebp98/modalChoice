/* Demo_01_Agent.h */

#ifndef DEMO_01_AGENT
#define DEMO_01_AGENT

#include "repast_hpc/AgentId.h"
#include "repast_hpc/SharedContext.h"


/* Agents */
class RepastHPCDemoAgent{

private:
    repast::AgentId   id_; // agent id
    double              c; //
    double          total;

		int age; //age of agent
		char mode; //mode of transport that agent is using
		int income; //personal income of agent
		int travelDistance; //distance of agents journey

public:
    RepastHPCDemoAgent(repast::AgentId id);

		RepastHPCDemoAgent(repast::AgentId id, int age, char mode, int income, int travelDistance); //added to set mode
	//RepastHPCDemoAgent(repast::AgentId id, char mode); //added to set mode


    RepastHPCDemoAgent(repast::AgentId id, double newC, double newTotal);

    ~RepastHPCDemoAgent();

    /* Required Getters */
    virtual repast::AgentId& getId(){                   return id_;    }
    virtual const repast::AgentId& getId() const {      return id_;    }

    /* Getters specific to this kind of Agent */
    double getC(){                                      return c;      }
    double getTotal(){                                  return total;  }

		//getters added for searching and decisions
		int getAge(){ 				return age;}
		char getMode(){				return mode;}
		int getIncome(){			return income;}
		int getTravelDistance(){	return travelDistance;}

    /* Setter */
    void set(int currentRank, double newC, double newTotal);

    /* Actions */
    bool cooperate();                                                 // Will indicate whether the agent cooperates or not; probability determined by = c / total
    void play(repast::SharedContext<RepastHPCDemoAgent>* context);    // Choose three other agents from the given context and see if they cooperate or not

		bool decideToSearch();
		void search();
		void decide();
};

#endif
