/* Agent.h */
//based on demo 2 at time of writing

#ifndef AGENT
#define AGENT

#include "repast_hpc/AgentId.h"
#include "repast_hpc/SharedContext.h"
#include "repast_hpc/SharedNetwork.h"
#include "Demo_02_Network.h"

/* Agents */

class DemoAgent{
private:
    repast::AgentId id_;
    
    char mode; //mode choice of agent
    int age;
    int income; //income per year
    int travelDistance;
    int outsideBusTime; //time spent travelling to and from bus
    int inconvenience; //function of preferred and actual arrival time ?
    

public:
    //constructor
    Agent(repast::AgentId id);
    
    //getters for agent
    char getMode();//returns mode choice
    
    
    //setters
    void set(int currentRank,char newMode ) //not sure of need for rank, clarification needed with notes
    
    //ACTION
    char switchMode(newMode) //which mode the agents should switch to (can stay the same)
    
    // agent logic
    void decideToSearch();
    void search(); //if agent decides to reevaluate run this code
    
    // Required Getters don't understand the use of these, need to ask GTA?
    virtual repast::AgentId& getId(){                   return id_;    }
    virtual const repast::AgentId& getId() const {      return id_;    }
    
    
    
    //probably needed but don't really understand so will add in later
    /*
     void play(repast::SharedNetwork<RepastHPCDemoAgent,
     DemoModelCustomEdge<RepastHPCDemoAgent>,
     DemoModelCustomEdgeContent<RepastHPCDemoAgent>,
     DemoModelCustomEdgeContentManager<RepastHPCDemoAgent> > *network);*/
};

//probably don't need to use this

//Serializable agent package
//don't understand use case but it's to do with sharing information

//struct AgentPackage {
//    int id;
//    int rank;
//    int currentRank; //don't understand distiction between this and above
//    char mode;
//
//    AgentPackage(); //for serialiation
//    RepastHPCDemoAgentPackage(int _id, int _rank, int _currentRank, char mode);
//
//    //again don't understand use case, needs to be researched
//     /* For archive packaging */
//    /*
//    template<class Archive>
//    void serialize(Archive &ar, const unsigned int version){
//        ar & id;
//        ar & rank;
//        ar & type;
//        ar & currentRank;
//        ar & c;
//        ar & total;
//    }
//    */
//};


#endif
