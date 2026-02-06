#include <stdio.h>
#include <stdint.h>
typedef enum {RECORD_LENGTH=0x1,ADDR=0x3,RECORD_TYPE=0x7,DATA=0x9} Intel_address_t;
int hex_to_byte(char val,char val1){
  
  int h_val,l_val;
  if (val>='A')h_val=(val-'A')+10;
  else h_val=val-'0';
  
  if (val1 >='A')l_val=(val1-'A')+10;
  else l_val=val1-'0';
  
  return (h_val<<4) |l_val;
}
int main(){
  size_t SIZE=1024;
  // 1kb
  int8_t record_length=0;
  uint8_t *addr;
  unsigned char buffer[SIZE];
  size_t bytesread;
  
  FILE *file_address=fopen("Sinewave.hex","rb");
  if (file_address==NULL){
    perror("errror while  opening file.\n");
    return 1;
  }
   do {
      bytesread =fread(buffer,1,sizeof(buffer),file_address);
      for (size_t i=0;i<(bytesread-2);i+=1){
        //printf("%02x\t",buffer[i]);
        /*
         each char in this  file 
         :10246200464C5549442050524F46494C4500464C33
         || |||||||||                              CC->Checksum
         || |||||||DD->Data
         || |||||TT->Record Type
         || |AAAA->Address
         |LL->Record Length
         :->Colon
        */
        // 0xF1 = "46 31"
        // 0b01000110  F=
        // value= (D x16)
        
        if (buffer[i] == 0x3a){
          char high =buffer[i+1];
          char low=buffer[i+2];
          
          uint8_t actual_value=(uint8_t)hex_to_byte(high,low)
          Intel_address_t addr=i;
          switch(addr){
            case RECORD_LENGTH:
              record_length=actual_value;
              break;
            case ADDR:
              addr=actual_value;
            case RECORD_TYPE;
              break;
            case DATA:
              // put eeprom write here 
              break;
            default:
              perror("Error while switching addresses");
              break;
          }

         }
        

    } 
        
      
      
   } while (bytesread>0);
  fclose(file_address);
  return 0;
}
