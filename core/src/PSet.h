
#ifndef PSet_cpp
#define PSet_cpp
#include "any.hpp"
#include <unordered_map>
//create or set a parameter named pt with initial value 10 : setPara("pt", 10)
//get a exist parameter named pt : getPara("pt")
//create a new parameter named pt with inital value 10 : addPara("pt", 10)
class PSet{
		public: 
				PSet(){};
				PSet(const char * name) : set_name(name){};
				~PSet(){
						for(auto it = vtable.begin(); it!= vtable.end(); ++it){
								//(*it).second->clear();
								//swap with an empty vector will free the memory of the vector
								std::vector<any>().swap(*((*it).second));
						}
				}
				bool exists(std::string name){
						return  table.find(name) == table.end() ? 0 : 1;
				}
				bool existsV(std::string name){
						return  vtable.find(name) == vtable.end() ? 0 : 1;
				}
				template <typename T>
						bool addPara(const char* pname, const T & val){
								if(exists(pname)){
										std::cout<<"parameter: "<<pname<<" exists in the Set"<<endl;
										return 0;
								}
								table[pname] = any(T(val));
								return 1;
						}
				template <typename T>
						bool insertVPara(const char* pname, const T & val){
								if(!existsV(pname)){
										vtable[pname] = new std::vector<any>();
								}
								vtable[pname]->push_back(any(T(val)));
								return 1;
						}
				template <typename T>
						bool setPara(const char* pname, const T & val){
								table[pname] = any(T(val));
								return 1;
						}
				std::vector<any> * getSetVector(const char* pname){
						if(!existsV(pname)) {
								std::cout<<"parameter vector '"<<pname<<"' haven't been defined in the PSet:"<<set_name<<endl;
								return NULL;
						}
						return vtable[pname];
				}

				template <typename T>
						T getVPara(const char * pname, int i){
								if(!existsV(pname)) {
										std::cout<<"parameter vector '"<<pname<<"' haven't been  defined in the PSet:"<<set_name<<endl;
										return NAN;
								}
								if( vtable[pname]->size()<=i) {
										std::cout<<"exceeds the length of parameter vector '"<<pname<<"'->("<<vtable[pname]->size()<<") in "<<set_name<<endl;
										return NAN;
								}
								return any_cast<T>(vtable[pname]->at(i));
						}
				template <typename T>
						T getPara(const char* pname){
								if(!exists(pname)) {
										std::cout<<"parameter '"<<pname<<"' haven't been  defined in the PSet:"<<set_name<<endl;
										return 0;
								}
								return any_cast<T>(table[pname]);
						}

				template <typename T>
						T securePara(const char* pname, T def){
								if(!exists(pname)) {
										std::cout<<"parameter '"<<pname<<"' not defined! using defalut value."<<endl;
										setPara<T>(pname, def);
										return T(def);
								}
								return any_cast<T>(table[pname]);
						}
				PSet* clone(){
						auto cps = new PSet();
						cps->table = table;
						cps->vtable = vtable;
						return cps;
				}
				PSet& operator=(const PSet & rhs){
						set_name = rhs.set_name;
						table = rhs.table;
						vtable = rhs.vtable;
						return (*this);
				};
		public: 
				std::string set_name="";
				std::unordered_map<std::string, any> table;
				std::unordered_map<std::string, std::vector<any>*> vtable;
};

#endif
