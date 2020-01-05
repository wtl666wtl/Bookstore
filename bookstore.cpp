#include <bits/stdc++.h>
using namespace std;
int main() {
	ofstream file_name("1.in",ofstream::out|ofstream::binary);
	char orz[101];
	orz[0]='a';orz[1]='c';orz[2]='\0';
	file_name.write((char*)(orz),sizeof(orz));
	file_name.close(); 
}
