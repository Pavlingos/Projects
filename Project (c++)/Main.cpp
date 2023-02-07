#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Classes.h"

using namespace std;

int battle( int playersInTile, Hero **players, int *indexes, string *levelArray ){

	Monster **monsters = new Monster*[playersInTile];
	int **decreasedStats = new int*[playersInTile * 3];
	for ( int i = 0; i < playersInTile * 3; i ++ ){
		decreasedStats[i] = NULL;
	}
	int heroesHealthPower = 0;
	int monstersHealthPower = 0;
	for ( int i = 0; i < playersInTile; i ++ ){
		int type = rand()% 3;
		string name;
		if ( type == 0 ){
			name = "Dragon ";
		}
		else if ( type == 1 ){
			name = "Exoskeleton ";
		}
		else{
			name = "Spirit ";
		}
		int lvl = players[indexes[i]]->getLevel();
		name += levelArray[lvl] + " no." + levelArray[i+1];
		if ( type == 0 ){
			monsters[i] = new Dragon( name, lvl, "Dragon");
		}
		else if ( type == 1 ){
			monsters[i] = new Exoskeleton( name, lvl, "Exoskeleton" );
		}
		else{
			monsters[i] = new Spirit( name, lvl, "Spirit" );
		}
		cout << "Monster: " << monsters[i]->getName() << endl;
		heroesHealthPower += players[indexes[i]]->getHealthPower();
		monstersHealthPower += monsters[i]->getHealthPower();
	}
	char move;
	int target, rounds, stat, decrease, choice;
	while ( heroesHealthPower > 0 && monstersHealthPower > 0 ){
		int i = 0;
		while ( i < playersInTile && players[indexes[i]]->getHealthPower() > 0 ){
			cout << "Hero " << players[indexes[i]]->getName() << ", A for attack, P for use potion, E for equip an Item, I for inventory" << endl;
			cin >> move;
			while ( move != 'A' && move != 'P' && move != 'E' && move != 'I' ){
				cout << "Invalid Input, give again your move, A for attack, P for use potion, E for equip an Item, I for inventory!" << endl;
				cin >> move;
			}
			if ( move == 'A' ){
				cout << players[indexes[i]]->getName() << " attacks!" << endl;
				if ( playersInTile > 1 ){
					cout << "Give your target: " << endl;
					cin >> target;
					while ( target >= playersInTile || target < 0 ){
						cout << "Wrong Input. Give your target again!" << endl;
						cin >> target;
					}
				}
				else{
					target = 1;
				}
				cout << "How do you want to attack? A for Normal Attack, S for Spell Attack!" << endl;
				char attackType;
				cin >> attackType;
				if ( attackType == 'S' ){
					int Spells = players[indexes[i]]->showSpellInventory();
					if ( Spells == 0 ){
						cout << "You have no spell to cast!" << endl;
					}
					else{
						cout << "Give position of spell you want to cast!" << endl;
						cin >> choice;
						if(players[indexes[i]]->getSpell(choice) == NULL)
						{
							cout<<"No spell in this position"<<endl;
						}
						else
						{
							if(players[indexes[i]] -> getMagicPower() >= players[indexes[i]] -> getSpell(choice - 9) -> getEnergyNeed() )
							{
								int j = 0;
								int flag = 0;
								while ( flag == 0 ){
									if ( decreasedStats[j] == NULL ){
										j ++;
									}
									else{
										flag = 1;
									}
								}
								decreasedStats[j] = new int[4];
								decreasedStats[j][0] = target - 1;
								decreasedStats[j][1] = players[indexes[i]]->getSpell( choice - 9 )->getRounds();
								decreasedStats[j][2] = players[indexes[i]]->getSpell( choice - 9 )->getType();
								decreasedStats[j][3] = players[indexes[i]]->getSpell( choice - 9 )->getDecrease();
								monstersHealthPower -= players[indexes[i]]->castSpell( monsters[target - 1], choice - 9);
								i ++;
							}
							else
							{
								cout<<"Not enough magic power to cast this spell"<< endl ;
							}
						}
					}
				}
				else if ( attackType == 'A' ){
					monstersHealthPower -= players[indexes[i]]->attack( monsters[target - 1] );
					i ++;
				}
			}
			else if ( move == 'E' ){
				int items = players[indexes[i]]->showItemInventory();
				if ( players[indexes[i]]->getWeaponNum() == 0 && players[indexes[i]]->getArmorNum() == 0 ){
					cout << "No items to equip!" << endl;
				}
				else{
					cout << "Give position of item you want to equip" << endl;
					int position;
					cin >> position;
					if ( position < 3 && position > 0 && players[indexes[i]]->getItem( position ) != NULL ) {
						if ( players[indexes[i]]->getWeaponsEquipped() == 2 ){
							players[indexes[i]]->showEquippedWeapons();
							cout << "Cannot equip more weapons. Chose which weapon to unequip" << endl;
							int unequip;
							cin >> unequip;
							players[indexes[i]]->unequipWeapon( unequip );
							players[indexes[i]]->equipWeapon( players[indexes[i]]->getItem( position ) );
							cout << "Weapon equipped!" << endl;
							i ++;
						}
						else if ( players[indexes[i]]->getHandsBusy() ){
							cout << "Cannot equip more weapon. Unequipping your already equipped weapon..." << endl;
							players[indexes[i]]->unequipWeapon( 0 );
							players[indexes[i]]->equipWeapon( players[indexes[i]]->getItem( position ) );
							cout << "Weapon equipped!" << endl;
							i ++;
						}
						else{
							players[indexes[i]]->equipWeapon( players[indexes[i]]->getItem( position ) );
							cout << "Weapon equipped!" << endl;
							i ++;
						}
					}
					else if ( position >= 3 && position < 6 && players[indexes[i]]->getItem( position ) != NULL ){
						if ( players[indexes[i]]->getArmorEquipped() == 1 ){
							players[indexes[i]]->showEquippedArmor();
							cout << "There is already an armor equipped. Unequipping..." << endl;
							players[indexes[i]]->unequipArmor();
							players[indexes[i]]->equipWeapon( players[indexes[i]]->getItem( position ) );
							cout << "Armor equipped!" << endl;
							i ++;
						}
						else{
							players[indexes[i]]->equipArmor( players[indexes[i]]->getItem( position ) );
							cout << "Armor equipped!" << endl;
							i ++;
						}
					}
					else{
						cout << "Invalid Input" << endl;
					}
				}
			}
			else if ( move == 'P' ){
				int potions = players[indexes[i]]->showItemInventory();
				if ( players[indexes[i]]->getPotionNum() != 0 ){
					cout << "Give position of potion you want to use" << endl;
					int position;
					cin >> position;
					if ( position >= 6 && position < 9 && players[indexes[i]]->getItem( position ) != NULL ){
						players[indexes[i]]->usePotion( position );
						i ++;
					}
					else if ( players[indexes[i]]->getItem( position ) == NULL ){
						cout << "No potion in position you gave!" << endl;
					}
					else{
						cout << "Invalid position" << endl;
					}
				}
			}
			else{
				for ( int j = 0; j < playersInTile; j ++ ){
					players[indexes[i]]->printInfo();
				}
				for ( int j = 0; j < playersInTile; j ++ ){
					monsters[i]->printInfo();
				}
			}
		}
		for ( i = 0; i < playersInTile; i ++ ){
			cout << "Monster " << monsters[i]->getName() << " attacks!" << endl;
			int damage = monsters[i]->attack();
			int monsterTarget = rand()% playersInTile;
			while ( players[indexes[monsterTarget]]->getHealthPower() == 0 ){
				monsterTarget = rand()% playersInTile;
			}
			int avoid = rand()% 10;
			if ( avoid < players[indexes[monsterTarget]]->getAgility() ){
				cout << "Hero " << players[indexes[monsterTarget]]->getName() << " avoided the attack!" << endl;
			}
			else{
				damage -= players[indexes[monsterTarget]]->getDamageSaved();
				if ( damage > players[indexes[monsterTarget]]->getHealthPower() ){
					damage = players[indexes[monsterTarget]]->getHealthPower();
				}
				else if(damage < 0 )
				{
					damage = 0;
				}
				cout << "Monster " << monsters[i]->getName() << " dealt " << damage << " damage to hero " << players[indexes[monsterTarget]]->getName() << endl;
				players[indexes[monsterTarget]]->addHealthPower( (-1) * damage );
			}
		}
		for ( i = 0; i < playersInTile; i ++ ){
			cout << "Hero " << players[indexes[i]]->getName() << " has " << players[indexes[i]]->getHealthPower() << " points of health power" << endl;
		}
		for ( i = 0; i < playersInTile; i ++ ){
			cout << "Monster " << monsters[i]->getName() << " has " << monsters[i]->getHealthPower() << " points of health power" << endl;
		}
		for ( i = 0; i < playersInTile * 3; i ++ ){
			if ( decreasedStats[i] != NULL ){
				decreasedStats[i][1] --;
				if ( decreasedStats[i][1] == 0 ){
					if ( decreasedStats[i][2] == 0 ){
						monsters[decreasedStats[i][0]]->adjustDamageRange( decreasedStats[i][3] );
					}
					else if ( decreasedStats[i][2] == 1 ){
						monsters[decreasedStats[i][0]]->adjustDefense( decreasedStats[i][3] );
					}
					else{
						monsters[decreasedStats[i][0]]->adjustAvoidance( decreasedStats[i][3] );
					}
				}
				delete[] decreasedStats[i];
				decreasedStats[i] = NULL;
			}
		}
		for ( i = 0; i < playersInTile; i++ ){
			if ( players[indexes[i]]->getHealthPower() > 0 ){
				players[indexes[i]]->addHealthPower( players[indexes[i]]->getHealthPower()/10 );
				players[indexes[i]]->addMagicPower( players[indexes[i]]->getMagicPower()/4 );
				if(players[indexes[i]]-> getHealthPower() > 50 + players[indexes[i]] -> getLevel()*5 )
				{
					players[indexes[i]] -> setHealthPower(50 + players[indexes[i]] -> getLevel()*5 );
				}

				if(players[indexes[i]] -> getMagicPower() > 10 + players[indexes[i]]-> getLevel()*2)
				{
					players[indexes[i]] -> setMagicPower(10 + players[indexes[i]] -> getLevel()*2 );
				}
			}
			if ( monsters[i]->getHealthPower() > 0 ){
				monsters[i]->addHealthPower( monsters[i]->getHealthPower()/10);
				if(monsters[i]-> getHealthPower() > 2*(50 + players[indexes[i]] -> getLevel()*5) )
				{
					monsters[i] -> setHealthPower(2 * ( 50 + players[indexes[i]] -> getLevel()*5 ));
				}
			}
		}
		heroesHealthPower = 0 ;
		monstersHealthPower = 0 ;
		for (i = 0 ; i < playersInTile ; i++)
		{
			heroesHealthPower += players[indexes[i]]-> getHealthPower();
			monstersHealthPower += monsters[i] -> getHealthPower();
		}
	}
	if ( heroesHealthPower > 0 ){
		cout << "Hero squad won the battle!!" << endl;
		return 1;
	}
	else{
		cout << "Hero squad lost the battle..." << endl;
		return 0;
	}
}

