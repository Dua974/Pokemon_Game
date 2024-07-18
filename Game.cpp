/********
 **File: Game.cpp
 **Project: Pokemon_Game
 **Author: Dua Abdullah
 **
 **The Game.cpp file contains the implementation of functions for a Pokémon game. It initializes the game, loads Pokémon data, displays menus, allows catching, training, battling, and manages player's
 **Pokémon team. The Start() function initiates the game by loading data and displaying the main menu. When starting the game, the players are given a main menu to add pokemons, battle with other
 **pokemons, and train them to improve them combat capabilities. 
 *********/


#include "Game.h"
#include "Pokemon.h"
#include<ctime>
#include<cmath> 
#include <cstdlib>


//Name: Game
//PreCondition: filename represents the name of the file containing Pokemon data.
//PostCondition: m_filename is updated  and LoadFile function is called to load Pokemon data from file. Then Game is initlized with data loaded from file.

Game::Game(string filename) {
    m_filename = filename;
    LoadFile();
}


//Name: LoadFile
//PreCondition: input file is passed and populated with pokemon.
//PostCondition: Each pokemon object in m_pokeDex is initialized with info. from the file and if file cannot be oppened then an error message displays. 

void Game::LoadFile() {
    ifstream file(m_filename);

    if (file.is_open()) {
        //iterate through each pokemon to read from data file 
        for (int i = 0; i < TOTAL_POKEMON; ++i) {
	  string pokemonName;    // stores name of Pokemon          
	  int pokemonCP;       // stores the combat power associated with Pokemon 
	  int pokemonRarity;    // stores rarity level of the Pokemon
	  int pokemonNumber;   // stores the identification number of Pokemon

            
          file >> pokemonNumber >>  pokemonName >> pokemonCP >> pokemonRarity;

          // Check if reading file  was successful
          if (!file.fail()) {
	    
	    m_pokeDex[i] = Pokemon(pokemonNumber, pokemonName, pokemonCP, pokemonRarity);
          } else {
	     // Break the loop if reading file  fail break;    
	     break; 
              
            }
        }

	// close the file after reading all Pokemon information 
        file.close();
    } else {
        cout << "Error: Unable to open the file." << endl;
    }
}


//Name:DisplayPokeDex
//PreCondition: m_pokeDex populated with Pokemon objects. TOTAL_POKEMON represents total number of pokemon stored in m_pokeDex array. NAME_WIDTH represents width for displaying Pokemon names.
//PostCondition: outputs the list of Pokemon numbers and names according to the format. 

void Game::DisplayPokeDex() {
  
  for (int i = 0; i < TOTAL_POKEMON; ++i) {
    // Pokemon number is displayed left-aligned in a 3-character width followed by "."
    cout << setw(3) << left << m_pokeDex[i].GetNum() << ". "; 
    cout << setw(NAME_WIDTH) << left << m_pokeDex[i].GetName() <<endl; 
    
  }
}


//Name: MainMenu
//PreCondition: input from userOption should be an integer corresponding to 1-6. m_pokeDex populated.
//PostCondition: Displays main menu options to user. Continously asks user to enter option until they enter option 6 to exit. Each option from 1-6 calls the function associated with it. 

void Game::MainMenu() {
  int userOption;   // stores the option user enters 

  while (userOption != 6) {
    cout << "What would you like to do?" << endl;
    cout << "1. Display Complete PokeDex" << endl;
    cout << "2. Display your Team" << endl;
    cout << "3. Search for a new Pokemon" << endl;
    cout << "4. Battle your Pokemon" << endl;
    cout << "5. Train your Pokemon" << endl;
    cout << "6. Exit" << endl;
    cin >> userOption;

    if (userOption == 1) {
      DisplayPokeDex();
    
    }else if (userOption == 2) {
      DisplayTeam();
    
    }else if (userOption == 3) {
      CatchPokemon();
    
    }else if (userOption == 4) {
      BattlePokemon();
      
    }else if (userOption ==5) {
      TrainPokemon();
      
    }else if (userOption == 6) {
      cout << "Thanks for playing!" << endl;

     //ignores invalid input and prompts the user to enter a valid option. 
    }else {
    }
 }

}

//Name: CatchPokemon
//PreCondition: CatchMenu() returns valid rarity option of 1,2,3. FoundPokemon() called will search for a Pokemon with that rarity. AddPokemon() adds the found Pokemon to player's team.
//PostCondition: random number generated to get Pokemon based on rarity user chooses, If the random number generated is less than the rarity category, a Pokemon is found and added to the player's team.
//If no Pokemon is found, a message indicates no pokemon is found. Ensures rarity option chosen is not invalid.

