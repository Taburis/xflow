
class rootEDM { 
		// root event data model base class, used for any class related to root analysis
		public : rootEDM(){};
				 ~rootEDM(){};
				 //					 virtual void begin(const PSet &) = 0;
};


class rootEDMAnalyzer : public rootEDM {
		public : rootEDMAnalyzer (){};
				 ~rootEDMAnalyzer () {};
				 TTree* handle(const char * t);
				 virtual void beginJob() = 0; 
				 virtual void body() = 0; 
				 virtual void end() = 0;
};

class rootEDMFrame : public rootEDM{
		// every edm has to be run with a frame 
		public : rootEDMFrame(){};
				 void loopEvent();
				 TFile* open(const char*);
				 TTree* regTree(const char* t);
				 void addAnalyzer(rootEDMAnalyzer * );
		public :
				 TFile* _infile;
				 Long64_t EventMax = 1;
				 std::vector<rootEDMAnalyzer * > _analyzer;
				 std::vector<void (*)()> begin_seq;
				 std::unordered_map<std::string, TTree*> forest;
};


