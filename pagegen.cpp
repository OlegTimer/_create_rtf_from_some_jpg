typedef unsigned int uint;
#define _BSD_SOURCE

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <winsock.h>
#include <windows.h>
#include <string>
#include <locale>
#include <streambuf>
#include <sstream>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <string.h>
using namespace std;

int pagew=600;
int pageh=800;
int s=7;
int letdiv = s*6/5;
int fat =s/10;
int leftmargin=s;
int h=pageh/2-2*s;
int w=leftmargin;
int maxsquarepix = 250;
int gdiRelativeScreenCoordCoeff = 4; //how gdi pixels are 4-6 less, than actual pixels on monitor
int rtfcoeff =30; // 68 max on page to 1 min image on rtf page ; 60 for duo and header 1 and lines 2*1
int rtfcoeffmax=68;
int rtfcoeffduo=60;

int photow = 1024;
int photoh = 768;
int headercount = 1;
int stringinpage=56;
int lettersinstring=58;

void setheadercount(int a){headercount=a;}
int getheadercount(){return headercount;}
int getphotow(){return photow;}
int getphotoh(){return photoh;}
int getpagew(){return pagew;}
int getpageh(){return pageh;}
int maxsquarepixget(){return maxsquarepix;}
int gdiRelativeScreenCoordCoeffget(){return gdiRelativeScreenCoordCoeff;}


char v2a(int c) {
    const char hex[] = "0123456789ABCDEF";
    return hex[c];
}


char *hexlifyn(char *bstr, uint str_len) {
    char *hstr=(char*) malloc((str_len*2)+1);
    memset(hstr,0,(str_len*2)+1);
    char *phstr=hstr;
    for(int i=0; i<str_len;i++) {
        *phstr++ =v2a((bstr[i]>>4)&0x0F);
        *phstr++ =v2a((bstr[i])&0x0F);
    }
    *phstr++ ='\0';
    return hstr;
}


std::string cuttab(std::string const& s) //cuts string from start till first tab
{
    std::string::size_type pos = s.find('\t');
    if (pos != std::string::npos)
    {
        return s.substr(0, pos);
    }
    else
    {
        return s;
    }
}


void pagegen() {
if (headercount<1){headercount=1;}	
// MessageBox(0, to_string(headercount).c_str(), "hh", 0);	//+1 for page num

std::ofstream fs2("__output.txt"); 
    if(!fs2)
    {
    }    
string o = "{\\rtf1 {\\fonttbl {\\f0 Times New Roman;}}\\fs24 \\vя\\v0 \\paperw12240\\paperh15840\\margl720\\margr720\\margt180\\margb180 \\qc ";  
//save as ANSI cp1251
string ConvertUTF8ToCP1251(const std::string& str);
string cp12512 = ConvertUTF8ToCP1251(o);
fs2<<cp12512;
    fs2.close();  
    
std::ofstream outfile;
outfile.open("__output.txt", std::ios_base::app);

int pagenum=1;	
char filename[] = "__finlist.txt"; 
    string myString;
    ifstream myfile;
    myfile.open(filename);

   if(!myfile.is_open()) {
      perror("Error open");
      exit(EXIT_FAILURE);
   }
    while(getline(myfile, myString)) { //read _fin file line by line start
    
if (myString.size()<2) {continue;}
if (pagenum>1){
outfile << "\\page";
}
outfile << "\\i "<<pagenum<<"\\par\\i0";
string getheader();
outfile <<getheader()<<"";
pagenum++;
//create page

string s0 = cuttab(myString); //img1
string s1 = myString.substr(s0.length()+1, myString.length());
string s2 = cuttab(s1); //img2

s1 = myString.substr(s0.length()+s2.length()+2, myString.length());
//MessageBox(0, s1.c_str(), "hh", 0);
int totalstringsperpage = s1.length()/lettersinstring  + headercount+3;
//MessageBox(0, to_string(totalstringsperpage).c_str(), "hh", 0);
// int stringinpage=56; 
int rtfcoeffmaxt = rtfcoeffmax+10;
if (stringinpage<5){rtfcoeffmaxt = rtfcoeffmax; }
if (!s2.empty()  ){ rtfcoeffmaxt= rtfcoeffduo;}

double rtfcoeffd = 1.0*rtfcoeffmaxt * ((stringinpage+4 - totalstringsperpage)/(1.0*stringinpage));
rtfcoeff = (int)rtfcoeffd;
//MessageBox(0, to_string(rtfcoeffd).c_str(), "hh", 0);

string text1= cuttab(s1);
s1 = s1.substr(text1.length()+1, s1.length());
string text2= cuttab(s1);
//MessageBox(0, text2.c_str(), text1.c_str(), 0);
    	 
outfile << "\n{\\pict{\\*}\\wmetafile8\\picw";
outfile << photow/96*254 *rtfcoeff/10;
outfile << "\\pich"; 
outfile << photoh/96*254 *rtfcoeff/10;
outfile << "\\picwgoa"; 
outfile <<  photow/96*144*rtfcoeff/10;
outfile << "\\pichgoa"; 
outfile << photoh/96*144*rtfcoeff/10;
outfile << "\n"; 
    FILE *f = fopen(s0.c_str(), "rb");
    if (f==NULL) return;
    fseek(f, 0, SEEK_END);
    size_t fsize = ftell(f);
    fseek(f, 0, SEEK_SET);
    void *data0 = malloc(fsize + 1);
    memset(data0,0, fsize + 1);
    fread(data0, 1, fsize, f);
    fclose(f);
    char* yourDataStr = hexlifyn((char*)data0, (uint)fsize);
    outfile << yourDataStr;
outfile << " \\sa200\\sl276\\slmult1\\par}";

outfile <<"\n\\par "<<text1;


if (!s2.empty()  ) {  
outfile << "\n  { \\pict{\\*}\\wmetafile8\\picw";
outfile << photow/96*254 *rtfcoeff/10;
outfile << "\\pich"; 
outfile << photoh/96*254 *rtfcoeff/10;
outfile << "\\picwgoa"; 
outfile << photow/96*144*rtfcoeff/10;
outfile << "\\pichgoa"; 
outfile << photoh/96*144*rtfcoeff/10;
outfile << "\n"; 
    FILE *f = fopen(s2.c_str(), "rb");
    if (f==NULL) return;
    fseek(f, 0, SEEK_END);
    size_t fsize = ftell(f);
    fseek(f, 0, SEEK_SET);
    void *data0 = malloc(fsize + 1);
    memset(data0,0, fsize + 1);
    fread(data0, 1, fsize, f);
    fclose(f);
    char* yourDataStr = hexlifyn((char*)data0, (uint)fsize);
    outfile << yourDataStr;
outfile << "\\par \\sa200\\sl276\\slmult1}";
}
outfile <<"\n\\par "<<text2;
   
}//read _fin file line by line end
    
outfile << "\\par \\pard\\sa200\\sl276\\slmult1}";
outfile.close();    
bool FileExists(const char* filename);   
bool z = 	FileExists("__output.rtf");
if (z){remove("__output.rtf");}
rename("__output.txt", "__output.rtf");
//save res
}