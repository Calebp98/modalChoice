/* Model.h */

#ifndef MODEL
#define MODEL

#include <boost/mpi.hpp>
#include "repast_hpc/Schedule.h"
#include "repast_hpc/Properties.h"
#include "repast_hpc/SharedContext.h"
#include "repast_hpc/AgentRequest.h"
#include "repast_hpc/TDataSource.h"
#include "repast_hpc/SVDataSet.h"
#include "repast_hpc/SharedNetwork.h"

#include "Network.h"
#include "Agent.h"

//don't really understand the point of model, will look up later
/* Agent Package Provider */
class AgentPackageProvider {
    
private:
    repast::SharedContext<Agent>* agents;
    
public:
    AgentPackageProvider(repast::SharedContext<Agent>* agentPtr); //constructor
    
    void providePackage(Agent * agent, std::vector<AgentPackage>& out); //what does out do ?
    void provideContent(repast::AgentRequest req, std::vector<AgentPackage>& out);

};


/* Agent Package Receiver */
class AgentPackageReceiver {
    
private:
    repast::SharedContext<Agent>* agents;
    
public:
    
    AgentPackageReceiver(repast::SharedContext<Agent>* agentPtr);
    
    Agent * createAgent(AgentPackage package);//don't understand these two lines
    
    void updateAgent(AgentPackage package);
};

/* Data Collection - collect data from model (e.g. summing agents with particular modal choice)*/
class DataSource_AgentTotals : public repast::TDataSource<int>{
private:
    repast::SharedContext<Agent>* context;
    
public:
    DataSource_AgentTotals(repast::SharedContext<Agent>* c);
    int getData();
};

//need to clarify understanding of this class
class DataSource_AgentCTotals : public repast::TDataSource<int>{
private:
    repast::SharedContext<Agent>* context;
    
public:
    DataSource_AgentCTotals(repast::SharedContext<Agent>* c);
    int getData();
};

class Model{
    //are these public private of global ???
    int stopAt; //lenght of simulation
    int countOfAgents;
    repast::Properties* props;
    repast::SharedContext<Agent> context;
    
    AgentPackageProvider* provider;
    AgentPackageReceiver* receiver;
    
    ModelCustomEdgeContentManager<Agent> edgeContentManager;
    
    repast::SVDataSet* agentValues;
    repast::SharedNetwork<Agent, ModelCustomEdge<Agent>, ModelCustomEdgeContent<Agent>, ModelCustomEdgeContentManager<Agent> >* agentNetwork;
    
public:
    Model(std::string propsFile, int argc, char** argv, boost::mpi::communicator* comm);
    ~Model();
    void init();
    void requestAgents();
    void connectAgentNetwork();
    void cancelAgentRequests();
    void removeLocalAgents();
    void moveAgents();
    void doSomething();
    void initSchedule(repast::ScheduleRunner& runner);
    void recordResults();
    
};

#endif
