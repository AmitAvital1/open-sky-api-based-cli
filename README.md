# open-sky-api

Flight Data API using OpenSky API
Description

This project is an API that fetches and sends data about flights from all over the world using the OpenSky API. It provides users with a simple command-line interface to interact with the API and retrieve flight data. The API is designed to run in a Docker container for easy deployment and scalability.
Features

    1.Fetch real-time flight data from the OpenSky API.
    2.Menu-driven CLI for user interaction and data retrieval.
    3.Data fetching and processing in a separate background container for improved efficiency.
    4.Utilizes CURL for HTTP requests, Libzip for data compression, and named pipes (FIFOs) for inter-container communication.
