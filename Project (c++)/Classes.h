#ifndef __CLASSES__
#define __CLASSES__
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class Tile{
	private:
		char type;
		int players;
	public:
		Tile();
		~Tile();
		int getPlayers( void );
		char getType( void );
		void addPlayer( void );
		void removePlayer( void );
};

class Grid{
	private:
		Tile ***tilesArray;
		int lines;
		int collumns;
	public:
		Grid( int givenLines, int givenCollumns );
		~Grid();
		int getLines( void );
		int getCollumns( void );
		Tile* getTile( int, int );
		void displayMap( void );
		void addPlayerToTile( int, int );
		void removePlayerFromTile( int, int );
};

class Item{
		string name;
		int price;
		int minimumLevel;
	public:
		Item();
		Item( string, int, int );
		Item( string, int );//armor
		Item( string, int, int, int );//potion
		virtual ~Item();
		string getName( void );
		int getPrice( void );
		int getMinimumLevel( void );
		virtual void printInfo( void );
		virtual int getStat( string );
		virtual void copyItem( Item* );
};

class Weapon : public Item{
	private:
		int damage;
		int hands;
	public:
		Weapon();
		Weapon( string , int, int );
		virtual ~Weapon();
		int getDamage( void );
		int getHands( void );
		void printInfo( void );
		int getStat( string );
		void copyItem( Item* );
};

class Armor : public Item{
	private:
		int damageDecrease;
	public:
		Armor();
		Armor( string, int );
		virtual ~Armor();
		int getDamageDecrease( void );
		void printInfo( void );
		int getStat( string );
		void copyItem( Item* );
};

class Potion : public Item{
	private:
		int increase;
		int stat;
	public:
		Potion();
		Potion( string , int , int , int );
		virtual ~Potion();
		int getIncrease( void );
		int getStat( void );
		void printInfo( void );
		int getStat( string );
		void copyItem( Item* );
};

class Spell{
	private:
		string name;
		int price;
		int minimumLevel;
		int damageRange;
		int energyNeed;
		int type;
	public:
		Spell();
		Spell( string, int, int, int );
		virtual ~Spell();
		string getName( void );
		int getType( void );
		int getPrice( void );
		int getMinimumLevel( void );
		int getDamageRange( void );
		int getEnergyNeed( void );
		virtual int getDamage( void ) = 0;
		virtual void setDamage( void ) = 0;
		virtual int getDecrease( void ) = 0;
		virtual void printInfo( void );
		virtual void copySpell( Spell* );
		virtual int getRounds( void ) = 0;
};

class Icespell : public Spell{
	private:
		int damage;
		int decrease;
		int rounds;
	public:
		Icespell();
		Icespell( string, int, int, int );
		virtual ~Icespell();
		int getDamage( void );
		void setDamage( void );
		int getDecrease( void );
		void printInfo( void );
		int getRounds( void );
		void copySpell( Spell* );
};

class Firespell : public Spell{
	private:
		int damage;
		int decrease;
		int rounds;
	public:
		Firespell();
		Firespell( string, int, int, int );
		virtual ~Firespell();
		int getDamage( void );
		void setDamage( void );
		int getDecrease( void );
		void printInfo( void );
		int getRounds( void );
		void copySpell( Spell* );
};

class Lightningspell : public Spell{
	private:
		int damage;
		int decrease;
		int rounds;
	public:
		Lightningspell();
		Lightningspell( string, int, int, int );
		virtual ~Lightningspell();
		int getDamage( void );
		void setDamage( void );
		int getDecrease( void );
		void printInfo( void );
		int getRounds( void );
		void copySpell( Spell* );
};

class Market{
	private:
		Item *itemMenu[15];
		Spell *spellMenu[5];
	public:
		Market();
		Market( string*, string*, int );
		~Market();
		void checkMarket( void );
		Item* getItemPointer( int );
		Spell* getSpellPointer( int );
};

class Living{
	private:
		string name;
		int level;
		int healthPower;
		string livingType;
	public:
		Living( string, string );
		Living( string, int, string);
		string getLivingType( void );
		virtual ~Living();
		string getName( void );
		int getLevel( void );
		void addLevel( void );
		void setHealthPower( int );
		int getHealthPower( void );
		void addHealthPower( int );
		virtual void printInfo( void );
};

class Monster : public Living{
	private:
		int damageRange;
		int defense;
		int avoidance;
		int minimumDamage;
	public:
		Monster( string, int, string );
		virtual ~Monster();
		int getDamageRange( void );
		void adjustDamageRange( int );
		int getDefense( void );
		void adjustDefense( int );
		int getAvoidance( void );
		void adjustAvoidance( int );
		int getMinDamage( void );
		virtual void printInfo( void );
		int attack( void );
};

class Dragon : public Monster{
	public:
		Dragon( string, int, string );
		virtual ~Dragon();
		void printInfo( void );
};

class Exoskeleton : public Monster{
	public:
		Exoskeleton( string, int, string );
		virtual ~Exoskeleton();
		void printInfo( void );
};

class Spirit : public Monster{
	public:
		Spirit( string, int, string );
		virtual ~Spirit();
		void printInfo( void );
};

class Hero : public Living{
	private:
		int magicPower;
		int strength;
		int dexterity;
		int agility;
		int money;
		int experience;
		Item *itemInv[9];
		int weaponNum;
		int armorNum;
		int potionNum;
		Spell *spellInv[3];
		int spellNum;
		Item *equipped[3];
		int weaponsEquipped;
		int handsBusy;
		int armorEquipped;
	public:
		Hero( string, string );
		virtual ~Hero();
		void setMagicPower( int );
		int getMagicPower( void );
		void addMagicPower( int );
		int getStrength( void );
		void addStrength( int );
		int getDexterity( void );
		void addDexterity( int );
		int getAgility( void );
		void addAgility( int );
		int getMoney( void );
		void addMoney( int );
		int getExperience( void );
		void setExperience( int );
		int getWeaponsEquipped( void );
		int getHandsBusy( void );
		int getArmorEquipped( void );
		void showEquippedWeapons( void );
		void showEquippedArmor( void );
		virtual void levelUp( void ) = 0;
		virtual void printInfo( void );
		int getWeaponNum( void );
		int getArmorNum( void );
		int getPotionNum( void );
		int getSpellNum( void );
		int checkIfBuyItem( Item*, int );
		int checkIfBuySpell( Spell* );
		void addItemToInv( Item*, int );
		void addSpellToInv( Spell* );
		int showItemInventory( void );
		int showSpellInventory( void );
		int showInventory( void );
		void sellSpell( int );
		void sellItem( int );
		int equipArmor( Item* );
		void unequipArmor( void );
		void unequipWeapon( int );
		int equipWeapon( Item* );
		void equip( Item*, int );
		void showEquipped( void );
		Item *getItem( int );
		void usePotion(  int );
		Spell *getSpell( int );
		int castSpell( Monster*, int );//thewrw oti to teras den mporei na apofigei ksorkia
		int attack( Monster* );
		int getDamageSaved( void );
};

class Warrior : public Hero{
	public:
		Warrior( string, string );
		virtual ~Warrior();
		void levelUp( void );
		void printInfo( void );
};

class Sorcerer : public Hero{
	public:
		Sorcerer( string, string );
		virtual ~Sorcerer();
		void levelUp( void );
		void printInfo( void );
};

class Paladin : public Hero{
	public:
		Paladin( string, string );
		virtual ~Paladin();
		void levelUp( void );
		void printInfo( void );
};

#endif
