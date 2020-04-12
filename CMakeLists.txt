cmake_minimum_required(VERSION 3.15)
project(Server)

set(CMAKE_CXX_STANDARD 11)
add_executable(Server main.cpp server_side.cpp server_side.h MySerialServer.cpp MySerialServer.h ClientHandler.h MyTestClientHandler.cpp MyTestClientHandler.h Solver.h CacheManager.h FileCacheManager.h BestFirstSearch.h Searchable.h DFS.h BFS.h AStar.h SearchSolver.cpp SearchSolver.h iSearcher.h State.cpp State.h StringReverserSolver.cpp StringReverserSolver.h boot.h MyClientHandler.cpp MyClientHandler.h Matrix.cpp Matrix.h Point.cpp Point.h MyParallelServer.cpp MyParallelServer.h)
target_link_libraries(${PROJECT_NAME} pthread)