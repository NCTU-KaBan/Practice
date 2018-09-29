#include <stdio.h>
int main(){char s[9],D[11]="~0my3[_p\x7f{";int n,i,j,f,t,w,a,
d[50];for(;scanf("%d",&n)==1;puts("none"+4*f)){for(a=i=0;i<n;
a|=d[i]=w,++i)for(scanf("%s",s),w=j=0;j<=4;++j)if(j-2)w=w<<7|
D[s[j]-'0'];for(f=t=0;t<1440;f=(a&w)?f:(printf(" %02d:%02d"+!
f,t/60,t%60),1),++t)for(i=w=0;i<n;j=(t+i)%1440,w|=(D[j/600]<<
21|D[j/60%10]<<14|D[j/10%6]<<7|D[j%10])^d[i],++i);}return 0;}
