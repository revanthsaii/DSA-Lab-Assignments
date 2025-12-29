#include <stdio.h>
#include <string.h>
void buildLPS(char* pat, int m, int* lps) { int len=0; lps[0]=0; for(int i=1;i<m;) { if(pat[i]==pat[len]) lps[i++]=++len; else if(len) len=lps[len-1]; else lps[i++]=0; } }
int KMP(char* txt, char* pat) { int n=strlen(txt), m=strlen(pat); int lps[m]; buildLPS(pat,m,lps); int i=0,j=0; while(i<n) { if(pat[j]==txt[i]) i++, j++; if(j==m) return i-j; else if(i<n&&pat[j]!=txt[i]) j?j=lps[j-1]:i++; } return -1; }
int main() { char txt[]="ABCCDDAEFGAHI", pat[]="AAB"; printf("\n===== KMP PATTERN MATCHING =====\n"); int res=KMP(txt,pat); printf("Text: %s\nPattern: %s\n",txt,pat); if(res==-1) printf("Pattern not found\n"); else printf("Pattern found at index: %d\n",res); return 0; }
