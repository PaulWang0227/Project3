Overview
The CBusSystem interface is designed to abstract the functionalities of a bus system within the context of a street mapping application. It serves as a foundational component for managing bus stops and routes, allowing for a flexible integration with various mapping and transit data sources. This interface defines the core operations and data structures necessary to represent and interact with bus stops (SStop) and bus routes (SRoute) effectively.

Structs and Methods
SStop: An abstract structure representing a bus stop, including methods to access its unique identifier and associated node ID on the street map.
SRoute: An abstract structure representing a bus route, including methods to access its name, count of stops, and identifiers for each stop within the route.
Virtual Methods: A set of pure virtual methods define the interface for implementing classes, including methods to get the count of stops and routes, and to retrieve stops and routes by various criteria.

Usage Scenarios
Transit System Modeling: Ideal for creating detailed models of public transit systems, enabling applications to calculate routes, estimate travel times, and more.
Mapping Applications: Can be used in conjunction with street mapping data to visualize bus routes, locate bus stops, and provide transit directions.
Data Analysis: Offers a structured approach to analyzing transit system coverage, efficiency, and accessibility by providing a standardized interface for accessing bus system data.