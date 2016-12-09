#include<iostream>
main(){int N,t,r=999,a;for(std::cin>>N;N--;){std::cin>>t;t*t<r*r||t==-r&&a<0?a=r=t:a;}std::cout<<a;}
