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

static constexpr int buflimit = 2048;///20*1024;

std::vector<char> vbuf(buflimit);///[buflimit];

void GrabSomeData(asio::ip::tcp::socket& socket)
{
    socket.async_read_some( asio::buffer( vbuf.data(), vbuf.size()),
    [&](std::error_code ec, std::size_t length)
    {
        if (!ec)
        {
            std::cout << "\n\nRead " << length << " bytes\n" << std::endl;
            for (int i = 0; i < length; i++)
            {
                std::cout << vbuf[i];
                GrabSomeData(socket);
            }
        }
    }
                           );}

int main(int argc, const char * argv[]) {
    

    /// insert code debugger here...
    asio::error_code ec;
    ///context that is platform specific - blocks boost framework
    asio::io_context ctx;
    ///distract the thread before it finishes - assign fake work - and fill eventually with productive functions - program will exit immidiatly once there is no more work left to do
    asio::io_context::work idleWrk(ctx);
    //start ctx in its own thread
    std::thread tCtx = std::thread([&]() {////lookup lambda functions  if running within it own thread - it can do thing independantly
        ctx.run();
    });
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
       GrabSomeData(soc);
       ///server expect http string request -this is a sample to send data
       std::string sr = "GET /index.html HTTP/1.1\r\n""Host: example.com\r\n""Connection: close\r\n\r\n";
       ///write data
       soc.write_some(asio::buffer(sr.data(), sr.size()), ec);
       ///give time for server to respond
       using namespace std::chrono_literals;
       ///wait abit longer before exiting
       std::this_thread::sleep_for(20000ms);
       /**       ///wait until connection goes through
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
        std::cout << "Bytes Available: " << bytes << std::endl;*/
       ////above is replaced by [GrabSomeData(soc);]
       
   }
    ///system("pause");
    return 0;
}
