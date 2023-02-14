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
2. Unpack it in the same directory as the project folder.

Install nlohmann/json:
1. Clone `https://github.com/nlohmann/json` repository in the same directory as the project folder

Install all dependencies from `resources/requirements.txt` with pip

## Usage

1. Start the dummy-server script with `python3 resources/server.py`
2. Build and run the "run" configuration of the outermost CMakeLists.txt file
3. Open the `core/main/webpage/index.html` file in the browser
