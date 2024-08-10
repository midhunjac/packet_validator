#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MIN_PACKET_LENGTH 4 //minimum packet length (type + subtype + wrapper checksum)

int validate_packet(char* packet)
{
    int length = strlen(packet);
    if(length < MIN_PACKET_LENGTH)
    {
        printf("Invalid packet: Packet is too short.\n");
        return 0;
    }

    //Extract the type and subtype of the incoming packet
    char type = packet[0];
    char subtype = packet[1];

    //Just checking whether the packet actually is a valid ASCII packet
    if(!isprint(type))
    {
        printf("Invalid packet: Type is not a printable ASCII character.\n");
        return 0;
    }
    if(!isprint(subtype))
    {
        printf("Invalid packet: Subtype is not a printable ASCII character.\n");
        return 0;
    }

    //Calculate wrapper checksum on our end to compare it with the actual wrapper checksum
    
    int wrapper_checksum_expected = ((int)type + (int)subtype) %256; // refer to protocol referenece manual section 1.1.1
    char wrapper_checksum_hex_expected[3]; // 2 char wrapper checksum + null termination
    snprintf(wrapper_checksum_hex_expected,3,"%02X",wrapper_checksum_expected);

    //extract the actual wrapper checksum accroding to protocl reference manual section 1.1
    char wrapper_checksum_actual[3] = {packet[length-2],packet[length-1],'\0'};
    
    //compare the actual and expected wrapper checksums to check if packet is valid
    if(strcmp(wrapper_checksum_hex_expected,wrapper_checksum_actual) != 0)
    {
        printf("Invalid packet: Wrapper checksum does not match.\n");
        return 0;
    }

    //If every condition is met, this is a valid packet
    printf("Valid packet.\n");
    return 1;
}

int main(int argc, char* argv[]) // command line argument fed input to help in quick testing
{
    if(argc != 2)
    {
        fprintf(stderr,"Usage: %s <packet>\n",argv[0]);
        return 1;
    }
    validate_packet(argv[1]);
    return 0;
}