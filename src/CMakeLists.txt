cmake_minimum_required(VERSION 3.14)

add_library(Hungarian hungarian.cpp)
add_library(Data Data.cpp)
add_library(BranchAndBound BranchAndBound.cpp)
add_library(Node Node.cpp)
add_library(Kruskal Kruskal.cpp)
add_library(CR CombinatorialRelaxation.cpp)
add_library(Subgradient Subgradient.cpp)
add_library(SubgradientSolution SubgradientSolution.cpp)