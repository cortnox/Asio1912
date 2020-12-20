//
//  main.cpp
//  Asio1912
//
//  Created by Scott Dean on 12/19/20.
//
#define ASIO_STANDALONE ///excludes boost  framework dependencies
#include <asio.hpp>
#include <iostream>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>



int main(int argc, const char * argv[]) {
    /// insert code debugger here...
    asio::error_code ec;
    ///context that block boost framework
    asio::io_context ctx;
    ///endpoint
    asio::ip::tcp::endpoint ep(asio::ip::make_address("93.184.216.34", ec), 80);///example.com: 93.184.216.34:80 | local: 192.168.1.13
    ///socket
    asio::ip::tcp::socket soc(ctx);
    
    soc.connect(ep,ec);
    if (!ec)
    {
        std::cout << "Connected!" << std::endl;
    }
    else
    {
        std::cout << "Failed connecting to address." << ec.message() << std::endl;
    }
    ///active connection
   if (soc.is_open())
   {
       ///server expect http string request -this is a sample to send data
       std::string sr = "GET /index.html HTTP/1.1\r\n""Host: example.com\r\n""Connection: close\r\n\r\n";
       ///write data
       soc.write_some(asio::buffer(sr.data(), sr.size()), ec);
       ///wait until connection goes through
       soc.wait(soc.wait_read);
       ///give time for server to respond
       //using namespace std::chrono_literals; std::this_thread::sleep_for(500ms);
       
       size_t bytes = soc.available();
       std::cout << "Bytes Available: " << bytes << std::endl;
       
       if (bytes > 0)
       {
           std::vector<char> vbf(bytes);
           ///read bytes
           soc.read_some(asio::buffer(vbf.data(), vbf.size()),ec);
           ///output bytes
           for (auto c : vbf)
           {
               std::cout << c;
           }
       }
       std::cout << "Bytes Available: " << bytes << std::endl;
   }
    ///system("pause");
    return 0;
}
fammYfqekja4torfyh
