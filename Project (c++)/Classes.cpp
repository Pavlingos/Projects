#include <iostream>
#include <string>
#include <cstdlib>
#include "Classes.h"

using namespace std;

//TILE FUNCTIONS
Tile::Tile(){
	
	int randType = rand()% 3;
	if ( randType == 0 ){
		type = 'C';
	}
	else if( randType == 1 ){
		type = 'M';
	}
	else{
		type = ' ';
	}
	players = 0;
}

Tile::~Tile(){
	//destructor of class Tile
}

int Tile::getPlayers( void ){
	
	return players;
}

char Tile::getType( void ){
	
	return type;
}

void Tile::addPlayer( void ){

	players ++;
}

void Tile::removePlayer( void ){

	players --;
}

//GRID FUNCTIONS

Grid::Grid( int givenLines, int givenCollumns ){
			
	lines = givenLines;
	collumns = givenCollumns;
	tilesArray = new Tile**[lines];
	for ( int i = 0; i < lines; i ++ ){
		tilesArray[i] = new Tile*[collumns];
		for ( int j = 0; j < collumns; j ++ ){
			tilesArray[i][j] = new Tile;
		}
	}
	cout << "Grid was created: " << lines << "x" << collumns << endl;
}

Grid::~Grid(){
	for ( int i = 0; i < lines; i ++ ){
		for ( int j = 0; j < collumns; j ++ ){
			delete tilesArray[i][j];
		}
		delete tilesArray[i];
	}
	delete[] tilesArray;
}

int Grid::getLines( void ){
			
	return lines;
}

int Grid::getCollumns( void ){
			
	return collumns;
}

Tile* Grid::getTile( int x, int y ){

	return tilesArray[x][y];
}

void Grid::displayMap( void ){
	
	for ( int i = 0; i < lines; i ++ ){
		for ( int j = 0; j < collumns; j ++ ){
			cout << tilesArray[i][j]->getType();
			if ( tilesArray[i][j]->getPlayers() != 0 ){
				cout << tilesArray[i][j]->getPlayers() << " ";
			}
			else{
				cout << "  ";
			}
		}
		cout << endl;
	}
}
void Grid::addPlayerToTile( int givenX, int givenY ){
		
	tilesArray[givenX][givenY]->addPlayer();
}
void Grid::removePlayerFromTile( int givenX, int givenY ){
	
	tilesArray[givenX][givenY]->removePlayer();
}

//ITEM FUNCTIONS

Item::Item(){
//maybe optional
}

Item::Item( string givenName, int special, int givenLevel ){//weapon
		
	name = givenName;
	minimumLevel = givenLevel;
	price = minimumLevel;
	if ( special == 1 ){
		price += minimumLevel/2;
	}
}

Item::Item( string givenName, int givenLevel ){//armor
		
	name = givenName;
	minimumLevel = givenLevel;
	price = minimumLevel;
}

Item::Item( string givenName, int special, int givenLevel, int givenStat){//potion
			
	name = givenName;
	minimumLevel = givenLevel;
	price = minimumLevel;
	if ( special == 1 ){
		price += minimumLevel/2;
	}
}

Item::~Item(){
	//destructor of class Item		
}

string Item::getName( void ){
			
	return name;
}

int Item::getPrice( void ){
			
	return price;
}

int Item::getMinimumLevel( void ){
	
	return minimumLevel;
}

void Item::printInfo( void ){
			
	cout << "Name: " << name << endl;
	cout << "Price: " << price << endl;
	cout << "Minimum Level: " << minimumLevel << endl;
}

int Item::getStat( string givenStat ){
			
	if ( givenStat.compare( "price" ) == 0 ){
		return getPrice();
	}
	else if( givenStat.compare( "minimumLevel" ) == 0 ){
		return getMinimumLevel();
	}
}

void Item::copyItem( Item *givenItem ){
			
	name = givenItem->getName();
	price = givenItem->getPrice();
	minimumLevel = givenItem->getMinimumLevel();
}

//WEAPON FUNCTIONS

Weapon::Weapon() : Item(){
	//maybe optional			
}

Weapon::Weapon( string givenName, int special, int givenLevel ) : Item( givenName, special, givenLevel ){
			
	if ( special == 0 ){
		hands = 1;
		damage = givenLevel * 5 + 5;
	}
	else{
		hands = 2;
		damage = givenLevel * 7 + 7;
	}
}

Weapon::~Weapon(){
	//destructor of class Weapon
}

