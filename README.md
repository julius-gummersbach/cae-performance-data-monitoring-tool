# CAE: Performance Data Monitoring Tool

This tool was developed as part of the Softwaretechnik lecture at FH Aachen University for the CAE GmbH.  
The lecture is part of the "Applied Mathematics and Computer Science" bachelor degree.  
The working group for this project consisted of:  

Jonas Böcker  
Simeon Burk  
Tom Ferdinandt  
Julius Gummersbach  
Josias Kasemann  
Taylor Seyler  

## Installation

(this installation was tested on windows using the mingw compiler)

Install Websocketpp:
1. Clone `https://github.com/zaphoyd/websocketpp` repository in the same directory as the project folder

Install Boost:
1. Download the zip file from `https://www.boost.org/users/history/version_1_81_0.html`
2. Unpack it in a folder called `boostlibrary` in the same directory as the project folder.

Install nlohmann/json:
1. Clone `https://github.com/nlohmann/json` repository in the same directory as the project folder

Install all dependencies from `resources/requirements.txt` with pip

## Usage

1. Start the dummy-server script with `python3 resources/server.py`
2. Build and run the "run" configuration of the outermost CMakeLists.txt file
3. Open the `core/main/webpage/index.html` file in a browser (tested with edge and chrome)

## About this Tool 

This tool is used to display data about threads that ran in a simulation instance.  
On startup, the tool connects to a websocket server and receives a JSON object containing the data.  
The data is then validated and stored in the graph- and data manager.  
When the user selects a thread to be displayed on the webpage, the webpage requests the graph and other data from the 
controller. The controller creates a svg of the graph on demand and provides the data to the webpage.  
The webpage then displays the data in a graph and a table.  
The user can select two threads and perform a mathematical operation on them. The result of that operation is stored as 
a new graph and can itself be used in further operations. This feature can be used to compare the performance of 
multiple threads.


## Project Timeline

During the SWT Project all [MATSE](https://de.wikipedia.org/wiki/Mathematisch-technischer_Softwareentwickler) students 
form groups to work on a software project for one of the companies that take part in the [MATSE trainee program]
(https://www.fh-aachen.de/studium/angewandte-mathematik-und-informatik-bsc/der-studiengang)

Our group took on a project offer from the [CAE GmbH](https://de.cae.com/en), a company that mainly develops training 
systems for the german air force, navy and army.  
The goal was to develop a tool that would receive data from a simulation at runtime and display it as graphs in a to be
determined GUI.  
These graphs were to be updated at runtime as new data from the simulation comes in.  
It was also required that the user could select two of the graphs and perform a mathematic operation on them 
(e.G. add, subtract, multiply, divide) and store the result as a new graph. This lead to the quite interesting 
circumstance that the graphs were to form a mathematical group.  

As we were all attending a lecture on C++ at the time, we decided to develop the software in C++ to practise what we had
learned in the lecture in practice.  
We started off by brainstorming a general design and structure for our software. You can find the class 
diagrams [here](TODO).  
Implementing most of our initial design took us about 50% of the scheduled project time.  
After we had initially planned to write a GUI in C++ using Qt or a similar framework, we decided to use the web TODO
technologies instead because we encountered some licensing problems.
We were almost done with most of the software when we were told that the application would in fact not receive live 
updates at runtime. Instead, it would receive all the data in one big batch at startup. This lead to a complete redesign 
of the software. This costed us a lot of time and meant that we would not be able to implement all the smaller features 
we had planned, like data exporting capabilities.  
It took this long to realise this misunderstanding, because it was difficult to get example data for our project, 
partially because the CAE GmbH was not allowed to share the original, confidential simulation data with us.

We quickly came up with a new design for the software. We were reusing and simplifying some of our initial ideas, as the
new requirements were of course much simpler to implement. You can find the new class diagrams [here](TODO).  
On January 22nd 2023 we presented the project at the MATSE Softwaretechnik fair.


## Lessons Learned

Apart from the obvious lessons learned about C++ and developing a website, we also gained a lot of experience in the
process of developing a software and working in a team.
The big misunderstanding about the requirements showed us how important it is to make sure everybody is on the same page
before investing a lot of time into an idea.
