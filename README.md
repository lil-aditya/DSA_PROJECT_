# Algorithmic Data Integrity and Prioritization Engine (ADIPE)

This repository contains the C++ implementation for **ADIPE (Algorithmic Data Integrity and Prioritization Engine)**, A lightweight framework for simulating a network with Authenticated Quality of Service (QoS).


# 📘 About the Project

This project is a **network simulation framework** that combines number-theoretic algorithms, graph traversal, and cryptographic verification to simulate how trusted digital packets move through a distributed system.

Every packet generated in the system is **digitally signed** using number-theoretic Data Structures & Algorithms (DSA). These signatures ensure:

- **Authenticity** — the packet truly comes from the claimed sender.
- **Integrity** — the packet has not been altered during transit.

Once verified, packets enter a **priority-based routing engine** built on top of **Heaps (Priority Queues)** and **Graphs (BFS/Dijkstra)**.

This allows the network to **route data intelligently** based on urgency, trust, and validity — unlike a normal BFS network where all packets are treated equally.

The entire system is visualized in a clean simulation UI, where users can:

- Inject packets  
- Track packet priority  
- Observe live C++ logs  
- Monitor node status  
- Watch real-time routing behavior  


---

# 🧠 Technical Stack

This simulation is built using the following technologies and algorithms:

---

## 🔹 Programming Language
- **C++** (chosen for low-level performance and control)

---

## 🔹 Core DSA Components
- Fast Modular Exponentiation  
- Extended Euclidean Algorithm  
- Custom Hash Map (O(1) average lookup time)  
- Priority Queue (Heap) – for urgency-based scheduling  
- Graph Traversal (Dijkstra-style routing)  

---

## 🔹 Integrity & Verification
- **RSA Digital Signatures**  
- **simplified hashing**  

---

## 🔹 Frontend / UI
- **React + Vite**  
- **TailwindCSS** for styling  
- Real-time event polling from C++ backend nodes  
- Live log viewer, packet injection panel, and priority visualization  

---


## 🚀 How to Run

To build and run the C++ command-line demonstration:

```bash
# 1.git clone https://github.com/lil-aditya/DSA_PROJECT_.git
# 2.Ensure you have MSYS2 UCRT64
# 3.In UCRT64 terminal run cd /c/Users/PC/Desktop/Project_dsa_old/DSA_PROJECT_
# 4.make
# 5../build/dsa_project.exe
# 6.In powershell go to \DSA_PROJECT_\adipe-frontend>  and then run "npm install"
# 7.npm run dev
