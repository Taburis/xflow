
#include <vector>
#include <unordered_map>
#include <iostream>
#include "TTree.h"

class rootEDM { 
		// root event data model base class, used for any class related to root analysis
		public : rootEDM(){}; ~rootEDM(){};
				 //					 virtual void begin(const PSet &) = 0;
};


class rootEDMAnalyzer : public rootEDM {
		public : rootEDMAnalyzer (){};
				 ~rootEDMAnalyzer () {};
				 TTree* handle(const char * t);
				 virtual void beginJob() = 0; 
				 virtual void analyzer() = 0; 
				 virtual void endJob() = 0;
};

class rootEDMEventFilter : public rootEDM {
		public : rootEDMEventFilter(){};
				 ~rootEDMEventFilter(){};
				 virtual void beginJob() = 0;
				 virtual void endJob() = 0;
				 // convention for the filter:
				 // return 1 means keep the event
				 virtual bool filter() = 0;
};

class rootEDMFrame : public rootEDM{
		// every edm has to be run with a frame 
		public : rootEDMFrame(){};
				 ~rootEDMFrame();
				 void eventLoop();
				 TFile* open(const char*);
				 TTree* regTree(const char* t);
				 void addAnalyzer(rootEDMAnalyzer * );
				 void addEventFilter(rootEDMEventFilter * );
				 void runBeginSection();
				 void runEndSection();
				 void runEventSection();
		public :
				 TFile* _infile;
				 Long64_t EventMax = 1;
				 std::vector<rootEDMAnalyzer * > _analyzer;
				 std::vector<rootEDMEventFilter * > _evtfilter;
				 std::vector<void (*)()> begin_seq;
				 std::unordered_map<std::string, TTree*> _forest;
};