int Weapon::getDamage( void ){
	
	return damage;
}
		
int Weapon::getHands( void ){
	
	return hands;
}
		
void Weapon::printInfo( void ){
			
	cout << "Weapon Info." << endl;
	Item::printInfo();
	cout << "Damage: " << damage << endl;
	cout << "Number of hands needed: " << hands << endl;
}
		
int Weapon::getStat( string givenStat ){
	
	if ( givenStat.compare( "hands" ) == 0 ){
		return getHands();
	}
	else if ( givenStat.compare( "damage" ) == 0 ){
		return getDamage();
	}
	else{
		return Item::getStat( givenStat );
	}
}
		
void Weapon::copyItem( Item *givenItem ){
	
	Item::copyItem( givenItem );
	damage = givenItem->getStat( "damage" );
	hands = givenItem->getStat( "hands" );
}

//ARMOR FUNCTIONS

Armor::Armor() : Item(){
	//maybe optional		
}

Armor::Armor( string givenName, int givenLevel ) : Item( givenName, givenLevel ){
	
	damageDecrease = givenLevel * 2 + 7;
}

Armor::~Armor(){
	//destructor of class Armor		
}

int Armor::getDamageDecrease( void ){
			
	return damageDecrease;
}

void Armor::printInfo( void ){
			
	cout << "Armor Info." << endl;
	Item::printInfo();
	cout << "Damage Decrease: " << damageDecrease << endl;
}

int Armor::getStat( string givenStat ){
			
	if ( givenStat.compare( "damageDecrease" ) == 0 ){
		return getDamageDecrease();
	}
	else{
		return Item::getStat( givenStat );
	}
}

void Armor::copyItem( Item *givenItem ){
			
	Item::copyItem( givenItem );
	damageDecrease = givenItem->getStat( "damageDecrease" );
}

//POTION FUNCTIONS

Potion::Potion() : Item(){
	//maybe optional		
}

Potion::Potion( string givenName, int special, int givenLevel, int givenStat ) : Item( givenName, special, givenLevel, givenStat ){
			
	stat = givenStat;
	if ( special == 0 ){
		increase = 1;
	}
	else{
		increase = 2;
	}
}

Potion::~Potion(){
	//destructor of class Potion		
}

int Potion::getIncrease( void ){

	return increase;
}

int Potion::getStat( void ){

	return stat;
}
		
void Potion::printInfo( void ){
			
	cout << "Potion Info." << endl;
	Item::printInfo();
	cout << "Increasing Stat: ";
	switch (stat){
		case 0:
			cout << "Health" << endl;
			break;
		case 1:
			cout << "Magic Power" << endl;
			break;
		case 2:
			cout << "Strength" << endl;
			break;
		case 3:
			cout << "Dexterity" << endl;
			break;
		case 4:
			cout << "Agility" << endl;
			break;
	}
	cout << "Increase Amount: " << increase << endl;
}
		
int Potion::getStat( string givenStat ){
	
	if ( givenStat.compare( "increase" ) == 0 ){
		return getIncrease();
	}
	else if ( givenStat.compare( "stat" ) == 0 ){
		return getStat();
	}
	else{
		return Item::getStat( givenStat );
	}
}
		
void Potion::copyItem( Item *givenItem ){
	
	Item::copyItem( givenItem );
	increase = givenItem->getStat( "increase" );
	stat = givenItem->getStat( "stat" );
}

//SPELL FUNCTIONS

Spell::Spell(){
	//maybe optional		
}
		
Spell::Spell( string givenName, int special, int givenLevel, int givenType ){
	
	name = givenName;
	minimumLevel = givenLevel;
	price = givenLevel;
	energyNeed = givenLevel / 2;
	damageRange = 2 * givenLevel + 10;
	if ( special == 1 ){
		energyNeed *= 2;
		damageRange *= 2;
	}
	type = givenType;
}
		
Spell::~Spell(){
		//constructor of class Spell	
}
		
string Spell::getName( void ){
			
	return name;
}
		
int Spell::getType( void ){
			
	return type;
}
		
int Spell::getPrice( void ){
	
	return price;
}
		
int Spell::getMinimumLevel( void ){
			
	return minimumLevel;
}
		
int Spell::getDamageRange( void ){
				
	return damageRange;
}
		
int Spell::getEnergyNeed( void ){
	
	return energyNeed;
}

