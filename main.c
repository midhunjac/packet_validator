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
    char type = packet[0];
    char subtype = packet[1];

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
    printf("Valid packet\n");
    return 1;
}

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        fprintf(stderr,"Usage: %s <packet>\n",argv[0]);
        return 1;
    }
    validate_packet(argv[1]);
    return 0;
}