enum PokemonID{};

class Pokemon extends Character{
	private:
		PokemonID id;
	public:
		Attack *performAttack();
}