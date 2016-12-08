#include <iostream>
main(){int X,Y,x,y;std::cin>>X>>Y>>x>>y;std::string r;for(;1;r=""){if(Y-y<0){r="N";y--;}else if(Y-y>0){r="S";y++;}if(X-x<0){x--;r+="W";}else if(X-x>0){x++;r+="E";}std::cout<<r+"\n";}}
