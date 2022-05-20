#include <algorithm>
#include <execution>
#include "CountingIterator.h"
#include "stdio.h"

int main(){
    /*
     * The mere presence of this loop influences the execution of the other standard algorithm.
     */  
    std::for_each_n(std::execution::seq, counting_iterator(0), 1, 
      [=](unsigned int i){
        float sw = 0.0;
        sw += 1;
    });   
    
    /*
     * Impacted computation.
     */  
    std::for_each_n(counting_iterator(0), 1, 
      [=](unsigned int i){
        float w = 0.6104355605587131;
        printf("  w = %.20f\n", w);
        printf("w/w = %.20f\n", w/w);
    });     

    return 0;
}
