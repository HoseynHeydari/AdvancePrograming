#include<iostream>
#include<vector>

using namespace std;


void print_vector(vector<int> v) {
	for (int i = 0; i < v.size(); i++)
			cout << (i == 0 ? "" : ",") << v[i];
  cout << endl;
}

void combination(vector<int> input, vector<int>& result) {
  if(input.empty())
    print_vector(result);

  for (int i = 0; i < input.size(); i++) {    
    vector<int> newinput = input;
    vector<int> resultclone = result;

    result.push_back(input[i]);
    newinput.erase(newinput.begin() + i);

    combination(newinput, result);

    result = resultclone;
  }
}

int main(int argc, char* argv[]) {
	int n;
  cin >> n;
  
  if (n < 1) {
    cerr << "invalid input, n should be greater than zero\n"; 
    exit(-1);
  }
	
	vector<int> input, output;
  for (int i = 0; i < n; i++)
    input.push_back(i + 1);
	
	combination(input, output);
}