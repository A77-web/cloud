.PHONY: cloud
cloud::cloud.cpp server.hpp
		g++ -std=c++14 $^ -o $@ -L./lib -lstdc++fs -ljsoncpp -lbundle -lpthread
