#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define MAX_CPU_BURST 100
//#define MAX_IO_BURST 100
#define MAX_PROCESS 100

struct process_t {
	int PID;
	int TARQ;
	int PRIO;
	int TNCPU;
	int CPU[MAX_CPU_BURST];
	int IO[MAX_CPU_BURST-1];
} all_process[MAX_PROCESS];

typedef bool (*schedule_t) (process_t *process_list, int process_c);
int string_spliter(string, int*, string);
process_t string_parser(string);

/*
//Algorithm Template
//=============================================================
bool schedule1 (process_t *process_list, int process_c){
	process_t process_local[MAX_PROCESS];
	memcpy (process_local, process_list, MAX_PROCESS);
	cout <<"test3"<<process_list[0].PID<<endl;
	cout <<"test4"<<process_local[0].PID<<endl;
	return true;
}

bool schedule2 (process_t *process_list, int process_c){
	process_t process_local[MAX_PROCESS];
	memcpy (process_local, process_list, MAX_PROCESS);
	process_local[0].PID = 999;
	cout <<"test2"<<process_list[0].PID<<endl;
	cout <<"test1"<<process_local[0].PID<<endl;
	
	return true;
}
//=============================================================
*/

int main(){ 
	ifstream myfile;
	string line;
	string path;
	cout << "Please enter the absolute path of the file: ";
	cin >> path;
	myfile.open(path);
	//myfile<<"Writing this to a file..... \n";
	int line_counter = 0;
	/*
	schedule_t schedule_functinos[] =
	{
		schedule1,
		schedule2
	};
	*/
	if (myfile.is_open()){
		while (myfile.good()){
			getline (myfile,line);
			all_process[line_counter] = string_parser (line);
			line_counter ++;
		}
	}
	myfile.close();
	/*
	schedule_functinos[1] (all_process, line_counter);
	schedule_functinos[0] (all_process, line_counter);
	*/
	for (int i = 0; i< line_counter; i++){
		cout <<"Process: "<<all_process[i].PID<<" ";
		cout <<all_process[i].TARQ<<" ";
		cout <<all_process[i].PRIO<<" ";
		cout <<all_process[i].TNCPU<<endl;
		cout <<"CPU/IO Burst: ";
		for (int j=0; j<all_process[i].TNCPU; j++){
			cout <<all_process[i].CPU[j]<<" ";
			if(!(all_process[i].TNCPU == j+1))
				cout <<all_process[i].IO[j]<<" ";
		}
		cout <<endl;
	}
	cout <<"Press enter to exit"<<endl;
	cin.ignore(); 
    cin.get();
	cout<<"terminating..."<<endl;
	return 0;
}

int string_spliter(string line, int *p_attributes, string delimiter){
	size_t prev = 0, pos;
	int att_count = 0;
	while ((pos = line.find_first_of(delimiter, prev)) != string::npos){
		if (pos > prev){
			string temp_str = line.substr(prev, pos-prev);
			p_attributes[att_count] = atoi(temp_str.c_str());
			att_count++;
		}
		prev = pos + 1;
	}
	return att_count;
}

process_t string_parser(string line){//, process_t *out_process, int p_index){
	int total_att;
	int att[MAX_CPU_BURST*2+3];
	int cpu_c = 0;
	int io_c = 0;
	process_t out_process;
	total_att = string_spliter(line, att, " ");
	out_process.PID = att[0];
	out_process.TARQ = att[1];
	out_process.PRIO = att[2];
	out_process.TNCPU = att[3];
	for (int i = 4; i < total_att; i++){
		if ((i%2) == 0){ 
			out_process.CPU[cpu_c] = att[i];
			cpu_c++;
		}
		else { 
			out_process.IO[io_c] = att[i];
			io_c++;
		}
	}
	return out_process;
	//out_process[p_index].TNCPU = att[3];
}

