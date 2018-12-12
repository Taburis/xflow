
#include "ParaSet.h"

ParaSet makePSet_edmJtcDefault(){
		ParaSet st("edmJtcAnalzyer_pset");
		Double_t jetptbin[] = {110, 120, 136, 152, 168, 184, 200, 216, 232, 248, 264, 280, 296, 312, 328, 344, 360, 380, 400, 432, 500};
//		cout<<"size is "<<sizeof(jetptbin)/sizeof(jetptbin[0])<<endl;
		st.setParaVector<Double_t>("jet_pt_bin", sizeof(jetptbin)/sizeof(jetptbin[0]), jetptbin);
		st.setPara<int>("npt", 6);
		st.setPara<int>("ncent", 2);
		return st;
}

