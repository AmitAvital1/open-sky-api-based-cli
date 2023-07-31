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

Acknowledgments

This project was inspired by the OpenSky API, which provides valuable real-time flight data.
