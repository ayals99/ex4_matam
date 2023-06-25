cmake_minimum_required(VERSION 3.25)
project(ex4_matam)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Cards)
include_directories(Players)

add_executable(ex4_matam
        Cards/Barfight.h
        Cards/Dragon.h
        Cards/Gremlin.h
        Cards/Mana.h
        Cards/Merchant.cpp
        Cards/Treasure.h
        Cards/Witch.h
        Cards/Well.h
        Players/Healer.h
        Players/Ninja.h
        Players/Player.cpp
        Players/Player.h
        Players/Warrior.h
        Exception.h
        utilities.cpp
        HealthPoints.cpp
        Cards/Merchant.cpp
        Mtmchkin.cpp
        Cards/BattleCards.cpp
        main.cpp)
