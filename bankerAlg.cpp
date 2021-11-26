#include <iostream>
#include <fstream>
using namespace std;


int main(){
	int n, m, i=0, j=0, k=0, num;
	//p0, p1, p2, p3, p4 are processes in this instance
	n = 5; //number of processes
	m = 3; //number of resources
	ifstream in("input.txt");
	int allocated[5][3]; //Allocation matrix for p0, p1, p2, p3, p4 respectively
	int max[5][3]; //Max Matrix for p0, p1, p2, p3, p4 respectively
	int avail[3]; //available resources
	int f[n], ans[n], ind = 0;//f[n] will indicate a spot is taken. ans holds order of processes. ind is index for ans
	if(!in.is_open()){
		cerr<<"Could not open the file - 'input.txt'\n";
		return EXIT_FAILURE;
	}
	while(in >> num){
		for(i=0; i<5; i++){
			for(j=0; j<3; j++){
				allocated[i][j]=num;
				cout<<allocated[i][j];
				in>>num;
			}
			cout<<endl;
		}
		cout<<endl;
		for(i=0; i<5; i++){
			for(j=0; j<3; j++){
				max[i][j] =  num;
				cout<<max[i][j];
				in>>num;
			}
			cout<<endl;
		}
		cout<<endl;
		for(j=0; j<3; j++){
			avail[j]=num;
			cout<<avail[j];
			in>>num;
		}
		cout<<endl;
		break;
	}//input values for allocated, max, and avail;
	in.close();
	for(k=0; k<n; k++)
		f[k] = 0;
	int need[n][m];//matrix for resources needed.
	for(i=0; i<n; i++)
		for(j=0; j<m; j++)
			need[i][j] = max[i][j] - allocated[i][j];//Finds resources needed for each process
	int y=0;
	for(k=0; k<5; k++){
		for(i=0; i<n; i++){
			if(f[i] == 0){

				int flag=0;
				for(j=0; j<m; j++){
					if(need[i][j] > avail[j]){
						flag=1;
						break;//will make process wait if it needs more than what's available
					}
				}

				if(flag==0){
					ans[ind++] = i;//finds order for processes
					for (y=0; y<m; y++)
						avail[y] += allocated[i][y];//returns allocated resources.
					f[i]=1;//indicates spot at i is taken
				}
			}
		}
	}
	cout <<"The following is a SAFE sequence" <<endl;
	for(i=0; i<n-1; i++)
		cout << " P" << ans[i] << " ->";
	cout << " P" << ans[n-1] << endl;
	return (0);                                                                                     
}
