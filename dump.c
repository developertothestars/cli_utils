/* adjust to screen size? */
/* integrate pager? */
/* jump to given offset? */
/* take command line argument? */

#include <stdio.h>
#define BUFSIZE 256 
#define BYTESPERLINE 16 

void dumpblock(int start_offset, char *buf, int bc)
{
   int i;
   int ofs;
   int max;
   int left;

   ofs = 0;
   left = bc;
   while (left > 0)
   {
      printf("%04x  ", start_offset);
      max = BYTESPERLINE > left ? left : BYTESPERLINE;
      for (i = 0; i < max; i++)
      {
         printf("%02x ", buf[i + ofs] & 0xff);
      }
      for (i = max; i < BYTESPERLINE; i++)
         printf("   ");
      printf(" ");
      for (i = 0; i < max; i++)
      {
         if (buf[i + ofs] > 0x1f && buf[i + ofs] < 0x7f)
            printf("%c", buf[i + ofs]);
         else
            printf(".");
      }
      printf("\n");
      left -= max;
      ofs += max;
      start_offset += max;
   }
}


int main(void)
{
   FILE *fp;
   char buf[BUFSIZE];
   int  bc;
   int  ofs;

   fp = fopen("dump.c", "r");
   ofs = 0;
   do
   {
      bc = fread(buf, 1, sizeof(buf), fp);
      if (bc > 0)
         dumpblock(ofs, buf, bc);
      ofs += bc;
   }
   while (bc > 0);
   fclose(fp);
   return 0;
}
