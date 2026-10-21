#include <stdio.h> 
#include "db.dat"
#define id 1

int main(int argc, char* argv[]) 
{ 
   struct student rec;
   FILE *fp;
   if (argc != 2) {
      fprintf(stderr, "How to use: %s FileName\n", argv[0]);
      exit(1); 
   }
   fp = fopen(argv[1], "wb");
   printf("%7s %6s %4s\n", "id", "bookname","author", "year","numofborrow", "borrow"); 
   while (scanf("%d %s %d", &rec.id,    rec.name, &rec.score) == 3) {
      fseek(fp,  (rec.id-id)* sizeof(rec),  SEEK_SET);
      fwrite(&rec, sizeof(rec), 1, fp);
   }
   fclose(fp);
   exit(0);
} 


