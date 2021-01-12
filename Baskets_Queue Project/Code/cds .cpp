#include<bits/stdc++.h>
#include<cstdlib>
#include<pthread.h>
#include<ctime>
#include<ratio>
#include<chrono>
using namespace std;
vector<int>vec[10000];
vector<vector<int>>qu(10000);
int ran;
int lilly1;
void * fun(void * i){
	long ii;
	ii=(long)i;
	int me=vec[ii].size();
	for(int i=0;i<me;i++){
		qu[ii].push_back(vec[ii][i]);
		//vec[ii].erase(vec[ii].begin());
	}
	vec[ii].clear();
//	pthread_exit(NULL);
} 
vector<pair<int,int>>vi;
int flag=0;
void threading(int n){	
	pthread_t threads[n];
	int tmp=0;
	vector<int>th;
	for(int i=0;i<n;i++){
		int me=vec[i].size();
		if(me==0){
	//		cout << i+1 << "th node is completed or pushed completely\n";
			continue;
		}
		flag=1;
		auto rc=pthread_create(&threads[tmp++],NULL, fun ,(void*)i);
		//qu[i].push_back(me1);
		th.push_back(rc);
		cout << i+1 << "th node pushing completed\n";
		//auto rc1=pthread_detach(rc);
	}
	for(auto &rc : th){
		pthread_detach(rc);
	}
//	pthread_exit(NULL);
	//	pthread_exit(NULL);
}
void *fun2(void *i){
	long ii;
	ii=long(i);
	qu[vi[ii].first].erase(find(qu[vi[ii].first].begin(),qu[vi[ii].first].end(),vi[ii].second));
//	pthread_exit(NULL);
}
void threading2(int m){
	pthread_t threads[m];
	int tmp=0;
	vector<int>th;
	for(int i=0;i<m;i++){
		auto rc=pthread_create(&threads[tmp++],NULL,fun2,(void*)i);
		th.push_back(rc);
		cout << "popped " << vi[i].second << " from " << vi[i].first+1 << "node\n";
	//	auto rc1=pthread_detach(rc);
	}
	for (auto &rc:th)
		pthread_detach(rc);
	//pthread_exit(NULL);
}
void *fun3(void *i){
	long ii;
	ii=long(i);
	qu[vi[ii].first].push_back(vi[ii].second);
	//pthread_exit(NULL);
}
void threading3(int m){
	pthread_t threads[m];
	int tmp=0;
	vector<int>th;
	for(int i=0;i<m;i++){
		auto rc=pthread_create(&threads[tmp++],NULL,fun3,(void*)i);
		th.push_back(rc);
		cout << "pushed " << vi[i].second << " into " << vi[i].first+1 << "node\n";
	//	auto rc1=pthread_detach(rc);
	}
	for (auto &rc:th)
		pthread_detach(rc);
	//pthread_exit(NULL);
}
int main(){
	int n;
	using namespace std::chrono;
	cout << "enter no of nodes to be in the queue :\n";
	cin >> n;
	int temp=0;
	int th=0;
	for(int i=0;i<n;i++){
		int m;
		cout << "enter number of elements in " << i+1 << " node followed by the elements\n";
		cin >> m;
		th=max(th,m);
		for(int j=0;j<m;j++){
			int a;
			cin >> a;
			vec[i].push_back(a);
		}
	}
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	cout << "pushing started\n";
	//	for(int i=0;i<pow(10,1);i++) temp++; //delay
	//	cout << "pushing ";
	srand(time(0));
	int l=0;
	cout << "creating " << n <<" threads"<< '\n';
	threading(n);
	for(int i=0;i<pow(10,2);i++) temp++; //delay
		//	pthread_exit(NULL);
	cout << "now the queue is :\n";
	for (int i=0;i<n;i++){
		for(int j=0;j<qu[i].size();j++){
			cout << qu[i][j] <<" ";
		}
		cout << '\n';
	}
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double, std::milli> time_span = t2 - t1;
        cout << "It took me " << time_span.count() << " for the opration\n";
	cout << "enter no of queries :\n";
	int q;
	cin >> q;
	while(q--){
		int m;
		vi.clear();
		string A;
		cout << "enque --> e, deque--> d\n";
		cin >> A;
		if(A=="e"){
			cout << "enter number of elements to be pushed:\n";
			cin >> m;
			cout << "elements followed by the index of the node of element:\n";
			pair<int,int>v;
			for(int i=0;i<m;i++){
				cin >> v.second >> v.first ;
				v.first--;
				vi.push_back(v);
			}
			cout << "pushing starts\n";
			high_resolution_clock::time_point t3 = high_resolution_clock::now();
			threading3(m);
			high_resolution_clock::time_point t4 = high_resolution_clock::now();
			duration<double, std::milli> time_me = t4 - t3;
        		cout << "It took me " << time_me.count() << " for this query\n";
		}
		else {
			cout << "enter no of elements to be pooped :\n";
			cin >> m;
			cout << "elements followed by the index of the node the element:\n";
			pair<int,int>v;
			for(int i=0;i<m;i++){
				cin >> v.second >> v.first;
				v.first--;
				vi.push_back(v);
			}
			cout << "popping starts:\n";
			high_resolution_clock::time_point t3 = high_resolution_clock::now();
			threading2(m);
			high_resolution_clock::time_point t4 = high_resolution_clock::now();
			duration<double, std::milli> time_me = t4 - t3;
        		cout << "It took me " << time_me.count() << " for this query\n";
		}
		for(int i=0;i<pow(10,2);i++) temp++;
		cout << "now the new queue is :\n";
		for (int i=0;i<n;i++){
			for(int j=0;j<qu[i].size();j++){
				cout << qu[i][j] <<" ";
			}
			cout << '\n';
		}
	}
        high_resolution_clock::time_point t5 = high_resolution_clock::now();
        duration<double, std::milli> time_span1 = t5 - t1;
        cout << "It took me " << time_span1.count() << " for total programe including user time\n";
	
	cout << "task completed than you :)\n";
}
