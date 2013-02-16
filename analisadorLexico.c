#include <stdio.h>
FILE *fp, *saida;
    
int main(){
	if((fp=fopen("entradaAnalisador","r")) == NULL ) {
		printf("nao foi possivel abri o arquivo\n");
		exit(1);
	}
	if((saida=fopen("saidaAnalisador","w")) == NULL ) {
		printf("nao foi possivel criar o arquivo\n");
		exit(1);
	}
	int apost=1;
	string c="\0";
	string s="\0";
	while (fread(c, sizeof(char), 1, fp) != EOF){
		if((c >='A' && c<='Z') || (c>='a' && c<='z')){
			s += c; 
		}
		else {
			if(c >= '0' && c<='9'){
				s+=c;
			}
			else{
				switch(s){
					case "v":
						s = "";
						fprintf(saida, "<OR,>");
						break;
					case "if":
						s = "";
						fprintf(saida, "<IF,>");]
						break;
					case "in":
						s = "";
						fprintf(saida, "<IN,>");
						break;
					case "out":
						s = "";
						fprintf(saida, "<OUT,>");
						break;
					case "else":
						s = "";
						fprintf(saida, "<ELSE,>");
						break;
					case "1":
						s="";
						fprintf(saida, "<TRUE,>");
						break;
					case "0":
						s="";
						fprintf(saida, "<FALSE,>");
						break;
					default:
						if((s[0] >='A' && s[0]<='Z') || (s[0]>='a' && s[0]<='z')){
							s="";
							fprintf(saida, "<ID,%s>", s);
						}						
				}
				s+=c;
				switch(s){
					case '^': 
						s = "";
						fprintf(saida, "<AND,>");
						break;
					case '\'':
						s = "";
						fprintf(saida, "<NOT,>");
						break;
					case '(':
						s = "";
						fprintf(saida, "<LPARENTS,>");
						break;
					case ')':
						s = "";
						fprintf(saida, "<RPARENTS,>");
						break;
					case '{':
						s = "";
						fprintf(saida, "<LCHAVES,>");
						break;
					case '}':
						s = "";
						fprintf(saida, "<RCHAVES,>");
						break;
					case ';':
						s = "";
						fprintf(saida, "<PONTOVIRGULA,>");
						break;			
					case "<":
					case "<-":
					case "-":
					case ":":
						break;
					case "<->":
						s = "";
						fprintf(saida, "<SESOMENTESE, >");
						break;
					case "->":
						s = "";
						fprintf(saida, "<SE,>");
						break;
					case ":=":
						s = "";
						fprintf(saida, "<IGUAL,>");
						break;
					case "\"":
						if(apost)
							apost=0;
						else 
							apost =1;
						if(apost)
							switch(s){
								case "v":
								case "verdadeiro":
								case "true":
									s="";
									fprintf(saida, "<TRUE,>");
									break;
								case "f":
								case "falso":
								case "false":
									s="";
									fprintf(saida, "<FALSE,>");
									break;

							}
						break;
					
				}
			}
			
		}
	}	
	fclose(fp);
	return 0;
}