void Spell::printInfo( void ){
			
	cout << "Spell Name: " << name << endl;
	cout << "Price: " << price << endl;
	cout << "Minimum Level: " << minimumLevel << endl;
	cout << "Damage Range: " << damageRange << endl;
	cout << "Energy Need: " << energyNeed << endl;
}

void Spell::copySpell( Spell *givenSpell ){
	
	name = givenSpell->getName();
	price = givenSpell->getPrice();
	minimumLevel = givenSpell->getMinimumLevel();
	damageRange = givenSpell->getDamageRange();
	energyNeed = givenSpell->getEnergyNeed();
	type = givenSpell->getType();
}

//ICESPELL FUNCTIONS

Icespell::Icespell(){
	//maybe optional		
}

Icespell::Icespell( string givenName, int special, int givenLevel, int givenType ) : Spell( givenName, special, givenLevel, givenType ){
		
	rounds = ( rand()% 3 ) + 1;
	if ( special == 0 ){
		decrease = givenLevel * 2 + 5;
	}
	else{
		decrease = givenLevel * 3 + 5;
		rounds += 2;
	}
}
		
Icespell::~Icespell(){
	//destructor of class Icespell
}
		
int Icespell::getDamage( void ){
			
	return damage;
}
		
void Icespell::setDamage( void ){
			
	damage = rand()% getDamageRange();
}
		
int Icespell::getDecrease( void ){
			
	return decrease;
}
		
void Icespell::printInfo( void ){
		
	Spell::printInfo();
	cout << "Decrease: " << decrease << endl;
}
		
int Icespell::getRounds( void ){
			
	return rounds;
}
		
void Icespell::copySpell( Spell *givenSpell ){
	
	decrease = givenSpell->getDecrease();
	rounds = givenSpell->getRounds();
	Spell::copySpell( givenSpell );
}

//FIRESPELL FUNCTIONS

Firespell::Firespell(){
	//maybe optional		
}
		
Firespell::Firespell( string givenName, int special, int givenLevel, int givenType ) : Spell( givenName, special, givenLevel, givenType ){
		
	rounds = ( rand()% 3 ) + 1;
	if ( special == 0 ){
		decrease = givenLevel * 2 + 5;
	}
	else{
		decrease = givenLevel * 3 + 5;
		rounds += 2;
	}
}
		
Firespell::~Firespell(){
	//destructor of class firespell	
}
		
int Firespell::getDamage( void ){
			
	return damage;
}
		
void Firespell::setDamage( void ){
			
	damage = rand()% getDamageRange();
}
		
int Firespell::getDecrease( void ){
			
	return decrease;
}
		
void Firespell::printInfo( void ){
			
	Spell::printInfo();
	cout << "Decrease: " << decrease << endl;
}
		
int Firespell::getRounds( void ){
			
	return rounds;
}
		
void Firespell::copySpell( Spell *givenSpell ){
			
	decrease = givenSpell->getDecrease();
	rounds = givenSpell->getRounds();
	Spell::copySpell( givenSpell );
}

//LIGHTNINGSPELL FUNCTIONS

Lightningspell::Lightningspell(){
	//maybe optional		
}
		
Lightningspell::Lightningspell( string givenName, int special, int givenLevel, int givenType ) : Spell( givenName, special, givenLevel, givenType ){
	
	rounds = ( rand()% 3 ) + 1;
	if ( special == 0 ){
		decrease = givenLevel * 2 + 5;
	}
	else{
		decrease = givenLevel * 3 + 5;
		rounds += 2;
	}
}
		
Lightningspell::~Lightningspell(){
	//destructoro of class Lightningspell		
}
		
int Lightningspell::getDamage( void ){
			
	return damage;
}
		
void Lightningspell::setDamage( void ){
			
	damage = rand()% getDamageRange();
}
		
int Lightningspell::getDecrease( void ){
			
	return decrease;
}
		
void Lightningspell::printInfo( void ){
			
	Spell::printInfo();
	cout << "Decrease: " << decrease << endl;
}
		
int Lightningspell::getRounds( void ){
			
	return rounds;
}
		
void Lightningspell::copySpell( Spell *givenSpell ){
	
	decrease = givenSpell->getDecrease();
	rounds = givenSpell->getRounds();
	Spell::copySpell( givenSpell );
}

//MAKET FUNCTIONS

Market::Market(){
	//maybe optional
}
		
