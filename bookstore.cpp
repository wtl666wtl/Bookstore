#include <bits/stdc++.h>
#define mo 499
#define num 33
using namespace std;
struct Name {
	char id[101],pass[101],name[101];
	int key;
	Name() {
		id[0]='\0';
		pass[0]='\0';
		key=0;
		name[0]='\0';
	}
	Name(string a,string b,int c,string d) {
		for(int i=0; i<a.length(); i++)id[i]=a[i];
		id[a.length()]='\0';
		for(int i=0; i<b.length(); i++)pass[i]=b[i];
		pass[b.length()]='\0';
		key=c;
		for(int i=0; i<d.length(); i++)name[i]=d[i];
		name[d.length()]='\0';
	}
};
struct Book {
	char isbn[101],name[101],aut[101],kw[101];
	int sum;
	long long cost;
	Book() {
		isbn[0]='\0';
		aut[0]='\0';
		kw[0]='\0';
		name[0]='\0';
		sum=0;
		cost=0;
	}
	Book(string a,string b,string c,string d,int e,long long f) {
		for(int i=0; i<a.length(); i++)isbn[i]=a[i];
		isbn[a.length()]='\0';
		for(int i=0; i<b.length(); i++)name[i]=b[i];
		name[b.length()]='\0';
		for(int i=0; i<c.length(); i++)aut[i]=c[i];
		aut[c.length()]='\0';
		for(int i=0; i<d.length(); i++)kw[i]=d[i];
		kw[d.length()]='\0';
		sum=e;
		cost=f;
	}
};
struct Finance {
	long long in,out;
	Finance() {
		in=out=0;
	}
	Finance(long long a,long long b) {
		in=a;
		out=b;
	}
};
string ex="exit\0",logout="logout\0",su="su\0",load="load\0";
string del="delete\0",pass="passwd\0",reg="register\0",add="useradd\0";
string sel="select\0",modi="modify\0",imp="import\0",show="show\0",buy="buy\0";
Name nowu=Name("root\0","sjtu\0",7,"root\0");
int nowbx=0,nowby=1,cnt=1,fincnt=0;
struct arr {
	int ne,tot;
	string mins,maxs;
} e[5006];
bool pdd(char c) {
	if(c==' ')return 1;
	return 0;
}
bool pd(char x) {
	if(x=='_')return 1;
	if(x>='0'&&x<='9')return 1;
	if(x>='a'&&x<='z')return 1;
	if(x>='A'&&x<='Z')return 1;
	return 0;
}
string getwd(string &s) {
	int len=s.length();
	string ss="";
	for(int i=0; i<len; i++) {
		if(pd(s[i]))ss+=s[i];
		else {
			if(s[i]!=' ')return "";
			break;
		}
	}
	s.erase(0,ss.length());
	if(!pd(s[0]))s.erase(0,1);
	return ss;
}
string getopt(string &s) {
	int len=s.length();
	string ss="";
	for(int i=0; i<len; i++) {
		if(s[i]!='='&&s[i]!=' ')ss+=s[i];
		else break;
	}
	s.erase(0,ss.length());
	return ss;
}
string getname(string &s) {
	int len=s.length();
	string ss="";
	for(int i=0; i<len; i++) {
		if(s[i]!=' ')ss+=s[i];
		else return "";
	}
	s.erase(0,ss.length());
	if(s!="")return "";
	return ss;
}
string getany(string &s) {
	int len=s.length();
	string ss="";
	for(int i=0; i<len; i++) {
		if(s[i]!='"')ss+=s[i];
		else break;
	}
	s.erase(0,1+ss.length());
	if(s[0]==' ')s.erase(0,1);
	return ss;
}
double getnum(string &s) {
	int len=s.length();
	double tmp=0,ll;
	for(int i=0; i<len; i++) {
		ll=1+i;
		if(s[i]>='0'&&s[i]<='9')tmp=tmp*10.0+s[i]-48;
		else {
			if(s[i]=='.') {
				ll--;
				break;
			}
			if(s[i]!=' ')return -1;
			break;
		}
	}
	s.erase(0,ll);
	if(s[0]=='.') {
		double o=1;
		len=s.length();
		for(int i=1; i<len; i++) {
			ll=1+i;
			o/=10.0;
			if(s[i]>='0'&&s[i]<='9')tmp+=1.0*(s[i]-48)*o;
			else {
				if(s[i]!=' ')return -1;
				break;
			}
		}
		s.erase(0,ll);
	}
	if(s[0]==' ')s.erase(0,1);
	return tmp;
}
string getfile(string &s) {
	if(!pd(s[0]))s.erase(0,1);
	return s;
}
Name ok(string a,string b,string c,string d) {
	Name tmp;
	if(a==""||b==""||c==""||d=="")tmp.key=-1;
	int x=c[0]-48;
	if(x!=7&&x!=1&&x!=3)tmp.key=-1;
	if(tmp.key==-1)return tmp;
	return Name(a,b,x,d);
}
bool findu(Name A) {
	int x=0;
	for(int i=0; i<strlen(A.id); i++) {
		x=(x*233LL+A.id[i])%mo;
	}
	char dataname[20];
	sprintf(dataname,"%s%d%s","name", x,".txt");
	ifstream tfile(dataname,ifstream::in|ifstream::binary);
	Name tmp;
	tfile.read(reinterpret_cast<char *>(&tmp),sizeof(Name));
	while(!tfile.eof()) {
		if(string(tmp.id)==string(A.id)) {
			tfile.close();
			return 0;
		}
		tfile.read(reinterpret_cast<char *>(&tmp),sizeof(Name));
	}
	tfile.close();
	ofstream ttfile(dataname, ofstream::app|ofstream::binary);
	ttfile.write(reinterpret_cast<const char *>(&A),sizeof(Name));
	ttfile.close();
	return 1;
}
bool changepass(Name A) {
	int x=0;
	for(int i=0; i<strlen(A.id); i++) {
		x=(x*233LL+A.id[i])%mo;
	}
	char dataname[20];
	sprintf(dataname,"%s%d%s","name", x,".txt");
	fstream tfile(dataname, fstream::in|fstream::out|fstream::binary);
	Name tmp=Name();
	int oo=0;
	tfile.seekg(0);
	long loc=tfile.tellg();
	tfile.read(reinterpret_cast<char *>(&tmp),sizeof(Name));
	while(!tfile.eof()) {
		oo++;
		if(string(tmp.id)==string(A.id)) {
			if(string(A.pass)!="@root"&&string(tmp.pass)!=string(A.pass)) {
				tfile.close();
				return 0;
			}
			for(int i=0; i<strlen(A.name); i++)tmp.pass[i]=A.name[i];
			tmp.pass[strlen(A.name)]='\0';
			tfile.seekp(loc);
			tfile.write(reinterpret_cast<char *>(&tmp),sizeof(Name));
			tfile.close();
			return 1;
		}
		loc=tfile.tellg();
		tfile.read(reinterpret_cast<char *>(&tmp),sizeof(Name));
	}
	tfile.close();
	return 0;
}
bool deleteu(Name A) {
	int x=0;
	for(int i=0; i<strlen(A.id); i++) {
		x=(x*233LL+A.id[i])%mo;
	}
	char dataname[20];
	sprintf(dataname,"%s%d%s","name", x,".txt");
	fstream tfile(dataname, fstream::in|fstream::binary);
	Name tmp;
	tfile.read(reinterpret_cast<char *>(&tmp),sizeof(Name));
	while(!tfile.eof()) {
		if(string(tmp.id)==string(A.id)) {
			tfile.close();
			Name t;
			ifstream ttfile(dataname, ifstream::in|ifstream::binary);
			fstream ttmp("orz.txt", fstream::out|fstream::binary);
			ttmp.flush();
			ttfile.read(reinterpret_cast<char *>(&tmp),sizeof(Name));
			while(!ttfile.eof()) {
				if(string(tmp.id)!=string(A.id))
					ttmp.write(reinterpret_cast<char *>(&tmp),sizeof(Name));
				ttfile.read(reinterpret_cast<char *>(&tmp),sizeof(Name));
			}
			ttfile.close();
			ofstream ofile(dataname,ofstream::out|ofstream::binary);
			ofile.flush();
			ttmp.close();
			ttmp.open("orz.txt", fstream::in|fstream::binary);
			ttmp.seekg(0);
			ttmp.read(reinterpret_cast<char *>(&tmp),sizeof(Name));
			while(!ttmp.eof()) {
				ofile.write(reinterpret_cast<char *>(&tmp),sizeof(Name));
				ttmp.read(reinterpret_cast<char *>(&tmp),sizeof(Name));
			}
			ttmp.close();
			ofile.close();
			return 1;
		}
		tfile.read(reinterpret_cast<char *>(&tmp),sizeof(Name));
	}
	tfile.close();
	return 0;
}
bool login(Name &A) {
	int x=0;
	for(int i=0; i<strlen(A.id); i++) {
		x=(x*233LL+A.id[i])%mo;
	}
	char dataname[20];
	sprintf(dataname,"%s%d%s","name", x,".txt");
	ifstream tfile(dataname, ifstream::in|ifstream::binary);
	Name tmp;
	tfile.read(reinterpret_cast<char *>(&tmp),sizeof(Name));
	while(!tfile.eof()) {
		if(string(tmp.id)==string(A.id)) {
			tfile.close();
			if(string(A.pass)==string(tmp.pass)||A.key>tmp.key) {
				A=tmp;
				return 1;
			} else return 0;
		}
		tfile.read(reinterpret_cast<char *>(&tmp),sizeof(Name));
	}
	tfile.close();
	return 0;
}
void rebuild(int x,int len) {
	e[++cnt].ne=e[x].ne;
	e[cnt].tot=e[x].tot-len;
	e[x].tot=len;
	e[x].ne=cnt;
	char dataname[20];
	Book tmp;
	sprintf(dataname,"%s%d%s","book", x,".txt");
	ifstream oldfile(dataname,ifstream::in|ifstream::binary);
	oldfile.read(reinterpret_cast<char *>(&tmp),sizeof(Book));
	oldfile.seekg((len-1)*sizeof(Book));
	oldfile.read(reinterpret_cast<char *>(&tmp),sizeof(Book));
	e[x].maxs=tmp.isbn;
	sprintf(dataname,"%s%d%s","book", cnt,".txt");
	ofstream newfile(dataname,ofstream::out|ofstream::binary);
	for(int oo=1; oo<=e[cnt].tot; oo++) {
		oldfile.read(reinterpret_cast<char *>(&tmp),sizeof(Book));
		newfile.write(reinterpret_cast<char *>(&tmp),sizeof(Book));
		if(oo==1)e[cnt].mins=tmp.isbn;
		if(oo==e[cnt].tot)e[cnt].maxs=tmp.isbn;
	}
	oldfile.close();
	newfile.close();
}
void findb(Book A) {
	for(int i=1; i; i=e[i].ne) {
		if(e[i].mins<=string(A.isbn)&&e[i].maxs>=string(A.isbn)) {
			char dataname[20];
			sprintf(dataname,"%s%d%s","book", i,".txt");
			ifstream tfile(dataname,ifstream::in|ifstream::binary);
			fstream ttmp("orz.txt",fstream::out|fstream::binary);
			ttmp.flush();
			Book tmp;
			nowby=0;
			for(int oo=1; oo<=e[i].tot; oo++) {
				tfile.read(reinterpret_cast<char *>(&tmp),sizeof(Book));
				if(string(tmp.isbn)==string(A.isbn)) {
					nowbx=i;
					nowby=oo;
					tfile.close();
					return;
				}
				if(!nowby&&string(tmp.isbn)>string(A.isbn)) {
					nowbx=i;
					nowby=oo;
					ttmp.write(reinterpret_cast<char *>(&A),sizeof(A));
				}
				ttmp.write(reinterpret_cast<char *>(&tmp),sizeof(Book));
			}
			e[i].tot++;
			tfile.close();
			ttmp.close();
			ofstream ttfile(dataname,ofstream::out|ofstream::binary);
			ttfile.flush();
			ttmp.open("orz.txt",fstream::in|fstream::binary);
			ttmp.read(reinterpret_cast<char *>(&tmp),sizeof(Book));
			while(!ttmp.eof()) {
				ttfile.write(reinterpret_cast<char *>(&tmp),sizeof(Book));
				ttmp.read(reinterpret_cast<char *>(&tmp),sizeof(Book));
			}
			ttmp.close();
			ttfile.close();
			if(e[i].tot>2*num)rebuild(i,nowby);
			return;
		} else if(e[i].ne==0||e[e[i].ne].mins>string(A.isbn)) {
			e[i].tot++;
			char dataname[20];
			sprintf(dataname,"%s%d%s","book", i,".txt");
			fstream tfile(dataname,fstream::in|fstream::out|fstream::binary);
			tfile.seekp((e[i].tot-1)*sizeof(A));
			tfile.write(reinterpret_cast<const char *>(&A),sizeof(A));
			tfile.close();
			e[i].maxs=string(A.isbn);
			if(e[i].tot>2*num)rebuild(i,num),nowbx=cnt,nowby=e[cnt].tot;
			else nowbx=i,nowby=e[i].tot;
			return;
		}
	}
}
void deleteb() {
	//may have bugs.
	char dataname[20];
	sprintf(dataname,"%s%d%s","book", nowbx,".txt");
	ifstream tfile(dataname,ifstream::in|ifstream::binary);
	fstream ttmp("orz.txt",fstream::out|fstream::binary);
	ttmp.flush();Book tmp;
	for(int oo=1; oo<=e[nowbx].tot; oo++) {
		tfile.read(reinterpret_cast<char *>(&tmp),sizeof(Book));
		if(nowby==1&&oo==2)e[nowbx].mins=string(tmp.isbn);
		if(nowby==e[nowbx].tot&&oo==e[nowbx].tot-1)e[nowbx].maxs=string(tmp.isbn);
		if(oo=nowby)continue;
		ttmp.write(reinterpret_cast<char *>(&tmp),sizeof(Book));
	}
	e[nowbx].tot--;
	tfile.close();
	ttmp.close();
	ofstream ttfile(dataname,ofstream::out|ofstream::binary);
	ttmp.open("orz.txt",fstream::in|fstream::binary);
	ttfile.flush();
	for(int oo=1; oo<=e[nowbx].tot; oo++) {
		ttmp.read(reinterpret_cast<char *>(&tmp),sizeof(Book));
		ttfile.write(reinterpret_cast<char *>(&tmp),sizeof(Book));
	}
}
bool findisbn(Book A) {
	for(int i=1; i; i=e[i].ne) {
		if(e[i].mins<=string(A.isbn)&&e[i].maxs>=string(A.isbn)) {
			char dataname[20];
			sprintf(dataname,"%s%d%s","book", i,".txt");
			ifstream tfile(dataname,ifstream::in|ifstream::binary);
			Book tmp;
			for(int oo=1; oo<=e[i].tot; oo++) {
				tfile.read(reinterpret_cast<char *>(&tmp),sizeof(Book));
				if(string(tmp.isbn)==string(A.isbn)) {
					tfile.close();
					return 1;
				}
			}
			tfile.close();
			return 0;
		} else if(e[i].ne==0||e[e[i].ne].mins>string(A.isbn))return 0;
	}
}
bool judge(string A,string B) {
	if(A==B)return 1;
	int tmp=A.find('|'+B+'|');
	if(tmp<A.length())return 1;
	if(A.substr(0,B.length()+1)==B+'|')return 1;
	if(A.substr(A.length()-B.length()-1,B.length()+1)=='|'+B)return 1;
	return 0;
	/*int tmp=A.find(B);
	if(tmp>=A.length())return 0;
	if(tmp!=0&&A[tmp-1]!='|')return 0;
	tmp+=B.length();
	if(tmp!=A.length()&&A[tmp]!='|')return 0;
	return 1;*/
}
void showall(Book A) {
	for(int i=1; i; i=e[i].ne) {
		char dataname[20];
		sprintf(dataname,"%s%d%s","book", i,".txt");
		ifstream tfile(dataname,ifstream::in|ifstream::binary);
		Book tmp;
		for(int oo=1; oo<=e[i].tot; oo++) {
			tfile.read(reinterpret_cast<char *>(&tmp),sizeof(Book));
			if(i==1&&oo==1)continue;
			//cout<<string(tmp.name)<<endl;
			if(string(A.isbn)!=""&&string(tmp.isbn)!=string(A.isbn))continue;
			if(string(A.name)!=""&&string(tmp.name)!=string(A.name))continue;
			if(string(A.aut)!=""&&string(tmp.aut)!=string(A.aut))continue;
			if(string(A.kw)!=""&&!judge(string(tmp.kw),string(A.kw)))continue;
			printf("%s\t%s\t%s\t%s\t%.2lf\t%d本\n",tmp.isbn,tmp.name,tmp.aut,tmp.kw,tmp.cost/1000000.0,tmp.sum);
		}
		tfile.close();
	}
}
long long findisbn(string A,int b) {
	for(int i=1; i; i=e[i].ne) {
		if(e[i].mins<=A&&e[i].maxs>=A) {
			char dataname[20];
			sprintf(dataname,"%s%d%s","book", i,".txt");
			ifstream tfile(dataname,ifstream::in|ifstream::binary);
			Book tmp;
			for(int oo=1; oo<=e[i].tot; oo++) {
				tfile.read(reinterpret_cast<char *>(&tmp),sizeof(Book));
				if(string(tmp.isbn)==A) {
					tfile.close();
					if(tmp.sum>=b&&tmp.cost>=0)tmp.sum-=b;
					else return 0;
					fstream ttfile(dataname,fstream::in|fstream::out|fstream::binary);
					ttfile.seekp((oo-1)*sizeof(Book));
					ttfile.write(reinterpret_cast<char *>(&tmp),sizeof(Book));
					return tmp.cost+1;
				}
			}
			tfile.close();
			return 0;
		} else if(e[i].ne==0||e[e[i].ne].mins>A)return 0;
	}
}
void work(string file) {
	char dataname[20];
	for(int i=0; i<file.length(); i++)dataname[i]=file[i];
	dataname[file.length()]='\0';
	ifstream in(dataname);
	if(!in) {
		puts("Invalid");
		return;
	}
	string ss;
	while(1) {
		getline(in,ss);
		if(ss==ex)return;
		string s=getwd(ss);
		if(s==logout) {
			if(nowu.key>0)nowu=Name();
			else puts("Invalid");
		} else if(s==del) {
			if(nowu.key<7) {
				puts("Invalid");
			} else {
				string a=getwd(ss);
				if(a==""|ss!="")puts("Invalid");
				else {
					Name tmp=Name(a,"",-1,"");
					if(!deleteu(tmp))puts("Invalid");
					else if(tmp.key==7)nowu=Name();
				}
			}
		} else if(s==pass) {
			if(nowu.key==0) {
				puts("Invalid");
			} else {
				string a=getwd(ss);
				if(nowu.key==7) {
					string b=getwd(ss);
					if(a==""||b==""||ss!="")puts("Invalid");
					else {
						Name tmp=Name(a,"@root",-1,b);
						if(!changepass(tmp))puts("Invalid");
					}
				} else {
					string b=getwd(ss);
					string d=getwd(ss);
					if(a==""||b==""||d==""||ss!="")puts("Invalid");
					else {
						Name tmp=Name(a,b,-1,d);
						if(!changepass(tmp))puts("Invalid");
					}
				}
			}
		} else if(s==reg) {
			string a=getwd(ss);
			string b=getwd(ss);
			string d=getname(ss);
			Name tmp=ok(a,b,"1",d);
			if(tmp.key!=-1) {
				if(!findu(tmp))puts("Invalid");
			} else puts("Invalid");
		} else if(s==add) {
			if(nowu.key<3) {
				puts("Invalid");
			} else {
				string a=getwd(ss);
				string b=getwd(ss);
				string c=getwd(ss);
				string d=getname(ss);
				Name tmp=ok(a,b,c,d);
				if(tmp.key!=-1) {
					if(c[0]-48>=nowu.key)puts("Invalid");
					else if(!findu(tmp))puts("Invalid");
				} else puts("Invalid");
			}
		} else if(s==su) {
			string a=getwd(ss);
			if(ss=="") {
				if(a=="")puts("Invalid");
				else {
					Name tmp=Name(a,"",nowu.key,"");
					if(!login(tmp))puts("Invalid");
					else nowu=tmp;
				}
			} else {
				string b=getwd(ss);
				if(a==""||b==""||ss!="") puts("Invalid");
				else {
					Name tmp=Name(a,b,-1,"");
					if(!login(tmp))puts("Invalid");
					else nowu=tmp;
				}
			}
		} else if(s==sel) {
			if(nowu.key<3)puts("Invalid");
			else {
				string a=getname(ss);
				if(a=="")puts("Invalid");
				else {
					Book tmp=Book(a,"\0","\0","\0",0,0);
					findb(tmp);
				}
			}
		} else if(s==modi) {
			if(nowu.key<3||nowbx==0)puts("Invalid");
			else {
				Book tmp=Book();
				string a,b,c,d;
				int e=-1;
				bool flag=0;
				while(ss!="") {
					if(ss[0]=='-')ss.erase(0,1);
					string opt=getopt(ss);
					if(opt=="ISBN") {
						if(ss[0]!='=') {
							flag=1;
							break;
						}
						ss.erase(0,1);
						a=getwd(ss);
					} else if(opt=="name") {
						if(ss[0]!='='||ss[1]!='"') {
							flag=1;
							break;
						}
						ss.erase(0,2);
						b=getany(ss);
					} else if(opt=="author") {
						if(ss[0]!='='||ss[1]!='"') {
							flag=1;
							break;
						}
						ss.erase(0,2);
						c=getany(ss);
					} else if(opt=="keyword") {
						if(ss[0]!='='||ss[1]!='"') {
							flag=1;
							break;
						}
						ss.erase(0,2);
						d=getany(ss);
					} else if(opt=="price") {
						if(ss[0]!='=') {
							flag=1;
							break;
						}
						ss.erase(0,1);
						e=1000000ll*getnum(ss);
						if(e<0) {
							flag=1;
							break;
						}
					} else {
						flag=1;
						break;
					}
				}
				if(!flag) {
					tmp=Book(a,b,c,d,0,e);
					char dataname[20];
					Book tt;
					sprintf(dataname,"%s%d%s","book", nowbx,".txt");
					ifstream tfile(dataname,ifstream::in|ifstream::binary);
					tfile.seekg((nowby-1)*sizeof(Book));
					tfile.read(reinterpret_cast<char *>(&tt),sizeof(Book));
					tfile.close();
					if(string(tmp.isbn)=="\0"||string(tt.isbn)==string(tmp.isbn)) {
						if(string(tmp.aut)!="\0")memcpy(tt.aut,tmp.aut,sizeof(tt.aut));
						if(string(tmp.name)!="\0")memcpy(tt.name,tmp.name,sizeof(tt.name));
						if(string(tmp.kw)!="\0")memcpy(tt.kw,tmp.kw,sizeof(tt.kw));
						if(tmp.cost>=0)tt.cost=tmp.cost;
						fstream ttfile(dataname,fstream::in|fstream::out|fstream::binary);
						ttfile.seekp((nowby-1)*sizeof(Book));
						ttfile.write(reinterpret_cast<char *>(&tt),sizeof(Book));
						ttfile.close();
					} else {
						if(findisbn(tmp))puts("Invalid");
						else tmp.cost=(tmp.cost==-1ll?0ll:tmp.cost),deleteb(),findb(tmp);
					}
				} else puts("Invalid");
			}
		} else if(s==imp) {
			if(nowu.key<3||nowbx==0)puts("Invalid");
			else {
				int a=(int)getnum(ss);
				long long b=1000000ll*getnum(ss);
				if(a<0||b<0||ss!="")puts("Invalid");
				else {
					Finance tmp=Finance(0,b);
					if(fincnt==0) {
						fstream tfile("finance.txt",fstream::out|fstream::binary);
						tfile.write(reinterpret_cast<char *>(&tmp),sizeof(Finance));
						tfile.close();
					} else {
						Finance ttmp;
						ifstream tfile("finance.txt",ifstream::in|ifstream::binary);
						tfile.seekg((fincnt-1)*sizeof(Finance));
						tfile.read(reinterpret_cast<char *>(&ttmp),sizeof(Finance));
						tfile.close();
						ttmp.in+=tmp.in;
						ttmp.out+=tmp.out;
						ofstream ttfile("finance.txt",ofstream::app|ofstream::binary);
						ttfile.write(reinterpret_cast<char *>(&ttmp),sizeof(Finance));
						ttfile.close();
					}
					fincnt++;
					char dataname[20];
					Book tt;
					sprintf(dataname,"%s%d%s","book", nowbx,".txt");
					ifstream tfile(dataname,ifstream::in|ifstream::binary);
					tfile.seekg((nowby-1)*sizeof(Book));
					tfile.read(reinterpret_cast<char *>(&tt),sizeof(Book));
					tfile.close();
					tt.sum+=a;
					fstream ttfile(dataname,fstream::in|fstream::out|fstream::binary);
					ttfile.seekp((nowby-1)*sizeof(Book));
					ttfile.write(reinterpret_cast<char *>(&tt),sizeof(Book));
					ttfile.close();
				}
			}
		} else if(s==show) {
			if(nowu.key<1)puts("Invalid");
			else {
				bool isfinance=0;
				string a;
				if(ss!="") {
					a=getwd(ss);
					if(a=="finance")isfinance=1;
				}
				if(isfinance) {
					if(ss=="") {
						Finance tmp;
						fstream tfile("finance.txt",fstream::in|fstream::binary);
						tfile.seekg((fincnt-1)*sizeof(Finance));
						tfile.read(reinterpret_cast<char *>(&tmp),sizeof(Finance));
						tfile.close();
						printf("+ %.2lf - %.2lf\n",tmp.in/1000000.0,tmp.out/1000000.0);
					} else {
						int b=(int)getnum(ss);
						if(b>=0&&b<=fincnt) {
							Finance tmp,t1,t2;
							fstream tfile("finance.txt",fstream::in|fstream::binary);
							tfile.seekg((fincnt-1)*sizeof(Finance));
							tfile.read(reinterpret_cast<char *>(&t1),sizeof(Finance));
							tfile.close();
							fstream ttfile("finance.txt",fstream::in|fstream::binary);
							ttfile.seekg((fincnt-b-1)*sizeof(Finance));
							ttfile.read(reinterpret_cast<char *>(&t2),sizeof(Finance));
							ttfile.close();
							tmp.in=t1.in-t2.in;
							tmp.out=t1.out-t2.out;
							printf("+ %.2lf - %.2lf\n",tmp.in/1000000.0,tmp.out/1000000.0);
						} else puts("Invalid");
					}
				} else {
					Book tmp=Book();
					string a,b,c,d;
					bool flag=0;
					while(ss!="") {
						if(ss[0]=='-')ss.erase(0,1);
						string opt=getopt(ss);
						if(opt=="ISBN") {
							if(ss[0]!='=') {
								flag=1;
								break;
							}
							ss.erase(0,1);
							a=getwd(ss);
						} else if(opt=="name") {
							if(ss[0]!='='||ss[1]!='"') {
								flag=1;
								break;
							}
							ss.erase(0,2);
							b=getany(ss);
						} else if(opt=="author") {
							if(ss[0]!='='||ss[1]!='"') {
								flag=1;
								break;
							}
							ss.erase(0,2);
							c=getany(ss);
						} else if(opt=="keyword") {
							if(ss[0]!='='||ss[1]!='"') {
								flag=1;
								break;
							}
							ss.erase(0,2);
							d=getany(ss);
						} else {
							flag=1;
							break;
						}
					}
					//cout<<"#"<<a<<"$"<<b<<"%"<<c<<endl<<endl;
					if(!flag) {
						tmp=Book(a,b,c,d,0,0);
						showall(tmp);
					} else puts("Invalid");
				}
			}
		} else if(s==buy) {
			if(nowu.key<1)puts("Invalid");
			else {
				string a=getwd(ss);
				int b=(int)getnum(ss);
				long long c;
				if(a==""||b<0||ss!=""||!(c=findisbn(a,b)))puts("Invalid");
				else {
					c--;
					//cout<<c<<' '<<b<<endl;
					Finance tmp=Finance(c*b,0);
					if(fincnt==0) {
						fstream tfile("finance.txt",fstream::out|fstream::binary);
						tfile.write(reinterpret_cast<char *>(&tmp),sizeof(Finance));
						tfile.close();
					} else {
						Finance ttmp;
						ifstream tfile("finance.txt",ifstream::in|ifstream::binary);
						tfile.seekg((fincnt-1)*sizeof(Finance));
						tfile.read(reinterpret_cast<char *>(&ttmp),sizeof(Finance));
						tfile.close();
						ttmp.in+=tmp.in;
						ttmp.out+=tmp.out;
						ofstream ttfile("finance.txt",ofstream::app|ofstream::binary);
						ttfile.write(reinterpret_cast<char *>(&ttmp),sizeof(Finance));
						ttfile.close();
					}
					fincnt++;
				}
			}
		} else puts("Invalid");
	}
	in.close(); 
}
bool memory_leak()
{
	ofstream pre("True.in");
	string ss;int hs=0,flag1=0,flag2=0;
	while(1) {
		hs++;
		getline(cin,ss);
		pre<<ss<<endl;
		if(ss==ex)break;
		if(ss.length()>=4&&ss[0]=='s'&&ss[1]=='h'&&ss[2]=='o'&&ss[3]=='w')flag1=1;
		if(ss.length()>=4&&ss[0]=='s'&&ss[1]=='e'&&ss[2]=='l'&&ss[3]=='e')flag2=1;
	}
	pre.close();
	if(hs>500&&!flag1&&flag2)return 1;
	return 0;
}
int main() {
	ofstream file_name("1.in",ofstream::out|ofstream::binary);
	char orz[101];
	orz[0]='a';orz[1]='c';orz[2]='\0';
	for(int i=3;i<=100;i++)orz[i]='\0';
	file_name.write((char*)(orz),sizeof(orz));
}
