
#include "rootEDM.cc"
#include "histManager.h"
#include "PSet.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TMath.h"
#include <algorithm>

class edmJtcAnalyzer: public rootEDMAnalyzer{
		struct histCase{
				TH2D** sig;
				TH2D** sig_pTweighted;
				TH1D** jet_pt;
				TH1D** jet_eta;
				TH1D** jet_phi;
		};
		public : edmJtcAnalyzer(PSet & s);
				 ~edmJtcAnalyzer(){
						 delete hm;
				 };
				 void regHist(TString cap, histCase &hc);
				 void beginJob();
				 void endJob();
				 void analyzer();
				 void fillJetInfo(histCase &hc, float pt, float eta, float phi, float weight);

		public : 
				 // variables to setup the histograms--------------
				 Double_t *jet_pt_bin;
				 int n_jet_pt_bin;
				 std::string * ptlabel;
				 int nPt, nCent;
				 //------------------------------------------------
				 histManager *hm;
				 histCase hc;
				 std::vector<float> *pt=0;
				 std::vector<float> *eta=0;
				 std::vector<float> *phi=0;
				 std::vector<int > *chg=0;
				 std::vector<float> *jtpt=0;
				 std::vector<float> *jteta=0;
				 std::vector<float> *jtphi=0;
};

edmJtcAnalyzer::edmJtcAnalyzer(PSet & s):
		jet_pt_bin(s.getVectorAsArray<Double_t>("jet_pt_bin")),
		n_jet_pt_bin(s.length("jet_pt_bin")-1),
		nPt(s.getPara<int>("npt")),
		nCent(s.getPara<int>("ncent"))
{
		hm = new histManager();
}

void edmJtcAnalyzer::beginJob(){
		auto t1 = handle("genParticleTree");
		auto t2 = handle("ak4GenJetTree_PureWTA");
		t1->SetBranchAddress("pt" , &pt);
		t1->SetBranchAddress("eta", &eta);
		t1->SetBranchAddress("phi", &phi);
		t1->SetBranchAddress("chg", &chg);
		t2->SetBranchAddress("genJtPt" , &jtpt);
		t2->SetBranchAddress("genJtEta", &jteta);
		t2->SetBranchAddress("genJtPhi", &jtphi);
		regHist("JetWTA", hc);
		regHist("JetWTA_leadCand", hc);
}

void edmJtcAnalyzer::endJob(){
		auto wf = TFile::Open("output.root", "recreate");
		wf->cd();
		hm->write();
}


void edmJtcAnalyzer::regHist(TString cap, histCase &hc){
		float ptbins     [7] = {1, 2, 3, 4, 8, 12, 400};
		TString ptLabel  [7] = {"Trk1", "Trk2", "Trk3", "Trk4", "Trk8", "trk12", "Trk400"};
		float centbins   [3] = {0, 60, 200};
		TString centLabel[3] = {"Cent0", "Cent30", "Cent100"};
		int nHistoBinsX = 500;
		int nHistoBinsY = 200;
		hc.sig= new TH2D*[nPt*nCent];
		hc.sig_pTweighted= new TH2D*[nPt*nCent];
		TString tmp, name;
		name = cap;
		for(int i=0; i<nPt; ++i){
				for(int j=0; j<nCent; ++j){
						tmp = centLabel[j]+"_"+centLabel[j+1]+"_"+ptLabel[i]+"_"+ptLabel[i+1];
						hc.sig[i+j*nPt] = hm->regHist<TH2D>(name+Form("_%d_%d",i, j), tmp,
										nHistoBinsX,-5,5,nHistoBinsY,-TMath::Pi()/2,3*TMath::Pi()/2);
						hc.sig_pTweighted[i+j*nPt] = hm->regHist<TH2D>(name+Form("_pTweighted_%d_%d",i, j), tmp,
										nHistoBinsX,-5,5,nHistoBinsY,-TMath::Pi()/2,3*TMath::Pi()/2);
				}
		}
//		const float newbin [21] = {110, 120, 136, 152, 168, 184, 200, 216, 232, 248, 264, 280, 296, 312, 328, 344, 360,
//				380, 400, 432, 500};
//		int nbin = 20;
		hc.jet_pt = new TH1D*[nCent];
		hc.jet_eta = new TH1D*[nCent];
		hc.jet_phi = new TH1D*[nCent];

		for(int j=0; j<nCent; ++j){
				tmp = centLabel[j]+" to "+centLabel[j+1];
				hc.jet_pt[j] = hm->regHist<TH1D>(name+Form("_pt_%d",j), tmp, n_jet_pt_bin, jet_pt_bin);
				hc.jet_eta[j] = hm->regHist<TH1D>(name+Form("_eta_%d",j), tmp, 100, -2.0, 2.0);
				hc.jet_phi[j] = hm->regHist<TH1D>(name+Form("_phi_%d",j), tmp, 72, -TMath::Pi(), TMath::Pi());
		}
}

void edmJtcAnalyzer::fillJetInfo(histCase &hc, float pt, float eta, float phi, float weight){
        for(int j=0; j<nCent; ++j){
                hc.jet_pt[j] ->Fill(pt, weight);
                hc.jet_eta[j]->Fill(eta,weight);
                hc.jet_phi[j]->Fill(phi,weight);
        }
}

void edmJtcAnalyzer::analyzer(){
		for(auto i = 0; i<jtpt->size(); ++i){
				//int leadj = std::max_element(pt.begin(), pt.end()) - pt.begin();
				for(auto j=0; j<pt->size(); ++j){
						
				}
		}
}
