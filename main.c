#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MIN_PACKET_LENGTH 4 //minimum packet length (type + subtype + wrapper checksum)
#define PACKET_TYPE_POS 0 //the packet type is found at this index. refer protocol reference manual section 1.1
#define PACKET_SUBTYPE_POS 1 //the packet subtype is found at this index. refer protocol reference manual section 1.1.1
#define CHUNK_DATA_START_POS 2 // chunk data starts at this index. Refer protocol reference manual section 1.1.1
#define CHUNK_DATA_SIZE 32  //the chunk of data can have a maximum of 32 characters. Refer to protocol referenc manual section 1.2
#define CHUNK_CHECKSUM_SIZE 2 // the chunk checksum size is 2 character size. refer to protocol reference manual section 1.2

int validate_packet(char* packet)
{
    int length = strlen(packet);

    if(length < MIN_PACKET_LENGTH)
    {
        printf("Invalid packet: Packet is too short.\n");
        return 0;
    }

    //Extract the type and subtype of the incoming packet
    char type = packet[PACKET_TYPE_POS];
    char subtype = packet[PACKET_SUBTYPE_POS];

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
    
    //calculate wrapper checksum accroding to PRM section 1.1.1
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

    //Check and validate data

    if(length == MIN_PACKET_LENGTH) //if total length is 4, there is no data
    {
        printf("Valid packet: No data\n");
        return 1;
    }

    //In case there is more than one chunk, validate each chunk
    int chunk_start = CHUNK_DATA_START_POS; //variable to keep track of current location in the packet
    while(chunk_start < length-2)
    {
        // find the end of the current check and adjust it accordingly
        int chunk_end = chunk_start + CHUNK_DATA_SIZE;
        if(chunk_end > length - 2 -CHUNK_CHECKSUM_SIZE)
        {
            chunk_end = length - 2- CHUNK_CHECKSUM_SIZE;
        }
    
        int chunk_char_sum = 0;
        for(int i= chunk_start; i < chunk_end; i++)
        {
            if(!isprint(packet[i])) //checking validity of each character
            {
                printf("Invalid packet: Non-printable ASCII character in chunk data.\n");
                return 0;
            }
            chunk_char_sum += (int)packet[i]; //sum of all characters in the chunk accroding to PRM section 1.2
        }

        int chunk_checksum_expected = chunk_char_sum %256; // Refer to PRM 1.2
        char chunk_checksum_hex_expected[3]; //2 character hex checksum + null termination
        snprintf(chunk_checksum_hex_expected,3,"%02X",chunk_checksum_expected);

        //Extract the actual chunk checksum according to PRM section 1.2 for single chunk packet
        char chunk_checksum_actual[3] = {packet[chunk_end],packet[chunk_end + 1],'\0'};

        if(strcmp(chunk_checksum_hex_expected,chunk_checksum_actual) !=0 )
        {
            printf("Invalid packet: Chunk checksum does not match.\n");
            return 0;
        } 

        chunk_start += (chunk_end - chunk_start) + CHUNK_CHECKSUM_SIZE; // move to the next chunk's beginning

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