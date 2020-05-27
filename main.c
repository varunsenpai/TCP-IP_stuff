#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#define PREFIX_LEN      16
void get_broadcast_address( char *ip_addr, char mask, char *output_buffer);

int main()
{
    char ipadd_buffer[PREFIX_LEN];
    memset(ipadd_buffer, 0, PREFIX_LEN);
    char *ip_add = "192.168.0.10";
    char mask = 24;
    get_broadcast_address(ip_add, mask, ipadd_buffer);

    printf("Broadcast address = %s\n", ipadd_buffer);
    return 0;
}

void get_broadcast_address( char *ip_addr, char mask, char *output_buffer)
{
   uint32_t mask_int = 0;
   unsigned int byte[4];
   uint32_t mask_int_filled_mask = 0;
   unsigned int arr[4];
   uint32_t string_to_int = 0;
   int temp = 0;
   uint32_t subnet_id = 0;

   mask_int = (unsigned int)mask;

   while((temp < mask_int) )
   {
       mask_int_filled_mask |= (1 << (31 - temp));
       ++temp;
   }


   sscanf(ip_addr, "%u.%u.%u.%u", &byte[0], &byte[1], &byte[2], &byte[3]);

   string_to_int = byte[3] + (byte[2] << 8 ) + (byte[1] << 16) + (byte[0] << 24);
   subnet_id = mask_int_filled_mask & string_to_int;


   uint32_t complement_mask = ~(mask_int_filled_mask);
   uint32_t broadcast_integer = string_to_int | complement_mask;
   arr[0] = broadcast_integer & 0xFF;
   arr[1] = (broadcast_integer >> 8) & 0xFF;
   arr[2] = (broadcast_integer >> 16) & 0xFF;
   arr[3] = (broadcast_integer >> 24) & 0xFF;


   snprintf(output_buffer, 16, "%u.%u.%u.%u", arr[3], arr[2], arr[1], arr[0]);
}
