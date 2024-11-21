#include "blockchain.h"

// Function to create a new block
Block *create_block(int index, const char *previous_hash, const char *data) {
    Block *block = (Block *)malloc(sizeof(Block));
    block->index = index;
    strncpy(block->previous_hash, previous_hash, MAX_HASH_SIZE);
    strncpy(block->data, data, MAX_DATA_SIZE);

    // Generate the timestamp
    time_t now = time(NULL);
    strftime(block->timestamp, MAX_TIMESTAMP_SIZE, "%Y-%m-%d %H:%M:%S", localtime(&now));

    // Calculate the block's hash using the hash module
    calculate_hash(block, block->hash);
    block->next = NULL;

    return block;
}

// Function to initialize the blockchain
Blockchain *initialize_blockchain() {
    Blockchain *blockchain = (Blockchain *)malloc(sizeof(Blockchain));
    blockchain->head = NULL;
    blockchain->size = 0;

    // Add the Genesis Block
    add_block(blockchain, "Genesis Block");
    return blockchain;
}

// Function to add a new block to the blockchain
void add_block(Blockchain *blockchain, const char *data) {
    Block *new_block;

    if (blockchain->head == NULL) {
        // Genesis Block
        new_block = create_block(0, "0", data);
        blockchain->head = new_block;
    } else {
        // Find the last block
        Block *last = blockchain->head;
        while (last->next != NULL) {
            last = last->next;
        }

        // Create and link the new block
        new_block = create_block(last->index + 1, last->hash, data);
        last->next = new_block;
    }

    blockchain->size++;
}

// Function to validate the blockchain's integrity
int validate_blockchain(const Blockchain *blockchain) {
    Block *current = blockchain->head;

    while (current != NULL && current->next != NULL) {
        // Check if the current block's hash matches the next block's previous hash
        if (strcmp(current->hash, current->next->previous_hash) != 0) {
            return 0; // Blockchain is invalid
        }

        // Recalculate the current block's hash and check if it matches the stored hash
        char recalculated_hash[MAX_HASH_SIZE];
        calculate_hash(current, recalculated_hash);
        if (strcmp(current->hash, recalculated_hash) != 0) {
            return 0; // Blockchain is invalid
        }

        current = current->next;
    }

    return 1; // Blockchain is valid
}

// Function to display the blockchain
void display_blockchain(const Blockchain *blockchain) {
    Block *current = blockchain->head;

    while (current != NULL) {
        printf("Block #%d\n", current->index);
        printf("Timestamp: %s\n", current->timestamp);
        printf("Data: %s\n", current->data);
        printf("Hash: %s\n", current->hash);
        printf("Previous Hash: %s\n", current->previous_hash);
        printf("----------------------\n");

        current = current->next;
    }
}

// Function to free the memory allocated for the blockchain
void free_blockchain(Blockchain *blockchain) {
    Block *current = blockchain->head;

    while (current != NULL) {
        Block *temp = current;
        current = current->next;
        free(temp);
    }

    free(blockchain);
}

// Save blockchain to a file
void save_blockchain(const Blockchain *blockchain, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file");
        return;
    }

    Block *current = blockchain->head;
    while (current != NULL) {
        fprintf(file, "%d|%s|%s|%s|%s|%u\n", current->index, current->previous_hash, current->timestamp,
                current->data, current->hash, current->nonce);
        current = current->next;
    }

    fclose(file);
}

// Load blockchain from a file
Blockchain *load_blockchain(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    Blockchain *blockchain = (Blockchain *)malloc(sizeof(Blockchain));
    blockchain->head = NULL;
    blockchain->size = 0;

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        Block *new_block = (Block *)malloc(sizeof(Block));
        sscanf(line, "%d|%64[^|]|%19[^|]|%255[^|]|%64[^|]|%u", &new_block->index, new_block->previous_hash,
               new_block->timestamp, new_block->data, new_block->hash, &new_block->nonce);

        new_block->next = NULL;

        if (blockchain->head == NULL) {
            blockchain->head = new_block;
        } else {
            Block *last = blockchain->head;
            while (last->next != NULL) {
                last = last->next;
            }
            last->next = new_block;
        }

        blockchain->size++;
    }

    fclose(file);
    return blockchain;
}