Market::Market( string *levelsArray, string *weaponArray, int weaponNumber ){
	
	int i, weapon, lvl, sp;
	string newName;
	for ( i = 0; i < 5; i ++ ){
		weapon = rand()% weaponNumber;
		lvl = rand()% 11;
		sp = rand()% 2;
		newName = weaponArray[weapon] + " lvl." + levelsArray[lvl];
		if ( sp == 0 ){
			newName += " single-Handed";
		}
		else{
			newName += " double-Handed";
		}
		itemMenu[i] = new Weapon( newName, sp, lvl );
	}
	for ( i = 5; i < 10; i ++ ){
		lvl = rand()% 11;
		newName = "Armor lvl." + levelsArray[lvl];
		itemMenu[i] = new Armor( newName, lvl );
	}
	for ( i = 10; i < 15; i ++ ){
		lvl = rand()% 11;
		sp = rand()% 10;// 1/10 to be special
		int stat = rand()% 5;
		switch (stat){
		case 0:
			newName = "Health ";
			break;
		case 1:
			newName = "Magic Power ";
			break;
		case 2:
			newName = "Strength ";
			break;
		case 3:
			newName = "Dexterity ";
			break;
		case 4:
			newName = "Agility ";
			break;
		}
		if ( sp == 1 ){
			newName += "Potion of Excellence, lvl.";
		}
		else{
			newName += "Potion, lvl.";
		}
		newName += levelsArray[lvl];
		itemMenu[i] = new Potion( newName, sp, lvl, stat );
	}
	for ( i = 0; i < 5; i ++ ){
		newName = "";
		sp = rand()% 15; // 1/15 to be special
		lvl = rand()% 11;
		int type = rand()% 3;
		if ( sp == 1 ){
			newName = "Great ";
		}
		if ( type == 0 ){
			newName += "Icespell lvl.";
			newName += levelsArray[lvl];
			spellMenu[i] = new Icespell( newName, sp, lvl, type );
		}
		else if ( type == 1 ){
			newName += "Firespell lvl.";
			newName += levelsArray[lvl];
			spellMenu[i] = new Firespell( newName, sp, lvl, type );
		}
		else{
			newName += "Lightningspell lvl.";
			newName += levelsArray[lvl];
			spellMenu[i] = new Lightningspell( newName, sp, lvl, type );
		}
	}
}
		
Market::~Market(){
	
	for ( int i = 0; i < 15; i ++ ){
		delete itemMenu[i];
	}
	for ( int i = 0; i < 5; i ++ ){
		delete spellMenu[i];
	}
}
		
void Market::checkMarket( void ){
			
	cout << "Item Menu:" << endl;
	for ( int i = 0; i < 15; i ++ ){
		itemMenu[i]->printInfo();
		cout << "Index: " << i << endl << endl;
	}
	for ( int i = 0; i < 5; i ++ ){
		spellMenu[i]->printInfo();
		cout << "Index: " << i + 15 << endl << endl;
	}
}
		
Item* Market::getItemPointer( int givenIndex){
			
	return itemMenu[givenIndex];
}
		
Spell* Market::getSpellPointer( int givenIndex ){
			
	return spellMenu[givenIndex]; 
}

//LIVING FUNCTIONS

Living::Living( string givenName, string givenClass ){

	name = givenName;
	livingType = givenClass;
	level = 0;
	healthPower = 50;
}
		
Living::Living( string givenName, int givenLevel, string givenClass ){

	level = givenLevel;
	livingType = givenClass;
	healthPower = 2 * ( 50 + givenLevel * 5 );
	name = givenName;
}
		
string Living::getLivingType( void ){

	return livingType;
}
		
Living::~Living(){
	//destructor of class Living
}
		
string Living::getName( void ){

	return name;
}
		
int Living::getLevel( void ){

	return level;
}
		
void Living::addLevel( void ){

	level ++;
}

void Living::setHealthPower ( int value ){
			
	healthPower = value ;
}

int Living::getHealthPower( void ){

	return healthPower;
}
		
void Living::addHealthPower( int value ){

	healthPower += value;
}
		
void Living::printInfo( void ){

	cout << "Name: " << name << endl;
	cout << "Level: " << level << endl;
	cout << "Health: " << healthPower << endl;
}

//MONSTER FUNCTIONS

Monster::Monster( string givenName, int givenLevel, string givenClass ) : Living( givenName, givenLevel, givenClass ){

	minimumDamage = givenLevel * 3 + 5;
	damageRange = givenLevel * 3 ;
	defense = givenLevel * 5;
	avoidance = givenLevel/2;
}
		
Monster::~Monster(){

}
		
