main(N){int t,r=999,a;for(scanf("%d",&N);N--;){scanf("%d",&t);if(t*t<r*r||t==-r&&a<0)a=r=t;}printf("%d",a);}
