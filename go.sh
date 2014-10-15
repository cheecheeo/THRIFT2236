cabal sandbox add-source ../thrift/lib/hs/
cabal exec ghc Main.hs gen-hs/ItemStore_Client.hs gen-hs/ItemStore.hs gen-hs/ItemStore_Iface.hs gen-hs/Performance_Consts.hs gen-hs/Performance_Types.hs -- -Wall -O2