void Game::CatchPokemon() { 
  int rarityOption = CatchMenu();    // Stores player's chosen rarity option for catching Pokemon.  
  int randomNumber = rand()%100 ;  // Generates a random number to simulate the chance of encountering a Pokemon


  int rarityCategory = 0;    // sotres rarity COMMON, ULTRA, UNCOMMON chosen by player 
  switch (rarityOption) {
    
    case 1:
      rarityCategory = COMMON;
      break;
    case 2:
      rarityCategory = UNCOMMON;
      break;
    case 3:

      //assigns a specific to value to the variable based on a particular case. 
      rarityCategory = ULTRA;
       break;
    default:
       cout << "Invalid rarity option." << endl;
       return;
  }
    if (randomNumber < rarityCategory) {
 
      Pokemon pokemonNew = FoundPokemon(rarityOption);     // Stores Pokemon found by FoundPokemon() function based on rarity option. 
      if(pokemonNew.GetNum() != 0) {      
	cout << "You start to search." <<endl;

	//Displays the name of the Pokemon found 
        cout << "You found a " << pokemonNew.GetName() << endl; 

        //newly found Pokemon is added to the player's team so they can use it for battles or other activity.
        AddPokemon(pokemonNew);
        
      
      } else {
        cout << " No Pokemon found. Better luck next time!" << endl;
      }
    }else {
      cout << " No Pokemon found. Better luck next time!" << endl;
      
  }
}


//Name: CatchMenu
//PreCondition: user will enter an int corresponding to one of the rarity  options 1-3
//PostCondition: Prompts the user to choose the rarity of Pokemon they would like to catch and returns selected category.

int Game::CatchMenu() {
  
  int rarityOption;    //sotres the rarity option the user will choose 
  cout << "What rarity of Pokemon would you like catch?" << endl;
  cout << "1. Common (High Probability)" << endl;
  cout << "2. Uncommon (Normal Probability)" << endl;
  cout << "3. Ultra Rare (Extremely Low Probability)" << endl;
  cin >> rarityOption;;
  return rarityOption;
}

//Name: FoundPokemon
//PreCondition: MAX_FIND and MIN_FIND represent valid values for adjusting CP of chosen Pokemon, m_pokeDex is populated with valid Pokemon objects.
//PostCondition: The function returns a Pokemon object with adjusted Combat Power (CP) based on the specified rarity, or a default-constructed Pokemon if no Pokemon of the specified rarity is found.

Pokemon Game::FoundPokemon(int rarity) {
  Pokemon pokemonsWithRarity[TOTAL_POKEMON];    // array use to store Pokemon objects that match specified rarity. Has a size of TOTAL_POKEMON and each element of this array holds Pokemon object with
  //specified rarity. 

  int countPokemonRarity = 0;   // stores number of Pokemon found with the specified rarity. 

    // Find and store Pokemon with the specified rarity
    for (int i = 0; i < TOTAL_POKEMON; ++i) {
        if (m_pokeDex[i].GetRarity() == rarity) {
            pokemonsWithRarity[countPokemonRarity++] = m_pokeDex[i];
        }
    }

    // If no Pokemon with the specified rarity were found, return a default-constructed Pokemon
    if (countPokemonRarity == 0) {
        return Pokemon();
    }

    // Randomly choose a Pokemon from the array
    int randomlyChoose = rand() % countPokemonRarity;    //generates random index within range of number of Pokemon found with specified rarity. Determines which Pokemon will be chosen randomly
    //from array. 

    Pokemon chosenPokemon = pokemonsWithRarity[randomlyChoose];   // Stores Pokemon chosen randomly from pokemonsWithRarity array based on randomly generated index. 

    // Reduce CP of the chosen Pokemon
    int cpReduced = rand() % (MAX_FIND - MIN_FIND + 1) + MIN_FIND;  // Calculates a random reduction value within the range specified. How much the CP of the chosen Pokemon will be decreased.
    
    int newPokemonCp = chosenPokemon.GetCP() - cpReduced;    //calculates the new CP of the chosen Pokemon by subtracting the randomly generated reduction value (cpReduced) from its current CP.
    

    // updates the CP of the chosen Pokemon with the adjusted value after applying the random reduction.
    chosenPokemon.SetCP(newPokemonCp);

    return chosenPokemon;
}

//Name: AddPokemon
//PreCondition:  The function is called with a valid Pokémon object, newPokemon, and the m_team array is properly initialized.
//PostCondition: If there is an empty slot in the m_team array, the newPokemon is added to the team, and a confirmation message is displayed.If the team is full, the function replaces the weakest
//Pokémon in the team with newPokemon if its Combat Power (CP) is higher than the weakest Pokémon's CP. A message indicating whether the Pokémon was added or replaced is displayed.

