#include "blockchain.h"
#include <openssl/sha.h> // For SHA-256 hashing

// Function to calculate the SHA-256 hash of a block
void calculate_hash(const Block *block, char *output_hash) {
    char input[512]; // Buffer to hold the concatenated data
    snprintf(input, sizeof(input), "%d%s%s%s", block->index, block->previous_hash, block->timestamp, block->data);

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *)input, strlen(input), hash);

    // Convert the hash to a hexadecimal string
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output_hash + (i * 2), "%02x", hash[i]);
    }
    output_hash[64] = '\0'; // Null-terminate the string
}

