Overview
The CCSVBusSystem implementation offers a concrete way to manage and interact with bus stops and routes, specifically designed to parse and utilize data from CSV files. This system leverages the flexibility of CSV data sources to populate its internal structures with comprehensive bus system information, making it highly adaptable for various transit data analysis and application needs.

Key Components
SStop Structure: Represents individual bus stops with unique identifiers (TStopID) and associated node IDs (CStreetMap::TNodeID), facilitating integration with street map data for geographic context.
SRoute Structure: Encapsulates bus routes, including a name and a collection of stop IDs, allowing for detailed route definitions and operations.
Data Storage: Utilizes unordered maps and vectors to efficiently store and index stops and routes, ensuring quick access to data by ID, name, or index.

Parsing and Initialization
CSV Data Reading: Parses stops and routes from CSV data sources provided at construction, using CDSVReader to read rows and extract necessary fields.
Direct Construction: Instantiates SStop and SRoute objects directly from parsed CSV data, ensuring the system is populated with accurate and usable data upon initialization

Usage
Designed for use in applications requiring access to structured bus system data, such as:
Transit Planning and Analysis: Enables detailed studies of transit network coverage, stop accessibility, and route efficiency.
Application Development: Serves as a backend component for apps providing transit information, route planning, and navigation services.
Data Visualization: Can be used to generate data-driven visualizations of bus networks, enhancing public information resources and operational insights.