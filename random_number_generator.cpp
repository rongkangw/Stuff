#include <iostream>
#include <string>
#include <math.h>
#include <random>


int generatenum(int lower, int upper){
    //used random number distribution to get a random number
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(lower,upper); //Pseudo-RNG from 1-99
    return dist(rng);
}

int signcheck(int num){
    if (num > 0) return 1;
    else if (num < 0) return -1;
    return 0;
}


void answer(int dist){
    /*Note: cannot use xx < dist <= yy, 
    since c++ treats this as (xx < dist) <= yy and xx < dist return (0,1) aka true/false, 
    so condition likely does not work*/
    if (dist < 5)
        std::cout << "Burning!" << std::endl;
    else if (5 < dist && dist <= 10)
        std::cout << "Hot!" << std::endl;
    else if (10 < dist && dist <= 20)
        std::cout << "Warm" << std::endl;
    else if (20 < dist && dist <= 40)
        std::cout << "Cold!" << std::endl;
    else
        std::cout << "Freezing!" << std::endl; 
}


int main(){
    //initial variables
    int choice;
    int secretnum;
    bool guess = false;
    int lower = 0;
    int upper = 0;
    //guessing variables
    int trys = 0;
    int num;
    char replay;
    int diff;
    int checkold;
    int checknew;
    int prevnum = 0;
    int change = 0;
    bool retry = false;
    
    do{
        std::cout << "Welcome to the Number's Game!\n"
                    "This is a game about guessing a number. Pick a difficulty!\n\n"
                    "1. Easy(1-20)\n"
                    "2. Normal (1-50)\n"
                    "3. Hard (1-100)\n"
                    "4. Impossible! (1-500)\n"
                    "5. Quit." << std::endl;

        while (std::cout << "Your Choice : "){
                //Validates data type
                if (!(std::cin >> choice)){
                    std::cout << "Invalid input!" << std::endl;
                    std::cin.clear(); //clear the bad state flag(change state=false to true) to prevent infinite looping when std::cin gets an incorrect data type
                    std::cin.ignore(1000, '\n'); // discards up to 1000char/num of input or until newline character encountered
                }

                //Validates range of numbers
                else if (1>choice or choice>5){
                    std::cout << "Out of range! It's 1 - 5 buddy" << std::endl;
                    std::cin.ignore(1000, '\n');
                }
                else{
                    break;
                }
            }
        
        switch (choice) {
            case 1 : {
                upper = 20;
            }
            break;

            case 2 : {
                upper = 50;
            }
            break;
            case 3 : {
                upper = 100;
            }
            break;

            case 4 : {
                upper = 500;
            }
            break;

            case 5 : {
                guess = true;
            }
            break;
        };

        lower = 1;
        secretnum = generatenum(lower, upper);
        //std::cout << "Secret num is " << secretnum << std::endl; //used for debugging, displays secret num
        while(guess==false){
            
            //Data validator to ensure only integer values accepted
            while (std::cout << "Guess : "){
                //Validates data type
                if (!(std::cin >> num)){
                    std::cout << "Invalid input!" << std::endl;
                    std::cin.clear(); //clear the bad state flag(change state=false to true) to prevent infinite looping when std::cin gets an incorrect data type
                    std::cin.ignore(1000, '\n'); // discards up to 1000char/num of input or until newline character encountered
                }

                //Validates range of numbers
                else if (lower>num or num>upper){
                    std::cout << "Out of range! (" << lower << "-" << upper << ")" << std::endl;
                    std::cin.ignore(1000, '\n');
                }
                else{
                    break;
                }
            }

            trys++;
            checknew = signcheck(secretnum-num); //swapcheck checks if guess crosses over secretnum on next guess
            diff = abs(secretnum-num); //using distance from secretnum to calculate hot/cold

            //Case where number is gussed correctly
            if (num == secretnum){
                guess = true;
                std::cout << "Well done," << "the secret number was indeed " << secretnum << " and you guessed " << trys << " times!" << std::endl;
            }
            //Case where number is guessed wrongly
            else {
                if (trys==1){ //For first guess

                    //std::cout << diff << std::endl; //can be used to check number difference

                    answer(diff);
                    change = diff;
                    checkold = checknew;
                }
                else{ //For subsequent guesses
                    if (change == diff && checknew == checkold){ //first check if number is the same
                        std::cout << "Its the same number!" << std::endl;
                    }
                    else {//then check if same dist + opp side of number
                        if (checknew != checkold && diff == change){
                            std::cout << "Still "; //no std::endl since answer() completes this sentence
                            answer(diff);
                        }//then check if further from number
                        else if (diff > change){
                            std::cout << "Getting colder!" << std::endl;
                        }//then closer to number
                        else if (diff < change){
                            std::cout << "Getting hotter!" << std::endl;
                        }
                        change = diff;
                        checkold = checknew;
                    }
                }
            }
        }
        //Validate answer for try again
        while (std::cout << "Play again? (Y/N) :" && std::cin >> replay){
            //Rejects all inputs other than 'Y' or 'N'
            if (replay != 'Y' && replay != 'N'){
                std::cout << "Please, only Y/N!" << std::endl;
                std::cin.ignore(1000, '\n');
            }
            else {
                break;
            }
        }
        
        //Loop back if 'Y' is selected
        if (replay == 'Y'){
            retry = true;
            guess = false;
            trys = 0;
            prevnum = 0;
            checkold = 0;
            checknew = 0;
            prevnum = 0;

        }
    }while(retry);

    std::cout << "Well see ya" << std::endl;
    return 0;
};

//add a hangman style max guess limit maybe?
//make guesses countdown instead of up
//add a GUI maybe?

