/*
 * Author: Luka Gajic kalahnar@uw.edu
 * Project: pr1.c
 * Version: 1.0
 * Worked on: Ubuntu 16.04 LTS Desktop 32-bit
*/
#include <stdio.h>
#define BITS 8 //constant for bits with value 8
int convertToBinary(int);
int convertToDecimal(int);
int main () {//mainstart
    int conversion, IP1, IP2, IP3, IP4, mask, ip1b, ip2b, ip3b, ip4b, i, j = 1;
    int y = sizeof(int)*BITS;
    unsigned int UIP1, UIP2, UIP3, UIP4,  maskDec = 0, nPrefix, hostID, bNPrefix, bHostID;
    unsigned int hostAdd, prefAdd, ipDec, addition;
    char choice;
    printf("What type of conversion do you want?\n");
    printf("Enter 1 for IP-address and subnet, 2 for the host and network prefix:\n"); 
    scanf("%d", &conversion);
    //if the user choses 1 it starts the if statement
    if(conversion == 1) { //if converstion == 1 start
         printf("\nEnter the message address: \n");
         scanf("%d.%d.%d.%d/%d", &IP1, &IP2, &IP3, &IP4, &mask);
         //making sure that there is a warding for illegal input
         while (IP1<0 || IP1 > 255 || IP2 < 0 || IP2 > 255 || 
               IP3<0 || IP3 > 255 || IP4 < 0 || IP4 > 255 || mask < 0 || mask > 32) {//while start
	                 printf("Wrong address, try again: \n");
                   scanf("%d.%d.%d.%d/%d", &IP1, &IP2, &IP3, &IP4, &mask);
         }//while end
         getchar();
         //shifting bits in order to get value for each individual number
         IP1 = IP1 << (3 * BITS);
         IP2 = IP2 << (2 * BITS);
         IP3 = IP3 << BITS;
         addition = IP1 + IP2 + IP3 + IP4;//adding all of them to get the decimal value
         ipDec = addition;//storing addition into a temporary variable
         printf("The IP-address is : %u in decimal and \n", addition);
        
         /*
          * Goes through the loop 32 times. The if statement checks if the Decimal value of the IP
          * address is greater than 2^31 (maximum value number can be in a 32 bit number). If it
          * is print 1 and shift it to the left by 1 bit if its not print 0 and still shift it by
          * 1 bit. I am using this logic in a couple of more places so the comments will be the 
          * same because the logic is the same.
          */
         for (i = 1; i <= y; i++) {//for start
              if(ipDec >= 2147483648u) {//if start
                   printf("1");
                   ipDec = ipDec << 1; 
              } else {//if end & else start
                   printf("0");
                   ipDec = ipDec << 1;   
              }//else end
              if((i % 8) == 0) {//if start
                  printf(" ");
              }//if end
         }//for end
         printf("in binary\n");

         //The subnet mask in binary
         printf("\nThe subnet mask is \n");
         /*
          * Goes through the loop 32 times. The if statement checks if the Decimal value of the IP
          * address is greater than 2^31 (maximum value number can be in a 32 bit number). If it
          * is print 1 and shift it to the left by 1 bit if its not print 0 and still shift it by
          * 1 bit. I am using this logic in a couple of more places so the comments will be the 
          * same because the logic is the same.
          */
         for(i = 0; i < y; i++) {//for start
             if(mask>0) {//if start
                  printf("1");
                  maskDec = maskDec << 1;
                  maskDec++;
                  mask--;
             } else {//if end & else start
                  printf("0");
                  maskDec = maskDec << 1;          
             }//else end
              
         }//for end
         printf(" in binary and \n");
         printf("%u in decimal\n", maskDec);
         /*
          * Shifting each of the numbers that the mask Decimal consists off to the left in order
          * to get the value of each of those numbers individually however I am also using modulo
          * because I don't want to lose other values so like this I don't have to shit them back
          * and fort I can just grab the value that i need. Since I am using this method later
          * on in looking for other dot-decimal values the comments will be the same.
          */
         UIP1 = (maskDec >> (BITS * 3));      
         UIP2 = (maskDec >> (BITS * 2)) % 256;
         UIP3 = (maskDec >> BITS) % 256;
         UIP4 = maskDec % 256;
         printf("The subnet mask in dot-decimal is: %u.%u.%u.%u\n", UIP1, UIP2, UIP3, UIP4);
         nPrefix = maskDec & addition;     //32 bit decimal value  
         /*
          * Shifting each of the numbers that the mask Decimal consists off to the left in order
          * to get the value of each of those numbers individually however I am also using modulo
          * because I don't want to lose other values so like this I don't have to shit them back
          * and fort I can just grab the value that i need. Since I am using this method later
          * on in looking for other dot-decimal values the comments will be the same.
          */
         printf("\nThe network prefix is: %u in decimal and\n", nPrefix);
         UIP1 = (nPrefix >> (BITS * 3));      //dot decimal value for netPrefix
         UIP2 = (nPrefix >> (BITS * 2)) % 256;
         UIP3 = (nPrefix >> BITS) % 256;
         UIP4 = nPrefix % 256;
         /*
          * Goes through the loop 32 times. The if statement checks if the Decimal value of the IP
          * address is greater than 2^31 (maximum value number can be in a 32 bit number). If it
          * is print 1 and shift it to the left by 1 bit if its not print 0 and still shift it by
          * 1 bit. I am using this logic in a couple of more places so the comments will be the 
          * same because the logic is the same.
          */
         for (i = 1; i <= y; i++) {//for start
              if(nPrefix >= 2147483648u) {//if start
                   printf("1");
                   nPrefix = nPrefix << 1;
              } else {//if end & else start
                   printf("0");
                   nPrefix = nPrefix << 1;
              }//else end
              if((i % 8) == 0) {//if start
                 printf(" ");
              }//if end
         }//for end
         printf(" in binary \n");
         printf("The network prefix is in dot-decimal is: %u.%u.%u.%u\n", UIP1, UIP2, UIP3, 
                UIP4);
         hostID = addition & ~maskDec; // findign the host ID based on formula given to us
         bHostID = hostID; // temp location for hostID since I will be changing it
         printf("\nThe host ID is : %u in decimal and\n", hostID);
         /*
          * Goes through the loop 32 times. The if statement checks if the Decimal value of the IP
          * address is greater than 2^31 (maximum value number can be in a 32 bit number). If it
          * is print 1 and shift it to the left by 1 bit if its not print 0 and still shift it by
          * 1 bit. I am using this logic in a couple of more places so the comments will be the 
          * same because the logic is the same.
          */
         for (i = 1; i <= y; i++) {//for start
              if(hostID >= 2147483648u) {
                   printf("1");
                   hostID = hostID << 1;
              } else {//if end & else start
                   printf("0");
                   hostID = hostID << 1;
              }//else start
              if((i % 8) == 0) {//if start
                  printf(" ");
              }//if end
         }//for end
         printf(" in binary\n");
         /*
          * Shifting each of the numbers that the mask Decimal consists off to the left in order
          * to get the value of each of those numbers individually however I am also using modulo
          * because I don't want to lose other values so like this I don't have to shit them back
          * and fort I can just grab the value that i need. Since I am using this method later
          * on in looking for other dot-decimal values the comments will be the same.
          */
         UIP1 = (bHostID >> (BITS * 3));      //dot decimal value for hostID
         UIP2 = (bHostID >> (BITS * 2)) % 256;
         UIP3 = (bHostID >> BITS) % 256;
         UIP4 = bHostID % 256;
         printf("The host ID in dot-decimal is: %u.%u.%u.%u\n", UIP1, UIP2, UIP3, UIP4);
        
         
         printf("\nEnter r to repeat, q to quit: \n");
         printf("\n------------------------------------");
         scanf("%c", &choice);
         if(choice == 'r'){//if start
             main();
         } else if (choice == 'q') {//if end & else start
            return 0;
         } //else end
    }else if (conversion == 2) {//if conversion == 2 start
         printf("Enter the host: \n");
         scanf("%d.%d.%d.%d", &IP1, &IP2, &IP3, &IP4);
         printf("Enter the network Prefix: \n");
         scanf("%d.%d.%d.%d", &ip1b, &ip2b, &ip3b, &ip4b);
         getchar();
         //shifting to the left a certain amount of bits in order to get each number individually
         IP1 = IP1 << 3 * BITS;
         IP2 = IP2 << 2 * BITS;
         IP3 = IP3 << BITS;
         hostAdd = IP1 + IP2 + IP3 + IP4;
         //shifting to the left a certain amount of bits in order to get each number individually
         ip1b = ip1b << 3 * BITS;
         ip2b = ip2b << 2 * BITS;
         ip3b = ip3b << BITS;
         prefAdd = ip1b + ip2b + ip3b +ip4b;
         ipDec = hostAdd | prefAdd; // finding the Ip decimal value
         /*
          * Shifting each of the numbers that the mask Decimal consists off to the left in order
          * to get the value of each of those numbers individually however I am also using modulo
          * because I don't want to lose other values so like this I don't have to shit them back
          * and fort I can just grab the value that i need. Since I am using this method later
          * on in looking for other dot-decimal values the comments will be the same.
          */
         UIP1 = (ipDec >> (BITS * 3));      
         UIP2 = (ipDec >> (BITS * 2)) % 256;
         UIP3 = (ipDec >> BITS) % 256;
         UIP4 = ipDec % 256;
         for(i = 0; i < y; i++) {//for start
             if(((prefAdd >> i) % 2) == 1) {//if start
                  mask = y - i;
                  break;
             }//if end            
         }//for end
         printf("The message is: %u.%u.%u.%u/%u \n", UIP1, UIP2, UIP3, UIP4, mask);
         printf("\nEnter r to repeat, q to quit: \n");
         printf("\n------------------------------------");
         scanf("%c", &choice);
         if(choice == 'r'){//if start
            main();
         } else if (choice == 'q') {//if end & else start
            return 0;
         } //else end

    }//conversion ==2 end
}//main end