int Monster::getDamageRange( void ){

	return damageRange;
}
		
void Monster::adjustDamageRange( int value ){

	damageRange += value;
}
		
int Monster::getDefense( void ){

	return defense;
}
		
void Monster::adjustDefense( int value ){

	defense += value;
}
		
int Monster::getAvoidance( void ){

	return avoidance;
}
		
void Monster::adjustAvoidance( int value ){

	avoidance += value;
}
		
int Monster::getMinDamage( void ){

	return minimumDamage;
}
		
void Monster::printInfo( void ){

	cout << "Monster stats." << endl;
	Living::printInfo();
	cout << "Damage Range: " << damageRange << endl;
	cout << "Defense: " << defense << endl;
	cout << "Avoidance: " << avoidance << endl;
	cout << "Minimum Damage: " << minimumDamage << endl;
}
		
int Monster::attack( void ){

	int damage = rand() % ( damageRange + 1 );
	damage += minimumDamage;
	return damage;
}

//DRAGON FUNCTIONS

Dragon::Dragon( string givenName, int givenLevel, string givenClass ) : Monster( givenName, givenLevel, givenClass ){

	adjustDamageRange( givenLevel * 2 );
}
		
Dragon::~Dragon(){
	//destructor of class Dragon
}
		
void Dragon::printInfo( void ){

	Monster::printInfo();
	cout << "Dragon" << endl;
}

//EXOSKELETON FUNCTIONS

Exoskeleton::Exoskeleton( string givenName, int givenLevel, string givenClass ) : Monster( givenName, givenLevel, givenClass ){

	adjustDefense( givenLevel * 2 );
}
		
Exoskeleton::~Exoskeleton(){
	//destructor of class Exoskeleton
}
		
void Exoskeleton::printInfo( void ){

	Monster::printInfo();
	cout << "Exoskeleton" << endl;
}

//SPIRIT FUNCTIONS

Spirit::Spirit( string givenName, int givenLevel, string givenClass ) : Monster( givenName, givenLevel, givenClass ){

	if ( givenLevel > 5 ){
		adjustAvoidance( 2 );
	}
	else{
		adjustAvoidance( 1 );
	}
}
		
Spirit::~Spirit(){
	//destrucor of class Spirit
}
		
void Spirit::printInfo( void ){

	Monster::printInfo();
	cout << "Spirit" << endl;
}

//HERO FUNCTIONS

Hero::Hero( string givenName, string givenClass ) : Living( givenName, givenClass ){

	magicPower = 10;
	strength = 30;
	dexterity = 20;
	agility = 1;
	money = 5;
	experience = 0;
	weaponNum = 0;
	armorNum = 0;
	potionNum = 0;
	spellNum = 0;
	weaponsEquipped = 0;
	handsBusy = 0;
	armorEquipped = 0;
	for ( int i = 0; i < 6; i ++ ){
		itemInv[i] = NULL;
	}
	for ( int i = 0; i < 2; i ++ ){
		spellInv[i] = NULL;
	}
	for ( int i = 0; i < 3; i ++ ){
		equipped[i] = NULL;
	}
}
		
Hero::~Hero(){
	//destructor of class Hero
}
		
void Hero::setMagicPower( int value ){

	magicPower = value;
}

int Hero::getMagicPower( void ){

	return magicPower;
}
		
void Hero::addMagicPower( int value ){

	magicPower += value;
}
		
int Hero::getStrength( void ){

	return strength;
}
		
void Hero::addStrength( int value ){

	strength += value;
}
		
int Hero::getDexterity( void ){

	return dexterity;
}
		
void Hero::addDexterity( int value ){

	dexterity += value;
}
		
int Hero::getAgility( void ){

	return agility;
}
		
void Hero::addAgility( int value ){//na min ftasei = 10

	agility += value;
}
		
int Hero::getMoney( void ){

	return money;
}
		
void Hero::addMoney( int value ){

	money += value;
}
		
int Hero::getExperience( void ){

	return experience;
}
		
void Hero::setExperience( int value ){

	experience = value;
}
		
int Hero::getWeaponsEquipped( void ){

	return weaponsEquipped;
}
		
int Hero::getHandsBusy( void ){

	return handsBusy;
}
		
int Hero::getArmorEquipped( void ){

	return armorEquipped;
}
		
void Hero::showEquippedWeapons( void ){//elegxos apeksw

	equipped[0]->printInfo();
	cout << "Index: 0" << endl;
	if ( weaponsEquipped == 2 ){
		equipped[1]->printInfo();
		cout << "Index: 1" << endl;
	}
}
		
