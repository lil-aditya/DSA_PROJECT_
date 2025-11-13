# Algorithmic Data Integrity and Prioritization Engine (ADIPE)

This repository contains the C++ implementation for **ADIPE (Algorithmic Data Integrity and Prioritization Engine)**, a system designed for verifiable and prioritized data management.

## 📖 About the Project

The core idea of this project is to build a framework that uses number-theoretic Data Structures and Algorithms (DSA) to create digital signatures for data packets. This process ensures the **authenticity** and **integrity** of the data.

Once data is verified, the system uses structures like **Heaps (Priority Queues)** and **Graphs** to manage and route the data based on its urgency. It is a research-level project that demonstrates how to unify number theory, graph traversal, and data structures to solve complex problems of trust and timeliness in distributed computing.

## 🛠️ Technical Stack

The project is built using the following technologies and algorithms:

* **Programming Language:** `C++` (chosen for low-level control).
* **Core DSA:**
    * Fast Modular Exponentiation
    * Extended Euclidean Algorithm
    * Custom Hash Map (for O(1) lookups)
    * Priority Queue (Heap)
    * Graph Traversal (BFS/Dijkstra)
* **Integrity & Verification:**
    * RSA Digital Signatures
    * SHA-256 (simplified Hashing)

## 🚀 How to Run

To build and run the C++ command-line demonstration:

```bash
# 1. Compile the project using make
make

# 2. Run the executable
./build/ADIPE