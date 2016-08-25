class Trainer: public Character{
		private:
			int nPokeballs;
		public:
			Trainer(int, WorldObject);
			Pokeball *throwPokeball();
};

Trainer::Trainer(int nPokeballs, WorldObject body) : Character(0, 0, 0, TRAINER, body){
	this->nPokeballs = nPokeballs;
}

Pokeball *Trainer::throwPokeball(){
	if(nPokeballs > 0){
		Point p = (Point){this->getPosition().x-0.2,this->getPosition().y+0.15};
		WorldObject corpo = WorldObject(p, (Dimension){0.1,0.1}, "ImageResources/pokeball.png", (Vector2D){0,0});
		return new Pokeball(false, corpo);
	}
	return NULL;
}