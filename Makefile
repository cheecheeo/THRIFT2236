GEN_SRC := gen-cpp/ItemStore.cpp gen-cpp/performance_constants.cpp gen-cpp/performance_types.cpp
GEN_OBJ := $(patsubst %.cpp,%.o, $(GEN_SRC))

# THRIFT_DIR := /usr/local/include/thrift
THRIFT_DIR := ../thrift/lib/cpp/src
BOOST_DIR := /usr/local/include

INC := -I$(THRIFT_DIR) -I$(BOOST_DIR)

.PHONY: all clean

all:   ItemStore_server ItemStore_client

%.o: %.cpp
	$(CXX) --std=c++11 -Wall -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H $(INC) -c $< -o $@

ItemStore_server: ItemStore_server.o $(GEN_OBJ)
	$(CXX) $^ -o $@ -L/usr/local/lib -lthrift -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H

ItemStore_client: ItemStore_client.o $(GEN_OBJ)
	$(CXX) $^ -o $@ -L/usr/local/lib -lthrift -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H

clean:
	$(RM) *.o ItemStore_server ItemStore_client