void Hero::showEquippedArmor( void ){

	equipped[2]->printInfo();
	cout << "Index: 2" << endl;
}
		
void Hero::printInfo( void ){

	cout << "Hero stats." << endl;
	Living::printInfo();
	cout << "Magic Power: " << magicPower << endl;
	cout << "Strength: " << strength << endl;
	cout << "Dexterity: " << dexterity << endl;
	cout << "Agility: " << agility << endl;
}
		
int Hero::getWeaponNum( void ){

	return weaponNum;
}
		
int Hero::getArmorNum( void ){

	return armorNum;
}
		
int Hero::getPotionNum( void ){

	return potionNum;
}
		
int Hero::getSpellNum( void ){

	return spellNum;
}
		
int Hero::checkIfBuyItem( Item *givenItem, int givenIndex ){

	if ( givenItem->getPrice() > money ){
		return -1;
	}
	else if( givenItem->getMinimumLevel() > getLevel() ){
		return -2;
	}
	else if ( ( givenIndex < 5 && weaponNum >= 2 ) || ( givenIndex < 10 && givenIndex < 5 && armorNum >= 3 ) ||
	 ( givenIndex < 15 && givenIndex < 10 && potionNum >= 3) ){
		return -3;
	}
	else{
		addItemToInv( givenItem, givenIndex );
		return 1;
	}
}
		
int Hero::checkIfBuySpell( Spell *givenSpell ){

	if ( givenSpell->getPrice() > money ){
		return -1;
	}
	else if( givenSpell->getMinimumLevel() > getLevel() ){
		return -2;
	}
	else if ( spellNum >= 3 ){
		return -3;
	}
	else{
		addSpellToInv( givenSpell );
		return 1;
	}
}
		
void Hero::addItemToInv( Item *givenItem, int givenIndex ){

	if ( givenIndex < 5 ){
		itemInv[weaponNum] = new Weapon;
		itemInv[weaponNum]->copyItem( givenItem );
		itemInv[weaponNum]->printInfo();
		weaponNum ++;
	}
	else if ( givenIndex < 10 ){
		itemInv[3 + armorNum] = new Armor;
		itemInv[3 + armorNum]->copyItem( givenItem );
		itemInv[3 + armorNum]->printInfo();
		armorNum ++;
	}
	else{
		itemInv[6 + potionNum] = new Potion;
		itemInv[6 + potionNum]->copyItem( givenItem );
		itemInv[6 + potionNum]->printInfo();
		potionNum ++;
	}
	money -= givenItem->getPrice();
}
		
void Hero::addSpellToInv( Spell *givenSpell ){

	if ( givenSpell->getType() == 0 ){
		spellInv[spellNum] = new Icespell;
	}
	else if ( givenSpell->getType() == 1 ){
		spellInv[spellNum] = new Firespell;
	}
	else{
		spellInv[spellNum] = new Lightningspell;
	}
	spellInv[spellNum]->copySpell( givenSpell );
	spellInv[spellNum]->printInfo();
	spellNum ++;
	money -= givenSpell->getPrice();
}
		
int Hero::showItemInventory( void ){

	int counter = 0;
	cout << "Item Inventory: " << endl;
	for ( int i = 0; i < 9; i ++ ){
		if ( itemInv[i] != NULL ){
			itemInv[i]->printInfo();
			cout << "Position of this item in the inventory is: " << i << endl << endl;
			counter ++;
		}
	}
	if ( counter == 0 ){
		cout << "Empty Item Inventory" << endl;
	}
	return counter;
}
		
int Hero::showSpellInventory( void ){

	int counter = 0;
	cout << "Spell Inventory: " << endl;
	for ( int i = 0; i < 2; i ++ ){
		if ( spellInv[i] != NULL ){
			spellInv[i]->printInfo();
			cout << "Position of this spell in the inventory is: " << 9 + i << endl << endl;
			counter ++;
		}
	}
	if ( counter == 0 ){
		cout << "Empty Spell Inventory" << endl;
	}
	return counter;
}
		
int Hero::showInventory( void ){

	int counter1 = showItemInventory();
	int counter2 = showSpellInventory();
	return ( counter1 + counter2 );
}
		
void Hero::sellSpell( int givenIndex ){

	money += spellInv[givenIndex]->getPrice()/2;
	spellInv[givenIndex] = NULL;
	spellNum --;
	cout << "Spell sold!" << endl;
}
		
