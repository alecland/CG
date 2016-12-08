#include <iostream>
main(){int X,Y,x,y;std::cin>>X>>Y>>x>>y;std::string r;for(;1;r=""){if(y>Y){r="N";y--;}else if(Y>y){r="S";y++;}if(x>X){x--;r+="W";}else if(X>x){x++;r+="E";}std::cout<<r+"\n";}}
