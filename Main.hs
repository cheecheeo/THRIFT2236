{-# LANGUAGE ScopedTypeVariables #-}
module Main where

import           Data.Int
import qualified Data.Vector as Vector
import qualified Data.HashMap.Strict  as HashMap
import           Network

-- Thrift libraries
import           Thrift.Server

-- Generated Thrift modules
import Performance_Types
import ItemStore_Iface
import ItemStore


i32toi :: Int32 -> Int
i32toi = fromIntegral

itoi32 :: Int -> Int32
itoi32 = fromIntegral

port :: PortNumber
port = 9090

data ItemHandler = ItemHandler

instance ItemStore_Iface ItemHandler where
    ping _                   = return () --putStrLn "ping"
    getItems _ mtname mtsize = do
        let size = i32toi mtsize
            item i = Item (Just mtname) (Just $ Vector.fromList $ map itoi32 [i..100])
            items = map item [0..(size-1)]
            itemsv = Vector.fromList items
            mappers = zip (map itoi32 [0..(size-1)]) items
            mappersh = HashMap.fromList mappers
            itemPack = ItemPack (Just itemsv) (Just mappersh)
        putStrLn "getItems"
        return itemPack

    setItems _ _             = do putStrLn "setItems"
                                  return True

    getVector _ mtsize       = do putStrLn "getVector"
                                  let size = i32toi mtsize
                                  return $ Vector.generate size itoi32

main :: IO ()
main = do
    _ <- runBasicServer ItemHandler process port
    putStrLn "Server stopped"