void Hero::sellItem( int givenIndex ){

	money += itemInv[givenIndex]->getPrice();
	itemInv[givenIndex] = NULL;
	if ( givenIndex < 3 ){
		weaponNum --;
	}
	else if ( givenIndex < 6 ){
		armorNum --;
	}
	else{
		potionNum --;
	}
	cout << "Item sold!" << endl;
}
		
int Hero::equipArmor( Item *givenArmor ){

	if ( armorEquipped == 0 ){
		equipped[2] = new Armor;
		equipped[2]->copyItem( givenArmor );
		return 1;
	}
	else{
		return -1;
	}
}
		
void Hero::unequipArmor( void ){

	delete equipped[2];
	equipped[2] = NULL;
}
		
void Hero::unequipWeapon( int givenIndex ){

	delete equipped[givenIndex];
	equipped[givenIndex] = NULL;
}
		
int Hero::equipWeapon( Item *givenWeapon ){

	if ( weaponsEquipped == 2 ){
		cout << "You have already 2 weapons equipped!" << endl;
		return -1;
	}
	else if( handsBusy == 2 ){
		cout << "Both hands are busy!" << endl;
		return -1;
	}
	else{
		equipped[weaponsEquipped] = new Weapon;
		equipped[weaponsEquipped]->copyItem( givenWeapon );
		weaponsEquipped ++;
		return 1;
	}
}
		
void Hero::equip( Item *givenItem, int givenIndex ){

	int result;
	if ( givenIndex < 3 ){
		result = equipWeapon( givenItem );
		if ( result < 0 ){
			cout << "Cannot equip weapon!" << endl;
		}
		else{
			cout << "Weapon equipped!" << endl;
		}
	}
	else if ( givenIndex < 6 ){
		result = equipArmor( givenItem );
		if ( result < 0 ){
			cout << "Cannot equip armor!" << endl;
		}
		else{
			cout << "Armor equipped!" << endl;
		}
	}
	else{
		cout << "This item cannot be equipped!" << endl;
	}
}
		
void Hero::showEquipped( void ){

	cout << "Equipped Items:" << endl;
	for ( int i = 0; i < 3; i ++ ){
		if ( equipped[i] != NULL ){
			equipped[i]->printInfo();
		}
	}
}
		
Item* Hero::getItem( int givenIndex ){

	return itemInv[givenIndex];
}
		
void Hero::usePotion(  int givenIndex ){ 

	if ( itemInv[givenIndex] == NULL || givenIndex < 6 ){
		cout << "No potion in this position" << endl;
	}
	else{
		int givenStat = itemInv[givenIndex]->getStat( "stat" );
		int givenIncrease = itemInv[givenIndex]->getStat( "increase" );
		if ( givenStat == 0 ){
			addHealthPower( givenIncrease * 5 );
			itemInv[givenIndex] = NULL;
			cout << "Potion used!" << endl;
		}
		else if ( givenStat == 1 ){
			addMagicPower( givenIncrease * 2 );
			itemInv[givenIndex] = NULL;
			cout << "Potion used!" << endl;
		}
		else if ( givenStat == 2 ){
			addStrength( givenIncrease * 4 );
			itemInv[givenIndex] = NULL;
			cout << "Potion used!" << endl;
		}
		else if ( givenStat == 3 ){
			addDexterity( givenIncrease * 4 );
			itemInv[givenIndex] = NULL;
			cout << "Potion used!" << endl;
		}
		else{
			char choice = 'Y';
			if ( agility == 9 ){
				cout << "Hero reached max agility, no point in using this potion" << endl;
				cout << "Do you still want to use the potion? Y for yes, N for no" << endl;
				cin >> choice;
			}
			if ( choice == 'Y' ){
				addAgility( givenIncrease );
				if ( agility > 9 ){
					agility == 9;
				}
				itemInv[givenIndex] = NULL;
				cout << "Potion used!" << endl;
			}
			else{
				cout << "Potion not used!" << endl;
			}
		}
	}
}
		
Spell* Hero::getSpell( int givenIndex ){

	return spellInv[givenIndex];
}
		
