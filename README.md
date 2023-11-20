# Flight DB

Flight Data API using OpenSky API
Description

Flight Service application This project is developed in Linux OS. The objective of the project is to practice working with process creation, signals, and interprocess communication using pipes. The application is designed to be an interactive multi-process application, divided into two processes. The first process interacts with the user, while the second process performs operations on a database (DB).

The program is divided into two processes:

1. Main Process: This process creates a child process upon initialization and handles user input and output. When the user chooses options 1-5, the request is passed from the main process to the child process, and the result data is received from the child process.
2. Child Process: This process receives operation codes (op-codes) from the main process, performs the required operation, and returns the data.

Features

    1.Fetch real-time flight data from the OpenSky API.
    2.Menu-driven CLI for user interaction and data retrieval.
    3.Data fetching and processing in a separate background container for improved efficiency.
    4.Utilizes CURL for HTTP requests, Libzip for data compression, and named pipes (FIFOs) for inter-container communication.
Requirements

    Docker installed on the host machine.

Installation and Usage

    Download the run.sh script and run it on terminal.

Background Data Fetching

    The data fetching and processing are performed in a separate container running in the background. The main container sends requests to the background container using named pipes (FIFOs). The background container fetches the data from the OpenSky API and compresses it using Libzip before sending it back to the main container.
    Contributing

Implementation Details

This Flight Data API project is implemented using a C++. The main reason for choosing these languages is their efficiency and performance, which are crucial when dealing with real-time data processing and networking tasks.

Preview:

![image](https://github.com/AmitAvital1/open-sky-api-based-cli/assets/116808245/930ce89c-e7e9-49bb-abe8-a08d6d6285fa)

