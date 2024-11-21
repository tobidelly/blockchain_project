#define DIFFICULTY 4 // Number of leading zeros required in the hash

// Updated Block structure
typedef struct Block {
    int index;
    char previous_hash[MAX_HASH_SIZE];
    char timestamp[MAX_TIMESTAMP_SIZE];
    char data[MAX_DATA_SIZE];
    char hash[MAX_HASH_SIZE];
    unsigned int nonce; // New field for Proof of Work
    struct Block *next;
} Block;

// Function declaration
void mine_block(Block *block);

