#include <iostream>
#include <time.h>
#include <string>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>

#include "Skip_list.h"

//==================================================
int main () {
	srand((unsigned) time(NULL));
	// Run for different n
	int max_n = 15;
	for (int n=200; n=<20000; n = n+100){
		Skip_list<int, int> sl(0.3); // while rng > q, increase. p: prob of stopping.
		for (int element=1; element <= n; element++)
			sl.insert(element, element);
	
		FILE *fp;
		char buffer[1024];
                snprintf(buffer, sizeof(buffer), "out/size/lookup_n_%i.txt", n);
                fp = fopen (buffer, "a+"); // file pointer
		for (int el=1; el<=n; el++){
			fprintf(fp, "%i ", sl.lookup(el));
		}

        	fprintf(fp, "%i\n", sl.get_number_pointers());
        	fclose (fp);
	}

	// Run for different q
	// Run for different n
        int size = 200; 
        for (int i=1; i<=19; i++){
		double alpha = (0.05)*i;
                Skip_list<int, int> sl(alpha); // while rng > q, increase. p: prob of stopping.
                for (int element=1; element <= size; element++)
                        sl.insert(element, element);
        
                FILE *fp;
                char buffer[1024];
                snprintf(buffer, sizeof(buffer), "out/alpha/lookup_alpha_%2f.txt", alpha);                                       
                fp = fopen (buffer, "a+"); // file pointer
                for (int el=1; el<=size; el++)
                        fprintf(fp, "%i ", sl.lookup(el));
                
                fprintf(fp, "%i\n", sl.get_number_pointers());
                fclose (fp);
        }
}
