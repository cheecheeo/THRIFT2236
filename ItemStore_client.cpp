#include <iostream>
#include <chrono>
#include "gen-cpp/ItemStore.h"

#include <transport/TSocket.h>
#include <transport/TBufferTransports.h>
#include <protocol/TBinaryProtocol.h>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace test;
using namespace std;

#define TIME_INIT  std::chrono::_V2::steady_clock::time_point start, stop; \
                   std::chrono::duration<long long int, std::ratio<1ll, 1000000000ll> > duration;
#define TIME_START start = std::chrono::steady_clock::now(); 
#define TIME_END   duration = std::chrono::steady_clock::now() - start; \
                   std::cout << chrono::duration <double, std::milli> (duration).count() << " ms" << std::endl;

int main(int argc, char **argv) {

    boost::shared_ptr<TSocket> socket(new TSocket("localhost", 9090));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

    ItemStoreClient server(protocol);
    transport->open();

    TIME_INIT

    long pings = 100;
    cout << "Sending " << pings << " pings" << endl;
    TIME_START
    for(auto i = 0 ; i< pings ; ++i)
        server.ping();
    TIME_END


    long vectorSize = 1000000;

    cout << "Transfering " << vectorSize << " size vector" << endl;
    std::vector<int> v;
    TIME_START
    server.getVector(v, vectorSize);
    TIME_END
    cout << "Recieved: " << v.size()*sizeof(int) / 1024.0 << " kB" << endl;


    long itemsSize = 100000;

    cout << "Transfering " << itemsSize << " items from server" << endl;
    ItemPack items;
    TIME_START
    server.getItems(items, "test", itemsSize);
    TIME_END


    cout << "Transfering " << itemsSize << " items to server" << endl;
    TIME_START
    server.setItems(items);
    TIME_END

    transport->close();

    return 0;
}