void Game::AddPokemon(Pokemon newPokemon) {
  int index = 0;   //used as a counter to iterate through elements of array
  
  while (index < NUM_TEAM) {
    if (m_team[index].GetNum() == 0) {
      m_team[index] = newPokemon;
      cout << newPokemon.GetName() << " added to your team!" << endl;
      return;
    }
    index++;
  }

  int minimumIndex = 0;   //keeps track of index of Pokemon with lowest CP in the team. 
  
  for (int i = 1; i < NUM_TEAM; ++i) {
    // checks if CP at current index i is less than CP of the Pokemon at minimumIndex, if so then CP of that pokemon is lower than the CP of the Pokémon currently considered to have the minimum CP
    //in the team. 

    if (m_team[i].GetCP() < m_team[minimumIndex].GetCP()) {
      minimumIndex = i;
    }
  }

  cout << "Your team is full. " << (newPokemon.GetCP() > m_team[minimumIndex].GetCP() ? newPokemon.GetName() + " replaced " + m_team[minimumIndex].GetName() : newPokemon.GetName() + " couldn't be added.") << endl;
  
  if (newPokemon.GetCP() > m_team[minimumIndex].GetCP()) {

    // replaces Pokemon with lowest CP in the team with newPokemon
    m_team[minimumIndex] = newPokemon;
  }
  
}


//Name: TeamSize
//PreCondition: m_team array is populated initialized and contains valid Pokemon objects. The constant NUM_TEAM represents the maximum size of the player's team.The GetNum() and GetCP() methods of the
//Pokemon class correctly return the Pokemon's number and Combat Power (CP) respectively.
//PostCondition: If there is an empty slot in the player's team (m_team), the newPokemon is added to the team, and a message is displayed indicating that the Pokemon has been successfully added.If
//there are no empty slots in the team, the function replaces the weakest Pokemon in the team with the newPokemon if its CP is higher than the weakest Pokemon's CP. A message is displayed indicating
//whether the Pokemon was added to the team or not.After the function executes, the player's team is updated with the new Pokemon, either by adding it to an empty slot or replacing the weakest Pokemon.

int Game::TeamSize() {
  int track = 0;   // counts the number of elements or tracks progress, specifically used to count the number of Pokemon in the player's team.

  // counts and returns the number of valid Pokémon entries in the m_team array.
  for (auto& pokemon : m_team) {
    if (pokemon.GetNum() != 0) {
      track++;
    }
  }
  return track;
}

//Name: DisplayTeam
//PreCondition: The DisplayTeam() function is called within the context of a Game object.The TeamSize() function is implemented and returns the number of Pokémon in the player's team.
//PostCondition: The function displays the player's team if it contains Pokemon, showing each Pokémon's name and CP in a formatted manner.If the player's team is empty, a message indicating so is
//displayed.

void Game::DisplayTeam() {
    
  if (TeamSize() == 0) {
  cout << "You have no team yet. Maybe search for a Pokemon?!" << endl;
  return;
  }

 
  int i = 1;   //initialized as a counter starting from 1. It is used to track the position of Pokemon within the team for display purposes.
  
  for (int index = 0; index < NUM_TEAM; ++index) {

    //This condition checks if a valid Pokémon exists at the current index in the m_team array.
    if (m_team[index].GetNum() != 0) { 
      cout << setw(2) << left << i << ". ";
      cout << setw(NAME_WIDTH) << left << m_team[index].GetName();
      cout << setw(NUM_WIDTH) << right << m_team[index].GetCP() << endl;

      //increments each time a valid Pokémon is encountered in the team during the iteration through the m_team array
      i++;
    }
  }  
}


//Name: FindPokemon
//PreCondition: The name parameter represents the name of the Pokémon being searched for.The m_pokeDex array is properly initialized and contains valid Pokémon objects.The constant TOTAL_POKEMON
//represents the total number of Pokémon in the game.
//PostCondition: The function returns the index of the Pokémon in the m_pokeDex array if it is found.If the Pokémon is not found, the function returns -1 to indicate that the Pokémon was not found in
//the m_pokeDex array. After the function executes, the state of the Game object remains unchanged.

int Game::FindPokemon(string name) {
  int i = 0;  //used as an index or counter to iterate through elements, starting from 0.
  
  while (i < TOTAL_POKEMON) {

    //This condition checks if the name of the Pokémon stored at index i in the m_pokeDex array matches the specified name.
    if (m_pokeDex[i].GetName() == name) {
      break;
    }
    i++;
  }
  
  if (i < TOTAL_POKEMON) {
      // Pokemon found, return index                  
      return i; 
  } else {
    
      //Pokemon not found
      return -1;
  }
}

