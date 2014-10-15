#include "gen-cpp/ItemStore.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

#include <map>
#include <vector>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;


using namespace test;
using boost::shared_ptr;

class ItemStoreHandler : virtual public ItemStoreIf {
  public:
    ItemStoreHandler() {
    }

    void ping() {
        // printf("ping\n");
    }

    void getItems(ItemPack& _return, const std::string& name, const int32_t count) {

        std::vector <Item> items;
        std::map<int, Item> mappers;

        for(auto i = 0 ; i < count ; ++i){
            std::vector<int> coordinates;
            for(auto c = i ; c< 100 ; ++c)
                coordinates.push_back(c);

            Item item;
            item.__set_name(name);
            item.__set_coordinates(coordinates);

            items.push_back(item);
            mappers[i] = item;
        }

        _return.__set_items(items);
        _return.__set_mappers(mappers);
        printf("getItems\n");
    }

    bool setItems(const ItemPack& items) {
        printf("setItems\n");
        return true;
    }

    void getVector(std::vector<int32_t> & _return, const int32_t count) {
        for(auto i = 0 ; i < count ; ++i)
            _return.push_back(i);
        printf("getVector\n");
    }
};

int main(int argc, char **argv) {
    int port = 9090;
    shared_ptr<ItemStoreHandler> handler(new ItemStoreHandler());
    shared_ptr<TProcessor> processor(new ItemStoreProcessor(handler));
    shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
    shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
    shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

    TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
    server.serve();
    return 0;
}
