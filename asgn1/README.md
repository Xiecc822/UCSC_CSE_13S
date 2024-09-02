# CSE 13S Assignment 1 -- Pass the Pigs

## Build   

    $ make  
    
    or  
    
    $ make all
	
## Running    
           
    $ ./pig
	
## Cleaning      

    $ make clean
    
## Possible Errors      
	When user uses invalid inputs include letters such as "abcd" or "abc456", the 
	programs skips over the user's input for a random seed. This error is due 
	to the way of the scanf() works.