//Name: TrainPokemon
//PreCondition: The TeamSize() function is implemented and correctly returns the number of Pokémon in the player's team.The DisplayTeam() function is implemented and correctly displays the
//player's team.The m_team array is properly initialized and contains valid Pokémon objects.The constant NUM_TEAM represents the maximum size of the player's team.The Train() method of the Pokemon
//class is implemented and correctly trains the Pokémon.
//PostCondition: After successful execution, the chosen Pokémon's Combat Power (CP) is increased.The function ensures that the state of the game remains unchanged except for the CP increase of the
//trained Pokémon.

void Game::TrainPokemon() {
  if (TeamSize() == 0) {
    cout << "You have no team yet. Maybe search for a Pokemon?!" << endl;
    return;
  }

  cout << "Which of your pokemon would you like to use?: " <<endl;

  //called to show the player's current team of Pokémon. 
  DisplayTeam();
  int userChoice;
  cin >> userChoice;

  // Adjusting for 0-based indexing   
  userChoice--; 

  
  if (userChoice < 0) {
    cout << "Invalid choice!" << endl;
  } else if (userChoice >= NUM_TEAM) {
      cout << "Invalid choice!" << endl;
  } else if (m_team[userChoice].GetNum() == 0) {
      cout << "Invalid choice!" << endl;
      return;
  }

  //train the selected Pokémon in the player's team. It calls the Train() method of the Pokemon class on the chosen Pokémon, passing its current Combat Power (CP) as an argument.
  m_team[userChoice].Train(m_team[userChoice].GetCP());
  cout <<"Your " <<  m_team[userChoice].GetName() << " goes up!" << endl;

}

//Name: BattlePokemon
//PreCondition: The TeamSize() function is implemented and correctly returns the number of Pokémon in the player's team.The DisplayTeam() function is implemented and correctly displays the player's
//team.The m_pokeDex array is properly initialized and contains valid Pokémon objects.The m_team array is properly initialized and contains valid Pokémon objects.The SetCP() method of the Pokemon class
//correctly sets the CP of a Pokémon.
//PostCondition: After the battle, the state of the game may be altered if the player's Pokémon loses, such as reducing its CP to 0. Otherwise, the state remains unchanged.

void Game::BattlePokemon() {
  int  MAX_CP = 1000;    //Represents the maximum Combat Power (CP) value assigned to Pokémon during battles.                                     
  int MIN_CP = 100;   //Represents the minimum Combat Power (CP) value assigned to Pokémon during battles.       

    
    if (TeamSize() == 0) {
        cout << "You have no team yet. Maybe search for a Pokemon?!" << endl;
        return;
     }

      //This helps to introduce randomness into the program, such as when selecting a random Pokémon for the player to battle against.
     srand(time(nullptr)); 

     int randomIndex = rand() % TOTAL_POKEMON;  //Represents a randomly generated index within the range of the total number of Pokémon available in the game (TOTAL_POKEMON). It is used to select a
     //random Pokémon from the m_pokeDex array for the player to battle against.

     Pokemon enemy = m_pokeDex[randomIndex];   //Represents the randomly selected Pokémon from the m_pokeDex array based on the generated randomIndex. This Pokémon becomes the opponent in the battle.
     
     int enemyStrength = rand() % (MAX_CP - MIN_CP + 1) + MIN_CP + ENEMY_ADD;  //Represents the combat strength of the enemy Pokémon
     enemy.SetCP(enemyStrength);

     cout << "You are going to fight a " << enemy.GetName() << endl;
     cout << "The enemy has a CP of " << enemy.GetCP() << endl;
     cout << "Which of your pokemon would you like to use?:" << endl;

     DisplayTeam();

     int userInput;    // store the index of the Pokémon chosen by the player from their team to participate in the battle
     cin >> userInput;
     userInput--;

    if (userInput < 0 || userInput >= NUM_TEAM || m_team[userInput].GetNum() == 0) {
        cout << "Invalid choice!" << endl;
        return;
    }

    //This condition compares the Combat Power (CP) of the Pokémon chosen by the player (m_team[userInput].GetCP()) with the CP of the enemy Pokémon (enemy.GetCP()). If the CP of the player's Pokémon
    //is greater than that of the enemy Pokémon, it indicates that the player's Pokémon is stronger than the enemy.
    if (m_team[userInput].GetCP() > enemy.GetCP()) {
        cout << "You won!!" << endl;
    } else {
        cout << "You lost." << endl;
        cout << "Your " << m_team[userInput].GetName() << " can't lift its head." << endl;
        cout << "You should replace it." << endl;

	// Setting CP to 0 for the losing Pokemon   
        m_team[userInput].SetCP(0);
    }
}

//Name: Start
//PreCondition: The LoadFile() function is implemented and correctly loads Pokémon data from a file.The MainMenu() function is implemented and correctly displays the main menu of the game.
//PostCondition: After the execution of the Start() function, the game is initialized and ready for the player to interact with, including accessing the main menu options and playing the game.
void Game::Start() {
  LoadFile();
  MainMenu();
}


