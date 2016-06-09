#include "Taula.hh"
#include <algorithm>

using namespace std;


typedef unordered_map<string,int> MSI;
typedef pair<string,int> PSD;  
typedef vector<PSD> VPSD;

bool ordenacio(PSD a, PSD b){
    if(a.second==b.second){
		if(a.first.size()==b.first.size()){
			return a.first<b.first;
		}
		return a.first.size()<b.first.size();
	}
	return a.second>b.second;
}


Taula::Taula(){
}

 
void Taula::afegir_un(string s) {
	if(aparicions_string.find(s)==aparicions_string.end()){
		aparicions_string[s]=1;
		return;
	}
	aparicions_string[s]+=1;
	return;
}

void Taula::replace_strings(string actual, string seguent) {
	if(aparicions_string.find(actual)==aparicions_string.end()) return;
	int auxiliar=aparicions_string[actual];
	aparicions_string.erase(actual);
	if(aparicions_string.find(seguent)==aparicions_string.end()){
		aparicions_string[seguent]=auxiliar;
		bool found=false;
		int i=0;
		while(not found){
			if(freq_string[i].first==actual){
				freq_string[i].first=seguent;
				found=true;
				if(i!=0 and freq_string[i-1].second<=freq_string[i].second){
					int j=i;
					while(j!=0 and ((freq_string[j-1].second<freq_string[i].second) or (freq_string[j-1].second==freq_string[j].second and (freq_string[j-1].first.size()>freq_string[j].first.size() or (freq_string[j-1].first.size()==freq_string[j].first.size() and ((freq_string[j-1].first)>(freq_string[j].first))))))){
						PSD auxiliar;
						auxiliar=freq_string[j-1];
						freq_string[j-1]=freq_string[j];
						freq_string[j]=auxiliar;
						--j;
					}
				}
				if(i!=freq_string.size()-1 and freq_string[i+1].second==freq_string[i].second){
					int j=i;
					while(j!=freq_string.size()-1 and freq_string[j+1].second==freq_string[j].second and (freq_string[j+1].first.size()<freq_string[j].first.size() or (freq_string[j+1].first.size()==freq_string[j].first.size() and ((freq_string[j+1].first) < (freq_string[j].first))))){
						PSD auxiliar;
						auxiliar=freq_string[j+1];
						freq_string[j+1]=freq_string[j];
						freq_string[j]=auxiliar;
						++j;
					}
				}
			}
			++i;
		}
		return;
	}
	aparicions_string[seguent]+=auxiliar;
	int freq;
	bool found=false;
	int i=0;
	while(not found){
		if(freq_string[i].first==actual){
			found=true;
			freq=freq_string[i].second;
			freq_string.erase(freq_string.begin()+i);
		}
		++i;
	}
	found=false;
	i=0;
	while(not found){ 
		if(freq_string[i].first==seguent){
			freq_string[i].second+=freq;
			found=true;
			if(i!=0 and freq_string[i-1].second<=freq_string[i].second){
				int j=i;
				while(j!=0 and ((freq_string[j-1].second<freq_string[j].second) or (freq_string[j-1].second==freq_string[j].second and (freq_string[j-1].first.size()>freq_string[j].first.size() or (freq_string[j-1].first.size()==freq_string[j].first.size() and ((freq_string[j-1].first)>(freq_string[j].first))))))){
					PSD auxiliar;
					auxiliar=freq_string[j-1];
					freq_string[j-1]=freq_string[j];
					freq_string[j]=auxiliar;
					--j;
				}
			}
			if(i!=freq_string.size()-1 and freq_string[i+1].second==freq_string[i].second){
				int j=i;
				while(j!=freq_string.size()-1 and freq_string[j+1].second==freq_string[j].second and (freq_string[j+1].first.size()<freq_string[j].first.size() or (freq_string[j+1].first.size()==freq_string[j].first.size() and ((freq_string[j+1].first)<(freq_string[j].first))))){
					PSD auxiliar;
					auxiliar=freq_string[j+1];
					freq_string[j+1]=freq_string[j];
					freq_string[j]=auxiliar;
					++j;
				}
			}
		}
		++i;
	}
	return;
	
}  

void Taula::crear_vector() {
	freq_string=VPSD(aparicions_string.size());
	int i=0;
	for(auto it:aparicions_string){
		freq_string[i]=PSD(it.first, it.second);
		++i;
	}
	sort(freq_string.begin(), freq_string.end(), ordenacio);
	return;	
}    
  		
void Taula::escriure_taula_freq() {
	for(int i=0; i<freq_string.size(); ++i){
		cout << freq_string[i].first << " " << freq_string[i].second << endl;
	}
}
