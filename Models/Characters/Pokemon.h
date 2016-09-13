enum PokemonID{PIKACHU, CHARMANDER};

class Pokemon: public Character{
	private:
		PokemonID id;
//	public:
//		Pokemon(double, double, double, WorldObject);
};

/*Pokemon::Pokemon(double hpMax, double hpCurrent, double width, Point position){
	WorldObject body = WorldObject(position, Dimension, string, Vector2D);
	Character::Character(0, hpMax, hpCurrent, POKEMON, body);
}*/