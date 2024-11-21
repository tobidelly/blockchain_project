#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Maximum size definitions
#define MAX_HASH_SIZE 65  // SHA-256 hash is 64 characters + null terminator
#define MAX_DATA_SIZE 256 // Maximum size for block data
#define MAX_TIMESTAMP_SIZE 20

// Structure to represent a single block in the blockchain
typedef struct Block {
    int index;                          // Position of the block in the blockchain
    char previous_hash[MAX_HASH_SIZE];  // Hash of the previous block
    char timestamp[MAX_TIMESTAMP_SIZE]; // Timestamp of block creation
    char data[MAX_DATA_SIZE];           // Data stored in the block
    char hash[MAX_HASH_SIZE];           // Hash of the current block
    struct Block *next;                 // Pointer to the next block
} Block;

// Structure to represent the entire blockchain
typedef struct Blockchain {
    Block *head; // Pointer to the first block (Genesis Block)
    int size;    // Number of blocks in the chain
} Blockchain;

// Function declarations
Blockchain *initialize_blockchain();
Block *create_block(int index, const char *previous_hash, const char *data);
void calculate_hash(const Block *block, char *output_hash);
void add_block(Blockchain *blockchain, const char *data);
int validate_blockchain(const Blockchain *blockchain);
void display_blockchain(const Blockchain *blockchain);
void free_blockchain(Blockchain *blockchain);

#endif // BLOCKCHAIN_H
