# open-sky-api

Flight Data API using OpenSky API
Description

This project is an API that fetches and sends data about flights from all over the world using the OpenSky API. It provides users with a simple command-line interface to interact with the API and retrieve flight data. The API is designed to run in a Docker container for easy deployment and scalability.
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

Contributions to this project are welcome. If you find a bug or have a feature suggestion, please open an issue on GitHub. Feel free to fork this repository and submit a pull request with your improvements.

Implementation Details

This Flight Data API project is implemented using a combination of C and C++. The main reason for choosing these languages is their efficiency and performance, which are crucial when dealing with real-time data processing and networking tasks.
C

The core functionality of the API, including the menu-driven command-line interface, inter-container communication with named pipes (FIFOs), and making HTTP requests to the OpenSky API using CURL, is implemented in C. C is well-suited for systems programming and offers low-level control, making it an excellent choice for handling low-level I/O operations and managing memory efficiently.
C++

C++ is utilized for data processing and manipulation tasks. The background container, responsible for fetching and processing flight data from the OpenSky API, is implemented in C++. C++'s object-oriented features, such as classes and data structures, provide a convenient way to organize and manage the flight data retrieved from the API. Additionally, C++'s standard library offers powerful data manipulation functionalities, which streamline the handling of complex data sets.

The combination of C and C++ in this project allows for an efficient and robust implementation. The C components handle the fundamental aspects of the API, while C++ enhances the project's data processing capabilities.
Advantages of Using C and C++

    Performance: C and C++ are known for their excellent performance and efficiency, making them ideal choices for real-time data processing and networking tasks.

    Low-level Control: C allows for direct manipulation of memory and low-level I/O operations, ensuring precise control over system resources.

    Object-Oriented Features: C++'s object-oriented features facilitate code organization and reusability, making it easier to manage and process the retrieved flight data.

    Standard Libraries: Both C and C++ come with robust standard libraries that offer a wide range of functionalities, reducing the need for external dependencies.

Acknowledgments

    This project was inspired by the OpenSky API, which provides valuable real-time flight data.
