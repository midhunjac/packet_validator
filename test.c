#include <stdio.h>
#include <assert.h>
#include <string.h>

#define TESTING
// Include the original packet validation functions
#include "main.c"


// Helper function to test validation
void test_validate_packet(char* packet, int expected_result) {
    int result = validate_packet(packet);
    assert(result == expected_result);
    if (result == expected_result) {
        printf("Test passed for packet: %s\n", packet);
    } else {
        printf("Test failed for packet: %s\n", packet);
    }
}

int main() {
    // Test cases with expected results
    test_validate_packet("A172", PACKET_VALID); // Valid packet: No data
    test_validate_packet("L1001411608032923583423317D", PACKET_VALID); // Valid packet with data
    test_validate_packet("H11E1050110117003D000000400010000043000200036+1368079",PACKET_VALID);//Valid packet with data
    test_validate_packet("B23F", PACKET_INVALID); // Invalid: Incorrect wrapper checksum
    test_validate_packet("X1001", PACKET_INVALID); // Invalid: Packet too short
    test_validate_packet("L1ZZ", PACKET_INVALID); // Invalid: Incorrect wrapper checksum
    test_validate_packet("L1", PACKET_INVALID); // Invalid: Packet too short
    test_validate_packet("L10014116080329235834233FF7D", PACKET_INVALID); // Invalid: Incorrect chunk checksum
    test_validate_packet("A1MMBNQOBRXWEQZBOWYYDMJPDGJMHCQJCF92LQNXJZBDKWPBOGACLYDCROZXIVDEGZAO93TYFJNRMZWZCNACSDLFQSFANXQQOOWXXKD6VAHPBQOULEF772",PACKET_INVALID);//Invalid: Incorrect chunk checksum
    test_validate_packet("Y1ZHRCNHZHUIHBJUXTFWUAPUZKVEBCZOROC9NFXDYZUSMVEOOUPMWIFWSZAFHGGJFXHFC0QSOEWUUGCCNUPLVAOOGRIUVOFRVSSLMOD2NZXWGLPBNZUQLFQWKGURQQWWXAZEZCOR03PYGPNZTCYEDJZEDZBYHLQVYXCBYGMKCLBBLDAMZAJKMSSMNNXSWADAUCAU208B",PACKET_INVALID);//Invalid: Incorrect wrapper checksum

    // Add more test cases as needed

    printf("All tests completed.\n");
    return 0;
}
