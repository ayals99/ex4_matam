cmake_minimum_required(VERSION 3.25)
project(ex4_matam)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Cards)
include_directories(Players)

add_executable(ex4_matam
#        Cards/Barfight.cpp
        Cards/Barfight.h
#        Cards/Dragon.cpp
        Cards/Dragon.h
#        Cards/Gremlin.cpp
        Cards/Gremlin.h
#        Cards/Mana.cpp
        Cards/Mana.h
        Cards/Merchant.cpp
#        Cards/Merchant.h
#        Cards/Treasure.cpp
        Cards/Treasure.h
#        Cards/Witch.cpp
        Cards/Witch.h
#        Cards/Well.cpp
        Cards/Well.h
#        "Given tests/test.cpp"

#        Players/testPlayers.cpp
        Players/Healer.h
        Players/Ninja.h
        Players/Player.cpp
        Players/Player.h
        Players/Warrior.h
        Exception.h
        Mtmchkin.h
        utilities.cpp
        HealthPoints.cpp
        Cards/Merchant.cpp
        Cards/CardTester.cpp
        Cards/Card.cpp Mtmchkin.cpp)
