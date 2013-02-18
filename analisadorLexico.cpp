#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <fstream>

using namespace std;

int letra(char c){
	if ((c >='A' && c<='Z') || (c>='a' && c<='z') )
			return 1;
	else
		return 0;
}
int numero(char c){
	if(c>='0' && c<='9')
		return 1;
	else 
		return 0;
}

int hash(string c){
	if(c=="(")
		return 1;
		else if(c==")")
			return 2;
		else if(c=="{")
			return 3;
		else if(c=="}")
			return 4;
		else if(c==";")
			return 5;
		else if(c==",")
			return 6;
		else if(c=="^")
			return 7;
		else if(c=="\'")
			return 8;
		else if(c==":=")
			return 9;
		else if(c=="->")
			return 10;
		else if(c=="<->")
			return 11;
		else if(c=="v")
			return 12;
		else if(c=="\"v\"" || c=="1" || c=="\"verdadeiro\"" || c=="\"true\"")
			return 14;
		else if(c=="\"f\"" || c=="0" || c=="\"falso\"" || c=="\"false\"")
			return 15;
		else if(c=="else")
			return 16;
		else if(c=="if")
			return 17;
		else if(c=="out")
			return 18;
		else if(c=="in")
			return 19;
		else if(letra(c[0]))
			return 20;
		//~ else if(*c.begin() =='\"' && c.begin() !=c.end()-1)
			//~ return 0;
		else if(c=="\"" || *c.begin() =='\"')
			return 21;
		else if(c=="-" || c=="<" || c=="<-" || c==":")
			return 22;
		else if(c==" " || c== "\n" || c=="\0" || c=="\t")
			return 23;
	return 0;
}

int main(){
	ifstream entrada("entradaAnalisador.txt"); 
     if (! entrada)
     {
         cout << "Erro abrindo arquivo." << endl;
         return -1;
     } 
     
	char c ='a' ;
	string s ="\0";
	while (entrada.get(c)){
		if(letra(c)){ 
			s += c;
		}
		else {
			if(letra(s[0]) && numero(c) ){
					s+=c;	
			}
			else{
				int a = hash(s);
				switch(a){
					case 12:
						s = "";
						cout << "<OR,>";
						break;
					case 16:
						s = "";
						cout <<  "<ELSE,>";
						break;
					case 17:
						s = "";
						cout << "<IF,>";
						break;
					case 18:
						s = "";
						cout << "<OUT,>";
						break;
					case 19:
						s = "";
						cout << "<IN,>";
						break;
					case 20:
						if((s[0] >='A' && s[0]<='Z') || (s[0]>='a' && s[0]<='z')){
							cout << "<ID,"<< s << ">";
							s="";
						}
						break;
					case 0:
							cout << "eRRO" << endl;
							exit(1);
							break;	
					case 21:
						break;
				}
				
				s+=c;
				a = hash(s);
				switch(a){
					case 1:
						s = "";
						cout << "<LPARENTS,>";
						break;
					case 2:
						s = "";
						cout << "<RPARENTS,>";
						break;
					case 3:
						s = "";
						cout << "<LCHAVES,>";
						break;
					case 4:
						s = "";
						cout << "<RCHAVES,>";
						break;
					case 5:
						s = "";
						cout << "<PONTOVIRGULA,>";
						break;			
					case 6:
						s = "";
						cout << "<VIRGULA,>";
						break;
					case 7: 
						s = "";
						cout << "<AND,>";
						break;
					case 8:
						s = "";
						cout << "<NOT,>";
						break;
					case 9:
						s = "";
						cout << "<IGUAL,>";
						break;
					case 10:
						s = "";
						cout << "<SE,>";
						break;
					case 11:
						s = "";
						cout << "<SESOMENTESE, >";
						break;
					case 14:
						s="";
						cout << "<TRUE,>";
						break;
					case 15:
						s="";
						cout << "<FALSE,>";
						break;		
					case 21:
						if( s.begin() !=s.end()-1){
							cout << "eRRO" << endl;
							exit(1);
						}
						break;
					case 22:
						break;
					case 23:
						s="";
						break;
					case 0:
						cout << "ERRO" << endl;
						exit(1);
						break;	
				}
			}
		}
	}	
	return 0;
}
