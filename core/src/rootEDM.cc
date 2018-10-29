
#include "TFile.h"
#include "TTree.h"
#include "rootEDM.h"
//global pointer:
rootEDMFrame * _edmFrame = 0;

TFile* rootEDMFrame::open(const char * f){
		_infile = TFile::Open(f);
		return _infile;
}

TTree* rootEDMFrame::regTree(const char* tn){
		if(forest.find(tn) == forest.end()){
		  	forest[tn]= (TTree*) _infile->Get(tn);
		}
		return forest[tn];
}

TTree* rootEDMAnalyzer::handle(const char* t){
		return _edmFrame->regTree(t);
}

void rootEDMFrame::addAnalyzer(rootEDMAnalyzer * ana){
		_analyzer.push_back(ana);
}

void rootEDMFrame::loopEvent(){
		_edmFrame = this;
		if( _analyzer.size() != 0 )
			   for(auto i =  _analyzer.begin(); i!=_analyzer.end(); ++i){
					   (*i)->beginJob();
			   }
		if( forest.size() == 0) return;
		Long64_t nevt = (*forest.begin()).second->GetEntries();
		if( EventMax == -1 ) EventMax = nevt;
		_infile->cd();
		TTree* t = (TTree*)_infile->Get("genParticleTree");
		for(Long64_t ievt=0; ievt< EventMax ; ++ievt){
				for(auto i= forest.begin(); i!= forest.end(); ++i) {
						(*i).second->GetEntry(ievt); 
				}
				if( _analyzer.size() != 0 )
						for(auto i =  _analyzer.begin(); i!=_analyzer.end(); ++i){
								(*i)->body();
						}
		}
}


