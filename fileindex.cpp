#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
 #endif

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <windows.h>
#include <algorithm>
using namespace std;


void replace_first(
    std::string& s,
    std::string const& toReplace,
    std::string const& replaceWith
) {
    std::size_t pos = s.find(toReplace);
    if (pos == std::string::npos) return;
    s.replace(pos, toReplace.length(), replaceWith);
}


void GetFilesInDirectory(std::vector<string> &out, const string &directory, bool getFolderNames)
{
	 char cCurrentPath[FILENAME_MAX];

 if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
     {
     }
     
    HANDLE dir;
    WIN32_FIND_DATA file_data;
    

    if ((dir = FindFirstFile((directory + "/*.jpg").c_str(), &file_data)) == INVALID_HANDLE_VALUE)
        return; /* No files found */

    do {
        const string file_name = file_data.cFileName;
        const string full_file_name = directory + "/" + file_name;
        const bool is_directory = ((file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0);

        if (file_name[0] == '.')
            continue;

        if (is_directory && !getFolderNames)
            continue;
string s =full_file_name;
        	s = s.substr(2, s.size()-1);
    	s = s.substr(0, s.size()-4);
    	s+=".txt";
    	 out.push_back(s);
    } while (FindNextFile(dir, &file_data));

    FindClose(dir);
}


string backward(string filename){
char ch = '\\';
size_t found = filename.find_last_of(ch);
string f =  filename.substr (found+1,filename.size());	 
vector<string> files;
    GetFilesInDirectory(files, ".", true);
    int i = 0;
    for(i=0; i < files.size(); i++ ) {
if (files[i]==f){break;}
}
    
if (i>0){filename=files[i-1];}
// MessageBox(0, f.c_str(), filename.c_str(), 0);
return 	filename;
}


string forward(string filename){	
char ch = '\\';
size_t found = filename.find_last_of(ch);
string f =  filename.substr (found+1,filename.size());	 
vector<string> files;
    GetFilesInDirectory(files, ".", true);
    int i = 0;
    for(i=0; i < files.size(); i++ ) {
if (files[i]==f){break;}
}
    
if (i<files.size()-1){filename=files[i+1];}	
// MessageBox(0, f.c_str(), filename.c_str(), 0);
return 	filename;
}


void creategentxt(){
std::ofstream fs2("__finlist.txt"); 
    if(!fs2)
    {
    }    
string original2 = "я\n"; //save as ANSI cp1251
string ConvertUTF8ToCP1251(const std::string& str);
string cp12512 = ConvertUTF8ToCP1251(original2);
fs2<<cp12512;
    fs2.close();    	
	
vector<string> files;
vector<string> list;
    GetFilesInDirectory(files, ".", true);
    int i = 0;
    for(i=0; i < files.size(); i++ ) {//
string filename = files[i];  
string imgname="";
bool FileExists(const char* filename);   
bool z = 	FileExists(filename.c_str());
if (!z){
//MessageBox(0, "hi", filename.c_str(), 0);	
	imgname  = filename.substr(0, filename.size()-4);
imgname+=".jpg";
std::ofstream fs(filename); 
    if(!fs)
    {
    }    
string original = "я\n"; //save as ANSI cp1251
string ConvertUTF8ToCP1251(const std::string& str);
string cp1251 = ConvertUTF8ToCP1251(original);
fs<<cp1251+imgname+"\n\n\n\n99\n\n\n\n\n\n";
    fs.close();       
}

vector<string> arr;	
ifstream file(filename);

if (file.is_open()) {
	     					
    std::string line;
    while (std::getline(file, line)) {
        line.c_str();
  string delim("\n");
  size_t prev = 0;
  size_t next;
  size_t delta3 = delim.length();
  while( ( next = line.find( delim, prev ) ) != string::npos ){
    arr.push_back( line.substr( prev, next-prev ) );
    prev = next + delta3;
  }
arr.push_back( line.substr(prev ) );
    }
    file.close();
}
 imgname =arr[1];
string address = arr[2];
string name = arr[3];
string defect = arr[4];
string prior = arr[5];
if (prior.empty()  ) {prior="0";}
string imgname0 = arr[6];
if (imgname0.empty()  ) {imgname0="tttphotoholder";}
string bonus = arr[7];
string num = arr[8];
string rname =arr[9];
string datep = arr[10];

string fin = prior+'\t'+imgname +'\t' +imgname0 +'\t'+"rrrtextholder"+'\t' + address+' '+defect+' '+bonus ;
if (prior!="0"){ list.push_back (fin); }
//MessageBox(0, fin.c_str(), "hh", 0);	
}//	

sort(list.begin(), list.end()); 

int point =1;
string ConvertUTF8ToCP1251(const std::string& str);
string pointstr = ConvertUTF8ToCP1251("Пункт ");
std::ofstream outfile;
outfile.open("__finlist.txt", std::ios_base::app); 
for (int i = 0; i<list.size();i++){//
//MessageBox(0, list[i].c_str(), "hh", 0);
string j = 	list[i];
if (j.empty()  ){}else{
char ch = '\t';
size_t found = j.find_first_of(ch);
j =  j.substr (found+1,j.size());

if (j.find("tttphotoholder") == std::string::npos && !j.empty()){
//if second photo exist
replace_first(j, "rrrtextholder", "");
replace_first(j, "\t\t", "\t");
		size_t found = j.find_first_of(ch);
		string t2 =  j.substr (found+1,j.size());
		found = t2.find_first_of(ch);
		string text =  t2.substr (found+1,t2.size());
		string img = j;
		replace_first(img, text, "");

j = img+"\t" +pointstr + to_string(point) +": " + text; 
point++;
}else{
//if second photo does not  exist
if (i<list.size()-1){
	string j2 = 	list[i+1];
	if  (j2.find("tttphotoholder") != std::string::npos){
		size_t found = j2.find_first_of(ch);
		string t2 =  j2.substr (found+1,j2.size());
		found = t2.find_first_of(ch);
		string name2 =  t2.substr (0,found);
		replace_first(j, "tttphotoholder", name2);
		size_t pos = j.rfind(ch); 
		string text1 = j.substr(pos+1, j.size());
		text1 = pointstr + to_string(point) +": " + text1; 
		point++;
		size_t pos2 = j2.rfind(ch); 
		string text2 = j2.substr(pos2+1, j2.size());
		text2 = pointstr + to_string(point) +": " + text2; 
		point++;
j =  j.substr (0,pos);
replace_first(j, "rrrtextholder", text1);
j+='\t'+text2;
		list[i+1]="";
		}else							{//single page if after it duo
										size_t pos = j.rfind(ch); 
				string text1 = j.substr(pos+1, j.size());
				string text2 = pointstr + to_string(point) +": " + text1; 
				point++;
				replace_first(j, text1, text2);
										}
	} else		{//last page
				if (j.size()>5){	
				size_t pos = j.rfind(ch); 
				string text1 = j.substr(pos+1, j.size());
				string text2 = pointstr + to_string(point) +": " + text1; 
				point++;
				replace_first(j, text1, text2);
				}}
}

replace_first(j, "tttphotoholder", "");
replace_first(j, "rrrtextholder", "");
outfile << j+"\n"; }
}//
outfile.close();
}