int main( int argc , char* argv[] ){

	string levels[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };
	string weapons[] = { "Runespear", "Skull of Man'aari", "Aluneth", "Kingsbane", "Rhok'delar", "Val'anyr", "Woecleaver", "Twig Of The World Tree", "Sulfuras",
	"Atiesh, Greatstaff" };
	int weaponCount = 10;
	int i;
	srand( time( NULL ) );
	int playerNum = atoi(argv[1]);
	Market **marketArray = new Market*[playerNum];
	for ( int j = 0; j < playerNum; j ++ ){
		marketArray[j] = NULL;
	}
	int *heroPositions[2];
	char *lastMove;
	lastMove = new char[playerNum];
	for ( i = 0; i < playerNum; i ++ ){
		lastMove[i] = 'F';
	}
	for ( i = 0; i < 2; i ++ ){
		heroPositions[i] = new int[playerNum];
	}
	Hero **Players = new Hero*[playerNum];
	int *indexes;
	i = 0;
	string name, type;
	while ( i < playerNum ){
		cout << "Hero " << i + 1 << ", give class of hero: Warrior, Sorcerer or Paladin" << endl;
		cin >> type;
		if ( type.compare( "Warrior" ) == 0 ){
			cout << "Give Player Name" << endl;
			cin >> name;
			Players[i] = new Warrior( name, "Warrior" );
			i++;
		}
		else if ( type.compare( "Sorcerer" ) == 0 ){
			cout << "Give Player Name" << endl;
			cin >> name;
			Players[i] = new Sorcerer( name, "Sorcerer" );
			i++;
		}
		else if ( type.compare( "Paladin" ) == 0 ){
			cout << "Give Player Name" << endl;
			cin >> name;
			Players[i] = new Paladin( name, "Paladin" );
			i++;
		}
		else{
			cout << "Wrong input" << endl;
		}
	}
	for ( i = 0; i < playerNum; i ++ ){
		cout << "Hero " << i + 1 << " name: " << Players[i]->getName() << ", type: " << Players[i]->getLivingType() << endl;
	}
	cout << "Give lines of the grid" << endl;
	int gridLines;
	cin >> gridLines;
	cout << "Give collumns of the grid" << endl;
	int gridCollumns;
	cin >> gridCollumns;
	cout << "The grid of the game is " << gridLines << "x" << gridCollumns << endl;
	Grid gameGrid( gridLines, gridCollumns );
	gameGrid.displayMap();
	i = 0;
	while ( i < playerNum ){
		cout << "Give the coordinates you want Hero" << i + 1 << " to be placed " << endl;
		cout << "X: ";
		int x;
		cin >> x;
		while ( x > gridLines ){
			cout << "Wrong Input, give again" << endl;
			cout << "X:";
			cin >> x;
		}
		cout << "Y: ";
		int y;
		cin >> y;
		while ( y > gridCollumns ){
			cout << "Wrong Input, give again" << endl;
			cout << "Y:";
			cin >> y;
		}
		if ( gameGrid.getTile( x-1, y-1 )->getType() == ' ' ){
			cout << "You cannot place a hero in a non accesible tile. Try again" << endl;
		}
		else{
			gameGrid.addPlayerToTile( x-1, y-1 );
			heroPositions[0][i] = x-1;
			heroPositions[1][i] = y-1;
			i++;
		}
	}
	gameGrid.displayMap();
	cout << "Exit OR Play?" << endl;
	cout << "X for exit, P for Play" << endl;
	char move;
	cin >> move;
	for ( i = 0; i < playerNum; i ++ ){//dimiourgw kata tin topothetisi ta market, dimiourgei themata an oxi
		if ( gameGrid.getTile( heroPositions[0][i], heroPositions[1][i] )->getType() == 'M' &&
		 gameGrid.getTile( heroPositions[0][i], heroPositions[1][i] )->getPlayers() == 1 ){
			marketArray[i] = new Market( levels, weapons, weaponCount );
		}
		else if ( gameGrid.getTile( heroPositions[0][i], heroPositions[1][i] )->getPlayers() != 1 &&
		 gameGrid.getTile( heroPositions[0][i], heroPositions[1][i] )->getType() == 'M' ){
			int found = 0;
			int same = 0;
			for ( int j = i - 1; j >= 0; j -- ){
				if ( heroPositions[0][i] == heroPositions[0][j] && heroPositions[1][i] == heroPositions[1][j] ){
					found ++;
					same = j;
				}
			}
			if ( found == 0 ){
				marketArray[i] = new Market( levels, weapons, weaponCount );
			}
			else{
				marketArray[i] = marketArray[same];
			}
		}
		else{
				marketArray[i] = NULL;
		}
	}
	while/*if*/ ( move != 'X' ){
		for ( i = 0; i < playerNum; i++ ){
			lastMove[i] = 'F';
			while ( lastMove[i] != 'A' && lastMove[i] != 'S' && lastMove[i] != 'D' && lastMove[i] != 'W' ){
				cout << "Hero " << i + 1 << " moves!" << endl;
				cout << "W for up, A for left, S for down, D for right, I for inventory," << endl << "E for equip or P for Potion, G for the game grid, X for exit,H for Hero's Stats" << endl;
				if ( gameGrid.getTile( heroPositions[0][i], heroPositions[1][i] )->getType() == 'M' ){
					cout << "Hero " << i + 1 << " is in market tile" << endl;
					cout << "You can also press M for check Market, B for buy, N for sell" << endl;
				}
				else if ( gameGrid.getTile( heroPositions[0][i], heroPositions[1][i] )->getType() == 'C' ){
					cout << "Hero " << i + 1 << " is in common tile" << endl;
				}
				cin >> move;
				if ( move == 'M' ){
					if ( gameGrid.getTile( heroPositions[0][i], heroPositions[1][i] )->getType() == 'C' ){
						cout << "Wrong input, Hero " << i + 1 << " is in common tile" << endl;
					}
					else{
						marketArray[i]->checkMarket();
					}
				}
				else if( move == 'H')
				{
					Players[i]-> printInfo();
				}
				else if ( move == 'B' ){
					if ( gameGrid.getTile( heroPositions[0][i], heroPositions[1][i] )->getType() == 'C' ){
						cout << "Wrong input, Hero " << i + 1 << " is in common tile" << endl;
					}
					else{
						marketArray[i]->checkMarket();//isws asxhmo
						cout << "Buy Item or Spell? I for item, S for spell." << endl;
						char choice = 'R';
						while ( choice != 'I' && choice != 'S' ){
							cin >> choice;
						}
						int wantedIndex;
						cout << "Give index of object you want to buy" << endl;
						cin >> wantedIndex;
						int result;
						if ( choice == 'I' ){
							if ( wantedIndex < 15 && wantedIndex >= 0 ){
								result = Players[i]->checkIfBuyItem( marketArray[i]->getItemPointer( wantedIndex ), wantedIndex );
								if ( result == 1 ){
									cout << "Item Bought!" << endl;
								}
							}
							else{
								cout << "Invalid Input" << endl;
							}
						}
						else{
							if ( wantedIndex >= 15 && wantedIndex < 20 ){
								result = Players[i]->checkIfBuySpell( marketArray[i]->getSpellPointer( wantedIndex - 15 ) );
								if ( result == 1 ){
									cout << "Spell Bought!" << endl;
								}
							}
							else{
								cout << "Invalid Input" << endl;
							}
						}
						if ( result < 0 ){
							if ( result == -1 ){
								cout << "Not Enough Money!" << endl;
							}
							else if( result == -2 ){
								cout << "Not In The Minimum Wanted Level!" << endl;
							}
							else{
								cout << "Full Inventory!" << endl;
							}
						}
					}
				}
				else if ( move == 'N' ){
					if ( gameGrid.getTile( heroPositions[0][i], heroPositions[1][i] )->getType() == 'C' ){
						cout << "Wrong input, Hero " << i + 1 << " is in common tile" << endl;
					}
					else{
						int notEmpty = Players[i]->showInventory();
						if ( notEmpty ){
							cout << "Give the position of item or spell you want to sell" << endl;
							int wantedIndex;
							cin >> wantedIndex;
							while ( ( wantedIndex < 3 && Players[i]->getWeaponNum() < wantedIndex ) || ( wantedIndex >= 3 && wantedIndex < 6 && Players[i]->getArmorNum() < wantedIndex - 3 ) ||
							( wantedIndex >= 6 && wantedIndex < 9 && Players[i]->getPotionNum() < wantedIndex - 6 ) ||
							 ( wantedIndex >= 9 && Players[i]->getSpellNum() < wantedIndex - 9 ) ){
								cout << "Wrong Input, empty spot on position you gave!" << endl;
								cout << "Give the position of item or spell you want to sell" << endl;
								cin >> wantedIndex;
							}
							if ( wantedIndex < 9 ){
								Players[i]->sellItem( wantedIndex );
							}
							else{
								Players[i]->sellSpell( wantedIndex - 9 );
							}
						}
					}
				}
				else if( move == 'W' ){
					if ( heroPositions[0][i] == 0 ){
						cout << "Sorry, you're as up as the grid goes!" << endl;
					}
					else if ( gameGrid.getTile( heroPositions[0][i] - 1, heroPositions[1][i] )->getType() == ' ' ){
						cout << "Sorry, you cannot go on a non-Accesible tile!" << endl;
					}
					else{
						gameGrid.removePlayerFromTile( heroPositions[0][i], heroPositions[1][i] );
						heroPositions[0][i] --;
						gameGrid.addPlayerToTile( heroPositions[0][i], heroPositions[1][i] );
					}
					gameGrid.displayMap();
				}
				else if ( move == 'A' ){
					if ( heroPositions[1][i] == 0 ){
						cout << "Sorry, you're as left as the grid goes!" << endl;
					}
					else if ( gameGrid.getTile( heroPositions[0][i], heroPositions[1][i] - 1 )->getType() == ' ' ){
						cout << "Sorry, you cannot go on a non-Accesible tile!" << endl;
					}
					else{
						gameGrid.removePlayerFromTile( heroPositions[0][i], heroPositions[1][i] );
						heroPositions[1][i] --;
						gameGrid.addPlayerToTile( heroPositions[0][i], heroPositions[1][i] );
					}
					gameGrid.displayMap();
				}
				else if ( move == 'S' ){
					if ( heroPositions[0][i] == gameGrid.getLines() - 1 ){
						cout << "Sorry, you're as down as the grid goes!" << endl;
					}
					else if ( gameGrid.getTile( heroPositions[0][i] + 1, heroPositions[1][i] )->getType() == ' ' ){
						cout << "Sorry, you cannot go on a non-Accesible tile!" << endl;
					}
					else{
						gameGrid.removePlayerFromTile( heroPositions[0][i], heroPositions[1][i] );
						heroPositions[0][i] ++;
						gameGrid.addPlayerToTile( heroPositions[0][i], heroPositions[1][i] );
					}
					gameGrid.displayMap();
				}
				else if ( move == 'D' ){
					if ( heroPositions[1][i] ==  gameGrid.getCollumns() - 1 ){
						cout << "Sorry, you're as right as the grid goes!" << endl;
					}
					else if ( gameGrid.getTile( heroPositions[0][i], heroPositions[1][i] + 1 )->getType() == ' ' ){
						cout << "Sorry, you cannot go on a non-Accesible tile!" << endl;
					}
					else{
						gameGrid.removePlayerFromTile( heroPositions[0][i], heroPositions[1][i] );
						heroPositions[1][i] ++;
						gameGrid.addPlayerToTile( heroPositions[0][i], heroPositions[1][i] );
					}
					gameGrid.displayMap();
				}
				else if ( move == 'I' ){
					int notEmpty = Players[i]->showInventory();
				}
				else if ( move == 'E' ){
					int notEmpty = Players[i]->showInventory();
					if ( notEmpty ){
						cout << "Give position of item you want to equip:" << endl;
						int givenIndex;
						cin >> givenIndex;
						Players[i]->equip( Players[i]->getItem( givenIndex ), givenIndex );
					}
					else{
						cout << "No item to equip!" << endl;
					}
				}
				else if ( move == 'P' ){
					cout << "Give position of potion you want to use:" << endl;
					int givenIndex;
					cin >> givenIndex;
					Players[i]->usePotion( givenIndex );
				}
				else if( move == 'G' )
				{
					gameGrid.displayMap();
				}
				else if ( move == 'X' ){
					cout << "Game Over!" << endl;
					return 1;
				}
				else{
					cout << "Wrong input, give your move again" << endl;
				}
				lastMove[i] = move;
			}
			if ( gameGrid.getTile( heroPositions[0][i], heroPositions[1][i] )->getType() == 'M' ){
				if ( gameGrid.getTile( heroPositions[0][i], heroPositions[1][i] )->getPlayers() == 1 ){
					marketArray[i] = new Market( levels, weapons, weaponCount );
				}
				else{
					int found = 0;
					int same = 0;
					for ( int j = 0; j < playerNum; j ++ ){
						if ( heroPositions[0][i] == heroPositions[0][j] && heroPositions[1][i] == heroPositions[1][j] ){
							found ++;
							same = j;
						}
					}
					if ( found == 0 ){
						marketArray[i] = new Market( levels, weapons, weaponCount );
					}
					else{
						marketArray[i] = marketArray[same];
					}
				}
			}
			else if ( gameGrid.getTile( heroPositions[0][i], heroPositions[1][i] )->getType() == 'C' ){
				if ( marketArray[i] != NULL ){
					int found = 0;
					for ( int j = 0; j < playerNum; j ++ ){
						if ( marketArray[i] == marketArray[j] && i != j ){
							found ++;
						}
					}
					if ( found == 0 ){
						delete marketArray[i];
					}
					marketArray[i] = NULL;
				}
			}
		}
		for ( i = 0; i < playerNum; i ++ ){
			int fight = rand() % 2;
			if ( gameGrid.getTile( heroPositions[0][i], heroPositions[1][i] )->getType() == 'C' && fight == 1){
				int found = 0;
				for ( int j = i; j >= 0; j -- ){
					if ( heroPositions[0][j] == heroPositions[0][i] && heroPositions[1][j] == heroPositions[1][i] ){
						found ++;
					}
				}
				if ( found == gameGrid.getTile( heroPositions[0][i], heroPositions[1][i] )->getPlayers() ){
					int playersToBattle = gameGrid.getTile( heroPositions[0][i], heroPositions[1][i] )->getPlayers();
					indexes = new int[playersToBattle];
					int j = 0;
					for ( int k = 0; k <= i; k ++ ){
						if ( heroPositions[0][k] == heroPositions[0][i] && heroPositions[1][k] == heroPositions[1][i] ){
							indexes[j] = k;
							j ++;
						}
					}

					int battleResult = battle( playersToBattle, Players, indexes, levels );

					if( battleResult )
					{
						for ( int i = 0 ; i< playersToBattle ; i++)
						{
							Players[indexes[i]] -> addMoney(4*playersToBattle*Players[indexes[i]]->getLevel());
							Players[indexes[i]] -> setExperience(playersToBattle*100);
							if( Players[indexes[i]] -> getHealthPower() == 0 )
							{
								Players[indexes[i]] -> addHealthPower((50 + Players[indexes[i]] -> getLevel()*5)/2);
							}
							if(Players[indexes[i]]-> getExperience() == (Players[indexes[i]] -> getLevel()+1)*100 )
							{
								Players[indexes[i]] -> levelUp();
								cout << Players[indexes[i]] ->getName() << " leveled up to "<< Players[indexes[i]]->getLevel()<< endl;
							}
						}
					}
					else 
					{
						for(int i = 0; i < playersToBattle; i++)
						{
							Players[indexes[i]] -> addMoney( (-1) * (Players[indexes[i]]->getMoney()/2) );
							Players[indexes[i]] -> addHealthPower((50 + Players[indexes[i]] -> getLevel()*5)/2);
						}
					}
				delete indexes;
				}
			}
		}
	}
	cout << "Game Over!" << endl;
}
