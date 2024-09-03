# MacMagic

**MacMagic** is a simple C-based program designed to perform MAC address vendor lookups. It reads a list of Organizationally Unique Identifiers (OUIs) from a file (`oui.txt`) and determines the vendor associated with a given MAC address. This tool is useful for network administrators, cybersecurity professionals, and anyone interested in identifying the manufacturer of network devices.

## Features

- **Vendor Lookup:** Quickly identify the vendor associated with a MAC address.
- **OUI Parsing:** Reads OUIs from a standard `oui.txt` file, which can be regularly updated.
- **Simple CLI Interface:** Easy-to-use command-line interface for quick lookups.

## Prerequisites

- A C compiler (e.g., `gcc`)
- An OUI list in the format of `oui.txt` (as provided by IEEE)

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/macmagic.git
   cd macmagic
   ```

   2. Compile the program using `gcc`:
   ```bash
   gcc -o macmagic macmagic.c
   ```

   3. Ensure that `oui.txt` is in the same directory as the compiled binary.
  
   ## Usage

   Run the program from the command line:
   ```bash
   ./macmagic
   ```

   Input a MAC address when prompted:
   ```
   Enter MAC address (format: XX:XX:XX:XX:XX:XX):
   ```

   ## Important Notes

   - Original OUI File: The program relies on `oui.txt`, which should be kept up-to-date with the latest OUI assignments. You can download the latest OUI file from IEEE's official site.
   - MAC Address Format: The MAC address should be provided in standard notation, e.g., `00:1A:2B:3C:4D:5E`.

   ## License

   This project is licensed under the MIT License - see the LICENSE file for details.
