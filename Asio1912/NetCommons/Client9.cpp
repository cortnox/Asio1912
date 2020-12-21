//
//  Client.cpp
//  Asio1912
//
//  Created by Scott Dean on 12/21/20.
//



#include "Ncanetna9.hpp"
//#include <iostream>
//#include "NetCommons.hpp"
//#include "NetMessage.hpp"

enum class customMessage9s : uint32_t
{
    fire9,
    move9
};

int main()
{
    nca9::neta9::message9 <customMessage9s> msg9;
    msg9.hdr9.id = customMessage9s::fire9;
    
    int _a = 1;
    bool _b = true;
    float _c = 4.21;
    
    struct {
        int x,y;
        
    } _d[5];
    
    msg9 << _a << _b << _c << _d;
    
    _a += _a;
    _b= !_b;
    _c += _c;
    
    msg9 >> _d >> _c >> _b >> _a;
    
    return 0;
    
}
