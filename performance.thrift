namespace hs test
namespace cpp test

struct Item {
    1: optional string    name
    2: optional list<i32> coordinates
}

struct ItemPack {
    1: optional list<Item>     items
    2: optional map<i32, Item> mappers
}


service ItemStore {
    void ping()
    ItemPack getItems(1:string name, 2: i32 count) 
    bool     setItems(1: ItemPack items)

    list<i32> getVector(1: i32 count)
}
