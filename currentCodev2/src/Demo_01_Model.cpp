/* Demo_01_Model.cpp */

#include <stdio.h>
#include <vector>
#include <boost/mpi.hpp>
#include "repast_hpc/AgentId.h"
#include "repast_hpc/RepastProcess.h"
#include "repast_hpc/Utilities.h"
#include "repast_hpc/Properties.h"
#include "repast_hpc/initialize_random.h"

#include "Demo_01_Model.h"

RepastHPCDemoModel::RepastHPCDemoModel(std::string propsFile, int argc, char** argv, boost::mpi::communicator* comm): context(comm){
	props = new repast::Properties(propsFile, argc, argv, comm);
	stopAt = repast::strToInt(props->getProperty("stop.at"));
	countOfAgents = repast::strToInt(props->getProperty("count.of.agents"));
	initializeRandom(*props, comm);
	if(repast::RepastProcess::instance()->rank() == 0) props->writeToSVFile("./output/record.csv");
}


RepastHPCDemoModel::~RepastHPCDemoModel(){
		delete props;
}

void RepastHPCDemoModel::init(){
	int rank = repast::RepastProcess::instance()->rank();

	for(int i = 0; i < countOfAgents; i++){
		repast::AgentId id(i, rank, 0);
		id.currentRank(rank);

	  //temporary just to see if i could set things like this!!
		char mode = 'n';
		int income = 30000;
		int travelDistance = 5;

		int age = repast::Random::instance()->nextDouble() * 100; //assign agetns random (uniform i think) age between 0 and 100

		if(age < 30){ //primative logic for choosing mode by age
			mode = 'b';
		}
		else{
			mode = 'c';
		}

		RepastHPCDemoAgent* agent = new RepastHPCDemoAgent(id,age,mode,income,travelDistance); //adds agents with type b for bike
		context.addAgent(agent);

	}
}

void RepastHPCDemoModel::doSomething(){
	std::vector<RepastHPCDemoAgent*> agents;
	context.selectAgents(countOfAgents, agents);
	std::vector<RepastHPCDemoAgent*>::iterator it = agents.begin();

//	std::cout << "Rank " << repast::RepastProcess::instance()->rank() << " is doing something: " << repast::Random::instance()->nextDouble() << std::endl;

	while(it != agents.end()){
		std::cout << (*it)->getId() << " Age: " <<(*it)->getAge() << " Mode: " << (*it)->getMode()<< " Income: " << (*it)->getIncome()<<" Travel distance: " << (*it)->getTravelDistance() << endl; //print ID and mode

//agent decsion fuzzy logic
		if ((*it)->decideToSearch()) {
			(*it)->search();
			(*it)->decide();
		}

//from demo
		(*it)->play(&context);
		it++;
    }
		std::cout << std::endl;
}

void RepastHPCDemoModel::initSchedule(repast::ScheduleRunner& runner){
	runner.scheduleEvent(1, 1, repast::Schedule::FunctorPtr(new repast::MethodFunctor<RepastHPCDemoModel> (this, &RepastHPCDemoModel::doSomething)));
	runner.scheduleEndEvent(repast::Schedule::FunctorPtr(new repast::MethodFunctor<RepastHPCDemoModel> (this, &RepastHPCDemoModel::recordResults)));
	runner.scheduleStop(stopAt);
}

void RepastHPCDemoModel::recordResults(){
	if(repast::RepastProcess::instance()->rank() == 0){
		props->putProperty("Result","Passed");
		std::vector<std::string> keyOrder;
		keyOrder.push_back("RunNumber");
		keyOrder.push_back("stop.at");
		keyOrder.push_back("Result");
		props->writeToSVFile("./output/results.csv", keyOrder);
	}
}
