# **Blockchain Implementation in C**

This project demonstrates a basic blockchain implementation in C, showcasing core blockchain features and advanced functionalities like Proof of Work, serialization, and networking. It is designed to highlight your expertise in low-level programming, cryptography, and systems design.

---

## **Features**

1. **Core Features**
   - Add and validate blocks.
   - SHA-256-based cryptographic hashing for data integrity.
   - Verify the validity of the blockchain.

2. **Advanced Features**
   - **Proof of Work (PoW):** Mine blocks by solving a computational puzzle.
   - **Serialization:** Save and load the blockchain to/from a file for persistence.
   - **Networking:** Send and receive blockchain data between peers over a network.

3. **Scalability**
   - Modular design for adding additional blockchain features, e.g., transactions or Merkle Trees.

---

## **Project Structure**

```
blockchain/
├── blockchain.h      # Header file defining blockchain structure and functions
├── blockchain.c      # Core blockchain implementation
├── block.c           # Block-specific implementation
├── hash.c            # SHA-256 hashing functions
├── network.c         # Networking utilities for peer-to-peer communication
├── Makefile          # Build system to compile the project
├── test/             # Directory for test cases
├── blockchain.dat    # Serialized blockchain file (generated after running tests)
└── README.md         # Project documentation
```

---

## **Getting Started**

### **Prerequisites**
- A C compiler, e.g., `gcc`.
- `make` build tool.
- Basic knowledge of C programming and blockchain concepts.

---

### **Installation**

1. Clone this repository:
   ```bash
   git clone https://github.com/yourusername/blockchain-c
   cd blockchain-c
   ```

2. Compile the project:
   ```bash
   make
   ```

3. Run the tests to verify functionality:
   ```bash
   ./blockchain
   ```

---

## **Usage**

### **1. Proof of Work**
Mine a block by solving a computational puzzle:
```bash
./blockchain
```
Output example:
```
Mined Block:
Index: 1
Hash: 00001a3f89dc9c6e8ec5a70c132...
Nonce: 45123
```

---

### **2. Serialization**
Save the blockchain to a file:
```bash
./blockchain
```
Load the blockchain from the file and print its contents:
```bash
cat blockchain.dat
```

---

### **3. Networking**
Run the server to accept blockchain data:
```bash
./blockchain_server
```
Send the blockchain to a peer:
```bash
./blockchain_client
```

---

## **How It Works**

### **Core Blockchain**
- Each block contains:
  - Index
  - Timestamp
  - Data
  - Previous block hash
  - Current block hash
  - Nonce (for Proof of Work)
- Hashing ensures the immutability of the blockchain.

### **Proof of Work**
- The block is mined by finding a nonce such that the hash meets a predefined difficulty.

### **Serialization**
- The blockchain is serialized into a binary file for persistence.
- It can be reloaded to reconstruct the blockchain in memory.

### **Networking**
- The server listens for connections from peers.
- Clients send serialized blockchain data to peers.

---

## **Future Enhancements**

- Add support for transactions and wallets.
- Implement Merkle Trees for efficient block data validation.
- Enhance networking with peer discovery and distributed consensus.
- Optimize Proof of Work for variable difficulty levels.

---

## **Contributing**

Contributions are welcome! If you have suggestions or bug fixes, feel free to open an issue or submit a pull request.

---

## **License**

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## **Acknowledgments**

- **Cryptographic Hashing:** Inspired by the SHA-256 algorithm.
- **Networking:** Concepts from peer-to-peer communication systems.
- **Blockchain Basics:** Referenced from Bitcoin and Ethereum whitepapers. 
