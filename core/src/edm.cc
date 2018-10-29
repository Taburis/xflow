
//#include "PSet.h"
#include "rootEDM.cc"

class tracker : public rootEDMAnalyzer {
		public : tracker(){};
				 void beginJob(){
						 auto t = handle("genParticleTree");
						 auto t2 = handle("ak4GenJetTree_PureWTA");
						 t->SetBranchAddress("pt",&pt);
						 t2->SetBranchAddress("genJtPt",&jtpt);
				 };
				 void body(){cout<<jtpt->size()<<endl;};
				 void end(){};
		public : vector <float > *pt=0;
				 vector <float > *jtpt=0;
};

void edm(){
		//get genParticleTree
		rootEDMFrame * ff = new rootEDMFrame();
		ff->open("/Applications/physPlayGround/Generators/PYTHIA8/bin/output/20181015/part1_CUETP8M1_NEvt10000_DoFlatPthatTrue_FlatPower4p50_PthatMin120p0_PthatMax999999p0_20181015.root");
		tracker * a = new tracker();
		ff->EventMax=10;
		ff->addAnalyzer(a);	
		ff->loopEvent();
}
