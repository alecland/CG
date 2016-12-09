main(N){int t,r=999,a;for(scanf("%d",&N);N--;){scanf("%d",&t);t*t<r*r||t==-r&&a<0?a=r=t:a;}printf("%d",a);}
