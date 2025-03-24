# Search Engine

This C++ program implements a simple search engine that indexes a text file and allows users to search for words or phrases. It supports basic boolean search operations:
- Union: Default behavior (matches any term).
- Intersection: Use + before a term (matches both terms).
- Exclusion: Use - before a term (excludes results containing that term).

Features:
- Parses and indexes text files using an inverted index.
- Cleans and normalizes search terms.
- Supports multi-word and boolean searches.

Users can input a filename and search for relevant URLs containing their query terms.

Files:
- main.cpp – Handles user interaction and initializes the search engine.
- search.h – Implements text processing, indexing, and search functionality.

How to Run: Compile and execute main.cpp, then enter a filename and search queries as prompted.
