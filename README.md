# Install yaml-cpp in Ubuntu
1) sudo apt-get install libyaml-cpp-dev


#Steps to Run the Crossing Bridge Puzzle

1) The application is compiled in build folder

  $ make
    g++ -Wall -g  -c CrossBridgeTest.cpp -o build/./CrossBridgeTest.o -L/usr/lib -lm -lyaml-cpp
    g++ -Wall -g -o ./build/CrossBridgeTest build/./CrossBridgeTest.o -L/usr/lib -lm -lyaml-cpp

2) Update userInp.yaml with person and Bridge details.
   Node: bridges              -- Indicates the number of bridges
   Node: length               -- Indicates the length of individual Bridge
   Node: personsPosition      -- Indicates the position of person on each bridge (eg: 1 for first bridge)
   Node: personsSpeed         -- Indicated the Speed of each person

3) Run the application you get Minimum Crossing time of person on all bridges
 
  $ cd build
  $ ./CrossBridgeTest 
    Object for ReadYAML is being created
    The Minimum crossing time: 247.000000
    Object for ReadYAML is being deleted




#Logic behind the Crossing Bridge Puzzle
If we consider single bridge with N number of people with time of travels. Sort with Ascending order.
The first 2 slow persons cross the bridge and faster of 2 retuns with torch...

A simple algorithm is : assume 'N' is the number of people who can cross at same time and one person has to cross back bearing the torch

1) When moving people from first side to second side preference should be given to the 'N' slowest walkers
2) Always use fastest walker to take torch from second side to first side
3) When moving people from first side to second side, take into consideration who will bring back the torch in the next step. If the speed of the torch bearer in next step will be equal to the fastest walker, among the 'N' slowest walkers, in the current step then instead of choosing 'N' slowest walker, as given in '1', choose 'N' fastest walkers
 

#Running Google Unit Test

1) sudo apt-get install libgtest-dev
2) sudo apt-get install cmake
3) cd /usr/src/gtest
4) sudo cmake CMakeLists.txt
5) sudo make
6) sudo cp *.a /usr/lib

Compile unit test code

   $cd unitTest
   $ g++ googleTest_CrossingBridge.cpp -o run_test -lyaml-cpp -lgtest -lpthread

Run unit test Code

   $ ./run_test 

[==========] Running 1 test from 1 test case.
[----------] Global test environment set-up.
[----------] 1 test from ReadYamlTest
[ RUN      ] ReadYamlTest.readYamlvalid
Object for ReadYAML is being created
Object for ReadYAML is being deleted
[       OK ] ReadYamlTest.readYamlvalid (0 ms)
[----------] 1 test from ReadYamlTest (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test case ran. (0 ms total)
[  PASSED  ] 1 test.

   