int Hero::castSpell( Monster *givenMonster, int givenIndex ){//thewrw oti to teras den mporei na apofigei ksorkia

	spellInv[givenIndex]->setDamage();
	int damage = spellInv[givenIndex]->getDamage();
	int decrease = spellInv[givenIndex]->getDecrease();
	int rounds = spellInv[givenIndex]->getRounds();
	int type = spellInv[givenIndex]->getType();
	if ( damage > givenMonster->getHealthPower() ){
		damage = givenMonster->getHealthPower();
	}
	givenMonster->addHealthPower( (-1)*damage );
	if ( type == 0 ){
		givenMonster->adjustDamageRange( (-1)*decrease );
	}
	else if ( type == 1 ){
		givenMonster->adjustDefense( (-1)*decrease );
	}
	else{
		givenMonster->adjustAvoidance( (-1)*decrease );
	}
	magicPower -= spellInv[givenIndex]->getEnergyNeed();
	delete spellInv[givenIndex];
	spellInv[givenIndex] = NULL;//���� ����� �������
	cout << "Hero " << getName() << " dealt " << damage <<" to Monster " << givenMonster -> getName()<< endl;
	return damage;
}
		
int Hero::attack( Monster *givenMonster ){

	int damage;
	int avoid = rand() % 10;
	if ( avoid >= givenMonster->getAvoidance() ){
		cout << "Hero  " << getName() << " attacked successfully!" << endl;
		damage = getStrength();
		for ( int i = 0; i < weaponsEquipped; i ++ ){
			damage += equipped[i]->getStat( "damage" );
		}
		damage -= givenMonster->getDefense();
		if ( damage > 0 ){
			if ( damage > givenMonster->getHealthPower() ){
				damage = givenMonster->getHealthPower();
			}
			givenMonster->addHealthPower( (-1) * damage );
			cout << damage << " damage dealt" << endl;
		}
		else{
			cout << "But no damage was dealt" << endl;
			return 0;
		}
	}
	else{
		cout << "The attack was evaded" << endl;
		return 0;
	}
	return damage;
}
		
int Hero::getDamageSaved( void ){
	
	if ( equipped[2] == NULL ){
		return 0;
	}
	else{
		return equipped[2]->getStat( "damageDecrease" );
	}
}

//WARRIOR FUNCTIONS

Warrior::Warrior( string givenName, string givenClass ) : Hero( givenName, givenClass ){
	//constructor of class Warrior
}
		
Warrior::~Warrior(){
	//destructor of class Warrior
}
		
void Warrior::levelUp( void ){

	addLevel();
	addHealthPower(5);
	addMagicPower(2);
	addStrength(4);
	addDexterity(4);
	addMoney( 4*getLevel() );
	if ( getLevel() == 10 ){
		addAgility(2);
	}
	else{
		if ( ( getLevel() % 3 ) == 0 ){
			addAgility(1);
		}
	}
	setExperience(0);
}
		
void Warrior::printInfo( void ){

	Hero::printInfo();
	cout << "Warrior" << endl;
}

//SORCERER FUCTIONS

Sorcerer::Sorcerer( string givenName, string givenClass ) : Hero( givenName, givenClass ){
	//constructor of class Sorcerer
}
		
Sorcerer::~Sorcerer(){
	//destructor of class Sorcerer
}
		
void Sorcerer::levelUp( void ){

	addLevel();
	addHealthPower(5);
	addMagicPower(2);
	addStrength(2);
	addDexterity(4);
	addMoney( 4*getLevel() );
	if ( getLevel() == 10 ){
		addAgility(2);
		setExperience(0);
	}
	else{
		if ( ( getLevel() % 2 ) == 0 ){
			addAgility(1);
		}
		setExperience( getExperience() + getLevel() * 100 );
	}
}
		
void Sorcerer::printInfo( void ){

	Hero::printInfo();
	cout << "Sorcerer" << endl;
}

//PALADIN FUNCTIONS

Paladin::Paladin( string givenName, string givenClass ) : Hero( givenName, givenClass ){
	//constructor of class Paladin
}
		
Paladin::~Paladin(){
	//destructor of class Paladin
}
		
void Paladin::levelUp( void ){

	addLevel();
	addHealthPower(5);
	addMagicPower(2);
	addStrength(4);
	addDexterity(2);
	addMoney( 4*getLevel() );
	if ( getLevel() == 10 ){
		addAgility(2);
		setExperience(0);
	}
	else{
		if ( ( getLevel() % 2 ) == 0 ){
			addAgility(1);
		}
		setExperience( getExperience() + getLevel() * 100 );
	}
}
		
void Paladin::printInfo( void ){

	Hero::printInfo();
	cout << "Paladin" << endl;
}
