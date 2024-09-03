#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OUI_FILE "oui.txt"
#define MAX_LINE_LENGTH 256

typedef struct OUIEntry {
    char oui[7];  // Store as 6 hex digits (e.g., "286FB9")
    char vendor[100];
    struct OUIEntry* next;
} OUIEntry;

OUIEntry* load_oui_database(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening OUI database file");
        exit(EXIT_FAILURE);
    }

    OUIEntry* head = NULL;
    OUIEntry* tail = NULL;

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        // Check if the line contains "(base 16)"
        if (strstr(line, "(base 16)") != NULL) {
            OUIEntry* entry = (OUIEntry*)malloc(sizeof(OUIEntry));
            if (!entry) {
                perror("Memory allocation failed");
                exit(EXIT_FAILURE);
            }

            // Extract OUI and vendor name
            sscanf(line, "%6s", entry->oui);  // Extract the OUI (6 characters)
            fgets(line, sizeof(line), file);  // Read the next line for the vendor name
            sscanf(line, "%99[^\n]", entry->vendor);  // Extract the vendor name

            entry->next = NULL;

            if (!head) {
                head = entry;
            } else {
                tail->next = entry;
            }
            tail = entry;
        }
    }

    fclose(file);
    return head;
}

const char* lookup_vendor(OUIEntry* head, const char* mac) {
    char mac_oui[7];
    strncpy(mac_oui, mac, 6);
    mac_oui[6] = '\0';

    for (OUIEntry* entry = head; entry != NULL; entry = entry->next) {
        if (strcmp(mac_oui, entry->oui) == 0) {
            return entry->vendor;
        }
    }

    return "Unknown Vendor";
}

void free_oui_database(OUIEntry* head) {
    OUIEntry* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    // Load OUI database
    OUIEntry* oui_db = load_oui_database(OUI_FILE);

    // Get MAC address from the user
    char mac_address[18];
    printf("Enter MAC address (format: XX:XX:XX:XX:XX:XX): ");
    scanf("%17s", mac_address);

    // Convert MAC address to uppercase and remove colons
    for (int i = 0, j = 0; i < strlen(mac_address); i++) {
        if (mac_address[i] != ':') {
            mac_address[j++] = toupper(mac_address[i]);
        }
    }

    // Lookup vendor
    const char* vendor = lookup_vendor(oui_db, mac_address);
    printf("The vendor for MAC address %s is %s\n", mac_address, vendor);

    // Clean up
    free_oui_database(oui_db);
    return 0;
}
