Overview
CStreetMap serves as an abstract base class for representing street maps, focusing on nodes and ways as fundamental elements. It's designed for extensions to provide concrete implementations for different map data sources.

Types and Constants (Parameteres)
TNodeID and TWayID: Unsigned 64-bit integers used for node and way identifiers.
TLocation: A pair of doubles representing latitude and longitude.
InvalidNodeID and InvalidWayID: Constants representing invalid IDs.
Structures
SNode: Abstract base for map nodes, supporting ID, location, and attribute queries.
SWay: Abstract base for map ways, encapsulating way ID, node references, and attributes.
Virtual Destructor
Ensures derived classes are properly destroyed.

Pure Virtual Methods
Node and way count accessors.
Methods to access nodes and ways by index or ID, returning shared pointers to SNode or SWay.
This class abstracts common functionalities required to interact with map data, allowing for flexible implementation specifics tailored to various map data formats or sources.