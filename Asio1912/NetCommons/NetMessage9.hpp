//
//  NetMessage.hpp
//  Asio1912
//
//  Created by Scott Dean on 12/21/20.
//

#ifndef NetMessage9_hpp
#define NetMessage9_hpp

//#include <stdio.h>
#include "NetCommons9.hpp"


#endif /* NetMessage_hpp */
///Static Header Library [Tool Kit]


namespace nca9 {
namespace neta9 {

template <typename T>

struct header9///passes int value in T to size
{
    T id{};
    uint32_t size9 = 0;
};
template <typename T>///Template are dynamic and reusable
struct message9
{///passive code structure whixh adhere to the design of the asio toolkit - minimalistic
    header9 <T> hdr9{};
    
    std::vector<uint8_t> body9;
    ///return size of msg  - bytes
    size_t size9() const
    {
        return sizeof(header9<T>) + body9.size();
    }
    ///override for std::cout compatibility - produces description of message9 packets outputs it to the console///see packets while debugging
    friend std::ostream& operator << (std::ostream& os, const message9 <T> & msg)//////overides  the bit shift  <<  operator//freind can be acces any wherre by any thing
    {//push out variety type to cout
        os << "ID:" << int(msg.hdr9.id) << " Size: " << msg.hdr9.size;
        return os;
    }
    ///Pushes any pod - like data into the message9 buffer///treated like stack
    template<typename DataType>
    
    friend message9<T>& operator << (message9<T>&msg, const DataType& data)///called friend because it will be accesible from anywhere
    {   ///check that the type of the data being pushed is trivially copyable///standard layout
        static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be pushed");
        ///cache current size of vector, point of inserting data
        size_t i = msg.body9.size();
        ///resize the vector by the size of the data being pushed
        msg.body9.resize(msg.body9.size() + sizeof(DataType));///append size to generic data
        ///physically copy the data into the newly allocated vector space
        std::memcpy(msg.body9.data() + i, &data, sizeof(DataType));
        ///Recalculate / update header size
        msg.hdr9.size9 = msg.size9();
        ///return &msg ref
        return msg;
    }
/// ///check that the type of the data being pushed is trivially copyable///standard layout
template<typename DataType>
    
    friend message9<T>& operator >> (message9<T>&msg, DataType& data)
    {///check that the type of the data being pushed is trivially copyable///standard layout
        static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be pulled");
        //cache the location towards the end of the vector where the pulled data starts
        size_t i = (msg.body9.size() - sizeof(DataType));
        //Physically copy the data from the vector into the user variable
        std::memcpy(&data, msg.body9.data() + i, sizeof(DataType));
        //shrink size of vector - doesnt cause any reallocation
        msg.body9.resize(i);
        //recalculate header size
        msg.hdr9.size9 = msg.size9();
        ///target.msg so it can be chained
        return msg;
    }
};
}
}
///  NetMessage.h//  Asio1912//  Created by Scott Dean on 12/20/20.
/**#ifndef NetMessage_h
#define NetMessage_h
#endif  NetMessage_h *****/
